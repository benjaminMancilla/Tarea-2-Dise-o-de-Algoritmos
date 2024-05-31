
#include "grafo.h"
#include "experimento.h"
#include "dijktraMinHeap.h"
#include "dijktraFibHeap.h"

int main() {
    // Generar el grafo
    Grafo grafo = generarGrafo(5, 7);

    // Imprimir el grafo en un archivo de texto
    imprimirGrafo(grafo, "grafo.txt");

    // Ejecutar el algoritmo de Dijkstra
    pair<vector<int>, vector<double>> resultado = dijkstraMinHeap(grafo);
    vector<int> previos = resultado.first;
    vector<double> distancias = resultado.second;

    // Imprimir las distancias mínimas
    for (int i = 0; i < distancias.size(); i++) {
        cout << "Distancia mínima de 0 a " << i << ": " << distancias[i] << endl;
    }

    // Imprimir los nodos previos
    for (int i = 0; i < previos.size(); i++) {
        cout << "Nodo previo de " << i << ": " << previos[i] << endl;
    }

    return 0;
}