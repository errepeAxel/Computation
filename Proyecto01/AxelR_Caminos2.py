# Algoritmo que obtiene el camino más corto entre dos nodos en una red no dirigida

import numpy as np  # Se importa la libreria numpy
import pandas as pd  # Se importa la libreria pandas
from queue import Queue  # Se importa la funcion Queue del modulo queue

# INPUT DE TABLA DE ADYACENCIA
nodos = int(input(f"Inserte el numero de nodos de la red: "))  # Numero de nodos de la red
ad_table = np.random.random((nodos, nodos))  # tabla de adyacencia con valores random
ad_table = pd.DataFrame(ad_table)
for i in range(nodos):
    for j in range(nodos):  # Para cada columna i de cada fila j
        if ad_table[j][i] != ad_table[i][j]:  # Si los valores de la tabla de adyacencia de la fila
            # j--columna i son diferentes a las de la fila i--columna j
            conex = int(input(f"El nodo {i} tiene una conexion con el nodo {j}? "))  # Input de si
            # existe conexion entre ambos nodos

            # Al ser una matriz no dirigida, las celdas j-i e i-j deben tener el mismo valor
            ad_table[j][i] = conex
            ad_table[i][j] = conex
        else:
            if j == i:  # Checamos si el nodo j tiene una concexion consigo msimo
                conex = int(input(f"El nodo {i} tiene una conexion con el nodo {j}? "))
                ad_table[j][i] = conex
                ad_table[i][j] = conex

# Creacion de la lista de adyacencia
adj_list2 = {}  # 'ad_list2' sera un diccionario en el que se almacenara la
# informacion de los vecinos de cada uno de los nodos del grafo
for nodo in range(nodos):
    vecinos2 = []  # 'vecinos2' almacena una lista con todos los vecinos del nodo 'nodo'
    for i in range(nodos):
        if ad_table[nodo][i] == 1:  # Si en la tabla de adyacencia se encuentra un 1, quiere
            # decir que el nodo 'nodo' y el nodo 'i' son vecinos
            vecinos2.append(i)  # Por eso se agrega al nodo 'i' a la lista de vecinos
    adj_list2[nodo] = vecinos2  # 'nodo' es la llave para los valores de la lista 'vecinos2',
    # que contienen los vecinos de ese mismo nodo

# PROCESO

# INICIALIZACION DE TODOS LOS ARREGLOS REQUERIDOS

visitados = {}  # Para tener registro de todos los nodos visitados
# distancias = {}  # Diccionario de distancias
vecino = {}  # Diccionario de los vecinos de cada nodo
camino_general = []  # El camino que se recorre del nodo de inicio hasta el ultimo vertice

cola = Queue()  # Inicializamos una cola vacia

for nod in adj_list2.keys():  # Para cada uno de los nodos
    visitados[nod] = 0  # Asumimos que no lo hemos visitado (no hemos pasado por el),
    vecino[nod] = None  # Que no tiene vecinos

nodo_inicio = int(input(f"Ingrese el nodo del que se parte: "))
visitados[nodo_inicio] = 1  # Puesto que es el nodo inicial, se dice que ya lo recorrimos
cola.put(nodo_inicio)  # Agregamos el nodo de inicio a la cola

while not cola.empty():  # Mientras la cola no este vacia
    actual = cola.get()  # Removemos el elemento mas a la izquierda de la cola
    camino_general.append(actual)

    for v in adj_list2[actual]:  # Para cada uno de los vecinos de actual
        if not visitados[v]:  # Checamos si el vertice 'v' (que es vecino de 'actual') ha sido
            # visitado anteriormente o no (si ya lo recorrimos o no)
            visitados[v] = 1  # Si no ha sido visitado, lo marcamos ahora como visitado
            vecino[v] = actual
            # al nodo de inicio sera la distancia del nodo 'actual' al mismo vertice mas uno (ya que
            # 'v' es vecino de 'actual' y por ende esta un nivel mas alejado de 'nodo_inicio')
            cola.put(v)  # Una vez visitado 'v', lo agregamos a la cola


# El camino mas corto del nodo de inicio hacia el nodo objetivo
nodo_ob = int(input(f"Ingrese al que se quiere llegar: "))  # Nodo objetivo
camino = []  # Vector que almacenara la ruta para llegar de nodo_i a nodo_ob
while nodo_ob is not None:
    camino.append(nodo_ob)
    nodo_ob = vecino[nodo_ob]
    # Esto quiere decir que iremos de reversa. Es decir, comenzamos desde el nodo al que queremos
    # llegar, checamos sus vecinos y agregamos

camino.reverse()  # Como el vector estaba al reves, lo volteamos para que quede en orden.

print(f"El camino mas corto es {camino}")
