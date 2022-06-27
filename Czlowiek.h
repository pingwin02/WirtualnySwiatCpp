#pragma once

#include "Zwierze.h"

class Czlowiek : public Zwierze {
private:
	int mnoznik;
	int cooldown;
protected:
	void rozmnoz() override;
public:
	Czlowiek(Swiat* swiat, int polozenieX, int polozenieY);
	void akcja() override;
	void setCooldown(int cooldown);
};