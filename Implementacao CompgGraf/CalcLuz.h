#pragma once
#include "Calc.hpp"

class CalcLuz:Calc
{
public:
	CalcLuz();

private:
	ponto3 P, n, I, pos, Kd, Ke;
private:
	float Tx, Ty, Tz;

};

