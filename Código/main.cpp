
#include "grafo.h"
#include "experimento.h"
#include "dijktraMinHeap.h"
#include "dijktraFibHeap.h"

void testGenerarGrafo(){
    Grafo grafo = generarGrafo(5, 10);

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
}

void testConocido() {

    Grafo grafo(4);
    grafo.agregarArista(0, 1, 1.0);
    grafo.agregarArista(1, 2, 2.0); 
    grafo.agregarArista(2, 3, 3.0);
    grafo.agregarArista(3, 0, 4.0); 

    vector<int> distanciasConocidas = {0, 1, 3, 4}; 
    vector<int> previosConocidos = {-1, 0, 1, 0}; 

    auto [previos, distancias] = dijkstraFibHeap(grafo);

    cout << "Los resultados de los nodos:\n";
    for (int i = 0; i < previos.size(); ++i) {
        cout << "Nodo " << i << ": " << previos[i] << " (esperado: " << previosConocidos[i] << ")\n";
    }

    cout << "Los resultados de las distancias:\n";
    for (int i = 0; i < distancias.size(); ++i) {
        cout << "Nodo " << i << ": " << distancias[i] << " (esperado: " << distanciasConocidas[i] << ")\n";
    }

}

int main() {
    testConocido();
    
    return 0;
}




