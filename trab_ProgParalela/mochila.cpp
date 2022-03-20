#include "mochila.h"
#include "GeradorPopulacaoFuncs.h"
#include "HelperFuncs.h"
#include <functional>
#include "itemFuncs.h"

Mochila::Mochila(int numero_de_items, int PesoMax, int valorMax)
{
	this->valorMax = valorMax;
	this->PesoMax = PesoMax;

	auto& individuosRef = this->individuos;

	auto items = CreateItems(numero_de_items, PesoMax, valorMax);
	logItems(items);

	GerarIndividuo_MenoresPesos(individuosRef, items, valorMax, PesoMax);
	logIndividuos(individuos);

	//GerarIndividuo_MenoresValores(items, valorMax, PesoMax);



}

Mochila::Mochila()
{
	individuo OptimalIndividuo;
	auto& OptimalIndividuoRef = OptimalIndividuo;

	auto& valorMaxRef = this->valorMax;
	auto& PesoMaxRef = this->PesoMax;
	auto& individuosRef = this->individuos;
	auto& valorTotalSomaRef = this->valorTotalSoma;
	auto& TotalItemsRef = this->TotalItems;

	items = FiletoItems("test1", valorMaxRef, PesoMaxRef, TotalItemsRef, OptimalIndividuoRef);
	logData(PesoMax, "PesoMax",2);
	//logItems(items);

	GerarIndividuo_MenoresPesos(individuosRef,items, PesoMax, valorTotalSomaRef);
	GerarIndividuo_MenoresValores(individuosRef, items, PesoMax, valorTotalSomaRef);
	GerarIndividuo_MelhorCustoBeneficioPeso(individuosRef, items, PesoMax, valorTotalSomaRef);
	GerarIndividuo_MelhorCustoBeneficioValor(individuosRef, items, PesoMax, valorTotalSomaRef);
	GerarIndividuo_Ultra_Aleatorio(individuosRef, items, PesoMax, valorTotalSomaRef);
	GerarIndividuo_Ultra_Aleatorio(individuosRef, items, PesoMax, valorTotalSomaRef);

	//sort(individuos.begin(), individuos.end(), MaiorPaMenor_ValorIndividuo);
	logIndividuosReducedData(individuos);
	geracoes.push_back(individuos);

	logData(valorTotalSoma, "valorTotalSoma", 2);

	int pardone = 0;
	pair<individuo, individuo> par;

	auto tempindividuos = individuos;
	auto& tempindividuosRef = tempindividuos;

	auto valorTotalSomaTemp = valorTotalSoma;

	for (auto& i : tempindividuos)
	{
		Probabilidades.clear();
		valorTotalSomaTemp = CalcValorTotal(tempindividuos);

		for (auto& i : tempindividuos)
		{
			cout << fixed;
			cout.precision(2);
			cout << "- prob individuo " << i.id << ": " << ((i.ValorTotal * 100.0) / valorTotalSomaTemp) << '%' << endl;
			Probabilidades.push_back(pair<int, float>(i.id, ((i.ValorTotal * 100.0) / valorTotalSomaTemp)));
		}
		if (pardone == 0)par.first = getIndividuoProbabilities(tempindividuosRef);
		else if (pardone == 1) 
		{ 
			par.second = getIndividuoProbabilities(tempindividuosRef); 
			pardone = -1; 

			paresIndividuos.push_back(par);
		}
		
		pardone++;
		cout << endl;
	}

	for (auto& p : paresIndividuos)
	{
		auto filhos = Reproduce(p);

		individuos.push_back(filhos.first);
		individuos.push_back(filhos.second);
	}
	
	logIndividuosReducedData(individuos);

	//GerarIndividuo_MenoresValores(items, valorMax, PesoMax);

	
	return;
}

individuo Mochila::getIndividuoProbabilities(vector<individuo>& tempIndividuos)
{
	auto tempProbabilidades = Probabilidades;
	sort(tempProbabilidades.begin(), tempProbabilidades.end(), MaiorPaMenor_Probs);

	random_device r;
	default_random_engine e1(r());
	uniform_real_distribution<> uniform_dist(0.0, 100.0);

	float value = uniform_dist(e1);

	pair<int, float>chosen; //fist = id || second = porcentage

	chosen.first = tempProbabilidades[0].first;
	chosen.second = tempProbabilidades[0].second;

	for (auto& p : tempProbabilidades)
	{
		if (value <= p.second)
		{
			chosen.first = p.first;
			chosen.second = p.second;
		}
	}
	//cout << "Valor gerado: " << value << endl;
	cout << "|||Individuo " << chosen.first << " com porcentagem " << chosen.second << " selecionado|||" << endl;

	int index = 0;
	for (auto& i : tempIndividuos)
	{

		if (i.id == chosen.first) 
		{
			auto save = i;
			tempIndividuos.erase(tempIndividuos.begin() + index);
			return save;
		}
		index++;
	}

}

pair<individuo, individuo> Mochila::Reproduce(pair<individuo, individuo> par)
{
	pair<individuo, individuo> filhos;

	random_device r;
	default_random_engine e1(r());
	uniform_int_distribution<> uniform_dist(1, TotalItems);

	int pontoCorte = uniform_dist(e1);

	individuo filho1;
	auto& filho1Ref = filho1;
	filho1Ref.Cromossomo = gerarCromossomo(par, pontoCorte, true);
	GerarEvolucao(filho1Ref, individuos.size(), geracoes.size() + 1, items);

	filhos.first = filho1;

	individuo filho2;
	auto& filho2Ref = filho2;
	filho2Ref.Cromossomo = gerarCromossomo(par, pontoCorte, false);
	GerarEvolucao(filho2Ref, individuos.size()+1, geracoes.size() + 1, items);

	filhos.second = filho2;



	return filhos;

}

vector<pair<int, bool>> Mochila::gerarCromossomo( pair<individuo, individuo> par, int pontoCorte,bool turn)
{
	vector <pair<int, bool>> cromossomo;
	individuo C1, C2;

	if (turn) { C1 = par.first; C2 = par.second; }
	else { C1 = par.second; C2 = par.first; }

	for (int i = pontoCorte - 1; i >= 0; i--) 
	{ 
		cromossomo.push_back(pair<int, bool>(C1.Cromossomo[i].first, C1.Cromossomo[i].second));
	}
	for (int i = pontoCorte; i < TotalItems; i++) 
	{ 
		cromossomo.push_back(pair<int, bool>(C2.Cromossomo[i].first, C2.Cromossomo[i].second));
	}

	sort(cromossomo.begin(), cromossomo.end(), MenorPaMaior_id_pair);

	return cromossomo;
}
