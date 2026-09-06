#include <iostream>
#include "Generador.hpp" // OBLIGATORIO PARA LLAMAR A OTRAS CLASES

using namespace std;

int main() {
    Generador sistema; 
    
    int cantidad = 0;
    cout << "Hola, Bienvenido al Generador de usuarios\n";
    cout << "Introduce cantidad a generar: ";
    cin >> cantidad;
    
    sistema.generarPersonajes(cantidad);
    
    return 0;
}