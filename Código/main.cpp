
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

int main() {
    cout << "\n######################### Inicia el programa #########################" << endl;
    ofstream archivo1("t_minheap_ms.csv");
    ofstream archivo2("t_fibheap_ms.csv");
    
    for (int i = 10; i < 15; i += 2) {
        cout << "\n======================= Experimento para i = "<< i <<" ======================" << endl;

        archivo1 << "i=" << i; 
        archivo2 << "i=" << i; 
        for (int h = 1; h <= 50; h++) {
            archivo1 << "," << "G" << h;
            archivo2 << "," << "G" << h;
        }
        archivo1 << endl; 
        archivo2 << endl;

        for (int j = 16; j < 23; j++) {
            if (i == 10 && j == 19) break; // Saltar la combinación i = 10, j = 19

            cout << "\nSe mide el tiempo de ambos algoritmos sobre 50 grafos con 2^"<< j <<" aristas" << endl;

            archivo1 << "j=" << j;
            archivo2 << "j=" << j;
            for (int k = 0; k < 50; k++) {

                Grafo grafo = generarGrafo(pow(2, i), pow(2, j));
            
                double tiempo_min = medirTiempo(contarAristas, grafo);
                archivo1 << "," << fixed << setprecision(2) << tiempo_min;

                double tiempo_fib = medirTiempo(contarAristas, grafo);
                archivo2 << "," << fixed << setprecision(2) << tiempo_fib;
            }

            archivo1 << endl; 
            archivo2 << endl;
        }

        archivo1 << endl; 
        archivo2 << endl;
    }


    archivo1.close();
    archivo2.close();

    cout << "\n======================================================================\n" << endl;
    cout << "Se guardan resultados en archivos t_minheap_ms.csv y t_fibheap_ms.csv\n" << endl;
    cout << "######################### Termina el programa ########################\n" << endl;
    
    return 0;
}




