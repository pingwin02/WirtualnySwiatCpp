#include "Zolw.h"

Zolw::Zolw(Swiat* swiat, int polozenieX, int polozenieY) {
	this->swiat = swiat;
	setX(polozenieX);
	setY(polozenieY);
	setSila(Z_SILA);
	setInicjatywa(Z_INICJATYWA);
	setZnak('Z');
	setNazwa("Zolw");
}

void Zolw::rozmnoz() {
	MiejsceUrodzenia wynik = SprawdzMiejsce();
	if (wynik.x != -1 && wynik.y != -1) {
		Organizm* dziecko = new Zolw(swiat, wynik.x, wynik.y);
		dziecko->setNarodzony(COOLDOWN_NA_RODZENIE);
		swiat->dodajOrganizm(dziecko);
		swiat->dodajWpis(getNazwa() + "(" + to_string(getX()) + "," + to_string(getY()) + ") rozmnozyl sie! ");
	}
}

void Zolw::akcja() {

	int randomX = 0, randomY = 0;
	random_device device;
	mt19937 gen(device());

	int szansa = gen() % 4;

	while (!(randomX || randomY) && !szansa) {
		do {
			randomX = gen() % 3 - 1;
			randomY = gen() % 3 - 1;
		} while (SprawdzLokacje(getX() + randomX, getY() + randomY));
	}

	swiat->dodajWpis(this, getX(), getY(), getX() + randomX, getY() + randomY);

	kolizja(getX() + randomX, getY() + randomY);
}

bool Zolw::czyOdbilAtak(Organizm& atakujacy) {

	if (atakujacy.getSila() < 5)
		return true;
	else
		return false;
}
