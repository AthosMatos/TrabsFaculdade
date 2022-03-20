#pragma once
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "structs.h"

vector <item> FiletoItems(string file, int& valorMax, int& PesoMax, int& TotalItemsRef,individuo& OptimalIndividuo)
{

    vector <item> items;
    ifstream indata;
    int num;
    indata.open(file);

    if (!indata) {
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }

    // cerr << "file opened" << endl;

    indata >> num;
    int NumItems = num;
    TotalItemsRef = NumItems;

    indata >> num;
    PesoMax = num;

    for (int i = 0; i < NumItems; i++)
    {
        if (indata.eof()) break;

        item tempItem;

        indata >> num;
        tempItem.id = i + 1;
        tempItem.valor = num;
        indata >> num;
        tempItem.peso = num;
        items.push_back(tempItem);
    }

    int TempPeso = 0;
    int TempValor = 0;

    int i = 0;

    while (!indata.eof())
    {
        indata >> num;
        if (num)
        {
            OptimalIndividuo.Cromossomo.push_back(pair<int, bool>(i + 1, true));
        
            TempPeso += items[i].peso;
            TempValor += items[i].valor;
        }
        else
        {
            OptimalIndividuo.Cromossomo.push_back(pair<int, bool>(i + 1, false));
        }

        i++;
    }

    OptimalIndividuo.pesoTotal = TempPeso;
    OptimalIndividuo.ValorTotal = TempValor;


    indata.close();
    //cout << "End-of-file reached.." << endl;

    return items;
}

///REDO WITH NEWER FUNCS
vector <item> CreateItems(int numero_de_items, int PesoMax, int valorMax)
{
    vector <item> items;

    for (int i = 0; i < numero_de_items; i++)
    {
        item tempItem;
        tempItem.id = i + 1;
        tempItem.peso = rand() % PesoMax + 1;
        tempItem.valor = rand() % valorMax + 1;

        items.push_back(tempItem);
    }
    return items;
}