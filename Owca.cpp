#include "Owca.h"

Owca::Owca(Swiat* swiat, int polozenieX, int polozenieY) {
	this->swiat = swiat;
	setX(polozenieX);
	setY(polozenieY);
	setSila(O_SILA);
	setInicjatywa(O_INICJATYWA);
	setZnak(OWCA);
	setNazwa("Owca");
}

void Owca::rozmnoz() {
	MiejsceUrodzenia wynik = SprawdzMiejsce();
	if (wynik.x != -1 && wynik.y != -1) {
		Organizm* dziecko = new Owca(swiat, wynik.x, wynik.y);
		dziecko->setNarodzony(COOLDOWN_NA_RODZENIE);
		swiat->dodajOrganizm(dziecko);
		swiat->dodajWpis(getNazwa() + "(" + to_string(getX()) + "," + to_string(getY()) + ") rozmnozyl sie! ");
	}
}
