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

void Individuo::CreatePerfectValor(int chanceAcimadoPeso)
{
	auto cr = cromossomo->GerarPerfeitoValor(chanceAcimadoPeso);
	peso = cr.first;
	valor = cr.second;
}

void Individuo::CreatePerfectPeso(int chanceAcimadoPeso)
{
	auto cr = cromossomo->GerarPerfeitoPeso(chanceAcimadoPeso);
	peso = cr.first;
	valor = cr.second;
}

void Individuo::CreatePerfectCustoBene(int chanceAcimadoPeso)
{
	auto cr = cromossomo->GerarPerfeitoValorCustoBene(chanceAcimadoPeso);
	peso = cr.first;
	valor = cr.second;
}

void Individuo::Create(int chanceAcimadoPeso, pair<Cromossomo*, Cromossomo*> par, int pontoCorte, bool turn)
{
	auto cr = cromossomo->Gerar(par, pontoCorte, turn);
	peso = cr.first;
	valor = cr.second;
}

void Individuo::UpdateDados()
{
	auto cv = cromossomo->GetVector();
	int tempPeso = 0;
	int	tempValor = 0;

	for (auto& i : cv)
	{
		tempPeso += i->peso;
		tempValor += i->valor;
	}

	peso = tempPeso;
	valor = tempValor;
}

void Individuo::release()
{
	free(cromossomo);
}

