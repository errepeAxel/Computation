// Metodo de Gauss-Seidel

#include<iostream>
#include<iomanip>  // Libreria para usar setw()
#include<cmath>

using namespace std;

int main(){
	cout.precision(4);  // Precision de cuatro numeros despues del punto
	cout.setf(ios::fixed);  // Muestra el punto decimal y los ceros posteriores 
	// para todos los numeros de puntos flotantes, incluso si los decimales no son necesarios.
	
	int n, i, j, k, flag=0, count=0; // Declaracion de variables
	// n almacena el numero de ecuaciones, por lo que debe de ser un numero entero
	// count cuenta el numero de iteraciones de x (cuantas x^count)
	
	cout<< "Ingrese el numero de ecuaciones: ";
	cin>> n;
	cout<<"\n";
	double a[n][n+1];  // Declaracion de la matriz donde se almacenan los coeficientes de las ecuaciones 
	double x[n];  // Declaracion del vector que almacena los valores de las variables
	double tol,y;  // tol para la tolerancia y 'y' es una var temporal
	
	// Llenado de la matriz con los coeficientes de las ecuaciones
	for (i=0; i<n; i++){  // Filas (para cada i-esima ecuacion)
		for (j=0; j<=n; j++){  // Columnas (para cada j-esima variable)
			if(j == n){
				cout<<"Resultado de la ecuacion " <<i+1 <<": ";
				cin>>a[i][j];
				cout<<"\n";
			}else{
				cout<<"Coeficiente de x"<<j+1<<" de la ecuacion "<<i+1<<": ";
				cin>>a[i][j];
			}
		}
	}
	
	// Valores iniciales de cada incognita
	cout<< "Los valores iniciales de cada incognita son: \n";
	for (i=0; i<n; i++){
		x[i] = 0;
		cout<<"x"<<i+1<<"= "<<x[i]<<setw(5);
	}
	cout<<"\n";
	
	// Input de tolerancia 
	cout<< "\nIngrese el valor de tolerancia: ";
	cin>> tol;
	
	// Ordenar la matriz de tal forma que en la diagonal de la misma se encuentren los coeficientes mayores de cada variable
	for (i=0; i<n; i++){ // Para cada i-esima ecuacion
		for (k=i+1; k<n; k++){  // Comparar con la k-esima ecuacion
			if (abs(a[i][i])<abs(a[k][i])){ // si el i-esimo valor de la ecuacion i es menor al i-esimo valor de la ecuacion k
				for (j=0; j<=n; j++){  // Este for ayuda a cambiar toda la ecuacion de lugar (una ecuacion con j-esimas variables)
					double temp = a[i][j]; //temp variable temporal que almacena el valor a intercambiar
					a[i][j]= a[k][j];  // j-esimo elemento de la k-esima ecuacion toma el 
					// lugar del j-esimo elemnto e la ecuacion i (la que tiene un menor coeficiente)
					a[k][j]= temp;
				}
			}
		} 
	}
	
	// Impresion de matriz ordenada 
	cout<<"\n";
	cout<<"Las ecuaciones ordenadas quedan de la siguiente manera: \n";
	for(i=0; i<n; i++){ // Filas
		for(j=0; j<=n; j++){ // Columnas
			if(j == n){
				cout<<"= "<<a[i][j]<<setw(6); //Imprime resultado de la i-esima ecuacion
			}else{
				cout<<a[i][j]<<"x"<<j+1<<setw(6)<<" ";  // Coeficeinte de la j-esima variable
			}
		}
		cout<<"\n";
	}
	
	// Proceso de calcular la aproximacion del valor de cada variable
	cout<<"\nIteracion"<<setw(9); // setw(10) modifica la anchura del campo. Sirve para que el output se vea alineado
	for(i=0; i<n; i++){
		cout<<"x"<<i+1<<setw(18);
	}
	
	do{  // Realiza iteraciones para calcular x1, x2, ..., xn
		cout<<"\n"<<count+1<<"."<<setw(16);
		for(i=0; i<n; i++){
			y = x[i];  // almacena el antiguo valor de x
			x[i]= a[i][n]; // almacena el resultado de la i-esima ecuacion
			for(j=0; j<n; j++){
				if (j!=i){
					x[i] = x[i] - a[i][j]*x[j];
				}
			}
			x[i] = x[i]/a[i][i];
			if (abs(x[i]-y)<=tol){  // Verifica que la diferencia entre cada i-esima solucion 
			// y la soluacion anterior sea menor a la tolerancia
				flag++; // Si es asi, se le suma uno a la bandera
			}
			cout<<x[i]<<setw(18);
		}
		cout<< "\n";
		count++;
	}while(flag<n);  // Si los valores de todas las variables son menores o iguales a la tolerancia, entonces la bandera deberia 
	// ser igual a n (numero de ecuaciones) y detener el ciclo
	cout<<"\nLas soluciones son: \n";
	for (i=0; i<n; i++){
		cout<<"x"<<i+1<<"= "<<x[i]<<"\n";
	}
}
