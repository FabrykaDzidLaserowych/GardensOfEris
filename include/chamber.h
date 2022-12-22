#ifndef CHAMBER_H
#define CHAMBER_H
#include "commons.h"
#include "randomWordGen.h"
#include <memory>
typedef struct color {
    int r;
    int g;
    int b;
    int a;
    } colour;
class bElem;
//using boost::multi_array;
class chamber: public std::enable_shared_from_this<chamber>
{
    public:
        static std::shared_ptr<chamber> makeNewChamber(coords csize);
        controlItem cntrlItm;
        int width;
        int height;
        coords player;
        std::shared_ptr<bElem> getElement(int x, int y);
        std::shared_ptr<bElem> getElement(coords point);
        void setElement(int x, int y, std::shared_ptr<bElem> elem);
        void setElement(coords point,std::shared_ptr<bElem> elem);
        explicit chamber(int x,int y);
        explicit chamber(coords csize);
        ~chamber();
        int getInstanceId();
        std::string getName();
        colour getChColour();
        coords getSizeOfChamber();
    private:
        void createFloor();
        std::vector<std::vector<std::shared_ptr<bElem>>> chamberArray;
        colour chamberColour;
        std::string chamberName;
        void setInstanceId(int id);
        int instanceid;
        static int lastid;
};

#endif // CHAMBER_H
