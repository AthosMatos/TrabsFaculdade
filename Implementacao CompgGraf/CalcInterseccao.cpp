#include "CalcInterseccao.h"
#define Ve pontos3[0]
#define Vd pontos3[1]
#define Vc pontos3[2]
#define VPa pontos3[2]
#define VPb pontos3[3]
#define VPc pontos3[4]

CalcInterseccao::CalcInterseccao()
{
	cout << "|| Calc Interseccao ||" << endl << endl;

	cout << "1-Esfera 2-Plano: "; cin >> espl;
	if (espl != 1 && espl != 2)return;

	for (int i = 0;; i++)
	{
		ponto3 ptemp;
		string pon;
		if (i == 0)pon = "e";
		else if (i == 1)pon = "d";
		else
		{
			if (espl == 1)
			{
				if (i == 2)pon = "c";
				else if (i == 3)pon = "r";
				else break;

			}
			else
			{
				if (i == 2)pon = "a";
				else if (i == 3)pon = "b";
				else if (i == 4)pon = "c";
				else break;
			}
		}

		cout << pon << " " << endl;

		if (espl == 1 && i == 3) { cout << "r: "; cin >> r; }
		else
		{
			cout << "x: "; cin >> ptemp.x;
			cout << "y: "; cin >> ptemp.y;
			cout << "z: "; cin >> ptemp.z;

			cout << pon << "(" << ptemp.x << ',' << ptemp.y << ',' << ptemp.z << ')' << endl << endl;

			pontos3.push_back(ptemp);
		}

	}

	if (espl == 1) CalcEsfera();
	else CalcPlano();
}

void CalcInterseccao::CalcEsfera()
{
	cout << "||Resultados||" << endl;
	auto A = pow(Vd.x, 2) + pow(Vd.y, 2) + pow(Vd.z, 2); cout << "A: " << A << endl;
	auto B = ((Vd.x * 2) * (Ve.x - Vc.x)) + ((Vd.y * 2) * (Ve.y - Vc.y)) + ((Vd.z * 2) * (Ve.z - Vc.z)); cout << "B: " << B << endl;
	auto C = (pow(Ve.x - Vc.x, 2) + pow(Ve.y - Vc.y, 2) + pow(Ve.z - Vc.z, 2)) - pow(r, 2); cout << "C: " << C << endl;

	auto Delta = pow(B, 2) - (4 * A * C);//bhaskara
	cout << "Delta: " << Delta << endl;
	if (Delta < 0) { cout << "Delta Negativo"; return; }

	auto X1 = ((-B) + sqrt(Delta)) / (2 * A); cout << "X1: " << X1 << endl;
	auto X2 = ((-B) - sqrt(Delta)) / (2 * A); cout << "X2: " << X2 << endl;

	double X;
	if (X1 < X2)X = X1; else X = X2;

	ponto3 Pt; //ponto interseccao
	Pt.x = Ve.x + (X * Vd.x);
	Pt.y = Ve.y + (X * Vd.y);
	Pt.z = Ve.z + (X * Vd.z);

	cout << "Ponto interseccao: (" << Pt.x << ',' << Pt.y << ',' << Pt.z << ')' << endl;

	ponto3 ni;//normal
	auto result = (1 / sqrt(pow(Pt.x - Vc.x, 2) + pow(Pt.y - Vc.y, 2) + pow(Pt.z - Vc.z, 2)));

	ni.x = result * (Pt.x - Vc.x);
	ni.y = result * (Pt.y - Vc.y);
	ni.z = result * (Pt.z - Vc.z);

	cout << "Normal: (" << ni.x << ',' << ni.y << ',' << ni.z << ')' << endl;
}

void CalcInterseccao::CalcPlano()
{
	//print do sistema
	cout << "|" << (VPa.x - VPb.x) << "B " << (VPa.x - VPc.x) << "y " << (Vd.x) << "t = " << (VPa.x - Ve.x) << endl;
	cout << "|" << (VPa.y - VPb.y) << "B " << (VPa.y - VPc.y) << "y " << (Vd.y) << "t = " << (VPa.y - Ve.y) << endl;
	cout << "|" << (VPa.z - VPb.z) << "B " << (VPa.z - VPc.z) << "y " << (Vd.z) << "t = " << (VPa.z - Ve.z) << endl;
}
