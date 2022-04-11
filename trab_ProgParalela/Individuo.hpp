#pragma once
#include "Cromossomo.hpp"

class Individuo
{
public:
	Individuo(int id, int geracao);
	void CreateRandom(int chanceAcimadoPeso);
	void Create(int chanceAcimadoPeso, pair<Cromossomo*, Cromossomo*> par, int pontoCorte, bool turn);
	void release(); //limpando memoria
	
public:
	int id; //id||numero do individuo
	int geracao; //geracao do individuo
	int peso; //peso do individuo
	int valor; //valor do individuo
	Cromossomo* cromossomo;//cromossomo do individuo com os items

	friend class Populacao;
};

