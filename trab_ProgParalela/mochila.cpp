#include "mochila.h"
#include "GeradorPopulacaoFuncs.h"
#include "HelperFuncs.h"
#include "itemFuncs.h"

Mochila::Mochila()
{
	margemErr = 0.2; //porcento
	mutationPorcentage = 5; //5% de chaance de mutacao
	maxPopulataion = 100; //tamanho populacao 
	iteracoes = 50;

	individuo OptimalIndividuo;
	auto& OptimalIndividuoRef = OptimalIndividuo;
	auto& valorMaxRef = this->valorMax;
	auto& PesoMaxRef = this->PesoMax;

	auto& individuosRef = individuos;
	auto& valorTotalSomaRef = this->valorTotalSoma;
	auto& TotalItemsRef = this->TotalItems;

	items = FiletoItems("test3", valorMaxRef, PesoMaxRef, TotalItemsRef, OptimalIndividuoRef);

	valorIdeal = OptimalIndividuo.ValorTotal;

	//logIndividuoReducedData(OptimalIndividuo);

	logData(PesoMax, "Peso Maximo suportado pela mochila", 1);
	logData(OptimalIndividuo.ValorTotal, "Valor Otimo", 1);
	logData(maxPopulataion, "Limite de individuos", 1);
	logData(iteracoes, "Limite de iteracoes", 1);
	auto me = to_string(margemErr);
	for (int i = me.length(); i > 3; i--){ me.erase(me.begin() + i); }
	logData(to_string(mutationPorcentage) + '%', "Chance de mutacao", 1);
	logData(me + '%', "Margem de erro para resultado", 2);

	//logItems(items);
	
	for (int i = 0; i < 6; i++) { threads.push_back(thread(&Mochila::GerarIndivididuo, this, i + 1, ref(individuosRef), ref(valorTotalSomaRef))); }
	for (auto& t : threads) { t.join(); }


	//logIndividuosReducedData(individuos);



	geracoes++;;

	//logData(valorTotalSoma, "valorTotalSoma", 2);

	if (!Evolve(iteracoes)) cout << "\nIndividuo com valor otimo nao encontrado! Tente aumentar a margem de erro ou o numero de iteracoes" << endl;

	return;
}

individuo Mochila::getIndividuoProbabilities(vector<individuo>& tempIndividuos, vector <pair<int, float>> tempProbabilidades)
{
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
	GerarEvolucao(filho1Ref, individuos.size(), geracoes + 1, items);

	filhos.first = filho1;

	individuo filho2;
	auto& filho2Ref = filho2;
	filho2Ref.Cromossomo = gerarCromossomo(par, pontoCorte, false);
	GerarEvolucao(filho2Ref, individuos.size()+1, geracoes + 1, items);

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

void Mochila::CheckMutation(vector<individuo>& generations)
{
	random_device r;
	default_random_engine e1(r());
	uniform_int_distribution<> uniform_dist(0, 100);

	for (auto& G : generations)
	{
		int value = uniform_dist(e1);
		if (value <= mutationPorcentage)
		{
			mutate(G);
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

bool Mochila::Evolve(int iterations)
{
	pair<individuo, individuo> par;
	vector<pair<individuo, individuo>> paresIndividuos;
	vector <pair<int, float>> Probabilidades;

	for (int i = 0, pardone = 0, valorTotalSomaTemp; i < iterations; i++)
	{
		paresIndividuos.clear();
		
		auto tempindividuos = individuos;
		auto& tempindividuosRef = tempindividuos;

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
			if (pardone == 0)par.first = getIndividuoProbabilities(tempindividuosRef, Probabilidades);
			else if (pardone == 1)
			{
				par.second = getIndividuoProbabilities(tempindividuosRef, Probabilidades);
				pardone = -1;

				paresIndividuos.push_back(par);
			}
			pardone++;
			//cout << endl;
		}

		vector<individuo> NewGeneration;
		auto& NewGenerationRef = NewGeneration;

		for (auto& p : paresIndividuos)
		{
			auto filhos = Reproduce(p);

			NewGeneration.push_back(filhos.first);
			NewGeneration.push_back(filhos.second);		
		}

		CheckMutation(NewGenerationRef);
		geracoes++;

		bool stop = false;
		for (auto& NG : NewGeneration)
		{ 
			individuos.push_back(NG); 

			if (CriterioParada(NG)) stop = true;
		}

		if (stop)
		{
			OrderUpdatedIndividuos();

			logData(geracoes - 1, "Iteracao: ", 0);
			logData(individuos.size(), "Numero de individuos na Populacao: ", 0);
			logData(geracoes, " Numero de geracoes: ", 1);

			cout << "\n****Individuo encontrado****"<<
				"\n|id| " << individuoWinner.id << 
				"\n|Geracao| : " << individuoWinner.geracao <<
				"\n|Peso| " << individuoWinner.pesoTotal << 
				"\n|Valor| : " << individuoWinner.ValorTotal << 
				endl << endl;

			logIndividuosReducedData(individuos);

			return true;
		}	
		else PexteBulbonica();	

		logData(geracoes - 1, "Iteracao: ", 0);
		logData(individuos.size(), "Numero de individuos na Populacao: ", 0);
		logData(geracoes, " Numero de geracoes: ", 1);
	}

	return false;
	
}

void Mochila::OrderUpdatedIndividuos()
{
	sort(individuos.begin(), individuos.end(), MenorPaMaior_id_individuo);

	int index = 1;
	for (auto& i : individuos)
	{
		i.id = index;
		index++;
	}
}

void Mochila::PexteBulbonica()
{
	sort(individuos.begin(), individuos.end(), MaiorPaMenor_ValorIndividuo);

	for (int index = 0;index < individuos.size();index++)
	{
		if (index >= (individuos.size() / 4))
		{
			if ((individuos[index].pesoTotal > PesoMax))
			{
				individuos.erase(individuos.begin() + index);
				index--;
			}
		}
	}

	OrderUpdatedIndividuos();

	for (int index = maxPopulataion; index < individuos.size(); index++)
	{
		individuos.erase(individuos.begin() + index);
		index--;
	}
}

bool Mochila::CriterioParada(individuo indiv)
{
	if (indiv.pesoTotal <= PesoMax)
	{
		if (indiv.ValorTotal >= (valorIdeal - ((valorIdeal * margemErr) / 100))
			&&
			indiv.ValorTotal <= (valorIdeal + ((valorIdeal * margemErr) / 100)))
		{
			individuoWinner.id = indiv.id;
			individuoWinner.pesoTotal = indiv.pesoTotal;
			individuoWinner.ValorTotal = indiv.ValorTotal;
			individuoWinner.geracao = indiv.geracao;

			return true;
		}
	}

	return false;
}

void Mochila::GerarIndivididuo(int type, vector<individuo>& individuosRef, int& valorTotalSomaRef)
{
	switch (type)
	{
		case 1:
		{
			GerarIndividuo_MenoresPesos(individuosRef, items, PesoMax, valorTotalSomaRef);
			return;
		}
		case 2:
		{
			GerarIndividuo_MenoresValores(individuosRef, items, PesoMax, valorTotalSomaRef);
			return;
		}
		case 3:
		{
			GerarIndividuo_MelhorCustoBeneficioPeso(individuosRef, items, PesoMax, valorTotalSomaRef);
			return;
		}
		case 4:
		{
			GerarIndividuo_MelhorCustoBeneficioValor(individuosRef, items, PesoMax, valorTotalSomaRef);
			return;
		}
		case 5:
		{
			GerarIndividuo_Ultra_Aleatorio(individuosRef, items, PesoMax, valorTotalSomaRef);
			return;
		}
		case 6:
		{
			GerarIndividuo_Ultra_Aleatorio(individuosRef, items, PesoMax, valorTotalSomaRef);
			return;
		}	
	}
}

