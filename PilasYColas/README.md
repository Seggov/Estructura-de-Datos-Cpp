# Unidad 06: Pilas (Stacks) y Colas (Queues) en C++

Las Pilas y las Colas son **Tipos Abstractos de Datos (TAD)** lineales con restricciones de acceso: no permiten insertar o eliminar elementos en posiciones arbitrarias, sino únicamente por sus extremos.

---

## Índice
1. [Pila (Stack) - Principio LIFO](#1-pila-stack---principio-lifo)
   - [Operaciones Primitivas](#operaciones-primitivas)
   - [Implementación Manual con Nodos ($O(1)$)](#implementación-manual-con-nodos-o1)
   - [Uso con la STL (`std::stack`)](#uso-con-la-stl-stdstack)
2. [Cola (Queue) - Principio FIFO](#2-cola-queue---principio-fifo)
   - [Operaciones Primitivas](#operaciones-primitivas-1)
   - [Implementación Manual con Punteros `front` y `rear`](#implementación-manual-con-punteros-front-y-rear)
   - [Uso con la STL (`std::queue`)](#uso-con-la-stl-stdqueue)
3. [Cola Circular con Arreglos](#3-cola-circular-con-arreglos)
4. [Problemas Típicos de Certamen](#4-problemas-típicos-de-certamen)
   - [Balanceo de Paréntesis y Símbolos](#balanceo-de-paréntesis-y-símbolos)
5. [Tabla Comparativa de Complejidades](#5-tabla-comparativa-de-complejidades)

---

## 1. Pila (Stack) - Principio LIFO

**LIFO:** *Last In, First Out* (El último en entrar es el primero en salir).
Imagina una pila de platos: solo puedes colocar un plato nuevo en la cima (*top*), y para retirar un plato, debes sacar el de la cima.

```text
    push(30)  ──>  | 30 |  <── top (cima)
                   | 20 |
                   | 10 |
                   +----+
    pop()     ──>  Retira el 30
```

### Operaciones Primitivas
* `push(x)`: Inserta un elemento en el tope ($O(1)$).
* `pop()`: Remueve el elemento del tope ($O(1)$).
* `top()` o `peek()`: Consulta el valor del tope sin eliminarlo ($O(1)$).
* `empty()`: Retorna `true` si la pila no tiene elementos ($O(1)$).
* `size()`: Retorna la cantidad de elementos ($O(1)$).

### Implementación Manual con Nodos ($O(1)$)
En muchas evaluaciones se prohíbe el uso de `<stack>` y se exige implementación dinámica:

```cpp
#include <iostream>
#include <stdexcept>
using namespace std;

class PilaEnlazada {
private:
    struct Nodo {
        int dato;
        Nodo* sig;
        Nodo(int v, Nodo* s = nullptr) : dato(v), sig(s) {}
    };
    Nodo* cima;
    int contador;

public:
    PilaEnlazada() : cima(nullptr), contador(0) {}

    ~PilaEnlazada() {
        while (!estaVacia()) pop();
    }

    void push(int valor) {
        cima = new Nodo(valor, cima);
        contador++;
    }

    void pop() {
        if (estaVacia()) throw runtime_error("Stack Underflow: La pila esta vacia");
        Nodo* temp = cima;
        cima = cima->sig;
        delete temp;
        contador--;
    }

    int top() const {
        if (estaVacia()) throw runtime_error("La pila esta vacia");
        return cima->dato;
    }

    bool estaVacia() const { return cima == nullptr; }
    int tamano() const { return contador; }
};
```

### Uso con la STL (`std::stack`)
```cpp
#include <iostream>
#include <stack>
using namespace std;

int main() {
    stack<string> historial;
    historial.push("google.com");
    historial.push("github.com");
    historial.push("stackoverflow.com");

    cout << "Tope actual: " << historial.top() << endl; // stackoverflow.com
    historial.pop(); // Desapila stackoverflow.com
    cout << "Nuevo tope: " << historial.top() << endl;  // github.com
    return 0;
}
```

---

## 2. Cola (Queue) - Principio FIFO

**FIFO:** *First In, First Out* (El primero en entrar es el primero en salir).
Imagina una fila en un banco o supermercado: el primer cliente en llegar es el primero en ser atendido. Los nuevos clientes se forman al final.

```text
    FRENTE (front)                              FINAL (back / rear)
         │                                               │
         ▼                                               ▼
     [ Cliente 1 ] ──> [ Cliente 2 ] ──> [ Cliente 3 ] <── push(nuevo)
         │
         ▼
     pop() (atendido)
```

### Implementación Manual con Punteros `front` y `rear`

```cpp
class ColaEnlazada {
private:
    struct Nodo {
        int dato;
        Nodo* sig;
        Nodo(int v) : dato(v), sig(nullptr) {}
    };
    Nodo* frente;
    Nodo* final;
    int contador;

public:
    ColaEnlazada() : frente(nullptr), final(nullptr), contador(0) {}

    ~ColaEnlazada() {
        while (!estaVacia()) dequeue();
    }

    void enqueue(int valor) {
        Nodo* nuevo = new Nodo(valor);
        if (estaVacia()) {
            frente = final = nuevo;
        } else {
            final->sig = nuevo;
            final = nuevo;
        }
        contador++;
    }

    void dequeue() {
        if (estaVacia()) throw runtime_error("Queue Underflow: Cola vacia");
        Nodo* temp = frente;
        frente = frente->sig;
        if (frente == nullptr) final = nullptr; // Si se vació completamente
        delete temp;
        contador--;
    }

    int getFrente() const {
        if (estaVacia()) throw runtime_error("Cola vacia");
        return frente->dato;
    }

    bool estaVacia() const { return frente == nullptr; }
};
```

---

## 3. Cola Circular con Arreglos

Cuando se implementa una cola sobre un arreglo de tamaño fijo, los índices avanzan usando el operador módulo `%` para no desperdiciar los espacios liberados al inicio:

$$\text{nuevoIndice} = (\text{indiceActual} + 1) \pmod{\text{CAPACIDAD}}$$

---

## 4. Problemas Típicos de Certamen

### Balanceo de Paréntesis y Símbolos
Dada una expresión como `"{[()]}"` o `"{[(])}"`, determinar si los delimitadores están correctamente abiertos y cerrados.

```cpp
#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool estanBalanceados(const string& expr) {
    stack<char> pila;
    for (char c : expr) {
        if (c == '(' || c == '[' || c == '{') {
            pila.push(c);
        } else if (c == ')' || c == ']' || c == '}') {
            if (pila.empty()) return false;
            char tope = pila.top();
            pila.pop();
            if ((c == ')' && tope != '(') ||
                (c == ']' && tope != '[') ||
                (c == '}' && tope != '{')) {
                return false;
            }
        }
    }
    return pila.empty();
}

int main() {
    cout << boolalpha;
    cout << estanBalanceados("{[()]}") << endl; // true
    cout << estanBalanceados("{[(])}") << endl; // false
    return 0;
}
```

---

## 5. Tabla Comparativa de Complejidades

| Operación | Pila (`std::stack` / Nodos) | Cola (`std::queue` / Nodos) | Arreglo común |
| :--- | :---: | :---: | :---: |
| **Insertar elemento** | $O(1)$ (`push`) | $O(1)$ (`enqueue` al final) | $O(n)$ al inicio / $O(1)$ al final |
| **Eliminar elemento** | $O(1)$ (`pop`) | $O(1)$ (`dequeue` al frente) | $O(n)$ al inicio |
| **Consultar extremo** | $O(1)$ (`top`) | $O(1)$ (`front`) | $O(1)$ |
| **Acceso arbitrario** | ❌ No permitido | ❌ No permitido | $O(1)$ por índice `arr[i]` |
