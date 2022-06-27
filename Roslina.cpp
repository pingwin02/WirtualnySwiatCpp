#include "Roslina.h"

void Roslina::akcja() {
	random_device device;
	mt19937 gen(device());

	int szansa = gen() % 100;

	if (!szansa && !getNarodzony()) {
		rozmnoz();
		swiat->dodajWpis(getNazwa() + "(" + to_string(getX()) + "," + to_string(getY()) + ") sie zasial");
	}
	else {
		swiat->dodajWpis(getNazwa() + "(" + to_string(getX()) + "," + to_string(getY()) + ") nie zasial sie");
	}

}