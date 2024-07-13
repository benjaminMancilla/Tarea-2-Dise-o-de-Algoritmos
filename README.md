# Tarea 2

Este proyecto consiste en un conjunto de archivos que permiten comparar el rendimiento de los algoritmos de Dijkstra utilizando un experimento en C++. Los resultados del experimento se almacenan en archivos CSV y se utiliza un script en Python para graficar estos resultados.

## Componentes del Proyecto

El proyecto está organizado en varios directorios y archivos principales:

- **src/**: Contiene el código fuente en C++ para ejecutar el experimento, incluyendo la función `main()` que inicia el programa.
  - **grafo.h**: Define las estructuras y funciones necesarias para trabajar con grafos no dirigidos.
  - **dijkstraMinHeap.h**: Implementa el algoritmo de Dijkstra utilizando un heap mínimo para mantener los nodos no visitados.
  - **dijkstraFibHeap.h**: Implementa el algoritmo de Dijkstra utilizando una cola de Fibonacci para mantener los nodos no visitados.
  - **experimento.h**: Proporciona funciones para generar grafos aleatorios y guardar los resultados en archivos CSV, así como para imprimir grafos en formato legible.
  - **main.cpp**: Programa principal en C++ que utiliza las funciones definidas en los archivos anteriores para generar un grafo aleatorio, ejecutar los algoritmos de Dijkstra y guardar los resultados en archivos CSV.

- **data/**: Almacena los archivos CSV que contienen los resultados generados por el experimento.
  - **t_minheap_ms.csv**: Archivo CSV con los tiempos de ejecución del algoritmo de Dijkstra utilizando minHeap.
  - **t_fibheap_ms.csv**: Archivo CSV con los tiempos de ejecución del algoritmo de Dijkstra utilizando fibHeap.

- **scripts/**: Contiene un script en Python para graficar los resultados del experimento.
  - **graficar.py**: Script en Python que lee los archivos CSV generados por el experimento y visualiza los resultados utilizando las bibliotecas `matplotlib` y `pandas`.

- **images/**: Directorio para almacenar las imágenes (gráficos) generadas por el script de Python.
  - Imágenes como `fib_i_10.jpg`, `heap_i_10.jpg`, `comparison_i_10.jpg`, entre otras, correspondientes a diferentes configuraciones del experimento.

- **README.md**: Archivo que contiene las instrucciones para ejecutar el proyecto y otra información relevante.

## Ejecución del Proyecto

### Requisitos Previos

Asegúrate de tener instalados los siguientes elementos:

- **Compilador de C++**: Necesitarás un compilador de C++ para compilar y ejecutar el archivo `main.cpp`.
- **Python 3**: Para ejecutar el script `graficar.py` que visualiza los resultados del experimento.

### Ejecución del Archivo `main.cpp`

Si deseas ejecutar únicamente el archivo `main.cpp`, sigue estos pasos:

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

### Ejecución del Script `graficar.py`

El script `graficar.py` requiere la ejecución previa de `main.cpp` porque utilizará los archivos CSV resultantes.

1. Asegúrate de tener instaladas las bibliotecas `matplotlib`, `pandas`, `numpy` y `curve_fit` Python. Puedes instalarlas utilizando `pip`:
   ```bash
   pip install matplotlib pandas numpy curve_fit
   ```
2. Abre una terminal en la carpeta raíz del proyecto.
3. Ejecuta el script `graficar.py` con el siguiente comando:
   ```bash
   python scripts/graficar.py
   ```
4. El script leerá los archivos CSV `t_minheap_ms.csv` y `t_fibheap_ms.csv` desde el directorio `data/` y generará gráficos comparativos en el directorio `images/`.

¡Listo! Ahora puedes ejecutar y visualizar el proyecto sin problemas.

