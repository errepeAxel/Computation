# Primer algoritmo que ordena un vector de menor a mayor

# INPUT DE LOS DATOS DEL VECTOR
vector = []  # Creacion de un vector vacio
tam_vect = int(input(f"Inserte la longitud del vector: "))  # Tamaño del vector

# Insercion de los datos del vector
for i in range(tam_vect):
    elemento = int(input(f"Inserte el elemento {i} del vector: \n"))  # i-esimo elemento del vector
    vector.append(elemento)  # Se agrega al vector

# ORDENAMIENTO DEL VECTOR
for i in range(1, tam_vect):
    actual = vector[i]  # tomamos el i-esimo elemento del vector
    j = i  # j es una var. temporal

    # Desplazamiento de los elementos
    while j > 0 and vector[j-1] > actual:  # mientras el elemento anterior a 'actual' (i-esimo elemento)
        # sea mayor que este
        vector[j] = vector[j-1]  # recorremos hacia adelante ese elemento (el anterior a 'actual')
        j = j-1  # se le resta 1 a 'j' debido a que ahora este será el índice del recorrido hacia atras
        # elemento 'actual'

    # Insertar el elemento en su lugar
    vector[j] = actual  # El desplazado elemento 'actual' toma su nuevo lugar en el j-esimo indice del vector
print(vector)
