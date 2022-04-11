#include "GodController.hpp"

int GodController::ultimaPopCriada = 0;

void GodController::GerarPopulacao(int numIndivs,int mediaFilhos, int chanceAcimadoPeso)
{
	Populacao* populacao;
	populacao = new Populacao(numIndivs, mediaFilhos);
	populacao->GerarPopInicial(chanceAcimadoPeso);
	populacoes.insert(pair<int, Populacao*>(populacoes.size() + 1, populacao));
	ultimaPopCriada = populacoes.size();
}

void GodController::EvoluirPopulacao(int numIteracoes,int popId)
{
	if (!popId)popId = ultimaPopCriada;
	populacoes[popId]->EvoluirPop(numIteracoes);

}

void GodController::release()
{
	for (auto& p : populacoes)
	{
		p.second->release();
		delete p.second;
	}
	
}