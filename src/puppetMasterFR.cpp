#include "puppetMasterFR.h"

videoElement::videoElementDef *puppetMasterFR::vd = nullptr;

videoElement::videoElementDef *puppetMasterFR::getVideoElementDef()
{
    return puppetMasterFR::vd;
}

puppetMasterFR::puppetMasterFR(std::shared_ptr<chamber> board) : collectible(board), mechanical(board, false), killableElements(board), nonSteppable(board)
{
    // ctor
}

puppetMasterFR::~puppetMasterFR()
{
    // dtor
}
puppetMasterFR::puppetMasterFR() : collectible(), mechanical(), killableElements(), nonSteppable()
{
}
void puppetMasterFR::setCollected(std::shared_ptr<bElem> who)
{
    collectible::setCollected(who);
    if (who.get() != nullptr)
    {
        if (who->getType() == _patrollingDrone) // if collected by the patrolling drone, activate the mechanics
        {
            if (this->getSubtype() == 0) // if subtype not set, set one randomly
            {
                this->setSubtype(1);
                //   this->setSubtype(1+(this->randomNumberGenerator()%50));
            }
            this->registerLiveElement(shared_from_this());
        }
        else if (who->getType() == _player)
            this->playSound("Collect", "Player");
    }
    else if (this->isLiveElement())
        this->deregisterLiveElement(this->getInstanceid()); // if not, we deactivate the elements mechanics, if it is not already disactivated
}

bool puppetMasterFR::mechanics()
{
    bool res = mechanical::mechanics();

    std::shared_ptr<bElem> clc = this->getCollector();
    if (res && clc.get() != nullptr && clc->getType() == _patrollingDrone && clc->getMoved() == 0)
    {
        switch (this->getSubtype()) // here we will route all the mechanics, when we are in the monster
        {
        case 1:
            return this->mechanicsPatrollingDrone();
            break;
        default:
            return false;
        }
    }
    return res;
}

bool puppetMasterFR::mechanicsPatrollingDrone()
{
    std::shared_ptr<bElem> collector = getCollector();
    direction cdir = collector->getDirection();
    direction pdir1 = (direction)((((int)cdir) + 1) % 4);
    direction pdir2 = (direction)((((int)cdir) + 3) % 4);
    bool b1 = false, b2 = false;
    if (collector->getElementInDirection(pdir1))
        b1 = collector->getElementInDirection(pdir1)->isSteppable();
    if (collector->getElementInDirection(pdir2))
        b2 = collector->getElementInDirection(pdir2)->isSteppable();
    int roulette=this->randomNumberGenerator() %55;
    if (b1 && roulette == 5) // same probablility for each
    {
        collector->setDirection(pdir1);
        collector->setWait(3);
        return true;
    }
    else if (b2 && roulette==25)
        {
            collector->setDirection(pdir1);
            collector->setWait(3);
            return true;
        }
    bool r = collector->moveInDirection(cdir);
    if (r == false)
    {
        int f = (this->randomNumberGenerator() % 2 == 0) ? 1 : 3;
        cdir = (direction)((((int)cdir) + f) % 4);
        collector->setDirection(cdir);
        collector->setWait(3);
        return true;
    }
    return r;
}

int puppetMasterFR::getType()
{
    return _puppetMasterType;
}
