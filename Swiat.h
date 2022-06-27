#pragma once

#define ANTYLOPA 'A'
#define A_SILA 4
#define A_INICJATYWA 4

#define CZLOWIEK 'C'
#define CZLOWIEK_S 'S'
#define C_SILA 5
#define C_INICJATYWA 4
#define UMIEJETNOSC_COOLDOWN 10

#define LIS 'L'
#define L_SILA 3
#define L_INICJATYWA 7

#define OWCA 'O'
#define O_SILA 4
#define O_INICJATYWA 4

#define WILK 'W'
#define W_SILA 9
#define W_INICJATYWA 5

#define ZOLW 'Z'
#define Z_SILA 2
#define Z_INICJATYWA 1

#define ROSLINA_INICJATYWA 0

#define BARSZCZ 'B'
#define B_SILA 10

#define GUARANA 'G'
#define G_SILA 0
#define MOC_GUARANY 3

#define MLECZ 'M'
#define M_SILA 0

#define TRAWA 'T'
#define T_SILA 0

#define WILCZEJAGODY 'X'
#define X_SILA 99

#define TAB 9
#define ESC 27
#define ARROW 224
#define S_KEY 115
#define W_KEY 119
#define M_KEY 109
#define N_KEY 110

#define COOLDOWN_NA_RODZENIE 10

#include "Organizm.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <conio.h>
#include <Windows.h>

using namespace std;

class Organizm;

class Swiat {
private:
	vector<Organizm*> organizmy;
	vector<string> dziennik;
	bool pokazujDziennik;
	Organizm*** plansza;
	int rozmiarX;
	int rozmiarY;
	int numerTury;
	void drukujOrganizmy();
	void zwolnijPamiec();
	void sortujOrganizmy();
	void usunMartwe();
public:
	Swiat();
	Swiat(int rozmiarX, int rozmiarY);
	void wykonajTure();
	void rysujSwiat();
	vector<Organizm*> getOrganizmy() const;
	void dodajWpis(string wiad);
	void dodajWpis(Organizm* o, int x1, int y1, int x2, int y2);
	void setOrganizmy(vector<Organizm*> v);
	int getRozmiarX() const;
	int getRozmiarY() const;
	void setPokazujDziennik(bool d);
	bool getPokazujDziennik() const;
	void setPlansza(int _x, int _y);
	Organizm*** getPlansza() const;
	void dodajOrganizm(Organizm* nowyOrganizm);
	void dodajOrganizm(char znak, int polozenieX, int polozenieY, int sila, int inicjatywa, int wiek);
	void generujSave();
	void wczytajSave();
	void generujGre();
	int menu();

	~Swiat();
};