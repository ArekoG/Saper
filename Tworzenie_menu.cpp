
//(*InternalHeaders(SaperFrame)

#include "SaperMain.h"


//*)

void SaperFrame::stworz_menu()
{
    Sleep(40);
    std::stringstream czas,bomby;

    czas<<aktualny_czas;
    bomby<<liczba_pozostalych_bomb;
    std::string liczba=czas.str();
    std::string liczba_bomb=bomby.str();

    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem3;
    wxMenuItem* MenuItem4;
    wxMenuItem* MenuItem5;

    wxMenuBar* MenuBar;
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenu* Menu3;
    wxMenu* Menu4;
    wxMenu* Menu5;


    MenuBar = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Wyjdz\tAlt-F4"), _("Wyjdz z gry"), wxITEM_NORMAL);
    MenuItem3 = new wxMenuItem(Menu1, idNewGame, _("Nowa gra"), _("Nowa gra"), wxITEM_NORMAL);
    Menu1->Append(MenuItem3);
    Menu1->Append(MenuItem1);
    MenuBar->Append(Menu1, _("&Gra"));



    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("Zasady gry\tF1"), _("Zasady gry w sapera"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);

    MenuItem4 = new wxMenuItem(Menu2, idMenuRules, _("O projekcie\tF2"), _("Pokaz informacje o aplikacji"), wxITEM_NORMAL);
    Menu2->Append(MenuItem4);
    MenuBar->Append(Menu2, _("&Pomoc"));



    Menu5 = new wxMenu();
    MenuItem5 = new wxMenuItem(Menu5, idRekord, _("Rekordzista sapera\tF3"), _("Pokaz rekordowy czas przejscia"), wxITEM_NORMAL);
    Menu5->Append(MenuItem5);
    MenuBar->Append(Menu5, ("Rekord"));


    Menu3 = new wxMenu();

    MenuBar->Append(Menu3, ("Twoj czas to: "+liczba+" sec"));
    liczba="";

    Menu4 = new wxMenu();

    MenuBar->Append(Menu4, ("Liczba pozostalych bomb: "+liczba_bomb));



    SetMenuBar(MenuBar);


}
//metody związane z menu

void SaperFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}
void SaperFrame::Pokaz_rekord(wxCommandEvent& event)
{

    std::ifstream plik("rekord.txt");

    double rekord=0;


    plik>>rekord;
    plik.close();

    std::stringstream str;
    str << std::fixed << rekord;

    std::string tekst = str.str();
    wxMessageBox("Najlepszy czas to "+tekst+"sec", _("Rekord"));


}

void SaperFrame::New_game(wxCommandEvent& event)
{

    od_nowa();
}

void SaperFrame::OnAbout(wxCommandEvent& event)
{



    wxString msg = ("Nasz saper oferuje pole do gry w rozmiarze 10x10\nNa planszy zostaje rozlosowanych losowo 10 bomb\n\nProjekt wykonali:\nArkadiusz Gajda\nDaniel Jedrzejczyk");
    wxMessageBox(msg, _("O projekcie"));

}


void SaperFrame::Rules(wxCommandEvent& event)
{


    wxString msg = ("Zasady gry:\nZasady gry Saper sa proste:\nOdkrycie miny konczy gre. \nOdkrycie pustego pola oznacza kontynuowanie rozgrywki. \nOdkrycie liczby informuje, ile min ukryto wsrod osmiu sasiadujacych z nia pol - na tej podstawie trzeba wydedukowac, ktore pola dookola mozna bezpiecznie kliknac.");
    wxMessageBox(msg, _("Zasady gry..."));

}

void SaperFrame::Najechanie(wxMouseEvent& event)
{


    stworz_menu();

}
