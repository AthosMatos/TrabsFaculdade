#pragma once
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class Calc
{
public:
	Calc();
	void PrintResult();

protected:
	struct ponto4
	{
		float x, y, z, w;
	};
	struct ponto3
	{
		float x, y, z;
	};

protected:
	vector<float> vetoresResult;
	int NumPontos;
	vector <ponto4> pontos4;
	vector <ponto3> pontos3;
};

