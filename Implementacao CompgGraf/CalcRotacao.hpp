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
	char coord;
	float graus;
};

