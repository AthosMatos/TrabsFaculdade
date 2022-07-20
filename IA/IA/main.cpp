#include <iostream>
#include "grafo.hpp"

using namespace std;

int main()
{
	Grafo grafo;

	grafo.add(8);

	grafo.connect("A", "B", 10);
	grafo.connect("A", "G", 5);
	grafo.connect("B", "C", 4);
	grafo.connect("B", "H", 8);
	grafo.connect("H", "D", 20);
	grafo.connect("D", "E", 10);
	grafo.connect("E", "F", 6);
	grafo.connect("F", "C", 9);
	grafo.UCS("A", "E");


	return 0;
}