#include "GodController.hpp"

using namespace std;

int main()
{
    /* clock_t clock(void) returns the number of clock ticks
       elapsed since the program was launched.To get the number
       of seconds used by the CPU, you will need to divide by
       CLOCKS_PER_SEC.where CLOCKS_PER_SEC is 1000000 on typical
       32 bit system.  */
    clock_t start, end;

    /* Recording the starting clock tick.*/
    start = clock();

    Itens* itens = new Itens();
    itens->SetItens("test2");

    GodController* god = new GodController;
    god->GerarPopulacao();
    god->EvoluirPopulacao(10);

    // Recording the end clock tick.
    end = clock();

    // Calculating total time taken by the program.
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by program is : " << fixed
        << time_taken << setprecision(5);
    cout << " sec " << endl;

	free(god);

	return 0;
}