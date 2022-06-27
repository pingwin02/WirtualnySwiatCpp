#include "Lis.h"

Lis::Lis(Swiat* swiat, int polozenieX, int polozenieY) {
	this->swiat = swiat;
	setX(polozenieX);
	setY(polozenieY);
	setSila(L_SILA);
	setInicjatywa(L_INICJATYWA);
	setZnak(LIS);
	setNazwa("Lis");
}

void Lis::rozmnoz() {
	MiejsceUrodzenia wynik = SprawdzMiejsce();
	if (wynik.x != -1 && wynik.y != -1) {
		Lis* dziecko = new Lis(swiat, wynik.x, wynik.y);
		dziecko->setNarodzony(COOLDOWN_NA_RODZENIE);
		swiat->dodajOrganizm(dziecko);
		swiat->dodajWpis(getNazwa() + "(" + to_string(getX()) + "," + to_string(getY()) + ") rozmnozyl sie! ");
	}
}

void Lis::akcja() {

	int randomX = 0, randomY = 0;
	random_device device;
	mt19937 gen(device());

	while (!(randomX || randomY)) {
		do {
			randomX = gen() % 3 - 1;
			randomY = gen() % 3 - 1;
		} while (SprawdzLokacje(getX() + randomX, getY() + randomY));
	}

	Organizm*** plansza = swiat->getPlansza();
	Organizm* miejsce = plansza[getY() + randomY][getX() + randomX];

	if (miejsce != nullptr) {
		if (miejsce->getSila() > getSila()) {
			swiat->dodajWpis(getNazwa() + "(" + to_string(getX()) + "," + to_string(getY()) + ") chcial isc ("
				+ to_string(getX() + randomX) + "," + to_string(getY() + randomY) + ") ale wykryl " + miejsce->getNazwa());
			randomX = 0;
			randomY = 0;
		}
		swiat->dodajWpis(this, getX(), getY(), getX() + randomX, getY() + randomY);
	}
	else {
		swiat->dodajWpis(this, getX(), getY(), getX() + randomX, getY() + randomY);
	}


	kolizja(getX() + randomX, getY() + randomY);
	
}