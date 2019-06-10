#include <iostream>
#include "Plansza.h"
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

int main()
{
    int tempi=-1,tempj=-1, tempi2=-1,tempj2=-1; /// ZMIENNE POMOCNICZE /// DO POPRAWY
    int i,j;

    int rozmiar_planszy;
    cout << "Podaj rozmiar planszy: ";
    cin >> rozmiar_planszy;
    int zawartosc = 0;

    /// POMOCNICZA TABLICA
    int tab_zaw[rozmiar_planszy][rozmiar_planszy];
    for(int i = 0; i < rozmiar_planszy; i++)
    {
        for (int j = 0; j < rozmiar_planszy; j++)
        {
            tab_zaw[i][j] = zawartosc;
            zawartosc++;
        }
    }

    /// ROZMIARY OKNA SPRITE'OW I EKRANOW Z WYNIKAMI
    static constexpr int window_size = 720;
    int rozmiar_tekstur = 12;
    int rozmiar_tekstur_wynik = 72;
    /// TABLICE PRZECHOWUJACE TEXTURY I SPRITE'Y
    sf::Texture textures[6];
    sf::Sprite sprites[6];

    /// DOBIERANIE SKALI DO ROZMIARU PLANSZY
    int rozmiar_komorki = window_size/rozmiar_planszy;
    int scale = rozmiar_komorki/rozmiar_tekstur;
    int scale2 =(rozmiar_komorki/rozmiar_tekstur_wynik);

    /// TWORZENIE OKNA
    sf::RenderWindow window (sf::VideoMode(window_size, window_size), "Kó³ko i krzy¿yk - MB");

    /// SPRITE'Y KOLKO KRZYZYK I PUSTA KOMORKA
    textures[0].loadFromFile("assets/light.png");
    textures[2].loadFromFile("assets/cross.png");
    textures[3].loadFromFile("assets/circle.png");
    sprites[0].setTexture(textures[0]);
    sprites[2].setTexture(textures[2]);
    sprites[3].setTexture(textures[3]);
    sprites[0].setScale(scale, scale);
    sprites[2].setScale(scale, scale);
    sprites[3].setScale(scale, scale);
    /// EKRANY Z WYNIKAMI
    textures[1].loadFromFile("assets/circlewon.png");
    textures[4].loadFromFile("assets/crosswon.png");
    textures[5].loadFromFile("assets/remis.png");
    sprites[1].setTexture(textures[1]);
    sprites[4].setTexture(textures[4]);
    sprites[5].setTexture(textures[5]);
    sprites[1].setScale(scale2, scale2);
    sprites[4].setScale(scale2, scale2);
    sprites[5].setScale(scale2, scale2);

    /// WYPELNNIANIE EKRANU PUSTYMI KOMORKAMI
    for( i = 0; i < rozmiar_planszy; i++) {
        for ( j = 0; j < rozmiar_planszy; j++) {
                sprites[0].setPosition(j * rozmiar_komorki, i * rozmiar_komorki);
                window.draw(sprites[0]);}
                }
    Plansza* Kolko_i_krzyzyk = new Plansza(rozmiar_planszy);
    /// GRACZ RUSZA PIERWSZY
    int Player = 1;
    Wartosc pionek = X;
    int ruch = 0;

    /// GLOWNA PETLA Z GRA
    while(Kolko_i_krzyzyk->Kto_wygral()==0)
        {

        system("cls");
                /// RYSOWANIE WYKONANYCH ROCHOW I WYSWIETLANIE NOWEJ KLATKI
                sprites[2].setPosition(tempj * rozmiar_komorki, tempi * rozmiar_komorki);
                window.draw(sprites[2]);
                sprites[3].setPosition(tempj2 * rozmiar_komorki, tempi2 * rozmiar_komorki);
                window.draw(sprites[3]);
                window.display();

        if(Player == 1) ///RUCH GRACZA
            {
            pionek = X;
            cout << "Twoj ruch: ";
            cin >> ruch;
            Player--;
            for( i = 0; i < rozmiar_planszy; i++)
                {
                for ( j = 0; j < rozmiar_planszy; j++) /// PRZEKLADANIE TABLICY JEDNOWYMIAROWEJ NA DWUWYMIAROWA
                    {
                    if(tab_zaw[i][j] == ruch){tempi = i; tempj=j;}
                    }
                }
            }else if(Player == 0) /// RUCH KOMPUTERA
            {

            pionek = O;
            ruch = Kolko_i_krzyzyk->Najlepszy_Ruch();
            Player++;

                for( i = 0; i < rozmiar_planszy; i++)
                    {
                    for ( j = 0; j < rozmiar_planszy; j++) /// PRZEKLADANIE TABLICY JEDNOWYMIAROWEJ NA DWUWYMIAROWA
                        {
                        if(tab_zaw[i][j] == ruch){tempi2=i;tempj2=j;}
                        }
                    }
            }
            Kolko_i_krzyzyk->Wykonaj_ruch(ruch,pionek); ///WYKONANIE RUCHU GRACZA LUB KOMPUTERA
        }

    system("cls");
    switch(Kolko_i_krzyzyk->Kto_wygral()){
    case -10: /// WARUNEK WYGRANEJ GRACZA

        sprites[4].setPosition(240, 240);
        window.clear();
        window.draw(sprites[4]);
        window.display();
        while(1){}
    case 10: /// WARUNEK WYGRANEJ KOMPUTERA

        sprites[1].setPosition(240, 240);
        window.clear();
        window.draw(sprites[1]);
        window.display();
        while(1){}
    case -1: /// WARUNEK REMISU

        sprites[5].setPosition(240, 240);
        window.clear();
        window.draw(sprites[5]);
        window.display();
        while(1){}
    }
}


