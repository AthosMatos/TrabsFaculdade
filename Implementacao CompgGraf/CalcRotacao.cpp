#include "CalcRotacao.hpp"

CalcRotacao::CalcRotacao()
{
	cout << "Calc Rotacao" << endl;
	cout << "Ponto: "; cin >> ponto;
	cout << "Graus: "; cin >> graus;
	cout << "Ponto x: "; cin >> x;
	cout << "Ponto y: "; cin >> y;
	cout << "Ponto z: "; cin >> z;
	cout << "Ponto w: "; cin >> w;

	if (ponto == 'x') CalcX();
	else if (ponto == 'y') CalcY();
	else if (ponto == 'z') CalcZ();
}

void CalcRotacao::CalcZ()
{
	vetoresResult.push_back((cos(graus) * x) + (-sin(graus) * y)); //x
	vetoresResult.push_back((sin(graus) * x) + (cos(graus) * y)); //y
	vetoresResult.push_back(1 * z); //z
	vetoresResult.push_back(1 * w); //const
}

void CalcRotacao::CalcY()
{
	vetoresResult.push_back((cos(graus) * x) + (sin(graus) * z)); //x
	vetoresResult.push_back(1 * y); //y
	vetoresResult.push_back((-sin(graus) * x) + (cos(graus) * z)); //z
	vetoresResult.push_back(1 * w); //const	
}

void CalcRotacao::CalcX()
{
	vetoresResult.push_back(1 * x); //x
	vetoresResult.push_back((cos(graus) * y) + (-sin(graus) * z)); //y
	vetoresResult.push_back((sin(graus) * y) + (cos(graus) * z)); //z
	vetoresResult.push_back(1 * w); //const
}
