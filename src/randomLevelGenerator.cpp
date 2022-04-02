#include "randomLevelGenerator.h"

randomLevelGenerator::randomLevelGenerator(int w, int h,gCollect *gbin)
{
    this->width=w;
    this->height=h;
    this->mychamber=new chamber(w,h,gbin);
    this->garbageCollector=gbin;
    std::random_device rd;
    std::mt19937::result_type seed = rd() ^ (
                                         (std::mt19937::result_type)
                                         std::chrono::duration_cast<std::chrono::seconds>(
                                                 std::chrono::system_clock::now().time_since_epoch()
                                         ).count() +
                                         (std::mt19937::result_type)
                                         std::chrono::duration_cast<std::chrono::microseconds>(
                                                 std::chrono::high_resolution_clock::now().time_since_epoch()
                                         ).count() );
    this->gen.seed(seed);
    //ctor
}

randomLevelGenerator::~randomLevelGenerator()
{
    //dtor
}


int randomLevelGenerator::checkWalls(int x, int y)
{
    bool  walls[]= {false,false,false,false};
    if (x>0)
    {
        if (this->mychamber->chamberArray[x-1][y]->getType()==_wallType) walls[0]=true;
    }
    if (x<this->mychamber->width)
    {
        if (this->mychamber->chamberArray[x+1][y]->getType()==_wallType) walls[1]=true;

    }
    if (y>0)
    {
        if (this->mychamber->chamberArray[x][y-1]->getType()==_wallType) walls[2]=true;
    }
    if (y<this->mychamber->height)
    {
        if (this->mychamber->chamberArray[x][y+1]->getType()==_wallType) walls[3]=true;

    }
    if (walls[0] && walls[1] && walls[2] && !walls[3])
    {
        this->mychamber->chamberArray[x-1][y]->disposeElement();
        this->mychamber->chamberArray[x][y]=new wall(this->mychamber,this->garbageCollector);
    }
    if (walls[0] && walls[1] && walls[3] && !walls[2])
    {
        this->mychamber->chamberArray[x+1][y]->disposeElement();
    }

    if (walls[0] && !walls[1] && walls[3] && walls[2])
    {
        this->mychamber->chamberArray[x][y+1]->disposeElement();
    }
    if (!walls[0] && walls[1] && walls[3] && walls[2])
    {
        this->mychamber->chamberArray[x][y-1]->disposeElement();
    }


    return 0;
}


int randomLevelGenerator::lvlGenerate(int x1, int y1, int x2, int y2,int depth,int holes,std::string loc)
{

    std::vector<int> doorPlaces1,doorPlaces2;
    int Hmin_=((y2-y1)/(1+loc.size()));
    int Wmin_=((x2-x1)/(1+loc.size()));
    int sa=0,sb=0,sc=0,sd=0;
    int surface;
    int blind=4; // this->gen()%4;
    if(Hmin_<Hmin)
        Hmin_=Hmin;
    if(Wmin_<Wmin)
        Wmin_=Wmin;

    int c=-1,dc1=-1,dc2=-1;
    int d=-1,dd1=-1,dd2=-1;
    //  bElem *belem;
    int dx,dy;
    if (depth<0)
    {
        surface=((x2-x1)*(y2-y1));
        this->endChambers.push_back({x1,y1,x2,y2,surface,false,loc});

        return surface;
    }

#ifdef _debugRandomGenerator
    std::cout<<"x1,y1 "<<x1<<","<<y1<<" x2,y2: "<<x2<<","<<y2<<" loc:"<<loc<<"\n";
#endif
    dx=x2-x1;
    dy=y2-y1;
    if (dx>Wmin_) // tutaj trzeba zrobić ograniczenie
        // Im krótsza ścieżka, tym wmin bliższe 1/3 planszy
    {

        c=(this->gen() % (dx-Wmin_)) +x1+(Wmin_/2); //find vertical divider location
        dc1=c-x1;
        dc2=x2-c+2;

    }
    //else return 0;
    if (dy>Hmin_)
    {
        d=(this->gen()%(dy-Hmin_)) +y1+(Hmin_/2);  // horizontal divider
        dd1=d-y1;
        dd2=y2-d+2;
    }

    if (dc1>Wmin && dd1>Hmin)
    {
        sa=this->lvlGenerate(x1,y1,c,d,depth-1,holes,loc+"a");
    }


    if (dc2>Wmin && dd1>Hmin)
    {
        sb=this->lvlGenerate(c+2,y1,x2,d,depth-1,holes,loc+"b");
    }

    if (dd2>Hmin && dc1>Wmin)
    {
        sc=this->lvlGenerate(x1,d+2,c,y2,depth-1,holes,loc+"d");
    }

    if (dd2>Hmin && dc2>Wmin)
    {
        sd=this->lvlGenerate(c+2,d+2,x2,y2,depth-1,holes,loc+"c");
    }
    doorPlaces1.clear();
    doorPlaces2.clear();
    if (c>x1 && c<x2 && d>0)
    {
        for (int a=y1; a<=y2; a++)
        {
            if (a!=d && this->mychamber->chamberArray[c][a]->isSteppable()==true && this->mychamber->chamberArray[c+2][a]->isSteppable()==true)
            {
                if (a<d+2)
                {
                    doorPlaces1.push_back(a);
                }
                else
                {
                    doorPlaces2.push_back(a);
                }
            }
            if (this->mychamber->chamberArray[c+1][a]->isSteppable())
            {
                bElem *newElement=new wall(this->mychamber,this->garbageCollector);
                newElement->stepOnElement(this->mychamber->chamberArray[c+1][a]);
            }
            else
            {
                break;
            }
        }
#ifdef _debugRandomGenerator
        std::cout<<" * "<<doorPlaces1.size()<<" "<<doorPlaces2.size()<<" "<<loc<<" "<<"c,d: "<<c<<","<<d<<"\n";
        int hits=0,hits1=0;
#endif
        for (int cnt=0; cnt<holes; cnt++)
        {
            if (blind!=0 && doorPlaces1.size()>0)
            {
                int rnd=this->gen()%(doorPlaces1.size());
                this->mychamber->chamberArray[c+1][doorPlaces1[rnd]]->disposeElement();
                doorPlaces1[rnd]=doorPlaces1[doorPlaces1.size()-1];
                doorPlaces1.pop_back();
#ifdef _debugRandomGenerator
                hits++;
#endif
            }
            if (blind!=1 && doorPlaces2.size()>0)
            {
                int rnd=this->gen()%(doorPlaces2.size());
                this->mychamber->chamberArray[c+1][doorPlaces2[rnd]]->disposeElement();
                //if(rnd<doorPlaces2.size()-1)
                doorPlaces2[rnd]=doorPlaces2[doorPlaces2.size()-1];
                doorPlaces2.pop_back();
#ifdef _debugRandomGenerator
                hits1++;
#endif
            }
        }
#ifdef _debugRandomGenerator
        if(hits==0 || hits1==0)
        {
            std::cout<<"Zero hits! "<<hits<<" "<<hits1<<" "<<loc<<"\n";
        }
#endif
    }
    if (d>y1 && d<y2 && c>=0)
    {
#ifdef _debugRandomGenerator
        int hits=0,hits1=0;
#endif
        doorPlaces1.clear();
        doorPlaces2.clear();
        for (int a=x1; a<=x2; a++)
        {
            if (a!=c && this->mychamber->chamberArray[a][d]->isSteppable()==true && this->mychamber->chamberArray[a][d+2]->isSteppable()==true)
            {
                if (a<c+2)
                {
                    doorPlaces1.push_back(a);
                }
                else
                {
                    doorPlaces2.push_back(a);
                }
            }
            if (mychamber->chamberArray[a][d+1]->isSteppable())
            {
                bElem *newElement=new wall(this->mychamber,this->garbageCollector);
                newElement->stepOnElement(this->mychamber->chamberArray[a][d+1]);
            }
        }
        for (int cnt=0; cnt<holes; cnt++)
        {
            if (blind!=2 && doorPlaces1.size()>0)
            {
                int rnd=this->gen()%(doorPlaces1.size());
                this->mychamber->chamberArray[doorPlaces1[rnd]][d+1]->disposeElement();
                doorPlaces1[rnd]=doorPlaces1[doorPlaces1.size()-1];
                doorPlaces1.pop_back();
#ifdef _debugRandomGenerator
                hits++;
#endif

            }
        }
        for (int cnt=0; cnt<holes; cnt++)
        {

            if (blind!=3 && doorPlaces2.size()>0)
            {
                int rnd=this->gen()%(doorPlaces2.size());
                this->mychamber->chamberArray[doorPlaces2[rnd]][d+1]->disposeElement();
                doorPlaces2[rnd]=doorPlaces2[doorPlaces2.size()-1];
                doorPlaces2.pop_back();
#ifdef _debugRandomGenerator
                hits1++;
#endif

            }
        }
#ifdef _debugRandomGenerator
        if(hits==0 || hits1==0)
        {
            std::cout<<"Low hits! "<<hits<<" "<<hits1<<" "<<loc<<"\n";
        }
#endif
    }
    surface=(dc1!=-1 && dd1!=-1)?sa+sb+sc+sd:((x2-x1)*(y2-y1));
    this->endChambers.push_back({x1,y1,x2,y2,surface,false,loc});
    return surface;
}



void randomLevelGenerator::addElementToPlace(elementToPlace element)
{
    this->elementsToPlace.push_back(element);
}

bool randomLevelGenerator::qualifies(std::string itemLoc, std::string chamLoc)
{
    if (chamLoc.size()<itemLoc.size())
        return false;
    for(int c=0; c<itemLoc.size(); c++)
    {
        if (itemLoc.at(c)!=chamLoc.at(c))
            return false;
    }
    return true;
}

int randomLevelGenerator::recalculateLocations()
{
    int c=0;
    int sGlobal=0;
    for(c=0; this->endChambers.size()>c; c++)
    {
        if(this->endChambers[c].banned==false)
        {
            int s=0;
            for(int x=this->endChambers[c].x0; x<=this->endChambers[c].x1; x++)
            {
                for (int y=this->endChambers[c].y0; y<=this->endChambers[c].y1; y++)
                {
                    if(this->isLocationAllowed(x,y) && this->mychamber->chamberArray[x][y]->isSteppable())
                    {
                        sGlobal++;
                        s++;
                        this->endChambers[c].surface=s;
                    }
                }
            }

        }
        else
        {
            this->endChambers[c].surface=0;
        }
    }
    return sGlobal;
}



bool randomLevelGenerator::claimSpace(spaceToCreate theClaim)
{
    rectangle spaces[5];
    std::string bLocation;
    int votedSpaceNo=this->gen()%5;
    int s=theClaim.surface*2;
    for(int c=0; c<5; c++)
    {
        spaces[c].surface=-1;
    }

    for(int c=0; c<this->endChambers.size(); c++)
    {
        if(this->endChambers[c].banned==false && this->endChambers[c].surface>=s)
        {
            for (int c1=0; c1<5; c1++)
            {
                if(spaces[c1].surface==-1)
                {
                    spaces[c1].surface=this->endChambers[c].surface;
                    break;
                }
                if(spaces[c1].surface>this->endChambers[c].surface)
                {
                    spaces[c1]=this->endChambers[c];
                    break;
                }
            }
        }

    }
    bLocation=spaces[votedSpaceNo].location;
   // bLocation.resize(spaces[votedSpaceNo].location.size()-1);
    // ok, now in array spaces, we have 5 candidates, to be picked., so we randomly try to pick one;
    //spaces[votedSpaceNo] - is our space:)
    if(theClaim.closing==doorTypeA || theClaim.closing==doorTypeB || theClaim.closing==teleport)
    {
        this->banLocation(bLocation);
    }
    return true;
}

bool randomLevelGenerator::banLocation(std::string loc)
{
    std::string bLocation=loc;
    bLocation.resize(loc.size()-1);
    for (int c2=0; c2>this->endChambers.size(); c2++)
    {
        if(this->endChambers[c2].banned==false && this->endChambers[c2].location==bLocation)
        {
            //We ban added location
            this->endChambers[c2].banned=true;
            break;
        }
    }
    return true;
}


bool randomLevelGenerator::generateLevel(int holes)
{
    int surface=this->lvlGenerate(1,1,this->width-2,this->height-2,_iterations,holes,"B");
    for(int c=0; c<this->width; c++)
    {
        bElem *newElem=new wall(this->mychamber,this->garbageCollector);
        bElem *newElem1=new wall(this->mychamber,this->garbageCollector);
        newElem->stepOnElement(this->mychamber->chamberArray[c][0]);
        newElem1->stepOnElement(this->mychamber->chamberArray[c][this->height-1]);

    }
    for(int c=0; c<this->height; c++)
    {

        bElem *newElem2=new wall(this->mychamber,this->garbageCollector);
        bElem *newElem3=new wall(this->mychamber,this->garbageCollector);
        newElem2->stepOnElement(this->mychamber->chamberArray[0][c]);
        newElem3->stepOnElement(this->mychamber->chamberArray[this->width-1][c]);
    }
    /*
    Create content:
    * spacesToCreate - each has a demanded surface
    * we iterate first through the spacesToBeCrested, then we look for a rectangle in endchambers that has appropriate capacity
         we seek for the 5 most fit (with deltas close to 0 as possible) and then we randomly choose the space.
    * space can be closed with doors (of different kinds), we create the keys outside the area.
    To do that, we perform this->findSpotsToChoose on one of the neighbooring structures, if that fails, we cut one letter from the end,
    and change test neighboors of that location.
    * if it is teleport, we leave blind walls and place a teleporter inside and outside the area (similar way as with the keys)
    */

    /*
    Generate random content.
    Player added last, because of door/key management.
    We got available surface, so we can calculate how many objects we would like to add. The 'holes' parameter will also be used to calculate how many objects we need.
    to formula would be:
    totalObjs=(surface/(holes*k)) - that would result in how many objects we want to create; - k-magic number
    divider=2+(rand()%10)
    collectibles=totalObj/divider
    totalObj=totalObj-collectibles
    divider=2+(rand()%10)
    rougeObj=totalObj/divider
    other=totalObj-rougeObj

    we will get this way required number of objects for each category:
    collectibles - { list of collectible items}
    rougeObjects - {Monsters, turrets, tanks and other like that}
    other - { weapons, bombs }





    */
    //  this->recalculateLocations();


    return true;

}

/*bool randomLevelGenerator::addSpaceToCreate(spaceToCreate spc)
{
    this->spacesToCreate.push_back(spc);
}
*/

int randomLevelGenerator::findSpotsToChoose(std::string location)
{
    /*
    Find all steppable and allowed spots at the location, returns the total amount of free points
    */
    this->spotsToChoose.clear();
    int surface=0;

    for(int c=0; c<this->endChambers.size(); c++)
    {
        if (this->endChambers[c].banned==false && location==this->endChambers[c].location)
        {
            for(int x=this->endChambers[c].x0; x<=this->endChambers[c].x1; x++)
            {
                for (int y=this->endChambers[c].y0; y<=this->endChambers[c].y1; y++)
                {
                    if (this->mychamber->chamberArray[x][y]->isSteppable() && this->isLocationAllowed(x,y)==true && this->steppableNeighs(x,y)>3)
                    {

                        this->spotsToChoose.push_back({x,y});
                        surface++;
                    }
                }
            }
        }
    }
    return surface;
}
bool randomLevelGenerator::isLocationAllowed(int x, int y)
{
    /*
    Checks if the location is allowed. It does that by examining all the allowed rectangles made by the maze generator.
    And then comparing the coordinates with the rectangle topleft and downright corners
    */
    for (int c=0; c<this->endChambers.size(); c++)
    {
        if (this->endChambers[c].banned==true && this->endChambers[c].x0>=x && this->endChambers[c].x1<=x && this->endChambers[c].y0>=y && this->endChambers[c].y1<=y)
        {
            return false;
        }
    }
    return true;
}


bool randomLevelGenerator::placeDoors(elementToPlace element,std::string location)
{
    /*
    Place doors at the location

    */

    for(int c=0; c<this->endChambers.size(); c++)
    {
        if (location==this->endChambers[c].location)
        {
            this->endChambers[c].banned=true;
            //Ok, now we need to place the door.
            for(int c1=this->endChambers[c].x0-1; c1<=this->endChambers[c].x1+1; c1++)
            {
                if (this->mychamber->chamberArray[c1][this->endChambers[c].y0-1]->isSteppable())
                {
                    bElem* neEl=this->createElement(element);
                    neEl->stepOnElement(this->mychamber->chamberArray[c1][this->endChambers[c].y0-1]);
                }
                if (this->mychamber->chamberArray[c1][this->endChambers[c].y1+1]->isSteppable())
                {
                    bElem* neEl=this->createElement(element);
                    neEl->stepOnElement(this->mychamber->chamberArray[c1][this->endChambers[c].y1+1]);
                }
            }
            for (int c2=this->endChambers[c].y0; c2<=this->endChambers[c].y1; c2++)
            {
                if (this->mychamber->chamberArray[this->endChambers[c].x0-1][c2]->isSteppable())
                {
                    bElem* neEl=this->createElement(element);
                    neEl->stepOnElement(this->mychamber->chamberArray[this->endChambers[c].x0-1][c2]);
                }
                if (this->mychamber->chamberArray[this->endChambers[c].x1+1][c2]->isSteppable())
                {
                    bElem* neEl=this->createElement(element);
                    neEl->stepOnElement(this->mychamber->chamberArray[this->endChambers[c].x1+1][c2]);
                }

            }

            break;
        }
    }
    return true;
}
int randomLevelGenerator::steppableNeighs(int x, int y)
{
    int res=0;
    for (int c=0;c<4;c++)
    {
        if (this->mychamber->getElement(x,y)->isSteppableDirection((direction)(c))==true)
        {
           res++;
        }
    }
    return res;
}

bool randomLevelGenerator::placeElement(elementToPlace element,std::string location)
{
    /*
    Place element in location.
    Remember, the element actually can contain more than one element of the same kind.
    */
    int rnd=0;
    int surface=0;
    std::vector<rectangle> candidates;

    surface=this->findSpotsToChoose(location);
    if (surface==0)
        return false;

    if (element.eType==_door)
    {
        return this->placeDoors(element,location);
    }

    for(; element.number>0; element.number--)
    {

        if(this->spotsToChoose.size()<=0)
        {
            break; // no more spots to place anything
        }
        rnd=this->gen()%this->spotsToChoose.size();
        coords tmp;
        bElem *newElem=this->createElement(element);
        if (newElem==NULL)
        {
            return false; // we failed to place elements
        }
        newElem->stepOnElement(this->mychamber->chamberArray[this->spotsToChoose[rnd].x][this->spotsToChoose[rnd].y]);

        if (newElem->selfAlign()==true)
        {
            surface=this->findSpotsToChoose(location);
        }
        else
        {
            this->spotsToChoose[rnd]=this->spotsToChoose[spotsToChoose.size()-1];
            this->spotsToChoose.pop_back();
            surface--;
        }
    }
    if(element.number>0)
        return false; // we failed to place all the elements
    return true;
}

bElem* randomLevelGenerator::createElement(elementToPlace element)
{
    switch(element.eType)
    {
    case _collectible:
        return new collectible(this->mychamber,this->garbageCollector);
        break;
    case _player:
        return new player(this->mychamber,this->garbageCollector);
        break;
    case _door:
        return new door(this->mychamber,this->garbageCollector,element.eSubType);
        break;
    case _key:
        return new key(this->mychamber,this->garbageCollector,element.eSubType);
        break;
    case _monster:
        return new monster(this->mychamber,this->garbageCollector);
        break;
    case _plainGun:
        return new plainGun(this->mychamber,this->garbageCollector);
        break;
    case _bunker:
        return new bunker(this->mychamber,this->garbageCollector);
        break;
    }
    return NULL;
}



