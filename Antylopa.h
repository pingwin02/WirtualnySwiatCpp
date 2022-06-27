#pragma once

#include "Zwierze.h"

class Antylopa : public Zwierze {
public:
	Antylopa(Swiat* swiat, int polozenieX, int polozenieY);
	void rozmnoz() override;
	void akcja() override;
	void atakowanie(Organizm& atakowany);
	bool czyUniknalAtak(Organizm& atakujacy) override;
};