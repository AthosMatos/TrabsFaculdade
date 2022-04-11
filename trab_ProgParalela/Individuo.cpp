#include "Individuo.hpp"

Individuo::Individuo(int id, int geracao)
{
	this->id = id;
	this->geracao = geracao;
	peso = 0;
	valor = 0;
	cromossomo = new Cromossomo();
}

void Individuo::CreateRandom(int chanceAcimadoPeso)
{
	auto cr = cromossomo->GerarAleatoriamente(chanceAcimadoPeso);
	peso = cr.first;
	valor = cr.second;
}

void Individuo::Create(int chanceAcimadoPeso, pair<Cromossomo*, Cromossomo*> par, int pontoCorte, bool turn)
{
	auto cr = cromossomo->Gerar(par, pontoCorte, turn);
	peso = cr.first;
	valor = cr.second;
}

void Individuo::release()
{
	delete cromossomo;
}

