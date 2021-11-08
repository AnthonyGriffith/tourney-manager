// LIBRERIAS
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
using namespace std;

// ESTRUCTURAS DE DATOS

// Arbol
struct Nodo{
	string nombre;
	int num; //numerador de nodo
	int id; //Identificador de participante
	int puntaje;
	Nodo *der;
	Nodo *izq;
	Nodo *padre;
	int victoria;
	int nivel;
	
};

// Listas


// PROTOTIPOS 

// Arbol
Nodo *crearNodo(int );
void crearArbolPerfecto(Nodo *&, int, int);
void crearArbolTorneo();
void mostrarArbol(Nodo*,int);

// Listas



// VARIABLES GLOBALES

// Arboles
Nodo *raiz = NULL;
int numParticipante = 1;
int idActual = 1;

// Listas

// FUNCIONES



// Arboles

Nodo *crearNodo(int n){
	Nodo *nuevo_nodo = new Nodo();
	nuevo_nodo->nombre = "";
	nuevo_nodo->num = n;
	nuevo_nodo->id = NULL;
	nuevo_nodo->puntaje = NULL;
	nuevo_nodo->der = NULL;
	nuevo_nodo->izq = NULL;
	nuevo_nodo->padre = NULL;
	nuevo_nodo->victoria = 0;
	idActual = idActual + 1;
	nuevo_nodo->nivel = 0;
	
	return nuevo_nodo;
}

void mostrarArbol(Nodo *arbol,int contador){
    if(arbol==NULL){
        return;

    }
    else{
        mostrarArbol(arbol ->der,contador+1);
        for(int i=0;i<contador;i++){
            printf("   ");
        }
        if(arbol->victoria == 0 && arbol->id != NULL ){
            printf("%s\n", arbol->nombre.c_str());
        }else{
            if(arbol->victoria == 2){
                printf("%s\n", arbol->nombre.c_str());
            }else if(arbol->victoria == 1){
                printf("(X)     \n",arbol->nombre.c_str());
            }else{
                printf("P-----\n",arbol->num);
            }
        }
        mostrarArbol(arbol->izq,contador+1);
    }
}

void crearArbolPerfecto(Nodo *&padre, int nivelActual, int nivel){
	
	Nodo *hijo1 = crearNodo(idActual);
	padre->izq = hijo1;
	hijo1->padre = padre;
	
	Nodo *hijo2 = crearNodo(idActual);
	padre->der = hijo2;
	hijo2->padre = padre;
	
	if(nivelActual < nivel){
		crearArbolPerfecto(hijo1, nivelActual + 1, nivel);
		crearArbolPerfecto(hijo2, nivelActual + 1, nivel);
	}else{
		string nombre1;
		int puntuacion1;
		
		printf("Ingrese el nombre del %d participante: ", numParticipante);
		cin.clear();
		cin.sync();
		getline(cin, nombre1);
		
		printf("Ingrese el puntaje inicial de %s : ", nombre1.c_str());
		cin.clear();
		cin.sync();
		cin >> puntuacion1;
		
		hijo1->nombre = nombre1;
		hijo1->id = numParticipante;
		hijo1->puntaje = puntuacion1;
		hijo1->nivel = nivel;

		numParticipante = numParticipante + 1;
		
		string nombre2;
		int puntuacion2;
		
		printf("Ingrese el nombre del %d participante: ", numParticipante);
		cin.clear();
		cin.sync();
		getline(cin, nombre2);
		
		printf("Ingrese el puntaje inicial de %s : ", nombre2.c_str());
		cin.clear();
		cin.sync();
		cin >> puntuacion2;
	
		hijo2->id = numParticipante;
		hijo2->nombre = nombre2;
		hijo2->puntaje = puntuacion2;
		hijo2->nivel = nivel;

		numParticipante = numParticipante + 1;
		
	}
}

void crearArbolTorneo(){
	int numParticipantes;
	int cont = 1;
	int bandera = false;
	cout << "Indique el tamaño del torneo, dicho numero debe ser una potencia de 2, ejemplo 2,4,8,16, etc...\n";
	cin >> numParticipantes;
	while(true){
		if(pow(2, cont) == numParticipantes){
			bandera = true;
			break;
		}else{
			if(cont > numParticipantes){
				bandera = false;
				cout << "El tamaño del torneo no es valido..." << endl;
				break;
			}
			cont = cont + 1;	
		}
	}
	if(!bandera){
		crearArbolTorneo();
	}else{
		cout << "Creando estructura del torneo..."<< endl;
		int nivel = log2(numParticipantes);
		Nodo *nuevoNodo = crearNodo(idActual);
		raiz = nuevoNodo;
		crearArbolPerfecto(raiz, 0, nivel-1);
		mostrarArbol(raiz,0);
		cout <<""<< endl;
		
	}
	
}


//MENU

void Menu(){

	
	int dato, opcion;
	do{
		opcion = 0;
		cout << "INGRESE UNA DE LAS OPCIONES:\n";
		cout << "1. Ingresar ganador partida\n";
		cout << "2. Choque de contendientes\n";
		cout << "3. Puntaje más alto posible si queda campeón\n";
		cout << "4. Mostrar llave\n";
		cout << "5. Mostrar contendientes por puntaje\n";
		cout << "6. Terminar el programa\n";
		cout << "-> ";
		cin >> opcion;
				
	
				
		switch(opcion){
			case 1:	
				
				break;
			case 2:
			
				break;
			case 3:
				
				
				break;
			case 4: 
				mostrarArbol(raiz, 0);
				break;
			case 5:
				
				break;
			default:
				cout << "Opcion no valida" << endl;
				break;
		}
		system("pause");
		system("cls");
		
		
	}while(opcion != 6);
	cout << "Programa finalizado." << endl;
}

//MAIN

int main(){
	try{
		//Menu();
		crearArbolTorneo();
		Nodo *jugador4 = crearNodo(NULL);
		
		cout << jugador4->nombre.c_str();
		Menu();
		
		getch();
		return 0;
	}catch(...){
		Menu();
		getch();
		return 0;
	}
	
}
