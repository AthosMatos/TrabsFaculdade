#pragma once
#include "Calc.hpp"

class CalcInterseccao : public Calc
{
public:
	CalcInterseccao();

private:
	void CalcEsfera();
	void CalcPlano();

private:
	float r;
	int espl;
};

