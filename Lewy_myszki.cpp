

//(*InternalHeaders(SaperFrame)

#include "SaperMain.h"


//*)
void SaperFrame::OnLeftDown(wxMouseEvent& event)
{
    stworz_menu();

    if(liczba_ruchow==0)
    {

        pthread_create(&watek,NULL,licz_czas,NULL);

        start=clock();
    }
    liczba_ruchow++;
    int win=0;
    wxPoint size = event.GetPosition();
    zwroc_wspolrzedne(size.x,size.y);
    wxClientDC  dc(this);
    wxImage img;
    img.LoadFile("puste_pole.png",wxBITMAP_TYPE_PNG);

    wxBitmap bm(img);

    wxBrush brush(bm);

    dc.SetBrush(brush);

    int aktualne_pole=znajdz_pole(cordy[0],cordy[1]);

    if((sprawdz(cordy[0],cordy[1]))!=true && cordy_c4[aktualne_pole]!=true  )
    {
        img.LoadFile("bomba_szara_43.png",wxBITMAP_TYPE_PNG);
        wxBitmap bomby(img);
        wxBrush brush(bomby);
        dc.SetBrush(brush);
        for(int i=0; i<10; i++)
        {

            Beep(100,50);
            dc.DrawRectangle(cord_bomby_x[i],cord_bomby_y[i],43,41);
        }
        wxString msg="\nTrafiles na bombe!\nKoniec gry!!!\n";


        stop = clock();
        czas = (double)(stop-start) / CLOCKS_PER_SEC;

        std::stringstream czasy;

        czasy<<czas;

        std::string czas_string=czasy.str();
        std::string calosc="";
        std::string czasowe="\nTwoj dokladny czas to : " + czas_string+" sec.\n";

        if ( wxMessageBox(czasowe+msg+"\n\n\nChcesz zagrac jeszcze raz?\n\n","Nowa gra?",wxICON_QUESTION | wxYES_NO) != wxYES ) Close();
        od_nowa();

    }
    else if((czy_jest_bomba(cordy[0],cordy[1])==false && cordy_c4[aktualne_pole]!=true) || (cordy[0]==0 && cordy[1]==0))
    {
        odkrywanie_pustych(cordy[0],cordy[1]);

    }
    liczba_pozostalych_pol=0;
    win=0;
    win=sprawdzanie_wygranej();

    if(win==10)
    {
        img.LoadFile("flaga_43_A.png",wxBITMAP_TYPE_PNG);
        wxBitmap flagi(img);
        wxBrush brush(flagi);
        dc.SetBrush(brush);
        for(int i=0; i<10; i++)
        {
            dc.DrawRectangle(cord_bomby_x[i],cord_bomby_y[i],43,41);
        }

        stop = clock();
        czas = (double)(stop-start) / CLOCKS_PER_SEC;


        std::stringstream ruchy,czasy;
        ruchy<<liczba_ruchow;
        czasy<<czas;
        std::string liczba=ruchy.str();
        std::string czas_string=czasy.str();
        std::string pobicie_rekordu="";

        std::ifstream plik("rekord.txt");

        double rekord=0;


        plik>>rekord;
        plik.close();

        std::ofstream plik1("rekord.txt");
        if(rekord!=0)//sprawdzamy czy w pliku cos jest
        {

            if(czas<rekord)//jest tak to sprawdzamy czy pobilismy rekord
            {

                plik1<<czas_string;//zapisujemy nowy rekord
                pobicie_rekordu="\nUdalo Ci sie pobic dotychczasowy rekord!\nTwoj wynik zostanie zapisany!\n";

            }
            else plik1<<rekord;//zapisujemy stary rekord
        }
        else if(rekord==0)//plik jest pusty, zapisujemy w nim wynik
        {
            plik1<<czas_string<<std::endl;

        }
        plik1.close();

        std:: string wiadomosc="\nBrawo! Wygrales w " + liczba;
        std::string calosc="";
        std::string czasowe=" ruchach!\nTwoj dokladny czas to :" + czas_string+" sec"+pobicie_rekordu;


        calosc=wiadomosc+czasowe;

        if ( wxMessageBox(calosc+"\n\n\nChcesz zagrac jeszcze raz?\n","Nowa gra?",wxICON_QUESTION | wxYES_NO) != wxYES ) Close();

        od_nowa();

    }
    dc.SetBrush(wxNullBrush);
}
