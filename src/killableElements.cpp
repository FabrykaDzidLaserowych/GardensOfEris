#include "killableElements.h"

killableElements::killableElements(chamber* board,gCollect* garbageBin) :movableElements(board,garbageBin)
{
    this->movable=false;
}

killableElements::killableElements(chamber* board, gCollect* garbageBin, int x, int y):movableElements(board,garbageBin,x,y)
{
    this->movable=false;
}

bool killableElements::mechanics(bool collected)
{
    bool res=movableElements::mechanics(collected);
    if(this->killed>0)
    {
        this->killed--;
        if(this->killed==0)
        {
            this->disposeElement(); //it seems we really died. what a waste
            return true;
        }
    }
    return res;
}



killableElements::~killableElements()
{
    //dtor
}
bool killableElements::canBeKilled()
{
    return (!this->isDying());
}

bool killableElements::canBeDestroyed()
{
    return (!this->isDying());
}




bool killableElements::hurt(int points)
{
   if (this->canBeKilled()==false)
    {
        return false;
    }
    this->setEnergy(this->getEnergy()-points);
    if (this->getEnergy()<=0)
        this->kill();
    return true;
}

bool killableElements::kill()
{
    if (this->canBeKilled()==false)
    {
        return false;
    }
    this->killed=_defaultKillTime;
    return true;
}

