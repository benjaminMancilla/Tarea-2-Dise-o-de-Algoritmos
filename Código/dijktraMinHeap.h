#ifndef DIJKTRAMINHEAP_H
#define DIJKTRAMINHEAP_H

#include "grafo.h"

class Q {
    vector<Par> heap;
    vector<int> pos;  // Almacena la posición de cada par en el Heap   

public:
    Q(int size) {
        heap.reserve(size);
        pos.resize(size);
    }

    // Método para insertar un par en el Heap
    void insertar(Par par) {
        int i = heap.size();
        heap.push_back(par);
        pos[par.nodo] = i;
        siftUp(i);
    }

    // Método para extraer el par con menor distancia
    Par extraerMin() {
        Par min = heap[0];
        heap[0] = heap[heap.size() - 1];
        pos[heap[0].nodo] = 0;
        heap.pop_back();
        siftDown(0);
        return min;
    }

    // Método para actualizar la distancia de un par en el Heap
    void decreaseKey(int nodo, double nuevaDistancia) {
        int i = pos[nodo];
        heap[i].distancia = nuevaDistancia;
        siftUp(i);
    }
    
    // Método para verificar si el Heap está vacío
    bool isEmpty() {
        return heap.empty();
    }

private:
    // Método para mantener la propiedad del Heap (subir un nodo)
    void siftUp(int i) {
        while (i > 0 && heap[padre(i)].distancia > heap[i].distancia) {
            swap(heap[i], heap[padre(i)]);
            pos[heap[i].nodo] = i;
            pos[heap[padre(i)].nodo] = padre(i);
            i = padre(i);
        }
    }

    // Método para mantener la propiedad del Heap (bajar un nodo)
    void siftDown(int i) {
        int indiceMenor = i;
        unsigned int izquierdo = hijoIzquierdo(i);
        unsigned int derecho = hijoDerecho(i);
        if (izquierdo < heap.size() && heap[izquierdo].distancia < heap[indiceMenor].distancia)
            indiceMenor = izquierdo;
        if (derecho < heap.size() && heap[derecho].distancia < heap[indiceMenor].distancia)
            indiceMenor = derecho;
        if (indiceMenor != i) {
            swap(heap[i], heap[indiceMenor]);
            pos[heap[i].nodo] = i;
            pos[heap[indiceMenor].nodo] = indiceMenor;
            siftDown(indiceMenor);
        }
    }

    // Métodos para calcular índices de padres e hijos
    int padre(int i) {
        return (i - 1) / 2;
    }

    int hijoIzquierdo(int i) {
        return 2 * i + 1;
    }

    int hijoDerecho(int i) {
        return 2 * i + 2;
    }
};

// Implementación del algoritmo de Dijkstra
pair<vector<int>, vector<double>> dijkstraMinHeap(Grafo& grafo) {
    int V = grafo.getV();
    vector<double> distancias(V, numeric_limits<double>::max());  // distancia mínimas
    vector<int> previos(V, -1);  // Nodos previos en el camino más corto
    Q heap(V);  // Heap para mantener los nodos no visitados

    // Paso 3: Inicializar la distancia del nodo raíz como 0
    distancias[0] = 0.0;
    heap.insertar(Par(0.0, 0));

    // Paso 4: Inicializar las distancias mínimas para cada nodo
    for (int v = 1; v < V; v++) {
        // Agregar el par (distancia = ∞, nodo = i) a Q
        heap.insertar(Par(distancias[v], v));
    }

    // Paso 6: Ejecutar el algoritmo de Dijkstra
    while (!heap.isEmpty()) {
        // Paso 6a: Obtener el par con la distancia mínima
        Par parMin = heap.extraerMin();
        int v = parMin.nodo;

        // Paso 6b: Relajar todas las aristas adyacentes al nodo actual
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