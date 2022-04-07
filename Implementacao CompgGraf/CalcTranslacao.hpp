#pragma once
#include "Calc.hpp"

class CalcTranslacao : public Calc
{
public:
	CalcTranslacao();

private:
	float x, y, z, w;
	float Tx, Ty, Tz;
};

