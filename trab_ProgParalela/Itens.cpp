#include "Itens.hpp"

vector<Item*> Itens::itens;
int Itens::pesoMax = 0;
int Itens::valorOtimo = 0;
int Itens::PesoOtimo = 0;

void Itens::SetItens(string filename)
{
    ifstream indata;
    int num;
    indata.open(filename);

    if (!indata) {
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }

    // cerr << "file opened" << endl;

    indata >> num;
    int NumItems = num;
    NumItems = NumItems;

    indata >> num;
    pesoMax = num;

    for (int i = 0; i < NumItems; i++)
    {
        if (indata.eof()) break;

        Item* item = new Item();

        indata >> num;
        item->id = i + 1;
        item->valor = num;
        indata >> num;
        item->peso = num;
        itens.push_back(item); //id no map e no item para ficar mais facil de achar qnd pesquisando
    }
    int TempPeso = 0, TempValor = 0;

    for (int i = 0; !indata.eof(); i++)
    {
        indata >> num;
        if (num)
        {
            TempPeso += itens[i]->peso;
            TempValor += itens[i]->valor;
        }    
    }
    PesoOtimo = TempPeso;
    valorOtimo = TempValor;

    indata.close();
    //cout << "End-of-file reached.." << endl;
}

vector<Item*> Itens::GetVector(){ return itens; }

void Itens::release()
{
    for (auto& m : itens)
    {
        delete m;
    }
}
