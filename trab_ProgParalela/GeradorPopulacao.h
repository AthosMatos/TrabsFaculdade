#pragma once
#include "structs.h"
#include <algorithm> 

vector <individuo> individuos;

bool MenorPaMaior_Peso(item i, item j)
{
	return i.peso < j.peso;
}

bool MenorPaMaior_Valor(item i, item j)
{
	return i.valor < j.valor;
}

bool MenorPaMaior_id(item i, item j)
{
	return i.id < j.id;
}

bool MenorPaMaior_id_pair(pair<int, bool> i, pair<int, bool> j)
{
	return i.first < j.first;
}

void logIndividuos()
{
	for (auto& i : individuos)
	{
		cout << "Individuo " << i.id << ": | ";

		auto& TempItems = i.items_Id_isActive;

		sort(TempItems.begin(), TempItems.end(), MenorPaMaior_id_pair);

		for (auto& ti : TempItems)
		{
			if (ti.second)cout << 1;
			else cout << 0;

			cout << " | ";
		}

		cout << "   PesoTotal: " << i.pesoTotal;
		cout << "  |  ValorTotal: " << i.ValorTotal;

		cout << endl;
	}
}

void logItems(vector <item> items)
{
	sort(items.begin(), items.end(), MenorPaMaior_id);

	cout << "item  : | ";
	for (auto& i : items)
	{
		cout << i.id << " | ";
	}
	cout << endl << "peso  : | ";
	for (auto& i : items)
	{
		cout << i.peso << " | ";
	}
	cout << endl << "valor : | ";
	for (auto& i : items)
	{
		cout << i.valor << " | ";
	}

	cout << endl << endl;
}

void GerarIndividuo_MenoresPesos(vector <item> items,int maxPeso,int valorMax)
{
	sort(items.begin(), items.end(), MenorPaMaior_Peso);

	//logItems(items);

	individuo Tempindividuo;
	Tempindividuo.id = individuos.size() + 1;
	int TempPeso = 0;
	int TempValor = 0;

	for (int i = 0; i < items.size(); i++)
	{
		if ((TempPeso + items[i].peso < maxPeso) && (TempValor + items[i].valor < valorMax))
		{
			Tempindividuo.items_Id_isActive.push_back(pair<int, bool>(items[i].id, true));
			TempPeso += items[i].peso;
			TempValor += items[i].valor;
		}
		else
		{
			Tempindividuo.items_Id_isActive.push_back(pair<int, bool>(items[i].id, false));
		}		
	}
	Tempindividuo.pesoTotal = TempPeso;
	Tempindividuo.ValorTotal = TempValor;

	individuos.push_back(Tempindividuo);

	//logIndividuos();
	
}

void GerarIndividuo_MenoresValores(vector <item> items, int maxPeso, int valorMax)
{
	sort(items.begin(), items.end(), MenorPaMaior_Valor);

	//logItems(items);

	individuo Tempindividuo;
	Tempindividuo.id = individuos.size() + 1;
	int TempPeso = 0;
	int TempValor = 0;

	for (int i = 0; i < items.size(); i++)
	{
		if ((TempPeso + items[i].peso < maxPeso) && (TempValor + items[i].valor < valorMax))
		{
			Tempindividuo.items_Id_isActive.push_back(pair<int, bool>(items[i].id, true));
			TempPeso += items[i].peso;
			TempValor += items[i].valor;
		}
		else
		{
			Tempindividuo.items_Id_isActive.push_back(pair<int, bool>(items[i].id, false));
		}
	}
	Tempindividuo.pesoTotal = TempPeso;
	Tempindividuo.ValorTotal = TempValor;

	individuos.push_back(Tempindividuo);

	//logIndividuos();
}

void GerarIndividuo_MelhorCustoBeneficio(vector <item> items)
{

}

void GerarIndividuo_Aleatorio(vector <item> items)
{

}