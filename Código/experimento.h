#ifndef EXPERIMENTO_H
#define EXPERIMENTO_H

#include "grafo.h"

// Función para generar un grafo aleatorio no dirigido con v vértices y e aristas con pesos aleatorios entre (0, 1]
Grafo generarGrafo(int v, int e) {
    Grafo grafo(v);
    uniform_real_distribution<double> randDouble(0.0, 1.0);
    

    // Se establecen v − 1 aristas para generar un árbol cobertor
    for (int i = 1; i < v; i++) {
        uniform_int_distribution<int> randInt(0, i-1);
        int nodoAleatorio = randInt(gen); //elige nodo aleatorio en [0, i-1]
        double peso = 0.0; 
        while (peso == 0.0) peso = randDouble(gen); //genera un peso aleatorio entre (0, 1]
        grafo.agregarArista(i, nodoAleatorio, peso); // Conectar con un nodo aleatorio anterior
    }
    
    // Se establecen las e − (v − 1) aristas restantes
    int aristasRestantes = e - (v - 1);
    uniform_int_distribution<int> randInt(0, v-1);
    while (aristasRestantes > 0) {
        int nodo1 = randInt(gen); // Se elige un nodo aleatorio
        int nodo2 = randInt(gen); // Se elige otro nodo aleatorio
        while (nodo1 == nodo2) nodo2 = randInt(gen); // Asegurarse que los nodos sean distintos
        double peso = 0.0; 
        while (peso == 0.0) peso = randDouble(gen); // Se genera un peso aleatorio entre (0, 1]
        if (!grafo.sonVecinos(nodo1, nodo2)) { // Se asegura que los nodos no tenga una arista previa
            grafo.agregarArista(nodo1, nodo2, peso);
            aristasRestantes--;
        }
    }

    return grafo;
}

void imprimirGrafo(Grafo& grafo, const std::string& filename) {
    int V = grafo.getV();
    std::ofstream file(filename);

    // Escribir el número de nodos en el archivo
    file << V << std::endl;

    // Escribir las aristas y pesos en el archivo en el formato: nodo_fuente nodo_destino peso
    for (int i = 0; i < V; i++) {
        std::vector<int> vecinos = grafo.getVecinos(i);
        std::vector<double> pesos = grafo.getPesos(i);
        for (int j = 0; j < vecinos.size(); j++) {
            file << i << " " << vecinos[j] << " " << pesos[j] << std::endl;
        }
    }

    file.close();
}

#endif