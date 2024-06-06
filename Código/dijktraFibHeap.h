#ifndef DIJKTRAFIBHEAP_H
#define DIJKTRAFIBHEAP_H

#include "grafo.h"

using namespace std;

struct NodeFib {
    Par* data;     // Par que contiene nodo y distancia (antes key)
    NodeFib* parent;
    NodeFib* child;
    NodeFib* left;
    NodeFib* right;
    int degree;
    bool mark;

    NodeFib(Par* p) 
        : data(p), parent(nullptr), child(nullptr), left(this), right(this), degree(0), mark(false) {}
};



class FibonacciHeap {
private:
    NodeFib* min;
    int n;

    void insertIntoRootList(NodeFib* x) {
        // if (x == nullptr) {
        //     std::cerr << "Error: node is nullptr in insertIntoRootList\n";
        //     return;
        // }
        // if (min == nullptr) {
        //     std::cerr << "Error: min is nullptr in insertIntoRootList\n";
        //     return;
        // }
        if (min == nullptr) {
            min = x;
        } else {
            x->left = min;
            x->right = min->right;
            min->right->left = x;
            min->right = x;
            if (x->data->distancia < min->data->distancia) {
                min = x;
            }
        }
    }


public:    
    // constructor
    FibonacciHeap() : min(nullptr), n(0) {}
    // FIB-HEAP-INSERT
    void insertNode(NodeFib* x) {
        x->degree = 0;
        x->parent = nullptr;
        x->child = nullptr;
        x->mark = false;
        if (min==nullptr) {
            min = x;
            x->left = x;
            x->right = x;
        } else {
            insertIntoRootList(x);
            if (x->data->distancia < min->data->distancia) {
                min = x;
            }
        }
        n++;
    }


    // Encontrar el mínimo
    NodeFib* getMin() {
        return min;
    }

    // para concatenar
    void concatenateLists(NodeFib* a, NodeFib* b) {
        if (a==nullptr || b==nullptr) return;
        NodeFib* aRight = a->right;
        NodeFib* bLeft = b->left;
        a->right = b;
        b->left = a;
        aRight->left = bLeft;
        bLeft->right = aRight;
    }

    //Union de dos Fib Heaps
    FibonacciHeap* unir(FibonacciHeap* H1, FibonacciHeap* H2) {
        FibonacciHeap* H = new FibonacciHeap();
        H->min = H1->min;
    
        concatenateLists(H->min, H2->min);
        
        if (H1->min == nullptr || (H2->min != nullptr && H2->min->data->distancia < H1->min->data->distancia)) {
            H->min = H2->min;
        }

        H->n = H1->n + H2->n;
        delete H1;
        delete H2;
        return H;
    }


    //linkea dos arboles del mismo degree
    void link(NodeFib* y, NodeFib* x) {
        if (y == nullptr || x == nullptr || y->data == nullptr || x->data == nullptr) {
            std::cerr << "Error: y, x, y->data, or x->data is nullptr in link\n";
            return;
        }
        y->left->right = y->right;
        y->right->left = y->left;

        y->parent = x;
        if (x->child == nullptr) {
            x->child = y;
            y->right = y;
            y->left = y;
        } else {
            y->left = x->child;
            y->right = x->child->right;
            x->child->right->left = y;
            x->child->right = y;
        }
        x->degree++;
        y->mark = false;
    }
    
    void consolidate() {
        int D = static_cast<int>(std::log2(n)) + 2;
        std::vector<NodeFib*> A(D, nullptr);

        int lenghtRootList = 0;
        NodeFib* startAux = min;
        NodeFib* p = min;
        do {
            lenghtRootList++;
            p = p->right;
        } while (p != startAux);

        // Inicializar el array A
        // for (int i = 0; i <= D; ++i) {
        //     A[i] = nullptr;
        // }

        if (min == nullptr) return; // Si el heap está vacío, no hay nada que consolidar

        NodeFib* start = min;
        NodeFib* w = min;
        int circularIndex = 0;

        do {
            NodeFib* x = w;
            NodeFib* next = w->right; // Guardar la referencia al siguiente nodo
            int d = x->degree;


            // Consolidar árboles del mismo grado
            while (A[d] != nullptr) {

                NodeFib* y = A[d];
                if (x->data->distancia > y->data->distancia) {
                    link(x, y); //link esta bien pero revisar
                    x = y;
                }

                else {
                    link(y, x);
                }
                
                A[d] = nullptr;
                d++;
            }
            A[d] = x;

            // Moverse al siguiente nodo
            w = next;
            circularIndex++;

        } while (circularIndex < lenghtRootList);

        // Reconstruir la lista de raíz y encontrar el nuevo mínimo
        min = nullptr;
        for (NodeFib* node : A) {
            if (node != nullptr) {
                if (min == nullptr) {
                    node->left = node;
                    node->right = node;
                    min = node;
                } else {
                    insertIntoRootList(node);
                    if (node->data->distancia < min->data->distancia) {
                        min = node;
                    }
                }
            }
        }
    }


    // Extraer minimo
    NodeFib* extractMin() {
        NodeFib* z = min;
        if (z!=nullptr) {
            if (z->child != nullptr) {
                NodeFib* child = z->child;
                do {
                    NodeFib* next = child->right;
                    insertIntoRootList(child);
                    child->parent = nullptr;
                    child = next;
                } while (child != z->child);
            }

            z->left->right = z->right;
            z->right->left = z->left;

            if (z == z->right) {
                min = nullptr;
            } else {
    
                min = z->right;
                consolidate();
            }

            n--;
        }
        return z;
    }

    //elimina nodo x de su nodo padre y y lo mueve a la lista raiz
    void cut(NodeFib* x, NodeFib* y) {
        //si es que es el unico hijo
        if (x->right == x) {
            y->child = nullptr;
        //sino, lo evita
        } else {
            x->left->right = x->right;
            x->right->left = x->left;
            if (y->child == x) {
                y->child = x->right;
            }
        }
        y->degree--;

        //agrega x en la root list
        insertIntoRootList(x);
        x->parent = nullptr;
        x->mark = false;
    }

    //cascading cuts
    void cascadingCut(NodeFib* y) {
        NodeFib* z = y->parent;
        if (z != nullptr) {
            if (y->mark==false) {
                y->mark = true;
            } else {
                cut(y, z);
                cascadingCut(z);
            }
        }
    }

    
    void decreaseKey(NodeFib* x, double newDistance) {
        if (newDistance > x->data->distancia) {
            throw std::invalid_argument("New key is greater than current key");
            return;
        }
        x->data->distancia = newDistance;
        NodeFib* y = x->parent;
        if (y != nullptr && x->data->distancia < y->data->distancia) {
            cut(x, y);
            cascadingCut(y);
        }

        if (x == nullptr) {
            std::cerr << "Error: x is nullptr\n";
            return;
        }
        if (x->data == nullptr) {
            std::cerr << "Error: x->data is nullptr\n";
            return;
        }
        if (min == nullptr) {
            std::cerr << "Error: min is nullptr\n";
            return;
        }
        if (min->data == nullptr) {
            std::cerr << "Error: min->data is nullptr\n";
            return;
        }
        if (x->data->distancia < min->data->distancia) {
            min = x;
        }
    }

};


// Implementación del algoritmo de Dijkstra
pair<vector<int>,vector<double>> dijkstraFibHeap(Grafo& grafo) {
    int V = grafo.getV();
    vector<double> distancias(V, numeric_limits<double>::max());  // distancia mínimas
    vector<int> previos(V, -1);  // Nodos previos en el camino más corto
    FibonacciHeap heap;  // Heap para mantener los nodos no visitados
    std::unordered_map<int, NodeFib*> nodeMap; // Mapea el id del nodo a NodeFib en el heap

    // Paso 3: Inicializar la distancia del nodo raíz como 0
    distancias[0] = 0;
    previos[0] = -1;
    Par* raizPar = new Par(0.0, 0);
    NodeFib* raizNodo = new NodeFib(raizPar);
    heap.insertNode(raizNodo);
    nodeMap[0] = heap.getMin(); // Guardamos el nodo en el mapa

    // Paso 4: Inicializar las distancias mínimas para cada nodo
    for (int v = 0; v < V; ++v) {
        if (v != 0) {
            Par* par = new Par(numeric_limits<double>::max(), v);
            NodeFib* x = new NodeFib(par);
            heap.insertNode(x);
            nodeMap[v] = x; // Guardamos el nodo en el mapa
        }
    }



    // Paso 6: Ejecutar el algoritmo de Dijkstra
    while (heap.getMin() != nullptr) {

        // Paso 6a: Obtener el par con la distancia mínima
        NodeFib* nodeMin = heap.extractMin();
        Par* parMin = nodeMin->data;
        int v = parMin->nodo;


        vector<int>& vecinos = grafo.getVecinos(v);
        vector<double>& pesos = grafo.getPesos(v);

        // Paso 6b: Relajar todas las aristas adyacentes al nodo actual
        for (unsigned int i = 0; i < vecinos.size(); ++i) {

            int u = vecinos[i];// Nodo vecino
            double peso = pesos[i];// Peso de la arista
            // Si la distancia de u es mayor que la distancia de v + peso
            if (distancias[u] > distancias[v] + peso) {
                // Actualizar la distancia de v
                distancias[u] = distancias[v] + peso;
                // Actualizar el nodo previo de v
                previos[u] = v;
                // Actualizar la distancia en el Heap
                heap.decreaseKey(nodeMap[u], distancias[u]);
            }
        }
    }

    // Paso 7: Retornar un par con los arreglos previos y distancias
    return {previos, distancias};
}

#endif