#pragma once
#include "Calc.hpp"
class CalcCamera : public Calc
{
public:
	CalcCamera();

private:
	void CalcZe();
	void CalcXe();
	void CalcYe();

private:
	ponto3 Ze, Xe, Ye;
};

