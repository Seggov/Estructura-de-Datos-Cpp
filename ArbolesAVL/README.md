# Unidad 08: Árboles Balanceados AVL en C++

El **Árbol AVL** (nombrado así en honor a sus inventores Adelson-Velsky y Landis) es un Árbol Binario de Búsqueda auto-balanceable. Garantiza que la altura del árbol sea siempre $O(\log n)$, eliminando por completo el riesgo de degeneración a lista enlazada.

---

## Índice
1. [El Problema del ABB Simple y la Solución AVL](#1-el-problema-del-abb-simple-y-la-solución-avl)
2. [Factor de Balance (FB) y Altura](#2-factor-de-balance-fb-y-altura)
3. [Las 4 Rotaciones de Rebalanceo](#3-las-4-rotaciones-de-rebalanceo)
   - [Rotación Simple a la Derecha (Caso LL)](#rotación-simple-a-la-derecha-caso-ll)
   - [Rotación Simple a la Izquierda (Caso RR)](#rotación-simple-a-la-izquierda-caso-rr)
   - [Rotación Doble Izquierda-Derecha (Caso LR)](#rotación-doble-izquierda-derecha-caso-lr)
   - [Rotación Doble Derecha-Izquierda (Caso RL)](#rotación-doble-derecha-izquierda-caso-rl)
4. [Estructura del Nodo AVL en C++](#4-estructura-del-nodo-avl-en-c)
5. [Algoritmo Completo de Inserción con Auto-balanceo](#5-algoritmo-completo-de-inserción-con-auto-balanceo)
6. [Eliminación en Árboles AVL](#6-eliminación-en-árboles-avl)
7. [Resumen y Comparación con ABB Normal](#7-resumen-y-comparación-con-abb-normal)

---

## 1. El Problema del ABB Simple y la Solución AVL

En un ABB simple, insertar datos en orden (como `1, 2, 3, 4, 5`) produce un árbol con forma de línea de altura $n$, donde buscar tarda $O(n)$.
El árbol AVL soluciona esto manteniendo una **condición de equilibrio estricta**: en todo nodo, la diferencia de alturas entre sus subárboles no puede ser mayor a 1.

---

## 2. Factor de Balance (FB) y Altura

Para cada nodo $N$:
$$\text{FB}(N) = \text{altura}(N \rightarrow \text{izq}) - \text{altura}(N \rightarrow \text{der})$$

* **Árbol Balanceado:** $\text{FB} \in \{-1, 0, +1\}$.
* **Desbalance Izquierdo:** $\text{FB} > +1$ (el subárbol izquierdo es demasiado alto).
* **Desbalance Derecho:** $\text{FB} < -1$ (el subárbol derecho es demasiado alto).

---

## 3. Las 4 Rotaciones de Rebalanceo

```text
    Desbalance Izquierdo (FB > 1)
        ├── Hijo Izquierdo pesado a la izquierda (FB >= 0) ──> Rotación Simple Derecha (LL)
        └── Hijo Izquierdo pesado a la derecha   (FB < 0)  ──> Rotación Doble Izq-Der (LR)

    Desbalance Derecho (FB < -1)
        ├── Hijo Derecho pesado a la derecha   (FB <= 0) ──> Rotación Simple Izquierda (RR)
        └── Hijo Derecho pesado a la izquierda (FB > 0)  ──> Rotación Doble Der-Izq (RL)
```

### Rotación Simple a la Derecha (LL)
```text
        z (FB=+2)                  y
       /                          / \
      y (FB=+1)       ───>       x   z
     /
    x
```
```cpp
NodoAVL* rotacionDerecha(NodoAVL* z) {
    NodoAVL* y = z->izq;
    NodoAVL* T3 = y->der;

    // Efectuar rotación
    y->der = z;
    z->izq = T3;

    // Actualizar alturas
    z->altura = 1 + max(getAltura(z->izq), getAltura(z->der));
    y->altura = 1 + max(getAltura(y->izq), getAltura(y->der));

    return y; // Nueva raíz del subárbol
}
```

### Rotación Simple a la Izquierda (RR)
```text
    z (FB=-2)                      y
     \                            / \
      y (FB=-1)       ───>       z   x
       \
        x
```
```cpp
NodoAVL* rotacionIzquierda(NodoAVL* z) {
    NodoAVL* y = z->der;
    NodoAVL* T2 = y->izq;

    // Efectuar rotación
    y->izq = z;
    z->der = T2;

    // Actualizar alturas
    z->altura = 1 + max(getAltura(z->izq), getAltura(z->der));
    y->altura = 1 + max(getAltura(y->izq), getAltura(y->der));

    return y; // Nueva raíz
}
```

### Rotación Doble Izquierda-Derecha (LR)
Se aplica cuando el desbalance es a la izquierda, pero el nuevo elemento se insertó a la derecha del hijo izquierdo.
1. Rotación Simple Izquierda sobre el hijo izquierdo (`z->izq`).
2. Rotación Simple Derecha sobre el nodo desbalanceado (`z`).

### Rotación Doble Derecha-Izquierda (RL)
Se aplica cuando el desbalance es a la derecha, pero el nuevo elemento se insertó a la izquierda del hijo derecho.
1. Rotación Simple Derecha sobre el hijo derecho (`z->der`).
2. Rotación Simple Izquierda sobre el nodo desbalanceado (`z`).

---

## 4. Estructura del Nodo AVL en C++

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

struct NodoAVL {
    int dato;
    int altura;
    NodoAVL* izq;
    NodoAVL* der;

    NodoAVL(int val) : dato(val), altura(1), izq(nullptr), der(nullptr) {}
};

int getAltura(NodoAVL* n) {
    return (n == nullptr) ? 0 : n->altura;
}

int getFactorBalance(NodoAVL* n) {
    return (n == nullptr) ? 0 : getAltura(n->izq) - getAltura(n->der);
}
```

---

## 5. Algoritmo Completo de Inserción con Auto-balanceo

```cpp
NodoAVL* insertarAVL(NodoAVL* nodo, int valor) {
    // 1. Inserción normal de ABB
    if (nodo == nullptr) return new NodoAVL(valor);

    if (valor < nodo->dato) {
        nodo->izq = insertarAVL(nodo->izq, valor);
    } else if (valor > nodo->dato) {
        nodo->der = insertarAVL(nodo->der, valor);
    } else {
        return nodo; // No se permiten duplicados en el ABB estándar
    }

    // 2. Actualizar altura del ancestro actual
    nodo->altura = 1 + max(getAltura(nodo->izq), getAltura(nodo->der));

    // 3. Obtener el factor de balance para verificar si se desequilibró
    int balance = getFactorBalance(nodo);

    // 4. Corregir según los 4 casos de rotación:

    // Caso LL (Izquierda - Izquierda)
    if (balance > 1 && valor < nodo->izq->dato) {
        return rotacionDerecha(nodo);
    }

    // Caso RR (Derecha - Derecha)
    if (balance < -1 && valor > nodo->der->dato) {
        return rotacionIzquierda(nodo);
    }

    // Caso LR (Izquierda - Derecha)
    if (balance > 1 && valor > nodo->izq->dato) {
        nodo->izq = rotacionIzquierda(nodo->izq);
        return rotacionDerecha(nodo);
    }

    // Caso RL (Derecha - Izquierda)
    if (balance < -1 && valor < nodo->der->dato) {
        nodo->der = rotacionDerecha(nodo->der);
        return rotacionIzquierda(nodo);
    }

    return nodo;
}
```

---

## 6. Eliminación en Árboles AVL

La eliminación sigue el algoritmo de borrado de un ABB clásico (buscar sucesor inorden si tiene 2 hijos) y luego, al retroceder en la recursión (*backtracking*), se recalcula la altura y el factor de balance en cada ancestro para aplicar las rotaciones correspondientes si el balance cayó fuera de $\{-1, 0, 1\}$.

---

## 7. Resumen y Comparación con ABB Normal

| Operación | ABB Común (Peor caso) | Árbol AVL (Garantizado) |
| :--- | :---: | :---: |
| **Búsqueda** | $O(n)$ | $\mathbf{O(\log n)}$ |
| **Inserción** | $O(n)$ | $\mathbf{O(\log n)}$ |
| **Eliminación** | $O(n)$ | $\mathbf{O(\log n)}$ |
| **Sobrecosto de Memoria** | Solo punteros | Entero adicional por nodo (`altura`) |
| **Costo de balanceo** | Ninguno | A lo sumo 2 rotaciones por inserción ($O(1)$ tras encontrar la posición) |
