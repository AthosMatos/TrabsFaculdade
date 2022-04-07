#include "CalcEscala.hpp"

CalcEscala::CalcEscala()
{
	cout << "Calc Escala" << endl;
	cout << "Ponto x: "; cin >> x;
	cout << "Ponto y: "; cin >> y;
	cout << "Ponto z: "; cin >> z;
	cout << "Ponto w: "; cin >> w;

	cout << "Ponto Sx: "; cin >> Sx;
	cout << "Ponto Sy: "; cin >> Sy;
	cout << "Ponto Sz: "; cin >> Sz;

	vetoresResult.push_back(x * Sx); //Sx
	vetoresResult.push_back(y * Sy); //Sy
	vetoresResult.push_back(z * Sz); //Sz
	vetoresResult.push_back(w * 1); //Sw
}


