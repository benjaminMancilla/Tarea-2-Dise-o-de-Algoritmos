# Tarea 2

Este proyecto consiste en un conjunto de archivos que permiten generar grafos aleatorios, ejecutar el algoritmo de Dijkstra para encontrar los caminos más cortos en estos grafos y visualizar los grafos generados. El objetivo principal es proporcionar una implementación funcional y extensible del algoritmo de Dijkstra utilizando estructuras de datos como heaps mínimos.

El proyecto incluye archivos escritos en C++ y Python. El código en C++ se encarga de generar los grafos aleatorios, ejecutar el algoritmo de Dijkstra y guardar los resultados en archivos de texto. El código en Python se utiliza para visualizar los grafos generados a partir de estos archivos.

A continuación, se detallan los principales componentes del proyecto:

- **grafo.h**: Define las estructuras y funciones necesarias para trabajar con grafos no dirigidos. También contiene las librerías necesarias para todo el proyecto.
- **dijktraMinHeap.h**: Contiene la implementación del algoritmo de Dijkstra utilizando un heap mínimo para mantener los nodos no visitados.
- **dijktraFibHeap.h**: Contiene la implementación del algoritmo de Dijkstra utilizando una cola de Fibonacci para mantener los nodos no visitados.
- **experimento.h**: Proporciona funciones para generar grafos aleatorios y guardarlos en archivos de texto, así como para imprimir grafos en formato legible.
- **main.cpp**: Un programa en C++ que utiliza las funciones definidas en los archivos anteriores para generar un grafo aleatorio, ejecutar el algoritmo de Dijkstra y guardar los resultados en un archivo de texto.
- **plot.py**: Un script en Python que lee el grafo generado desde el archivo de texto y visualiza el grafo utilizando la biblioteca `networkx`.

Este proyecto es útil para comprender y aplicar el algoritmo de Dijkstra en la resolución de problemas de búsqueda de caminos más cortos en grafos, así como para aprender sobre el uso de estructuras de datos como heaps mínimos en algoritmos de grafos. Además, proporciona una base sólida para futuras extensiones y aplicaciones relacionadas con grafos en C++ y Python.

## Instrucciones para Ejecutar el Proyecto

Este proyecto incluye archivos para generar un grafo aleatorio, ejecutar el algoritmo de Dijkstra y visualizar el grafo generado. A continuación, se detallan los pasos para ejecutar cada parte del proyecto.

## Requisitos Previos

Asegúrate de tener instalados los siguientes elementos:

- **Compilador de C++**: Necesitarás un compilador de C++ para compilar y ejecutar el archivo `main.cpp`.
- **Python 3**: Para ejecutar el script `plot.py` que visualiza el grafo generado.

## Ejecución del Archivo main.cpp
Si solo se quiere ejecutar el archivo main.cpp:

1. Abre una terminal en la carpeta raíz del proyecto.
2. Compila el archivo `main.cpp` ejecutando el siguiente comando:
   ```bash
   g++ -o main main.cpp
   ```
3. Una vez compilado exitosamente, ejecuta el programa generado con el siguiente comando:
   ```bash
   ./main
   ```
4. El programa imprimirá las distancias mínimas de un nodo origen a todos los demás nodos, así como los nodos previos en el camino más corto.

## Ejecución del Script plot.py
El archivo plot.py compila y ejecuta el archivo main.cpp, no es necesario ejecutar el archivo main.cpp previamente.

1. Asegúrate de tener instaladas las bibliotecas `networkx` y `matplotlib` de Python. Puedes instalarlas utilizando `pip`:
   ```bash
   pip install networkx matplotlib
   ```
2. Abre una terminal en la carpeta raíz del proyecto.
3. Ejecuta el script `plot.py` con el siguiente comando:
   ```bash
   python plot.py
   ```
4. El script leerá el grafo generado por `main.cpp` desde el archivo `grafo.txt` y visualizará el grafo utilizando la biblioteca `networkx`.

¡Listo! Ahora puedes ejecutar y visualizar el proyecto sin problemas.

