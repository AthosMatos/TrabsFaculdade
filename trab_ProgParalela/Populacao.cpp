#include "Populacao.hpp"

Populacao::Populacao(int num_individuos, int media_filhos,int porcentagem_mutacao, float margem_erro)
{
	this->num_individuos = num_individuos;
	this->media_filhos = media_filhos;
	geracao = 1;
	valor_total_acomulado = 0;
	this->porcentagem_mutacao = porcentagem_mutacao;
	this->margem_erro = margem_erro;
}

void Populacao::GerarPopInicial(int chanceAcimadoPeso)
{
	random_device rd;
	auto random = default_random_engine{ rd() };
	uniform_int_distribution<> uniform_dist(1, 100);

	for (int i = 0; i < num_individuos; i++)
	{
		Individuo* indiv = new Individuo(i + 1, geracao);

		if ((uniform_dist(random) <= chanceAcimadoPeso))indiv->CreateRandom(chanceAcimadoPeso);
		else indiv->CreateRandom(0);

		valor_total_acomulado += indiv->valor;
		pop.push_back(indiv);
	}
}

bool Populacao::EvoluirPop(int iteracoes)
{
	for (int i = 0; i < iteracoes; i++)
	{
		auto paresIndividuos = FazerPares(pop);

		for (auto& p : paresIndividuos)
		{
			auto filhos = Cruzar(p, media_filhos, pop.size() + NewGeneration.size(), geracao);

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
			winner = CriterioParada(NG, margem_erro);

			if (winner != NULL) stop = true;
		}

		if (stop)
		{
			/*/OrderUpdatedIndividuos();

			logData(geracoes - 1, "Iteracao: ", 0);
			logData(individuos.size(), "Numero de individuos na Populacao: ", 0);
			logData(geracoes, " Numero de geracoes: ", 1);

			cout << "\n****Individuo encontrado****" <<
				"\n|id| " << individuoWinner.id <<
				"\n|Geracao| : " << individuoWinner.geracao <<
				"\n|Peso| " << individuoWinner.pesoTotal <<
				"\n|Valor| : " << individuoWinner.ValorTotal <<
				endl << endl;

			logIndividuosReducedData(individuos);
			*/
			return true;
		}
		else pop = PexteBulbonica(pop, num_individuos);

		//logData(geracoes - 1, "Iteracao: ", 0);
		//logData(individuos.size(), "Numero de individuos na Populacao: ", 0);
		//logData(geracoes, " Numero de geracoes: ", 1);
		

	}
	//logIndividuosReducedData(individuos);
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

