#pragma once
#include "Individuo.hpp"
#include "Itens.hpp"


class PopController 
{
public:
	PopController();

protected:
	vector<pair<Individuo*, Individuo*>> FazerPares(vector<Individuo*> poptemp);
	int CalcValorTotal(vector<Individuo*> individuos);
	vector<pair<int, float>> CalcProbabilidades();
	Individuo* getIndividuoProbabilities(vector<pair<int, float>> tempProbabilidades);
	vector<Individuo*> Cruzar(pair<Individuo*, Individuo*> par, int media_filhos, int numIndivids, int geracao);
	void CheckMutation(vector<Individuo*> NewGeneration,int porcentagem_mutacao);
	void mutate(Individuo* i);
	Individuo* CriterioParada(Individuo* indiv, int margem_erro);
	vector<Individuo*> PexteBulbonica(vector<Individuo*> pop,int popMax);
	vector<Individuo*> OrderUpdatedIndividuos(vector<Individuo*> pop);

protected:
	vector<Individuo*> popTemp;
	Itens* itens;
private:
	random_device r;
	
};

