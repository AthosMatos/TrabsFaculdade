#pragma once
#include "Calc.hpp"

class CalcEscala : public Calc
{
public:
	CalcEscala();

private:
	float x, y, z, w;
	float Sx, Sy, Sz;
};

