#pragma once
#include "Populacao.hpp"

class GodController
{
public:
	//gera uma populacao
	void GerarPopulacao(int numIndivs = 100, int mediaFilhos = 2, int chanceAcimadoPeso = 0, int porcentagem_mutacao = 5);
	//evolui uma populacao ate o limite de iteracoes
	void EvoluirPopulacao(int numIteracoes = 50,int popId = 0);
	void release();

private:
	map <int, Populacao*> populacoes;

private:
	static int ultimaPopCriada;
};

