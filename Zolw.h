#pragma once

#include "Zwierze.h"

class Zolw : public Zwierze {
public:
	Zolw(Swiat* swiat, int polozenieX, int polozenieY);
	void rozmnoz() override;
	void akcja() override;
	bool czyOdbilAtak(Organizm& atakujacy) override;
};