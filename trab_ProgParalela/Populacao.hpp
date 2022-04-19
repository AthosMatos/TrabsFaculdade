#pragma once
#include "Individuo.hpp"
#include <thread>

using namespace std;

class Populacao 
{
public:
	//Iniciador de Populacoes
	Populacao(int NumIndivids, int media_filhos, int porcentagem_mutacao, float margem_erro = 0.5,int numThreads = 4);

	void GerarPopInicial(int chanceAcimadoPeso);
	bool EvoluirPop(int iteracoes);
	void release();

protected:
	vector<Individuo*> getVector(); //retorna um vetor com os individuos da populacao
	int getGeracao(); //retorna o valor da geracao erm que a populacao esta

private:
	vector<pair<Individuo*, Individuo*>> FazerPares();
	int CalcValorTotal(vector<Individuo*> individuos);
	vector<pair<int, float>> CalcProbabilidades();
	Individuo* getIndividuoProbabilities(vector<pair<int, float>> tempProbabilidades);
	void Cruzar(pair<Individuo*, Individuo*> par, int numIndivids, int index);
	void CheckMutation(Individuo* Teen);
	void mutate(Individuo* i);
	void CriterioParada(Individuo* indiv, int margem_erro);
	void PexteBulbonica(int popMax);
	void OrderUpdatedIndividuos();

private:
	void CruzarThreaded(vector<pair<Individuo*, Individuo*>> paresIndividuos, float start, float end, int index);

private:
	vector<Individuo*> pop;
	vector<Individuo*> popTemp;
	vector<Individuo*> NewGeneration;
	vector<thread> threads;

private:
	map <int,int> valoresPesosUsados; //map para valores achar individuos com valores repetidos mais rapido e deletar eles da populacao

private:
	int num_individuos; //Numero de individuos que sempre vao compor a populacao
	int media_filhos; //Media de filhos por familia, valor muda a porcentagem de chance de vir 1 ou + filhos
	int geracao; //Geracao em que a populacao esta
	int valor_total_acomulado; //soma de todos os valore dos individuos da populacao
	int porcentagem_mutacao;
	float margem_erro;
	int numThreads;

	Itens* itens;

	Individuo* winner;
	random_device r;

	friend class GodController;
};

