#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <iostream>
#include <limits>
#include <random>
#include <ctime>
#include <string>
#include <fstream>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <unordered_map>

using namespace std; // Habilita el uso de todos los elementos del espacio de nombres std
using namespace std::chrono; // Hbilita el uso de todos los elementos del espacio de nombres std::chrono

random_device rd;  // Inicializa la semilla del generador de números aleatorios
mt19937 gen(rd()); // Generador de números aleatorios usando la semilla rd

// Estructura que representa un nodo del grafo
struct Nodo {
    int id;  // Identificador del nodo
    vector<int> vecinos;  // Lista de nodos adyacentes
    vector<double> pesos; // Pesos de las aristas

    Nodo(int id) : id(id) {}
};

// Estructura que representa el grafo
class Grafo {
    vector<Nodo> nodos; // Lista de nodos en el grafo

public:
    // Constructor de un grafo con V vértices
    Grafo(int V){
        for (int i = 0; i < V; i++) {
            nodos.push_back(Nodo(i));
        }
    }

    // Método para agregar una arista entre dos nodos al grafo
    void agregarArista(int v, int destino, double peso) {
        nodos[v].vecinos.push_back(destino);
        nodos[v].pesos.push_back(peso);
        nodos[destino].vecinos.push_back(v);
        nodos[destino].pesos.push_back(peso);
    }

    // Metodo para verificar si dos nodos del grafo son vecinos
    bool sonVecinos(int nodo1, int nodo2) {
        vector<int>& vecinos = getVecinos(nodo1);
        for (int vecino : vecinos) {
            if (vecino == nodo2) {
                return true;
            }
        }
        return false;
    }

    // Método para obtener un nodo por su id
    vector<Nodo>& getNodos(){
        return nodos;
    }
    
    // Método para obtener la lista de adyacencia de un nodo
    vector<int>& getVecinos(int id) {
        return nodos[id].vecinos;
    }

    // Método para obtener la lista de pesos de las aristas a un nodo
    vector<double>& getPesos(int id) {
        return nodos[id].pesos;
    }

    // Método para obtener el número de vértices en el grafo
    int getV() {
        return nodos.size();
    }

};

// Estructura que representa un par de la forma (distancia, nodo). Será almacenado en Q
struct Par {
    double distancia;  // Distancia mínima desde el nodo de origen
    int nodo;  // Índice del nodo en el grafo

    Par() : distancia(numeric_limits<double>::max()), nodo(-1) {}  // Constructor predeterminado
    Par(double distancia, int nodo) : distancia(distancia), nodo(nodo) {} // Constructor con parámetros
};

#endif