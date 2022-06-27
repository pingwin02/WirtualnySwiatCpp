#pragma once

#include <iostream>
#include <fstream>
#include "Swiat.h"

using namespace std;

class Swiat;

class Organizm {
private:
	int sila = 0;
	int inicjatywa = 0;
	int polozenieX = 0;
	int polozenieY = 0;
	string nazwa = "Organizm";
	char znak = '?';
	bool zyje = 1;
	int narodzony = 0;
	int wiek = 0;
protected:
	Swiat* swiat;
	friend std::ostream& operator<<(std::ostream& ostr, Organizm* o);
	virtual void rozmnoz() = 0;
	virtual void atakowanie(Organizm& atakowany);
	virtual bool czyOdbilAtak(Organizm& atakujacy);
	virtual bool czyUniknalAtak(Organizm& atakujacy);
	virtual bool czyZjadlSpecjalna(Organizm& jedzacy);
public:
	virtual void akcja() = 0;
	virtual void kolizja(int x, int y);
	virtual char rysowanie() const;
	virtual void setZnak(char znak);
	virtual void setNazwa(string nazwa);
	virtual string getNazwa() const;
	virtual string generujKomende();
	virtual void setX(int x);
	virtual void setY(int y);
	virtual int getX() const;
	virtual int getY() const;
	virtual int getSila() const;
	virtual void setSila(int sila);
	virtual void setNarodzony(int narodzony);
	virtual int getNarodzony() const;
	virtual void setInicjatywa(int inicjatywa);
	virtual int getInicjatywa() const;
	virtual bool getZyje() const;
	virtual void setZyje(bool zyje);
	virtual int getWiek() const;
	virtual void setWiek(int wiek);
	virtual bool SprawdzLokacje(int x, int y) const;
	struct MiejsceUrodzenia {
		int x = -1;
		int y = -1;
	};
	MiejsceUrodzenia SprawdzMiejsce() const;
};