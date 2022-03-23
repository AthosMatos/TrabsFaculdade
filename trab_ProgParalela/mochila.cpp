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
	mutationPorcentage = 5; //5% de chaance de mutacao
	maxPopulataion = 100;
	//tamanho populacao
	//altera mutacao pegando todos os individuos colocar pra pegar apenas novas geracoes

	individuo OptimalIndividuo;
	auto& OptimalIndividuoRef = OptimalIndividuo;
	auto& valorMaxRef = this->valorMax;
	auto& PesoMaxRef = this->PesoMax;
	auto& individuosRef = this->individuos;
	auto& valorTotalSomaRef = this->valorTotalSoma;
	auto& TotalItemsRef = this->TotalItems;

	items = FiletoItems("test3", valorMaxRef, PesoMaxRef, TotalItemsRef, OptimalIndividuoRef);

	valorIdeal = OptimalIndividuo.ValorTotal;

	logIndividuoReducedData(OptimalIndividuo);

	logData(PesoMax, "\nPesoMax",2);
	//logItems(items);

	GerarIndividuo_MenoresPesos(individuosRef,items, PesoMax, valorTotalSomaRef);
	GerarIndividuo_MenoresValores(individuosRef, items, PesoMax, valorTotalSomaRef);
	GerarIndividuo_MelhorCustoBeneficioPeso(individuosRef, items, PesoMax, valorTotalSomaRef);
	GerarIndividuo_MelhorCustoBeneficioValor(individuosRef, items, PesoMax, valorTotalSomaRef);
	GerarIndividuo_Ultra_Aleatorio(individuosRef, items, PesoMax, valorTotalSomaRef);
	GerarIndividuo_Ultra_Aleatorio(individuosRef, items, PesoMax, valorTotalSomaRef);

	//sort(individuos.begin(), individuos.end(), MaiorPaMenor_ValorIndividuo);
	//logIndividuosReducedData(individuos);

	geracoes.push_back(individuos);

	//logData(valorTotalSoma, "valorTotalSoma", 2);

	Evolve(10);
	
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
	//cout << "|||Individuo " << chosen.first << " com porcentagem " << chosen.second << " selecionado|||" << endl;

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

void Mochila::CheckMutation()
{
	random_device r;
	default_random_engine e1(r());
	uniform_int_distribution<> uniform_dist(0, 100);

	for (auto& i : individuos)
	{
		int value = uniform_dist(e1);
		if (value <= mutationPorcentage)
		{
			mutate(i);
		}
	}

}

void Mochila::mutate(individuo& i)
{
	random_device r;
	default_random_engine e1(r());
	uniform_int_distribution<> uniform_dist(0, i.Cromossomo.size() - 1);

	int index = uniform_dist(e1);

	i.Cromossomo[index].second = !i.Cromossomo[index].second;
	
}

void Mochila::Evolve(int iterations)
{
	for (int i = 0; i < iterations; i++)
	{
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
				//cout << "- prob individuo " << i.id << ": " << ((i.ValorTotal * 100.0) / valorTotalSomaTemp) << '%' << endl;

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
			//cout << endl;
		}

		vector<individuo> NewGeneration;

		for (auto& p : paresIndividuos)
		{
			auto filhos = Reproduce(p);

			individuos.push_back(filhos.first);
			individuos.push_back(filhos.second);

			NewGeneration.push_back(filhos.first);
			NewGeneration.push_back(filhos.second);

			if (CriterioParada(filhos.first, filhos.second))
			{
				logIndividuosReducedData(individuos);
				return;
			}
				
		}

		CheckMutation();

		PexteBulbonica();

		geracoes.push_back(NewGeneration);
	}

	
}

void Mochila::PexteBulbonica()
{
	sort(individuos.begin(), individuos.end(), MaiorPaMenor_ValorIndividuo);

	for (int index = 0;index< individuos.size();index++)
	{
		if (index >= (individuos.size() / 4))
		{
			if ((individuos[index].pesoTotal > PesoMax))
			{
				individuos.erase(individuos.begin() + index);
				index -= 1;
				continue;
			}
		}

		if (index > maxPopulataion)
		{
			individuos.erase(individuos.begin() + index);
			index -= 1;
			continue;
		}
		
	}

	sort(individuos.begin(), individuos.end(), MenorPaMaior_id_individuo);

	int index = 1;
	for (auto& i : individuos)
	{
		i.id = index;
		index++;
	}


	return;
}

bool Mochila::CriterioParada(individuo i1, individuo i2)
{
	const float margemErr = 0.2; //porcento

	if (i1.pesoTotal <= PesoMax && i2.pesoTotal <= PesoMax)
	{
		if (i1.ValorTotal >= (valorIdeal - ((valorIdeal * margemErr) / 100))
			&&
			i1.ValorTotal <= (valorIdeal + ((valorIdeal * margemErr) / 100)))
		{
			cout << "Individuo " << i1.id << " de peso " << i1.pesoTotal << " Aproximdo valor : " << i1.ValorTotal << endl;
			return true;
		}
		else if (i2.ValorTotal >= (valorIdeal - ((valorIdeal * margemErr) / 100))
			&&
			i2.ValorTotal <= (valorIdeal + ((valorIdeal * margemErr) / 100)))
		{
			cout << "Individuo " << i2.id << " de peso " << i2.pesoTotal << " Aproximdo valor : " << i2.ValorTotal << endl;
			return true;
		}
	}

	return false;
}
