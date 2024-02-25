# Algoritmo que obtiene el camino más corto entre dos nodos en una red no dirigida

import numpy as np  # Se importa la libreria numpy
import pandas as pd  # Se importa la libreria pandas
from queue import Queue  # Se importa la funcion Queue del modulo queue


# INPUT DE TABLA DE ADYACENCIA
nodos = int(input(f"Inserte el numero de nodos de la red: "))  # Numero de nodos de la red
ad_table = np.random.random((nodos, nodos))  # tabla de adyacencia
ad_table = pd.DataFrame(ad_table)
for i in range(nodos):
    for j in range(nodos):  # Para cada columna i de cada fila j
        if ad_table[j][i] != ad_table[i][j]:  # Si los valores de la tabla de adyacencia de la
            # fila j--columna i son diferentes a las de la fila i--columna j
            conex = int(input(f"El nodo {i} tiene una conexion con el nodo {j}? "))  # Input de si
            # existe conecion entre ambos nodos

            # Al ser una matriz no dirigida, las celdas j-i e i-j deben tener el mismo valor
            ad_table[j][i] = conex
            ad_table[i][j] = conex
        else:
            if j == i:  # Si estamos checando si el nodo j tiene una concexion consigo msimo
                conex = int(input(f"El nodo {i} tiene una conexion con el nodo {j}? "))
                ad_table[j][i] = conex
                ad_table[i][j] = conex


# DEFINICION DE LA CLASE NODO
class Nodo():
    def __init__(self, matriz, n_nodos, nodo_id):
        self.matriz = pd.DataFrame(matriz)  # Matriz de adyacencia del grafo al que pertenece el nodo
        self.n_nodos = int(n_nodos)  # Numero de nodos en esa matriz
        self.nodo_id = int(nodo_id)  # Nombre del nodo

    def Vecinos(self):
        vecinos = []  # Vector donde se lamacenan todos los nodos vecinos de nodo_id
        n_nodos2 = self.n_nodos  # Numero de nodos en el grafo
        nodo_id2 = self.nodo_id  # Nombre del grafo del que se requiere los vecinos
        for i in range(n_nodos2):  # Para cada uno de los nodos
            if self.matriz[nodo_id2][i] == 1:  # Si su interseccion en la matriz de adyacencia con nodo_id es igual a 1
                vecinos.append(i)  # Quiere decir que son vecinos. Se agrega el nodo i al vector de vecinos
        return vecinos


lista_adyacencia = {}  # 'lista_adyacencia' sera un diccionario en el que se almacenara la
# informacion de los vecinos de cada uno de los nodos del grafo
for n in range(nodos):  # Para cada uno de los nodos
    nodo = Nodo(matriz=ad_table, n_nodos=nodos, nodo_id=n)  # Se crea un objeto llamado nodo
    nodo_name = n  # Se le da nombre a ese nodo. Estos nombres seran las llaves del diccionario
    lista_adyacencia[nodo_name] = nodo.Vecinos()  # Se aplica la funcion 'Vecinos' al nodo 'nodo' con
    # el objetivo de guardar estos valores en el diccionario de 'lista_adyacencia'


# PROCESO

# Inicializacion de todos los arreglos requeridos

visitados = {}  # Para tener registro de todos los nodos visitados
distancias = {}  # Diccionario de distancias
vecino = {}  # Diccionario de los vecinos de cada nodo
camino_general = []  # El camino que se recorre del nodo de inicio hasta el ultimo vertice

cola = Queue()  # Inicializamos una cola vacia

for nod in lista_adyacencia.keys():  # Para cada uno de los nodos
    visitados[nod] = False  # Asumimos que no lo hemos visitado (no hemos pasado por el)
    vecino[nod] = None  # Que no tiene parientes
    distancias[nod] = -1  # Que su distancia es de -1. Esto solo para tener un orden

nodo_inicio = int(input(f"Ingrese el nodo del que se parte: "))
visitados[nodo_inicio] = True  # Puesto que es el nodo inicial, se dice que ya lo recorrimos
distancias[nodo_inicio] = 0  # La distancia de un nodo a si mismo es 0
cola.put(nodo_inicio)  # Agregamos el nodo de inicio a la cola

while not cola.empty():  # Mientras la cola no este vacia
    actual = cola.get()  # Removemos el elemento mas a la izquierda de la cola
    camino_general.append(actual)

    for v in lista_adyacencia[actual]:  # Para cada uno de los vecinos de actual
        if not visitados[v]:  # Checamos si el vertice 'v' (que es vecino de 'actual') ha sido visitado
            # anteriormente o no (si ya lo recorrimos o no)
            visitados[v] = True  # Si no ha sido visitado, lo marcamos ahora como visitado
            vecino[v] = actual
            distancias[v] = distancias[actual] + 1  # Esto quiere decir que la distancia de 'v' al
            # nodo de inicio sera la distancia del nodo 'actual' al mismo vertice mas uno (ya que 'v' es
            # vecino de 'actual' y por ende esta un nivel mas alejado de 'nodo_inicio')
            cola.put(v)  # Una vez visitado 'v', lo agregamos a la cola

# El camino mas corto del nodo de inicio hacia el nodo objetivo
nodo_ob = int(input(f"Ingrese al que se quiere llegar: "))  # Nodo objetivo
camino = []  # Vector que almacenara la ruta para llegar de nodo_inico a nodo_ob
while nodo_ob is not None:  # Se rompe cuando nodo_ob es igual a None, ya que el valor en el que la
    # llave es el nodo de inicio es igual, justamente, a None. Esto debido a que como no entro en el
    # condicional de 'if no visitados[v]', no se le asigno ningun valor.
    camino.append(nodo_ob)
    nodo_ob = vecino[nodo_ob]
    # Esto quiere decir que iremos de reversa. Es decir, comenzamos desde el nodo al que
    # queremos llegar, checamos sus vecinos y agregamos

camino.reverse()  # Como el vector estaba al reves, lo volteamos para que quede en orden.

print(f"El camino mas corto es {camino}")
