#pragma once
#include <map>
#include <algorithm> 
#include <random>
#include "Itens.hpp"

using namespace std;

class Cromossomo : private Itens
{
public:
	//Funcao para checar se o gene esta sendo utilizado 
	bool isGeneActive(int id);
	//gera cromossomos aleatoriamente com uma chance de gerar acima do peso
	pair<int,int> GerarAleatoriamente(int chanceAcimaPeso);
	pair<int, int> GerarPerfeitoPeso(int chanceAcimaPeso);
	pair<int, int> GerarPerfeitoValor(int chanceAcimaPeso);
	pair<int, int> GerarPerfeitoValorCustoBene(int chanceAcimaPeso);
	pair<int, int> Gerar(pair<Cromossomo*, Cromossomo*> par, int pontoCorte, bool turn);
	map<int, bool> getGenes();

protected:
	map<int, bool> genes; //map dos genes onde o int = (id do item) e bool = (se esse item sendo utilizado)

	friend class Individuo;
	friend class Populacao;
};

