#include "CalcCamera.h"
#include <string>
#define eye pontos3[0]
#define center pontos3[1]
#define up pontos3[2]

#define LimiteCasas 100000.0

CalcCamera::CalcCamera()
{
	cout << "|| Calc Camera ||" << endl << endl;

	for (int i = 0; i < 3; i++)
	{
		ponto3 ptemp;
		string pon;
		if (i == 0)pon = "eye";
		else if(i == 1)pon = "center";
		else if (i == 2)pon = "up";

		cout << pon << " " << endl;

		cout << "x: "; cin >> ptemp.x;
		cout << "y: "; cin >> ptemp.y;
		cout << "z: "; cin >> ptemp.z;

		cout << "Ponto " << pon << "(" << ptemp.x << ',' << ptemp.y << ',' << ptemp.z << ')' << endl << endl;

		pontos3.push_back(ptemp);
	}

	CalcZe();
	CalcXe();
	CalcYe();
}

void CalcCamera::CalcZe()
{
	auto result = (1 / sqrt(pow(eye.x - center.x, 2) + pow(eye.y - center.y, 2) + pow(eye.z - center.z, 2)));
	Ze.x = result * (eye.x - center.x);
	Ze.y = result * (eye.y - center.y);
	Ze.z = result * (eye.z - center.z);

	cout << "Ze " << "(" << Ze.x << ',' << Ze.y << ',' << Ze.z << ')' << endl << endl;

}

void CalcCamera::CalcXe()
{
	auto result = (1 / sqrt(pow((Ze.y * up.z) - (Ze.z * up.y), 2) + pow((Ze.x * up.z) - (Ze.z * up.x), 2) + pow((Ze.x * up.y) - (Ze.y * up.x), 2)));
	Xe.x = result * ((up.y * Ze.z) - (up.z * Ze.y));
	Xe.y = result * ((up.x * Ze.z) - (up.z * Ze.x));
	Xe.z = result * ((up.x * Ze.y) - (up.y * Ze.x));

	cout << "Xe " << "(" << Xe.x << ',' << Xe.y << ',' << Xe.z << ')' << endl << endl;
}

void CalcCamera::CalcYe()
{
	Ye.x = (Ze.y * Xe.z) - (Ze.z * Xe.y); 
	Ye.y = (Ze.x * Xe.z) - (Ze.z * Xe.x); 
	Ye.z = (Ze.x * Xe.y) - (Ze.y * Xe.x); 

	cout << "Ye " << "(" << Ye.x << ',' << Ye.y << ',' << Ye.z << ')' << endl << endl;

}
