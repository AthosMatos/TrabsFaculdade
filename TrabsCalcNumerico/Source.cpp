#include <iostream>
#include <math.h>

using namespace std;

float func(int x)
{
	return ((2 * x) / (1 + pow(x, 3)));
}


float CalcSimpson(float h, int interval_start, int interval_end)
{
	float x0 = 0;
	float x1 = x0 + h;
	float x2 = x1 + h;
	float I = 0;

	while(x2 < interval_end)
	{
		I += ((h / 3) * (func(interval_start + x0) + (4 * func(interval_start + x1)) + func(interval_start + x2)));
		x0 = x2;
		x1 = x0 + h;
		x2 = x1 + h;
	}

	return I;
}

float CalcTrapezio(float h, int interval_start, int interval_end)
{
	float x0 = 0;
	float x1 = x0 + h;
	float I = 0;

	while(x1 < interval_end)
	{
		I += ((h / 2) * (func(interval_start + x0) + func(interval_start + x1)));
		x0 = x1;
		x1 = x0 + h;
	}

	return I;
}

int main()
{
	float i_a; //intervalo inicial da integral 
	float i_b; //intervalo final da integral 
	int n;

	cout << "intervalo inicial da integral: ";
	cin >> i_a;
	cout << "intervalo final da integral: ";
	cin >> i_b;

	cout << "numero de trapezios: ";
	cin >> n;

	auto h = (i_b - i_a) / n;

	CalcTrapezio(h, i_a, i_b);
	//CalcSimpson(h, i_a, i_b);

	return 0;
}