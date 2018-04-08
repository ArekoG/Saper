/***************************************************************
 * Name:      SaperMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Arkadiusz Gajda,Daniel Jedrzejczyk ()
 * Created:   2017-12-29
 * Copyright: Arkadiusz Gajda,Daniel Jedrzejczyk ()
 * License:
 **************************************************************/




//(*InternalHeaders(SaperFrame)

#include "SaperMain.h"
#include "SaperApp.h"
#include <pthread.h>
//*)

//helper functions
enum wxbuildinfoformat
{
    short_f, long_f
};

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(SaperFrame)
const long SaperFrame::idMenuQuit = wxNewId();
const long SaperFrame::idMenuAbout = wxNewId();
const long SaperFrame::idMenuRules = wxNewId();
const long SaperFrame::idBomby = wxNewId();
const long SaperFrame::idNewGame = wxNewId();
const long SaperFrame::idRekord = wxNewId();
//*)

BEGIN_EVENT_TABLE(SaperFrame,wxFrame)
    //(*EventTable(SaperFrame)

    //*)


    EVT_LEFT_DOWN(SaperFrame::OnLeftDown)
    EVT_RIGHT_DOWN	(SaperFrame::OnRightDown)
    EVT_PAINT(SaperFrame::OnPaint)
    EVT_MOTION	(SaperFrame::Najechanie)


END_EVENT_TABLE()
double SaperFrame::aktualny_czas;
bool SaperFrame::koniec;
void *SaperFrame::licz_czas(void * data)
{


    aktualny_czas=1;
    while(!koniec)
    {
        Sleep(1000);
        aktualny_czas++;

    }


    return NULL;
}



SaperFrame::SaperFrame(wxWindow* parent,wxWindowID id)
{



    Create(parent, id, wxEmptyString, wxDefaultPosition, wxSize(445, 469), wxDEFAULT_FRAME_STYLE, _T("id"));



    liczba_pozostalych_bomb=10;
    Connect(idRekord,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SaperFrame::Pokaz_rekord);
    Connect(idMenuRules,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SaperFrame::OnAbout);
    Connect(idBomby,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SaperFrame::OnAbout);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SaperFrame::Rules);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SaperFrame::OnQuit);
    Connect(idNewGame,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SaperFrame::New_game);


    stworz_menu();


    this->Center();


}



SaperFrame::~SaperFrame()
{
    //(*Destroy(SaperFrame)
    //*)

    aktualny_czas=0;
    for(int i=0; i<100; i++)
    {
        liczba_bomb_obok[i]=0;
        wygrana[i]=false;
        cordy_c4[i]=false;
    }

}




void SaperFrame::od_nowa()
{

    for(int i=0; i<100; i++)
    {
        liczba_bomb_obok[i]=0;
        cordy_c4[i]=false;

    }
    liczba_pozostalych_bomb=10;
    koniec=true;
    pthread_join(watek,NULL);
    start=0;
    stop=0;
    koniec=false;
    liczba_ruchow=0;
    aktualny_czas=0;
    stworz_menu();
    Refresh();
    Update();

}







void SaperFrame::zwroc_wspolrzedne(int x,int y)
{

    for(int i=0; i<100; i++)
    {

        if(x>=cordy_mapy_x[i] && x<=cordy_mapy_x[i]+43 && y>=cordy_mapy_y[i] && y<=cordy_mapy_y[i]+41 )
        {
            cordy[0]=cordy_mapy_x[i];
            cordy[1]=cordy_mapy_y[i];

        }

    }

}

int SaperFrame::znajdz_pole(int x,int y)
{

    for(int i=0; i<100; i++)
    {
        if(cordy_mapy_x[i]==x && cordy_mapy_y[i]==y)return i;

    }


    return -1;
}

int SaperFrame::sprawdzanie_wygranej()
{


    for(int i=0; i<100; i++)
    {
        if(wygrana[i]==true)liczba_pozostalych_pol+=1;
    }


    return liczba_pozostalych_pol;
}



void SaperFrame::zliczanie_bomb()
{
    for(int i=0; i<100; i++)
    {
        for(int j=0; j<11; j++)
        {
            if((cordy_mapy_x[i]-43 ==cord_bomby_x[j] ) &&(cordy_mapy_y[i] == cord_bomby_y[j]))liczba_bomb_obok[i]++;//warunek na sprawdzanie pola na lewo
            if((cordy_mapy_x[i]+43 ==cord_bomby_x[j] ) &&(cordy_mapy_y[i] == cord_bomby_y[j]))liczba_bomb_obok[i]++;//warunek na sprawdzanie pola na prawo

            if((cordy_mapy_x[i] ==cord_bomby_x[j] ) &&(cordy_mapy_y[i]+41 == cord_bomby_y[j]))liczba_bomb_obok[i]++;//warunek na sprawdzanie pola w dol
            if((cordy_mapy_x[i] ==cord_bomby_x[j] ) &&(cordy_mapy_y[i]-41 == cord_bomby_y[j]))liczba_bomb_obok[i]++;//warunek na sprawdzanie pola w gore

            if((cordy_mapy_x[i]-43 ==cord_bomby_x[j] ) &&(cordy_mapy_y[i]-41 == cord_bomby_y[j]))liczba_bomb_obok[i]++;//warunek na sprawdzanie pola na lewy gorny skos
            if((cordy_mapy_x[i]-43 ==cord_bomby_x[j] ) &&(cordy_mapy_y[i]+41 == cord_bomby_y[j]))liczba_bomb_obok[i]++;//warunek na sprawdzanie pola na lewy dolny skos

            if((cordy_mapy_x[i]+43 ==cord_bomby_x[j] ) &&(cordy_mapy_y[i]-41 == cord_bomby_y[j]))liczba_bomb_obok[i]++;//warunek na sprawdzanie pola na prawy gorny skos
            if((cordy_mapy_x[i]+43 ==cord_bomby_x[j] ) &&(cordy_mapy_y[i]+41 == cord_bomby_y[j]))liczba_bomb_obok[i]++;//warunek na sprawdzanie pola na prawy dolny skos
        }
    }
}

void SaperFrame::odkrywanie_pustych(int x,int y)
{
    wxClientDC dc(this);
    wxFont f(31, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD,false, "Courier");
    dc.SetFont(f);
    wxImage img;
    img.LoadFile("puste_pole.png",wxBITMAP_TYPE_PNG);
    wxBitmap bm(img);


    wxBrush brush(bm);


    dc.SetBrush(brush);


    int aktualny=znajdz_pole(x,y);



    if(   sprawdz(x,y)==true && wygrana[aktualny]==true)
    {

        dc.DrawRectangle(x,y,43,41);
        wygrana[aktualny]=false;
        if(liczba_bomb_obok[aktualny]!=0)
        {
            if (liczba_bomb_obok[aktualny]==1) dc.SetTextForeground(RGB(111,156,235));
            if (liczba_bomb_obok[aktualny]==2) dc.SetTextForeground("green");
            if (liczba_bomb_obok[aktualny]==3) dc.SetTextForeground(RGB(183,28,28));
            if (liczba_bomb_obok[aktualny]==4) dc.SetTextForeground("black");
            std::ostringstream ss;
            ss << liczba_bomb_obok[aktualny];
            std::string str = ss.str();
            dc.DrawText(str,wxPoint(x+13,y+8));
        }

        if(x>=0 && x<=430 && y>=0 && y<=410 && liczba_bomb_obok[aktualny]==0)
        {
            odkrywanie_pustych(x+43,y);
            odkrywanie_pustych(x-43,y);

            odkrywanie_pustych(x,y+41);
            odkrywanie_pustych(x,y-41);

            odkrywanie_pustych(x-43,y-41);
            odkrywanie_pustych(x-43,y+41);

            odkrywanie_pustych(x+43,y-41);
            odkrywanie_pustych(x+43,y+41);
        }
    }

    dc.SetBrush(wxNullBrush);
}



