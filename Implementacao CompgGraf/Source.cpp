#include "CalcRotacao.hpp" 
#include "CalcEscala.hpp"
#include "CalcTranslacao.hpp"

int main()
{
	CalcRotacao* rotacao;
	CalcEscala* escala;
	CalcTranslacao* translacao;

	//rotacao = new CalcRotacao;
	//rotacao->PrintResult();

	//escala = new CalcEscala;
	//escala->PrintResult();
	
	translacao = new CalcTranslacao;
	translacao->PrintResult();

	return 0;
}