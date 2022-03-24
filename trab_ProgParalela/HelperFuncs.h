#pragma once
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "structs.h"

using namespace std;

bool MaiorPaMenor_CustoBeneficioPeso(item i, item j)
{
    return (i.peso / i.valor) > (j.peso / j.valor);
}

bool MaiorPaMenor_CustoBeneficioValor(item i, item j)
{
    return (i.valor / i.peso) > (j.valor / j.peso);
}

bool MenorPaMaior_Peso(item i, item j)
{
    return i.peso < j.peso;
}

bool MenorPaMaior_Valor(item i, item j)
{
    return i.valor < j.valor;
}

bool MaiorPaMenor_ValorIndividuo(individuo i, individuo j)
{
    return i.ValorTotal > j.ValorTotal;
}

bool MenorPaMaior_id_individuo(individuo i, individuo j)
{
    return i.id < j.id;
}


bool MaiorPaMenor_Probs(pair<int, float> i, pair<int, float> j)
{
    return i.second > j.second;
}

bool MenorPaMaior_id(item i, item j)
{
    return i.id < j.id;
}

bool MenorPaMaior_id_pair(pair<int, bool> i, pair<int, bool> j)
{
    return i.first < j.first;
}


int CalcValorTotal(vector<individuo>individuos)
{
    int soma = 0;

    for (auto& i : individuos)
    {
        soma += i.ValorTotal;
    }
    return soma;
}


void logIndividuos(vector <individuo> individuos)
{
    int geracao = 1;

    cout << "|| Geracao " << 1 << " ||" << endl << endl;

    for (auto& i : individuos)
    {
        if (i.geracao != geracao)
        {
            cout << "|| Geracao " << i.geracao << " ||" << endl << endl;
            geracao = i.geracao;
        }

        cout << "Individuo " << i.id << ": | ";

        auto& TempItems = i.Cromossomo;

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

void logIndividuosReducedData(vector <individuo> individuos)
{
    int geracao = 1;

    cout << "|| Geracao " << 1 << " ||" << endl << endl;

    for (auto& i : individuos)
    {
        if (i.geracao != geracao)
        {
            cout << "|| Geracao " << i.geracao << " ||" << endl << endl;
            geracao = i.geracao;
        }
   
        cout << "Individuo " << i.id << ": | ";

        cout << "   PesoTotal: " << i.pesoTotal;
        cout << "  |  ValorTotal: " << i.ValorTotal;

        cout << endl;
    }
}

void logIndividuoReducedData(individuo i)
{
    cout << "|| Geracao " << i.geracao << " ||" << endl << endl;

    cout << "Individuo " << i.id << ": | ";

    cout << "   PesoTotal: " << i.pesoTotal;
    cout << "  |  ValorTotal: " << i.ValorTotal;

    cout << endl;
    
}

void logItems(vector <item> items)
{
    sort(items.begin(), items.end(), MenorPaMaior_id);

    for (auto& i : items)
    {
        cout << "||| item " << i.id << " |||";
        cout << endl << endl << "peso  : | " << i.peso << " | ";
        cout << endl<< "valor : | " << i.valor << " | " << endl << endl;

    }
    cout << endl << endl;
}

void logItemsUnsorted(vector <item> items)
{
    for (auto& i : items)
    {
        cout << "||| item " << i.id << " |||";
        cout << endl << endl << "peso  : | " << i.peso << " | ";
        cout << endl << "valor : | " << i.valor << " | " << endl << endl;

    }
    cout << endl << endl;
}

void logData(int valorMax, int PesoMax)
{
    cout << "valorMax  : | " << valorMax << " | ";
    cout << endl << "PesoMax : | " << PesoMax << " | " << endl << endl;
}

void logData(int Value, string valueName,int linesBetween)
{
    cout << valueName << "  : | " << Value << " | ";
        
    for (int i = 0; i < linesBetween; i++) { cout << endl; }
        
}

void logData(string Value, string valueName, int linesBetween)
{
    cout << valueName << "  : | " << Value << " | ";

    for (int i = 0; i < linesBetween; i++) { cout << endl; }

}