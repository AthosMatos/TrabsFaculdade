#pragma once
#include <algorithm> 
#include "HelperFuncs.h"
#include <random>

void stdIndividuoGeneratorPesoBased(vector<individuo>& individuos, vector <item> items, int pesoMax, int& valorTotalSomaRef)
{
	individuo Tempindividuo;
	Tempindividuo.id = individuos.size() + 1;
	int TempPeso = 0;
	int TempValor = 0;

	for (int i = 0; i < items.size(); i++)
	{
		if ((TempPeso + items[i].peso < pesoMax))
		{
			Tempindividuo.Cromossomo.push_back(pair<int, bool>(items[i].id, true));
			TempPeso += items[i].peso;
			TempValor += items[i].valor;
		}
		else
		{
			Tempindividuo.Cromossomo.push_back(pair<int, bool>(items[i].id, false));
		}
	}
	sort(Tempindividuo.Cromossomo.begin(), Tempindividuo.Cromossomo.end(), MenorPaMaior_id_pair);
	Tempindividuo.pesoTotal = TempPeso;
	Tempindividuo.ValorTotal = TempValor;
	valorTotalSomaRef += TempValor;

	individuos.push_back(Tempindividuo);
}
void stdIndividuoGeneratorPesoAndValorBased(vector<individuo>& individuos, vector <item> items, int pesoMax, int valorMax, int& valorTotalSomaRef)
{
	individuo Tempindividuo;
	Tempindividuo.id = individuos.size() + 1;
	int TempPeso = 0;
	int TempValor = 0;

	for (int i = 0; i < items.size(); i++)
	{
		if ((TempPeso + items[i].peso < pesoMax) && (TempValor + items[i].valor < valorMax))
		{
			Tempindividuo.Cromossomo.push_back(pair<int, bool>(items[i].id, true));
			TempPeso += items[i].peso;
			TempValor += items[i].valor;
		}
		else
		{
			Tempindividuo.Cromossomo.push_back(pair<int, bool>(items[i].id, false));
		}
	}
	
	sort(Tempindividuo.Cromossomo.begin(), Tempindividuo.Cromossomo.end(), MenorPaMaior_id_pair);
	Tempindividuo.pesoTotal = TempPeso;
	Tempindividuo.ValorTotal = TempValor;
	valorTotalSomaRef += TempValor;

	individuos.push_back(Tempindividuo);
}

void GerarEvolucao(individuo& evolucao,int numIndividuos, int geracao, vector <item> items) 
{
	evolucao.geracao = geracao;
	evolucao.id = numIndividuos + 1;
	int TempPeso = 0;
	int TempValor = 0;

	for (int i = 0; i < items.size(); i++)
	{
		if (evolucao.Cromossomo[i].second)
		{
			TempPeso += items[i].peso;
			TempValor += items[i].valor;
		}
	}
	
	evolucao.pesoTotal = TempPeso;
	evolucao.ValorTotal = TempValor;
}


thread GerarIndividuo_MenoresPesos(vector<individuo>& individuos, vector <item> items,int pesoMax,int valorMax, int& valorTotalSomaRef)
{
	sort(items.begin(), items.end(), MenorPaMaior_Peso);
	return thread(stdIndividuoGeneratorPesoAndValorBased, ref(individuos), items, pesoMax, valorMax, ref(valorTotalSomaRef));
}
thread GerarIndividuo_MenoresPesos(vector<individuo>& individuos, vector <item> items, int pesoMax, int& valorTotalSomaRef)
{
	sort(items.begin(), items.end(), MenorPaMaior_Peso);
	return thread(stdIndividuoGeneratorPesoBased, ref(individuos), items, pesoMax, ref(valorTotalSomaRef));
}

thread GerarIndividuo_MenoresValores(vector<individuo>& individuos, vector <item> items, int pesoMax, int valorMax, int& valorTotalSomaRef)
{
	sort(items.begin(), items.end(), MenorPaMaior_Valor);
	return thread(stdIndividuoGeneratorPesoAndValorBased, ref(individuos), items, pesoMax, valorMax, ref(valorTotalSomaRef));
}
thread GerarIndividuo_MenoresValores(vector<individuo>& individuos, vector <item> items, int pesoMax, int& valorTotalSomaRef)
{
	sort(items.begin(), items.end(), MenorPaMaior_Valor);
	return thread(stdIndividuoGeneratorPesoBased, ref(individuos), items, pesoMax, ref(valorTotalSomaRef));
}

//Mais peso por valor
thread GerarIndividuo_MelhorCustoBeneficioPeso(vector<individuo>& individuos, vector <item> items, int pesoMax, int& valorTotalSomaRef)
{
	sort(items.begin(), items.end(), MaiorPaMenor_CustoBeneficioPeso);
	return thread(stdIndividuoGeneratorPesoBased, ref(individuos), items, pesoMax, ref(valorTotalSomaRef));
}

//Mais valor por peso
thread GerarIndividuo_MelhorCustoBeneficioValor(vector<individuo>& individuos, vector <item> items, int pesoMax, int& valorTotalSomaRef)
{
	sort(items.begin(), items.end(), MaiorPaMenor_CustoBeneficioValor);
	return thread(stdIndividuoGeneratorPesoBased, ref(individuos), items, pesoMax, ref(valorTotalSomaRef));
}

thread GerarIndividuo_Ultra_Aleatorio(vector<individuo>& individuos, vector <item> items, int pesoMax, int& valorTotalSomaRef)
{
	random_device rd;
	auto random = default_random_engine{ rd() };
	shuffle(items.begin(), items.end(), random);

	return thread(stdIndividuoGeneratorPesoBased, ref(individuos), items, pesoMax, ref(valorTotalSomaRef));
}
