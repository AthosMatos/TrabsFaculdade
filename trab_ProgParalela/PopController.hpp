#pragma once
#include "Individuo.hpp"

class PopController
{
protected:
	vector<pair<Individuo*, Individuo*>> FazerPares(vector<Individuo*> poptemp);
	int CalcValorTotal(vector<Individuo*> individuos);
	vector<pair<int, float>> CalcProbabilidades();
	Individuo* getIndividuoProbabilities(vector<pair<int, float>> tempProbabilidades);
	vector<Individuo*> Cruzar(pair<Individuo*, Individuo*> par, int media_filhos, int numIndivids, int geracao);

protected:
	vector<Individuo*> popTemp;

};

