#include "CalcEscala.hpp"

CalcEscala::CalcEscala()
{
	cout << "|| Calc Escala ||" << endl << endl;

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


	cout << "Ponto para Escala" << endl;

	cout << "Ponto Sx: "; cin >> Sx;
	cout << "Ponto Sy: "; cin >> Sy;
	cout << "Ponto Sz: "; cin >> Sz; cout << endl;

	int index = 1;
	for (auto& p : pontos4)
	{
		cout << "Novo ponto " << index << "(" << p.x * Sx << ","
			<< p.y * Sy << ","
			<< p.z * Sz << ","
			<< p.w * 1 << ")" << endl;

		index++;
	}
	
}


