#include "Plansza.h"
using namespace std;
Plansza::~Plansza(){}
bool Plansza::Szukanie_Wygranej(Wartosc wartosc_pola) const {


    for(int i=0; i<rozmiar_planszy; i++){
        int k = rozmiar_planszy - i;

        while(i < rozmiar_planszy*rozmiar_planszy-1) {
            if(Tab[i].Wartosc_pola == wartosc_pola){ ///SPRAWDZANIE KOLUMN
                i += rozmiar_planszy;
            }
            if(Tab[i].Wartosc_pola != wartosc_pola) { /// PRZERWANIE PO NATRAFIENIU NA ZNAK INNY NIZ SPRAWDZANY
                break;
            }
            if((i==((rozmiar_planszy*rozmiar_planszy)-k)) && (Tab[i].Wartosc_pola==wartosc_pola)) { ///ZNALEZIONO WYGRANA
                return true;
            }
        }
    }


    for(int i=0; i<(rozmiar_planszy*rozmiar_planszy); i+=rozmiar_planszy){ /// SPRAWDZANIE WIERSZY
        int k=i-1;

        if(Tab[i].Wartosc_pola == wartosc_pola){
            while(i <= rozmiar_planszy*rozmiar_planszy){
                if(Tab[i].Wartosc_pola == wartosc_pola) {
                    i++;
                }
                if(Tab[i].Wartosc_pola != wartosc_pola) { ///PRZERWANIE PO NATRAFIENIU NA ZNAK INNY NIZ SZUKANY
                    break;
                }
                if((i == k+rozmiar_planszy) && (Tab[i].Wartosc_pola == wartosc_pola)) { ///ZNALEZIONO WYGRANA
                    return true;
                }
            }
        }
    }


    int j=0;

    while(j <= rozmiar_planszy*rozmiar_planszy){ /// SPRAWDZANIE PRZEKATNEJ OD LEWEJ DO PRAWEJ
        if(Tab[j].Wartosc_pola == wartosc_pola) {
            j += rozmiar_planszy+1;
        }
        if(Tab[j].Wartosc_pola!=wartosc_pola) { ///PRZERWANIE PO NATRAFIENIU NA ZNAK INNY NIZ SZUKANY
            break;
        }
        if((j == rozmiar_planszy*rozmiar_planszy-1) && (Tab[j].Wartosc_pola == wartosc_pola)) { ///ZNALEZIONO WYGRANA
            return true;
        }
    }

    j = rozmiar_planszy-1;

    while(j <= (rozmiar_planszy*rozmiar_planszy)-rozmiar_planszy){ /// SPRAWDZANIE PRZEKATNEJ OD PRAWEJ DO LEWEJ
        if(Tab[j].Wartosc_pola == wartosc_pola) {
            j += rozmiar_planszy-1;
        }
        if(Tab[j].Wartosc_pola != wartosc_pola) { ///PRZERWANIE PO NATRAFIENIU NA ZNAK INNY NIZ SZUKANY
            break;
        }
        if( (j==(rozmiar_planszy*rozmiar_planszy)-rozmiar_planszy) && (Tab[j].Wartosc_pola == wartosc_pola)) { ///ZNALEZIONO WYGRANA
            return true;
        }
    }

    return false;
}

int Plansza::Kto_wygral() const {
    bool Win_X = Szukanie_Wygranej(X); /// WYGRAL KRZYZYK
    bool Win_O = Szukanie_Wygranej(O); /// WYGRALO KOLKO

    if(Win_X == true){
        return -10;
    }
    if(Win_O == true) {
        return 10;
    }
    if((Win_X == false) && (Win_O == false) && (Czy_pelna() == true)){ /// TABLICA PELNA I NIKT NIE WYGRAL = REMIS
        return -1;
    }

    return 0;
}

bool Plansza::Czy_pelna() const {
    for(int l=0; l<(rozmiar_planszy*rozmiar_planszy); l++){
        if(Tab[l].Wartosc_pola == puste){ ///KOMORKA NIE JEST PUSTA = PELNA
            return false;
        }
    }
    return true;
}

int Plansza::Najlepszy_Ruch() {
    int zm_pomocnicza = -1000000;
    int numer_komorki = 0;
    int wartosc_ruchu = 0;

    for(int i=0; i<rozmiar_planszy*rozmiar_planszy; i++){
        if(Tab[i].Wartosc_pola == puste){
            Tab[i].Wartosc_pola = O;

            wartosc_ruchu = Alfa_Beta(Tab, 0, -1000000, 1000000, 0); ///poczatkowe wywolanie algorytmu

            Tab[i].Wartosc_pola = puste;

            if(wartosc_ruchu>zm_pomocnicza) {
                zm_pomocnicza = wartosc_ruchu;
                numer_komorki = i;
            }
        }
    }
    return numer_komorki;
}

int Plansza::Alfa_Beta(Pole *Tab, int Depth, int Alfa, int Beta, bool isMax)
{

    int SCORE;
    int AB_OutcomeMax;
    int AB_OutcomeMin;
    /// STANY KOÑCOWE
    int TerminalState = Kto_wygral();
    if(TerminalState == 10) {
         return (10000);
    }
    if(TerminalState == -10) {
        return (-10000);
    }
    if(TerminalState == -1) {
        return 0;
    }

/// GLEBOKOSC PRZESZUKIWANIA
if (Depth < 10){
/// ALGORYTM MINIMAX Z CIECIAMI ALFA BETA
    if(isMax == true) {
        SCORE = -1000000;

        for(int i=0; i<rozmiar_planszy*rozmiar_planszy; i++) {
            if(Tab[i].Wartosc_pola==puste) {
                Tab[i].Wartosc_pola = O; /// HIPOTETYCZNY RUCH KOMPUTERA

                AB_OutcomeMax = Alfa_Beta(Tab, Depth+1, Alfa, Beta, 0);

                SCORE = max(SCORE, AB_OutcomeMax );
                Alfa = max(SCORE, Alfa);
                Tab[i].Wartosc_pola = puste; ///ZWOLNIENIE POLA

                if(Alfa>=Beta){ /// ODCIECIE
                    break;
                }
            }
        }
    }
    else
    {
        SCORE = 1000000;

        for(int i=0; i<rozmiar_planszy*rozmiar_planszy; i++) {
            if(Tab[i].Wartosc_pola == puste){
                Tab[i].Wartosc_pola = X;

                AB_OutcomeMin = Alfa_Beta(Tab, Depth+1, Alfa, Beta, 1);

                SCORE = min(SCORE, AB_OutcomeMin);
                Beta = min(SCORE, Beta);
                Tab[i].Wartosc_pola = puste;

                if(Alfa>=Beta){ /// ODCIECIE

                   break;
                }
            }
        }
    }}
return SCORE;

   }



