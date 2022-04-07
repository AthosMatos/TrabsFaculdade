#include "CalcTranslacao.hpp"

CalcTranslacao::CalcTranslacao()
{
	cout << "Calc Translacao" << endl;
	cout << "Ponto x: "; cin >> x;
	cout << "Ponto y: "; cin >> y;
	cout << "Ponto z: "; cin >> z;
	cout << "Ponto w: "; cin >> w;

	cout << "Ponto Tx: "; cin >> Tx;
	cout << "Ponto Ty: "; cin >> Ty;
	cout << "Ponto Tz: "; cin >> Tz;

	vetoresResult.push_back((x * 1) + (1 * Tx)); //Tx
	vetoresResult.push_back((y * 1) + (1 * Ty)); //Ty
	vetoresResult.push_back((z * 1) + (1 * Tz)); //Tz
	vetoresResult.push_back(1 * w); //Tw
}
