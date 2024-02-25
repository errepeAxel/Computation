#include <iostream>
#include<bits/stdc++.h>
#include<time.h> // Libreria para generar numeros al azar
#include <vector>

using namespace std;  // Utilizamos el espacio de trabajo estandar 

vector<int>lista_adyacencia;

int main() {
	int nodos, nodo_i, nodo_ob, s;  
  	int i, j;  // Variabkes contadoras
  	int conex, n_conexiones=0;
  	
  	srand(time(NULL));  // Para poder obtener numeros aleatorios
  
  	cout<<"Inserte el numero de nodos de la red: ";
  	cin>>nodos;
  
  	// Input de la tabla de adyacencia 
  	int ad_table[nodos][nodos]; // ad_table es una variable con 'nodos' columnas con datos de tipo int
  	
  	//Declaracion de la lista de adyacencia
  	vector<int> ad_list[nodos];
  	
  	int *p1;  // Puntero que apunta hacia la direccion en memoria del elemento en la fila i, columna j 
  	int *p2; // Puntero que apunta hacia el elemento de la i-esima fila y j-esima columna de la matriz de adyacencia
  	int *p3; // Puntero que apunta hacia el elemento de la j-esima fila y i-esima columna de la matriz de adyacencia
  	
  	// LLENADO DE MATRIZ CON NUMEROS ALEATORIOS
  	// Se requiere de una matriz con numero aleatorios para no tener que preguntar dos 
	// veces por la conexion entre dos nodos que con anticipacion ya sabemos tienen una conexion. 
	// Esto debido a que es un grafo no dirigido
	for(i=0; i<nodos; i++){
  		for(j=0; j<nodos; j++){
  			p1 = &ad_table[i][j];
  			*p1 = 1+rand() %1000; // el valor del elemento de la fila i, columna j tendra un 
			  // valor aleatorio desde 0 a 1000
		  }
	  }
	  
	  
	// PROCESO
	for(i=0; i<nodos; i++){
		for(j=0; j<nodos; j++){
			if(ad_table[i][j] != ad_table[j][i]){  //Si los valores de la tabla de adyacencia de la fila
            // j--columna i son diferentes a las de la fila i--columna j
				cout<<"El nodo " <<i<< " tiene una conexion con el nodo " <<j<< "? ";
				cin>>conex; // Input de si existe conecion entre ambos nodos
				p2 = &ad_table[i][j];
				p3 = &ad_table[j][i];
				// Al ser una matriz no dirigida, las celdas j-i e i-j deben tener el mismo valor
				*p2 = conex;
				*p3 = conex;
				if(conex == 1){
					n_conexiones = n_conexiones+1;
					ad_list[i].push_back(j); // Anyadimos a la lista de adyacencia a 'j' en la posicion 'i'
					ad_list[j].push_back(i); // // Anyadimos a la lista de adyacencia a 'i' en la posicion 'j'
				}	
			}else{
				if(j==i){ // Checamos si el nodo j tiene una concexion consigo msimo
					cout<<"El nodo " <<i<< " tiene una conexion con el nodo " <<j<< "? ";
					cin>>conex;
					p2 = &ad_table[i][j];
					p3 = &ad_table[j][i];
					*p2 = conex;
					*p3 = conex;
					if(conex == 1){
						n_conexiones = n_conexiones+1;
						ad_list[i].push_back(j);
						ad_list[j].push_back(i);
					}
				}
			}
		}
	}
	
	
	// INICIALIZACION DE TODOS LOS ARREGLOS REQUERIDOS
	 int visitados[nodos]= {0}; // vector de tamanyo nodos con valores igual a 0, 
	 // indicando que no se ha visitado ningun nodo
	 int *p4; //Puntero que apunta hacia la direccion en memoria de el indice 'nodo_i' 
	
	 int vecinos[nodos]; // Vector 'vecinos' para los vecinos de cada nodo. Se utiliza para encontrar el camino mas corto
	 int *p5; // Puntero que apunta hacia la direccion en memoria de vecinos[nodo_i]
	
	cout<<"Inserte el nodo de donde se parte: ";
	cin>>nodo_i; // Nodo inicial
	int *p6;
	p6 = &nodo_i; // p6 es un puntero que apunta hacia el nodo inicial
	
	int *p7;  // Puntero que se utiliza para apuntar hacia el u-esimo 
	// valor del vector visitados
	int *p8;  // Puntero que se utiliza para apuntar hacia el u-esimo 
	// valor del vector vecinos
	
	p4 = &visitados[nodo_i];
	*p4 = 1;  // mediante la desreferenciacion de p4 le asigamos 1 a el nodo_i-esimo 
	// valor del vector 'visitados'. Esto porque se marca como visitado el nodo fuente
	p5 = &vecinos[nodo_i];
	*p5 = -1;  // mediante la desreferenciacion de p5 le asignamos -1 al nodo_i-esimo valor del vector vecinos,
	// debido a que el nodo base no parte hacia ningun lado, es decir, se toma como si no tuviera parientes.
	
	queue<int> cola;  // Creamos una cola 
	cola.push(*p6);  // Incluimos al nodo inicial al inicio de la cola
	while(!cola.empty()){  // mientras la cola no este vacia 
		int elemento = cola.front();  // 'v' va a ser el elemento que tomamos del principio de la cola
		cola.pop();  // lo removemos de la cola
		for(int u: ad_list[elemento]){  // Para cada uno de los vecinos de 'elemento'
			p7 = &visitados[u]; 
			p8 = &vecinos[u];
			if (!*p7){ // Si no ha sido visitado
				*p7 = 1; // Lo marcamos ahora como visitado
				cola.push(u);  // Ahora incluimos u a la cola 
				*p8 = elemento;  // uno de los vecinos del nodo 'u' va a ser 'elemento'
			}
		}
	}
	
	// ENCONTRAR EL CAMINO MAS CORTO
	cout<<"Inserte el nodo al que se quiere llegar: ";
	cin>>nodo_ob; 

	int actual = nodo_ob; // El nodo que empezaremos evaluando es el nodo objetivo
	
	int *camino;  // puntero que utilizamos como vector
	int *p12;  // p12 apunta hacia la direccion en memoria del f-esimo valor del vector vecinos
	
	camino = new(nothrow) int[nodos]; // En el peor de los casos, el camino mas corto sera igual al numero de nodos de la red
	int f = 0;  // tamanyo final del vector 'camino'
	if(camino == nullptr){
		cout << "Error: no hay memoria suficiente";
	}else{
		while (actual != -1){  //mientras que el nodo que estemos verificando sea distinto de -1. Es decir, mientras que no sea el nodo inicial
			p12 = &camino[f]; 
			*p12 = actual;  // uno de los vecinos del f-esimo elemento es actual
			actual = vecinos[actual];  // actual es uno de los vecinos de actual
			f++;
		}
	}
	
	
	// REVERSIR EL ARREGLO 'camino'
    int camino2[f];  
    int *p13;  // Puntero que apunta a los valores de los vectores 'camino' y 'camino2'

    p13 = &camino[0];  
    for (i = 0; i < f; i++){  
        p13++; // Obtenemos el ultimo valor ddel vector 'camino'
    }  
    p13--; // decrementamos 'p13'
    for ( i = 0; i < f; i++) {  
        camino2[i] = *p13;  // El ultimo valor de 'camino' lo hacemos el primero de 'camino2'; 
		// el penultimo de 'camino', el segundo de 'camino2' y asi sucesivamente
        p13--;  
    }  
    p13 = &camino2[0];  
    for ( i = 0; i < f; i++){  
        camino[i] = *p13;  // Nos regresa 'camino' ahora ordenado
        p13++; 
    }
	
	// IMPRESION A PANTALLA DE CAMINO MAS CORTO  
    p13 = &camino[0]; // p13 guarda la direccion del primer valor de 'camino'        
    for ( i = 0; i < f; i++){  
        cout <<" " << *p13 <<endl;  // Imprime cada elemento del camino
        p13++;  
    }  
	
	// LIBERAR MEMORIA 
	delete[] camino;
}
