#include "../include/bElem.h"

videoElement::videoElementDef* bElem::vd=NULL;
int bElem::instances=0;

int bElem::getInstanceid()
{
   return this->instance;
}

void bElem::resetInstances()
{
    bElem::instances=0;
}



bElem::bElem()
{

    this->init();
}

bElem::bElem(chamber* board, gCollect* garbage)
{
    this->init();
    this->attachedBoard=board;
    this->garbageBin=garbage;

}
bool bElem::isUsable()
{
    return false;
}

bool bElem::isWeapon()
{
    return false;
}


bElem::bElem(chamber* board, gCollect* garbage, int x, int y)
{
    this->init();
    this->attachedBoard=board;
    this->garbageBin=garbage;
    this->x=x;
    this->y=y;
    // If we fail to place the object on a board, we will let it hanging, check, if x or y are ==-1
    if (this->attachedBoard->chamberArray[x][y]!=NULL)
    {


        if (this->stepOnElement(this->attachedBoard->chamberArray[x][y])==false)
        {
            this->x=-1;
            this->y=-1;

        }
    }
    else
    {
        this->attachedBoard->chamberArray[x][y]=this;
    }

}

void bElem::init()
{
    this->attachedBoard=NULL;
    this->garbageBin=NULL;
    this->x=-1;
    this->y=-1;
    this->animPhase=0;
    this->energy=_defaultEnergy;
    this->killed=0;
    this->steppingOn=NULL;
    this->interacted=0;
    this->destroyed=0;
    this->instance=bElem::instances;
    bElem::instances++;
    this->collectedBy=NULL;

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
    this->randomNumberGenerator.seed(seed);
}

bool bElem::setDirection(direction dir)
{
    this->myDirection=dir;
    return true;
}

bool bElem::isInteractive()
{
    return false;
}


void bElem::setBoard(chamber* board)
{
    this->attachedBoard=board;
}

void bElem::setGarbageBin(gCollect* garbage)
{
    this->garbageBin=garbage;
}
direction bElem::getDirection()
{
    return this->myDirection;
}

void bElem::setCoords(int x, int y)
{
    this->x=x;
    this->y=y;
}


// the way it should operate is:
// release the field it is residingg and step on the new one (replace it on a board)
bool bElem::stepOnElement(bElem* step)
{
    if (this->attachedBoard==NULL || this->garbageBin==NULL || step->isSteppable()==false)  return false;
    if (this->steppingOn==NULL)
    {
        this->steppingOn=step;
    }
    else
    {
        this->attachedBoard->chamberArray[this->x][this->y]=this->steppingOn;
        this->steppingOn=step;
    }
    coords crds=this->steppingOn->getCoords();
    this->attachedBoard->chamberArray[crds.x][crds.y]=this;
    this->x=crds.x;
    this->y=crds.y;
    return true;
}

coords bElem::getCoords()
{
    coords mycoords;
    mycoords.x=this->x;
    mycoords.y=this->y;
    return mycoords;
}

oState bElem::disposeElement()
{
    oState res;
    if ( this->garbageBin==NULL )
    {
        #ifdef _debug
        std::cout<<"Tried to dispose broken element!\n";
        #endif
        return ERROR;
    }
    if(this->steppingOn!=NULL && x>=0 && y>=0)
    {
        this->attachedBoard->chamberArray[this->x][this->y]=this->steppingOn; //steppingOn can be NULL, that could mean that someone would have to create an empty field here.
        this->steppingOn=NULL;
        res=(this->attachedBoard->chamberArray[this->x][this->y]==NULL?NULLREACHED:DISPOSED);
    }
    else if (x>=0 && y>=0)
    {
        bElem* be=new bElem(this->attachedBoard,this->garbageBin);
        this->attachedBoard->chamberArray[this->x][this->y]=be;
    }
    else
    {
        res=DISPOSED;
    }
    this->garbageBin->addToBin(this); //add myself to to bin - this should be the only way of the object disposal!
    this->x=-1; //we set the state of the object to be unprovisioned - out of the game.
    this->y=-1;
    this->attachedBoard=NULL;
    this->garbageBin=NULL;
    return res; // false means that there is no more elements to go.
}


/*
 * This method returns absolute coordinates, when asked for coordinates of the next cell in a direction from the elements's standpoint, should be resistant for non-provisioned units
 * better use those on a board though
 */
coords bElem::getAbsCoords(direction dir)
{
    coords res;
    res.x=this->x;
    res.y=this->y;

    switch (dir)
    {
    case UP:
        res.y--;
        break;
    case DOWN:
        res.y++;
        break;
    case LEFT:
        res.x--;
        break;
    case RIGHT:
        res.x++;
        break;
    }
    if (this->attachedBoard==NULL)
        return NOCOORDS;
//    std::cout<<"resxy "<<res.y<<" "<<(this->attachedBoard->width)<<"\n";
    if (res.y>=this->attachedBoard->height || res.y<0 || res.x>=this->attachedBoard->width || res.x<0)
    {
        return NOCOORDS;
    }
    return res;
}

bElem* bElem::getElementInDirection(direction di)
{
    coords mycoords=this->getAbsCoords(di);
    if (mycoords==NOCOORDS)
        return NULL;
    return this->attachedBoard->getElement(mycoords.x,mycoords.y);
}



bElem::~bElem()
{
    if(this->canCollect()==true)
    {
        for(int c=0;c<this->collectedItems.size();c++)
            delete this->collectedItems[c];
        this->collectedItems.clear();
    }

}

int bElem::getType()
{
    return _belemType;
}

int bElem::getSubtype()
{
    return this->subtype;
}

int bElem::getAmmo()
{
  return 0;
}

void bElem::setAmmo()
{
    return;
}


bool bElem::isProvisioned()
{
    if (this->attachedBoard!=NULL && this->x!=-1 && this->y!=-1 && this->garbageBin!=NULL)
        return true;
    return false;
}

bool bElem::moveInDirection(direction d)
{
    return false;
}

bool bElem::use(bElem *who)
{
    return false;
}
bool bElem::getActive()
{
    return true;
}




bool bElem::interact(bElem *who)
{
    if (who!=NULL)
    {
        who->interacted=_interactedTime;
    }
    return false;
}

bool bElem::destroy()
{
    if (this->canBeDestroyed()==true && this->isDestroyed()==false)
    {
        this->destroyed=_defaultDestroyTime;
        return true;
    }
    return false;
}


int bElem::getCnt()
{
    return 0;
}

int bElem::getAnimPh()
{
    // this->animPhase++;
    return this->animPhase/10;
}

int bElem::getSwitchId()
{
    return -1;
}

bool bElem::isMovable()
{
    return false;
}

bool bElem::isActive()
{
    return true;
}

bool bElem::isOpen()
{
    return true;
}

bool bElem::isSwitchOn()
{
    return false;
}

bool bElem::mechanics(bool collected)
{
    this->taterCounter++; //this is our source of sequential numbers
    if (this->steppingOn!=NULL)
    {
        this->steppingOn->mechanics(true);
    }
    this->animPhase++;

    if (this->destroyed>0) //We support two modes of destruction, this one is the demolishion thing
    {
        this->destroyed--;
        if(this->destroyed==0)
        {
            if (this->getType()!=_belemType) //We do not dispose the empty elements
                this->disposeElement();
            return true;
        }
    }

    if(this->killed>0)
    {
        this->killed--;
        if(this->killed==0)
        {
            this->disposeElement(); //it seems we really died. what a waste
            return true;
        }
    }
    if(this->canCollect()==true && this->collectedItems.size()>0)
    {
        for(int cn0=0;cn0<this->collectedItems.size();cn0++)
        {
            this->collectedItems[cn0]->mechanics(true);
        }
    }
    return false;
}

bool bElem::isSteppable()
{
    return true;
}

bool bElem::canBeKilled()
{
    return false;
}

bool bElem::canBeDestroyed()
{
    return false;
}

bool bElem::isSteppableDirection(direction di)
{
    coords tmpcoords;
    tmpcoords=this->getAbsCoords(di);
    if(!(tmpcoords==NOCOORDS))
    {
        if(this->attachedBoard->getElement(tmpcoords.x,tmpcoords.y)!=NULL)
        {
            return this->attachedBoard->getElement(tmpcoords.x,tmpcoords.y)->isSteppable();
        }
    }
    return false;
}


videoElement::videoElementDef* bElem::getVideoElementDef()
{
    return bElem::vd;
}

bool bElem::isDying()
{
    return (this->killed>0)?true:false;
}

bool bElem::isTeleporting()
{
    return false;
}


bool bElem::isCollectible()
{
    return false;
}

bool bElem::canCollect()
{
    return false;
}
// remove element from the board, and return it for further processing(if not needed, run .dispose() on it)
bElem* bElem::removeElement()
{
    if (this->x<0 || this->y<0)
    {
        return NULL;
    }

    if (this->steppingOn!=NULL)
    {
        this->attachedBoard->chamberArray[this->x][this->y]=this->steppingOn;
        this->steppingOn=NULL;
        this->x=-1;
        this->y=-1;
        return this;
    }
    else
    {
        bElem *newElem=new bElem(this->attachedBoard,this->garbageBin,this->x,this->y);
        //we remove the coordinates as well
        this->x=-1;
        this->y=-1;
        this->attachedBoard->chamberArray[this->x][this->y]=newElem;
        return this;
    }
    return NULL; // Should never happen!
}

// this object cannot actively interact with outhers
bool bElem::canInteract()
{
    return false;
}

// Collect another element. The collectible contains location information. that way,
// we restore the element below the collectible, and the collectible will be stored in a vector structure.
// but for now it does nothing
bool bElem::collect(bElem *collectible)
{
    bElem *collected;
    if (this->canCollect()==false)
    {
        return false;
    }
    if (collectible==NULL)
    {
        return false;
    }
    collected=collectible->removeElement();
    if (collected==NULL) //this should never happen!
    {
#ifdef _debug
        std::cout<<"Collecting failed!\n";
#endif
        return false;
    }
#ifdef _debug
    std::cout<<"Collect "<<collected->getType()<<" st: "<<collected->getSubtype()<<"\n";
#endif
    collected->setCollector(this);
    this->collectedItems.push_back(collected);
    return true;
}

bElem* bElem::getCollector()
{
    return this->collectedBy;
}
void bElem::setCollector(bElem* collector)
{
    this->collectedBy=collector;
}





bool bElem::selfAlign()
{
    return false;
}

bool bElem::setSubtype(int st)
{
    this->subtype=st;
    return true;
}

//removes from collection, does not keep the order
bool bElem::removeFromcollection(int position)
{
    if (position>=(int)this->collectedItems.size() || position<0 || (int)this->collectedItems.size()==0)
        return false;
    this->collectedItems[position]->disposeElement();
    this->collectedItems[position]=this->collectedItems[this->collectedItems.size()-1];
    this->collectedItems.pop_back();
    return true;
}


bool bElem::hurt(int points)
{
    if ((this->canBeKilled()==false || this->isDying() ) && this->getEnergy()<=0)
    {
        return false;
    }
#ifdef _debug
    std::cout<<"Hurt me by "<<points<<" points "<<this->getEnergy()<<"\n";
#endif
    this->setEnergy(this->getEnergy()-points);
    if (this->getEnergy()<=0)
        this->kill();
    return true;
}

int bElem::getEnergy()
{
    return this->energy;
}

bool bElem::setEnergy(int points)
{
    this->energy=(points>=0)?points:0;
    return (points==0);
}

bool bElem::kill()
{
    if (this->canBeKilled()==false || this->isDying())
    {
        return false;
    }
    this->killed=_defaultKillTime;
    return true;
}

bool bElem::isDestroyed()
{
    return (this->destroyed>0);
}


