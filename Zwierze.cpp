#include "Zwierze.h"

void Zwierze::akcja() {

	int randomX = 0, randomY = 0;
	random_device device;
	mt19937 gen(device());

	while (!(randomX || randomY)) {
		do {
			randomX = gen() % 3 - 1;
			randomY = gen() % 3 - 1;
		} while (SprawdzLokacje(getX() + randomX, getY() + randomY));
	} 

	swiat->dodajWpis(this, getX(), getY(), getX() + randomX, getY() + randomY);

	kolizja(getX() + randomX , getY() + randomY);

}