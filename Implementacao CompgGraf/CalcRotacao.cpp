#include "CalcRotacao.hpp"
#define PI 3.14159265
#define LimiteCasas 100000.0

CalcRotacao::CalcRotacao()
{
	cout << "|| Calc Rotacao ||" << endl << endl;

	cout << "Numero de Pontos do poligono: "; cin >> NumPontos;

	for (int i = 0; i < NumPontos; i++)
	{
		ponto4 ptemp;

		cout << "Ponto " << pontos4.size() + 1 << endl;

		cout << "x: "; cin >> ptemp.x;
		cout << "y: "; cin >> ptemp.y;
		cout << "z: "; cin >> ptemp.z;
		ptemp.w = 1;

		cout << "Ponto " << pontos4.size() + 1 << "(" << ptemp.x << ',' << ptemp.y << ',' << ptemp.z << ',' << ptemp.w << ')' << endl << endl;

		pontos4.push_back(ptemp);
	}

	while (true)
	{
		cout << endl;
		cout << "Coordenada para calcular: "; cin >> coord; if (coord=='0') break;
		cout << "Graus: "; cin >> graus;
		graus = graus * PI / 180;

		if (coord == 'x') CalcX();
		else if (coord == 'y') CalcY();
		else if (coord == 'z') CalcZ();
	}

}

void CalcRotacao::CalcZ()
{
	int index = 1;
	for (auto& p : pontos4)
	{
		auto px = (((round(cos(graus) * LimiteCasas) / LimiteCasas) * p.x)) + (round((-sin(graus) * LimiteCasas) / LimiteCasas) * p.y);
		auto py = (((round(sin(graus) * LimiteCasas) / LimiteCasas) * p.x)) + (round((cos(graus) * LimiteCasas) / LimiteCasas) * p.y);
		auto pz = 1 * p.z;
		auto pw = 1 * p.w;

		p.x = px;
		p.y = py;
		p.z = pz;
		p.w = pw;

		cout << "Novo ponto " << index << "(" << p.x << ","
			<< p.y << ","
			<< p.z << ","
			<< p.w << ")" << endl;
		index++;
	}
}

void CalcRotacao::CalcY()
{
	int index = 1;
	for (auto& p : pontos4)
	{
		auto px = ((round(cos(graus) * LimiteCasas) / LimiteCasas) * p.x) + (round((sin(graus) * LimiteCasas) / LimiteCasas) * p.z);
		auto py = 1 * p.y;
		auto pz = ((round(-sin(graus) * LimiteCasas) / LimiteCasas) * p.x) + (round((cos(graus) * LimiteCasas) / LimiteCasas) * p.z);
		auto pw = 1 * p.w;

		p.x = px;
		p.y = py;
		p.z = pz;
		p.w = pw;

		cout << "Novo ponto " << index << "(" << p.x << ","
			<< p.y << ","
			<< p.z << ","
			<< p.w << ")" << endl;
		index++;
	}
}

void CalcRotacao::CalcX()
{
	int index = 1;
	for (auto& p : pontos4)
	{	
		auto px = 1 * p.x; p.x = round(p.x *LimiteCasas) /LimiteCasas;
		auto py = ((round(cos(graus) * LimiteCasas) / LimiteCasas) * p.y) + (round(-sin(graus) * LimiteCasas) / LimiteCasas * p.z);
		auto pz = ((round(sin(graus) * LimiteCasas) / LimiteCasas) * p.y) + (round((cos(graus) * LimiteCasas) / LimiteCasas)  * p.z);
		auto pw = 1 * p.w;

		p.x = px;
		p.y = py;
		p.z = pz;
		p.w = pw;

		cout << "Novo ponto " << index << "(" << p.x << ","
			<< p.y << ","
			<< p.z << ","
			<< p.w << ")" << endl;
		index++;
	}
}
