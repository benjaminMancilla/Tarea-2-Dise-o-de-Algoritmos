#ifndef EXPERIMENTO_H
#define EXPERIMENTO_H

#include "grafo.h"

// Función para generar un grafo aleatorio no dirigido con v vértices y e aristas con pesos aleatorios entre (0, 1]
Grafo generarGrafo(int v, int e) {
    Grafo grafo(v);
    uniform_real_distribution<double> randDouble(0.0, 1.0);

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

// Función para contar las aristas de un grafo
int contarAristas(Grafo grafo) {
    int numAristas = 0;

    for (const Nodo& nodo : grafo.getNodos()) {
        // Sumar el número de vecinos del nodo
        numAristas += nodo.vecinos.size();
    }

    // Cada arista se cuenta dos veces en un grafo no dirigido, así que dividimos por 2
    return numAristas / 2;
}

//Mide el tiempo de ejecución de un algoritmo que toma un Grafo como argumento.
//Recibe el puntero a una función que toma un grafo como argumento y devuelve un entero  (esto después se cambia por un par de vectores que es lo que retorna Dijkstra)
//También recibe el grafo sobre el que se va a ejecutar el algoritmo.
//Retorna el tiempo de ejecución del algoritmo en milisegundos.
double medirTiempo(int (algoritmo)(Grafo), Grafo& grafo) {
    auto start = high_resolution_clock::now(); // Toma el tiempo de inicio
    int resultado = algoritmo(grafo); // Se ejecuta el algoritmo
    auto stop = high_resolution_clock::now(); // Toma el tiempo de finalización
    auto duration = duration_cast<microseconds>(stop - start); // Calcular la duración en microsegundos
    return duration.count() / 1000.0; // Convertir a milisegundos
}

void experimento() {
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
}
















#endif