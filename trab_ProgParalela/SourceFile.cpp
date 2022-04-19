#include "GodController.hpp"

using namespace std;

int main()
{
	Itens* itens = new Itens();
	itens->SetItens("test1");
	
	GodController* god = new GodController;
	god->GerarPopulacao();
	god->EvoluirPopulacao(10);

	//geraitems
	//gerarpopinit
	//LogFileData();

	return 0;
}