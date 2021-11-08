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
Nodo* jugadorBuscado = NULL;

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
            printf("(%d)%s\n", arbol->id, arbol->nombre.c_str());
        }else{
            if(arbol->victoria == 2){
                printf("(%d)%s\n", arbol->id, arbol->nombre.c_str());
            }else if(arbol->victoria == 1){
                printf("(X)%s     \n",arbol->nombre.c_str());
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
	cout << "Indique la cantidad de participantes del torneo\nNOTA: dicho numero debe ser una potencia de 2, ejemplo 2,4,8,16, etc...\n--> ";
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

void buscarJugador(Nodo *arbol, int id){ // Secundaria
	if(arbol == NULL){
		
	}else{
		if(arbol->id == id && arbol->victoria == 0){
			jugadorBuscado = arbol;
		}
		buscarJugador(arbol->izq, id);
		buscarJugador(arbol->der, id);
	}
}

Nodo *buscarContrincante(Nodo * arbol){ // Secundaria
	if(arbol->padre->izq->num == arbol->num){
		return arbol->padre->der;
	}
	return arbol->padre->izq;
}

void ganadorPartida(int id){
	buscarJugador(raiz, id);
	Nodo *jugador = jugadorBuscado;
	Nodo *contrincante = buscarContrincante(jugador);
	if (contrincante->id == NULL){
		cout << "No hay contrincante aun" << endl;	
	}else if(jugador->padre == NULL){
		cout << "Ya el torneo tiene un ganador!" << endl;
	}else{
		// Movemos al ganador al siguiente bracket
		jugador->padre->id = jugador->id;
		jugador->padre->nombre = jugador->nombre;
		
		// Recalculamos el puntaje
		jugador->padre->puntaje = jugador->puntaje + 1 + (contrincante->puntaje/jugador->puntaje);
		
		// Indicamos resultados
		contrincante->victoria = 1;
		jugador->victoria = 2;
		printf("\n-----------------------------\n");
		//Mostramos en pantalla
		printf("%s ha ganado su encuentro correctamente\nEl estado actual del torneo es el siguiente:\n\n", jugador->nombre.c_str());
		mostrarArbol(raiz, 0);
		printf("\n-----------------------------\n");
		if(jugador->padre->padre == NULL){
			printf("El ganador del torneo es... %s con %d puntos!!!\n", jugador->padre->nombre.c_str(), jugador->padre->puntaje);
		}
		
	}
	
}

void completarRama(Nodo* rama){ // Secundaria
	Nodo *hijoIzq = rama->izq;
	Nodo *hijoDer = rama->der;
	if(hijoIzq->id == NULL){
		completarRama(hijoIzq);
	}
	if(hijoDer->id == NULL){
		completarRama(hijoDer);
	}
	int puntajeIzquierda = hijoIzq->puntaje + (hijoDer->puntaje/hijoIzq->puntaje); 
	int puntajeDerecha = hijoDer->puntaje + (hijoIzq->puntaje/hijoDer->puntaje); 
	if(puntajeIzquierda < puntajeDerecha){
		ganadorPartida(hijoDer->id);
	}else{
		ganadorPartida(hijoIzq->id);
	}
}

void ganarHastaNivel(Nodo *jugador, int nivel){ // Secundaria
	while(jugador->nivel > nivel){
		Nodo *contrincante = buscarContrincante(jugador);
		if(contrincante->id == NULL){
			completarRama(contrincante);	
		}
		ganadorPartida(jugador->id);

		jugador = jugador->padre;
	}
}

void choqueContendientes(int id1, int id2){

	buscarJugador(raiz, id1);
	Nodo *contendiente1 = jugadorBuscado;
	
	buscarJugador(raiz, id2);
	Nodo *contendiente2 = jugadorBuscado;
	
	while(contendiente2->padre != contendiente1->padre){
		
		if(contendiente1->nivel > contendiente2->nivel){ // El contendiente 1 necesita realizar partidas
			ganarHastaNivel(contendiente1, contendiente2->nivel); 
		}else if(contendiente1->nivel < contendiente2->nivel){ // El contendiente 1 necesita realizar partidas
			ganarHastaNivel(contendiente2, contendiente1->nivel);
		}else{ // Ambos necesitan realizar partidas
			Nodo *contrincante = buscarContrincante(contendiente1);
			if(contrincante->id == NULL){ //Si aun no hay un contrincante, se busca uno
				completarRama(contrincante); 	
			}
			ganadorPartida(contendiente1->id);
			contendiente1 = contendiente1->padre;
			
			contrincante = buscarContrincante(contendiente2);
			if(contrincante->id == NULL){ //Si aun no hay un contrincante, se busca uno
				completarRama(contrincante);
			}
			ganadorPartida(contendiente2->id);
			contendiente2 = contendiente2->padre;
		}
		buscarJugador(raiz, id1);
		contendiente1 = jugadorBuscado;
	
		buscarJugador(raiz, id2);
		contendiente2 = jugadorBuscado;	
	}
	
	cout << "Los contendientes estan listos para enfrentarse.\n\n" << endl;
}

void puntajeMasAlto(int id){
	buscarJugador(raiz, id);
	Nodo *jugador = jugadorBuscado;
	while(jugador->padre != NULL){
		Nodo *contrincante = buscarContrincante(jugador);
		if(contrincante->id != NULL){ // Si hay un contrincante, hacemos que el jugador gane
			ganadorPartida(jugador->id);
			jugador = jugador->padre;
		}else{ // Si no, se consigue el un rival 
			completarRama(contrincante); // Este metodo consigue el rival con mayor puntos posibles
		}
	}
	printf("El maximo puntaje obtenido por el jugador es de: %d puntos\n",jugador->puntaje);
};

//MENU

void Menu(){

	int dato, opcion;
	do{
		opcion = 0;
		cout << "INGRESE UNA DE LAS OPCIONES:\n";
		cout << "1. Ingresar ganador partida\n";
		cout << "2. Choque de contendientes\n";
		cout << "3. Puntaje mas alto posible si queda campeon\n";
		cout << "4. Mostrar llave\n";
		cout << "5. Mostrar contendientes por puntaje\n";
		cout << "6. Terminar el programa\n";
		cout << "-> ";
		cin >> opcion;
				
	
				
		switch(opcion){
			case 1:	
				cout<<"Id del jugador: ";
				cin>>dato;
				ganadorPartida(dato);
				break;
				break;
			case 2:
				int jug1;
				int jug2;
				
				cout << "Id del primer contendiente: ";
				cin >> jug1;
				cout << "\n";
				
				cout <<"Id del segundo contendiente: ";
				cin >> jug2;
				cout<<"\n";
				
				choqueContendientes(jug1, jug2);
				break;
			case 3:
				int id;
				cout << "Id del jugador: ";
				cin >> id;
				puntajeMasAlto(id);
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
