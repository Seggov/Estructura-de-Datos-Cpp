# Unidad 01: Punteros, Referencias y Memoria Dinámica en C++

Bienvenido a la unidad de **Punteros y Gestión de Memoria**. Este es el pilar fundamental de toda la asignatura de Estructura de Datos: sin entender punteros, no es posible comprender listas enlazadas, árboles ni grafos.

---

## Índice
1. [Concepto de Memoria: Stack vs Heap](#1-concepto-de-memoria-stack-vs-heap)
2. [Operadores Fundamentales: & y *](#2-operadores-fundamentales--y-)
3. [Declaración y Uso de Punteros](#3-declaración-y-uso-de-punteros)
4. [Referencias vs Punteros](#4-referencias-vs-punteros)
5. [Aritmética de Punteros y Arreglos](#5-aritmética-de-punteros-y-arreglos)
6. [Puntero a Puntero (Doble Puntero: `T**`)](#6-puntero-a-puntero-doble-puntero-t)
7. [Memoria Dinámica: `new` y `delete`](#7-memoria-dinámica-new-y-delete)
8. [Errores Críticos y Buenas Prácticas](#8-errores-críticos-y-buenas-prácticas)
9. [Ejemplo Completo Integrador](#9-ejemplo-completo-integrador)

---

## 1. Concepto de Memoria: Stack vs Heap

En C++, la memoria asignada a un programa se divide principalmente en:

| Característica | Stack (Pila de llamadas) | Heap (Memoria Dinámica) |
| :--- | :--- | :--- |
| **Asignación** | Automática (tiempo de compilación / ejecución de funciones) | Manual mediante `new` (tiempo de ejecución) |
| **Liberación** | Automática al salir del bloque `{}` | Manual mediante `delete` o `delete[]` |
| **Velocidad** | Extremadamente rápida | Ligeramente más lenta |
| **Tamaño** | Limitado (riesgo de *Stack Overflow*) | Limitado solo por la RAM disponible |
| **Persistencia** | Se destruye al terminar la función | Persiste hasta que se libere explícitamente |

---

## 2. Operadores Fundamentales: `&` y `*`

Todo dato almacenado en memoria tiene dos atributos esenciales:
1. **Su dirección**: La celda física de la memoria RAM donde vive (ej: `0x7ffee4b2a1bc`).
2. **Su contenido**: El valor numérico, texto o estructura que almacena.

```cpp
int x = 42;
// &x -> Operador "Address-of": Devuelve la dirección de memoria de x.
// *ptr -> Operador de "Desreferenciación": Accede al contenido alojado en la dirección.
```

---

## 3. Declaración y Uso de Punteros

Un puntero es una variable cuyo valor es la dirección de memoria de otra variable.

```cpp
#include <iostream>
using namespace std;

int main() {
    int numero = 100;
    int* ptr = &numero; // ptr guarda la dirección de memoria de 'numero'

    cout << "Valor de 'numero': " << numero << endl;       // Imprime 100
    cout << "Dirección de 'numero' (&numero): " << &numero << endl; // Ej: 0x7fff5fbff8ac
    cout << "Valor de 'ptr' (dirección que guarda): " << ptr << endl; // Igual a &numero
    cout << "Dirección propia de 'ptr' (&ptr): " << &ptr << endl;   // Otra dirección en el Stack
    cout << "Valor desreferenciado (*ptr): " << *ptr << endl;       // Imprime 100

    // Modificar la variable original a través del puntero
    *ptr = 250;
    cout << "Nuevo valor de 'numero': " << numero << endl; // Imprime 250

    return 0;
}
```

### El puntero nulo: `nullptr`
Siempre que un puntero no apunte a ninguna dirección válida, inicialízalo con `nullptr` (C++11 en adelante):
```cpp
int* ptr = nullptr;
if (ptr != nullptr) {
    *ptr = 5; // Seguro
} else {
    cout << "El puntero no apunta a ninguna dirección válida." << endl;
}
```
> [!WARNING]
> Desreferenciar un puntero `nullptr` o no inicializado provoca un **Segmentation Fault (Core Dump)** y crashea el programa de inmediato.

---

## 4. Referencias vs Punteros

Una **referencia** (`&`) es un alias o sobrenombre permanente para una variable existente.

```cpp
int a = 10;
int& ref = a; // ref ES 'a'

ref = 20; // 'a' ahora vale 20
```

### Tabla Comparativa
| Propiedad | Puntero (`T*`) | Referencia (`T&`) |
| :--- | :--- | :--- |
| **Puede ser nulo** | Sí (`nullptr`) | No, siempre debe referenciar a una variable real |
| **Reasignable** | Sí, puede apuntar a otra variable | No, no se puede cambiar a qué refiere una vez creada |
| **Sintaxis de acceso** | Requiere desreferenciar con `*` o flecha `->` | Sintaxis directa como una variable común |
| **Inicialización** | Puede declararse sin inicializar (peligroso) | Obligatorio inicializar al momento de declarar |

---

## 5. Aritmética de Punteros y Arreglos

En C++, el nombre de un arreglo estático decae (*decays*) a un puntero al primer elemento:
```cpp
int v[5] = {10, 20, 30, 40, 50};

// v es equivalente a &v[0]
int* ptr = v;

cout << *ptr << endl;       // Imprime 10 (elemento en v[0])
cout << *(ptr + 1) << endl; // Imprime 20 (elemento en v[1])
cout << *(ptr + 3) << endl; // Imprime 40 (elemento en v[3])
```
La expresión `*(v + i)` es exactamente equivalente a `v[i]`. Cuando sumas `1` a un puntero, C++ avanza `sizeof(Tipo)` bytes en la memoria.

---

## 6. Puntero a Puntero (Doble Puntero: `T**`)

Un doble puntero guarda la dirección de memoria de otro puntero. Se utiliza frecuentemente para:
1. Crear matrices dinámicas bidimensionales.
2. Modificar la cabeza de una lista enlazada dentro de una función sin necesidad de retornar el nuevo nodo.

```cpp
int valor = 500;
int* ptr1 = &valor;
int** ptr2 = &ptr1; // ptr2 guarda la dirección de ptr1

cout << "Valor: " << valor << endl;      // 500
cout << "Via *ptr1: " << *ptr1 << endl;   // 500
cout << "Via **ptr2: " << **ptr2 << endl; // 500
```

---

## 7. Memoria Dinámica: `new` y `delete`

Permite solicitar memoria al sistema operativo en tiempo de ejecución (Heap):

### Variable individual
```cpp
int* p = new int;      // Reserva memoria para un entero
*p = 42;
delete p;              // Libera la memoria
p = nullptr;           // Evita dejar un puntero colgante
```

### Arreglo dinámico
```cpp
int n = 100;
int* arreglo = new int[n]; // Reserva n enteros contiguos

for (int i = 0; i < n; i++) {
    arreglo[i] = i * 2;
}

delete[] arreglo;          // OBLIGATORIO usar delete[] para arreglos
arreglo = nullptr;
```

### Matriz Dinámica ($N \times M$)
```cpp
int filas = 3, columnas = 4;
int** matriz = new int*[filas];

for (int i = 0; i < filas; i++) {
    matriz[i] = new int[columnas];
}

// Liberar memoria (en orden inverso de asignación)
for (int i = 0; i < filas; i++) {
    delete[] matriz[i];
}
delete[] matriz;
matriz = nullptr;
```

---

## 8. Errores Críticos y Buenas Prácticas

1. **Fuga de Memoria (*Memory Leak*)**: Ocurre cuando se pierde el puntero a una zona del Heap sin haber hecho `delete`.
2. **Puntero Colgante (*Dangling Pointer*)**: Puntero que sigue apuntando a memoria que ya fue liberada con `delete`. Solución: Inmediatamente tras `delete ptr;`, asignar `ptr = nullptr;`.
3. **Doble Liberación (*Double Free*)**: Hacer `delete` dos veces sobre el mismo puntero causa corrupción de memoria.
4. **Olvidar los corchetes en `delete[]`**: Si reservas con `new[]`, debes liberar con `delete[]`.

---

## 9. Ejemplo Completo Integrador

```cpp
#include <iostream>
using namespace std;

// Función que modifica un valor usando punteros
void duplicar(int* ptr) {
    if (ptr != nullptr) {
        *ptr = (*ptr) * 2;
    }
}

// Función que modifica un valor usando referencias
void triplicar(int& ref) {
    ref = ref * 3;
}

int main() {
    int valor = 10;

    duplicar(&valor);
    cout << "Despues de duplicar: " << valor << endl; // 20

    triplicar(valor);
    cout << "Despues de triplicar: " << valor << endl; // 60

    // Arreglo dinamico
    int tamano = 3;
    int* lista = new int[tamano]{100, 200, 300};

    for (int i = 0; i < tamano; i++) {
        cout << "Elemento [" << i << "]: " << *(lista + i) << endl;
    }

    delete[] lista;
    lista = nullptr;

    return 0;
}
```
