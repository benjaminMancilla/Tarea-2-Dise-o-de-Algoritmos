#ifndef DIJKSTRAMINHEAP_H
#define DIJKSTRAMINHEAP_H

#include "grafo.h"

// Estructura que representa una cola de prioridad mínima
class minHeap {
    vector<Par> nodosHeap; // Representa la cola de prioridad. Cada elemento (nodo del heap) es un par (distancia, nodo).
    vector<int> pos;  // Almacena la posición de cada par en el Heap   

public:
    // Constructor de la cola de prioridad
    minHeap(int size) { 
        nodosHeap.reserve(size);
        pos.resize(size);
    }

    // Método para extraer el par con menor distancia
    Par extraerMin() {
        Par min = nodosHeap[0];
        nodosHeap[0] = nodosHeap[nodosHeap.size() - 1];
        pos[nodosHeap[0].nodo] = 0;
        nodosHeap.pop_back();
        bajarNodo(0);
        return min;
    }

    // Método para actualizar la distancia de un par en el Heap
    void decreaseKey(int nodo, double nuevaDistancia) {
        int i = pos[nodo];
        nodosHeap[i].distancia = nuevaDistancia;
        subirNodo(i);
    }
    
    // Método para verificar si el Heap está vacío
    bool isEmpty() {
        return nodosHeap.empty();
    }


    // Método para construir el heap a partir de un vector de pares (heapify)
    void buildHeap(vector<Par>& pares) {
        nodosHeap = pares;
        for (int i = 0; i < nodosHeap.size(); i++) {
            pos[nodosHeap[i].nodo] = i;
        }
        for (int i = padre(nodosHeap.size() - 1); i >= 0; i--) {
            bajarNodo(i);
        }
    }

private:
    // Método para mantener la propiedad del Heap (subir un nodo)
    void subirNodo(int i) {
        while (i > 0 && nodosHeap[padre(i)].distancia > nodosHeap[i].distancia) {
            swap(nodosHeap[i], nodosHeap[padre(i)]);
            pos[nodosHeap[i].nodo] = i;
            pos[nodosHeap[padre(i)].nodo] = padre(i);
            i = padre(i);
        }
    }

    // Método para mantener la propiedad del Heap (bajar un nodo)
    void bajarNodo(int i) {
        int indiceMenor = i;
        unsigned int izquierdo = hijoIzquierdo(i);
        unsigned int derecho = hijoDerecho(i);
        if (izquierdo < nodosHeap.size() && nodosHeap[izquierdo].distancia < nodosHeap[indiceMenor].distancia)
            indiceMenor = izquierdo;
        if (derecho < nodosHeap.size() && nodosHeap[derecho].distancia < nodosHeap[indiceMenor].distancia)
            indiceMenor = derecho;
        if (indiceMenor != i) {
            swap(nodosHeap[i], nodosHeap[indiceMenor]);
            pos[nodosHeap[i].nodo] = i;
            pos[nodosHeap[indiceMenor].nodo] = indiceMenor;
            bajarNodo(indiceMenor);
        }
    }

    // Métodos para calcular el índice del padre de un nodo dado
    int padre(int i) {
        return (i - 1) / 2;
    }

    // Métodos para calcular el índice del hijo izquierdo de un nodo dado
    int hijoIzquierdo(int i) {
        return 2 * i + 1;
    }

    // Métodos para calcular el índice del hijo derecho de un nodo dado
    int hijoDerecho(int i) {
        return 2 * i + 2;
    }
};

// Implementación del algoritmo de Dijkstra
pair<vector<int>, vector<double>> dijkstraMinHeap(Grafo& grafo) {
    int V = grafo.getV();
    // Paso 1: Crear un vector de distancias y previos
    vector<double> distancias(V, numeric_limits<double>::max());  // distancia mínimas
    vector<int> previos(V, -1);  // Nodos previos en el camino más corto

    // Paso 2: Crear un objeto minHeap como estructura Q
    minHeap heap(V);  // Heap para mantener los nodos no visitados

    // Paso 3: Inicializar la distancia del nodo raíz como 0
    distancias[0] = 0.0;

    vector<Par> pares(V);
    pares[0] = Par(0.0, 0);

    // Paso 4: Se agregan los nodos a un vector de pares
    for (int v = 1; v < V; v++) {
        // Agregar el par (distancia = ∞, nodo = i) a Q
        pares[v] = Par(distancias[v], v);
    }

    // Paso 5: Construir el Heap a partir del vector de pares (heapify)
    heap.buildHeap(pares);

    // Paso 6: Ejecutar el algoritmo de Dijkstra
    while (!heap.isEmpty()) {
        // Paso 6a: Obtener el par con la distancia mínima
        Par parMin = heap.extraerMin();
        int v = parMin.nodo;

        // Paso 6b: Iterar sobre los vecinos del nodo v
        for (unsigned int i = 0; i < grafo.getVecinos(v).size(); i++) {
            int u = grafo.getVecinos(v)[i]; // Nodo vecino
            double peso = grafo.getPesos(v)[i]; // Peso de la arista
            // Si la distancia de u es mayor que la distancia de v + peso
            if (distancias[u] > distancias[v] + peso) {
                // Actualizar la distancia de v
                distancias[u] = distancias[v] + peso;
                // Actualizar el nodo previo de v
                previos[u] = v;
                // Actualizar la distancia en el Heap
                heap.decreaseKey(u, distancias[u]);
            }
        }
    }

    // Paso 7: Retornar un par con los arreglos previos y distancias
    return {previos, distancias};
}



#endif