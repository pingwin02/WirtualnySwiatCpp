#include "Trawa.h"

Trawa::Trawa(Swiat* swiat, int polozenieX, int polozenieY) {
	this->swiat = swiat;
	setX(polozenieX);
	setY(polozenieY);
	setSila(T_SILA);
	setInicjatywa(ROSLINA_INICJATYWA);
	setZnak(TRAWA);
	setNazwa("Trawa");
}

void Trawa::rozmnoz() {
	MiejsceUrodzenia wynik = SprawdzMiejsce();
	if (wynik.x != -1 && wynik.y != -1) {
		Organizm* dziecko = new Trawa(swiat, wynik.x, wynik.y);
		dziecko->setNarodzony(COOLDOWN_NA_RODZENIE);
		swiat->dodajOrganizm(dziecko);
	}
}

