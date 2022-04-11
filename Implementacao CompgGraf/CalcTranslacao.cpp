#include "CalcTranslacao.hpp"

CalcTranslacao::CalcTranslacao()
{
	cout << "|| Calc Translacao ||" << endl << endl;

	cout << "Numero de Pontos do poligono: "; cin >> NumPontos;

	for (int i = 0; i < NumPontos; i++)
	{
		ponto4 ptemp;

		cout << "Ponto " << pontos4.size()+1 << endl;

		cout << "x: "; cin >> ptemp.x;
		cout << "y: "; cin >> ptemp.y;
		cout << "z: "; cin >> ptemp.z;
		ptemp.w = 1;

		cout << "Ponto " << pontos4.size() + 1 << "(" << ptemp.x << ',' << ptemp.y << ',' << ptemp.z << ',' << ptemp.w << ')' << endl << endl;

		pontos4.push_back(ptemp);
	}

	cout << "Ponto para Transformacao" << endl;

	cout << "Ponto Tx: "; cin >> Tx;
	cout << "Ponto Ty: "; cin >> Ty;
	cout << "Ponto Tz: "; cin >> Tz; cout << endl;

	int index = 1;
	for (auto& p : pontos4)
	{
		cout << "Novo ponto " << index << "(" << (p.x * 1) + (1 * Tx) << ","
			<< (p.y * 1) + (1 * Ty) << ","
			<< (p.z * 1) + (1 * Tz) << "," 
			<< 1 * p.w << ")" << endl;

		index++;
	}
}

