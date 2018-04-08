//(*InternalHeaders(SaperFrame)

#include "SaperMain.h"


//*)

bool SaperFrame::sprawdz(int x,int y)
{

    for(int i=0; i<10; i++)
    {
        if(x==cord_bomby_x[i] && y==cord_bomby_y[i])return false;
    }
    return true;
}


bool SaperFrame::czy_jest_bomba(int x,int y)
{

    for(int i=0; i<100; i++)
    {

        if(x==cord_bomby_x[i] && y==cord_bomby_y[i])return true;


    }
    return false;

}

bool SaperFrame::bomby_na_tej_samej_pozycji(int x,int y)
{


    for(int i=0; i<10; i++)
    {
        if((cord_bomby_x[i]==x && cord_bomby_y[i]==y) || (x==0 && y==0))return false;

    }
    return true;

}

