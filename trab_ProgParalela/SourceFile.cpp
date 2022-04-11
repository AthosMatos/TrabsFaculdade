#include "GodController.hpp"

using namespace std;

int main()
{
    //auto mochila = new Mochila(12, 50, 7);

	//auto mochila = new Mochila;
	//mochila->setMargemErro(0.05);
	//mochila->setMaxIteracoes(50);
	//mochila->setMutacao(20);
	//mochila->setNumeroMaxPopulacao(100);

	//mochila->GerarItems("test5");
	//mochila->GerarPopInicial();
	//mochila->Evoluir();
	Itens* itens = new Itens();
	itens->SetItens("test1");
	
	GodController* god = new GodController;
	god->GerarPopulacao();
	god->EvoluirPopulacao();

	//geraitems
	//gerarpopinit
	//LogFileData();

	return 0;
}