#pragma once
#include <string>
#include <vector>

class Generador {
private:
    // Atributos (Tus antiguas variables globales)
    const int minimoAdulto = 18;
    const std::string nombre = "Pedrosky Rey del Trosky";
    std::vector<std::string> listaNombres;

    // Métodos internos (solo la clase los usa)
    void lecturaArchivos();
    int generarAleatorio(int minimo, int maximo);
    int generadorNumberCordenada();
    std::string generarNombreAleatorio();
    std::string intervaloEdad(int edad);
    void imprimirCreacion(int x, int y, std::string rango, int edad, std::string rut, std::string nombreAleatorio);

public:
    // Constructor y método principal
    Generador();
    void generarPersonajes(int cantidad);
};