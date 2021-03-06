// mazo.cpp
// Definici�n de la clase Mazo

#include "mazo.h"

// Constructor
// Inicializa el naipe con las cartas 
Mazo::Mazo() : naipe(nullptr), primera(0) {
	inicializar();
}

// Destructor
// Libera toda la memoria asignada al Mazo
Mazo::~Mazo() {
	limpiar();
}

// Inicializa un Mazo 
void Mazo::inicializar() {
	int maxCartas = 0;

	naipe = new Carta*[NUMCARTAS];

	// Inicializamos el mazo de cartas
	// 13 cartas por cada palo y todas boca abajo
	while (maxCartas < NUMCARTAS) {

		for (int i = 0; i < MAX_PALOS; ++i)
			for (int j = 1; j <= MAX_RANGO; ++j)
				naipe[maxCartas++] = new Carta(Rango(j), Palo(i), false);
	}
}

// Toma el mazo y desordena las cartas movi�ndolas en diferentes posiciones del vector de manera aleatoria
// Utiliza la funci�n de la librer�a est�ndar 'shufle' para tal fin
void Mazo::barajar() {
	// Utilizado para generar un n�mero aleatorio no determin�stico (depende de la implementaci�n)
	// No recomendado si la portabilidad es importante
	// Soluci�n no �ptima para generar n�meros pseudoaleatorios (PRNG)
	std::random_device rd;
	std::default_random_engine generador(rd());

	std::shuffle(naipe, naipe + NUMCARTAS, generador);
}

void Mazo::limpiar() {
	// Eliminamos todas las cartas del mazo. Hay que cuidar de no intentar una posici�n en donde no exista un apuntador
	// Las cartas se fueron sacando del mazo
	for (int i = primera; i < NUMCARTAS; ++i)
		if (naipe[i] != nullptr)
			delete naipe[i];

	delete[] naipe;
	naipe = nullptr;
	primera = 0;
}

// Funci�n que obtiene la direcci�n de memoria de la primera carta del mazo y la retorna
// La posici�n del vector en donde se encontraba la carta se marca como 'nullptr'
// La siguiente carta del mazo se convierte en la primera
Carta* Mazo::tomarCarta() {
	Carta* tmp = naipe[primera];
	naipe[primera++] = nullptr;
	
	return tmp;
}