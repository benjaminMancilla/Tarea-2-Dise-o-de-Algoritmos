#ifndef EXPERIMENTO_H
#define EXPERIMENTO_H

#include "grafo.h"
#include "dijkstraFibHeap.h"
#include "dijkstraMinHeap.h"


// Función para generar un grafo aleatorio no dirigido con v vértices y e aristas con pesos aleatorios entre (0, 1]
Grafo generarGrafo(int v, int e) {
    Grafo grafo(v); // Se crea un grafo con v vértices
    uniform_real_distribution<double> randDouble(0.0, 1.0); // Generador de números aleatorios entre (0, 1]

    // Verificar el mínimo número de aristas (v - 1)
    int minAristas = v - 1;
    if (e < minAristas) {
        cerr << "Error: El número mínimo de aristas para un grafo con " << v << " nodos es " << minAristas << endl;
        Grafo grafoError(2);
        grafoError.agregarArista(0, 1, 66.6);
        return grafoError; // Retorna un grafo de error
    }

    // Verificar el máximo número de aristas (v*(v-1)/2)
    int maxAristas = (v * (v - 1)) / 2;
    if (e > maxAristas) {
        cerr << "Error: El número máximo de aristas para un grafo con " << v << " nodos es " << maxAristas << endl;
        Grafo grafoError(2);
        grafoError.agregarArista(0, 1, 66.6);
        return grafoError; // Retorna un grafo de error
    }

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


// Función para medir el tiempo de ejecución en milisegundos de un algoritmo sobre un grafo
double medirTiempo(pair<vector<int>, vector<double>> (algoritmo)(Grafo&), Grafo& grafo) {
    auto start = high_resolution_clock::now(); // Toma el tiempo de inicio
    pair<vector<int>, vector<double>> resultado = algoritmo(grafo); // Se ejecuta el algoritmo
    auto stop = high_resolution_clock::now(); // Toma el tiempo de finalización
    auto duration = duration_cast<microseconds>(stop - start); // Calcular la duración en microsegundos
    return duration.count() / 1000.0; // Convertir a milisegundos
}


// Función para realizar el experimento de medir el tiempo de ejecución de Dijkstra con MinHeap y Dijkstra con FibHeap sobre 850 grafos. Los resultados se guardan en dos archivos .csv
void experimento(){
    cout << "\n######################### Inicia el programa #########################" << endl;
    ofstream archivo1("../data/t_minheap_ms.csv"); // Se crea un archivo para guardar los resultados de Dijkstra con MinHeap
    ofstream archivo2("../data/t_fibheap_ms.csv"); // Se crea un archivo para guardar los resultados de Dijkstra con FibHeap
    
    for (int i = 10; i < 15; i += 2) { // Se mide el tiempo de ambos algoritmos para i = 10, 12, 14
        cout << "\n======================= Experimento para i = "<< i <<" ======================" << endl;

        // Se escriben los encabezados de los archivos
        archivo1 << "i=" << i; 
        archivo2 << "i=" << i; 
        for (int h = 1; h <= 50; h++) {
            archivo1 << "," << "G" << h;
            archivo2 << "," << "G" << h;
        }
        archivo1 << endl; 
        archivo2 << endl;

        for (int j = 16; j < 23; j++) { // Se mide el tiempo de ambos algoritmos para j = 16, 17, 18, 19, 20, 21, 22
            if (i == 10 && j == 19) break; // Se saltan los valores j = 19, j = 20, j = 21, j = 22 para i = 10

            cout << "\nSe mide el tiempo de ambos algoritmos sobre 50 grafos con 2^"<< j <<" aristas" << endl;

            archivo1 << "j=" << j;
            archivo2 << "j=" << j;
            for (int k = 0; k < 50; k++) { // Se mide el tiempo de ambos algoritmos sobre 50 grafos

                Grafo grafo = generarGrafo(pow(2, i), pow(2, j));
            
                double tiempo_min = medirTiempo(dijkstraMinHeap, grafo); // Se mide el tiempo de Dijkstra con MinHeap
                archivo1 << "," << fixed << setprecision(2) << tiempo_min; // Se guarda el tiempo en el archivo

                double tiempo_fib = medirTiempo(dijkstraFibHeap, grafo); // Se mide el tiempo de Dijkstra con FibHeap
                archivo2 << "," << fixed << setprecision(2) << tiempo_fib; // Se guarda el tiempo en el archivo
            }
            
            archivo1 << endl; 
            archivo2 << endl;
        }

        archivo1 << endl; 
        archivo2 << endl;
    }

    // Se cierran los archivos
    archivo1.close();
    archivo2.close();

    cout << "\n======================================================================\n" << endl;
    cout << "Se guardan resultados en archivos t_minheap_ms.csv y t_fibheap_ms.csv\n" << endl;
    cout << "######################### Termina el programa ########################\n" << endl;
    
}

#endif