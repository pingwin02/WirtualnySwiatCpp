#include "Antylopa.h"

Antylopa::Antylopa(Swiat* swiat, int polozenieX, int polozenieY) {
	this->swiat = swiat;
	setX(polozenieX);
	setY(polozenieY);
	setSila(A_SILA);
	setInicjatywa(A_INICJATYWA);
	setZnak(ANTYLOPA);
	setNazwa("Antylopa");
}

void Antylopa::rozmnoz() {
	MiejsceUrodzenia wynik = SprawdzMiejsce();
	if (wynik.x != -1 && wynik.y != -1) {
		Organizm* dziecko = new Antylopa(swiat, wynik.x, wynik.y);
		dziecko->setNarodzony(COOLDOWN_NA_RODZENIE);
		swiat->dodajOrganizm(dziecko);
		swiat->dodajWpis(getNazwa() + "(" + to_string(getX()) + "," + to_string(getY()) + ") rozmnozyl sie! ");
	}
}

void Antylopa::akcja() {

	int randomX = 0, randomY = 0;
	random_device device;
	mt19937 gen(device());

	while (!(randomX || randomY)) {
		do {
			randomX = gen() % 5 - 2;
			randomY = gen() % 5 - 2;
		} while (SprawdzLokacje(getX() + randomX, getY() + randomY));
	}

	swiat->dodajWpis(this, getX(), getY(), getX() + randomX, getY() + randomY);

	kolizja(getX() + randomX, getY() + randomY);
}

void Antylopa::atakowanie(Organizm& atakowany) {
	random_device device;
	mt19937 gen(device());

	int szansa = gen() % 2;

	if (!szansa) {
		MiejsceUrodzenia wynik = atakowany.SprawdzMiejsce();
		if (wynik.x != -1 && wynik.y != -1) {
			swiat->dodajWpis(getNazwa() + "(" + to_string(getX()) + "," + to_string(getY()) + ") chce uciec przed zaatakowaniem " + atakowany.getNazwa() + " do ("
				+ to_string(wynik.x) + "," + to_string(wynik.y) + ")");
			kolizja(wynik.x, wynik.y);//przesuniecie
		}
		else {
			swiat->dodajWpis(getNazwa() + "(" + to_string(getX()) + "," + to_string(getY()) + ") nie udalo sie uciec przed zaatakowaniem " + atakowany.getNazwa());
			Organizm::atakowanie(atakowany);
		}
	}
	else {
		swiat->dodajWpis(getNazwa() + "(" + to_string(getX()) + "," + to_string(getY()) + ") nie udalo sie uciec przed zaatakowaniem " + atakowany.getNazwa());
		Organizm::atakowanie(atakowany);
	}

}

bool Antylopa::czyUniknalAtak(Organizm& atakujacy) {

	random_device device;
	mt19937 gen(device());

	int szansa = gen() % 2;

	int x = getX();
	int y = getY();

	if (!szansa) {
		MiejsceUrodzenia wynik = SprawdzMiejsce();
		if (wynik.x != -1 && wynik.y != -1) {
			swiat->dodajWpis(getNazwa() + "(" + to_string(getX()) + "," + to_string(getY()) + ") chce uciec przed atakujacym " + atakujacy.getNazwa() + " do ("
				+ to_string(wynik.x) + "," + to_string(wynik.y) + ")");
			kolizja(wynik.x, wynik.y);//przesuniecie
			atakujacy.kolizja(x, y);//przesuniecie
			return true;
		}
		else {
			swiat->dodajWpis(getNazwa() + "(" + to_string(getX()) + "," + to_string(getY()) + ") nie udalo sie uciec przed atakujacym " + atakujacy.getNazwa());
			return false;
		}
	}
	else {
		swiat->dodajWpis(getNazwa() + "(" + to_string(getX()) + "," + to_string(getY()) + ") nie udalo sie uciec przed atakujacym " + atakujacy.getNazwa());
		return false;
	}
}
