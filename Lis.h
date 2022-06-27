#pragma once


#include "Zwierze.h"

class Lis : public Zwierze {
public:
	Lis(Swiat* swiat, int polozenieX, int polozenieY);
	void rozmnoz() override;
	void akcja() override;
};