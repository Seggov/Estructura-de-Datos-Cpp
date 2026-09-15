# Unidad 02: Lectura y Escritura de Archivos en C++

> 📍 **Navegación:** [🏠 Menú Principal](../README.md) \| [📘 Guía Prueba 1](../Prueba_1/README.md) \| [📙 Guía Prueba 2](../Prueba_2/README.md)

---


## Índice
1. [Librerías y Flujos: `<fstream>`](#1-librerías-y-flujos-fstream)
2. [Apertura y Verificación de Archivos](#2-apertura-y-verificación-de-archivos)
3. [Lectura Línea por Línea: `std::getline`](#3-lectura-línea-por-línea-stdgetline)
4. [Tokenización y Parseo con `<sstream>`](#4-tokenización-y-parseo-con-sstream)
5. [Conversión de Tipos: `stoi`, `stod`, `stof`](#5-conversión-de-tipos-stoi-stod-stof)
6. [Escritura de Archivos: `ofstream`](#6-escritura-de-archivos-ofstream)
7. [Patrón de Carga para Estructuras de Datos](#7-patrón-de-carga-para-estructuras-de-datos)
8. [Buenas Prácticas y Errores Habituales](#8-buenas-prácticas-y-errores-habituales)

---

## 1. Librerías y Flujos: `<fstream>`

C++ provee tres clases clave en el encabezado `<fstream>`:

| Clase | Propósito | Operación |
| :--- | :--- | :--- |
| `std::ifstream` | *Input File Stream* | Leer datos desde un archivo |
| `std::ofstream` | *Output File Stream* | Escribir datos hacia un archivo (crea o sobreescribe) |
| `std::fstream` | *File Stream* | Lectura y escritura simultánea |

---

## 2. Apertura y Verificación de Archivos

Siempre se debe comprobar si el archivo fue abierto con éxito antes de intentar cualquier operación de lectura o escritura.

```cpp
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream archivo("datos.txt");

    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo datos.txt. Verifica que la ruta sea correcta." << endl;
        return 1;
    }

    // Procesar archivo...

    archivo.close(); // Siempre cerrar el archivo al terminar
    return 0;
}
```

### Modos de apertura comunes:
* `ios::in`: Abre en modo lectura (por defecto en `ifstream`).
* `ios::out`: Abre en modo escritura (por defecto en `ofstream`, trunca el archivo si ya existe).
* `ios::app`: *Append*, añade el nuevo contenido al final del archivo sin borrar lo anterior.
* `ios::binary`: Abre en modo binario en lugar de texto.

---

## 3. Lectura Línea por Línea: `std::getline`

La función `getline(archivo, linea)` lee una línea completa hasta encontrar un salto de línea (`\n`).

```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void leerTodoElArchivo(const string& ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) return;

    string linea;
    int numeroLinea = 1;

    // El while continúa mientras haya líneas disponibles para leer
    while (getline(archivo, linea)) {
        cout << "Linea " << numeroLinea++ << ": " << linea << endl;
    }

    archivo.close();
}
```

---

## 4. Tokenización y Parseo con `<sstream>`

En certámenes y talleres, la información suele venir separada por comas (CSV), punto y coma (`;`) o barras (`|`). Ejemplo de archivo `pacientes.txt`:
```text
12345678-9,Juan Perez,35,Urgencias
98765432-1,Maria Soto,22,Consulta
```

Para separar cada campo de la línea usamos `std::stringstream`:

```cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Paciente {
    string rut;
    string nombre;
    int edad;
    string motivo;
};

vector<Paciente> cargarPacientes(const string& ruta) {
    vector<Paciente> lista;
    ifstream archivo(ruta);

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir " << ruta << endl;
        return lista;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue; // Omitir líneas en blanco

        stringstream ss(linea);
        string rut, nombre, edadStr, motivo;

        // Leer campos separados por delimitador ','
        getline(ss, rut, ',');
        getline(ss, nombre, ',');
        getline(ss, edadStr, ',');
        getline(ss, motivo, ',');

        Paciente p;
        p.rut = rut;
        p.nombre = nombre;
        p.edad = stoi(edadStr); // Convertir string a entero
        p.motivo = motivo;

        lista.push_back(p);
    }

    archivo.close();
    return lista;
}
```

---

## 5. Conversión de Tipos: `stoi`, `stod`, `stof`

| Función | Tipo de Destino | Ejemplo |
| :--- | :--- | :--- |
| `std::stoi(str)` | `int` (entero) | `int edad = stoi("28");` |
| `std::stod(str)` | `double` (decimal de doble precisión) | `double precio = stod("19.99");` |
| `std::stof(str)` | `float` (decimal de precisión simple) | `float peso = stof("75.4");` |
| `std::to_string(val)` | `std::string` | `string s = to_string(100);` |

---

## 6. Escritura de Archivos: `ofstream`

Permite guardar reportes, resultados de algoritmos o estados finales de estructuras de datos.

```cpp
#include <iostream>
#include <fstream>
using namespace std;

void guardarReporte(const string& ruta) {
    // Abre en modo append para no sobreescribir el historial
    ofstream salida(ruta, ios::app);

    if (!salida.is_open()) {
        cerr << "Error al abrir para escritura." << endl;
        return;
    }

    salida << "===============================" << endl;
    salida << "REPORTE DE EJECUCION" << endl;
    salida << "Total de nodos procesados: 45" << endl;
    salida << "Estado: EXITOSO" << endl;
    salida << "===============================" << endl;

    salida.close();
}
```

---

## 7. Patrón de Carga para Estructuras de Datos

Al trabajar con clases contenedoras (como `ListaEnlazada`, `Grafo` o `Arbol`), el patrón estándar es tener un método `cargarDesdeArchivo(ruta)`:

```cpp
class GestorPersonas {
private:
    vector<string> nombres;

public:
    void cargarNombres(const string& rutaArchivo) {
        ifstream archivo(rutaArchivo);
        if (!archivo.is_open()) {
            cout << "ERROR: Archivo no disponible." << endl;
            return;
        }

        string linea;
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string item;
            while (getline(ss, item, ',')) {
                nombres.push_back(item);
            }
        }
        archivo.close();
    }
};
```

---

## 8. Buenas Prácticas y Errores Habituales

1. **Rutas relativas**: Si ejecutas desde la terminal o el IDE, asegúrate de que el archivo `.txt` esté en el directorio de trabajo actual (*Working Directory*).
2. **Líneas vacías al final**: Siempre valida `if (linea.empty()) continue;` para evitar excepciones por `stoi("")`.
3. **No cerrar el archivo**: Si no llamas a `close()`, los búferes pueden quedar sin vaciar (*flush*) en el disco.
4. **Validación de delimitadores faltantes**: Si una fila está corrupta o incompleta, `stoi` lanzará `std::invalid_argument`.
