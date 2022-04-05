#include "mochila.h"

using namespace std;

int main()
{
    //auto mochila = new Mochila(12, 50, 7);

	auto mochila = new Mochila;
	mochila->setMargemErro(0.05);
	//mochila->setMaxIteracoes(50);
	//mochila->setMutacao(20);
	mochila->setNumeroMaxPopulacao(100);

	mochila->GerarItems("test5");
	mochila->GerarPopInicial();
	mochila->Evoluir();

	//geraitems
	//gerarpopinit
	//LogFileData();

	return 0;
}