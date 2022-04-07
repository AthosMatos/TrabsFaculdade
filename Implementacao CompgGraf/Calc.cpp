#include "Calc.hpp"

Calc::Calc()
{
	vetoresResult.clear();
}

void Calc::PrintResult()
{
	for (auto& i : vetoresResult)
	{
		cout << "| " << i << " |" << endl;
	}
	cout << endl;
}