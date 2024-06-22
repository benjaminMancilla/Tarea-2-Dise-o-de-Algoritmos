# -*- coding: utf-8 -*-
"""
Created on Mon Jun 10 18:17:24 2024

@author: benja
"""

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit
import os

# Función para cargar y procesar datos del archivo CSV
def load_and_process_csv(filename):
    rows = []
    with open(filename, 'r') as file:
        i = None
        for line in file:
            line = line.strip()
            if line.startswith('i='):
                i = int(line.split('=')[1].split(',')[0])  # Extraer el entero después de '=' y antes de ','
            elif line.startswith('j='):
                j = int(line.split('=')[1].split(',')[0])  # Extraer el entero después de '=' y antes de ','
                row_data = [float(value) for value in line.split(',')[1:]]  # Saltar 'j=' y convertir el resto a flotante
                rows.append((i, j, row_data))
                print(f"Data for i={i}, j={j}: {row_data}")
    return rows

# Cargar datos
parent_directory = os.path.dirname(os.path.dirname(os.path.abspath(__file__))) # Obtener el directorio padre
original_directory = os.getcwd() # Guarda el directorio actual como el original
images_directory = parent_directory + "/images" # Directorio para guardar las imágenes
heap_data = load_and_process_csv(parent_directory + "/data/t_minheap_ms.csv")
fib_data = load_and_process_csv(parent_directory + "/data/t_fibheap_ms.csv")

# Calcular promedios y generar datos para graficar
def calculate_averages(data):
    averages = []
    for (i, j, times) in data:
        avg_time = np.mean(times)
        averages.append((i, j, avg_time))
    return pd.DataFrame(averages, columns=['i', 'j', 'avg_time'])

# Calcular promedios y generar datos para graficar
def calculate_averages_and_stds(data):
    averages = []
    std_devs = []
    for (i, j, times) in data:
        avg_time = np.mean(times)
        std_dev = np.std(times)
        averages.append((i, j, avg_time))
        std_devs.append((i, j, std_dev))
    return pd.DataFrame(averages, columns=['i', 'j', 'avg_time']), pd.DataFrame(std_devs, columns=['i', 'j', 'std_dev'])

# Calcular promedios y desviaciones estándar para los datos cargados
heap_avg, heap_std = calculate_averages_and_stds(heap_data)
fib_avg, fib_std = calculate_averages_and_stds(fib_data)

# Definir la función para ajustar los datos con el nuevo parámetro c3
def heap_func(j, c1, c2, c3, i):
    return c1 * (2**j) * np.log(c2 * (2**i)) + c3

def fib_func(j, c1, c2, c3, i):
    return c1 * (2**j) + c2 * (2**i) * np.log(c3 * (2**i))

# Ajustar los datos y generar valores ajustados para cada valor de i
def fit_and_generate(data, funco, num_params):
    fits = {}
    for i, group in data.groupby('i'):
        params, _ = curve_fit(lambda j, c1, c2, c3: funco(j, c1, c2, c3, i), group['j'], group['avg_time'])
        n_fit = np.linspace(min(group['j']), max(group['j']), 100)
        fit = funco(n_fit, params[0], params[1], params[2], i)
        fits[i] = (n_fit, fit, params)
    return fits

# Ajustar y generar datos para los promedios de los datos de heap
heap_fits = fit_and_generate(heap_avg, heap_func, num_params=4)
fib_fits = fit_and_generate(fib_avg, fib_func, num_params=4)

# Graficar resultados
for i, (heap_n_fit, heap_fit, heap_params) in heap_fits.items():
    plt.figure(figsize=(7, 5))
    group = heap_avg[heap_avg['i'] == i]
    plt.scatter(group['j'], group['avg_time'], label='Heap Time', color='blue')
    plt.plot(heap_n_fit, heap_fit, label=f'Heap Fit: {heap_params[0]:.2e}*2^j*log({heap_params[1]:.2e}*2^{i}) + {round(heap_params[2], 2)}', color='blue', linestyle='--')
    plt.xlabel('j')
    plt.ylabel('Average Time (ms)')
    plt.legend()
    plt.title(f'Dijkstra Algorithm Timing with Min-Heap (i={i})')
    plt.grid(True)
    prefix = 'heap'
    os.chdir(images_directory)
    plt.savefig(f'{prefix}_i_{i}.jpg')
    plt.show()
    plt.close()
    os.chdir(original_directory)
    
    
    

for i, (fib_n_fit, fib_fit, fib_params) in fib_fits.items():
    plt.figure(figsize=(7, 5))
    group = fib_avg[fib_avg['i'] == i]
    plt.scatter(group['j'], group['avg_time'], label='Fibonacci Heap Time', color='green')
    plt.plot(fib_n_fit, fib_fit, label=f'Fib Heap Fit: {fib_params[0]:.2e}*2^j + {fib_params[1]:.2e}*2^{i}*log({fib_params[2]:.2e}*2^{i})', color='green', linestyle='--')
    plt.xlabel('j')
    plt.ylabel('Average Time (ms)')
    plt.legend()
    plt.title(f'Dijkstra Algorithm Timing with Fibonacci Heap (i={i})')
    plt.grid(True)
    prefix = 'fib'
    os.chdir(images_directory)
    plt.savefig(f'{prefix}_i_{i}.jpg')
    plt.show()
    plt.close()
    os.chdir(original_directory)
    
    
    
# Graficar resultados con barras de error
for i, group in heap_avg.groupby('i'):
    plt.figure(figsize=(7, 5))
    plt.errorbar(group['j'], group['avg_time'], yerr=heap_std[heap_std['i'] == i]['std_dev'], fmt='o', label='Heap Time', color='blue', ecolor='darkblue', capsize=5)
    heap_n_fit, heap_fit, heap_params = heap_fits[i]

    plt.xlabel('j')
    plt.ylabel('Average Time (ms)')
    plt.legend()
    plt.title(f'Dijkstra Algorithm Timing with Min-Heap (i={i}) with Error Bars')
    plt.grid(True)
    prefix = 'heap_error_bars'
    os.chdir(images_directory)
    plt.savefig(f'{prefix}_i_{i}.jpg')
    plt.show()
    plt.close()
    os.chdir(original_directory)

for i, group in fib_avg.groupby('i'):
    plt.figure(figsize=(7, 5))
    plt.errorbar(group['j'], group['avg_time'], yerr=fib_std[fib_std['i'] == i]['std_dev'], fmt='o', label='Fibonacci Heap Time', color='green', ecolor='darkgreen', capsize=5)
    fib_n_fit, fib_fit, fib_params = fib_fits[i]
    
    plt.xlabel('j')
    plt.ylabel('Average Time (ms)')
    plt.legend()
    plt.title(f'Dijkstra Algorithm Timing with Fibonacci Heap (i={i}) with Error Bars')
    plt.grid(True)
    prefix = 'fib_error_bars'
    os.chdir(images_directory)
    plt.savefig(f'{prefix}_i_{i}.jpg')
    plt.show()
    plt.close()
    os.chdir(original_directory)
    
    

# Crear DataFrames para los valores fiteados de Heap y Fibonacci
heap_fit_params_df = pd.DataFrame(columns=['i', 'j', 'c1', 'c2', 'c3', 'error'])
fib_fit_params_df = pd.DataFrame(columns=['i', 'j', 'c1', 'c2', 'c3', 'error'])

# Calcular y almacenar los valores fiteados para Heap
for i, (_, heap_fit, heap_params) in heap_fits.items():
    actual_group = heap_avg[heap_avg['i'] == i]
    for j, avg_time in zip(actual_group['j'], actual_group['avg_time']):
        predicted = heap_func(j, *heap_params, i)
        mse = (avg_time - predicted) ** 2
        heap_fit_params_df.loc[len(heap_fit_params_df)] = {'i': i, 'j': j, 'c1': heap_params[0], 'c2': heap_params[1], 'c3': heap_params[2], 'error': mse}

# Calcular y almacenar los valores fiteados para Fibonacci
for i, (_, fib_fit, fib_params) in fib_fits.items():
    actual_group = fib_avg[fib_avg['i'] == i]
    for j, avg_time in zip(actual_group['j'], actual_group['avg_time']):
        predicted = fib_func(j, *fib_params, i)
        mse = (avg_time - predicted) ** 2
        fib_fit_params_df.loc[len(fib_fit_params_df)] = {'i': i, 'j': j, 'c1': fib_params[0], 'c2': fib_params[1], 'c3': fib_params[2], 'error': mse}

# Mostrar los DataFrames con los valores de 'j'
print("Heap Fit Parameters:")
print(heap_fit_params_df)

print("\nFibonacci Fit Parameters:")
print(fib_fit_params_df)

heap_stats = heap_avg.merge(heap_std, on=['i', 'j'])
heap_stats['variance'] = heap_stats['std_dev'] ** 2

fib_stats = fib_avg.merge(fib_std, on=['i', 'j'])
fib_stats['variance'] = fib_stats['std_dev'] ** 2

# Mostrar las tablas con los valores requeridos
print("Heap Statistics:")
print(heap_stats)

print("\nFibonacci Heap Statistics:")
print(fib_stats)

average_errorsHeap = heap_fit_params_df.groupby('i')['error'].mean().reset_index()
average_errorsFib = fib_fit_params_df.groupby('i')['error'].mean().reset_index()

# Graficar resultados para Min-Heap y Fibonacci Heap
for i in [10, 12, 14]:
    plt.figure(figsize=(10, 6))
    
    # Min-Heap
    group_heap = heap_avg[heap_avg['i'] == i]
    heap_n_fit, heap_fit, heap_params = heap_fits[i]
    plt.plot(heap_n_fit, heap_fit, label=f'Min-Heap Fit: {heap_params[0]:.2e}*2^j*log({heap_params[1]:.2e}*2^{i}) + {heap_params[2]:.2e}', color='blue')
    
    # Fibonacci Heap
    group_fib = fib_avg[fib_avg['i'] == i]
    fib_n_fit, fib_fit, fib_params = fib_fits[i]
    plt.plot(fib_n_fit, fib_fit, label=f'Fibonacci Heap Fit: {fib_params[0]:.2e}*2^j + {fib_params[1]:.2e}*2^{i}*log({fib_params[2]:.2e}*2^{i})', color='green')
    
    # Configuración del gráfico
    plt.xlabel('j')
    plt.ylabel('Average Time (ms)')
    plt.legend()
    plt.title(f'Dijkstra Algorithm Timing Comparison (i={i})')
    plt.grid(True)
    os.chdir(images_directory)
    plt.savefig(f'comparison_i_{i}.jpg')
    plt.show()
    plt.close()
    os.chdir(original_directory)
