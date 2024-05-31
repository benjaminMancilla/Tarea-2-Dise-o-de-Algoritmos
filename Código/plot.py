import os
import subprocess
import networkx as nx
import matplotlib.pyplot as plt

def generar_grafo_desde_archivo(filename):
    with open(filename, 'r') as file:
        # Leer el número de nodos
        V = int(file.readline())

        # Leer las aristas y pesos y construir el grafo
        edges = []
        edge_labels = {}
        for line in file:
            if line.strip():  # Ignorar líneas en blanco
                src, dest, weight = map(float, line.split())
                edges.append((int(src), int(dest)))
                edge_labels[(int(src), int(dest))] = weight

        G = nx.Graph()
        G.add_nodes_from(range(V))
        G.add_edges_from(edges)

    return G, edge_labels

# Se rescata la dirección del archivo actual
directorio = os.path.dirname(os.path.abspath(__file__))

# Compilar el programa externo
compilacion_exitosa = subprocess.run(["g++", "-o", directorio + "/main", directorio + "/main.cpp"], stdout=subprocess.PIPE, stderr=subprocess.PIPE).returncode

if compilacion_exitosa != 0:
    print("Error: No se pudo compilar el programa externo.")
    exit(1)



# Cambiar al directorio donde se encuentra el programa compilado
os.chdir(directorio)

# Se compila y corre el archivo main.cpp imprimiendo en consola el output
output = subprocess.run(["./main"], stdout=subprocess.PIPE).stdout.decode('utf-8')
# Imprimir el output del programa externo
print(output)

# Esperar a que se complete la ejecución del programa externo
# antes de intentar cargar el grafo desde el archivo generado
G, edge_labels = generar_grafo_desde_archivo(directorio + "/grafo.txt")

# Visualizar el grafo generado desde el archivo de texto
pos = nx.spring_layout(G)  # Determina la posición de los nodos
nx.draw(G, pos, with_labels=True, node_size=700)  # Dibuja los nodos
nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels)
plt.title("Grafo generado desde archivo")
plt.show()
