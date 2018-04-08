//(*InternalHeaders(SaperFrame)

#include "SaperMain.h"


//*)
void SaperFrame::OnRightDown(wxMouseEvent& event)
{

    wxPoint size = event.GetPosition();
    wxClientDC  dc(this);
    wxImage img;
    img.LoadFile("flaga_43_A.png",wxBITMAP_TYPE_PNG);
    wxBitmap bm(img);
    wxBrush brush(bm);
    dc.SetBrush(brush);
    zwroc_wspolrzedne(size.x,size.y);

    int aktualne_pole=znajdz_pole(cordy[0],cordy[1]);

    if(cordy_c4[aktualne_pole]==true)//sprawdza czy na danym polu znajduje sie C4
    {
        liczba_pozostalych_bomb++;
        wxImage img;
        img.LoadFile("pole.png",wxBITMAP_TYPE_PNG);
        wxBitmap bm(img);
        wxBrush brush(bm);
        dc.SetBrush(brush);
        dc.DrawRectangle(cordy[0],cordy[1],43,41);
        cordy_c4[aktualne_pole]=false;
    }
    else if(cordy_c4[aktualne_pole]!=true && wygrana[aktualne_pole]==true && liczba_pozostalych_bomb>0)
    {
        liczba_pozostalych_bomb--;
        cordy_c4[aktualne_pole]=true;
        dc.DrawRectangle(cordy[0],cordy[1],43,41);
    }
    dc.SetBrush(wxNullBrush);
}
