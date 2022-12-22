#ifndef PLAYER_H
#define PLAYER_H

#include <movableElements.h>
#include "commons.h"
#include "objectTypes.h"
#include "videoElementDef.h"
#include "plainGun.h"

class player : public killableElements,public movableElements,public nonSteppable,public mechanical
{
public:
    player();
    player(std::shared_ptr<chamber> board);
    virtual ~player() =default;
    static unsigned int countVisitedPlayers();
    virtual videoElement::videoElementDef* getVideoElementDef();
    static videoElement::videoElementDef* vd;
    static std::shared_ptr<bElem> getActivePlayer();
    bool mechanics();
    bool interact(std::shared_ptr<bElem> who);
    bool canPush();
    bool getVisited();
    int getType();
    void setActive(bool act);
    bool isActive();
    int getAnimPh();
    virtual bool shootGun();
    virtual oState disposeElement();
    virtual bool additionalProvisioning();

private:
    static std::shared_ptr<bElem> activePlayer;
    static std::vector<std::shared_ptr<bElem>> allPlayers;
    static std::vector<std::shared_ptr<bElem>> visitedPlayers;
    bool visited=false;
    int animPh=0;
    int moved=0;
    int shot=0;
    bool activated=false;
    int used=0;
    int interacted=0;
    bool provisioned=false;
};

#endif // PLAYER_H
