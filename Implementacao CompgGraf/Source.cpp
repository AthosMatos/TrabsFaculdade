#include "CalcRotacao.hpp" 
#include "CalcEscala.hpp"
#include "CalcTranslacao.hpp"
#include "CalcCamera.h"
#include "CalcInterseccao.h"
#include "CalcLuz.h"

int main()
{
	CalcRotacao* rotacao;
	CalcEscala* escala;
	CalcTranslacao* translacao;
	CalcCamera* camera;
	CalcInterseccao* interseccao;
	CalcLuz* luz;

	//Descomentar a implementacao desejada para o codigo rodar certo

	//luz = new CalcLuz;
	//interseccao = new CalcInterseccao;
	//camera = new CalcCamera;
	rotacao = new CalcRotacao;
	//escala = new CalcEscala;
	//translacao = new CalcTranslacao;
	

	return 0;
}