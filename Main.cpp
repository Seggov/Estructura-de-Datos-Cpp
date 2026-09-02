#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

const int minimoAdulto = 18;
const string nombre = "Pedrosky Rey del Trosky"; // VARIABLE CONSTANTE

int generarAleatorio(int minimo, int maximo);
int generadorNumberCordenada();
string intervaloEdad(int edad);
void imprimirCreacion(int x,int y,string rango,int edad,string rut,string nombreAleatorio);
void generadorPersonajes(int cantidad); 
void lecturaArchivos(); //Por el momento no lo utilizaremos 
string generarNombreAleatorio();


int main(){
int cantidadGeneraciones = 0;

cout << "Hola, Bienvenido al Generador de usuarios\n";
cout << "Introduce cantidad de Personajes a Generar: ";

cin >> cantidadGeneraciones;

generadorPersonajes(cantidadGeneraciones);

return 0;
}


void generadorPersonajes(int cantidad)
{
for (int contador = 0; contador < cantidad; contador++)
{
    int edad = generarAleatorio(1, 100);

    int coordenadaX = generadorNumberCordenada();
    int coordenadaY = generadorNumberCordenada();

    string nombreAleatorio = generarNombreAleatorio();

    string rangoEtario = intervaloEdad(edad);

    string rut = "";

    imprimirCreacion(
        coordenadaX,
        coordenadaY,
        rangoEtario,
        edad,
        rut,
        nombreAleatorio
    );
}
}


string intervaloEdad(int edad)
{
if (edad >= 80)
{
    return "ANCIANO";
}

if (edad >= 50)
{
    return "ADULTO MAYOR";
}

if (edad >= 18)
{
    return "ADULTO JOVEN";
}

return "JOVEN";
}


void imprimirCreacion(
int x,
int y,
string rango,
int edad,
string rut,
string nombreAleatorio
)
{
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


string generarNombreAleatorio()
{
    if (true)
    {
        return "SIN NOMBRE";
    }

}

int generadorNumberCordenada()
{
return generarAleatorio(1000, 1824203298);
}


int generarAleatorio(int minimo, int maximo)
{
static random_device semilla;
static mt19937 generador(semilla());

uniform_int_distribution<int> rango(minimo, maximo);

return rango(generador);
}

void lecturaArchivos()
{
    ifstream archivo("nombres.txt");

    if (!archivo.is_open()) {
        cout << "ERROR: No se pudo abrir nombres.txt" << endl;
        return;
    }

    string linea;

    while (getline(archivo, linea))
    {
        stringstream ss(linea);

        string nombre;

        getline(ss, nombre, ',');
    }

    archivo.close();
}
