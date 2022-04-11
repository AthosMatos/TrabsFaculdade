#include "Cromossomo.hpp"

void Cromossomo::release()
{
	Itens::release();
}

bool Cromossomo::isGeneActive(int id)
{
	if (genes[id]) return true;
	else return false;
}

pair<int, int> Cromossomo::GerarAleatoriamente(int chanceAcimaPeso)
{
	random_device rd;
	auto random = default_random_engine{ rd() };
	auto itemscpy = itens;
	shuffle(itemscpy.begin(), itemscpy.end(), random); //randomizando para a ordem dos intens sempre serem aleatoria
	uniform_int_distribution<> uniform_dist(1, 100);

	int TempPeso = 0;
	int TempValor = 0;

	for (int i = 0; i < itemscpy.size(); i++)
	{
		if ((TempPeso + itemscpy[i]->peso < pesoMax) || (uniform_dist(random) <= chanceAcimaPeso))
		{
			genes.insert(pair<int, bool>(itemscpy[i]->id, true));
			TempPeso += itemscpy[i]->peso;
			TempValor += itemscpy[i]->valor;
		}
		else
		{
			genes.insert(pair<int, bool>(itemscpy[i]->id, false));
		}
	}
	return pair<int, int>(TempPeso, TempValor);
}

pair<int, int> Cromossomo::Gerar(pair<Cromossomo*, Cromossomo*> par, int pontoCorte, bool turn)
{
	Cromossomo* C1;
	Cromossomo* C2;

	int TempPeso = 0;
	int TempValor = 0;

	if (turn) { C1 = par.first; C2 = par.second; }
	else { C1 = par.second; C2 = par.first; }
	
	for (int i = pontoCorte - 1; i >= 0; i--)
	{
		genes.insert(pair<int, bool>(i + 1, C1->genes[i + 1]));
		if (C1->genes[i + 1])
		{
			TempPeso += itens[i]->peso;
			TempValor += itens[i]->valor;
		}
	}

	for (int i = pontoCorte; i < itens.size(); i++)
	{
		genes.insert(pair<int, bool>(i + 1, C2->genes[i + 1]));
		if (C1->genes[i + 1])
		{
			TempPeso += itens[i]->peso;
			TempValor += itens[i]->valor;
		}
	}

	return pair<int, int>(TempPeso, TempValor);
}

map<int, bool> Cromossomo::getGenes()
{
	return genes;
}

