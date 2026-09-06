#include "Generador.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>

using namespace std;

// Constructor: se ejecuta automáticamente al crear el objeto en el main
Generador::Generador() {
    lecturaArchivos();
}

void Generador::lecturaArchivos() {
    ifstream archivo("nombres.txt");
    if (!archivo.is_open()) {
        cout << "ERROR: No se pudo abrir nombres.txt" << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string nombre;
        while (getline(ss, nombre, ',')) {
            listaNombres.push_back(nombre); 
        }
    }
    archivo.close();
}

void Generador::generarPersonajes(int cantidad) {
    for (int contador = 0; contador < cantidad; contador++) {
        int edad = generarAleatorio(1, 100);
        int coordenadaX = generadorNumberCordenada();
        int coordenadaY = generadorNumberCordenada();
        string nombreAleatorio = generarNombreAleatorio();
        string rangoEtario = intervaloEdad(edad);
        string rut = "Pendiente"; // Puedes agregar lógica de RUT después
        
        // Llamamos al método interno directamente
        imprimirCreacion(coordenadaX, coordenadaY, rangoEtario, edad, rut, nombreAleatorio);
    }
}

void Generador::imprimirCreacion(int x, int y, string rango, int edad, string rut, string nombreAleatorio) {
    cout << "\n====================================" << endl;
    cout << "       REGISTRO CREADO CON EXITO    " << endl;
    cout << "====================================" << endl;
    cout << " Nombre      : " << nombreAleatorio << endl;
    cout << " RUT         : " << rut << endl;
    cout << " Edad        : " << edad << " anos" << endl;
    cout << " Rango       : " << rango << endl;
    cout << " Coordenadas : (" << x << ", " << y << ")" << endl;
    cout << "====================================" << endl;
    cout << " Estado      : ACTIVO" << endl;
    cout << "====================================" << endl;
}

string Generador::intervaloEdad(int edad) {
    if (edad >= 80) return "ANCIANO";
    if (edad >= 50) return "ADULTO MAYOR";
    if (edad >= 18) return "ADULTO JOVEN";
    return "JOVEN";
}

string Generador::generarNombreAleatorio() {
    if (listaNombres.empty()) {
        return "Desconocido"; 
    }
    int indiceAleatorio = generarAleatorio(0, listaNombres.size() - 1);
    return listaNombres[indiceAleatorio]; 
}

int Generador::generadorNumberCordenada() {
    return generarAleatorio(1000, 1824203298);
}

int Generador::generarAleatorio(int minimo, int maximo) {
    static random_device semilla;
    static mt19937 generador(semilla());
    uniform_int_distribution<int> rango(minimo, maximo);
    return rango(generador);
}