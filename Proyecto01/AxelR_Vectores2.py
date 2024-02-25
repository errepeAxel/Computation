# Segundo algoritmo que ordena un vector de menor a mayor

# INPUT DE LOS DATOS DEL VECTOR
vector = []  # Creacion de un vector vacio
tam_vect = int(input(f"Inserte la longitud del vector: "))  # Tamaño del vector

# Insercion de los datos del vector
for i in range(tam_vect):
    elemento = int(input(f"Inserte el elemento {i} del vector: \n"))  # i-esimo elemento del vector
    vector.append(elemento)  # Se agrega al vector

# ORDENAMIENTO DEL VECTOR
orden = 1  # Bandera encendida (igual a 1) cuando siga siendo necesario un ordenamiento
tope = 0  # numero de elementos desordenados - 1. Funciona como tope
while orden == 1:  # Mientras el vector siga desordenado
    orden = 0  # Asumimos que esta ordenado
    tope = tope + 1
    for i in range(0, tam_vect - tope):  # Para cada i-esimo elemento en los indices de 0 al tope del vector - tope
        if vector[i] > vector[i + 1]:  # Si el i-esimo elemento del vector es mayor a su contiguo
            orden = 1  # El vector esta desordenado

            # Intercambiamos los dos elementos
            mayor = vector[i]  # Almacenamos el elemento de mayor valor
            menor = vector[i+1]  # Almacenamos el elemento de mayor valor
            vector[i+1] = mayor  # Se recorre el elemento mayor una posicion
            vector[i] = menor  # El elemento menor retrocede una posicion

print(vector)
