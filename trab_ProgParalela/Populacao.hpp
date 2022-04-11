#pragma once
#include "PopController.hpp"

using namespace std;

class Populacao : private PopController
{
public:
	//Iniciador de Populacoes
	Populacao(int NumIndivids, int media_filhos);

	void GerarPopInicial(int chanceAcimadoPeso);
	bool EvoluirPop(int iteracoes);
	void release();

protected:
	vector<Individuo*> getVector(); //retorna um vetor com os individuos da populacao
	int getGeracao(); //retorna o valor da geracao erm que a populacao esta

private:
	vector<Individuo*> pop;
	vector<Individuo*> NewGeneration;
private:
	int num_individuos; //Numero de individuos que sempre vao compor a populacao
	int media_filhos; //Media de filhos por familia, valor muda a porcentagem de chance de vir 1 ou + filhos
	int geracao; //Geracao em que a populacao esta
	int valor_total_acomulado; //soma de todos os valore dos individuos da populacao

	friend class GodController;
};

