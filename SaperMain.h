/***************************************************************
 * Name:      SaperMain.h
 * Purpose:   Defines Application Frame
 * Author:    Arkadiusz Gajda,Daniel Jedrzejczyk ()
 * Created:   2017-12-29
 * Copyright: Arkadiusz Gajda,Daniel Jedrzejczyk ()
 * License:
 **************************************************************/

#ifndef SAPERMAIN_H
#define SAPERMAIN_H

//(*Headers(SaperFrame)
#include <wx/menu.h>
#include <wx/frame.h>
#include <wx/dcclient.h>
#include <wx/wx.h>
#include <string>
#include<sstream>
#include<fstream>
#include <time.h>
#include <windows.h>
#include <iostream>
#include<wx/event.h>
#include <wx/string.h>

//*)

class SaperFrame: public wxFrame
{

public:
    SaperFrame(wxWindow* parent,wxWindowID id = -1);

private:
    bool czy_jest_bomba(int,int);


    static bool koniec ;//sluży do konczenia pracy wątku
    int cord_bomby_x[10]; //kordy x bomb
    int cord_bomby_y[10]; //kordy y bomb
    clock_t start,stop;//poczatek i koniec pomiaru czasu
    double czas;//zlicza dokładny czas
    int cordy_mapy_x[100]; //kordy wszystkich pól na mapie
    int cordy_mapy_y[100]; //kordy wszystkich pól na mapie
    static double aktualny_czas;
    bool cordy_c4[100];//sprawdza czy na danym polu jest c4 , true czyli jest
    int index;
    int liczba_pozostalych_bomb;

    void odkrywanie_pustych(int,int);

    bool sprawdz(int,int);
    int znajdz_pole(int,int);//zwraca index aktualnie kliknietego pola
    int cordy[2];//tablica ktora przechowuje wciśnięte przez użytkownika pole(jego x,y)
    int liczba_ruchow=0;
    bool wygrana[100];//oznacza wszystkie pola jako true a w momencie klikniecia w nie jako false, przez co na pozycji "true" zostaja tylko pola z bombami
    int liczba_pozostalych_pol;
    int liczba_bomb_obok[100];//tablica przechowujaca informacje o kazdym polu - ile jest wokol niego bomb
    void zwroc_wspolrzedne(int,int);// metoda "dopasowuje" kordy wcisniete przez uzytkownika do odpowiedniego pola z tablicy cordy_mapy_x,y
    int sprawdzanie_wygranej();// sprawdza czy na pozycji true zostalo tylko tyle pol ile jest min, przez co wiadomo kiedy gracz wygral gre
    bool bomby_na_tej_samej_pozycji(int,int);//zabezpieczenie przez wylosowaniem bomby na tym samym polu
    void zliczanie_bomb();////warunek sprwadzający ilosc bomb w kratkach obok kazdego pola - sprawdza 8 pol
    void stworz_menu();//tworzy menu sluzy do "odswiezania czasu"

    static  void *licz_czas(void*);//funkcja ktora w ramach wątku liczy czas na bieżąco i pokazuje go użytkwonikowi
    virtual ~SaperFrame();
    void od_nowa();//zeruje wszystkie ustawienia,wygenerowane bomby itp

    pthread_t watek;//tworzy wątek służacy do pomiaru czasu


    //(*Handlers(SaperFrame)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void Rules(wxCommandEvent& event);
    void New_game(wxCommandEvent& event);
    void Pokaz_rekord(wxCommandEvent& event);

    void OnPaint(wxPaintEvent& event);
    void Najechanie  (wxMouseEvent& event);
    void OnLeftDown  (wxMouseEvent& event);
    void OnRightDown (wxMouseEvent& event);
    //*)

    //(*Identifiers(SaperFrame)
    static const long idMenuQuit;
    static const long idRekord;
    static const long idMenuRules;
    static const long idBomby;
    static const long idNewGame;
    static const long idMenuAbout;
    static const long idOnPaint;
    static const long idOnLeftDown;
    static const long idOnRightDown;
    static const long ID_STATUSBAR1;
    //*)

    //(*Declarations(SaperFrame)
    wxStatusBar* StatusBar1;
    //*)

    DECLARE_EVENT_TABLE()

};




#endif // CUSTOMMAIN_H
