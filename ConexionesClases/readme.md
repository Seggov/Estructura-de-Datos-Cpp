# Unidad 03: Programación Orientada a Objetos y Conexiones entre Clases en C++

En Estructura de Datos, la Programación Orientada a Objetos (POO) permite encapsular la complejidad interna de las estructuras (nodos, punteros de control, balanceo) y ofrecer al usuario una interfaz limpia y segura (`insertar()`, `eliminar()`, `buscar()`).

---

## Índice
1. [Clases vs Structs en C++](#1-clases-vs-structs-en-c)
2. [Modularización: Separación `.hpp` y `.cpp`](#2-modularización-separación-hpp-y-cpp)
3. [Constructores y Destructores](#3-constructores-y-destructores)
4. [Encapsulamiento y Modificadores de Acceso](#4-encapsulamiento-y-modificadores-de-acceso)
5. [Relaciones y Conexiones entre Clases](#5-relaciones-y-conexiones-entre-clases)
   - [Asociación](#asociación)
   - [Agregación](#agregación)
   - [Composición (Patrón Contenedor - Nodo)](#composición-patrón-contenedor---nodo)
   - [Herencia y Polimorfismo](#herencia-y-polimorfismo)
6. [El Puntero `this` y Operador Flecha `->`](#6-el-puntero-this-y-operador-flecha--)
7. [Ejemplo Completo Modularizado](#7-ejemplo-completo-modularizado)

---

## 1. Clases vs Structs en C++

En C++, la única diferencia técnica entre `class` y `struct` es la visibilidad por defecto:

* En un **`struct`**, todos los miembros son `public` por defecto. Se usa convencionalmente para estructuras simples de datos pasivos (como un `Nodo`).
* En una **`class`**, todos los miembros son `private` por defecto. Se usa para encapsular lógica de negocio y estructuras de datos complejas.

```cpp
// Estructura pasiva común para Nodos
struct Nodo {
    int dato;
    Nodo* siguiente;

    Nodo(int valor) : dato(valor), siguiente(nullptr) {}
};

// Clase que gestiona y encapsula la estructura
class Lista {
private:
    Nodo* cabeza; // Solo accesible internamente
public:
    Lista();
    ~Lista();
    void insertar(int valor);
};
```

---

## 2. Modularización: Separación `.hpp` y `.cpp`

Para proyectos profesionales y certámenes, el código se divide en dos archivos:

1. **Archivo de Cabecera (`.hpp` o `.h`)**: Contiene la **declaración** de la clase, atributos y prototipos de métodos. Utiliza `#pragma once` para evitar inclusiones duplicadas.
2. **Archivo Fuente (`.cpp`)**: Contiene la **implementación** de los métodos usando el operador de resolución de ámbito `::`.

```cpp
// Persona.hpp
#pragma once
#include <string>

class Persona {
private:
    std::string nombre;
    int edad;

public:
    Persona(std::string nombre, int edad);
    void presentarse() const;
    int getEdad() const;
};
```

```cpp
// Persona.cpp
#include "Persona.hpp"
#include <iostream>

Persona::Persona(std::string nombre, int edad) : nombre(nombre), edad(edad) {}

void Persona::presentarse() const {
    std::cout << "Hola, soy " << nombre << " y tengo " << edad << " anos." << std::endl;
}

int Persona::getEdad() const {
    return edad;
}
```

---

## 3. Constructores y Destructores

* **Constructor (`Clase()`)**: Se ejecuta automáticamente cuando el objeto se instancia. Inicializa punteros a `nullptr` y reserva recursos.
* **Destructor (`~Clase()`)**: Se ejecuta automáticamente cuando el objeto sale de ámbito o se le aplica `delete`. **Es indispensable en Estructuras de Datos para liberar todos los nodos enlazados del Heap**, evitando fugas de memoria (*memory leaks*).

```cpp
class GestorMemoria {
private:
    int* buffer;
public:
    GestorMemoria(int tamano) {
        buffer = new int[tamano];
    }

    ~GestorMemoria() {
        delete[] buffer; // Libera memoria al destruirse el objeto
    }
};
```

---

## 4. Encapsulamiento y Modificadores de Acceso

| Modificador | Acceso dentro de la Clase | Clases Hijas (Subclases) | Código Externo |
| :--- | :---: | :---: | :---: |
| `public` | Sí | Sí | Sí |
| `protected` | Sí | Sí | No |
| `private` | Sí | No | No |

---

## 5. Relaciones y Conexiones entre Clases

### Asociación
Dos clases se conocen e interactúan, pero sus ciclos de vida son completamente independientes.
```cpp
class Medico;

class Paciente {
    Medico* medicoCabecera; // Apunta a un médico, pero si el paciente muere, el médico sigue existiendo
};
```

### Agregación
Relación del tipo "tiene un" (*has-a* débil). Una clase contiene referencias a otras, pero los objetos contenidos existen fuera del contenedor.
```cpp
class Curso {
    vector<Estudiante*> alumnosInscritos; // Si el curso se cierra, los estudiantes siguen vivos
};
```

### Composición (Patrón Contenedor - Nodo)
Relación del tipo "posee fuertemente". El objeto contenedor es dueño absoluto de los objetos contenidos. Si el contenedor se destruye, los componentes se destruyen con él.
```cpp
class ListaEnlazada {
private:
    struct Nodo {
        int valor;
        Nodo* sig;
    };
    Nodo* primero;

public:
    ~ListaEnlazada() {
        // Al morir la lista, DESTRUYE todos sus nodos
        Nodo* actual = primero;
        while (actual != nullptr) {
            Nodo* aBorrar = actual;
            actual = actual->sig;
            delete aBorrar;
        }
    }
};
```

### Herencia y Polimorfismo
Permite especializar clases base. Siempre se debe marcar el destructor base como `virtual`.

```cpp
class EstructuraLineal {
public:
    virtual void insertar(int valor) = 0; // Método virtual puro (interfaz)
    virtual ~EstructuraLineal() {}        // Destructor virtual obligatorio
};

class Pila : public EstructuraLineal {
public:
    void insertar(int valor) override {
        // Implementación LIFO (push)
    }
};
```

---

## 6. El Puntero `this` y Operador Flecha `->`

* `this`: Puntero implícito que apunta a la instancia actual del objeto sobre la cual se está ejecutando el método.
* Operador `->`: Desreferencia y accede a miembros de un puntero a objeto (`ptr->metodo()` equivale a `(*ptr).metodo()`).

---

## 7. Ejemplo Completo Modularizado

```cpp
#include <iostream>
#include <string>

using namespace std;

class CuentaBancaria {
private:
    string titular;
    double saldo;

public:
    CuentaBancaria(string titular, double saldoInicial) {
        this->titular = titular;
        this->saldo = saldoInicial;
    }

    void depositar(double monto) {
        if (monto > 0) saldo += monto;
    }

    bool retirar(double monto) {
        if (monto > 0 && saldo >= monto) {
            saldo -= monto;
            return true;
        }
        return false;
    }

    void mostrarEstado() const {
        cout << "Titular: " << titular << " | Saldo actual: $" << saldo << endl;
    }
};

int main() {
    // Instanciación en Stack
    CuentaBancaria cuenta1("Carlos Santana", 1500.0);
    cuenta1.depositar(500.0);
    cuenta1.mostrarEstado();

    // Instanciación dinámica en Heap
    CuentaBancaria* cuenta2 = new CuentaBancaria("Ana Lopez", 3000.0);
    cuenta2->retirar(1000.0);
    cuenta2->mostrarEstado();
    delete cuenta2; // Liberación obligatoria

    return 0;
}
```
