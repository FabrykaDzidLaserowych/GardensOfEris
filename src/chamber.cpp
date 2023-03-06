#include "chamber.h"
#include "floorElement.h"

int chamber::lastid = 0;

std::shared_ptr<chamber> chamber::makeNewChamber(coords csize)
{
#ifdef _VerbousMode_
    std::cout << "generate chamber" << csize.x << "," << csize.y << "\n";
#endif
    std::shared_ptr<chamber> c = std::make_shared<chamber>(csize.x, csize.y);
#ifdef _VerbousMode_
    std::cout << "generated object\n";
#endif
    c->createFloor();
    return c;
}

void chamber::createFloor()
{
#ifdef _VerbousMode_
    std::cout << "Create floor instance [" << this->getInstanceId() << "]\n";
    std::cout << " cfsize [";
#endif
    for (int c = 0; c < this->width; c++)
    {

        std::vector<int> v2(this->height,255);
        this->visitedElements.push_back(v2);

        std::vector<std::shared_ptr<bElem>> v;
        for (int d = 0; d < this->height; d++)
        {
#ifdef _VerbousMode_
            std::cout << "Create an object to place\n";
#endif
            std::shared_ptr<bElem> b = elementFactory::generateAnElement<floorElement>(shared_from_this());
#ifdef _VerbousMode_
            std::cout << "created id " << b->getInstanceid() << "\n";
#endif
            if (bElem::randomNumberGenerator() % 10 == 0)
                b->setSubtype(1);
            if (bElem::randomNumberGenerator() % 100 == 0)
                b->setSubtype(2);
            b->setCoords(c, d);
#ifdef _VerbousMode_
            std::cout << "Push object into column vector id " << b->getInstanceid() << "\n";
#endif
            v.push_back(b);
        }
        this->chamberArray.push_back(v);
#ifdef _VerbousMode_
        std::cout << this->chamberArray.size() << " " << v.size() << " ";
#endif
    }
#ifdef _VerbousMode_
    std::cout << "\n CFsize " << this->chamberArray.size() << " " << this->chamberArray[0].size() << "\n";
#endif
}

coords chamber::getSizeOfChamber()
{
    return (coords)
    {
        (int)this->chamberArray.size(), (this->chamberArray.size() > 0) ? (int)this->chamberArray[0].size() : -1
    };
}

chamber::chamber(int x, int y) : std::enable_shared_from_this<chamber>(), width(x), height(y)
{
    std::shared_ptr<randomWordGen> rwg = std::make_shared<randomWordGen>();
    this->setInstanceId(chamber::lastid++);
    this->chamberName = rwg->generateWord(3);
    this->chamberColour.a = 255;
    this->chamberColour.r = 30 + rwg->randomNumberGenerator() % 50;
    this->chamberColour.g = 30 + rwg->randomNumberGenerator() % 50;
    this->chamberColour.b = 50 + rwg->randomNumberGenerator() % 70;
}
chamber::chamber(coords csize) : chamber(csize.x, csize.y)
{
}

colour chamber::getChColour()
{
    return this->chamberColour;
}

chamber::~chamber()
{
    /*    std::cout<<"Destroy chamber: "<<this->getInstanceId()<<"\n";
        for (unsigned int cX=0; cX<this->chamberArray.size(); cX++)
        {
           this->chamberArray[cX].clear();
        }
        this->chamberArray.clear();

        */
}

std::string chamber::getName()
{
    return this->chamberName;
}

std::shared_ptr<bElem> chamber::getElement(coords point)
{
    return this->getElement(point.x, point.y);
}
bool chamber::visitPosition(coords point)
{
    if(point==NOCOORDS)
        return false;
    float hradius=this->visibilityRadius/2;
    int x0=((point.x-this->visibilityRadius)<0)?0:((point.x-this->visibilityRadius>=this->width)?this->width-1:point.x-this->visibilityRadius);
    int y0=((point.y-this->visibilityRadius)<0)?0:((point.y-this->visibilityRadius>=this->width)?this->width-1:point.y-this->visibilityRadius);
    int x1=((point.x+this->visibilityRadius)<0)?0:((point.x+this->visibilityRadius>=this->width)?this->width-1:point.x+this->visibilityRadius);
    int y1=((point.y+this->visibilityRadius)<0)?0:((point.y+this->visibilityRadius>=this->width)?this->width-1:point.y+this->visibilityRadius);
    for(int x=x0; x<=x1; x++)
    {
        for(int y=y0; y<=y1; y++)
        {
            float distance=std::sqrt((x-point.x)*(x-point.x)+(y-point.y)*(y-point.y));

            if (distance<=hradius)
                this->visitedElements[x][y]=0;
            else if (distance<=this->visibilityRadius && this->visitedElements[x][y]>(distance-hradius)*64)
                this->visitedElements[x][y]=(distance-hradius)*64;
            if(this->visitedElements[x][y]>255)
                this->visitedElements[x][y]=255;
        }
    }
    return true;

}
void chamber::setVisible(coords point,int v)
{
    this->visitedElements[point.x][point.y]=v;
}


int chamber::isVisible(int x, int y)
{
    return this->isVisible((coords)
    {
        x,y
    });
}

int chamber::isVisible(coords point)
{

    if(point.x<this->width && point.y<this->height && point.x>=0 && point.y>=0)
        return this->visitedElements[point.x][point.y];
    return false;

}



std::shared_ptr<bElem> chamber::getElement(int x, int y)
{
    if (x < 0 || y < 0 || (unsigned int)x >= this->chamberArray.size() || (unsigned int)y >= this->chamberArray[x].size())
        return nullptr;
    return this->chamberArray[x][y];
}

void chamber::setElement(int x, int y, std::shared_ptr<bElem> elem)
{
    if (x < 0 || x > this->width - 1 || y < 0 || y > this->height - 1)
        return;
    this->chamberArray[x][y] = elem;
}

void chamber::setElement(coords point, std::shared_ptr<bElem> elem)
{
    this->setElement(point.x, point.y, elem);
}

int chamber::getInstanceId()
{
    return this->instanceid;
}

void chamber::setInstanceId(int id)
{
    this->instanceid = id;
}
