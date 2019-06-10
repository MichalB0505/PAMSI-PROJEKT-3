#ifndef PLANSZA_H
#define PLANSZA_H
#include <iostream>
#include <algorithm>
#include <vector>
#include<map>
using namespace std;

///WARTOSCI KTORE MOZE MIEC DANA KOMORKA/POLE
enum Wartosc {O, X, puste};

struct Pole
{
    Wartosc Wartosc_pola = puste; /// STRUKTURA REPREZENTUJACA GRACZA/KOMPUTER/PUSTE POLE
};

class Plansza
{
public:
    /// KONSTRUKTOR INICJALIZUJACY PLANSZE
    Plansza(const int roz_pl): rozmiar_planszy(roz_pl) {Tab = new Pole[rozmiar_planszy*rozmiar_planszy];}
    ~Plansza();
    /// TABLICA PRZECHOWUJACA AKTUALNY RUCH
    Pole *Tab;
    /// METODA SPRAWDZA CZY WYGRA£ GRACZ CZY KOMPUTER
    bool Szukanie_Wygranej(Wartosc wartosc_pola) const;
    /// METODA ZWRACA ODPOWIEDNIA WARTOS W ZALEZNOSCI OD WYNIKU
    int Kto_wygral() const;
    /// METODA SPRAWDZA CZY TABLICA JEST PELNA - WARUNEK REMISU
    bool Czy_pelna() const;
    /// METODA WYKONUJE RUCH
    void Wykonaj_ruch(int x, Wartosc pionek) {Tab[x].Wartosc_pola = pionek;}
    /// METODA REPREZENTUJACA SZTUCZNA INTELIGENCJE
    int Alfa_Beta(Pole *Tab, int Depth, int Alfa, int Beta, bool max) ;
    /// METODA INICJALIZUJE ALGORYTM ALFA-BETA ZWRACA RUCH, KTORY POWINNO WYKONAC SI
    int Najlepszy_Ruch();


private:
    /// ROZMIAR TABLICY
    const int rozmiar_planszy;
};

#endif
