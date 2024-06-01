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

using namespace std;
using namespace std::chrono;

random_device rd;  // Inicializa la semilla del generador de números aleatorios
mt19937 gen(rd()); // Generador de números aleatorios

// Estructura que representa un nodo
struct Nodo {
    int id;  // Identificador del nodo
    vector<int> vecinos;  // Lista de nodos adyacentes
    vector<double> pesos; // Pesos de las aristas

    Nodo(int id) : id(id) {}
};

// Estructura que representa el grafo
class Grafo {
public:
    vector<Nodo> nodos; // Lista de nodos en el grafo


    // Constructor de un grafo con V vértices
    Grafo(int V){
        for (int i = 0; i < V; i++) {
            nodos.push_back(Nodo(i));
        }
    }

    // Método para agregar una arista al grafo
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
    
    // Método para obtener la lista de adyacencia de un nodo
    vector<int>& getVecinos(int v) {
        return nodos[v].vecinos;
    }

    // Método para obtener los pesos de las aristas adyacentes a un nodo
    vector<double>& getPesos(int v) {
        return nodos[v].pesos;
    }

    // Método para obtener el número de vértices en el grafo
    int getV() {
        return nodos.size();
    }
};

#endif