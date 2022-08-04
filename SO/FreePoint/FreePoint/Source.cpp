#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <mutex>  

using namespace std;

bool CA = false;
bool CB = false;
mutex mtx;
char turn;

void ProcessoA()
{
	CA = true;
	turn = 'B';
	
	while (CB && (turn == 'B'))
	{
		mtx.lock();
		cout << "Processo A Esperando" << endl;
		mtx.unlock();
	}
	mtx.lock();
	cout << "Secao Critica do Processo A Comecado" << endl;
	mtx.unlock();
	for (int i = 0; i < 10000; i++);
	mtx.lock();
	cout << "Secao Critica do Processo A Terminado" << endl;
	mtx.unlock();

	CA = false;

	mtx.lock();
	cout << "Secao Normal: Processo A" << endl;
	mtx.unlock();
}

void ProcessoB()
{
	CB = true;
	turn = 'A';

	while (CA && (turn == 'A'))
	{
		mtx.lock();
		cout << "Processo B Esperando" << endl;
		mtx.unlock();
	}
	mtx.lock();
	cout << "Secao Critica do Processo B Comecado" << endl;
	mtx.unlock();
	for (int i = 0; i < 10000; i++);
	mtx.lock();
	cout << "Secao Critica do Processo B Terminado" << endl;
	mtx.unlock();

	CB = false;

	mtx.lock();
	cout << "Secao Normal: Processo B" << endl;
	mtx.unlock();
}


int main()
{
	vector <thread> processos;
	
	processos.emplace_back(ProcessoA);
	processos.emplace_back(ProcessoB);

	for (auto& p : processos)
	{
		p.join();
	}

	return 0;
}