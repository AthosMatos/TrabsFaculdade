#include "PopController.hpp"

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

PopController::PopController()
{
	itens = new Itens;
}

vector<pair<Individuo*, Individuo*>> PopController::FazerPares(vector<Individuo*> poptemp)
{
	vector<pair<Individuo*, Individuo*>> pares;
	pair<Individuo*, Individuo*> par;
	popTemp = poptemp;

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

int PopController::CalcValorTotal(vector<Individuo*> individuos)
{
	int soma = 0;

	for (auto& i : individuos)
	{
		soma += i->valor;
	}
	return soma;
}

vector<pair<int, float>> PopController::CalcProbabilidades()
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

Individuo* PopController::getIndividuoProbabilities(vector<pair<int, float>> tempProbabilidades)
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

vector<Individuo*> PopController::Cruzar(pair<Individuo*, Individuo*> par, int media_filhos, int numIndivids, int geracao)
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
		Individuo* filho = new Individuo(numIndivids + i + 1, geracao + 1);
		filho->Create(0, pair<Cromossomo*, Cromossomo*>(par.first->cromossomo, par.second->cromossomo), pontoCorte, turn);

		filhos.push_back(filho);
		turn = !turn;
		if (turn) pontoCorte = uniform_dist(e1);
	}

	return filhos;
}

void PopController::CheckMutation(vector<Individuo*> NewGeneration,int porcentagem_mutacao)
{
	default_random_engine e1(r());
	uniform_int_distribution<> uniform_dist(0, 100);

	for (auto& G : NewGeneration)
	{
		int value = uniform_dist(e1);
		if (value <= porcentagem_mutacao)
		{
			mutate(G);
			return;
		}
	}
}

void PopController::mutate(Individuo* i)
{
	default_random_engine e1(r());
	uniform_int_distribution<> uniform_dist(0, i->cromossomo->getGenes().size());

	int index = uniform_dist(e1);

	i->cromossomo->genes[index] = !i->cromossomo->genes[index];

}

Individuo* PopController::CriterioParada(Individuo* indiv, int margem_erro)
{
	Individuo* Winner;

	if (indiv->peso <= itens->pesoMax)
	{
		if (indiv->valor >= (itens->valorOtimo - ((itens->valorOtimo * margem_erro) / 100))
			&&
			indiv->valor <= (itens->valorOtimo + ((itens->valorOtimo * margem_erro) / 100)))
		{
			Winner = new Individuo(indiv->id, indiv->geracao);
			Winner->peso = indiv->peso;
			Winner->valor = indiv->valor;
			
			return Winner;
		}
	}

	return NULL;
}

vector<Individuo*> PopController::PexteBulbonica(vector<Individuo*> pop, int popMax)
{
	sort(pop.begin(), pop.end(), MaiorPaMenor_ValorIndividuo);

	for (int index = pop.size() * 0.75; index < pop.size(); index++)
	{
		if ((pop[index]->peso > itens->pesoMax))
		{
			pop.erase(pop.begin() + index);//colocar pra deletar o ponteiro tbm
			index--;
		}
	}

	pop = OrderUpdatedIndividuos(pop);

	for (int index = popMax; index < pop.size(); index++)
	{
		pop.erase(pop.begin() + index);
		index--;
	}

	return pop;
}

vector<Individuo*> PopController::OrderUpdatedIndividuos(vector<Individuo*> pop)
{
	sort(pop.begin(), pop.end(), MenorPaMaior_id_individuo);

	int index = 1;
	for (auto& i : pop)
	{
		i->id = index;
		index++;
	}

	return pop;
}