#include "Mlecz.h"

Mlecz::Mlecz(Swiat* swiat, int polozenieX, int polozenieY) {
	this->swiat = swiat;
	setX(polozenieX);
	setY(polozenieY);
	setSila(M_SILA);
	setInicjatywa(ROSLINA_INICJATYWA);
	setZnak(MLECZ);
	setNazwa("Mlecz");
}

void Mlecz::akcja() {

	for (int i = 0; i < 3; i++) {
		Roslina::akcja();
	}

}

void Mlecz::rozmnoz() {
	MiejsceUrodzenia wynik = SprawdzMiejsce();
	if (wynik.x != -1 && wynik.y != -1) {
		Organizm* dziecko = new Mlecz(swiat, wynik.x, wynik.y);
		dziecko->setNarodzony(COOLDOWN_NA_RODZENIE);
		swiat->dodajOrganizm(dziecko);
	}
}


