#include "mochila.h"
#include "GeradorPopulacao.h"

Mochila::Mochila(int capacidadeMax, int valorMax, int numero_de_items)
{
	this->capacidadeMax = capacidadeMax;
	this->valorMax = valorMax;

	valorAdicionados = 0;
	capacidadePreenchida = 0;

	item tempItem;
	srand(time(NULL));

	for (int i = 0; i < numero_de_items; i++)
	{
		tempItem.id = i + 1;
		
		tempItem.peso = rand() % capacidadeMax + 1;
		
		tempItem.valor = rand() % valorMax + 1;

		items.push_back(tempItem);
	}

	logItems(items);

	GerarIndividuo_MenoresPesos(items, capacidadeMax, valorMax);
	GerarIndividuo_MenoresValores(items, capacidadeMax, valorMax);

	logIndividuos();
	return;

}
