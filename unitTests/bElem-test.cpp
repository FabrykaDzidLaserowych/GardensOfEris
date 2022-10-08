//#ifndef _UNIT_TEST_BUILD_
//#ifndef BELEM_H_INCLUDED
//#define BELEM_H_INCLUDED
#include "bElem.h"
#include "player.h"
#include "mechanical.h"
#include "killableElements.h"
#include "commons.h"
#include "chamber.h"
#include "gCollect.h"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Fixtures
#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>




typedef boost::mpl::list<bElem,killableElements,player,mechanical> test_types;


/* bElem class unit tests */

BOOST_AUTO_TEST_SUITE( BasicObjectTests )
//Create a bElem object, and destroy it - smoke test
BOOST_AUTO_TEST_CASE( bElemCreateDestroy )
{
    // the simpliest possible test case
    bElem* be=new bElem();
    BOOST_CHECK( be!=NULL);
    delete be;

}
//create an object, a whole chamber, and then place an object somewhere, and remove it, very simple case
BOOST_AUTO_TEST_CASE( bElemCreateDestroyChamber)
{
    chamber* chmbr=new chamber(10,10); // we need only a small chamber
    BOOST_ASSERT( chmbr!=NULL );

    for(int c=0; c<chmbr->width; c++) // check that all elements are not null
        for(int d=0; d<chmbr->height; d++)
        {
            bElem* beOrig=chmbr->getElement(c,d);
            BOOST_ASSERT(beOrig!=NULL);
            BOOST_CHECK( beOrig->getType()==_belemType);
            coords crds=beOrig->getCoords();
            BOOST_ASSERT(crds.x==c);
            BOOST_ASSERT(crds.y==d);
            BOOST_CHECK(beOrig->getStomper()==NULL);
            BOOST_ASSERT(beOrig->steppingOn==NULL);
        }

    bElem* beOrig=chmbr->getElement(0,0); // ok, now let's step on something
    bElem* be=new bElem(chmbr);
    BOOST_ASSERT( be!=NULL );
    be->stepOnElement(chmbr->getElement(0,0));
    BOOST_CHECK(be->getBoard()==chmbr);
    bElem* be2=chmbr->getElement(0,0); // check if the element is placed
    BOOST_CHECK(be->getInstanceid()==be2->getInstanceid());
    BOOST_ASSERT(be->steppingOn!=NULL); // something is under the new object
    BOOST_CHECK(be->steppingOn->getInstanceid()==beOrig->getInstanceid()); // check it is original background
    BOOST_CHECK(beOrig->getStomper()!=NULL); // check, that the object below, "knows" it is below.
    BOOST_CHECK(beOrig->getStomper()->getInstanceid()==be->getInstanceid());
    be->removeElement(); // remove the object from the board
    BOOST_CHECK(beOrig->getStomper()==NULL); //check if the original object is being stepped on
    be2=chmbr->getElement(0,0); // fetch the element from the board, and compare it with the original object, there should be a match
    BOOST_CHECK(beOrig->getInstanceid()==be2->getInstanceid());
    BOOST_CHECK(beOrig->getBoard()==chmbr);
    BOOST_CHECK(be->getBoard()==NULL);
    BOOST_CHECK(be->getCoords()==NOCOORDS);
    delete be;
    delete chmbr;


    /*
     Napisać resztę testu - tutaj t
    */



}
bool searchForIdInSteppers(bElem* el,int id)
{
    while(el!=NULL)
    {
        if(id==el->getInstanceid())
            return true;
        el=el->steppingOn;
    }
    return false;
}

int findDepth(bElem* b)
{
    int d=0;
    while(b!=NULL)
    {
        d++;
        if(b->steppingOn)
        {

            b=b->steppingOn;

        }
        else
        {
            return d;
        }

    }
    return d;
}

bElem* findLastStep(bElem* first)
{
    bElem* last=first;
    while(first!=NULL)
    {
        last=first;
        first=first->steppingOn;
    }
    return last;
}

//Place few objects on each other, then remove some from the top, bottom, middle
BOOST_AUTO_TEST_CASE(StackingAndRemovingTest)
{
    chamber* mc=new chamber(5,5);
    bElem* te;
    bElem* te2;
    int ccc=0;
    for(int x=0; x<10; x++)
    {
        bElem* be=new bElem(mc,3,3);
        BOOST_ASSERT(mc->getElement(3,3)->getInstanceid()==be->getInstanceid());
        BOOST_ASSERT(mc->getElement(3,3)->steppingOn!=NULL);
    }
    //we at first take the last element, at the bottom, because it usually causes issues
    te=findLastStep(mc->getElement(3,3));
    te2=te->removeElement();
    if(mc->getElement(3,3)!=NULL) //check if element is really removed
        BOOST_CHECK(searchForIdInSteppers(mc->getElement(3,3),te2->getInstanceid())==false);
    delete te2;
    te=mc->getElement(3,3);
    while(findDepth(mc->getElement(3,3))>2)
    {
        if(te==NULL)
        {
            te=mc->getElement(3,3);
            ccc=0;
        }
        //     std::cout<<"depth="<<ccc<<" "<<findDepth(mc->getElement(3,3))<<" "<<(std::string)((te->steppingOn!=NULL)?"Middle ":"Edge ")<<te->getInstanceid()<<"\n";
        if(bElem::randomNumberGenerator()%2==0)
        {

            //          std::cout<<"Delete\n";
            bElem* te3=te->steppingOn;
            te2=te->removeElement();
            te=te3;
            BOOST_ASSERT(te2!=NULL);
            if(mc->getElement(3,3)!=NULL)
                BOOST_CHECK(searchForIdInSteppers(mc->getElement(3,3),te2->getInstanceid())==false);
            /*            te2=mc->getElement(3,3);
            /*            while(te2!=NULL)
                        {
                            std::cout<<" "<<te2->getInstanceid();
                            te2=te2->steppingOn;
                        }
                        std::cout<<"EndOFDump\n\n";
                        */
            delete te2;
        }
        else
        {
            te=te->steppingOn;
            ccc++;
        }

    }
    delete mc;
    gCollect::getInstance()->purgeGarbage();
}


bool findInstanceInGarbage(int instance)
{
    for(int cnt=0; cnt<gCollect::getInstance()->garbageVector.size(); cnt++)
    {
        if (instance==gCollect::getInstance()->garbageVector[cnt]->getInstanceid())
            return true;
    }
    return false;

}

//Place few objects on each other, then remove some from the top, bottom, middle
BOOST_AUTO_TEST_CASE(StackingAndDisposingTest)
{
    chamber* mc=new chamber(5,5);
    bElem* te;
    int myId;
    for(int x=0; x<10; x++)
    {
        bElem* be=new bElem(mc,3,3);
        BOOST_ASSERT(mc->getElement(3,3)->getInstanceid()==be->getInstanceid());
        BOOST_ASSERT(mc->getElement(3,3)->steppingOn!=NULL);
    }
    te=findLastStep(mc->getElement(3,3));
    myId=te->getInstanceid();
    te->disposeElement();
    if(mc->getElement(3,3)!=NULL)
        BOOST_CHECK(searchForIdInSteppers(mc->getElement(3,3),myId)==false);

    te=mc->getElement(3,3);
    while(mc->getElement(3,3)!=NULL && mc->getElement(3,3)->steppingOn!=NULL)
    {
        if(bElem::randomNumberGenerator()%2==0)
        {

            bElem* te3=te->steppingOn;
            myId=te->getInstanceid();
            te->disposeElement();
            te=te3;
            if(mc->getElement(3,3)!=NULL)
                BOOST_CHECK(searchForIdInSteppers(mc->getElement(3,3),myId)==false);
            BOOST_CHECK(findInstanceInGarbage(myId)==true);

        }
        else
        {
            te=te->steppingOn;
        }
        if(te==NULL)
            te=mc->getElement(3,3);
    }
    delete mc;
    gCollect::getInstance()->purgeGarbage();
}


BOOST_AUTO_TEST_CASE(SubTypeChecker)
{
    bElem* myobj=new bElem();
    for(int x=0; x<10; x++)
    {
        myobj->setSubtype(x);
        BOOST_ASSERT(myobj->getSubtype()==x);
    }
    delete myobj;

}


BOOST_AUTO_TEST_CASE_TEMPLATE(WaitMechanismTest,T,test_types)
{
    chamber* mc=new chamber(5,5);
    bElem* testObj=new T(mc);
    testObj->stepOnElement(mc->getElement(3,3));
    for(int d=1; d<1000; d++)
    {
        int c=0;
        //std::cout<<"d="<<d<<"\n";
        testObj->setWait(d);
        while(testObj->isWaiting())
        {
            BOOST_ASSERT(testObj->mechanics(false)==false); //mechanics is blocked during waiting time
            c++;
            bElem::tick();
        }
        BOOST_ASSERT(testObj->mechanics(false)==true); // mechanics is unblocked after the waiting time
        //std::cout<<"c="<<c<<"\n";
        if(d<=_maxWaitingTtime)
        {
            BOOST_ASSERT(c==d);
        }
        else
        {
            BOOST_ASSERT(c==0);
        }

    }
    delete mc;
    gCollect::getInstance()->purgeGarbage();
}

// Check destroying mechanism. Remember, that for bElem types, the object is not disposed
// We do not check the disposal process itself, as it should be tested with other tests
BOOST_AUTO_TEST_CASE_TEMPLATE(DestroyObjectOnBoard,T,test_types)
{
    chamber* mc=new chamber(5,5);

    bElem* myObj=new T(mc);
    int origType=myObj->getType();
   // std::cout<<"type:"<<myObj->getType()<<" "<<_belemType<<"\n";
    int instance=myObj->getInstanceid();
    bElem::tick();
    myObj->stepOnElement(mc->getElement(3,3));
    myObj->destroy();
    for(int c=0; c<_defaultDestroyTime; c++)
    {
        BOOST_CHECK(mc->getElement(3,3)->isDestroyed()==true);
        bElem::runLiveElements();
    }
    myObj=mc->getElement(3,3);
    BOOST_CHECK(mc->getElement(3,3)->isDestroyed()==false);
    if(origType==_belemType)
    {
        BOOST_CHECK(mc->getElement(3,3)->getInstanceid()==instance);
    }
    else
    {

     BOOST_CHECK(mc->getElement(3,3)->getInstanceid()!=instance);
    }
}

// BOOST_AUTO_TEST_CASE()

BOOST_AUTO_TEST_SUITE_END()





//#endif // BELEM_H_INCLUDED
//#endif
