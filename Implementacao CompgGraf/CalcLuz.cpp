#include "CalcLuz.h"

CalcLuz::CalcLuz()
{
	cout << "|| Calc Luz ||" << endl << endl;


	for (int i = 0; i < 5; i++)
	{
		if (i == 0)cout << "P "; else if (i == 1)cout << "n "; else if (i == 2)cout << "I "; else if (i == 3)cout << "posicao "; else if (i == 4)cout << "Kd ";
		
		cout << endl;

		ponto3 tempP;
		cout << "x: "; cin >> tempP.x;
		cout << "y: "; cin >> tempP.y;
		cout << "z: "; cin >> tempP.z;

		if (i == 0)cout << "P "; else if (i == 1)cout << "n "; else if (i == 2)cout << "I "; else if (i == 3)cout << "posicao "; else if (i == 4)cout << "Kd ";
		cout << "(" << tempP.x << ',' << tempP.y << ',' << tempP.z << ')' << endl << endl;

		if (i == 0)P = tempP; else if (i == 1)n = tempP; else if (i == 2)I = tempP; else if (i == 3)pos = tempP; else if (i == 4)Kd = tempP; 
	}

	ponto3 nNorm;
	nNorm.x = n.x / sqrt(pow(n.x, 2) + pow(n.y, 2) + pow(n.z, 2));
	nNorm.y = n.y / sqrt(pow(n.x, 2) + pow(n.y, 2) + pow(n.z, 2));
	nNorm.z = n.z / sqrt(pow(n.x, 2) + pow(n.y, 2) + pow(n.z, 2));

	ponto3 nL;
	nL.x = (pos.x - P.x) / sqrt(pow(pos.x - P.x, 2) + pow(pos.y - P.y, 2) + pow(pos.z - P.z, 2));
	nL.y = (pos.y - P.y) / sqrt(pow(pos.x - P.x, 2) + pow(pos.y - P.y, 2) + pow(pos.z - P.z, 2));
	nL.z = (pos.z - P.z) / sqrt(pow(pos.x - P.x, 2) + pow(pos.y - P.y, 2) + pow(pos.z - P.z, 2));
	
	auto result = (nNorm.x * nL.x) + (nNorm.y * nL.y) + (nNorm.z * nL.z);
	if (result <= 0)result = 0;

	ponto3 ld;
	ld.x = (Kd.x * I.x * result);
	ld.y = (Kd.y * I.y * result);
	ld.z = (Kd.z * I.z * result);

	cout << "LD" << "(" << ld.x << ',' << ld.y << ',' << ld.z << ')' << endl << endl;

}
