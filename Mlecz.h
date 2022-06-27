#pragma once

#include "Roslina.h"

class Mlecz : public Roslina {
public:
	Mlecz(Swiat* swiat, int polozenieX, int polozenieY);
	void akcja() override;
	void rozmnoz() override;
};