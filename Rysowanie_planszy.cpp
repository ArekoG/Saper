//(*InternalHeaders(SaperFrame)

#include "SaperMain.h"

//*)

void SaperFrame::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);
    wxImage img;
    img.LoadFile("pole.png",wxBITMAP_TYPE_PNG);
    wxBitmap bm(img);

    wxBrush brush(bm);
    dc.SetBrush(brush);

    srand( time( NULL ) );
    int xx,yy;
    int indeks=0;
    for(int i=0; i<10; i++)
    {
        for(int j=0; j<10; j++)
        {
            xx=(i) *43;
            yy=(j)*41;
            dc.DrawRectangle(xx,yy,43,41);
            cordy_mapy_x[indeks]=xx;
            cordy_mapy_y[indeks]=yy;
            wygrana[indeks]=true;
            indeks+=1;
        }

    }
    for(int j=0; j<10; j++)
    {
        do
        {
            xx=rand()%10 *43;
            yy=rand()%10*41;
        }
        while(bomby_na_tej_samej_pozycji(xx,yy)==false);

        cord_bomby_x[j]=xx;
        cord_bomby_y[j]=yy;

    }
    zliczanie_bomb();


    dc.SetBrush(wxNullBrush);
}
