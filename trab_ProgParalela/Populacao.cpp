#include "Populacao.hpp"

bool MaiorPaMenor_Probs(pair<int, float> i, pair<int, float> j)
{
	return i.second > j.second;
}

bool MaiorPaMenor_ValorIndividuo(Individuo* i, Individuo* j)
{
	return i->valor > j->valor;
}

bool MenorPaMaior_id_individuo(Individuo* i, Individuo* j)
{
	return i->id < j->id;
}

void logData(int Value, string valueName, int linesBetween)
{
	cout << valueName << "  : | " << Value << " | ";
	for (int i = 0; i < linesBetween; i++) { cout << endl; }
}

void logData(string Value, string valueName, int linesBetween)
{
	cout << valueName << "  : | " << Value << " | ";
	for (int i = 0; i < linesBetween; i++) { cout << endl; }
}

void logIndividuosReducedData(vector <Individuo*> individuos)
{
	int geracao = 1;

	cout << "|| Geracao " << 1 << " ||" << endl << endl;

	for (auto& i : individuos)
	{
		if (i->geracao != geracao)
		{
			cout << "|| Geracao " << i->geracao << " ||" << endl << endl;
			geracao = i->geracao;
		}

		cout << "Individuo " << i->id << ": | ";

		cout << "   PesoTotal: " << i->peso;
		cout << "  |  ValorTotal: " << i->valor;

		cout << endl;
	}
}


Populacao::Populacao(int num_individuos, int media_filhos,int porcentagem_mutacao, float margem_erro)
{
	this->num_individuos = num_individuos;
	this->media_filhos = media_filhos;
	geracao = 1;
	valor_total_acomulado = 0;
	this->porcentagem_mutacao = porcentagem_mutacao;
	this->margem_erro = margem_erro;
	itens = new Itens;
}

void Populacao::GerarPopInicial(int chanceAcimadoPeso)
{
	random_device rd;
	auto random = default_random_engine{ rd() };
	uniform_int_distribution<> uniform_dist(1, 100);

	/*Individuo* indiv1 = new Individuo(1, geracao);
	indiv1->CreatePerfectCustoBene(0);
	pop.push_back(indiv1);

	Individuo* indiv2 = new Individuo(2, geracao);
	indiv2->CreatePerfectValor(0);
	pop.push_back(indiv2);
	*/
	for (int i = 0; i < num_individuos; i++)
	{
		Individuo* indiv = new Individuo(i + 1, geracao);

		if ((uniform_dist(random) <= chanceAcimadoPeso))indiv->CreateRandom(chanceAcimadoPeso);
		else indiv->CreateRandom(0);

		valor_total_acomulado += indiv->valor;
		pop.push_back(indiv);
	}

	sort(pop.begin(), pop.end(), MaiorPaMenor_ValorIndividuo);
}

bool Populacao::EvoluirPop(int iteracoes)
{
	for (int i = 0; i < iteracoes; i++)
	{
		vector<Individuo*> NewGeneration;

		auto paresIndividuos = FazerPares();

		for (auto& p : paresIndividuos)
		{
			auto filhos = Cruzar(p, media_filhos, pop.size() + NewGeneration.size(), geracao + 1);

			for (auto& f : filhos)
			{
				NewGeneration.push_back(f);
			}
		}
		CheckMutation(NewGeneration, porcentagem_mutacao);
		geracao++;

		bool stop = false;
		for (auto& NG : NewGeneration)
		{
			pop.push_back(NG);
			CriterioParada(NG, margem_erro);

			if (winner != NULL) stop = true;
		}

		if (stop)
		{
			OrderUpdatedIndividuos();

			logData(geracao - 1, "Iteracao: ", 0);
			logData(pop.size(), "Numero de individuos na Populacao: ", 0);
			logData(geracao, " Numero de geracoes: ", 1);

			cout << "\n****Individuo encontrado****" <<
				"\n|id| " << winner->id <<
				"\n|Geracao| : " << winner->geracao <<
				"\n|Peso| " << winner->peso <<
				"\n|Valor| : " << winner->valor <<
				endl << endl;

			logIndividuosReducedData(pop);
			
			return true;
		}
		else PexteBulbonica(num_individuos);

		logData(geracao - 1, "Iteracao: ", 0);
		logData(pop.size(), "Numero de individuos na Populacao: ", 0);
		logData(geracao, " Numero de geracoes: ", 1);
	}
	logIndividuosReducedData(pop);
	return false;
}

void Populacao::release()
{
	for (auto& p : pop)
	{
		p->release();
		delete p;
	}
}

vector<Individuo*> Populacao::getVector() { return pop; }

int Populacao::getGeracao(){ return geracao; }

vector<pair<Individuo*, Individuo*>> Populacao::FazerPares()
{
	vector<pair<Individuo*, Individuo*>> pares;
	pair<Individuo*, Individuo*> par;
	popTemp.clear();
	popTemp = pop;

	bool pardone = false;

	for (auto& p : popTemp)
	{
		//retornando probabilidades em um vetor com o id do individuo e sua probabilidade de ser escolhido em float
		//e passando esses dados para a funcao que vai selecionar o individuo baseado nessas prob
		//a funcao retorna um individuo
		if (!pardone)par.first = getIndividuoProbabilities(CalcProbabilidades());
		else
		{
			par.second = getIndividuoProbabilities(CalcProbabilidades());
			pares.push_back(par);
		}
		pardone = !pardone;
		//cout << endl;
	}

	return pares;
}

int Populacao::CalcValorTotal(vector<Individuo*> individuos)
{
	int soma = 0;

	for (auto& i : individuos)
	{
		soma += i->valor;
	}
	return soma;
}

vector<pair<int, float>> Populacao::CalcProbabilidades()
{
	vector <pair<int, float>> Probabilidades; //vetor com ([id do individuo],[probabilidade dele ser escolhido])
	auto valorTotalSomaTemp = CalcValorTotal(popTemp); //pegando soma total de todos os valores para divisao de probabilidades

	for (auto& i : popTemp)
	{
		//cout << fixed;
		//cout.precision(2);
		//cout << "- prob individuo " << i.id << ": " << ((i.ValorTotal * 100.0) / valorTotalSomaTemp) << '%' << endl;

		Probabilidades.push_back(pair<int, float>(i->id, ((i->valor * 100.0) / valorTotalSomaTemp)));
	}

	return Probabilidades;
}

Individuo* Populacao::getIndividuoProbabilities(vector<pair<int, float>> tempProbabilidades)
{
	//organiza probalidades do que tem mais chance para o que tem menos
	sort(tempProbabilidades.begin(), tempProbabilidades.end(), MaiorPaMenor_Probs);

	random_device r;
	default_random_engine e1(r());
	uniform_real_distribution<> uniform_dist(0.0, 100.0);

	//valor aleatorio para saber em qual probabilidade caiu
	float value = uniform_dist(e1);

	//individuo escolhido que comeca com o individuo com maior porcentagem
	pair<int, float>chosen; //fist = id || second = porcentage
	chosen.first = tempProbabilidades[0].first;
	chosen.second = tempProbabilidades[0].second;

	//iterando probabilidades e setando o escolhido de acordo com a porcentagem dele
	for (auto& p : tempProbabilidades)
	{
		if (value <= p.second)chosen = p;
	}
	//cout << "Valor gerado: " << value << endl;
	//cout << "|||Individuo " << chosen.first << " com porcentagem " << chosen.second << " selecionado|||" << endl;

	//iterando para achar o individuo selecionado e deletando ele do vetor temporario geral
	int index = 0;
	for (auto& i : popTemp)
	{
		if (i->id == chosen.first)
		{
			auto save = i;
			popTemp.erase(popTemp.begin() + index);
			return save;
		}
		index++;
	}
}

vector<Individuo*> Populacao::Cruzar(pair<Individuo*, Individuo*> par, int media_filhos, int numIndivids, int geracao)
{
	vector<Individuo* >filhos;

	random_device r;
	default_random_engine e1(r());
	uniform_int_distribution<> uniform_dist(1, itens->GetVector().size());//gerador de numero aleatorio de 1 a (total de itens)
	uniform_int_distribution<> uniform_dist2(1, 100);//gerador de numero aleatorio de 1 a 100

	vector<pair<int, int>>childChances;

	for (int i = 0; i < 5; i++)
	{
		float porcent;
		if (((i + 1) == media_filhos + 1) || ((i + 1) == media_filhos - 1))
		{
			porcent = 20;
		}
		else if ((i + 1) == media_filhos)
		{
			porcent = 40;
		}
		else
		{
			porcent = 10;
		}
		childChances.push_back(pair<int, float>(i + 1, porcent));
	}

	//baguncanco o vector para nunca cair os msm valores
	shuffle(childChances.begin(), childChances.end(), e1);

	int mediaFilhoChance = uniform_dist2(e1);//gerando numero para porcentagem

	for (auto& m : childChances)
	{
		if (mediaFilhoChance <= m.second)media_filhos = m.first;
	}
	bool turn = true;
	int pontoCorte = uniform_dist(e1);//gerando ponto de corte do cromossomo

	for (int i = 0; i < media_filhos; i++)
	{
		Individuo* filho = new Individuo(numIndivids + i + 1, geracao);
		filho->Create(0, pair<Cromossomo*, Cromossomo*>(par.first->cromossomo, par.second->cromossomo), pontoCorte, turn);

		filhos.push_back(filho);
		turn = !turn;
		if (turn) pontoCorte = uniform_dist(e1);
	}

	return filhos;
}

void Populacao::CheckMutation(vector<Individuo*> NewGeneration, int porcentagem_mutacao)
{
	default_random_engine e1(r());
	uniform_int_distribution<> uniform_dist(0, 100);

	for (auto& G : NewGeneration)
	{
		int value = uniform_dist(e1);
		if (value <= porcentagem_mutacao)
		{
			mutate(G);
			G->UpdateDados();
			return;
		}
	}
}

void Populacao::mutate(Individuo* i)
{
	default_random_engine e1(r());
	uniform_int_distribution<> uniform_dist(0, i->cromossomo->getGenes().size());

	int index = uniform_dist(e1);

	i->cromossomo->genes[index] = !i->cromossomo->genes[index];

}

void Populacao::CriterioParada(Individuo* indiv, int margem_erro)
{
	if (indiv->peso <= itens->pesoMax)
	{
		if (indiv->valor >= (itens->valorOtimo - ((itens->valorOtimo * margem_erro) / 100))
			&&
			indiv->valor <= (itens->valorOtimo + ((itens->valorOtimo * margem_erro) / 100)))
		{
			if (winner)delete winner;
			winner = new Individuo(indiv->id, indiv->geracao);
			winner->peso = indiv->peso;
			winner->valor = indiv->valor;
		}
	}
}

void Populacao::PexteBulbonica(int popMax)
{
	int fatEliminatorPorcentage = 10; //fazer paramentro disso????
	int twinEliminatorPorcentage = 10; //fazer paramentro disso????

	default_random_engine e1(r());

	sort(pop.begin(), pop.end(), MaiorPaMenor_ValorIndividuo);
	uniform_int_distribution<> uniform_dist(1, 100);

	for (int i = 0; i < pop.size(); i++)// deleta uma quantidade de individuos com valor repetido
	{
		int TwinKiller = uniform_dist(e1);
		if (valoresPesosUsados.find(pop[i]->valor) != valoresPesosUsados.end())
		{
			if (TwinKiller <= twinEliminatorPorcentage)
			{
				int amount = 0;
				for (auto& p : pop)
				{
					if (p->valor == pop[i]->valor)amount++;
				}
				if (amount > 1)
				{
					pop[i]->release();
					delete pop[i];
					pop.erase(pop.begin() + i);
					i = 0;
				}
			}
		}
	}

	for (int index = 0; index < pop.size(); index++) //deleta uma porcentagem(predefinida) de individuos acima do peso(individuos selecionados aleatoriamente)
	{
		int fatKiller = uniform_dist(e1);
		if (fatKiller <= fatEliminatorPorcentage)
		{
			if ((pop[index]->peso > itens->pesoMax))
			{
				pop[index]->release();
				delete pop[index];
				pop.erase(pop.begin() + index);//colocar pra deletar o ponteiro tbm
				index = 0;
			}

		}
	}

	

	OrderUpdatedIndividuos();

	for (int index = popMax; index < pop.size(); index++)
	{
		pop[index]->release();
		delete pop[index];
		pop.erase(pop.begin() + index);
		index--;
	}
}

void Populacao::OrderUpdatedIndividuos()
{
	sort(pop.begin(), pop.end(), MenorPaMaior_id_individuo);

	int index = 1;
	for (auto& i : pop)
	{
		i->id = index;
		index++;
	}
}