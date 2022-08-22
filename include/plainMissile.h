#ifndef PLAINMISSILE_H
#define PLAINMISSILE_H
#include "killableElements.h"
#include "videoElementDef.h"
#include <math.h>
class plainMissile : public killableElements
{
public:
    static videoElement::videoElementDef* vd;
    virtual videoElement::videoElementDef* getVideoElementDef();
    virtual int getType();
    virtual int getSubtype();
    plainMissile(chamber *mychamber);
    plainMissile(chamber *mychamber,int energy);
    void setStatsOwner(bElem* owner);
    virtual ~plainMissile();
    virtual bool mechanics(bool collected);

protected:


    bool killing;
private:
    bElem* statsOwner;
};

#endif // PLAINMISSILE_H
