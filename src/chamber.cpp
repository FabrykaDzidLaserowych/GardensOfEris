#include "chamber.h"

chamber::chamber(int x,int y)
{
    this->chamberArray.resize(boost::extents[x][y]);
    this->width=x;
    this->height=y;
    this->garbageBin=gCollect::getInstance();
    for(int cX=0; cX<x; cX++)
    {
        for (int cY=0; cY<y; cY++)
        {
            this->chamberArray[cX][cY]=new bElem(this,cX,cY);
        }
    }
}

chamber::~chamber()
{
    for (int cX=0; cX<this->width; cX++)
    {
        for (int cY=0; cY<this->height;cY++)
        {
            while(this->chamberArray[cX][cY]->disposeElementUnsafe()==DISPOSED);
        }
        this->garbageBin->purgeGarbage();

    }
}

bElem* chamber::getElement(int x, int y)
{
    if (x<0 || x>this->width-1 || y<0 || y>this->height-1)
        return NULL;
    return this->chamberArray[x][y];
}



