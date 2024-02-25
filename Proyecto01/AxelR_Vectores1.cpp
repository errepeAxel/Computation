// Algoritmo que que ordena un vector de menor a mayor
// Rodriguez Perez Axel


#include<iostream>  /* libreria (archivo de cabecera) iostream contiene codigo que permite a un programa C++ mostrar 
la salida en la pantalla y leer la entrada del teclado */
#include<new> 
#include <typeinfo>


using namespace std;  // Utilizamos el espacio de trabajo estandar 

int main() {
	int i, j, z;  // Variables auxiliares
	int actual;  // Var. temporal que se utiliza para evaluar un elemento
	int tam_vect;  // Var. que almacena el tamanyo del vector
	int *p2;  // Puntero que apunta a elementos de vector
	int *p1;  // Puntero que apunta hacia 'actual'
	int *p3;  // Puntero que apunta hacia z-esimo elemento del vector
	int *vector;  // vector a ordenar

	
	// INPUT DEL VECTOR
	cout<<"Introduzca el tamanyo del vector: "; 
	cin>> tam_vect; // tamanyo del vector

	vector = new (nothrow) int [tam_vect];  // Creacion de vector dinamico

	// Verificar que sea un puntero valido 
	if (vector == nullptr){
		cout << "Error: no hay memoria suficiente";
	}else{
		p2 = vector;
    	for(z=0; z<tam_vect; z++){
			cout<<"Ingrese el valor del elemento " <<z<<": "; 
			p3 = &vector[z];
      		cin>>*p3; // Input del z-esimoelemento del vector
	  	}
  	}

	// ORDENAMIENTO DEL VECTOR 
	for(i=1; i<tam_vect; i++){ // Para cada elemento del vector
		actual = vector[i]; // el valor a evaluar sera el i-esimo elemento del vector
		p1 = &actual;  // p1 apunta hacia la ubicacion de variable 'actual'
		for(j=i; j > 0 && vector[j-1] > *p1; j--){ // Para el elemento evaluado 'i', si j 
		// mayor a cero Y el elemento anterior a 'i'('j') menor a 'actual'
    		vector[j] = vector[j-1];  // cambiar j a la posicion de de 'actual'
    	}
	vector[j] = *p1; // cambiar a actual a la posicion donde antes estaba el elemento 'j'.
  	}

	// IMPRESION DE VECTOR ORDENADO
	for(i=0; i<tam_vect; i++){
		cout<<*p2<<endl;
    	p2++;
  	}

  //LIBERAR MEMORIA
  delete[] vector;
}
