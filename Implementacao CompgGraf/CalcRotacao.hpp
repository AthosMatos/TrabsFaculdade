#pragma once
#include "Calc.hpp"

class CalcRotacao : public Calc
{
public:
	CalcRotacao();

private:
	void CalcZ();
	void CalcY();
	void CalcX();

private:
	char ponto;
	float x, y, z, w;
	int graus;
};

