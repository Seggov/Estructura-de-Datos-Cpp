# Unidad 10: Algoritmos Avanzados en Árboles Binarios

> 📍 **Navegación:** [🏠 Menú Principal](../README.md) \| [📘 Guía Prueba 1](../Prueba_1/README.md) \| [📙 Guía Prueba 2](../Prueba_2/README.md)

---


## Índice
1. [Recorrido por Niveles (BFS con Cola)](#1-recorrido-por-niveles-bfs-con-cola)
2. [Reconstrucción desde Recorridos](#2-reconstrucción-desde-recorridos)
   - [Inorden + Preorden](#inorden--preorden)
   - [Inorden + Postorden](#inorden--postorden)
3. [Validar si un Árbol Binario es un BST Válido](#3-validar-si-un-árbol-binario-es-un-bst-válido)
4. [Ancestro Común más Cercano (LCA - Lowest Common Ancestor)](#4-ancestro-común-más-cercano-lca---lowest-common-ancestor)
   - [LCA en un BST ($O(h)$)](#lca-en-un-bst-oh)
   - [LCA en Árbol Binario General ($O(n)$)](#lca-en-árbol-binario-general-on)
5. [Espejo de un Árbol (*Mirror / Invert Tree*)](#5-espejo-de-un-árbol-mirror--invert-tree)
6. [Resumen de Complejidades](#6-resumen-de-complejidades)

---

## 1. Recorrido por Niveles (BFS con Cola)

Visita los nodos nivel por nivel, de izquierda a derecha. Utiliza una cola auxiliar (`std::queue`):

```cpp
#include <iostream>
#include <queue>
using namespace std;

struct Nodo {
    int dato;
    Nodo* izq;
    Nodo* der;
    Nodo(int v) : dato(v), izq(nullptr), der(nullptr) {}
};

void recorridoPorNiveles(Nodo* raiz) {
    if (raiz == nullptr) return;

    queue<Nodo*> cola;
    cola.push(raiz);

    while (!cola.empty()) {
        Nodo* actual = cola.front();
        cola.pop();

        cout << actual->dato << " ";

        if (actual->izq != nullptr) cola.push(actual->izq);
        if (actual->der != nullptr) cola.push(actual->der);
    }
}
```

---

## 2. Reconstrucción desde Recorridos

> [!IMPORTANT]
> Para reconstruir de forma única un árbol binario, es **estrictamente obligatorio** contar con el recorrido **Inorden** más uno de los otros dos (**Preorden** o **Postorden**).

### Inorden + Preorden
* **Preorden:** El **primer elemento** de la secuencia siempre es la raíz.
* **Inorden:** Todo lo que se encuentre a la izquierda de dicha raíz pertenece al subárbol izquierdo; lo que esté a la derecha pertenece al subárbol derecho.

```cpp
#include <vector>
using namespace std;

Nodo* construirDesdePreIn(const vector<int>& pre, const vector<int>& in,
                          int preInicio, int inInicio, int inFin) {
    if (inInicio > inFin || preInicio >= (int)pre.size()) return nullptr;

    Nodo* raiz = new Nodo(pre[preInicio]);

    // Buscar la posición de la raíz dentro de inorden
    int indiceRaizEnInorden = inInicio;
    while (in[indiceRaizEnInorden] != raiz->dato) {
        indiceRaizEnInorden++;
    }

    int cantidadNodosIzq = indiceRaizEnInorden - inInicio;

    raiz->izq = construirDesdePreIn(pre, in, preInicio + 1, inInicio, indiceRaizEnInorden - 1);
    raiz->der = construirDesdePreIn(pre, in, preInicio + 1 + cantidadNodosIzq, indiceRaizEnInorden + 1, inFin);

    return raiz;
}
```

---

## 3. Validar si un Árbol Binario es un BST Válido

Un error común en certámenes es comparar solo el nodo con su hijo inmediato (`izq->dato < raiz->dato`). Esto es incorrecto porque un nodo más profundo en el subárbol izquierdo podría ser mayor que un ancestro superior.

**Solución Correcta:** Propagar un rango válido $(\text{mínimo}, \text{máximo})$ por referencia recursiva:

```cpp
#include <climits>

bool esBSTValido(Nodo* raiz, long long minVal = LLONG_MIN, long long maxVal = LLONG_MAX) {
    if (raiz == nullptr) return true;

    // El valor actual debe estar estrictamente dentro del rango permitido
    if (raiz->dato <= minVal || raiz->dato >= maxVal) {
        return false;
    }

    // A la izquierda el máximo permitido es el valor actual
    // A la derecha el mínimo permitido es el valor actual
    return esBSTValido(raiz->izq, minVal, raiz->dato) &&
           esBSTValido(raiz->der, raiz->dato, maxVal);
}
```

---

## 4. Ancestro Común más Cercano (LCA - Lowest Common Ancestor)

El LCA de dos nodos $p$ y $q$ es el nodo más profundo que tiene a ambos como descendientes.

### LCA en un BST ($O(h)$)
Aprovecha la propiedad de búsqueda del BST:
* Si ambos valores son menores que la raíz, el LCA está en el subárbol izquierdo.
* Si ambos valores son mayores que la raíz, el LCA está en el subárbol derecho.
* En cuanto los valores se "dividan" (uno menor y otro mayor) o uno sea igual a la raíz actual, esa raíz es el LCA.

```cpp
Nodo* lcaBST(Nodo* raiz, int n1, int n2) {
    if (raiz == nullptr) return nullptr;

    if (n1 < raiz->dato && n2 < raiz->dato) {
        return lcaBST(raiz->izq, n1, n2);
    }
    if (n1 > raiz->dato && n2 > raiz->dato) {
        return lcaBST(raiz->der, n1, n2);
    }
    return raiz; // Punto de bifurcación
}
```

### LCA en Árbol Binario General ($O(n)$)
```cpp
Nodo* lcaGeneral(Nodo* raiz, int n1, int n2) {
    if (raiz == nullptr || raiz->dato == n1 || raiz->dato == n2) {
        return raiz;
    }

    Nodo* izq = lcaGeneral(raiz->izq, n1, n2);
    Nodo* der = lcaGeneral(raiz->der, n1, n2);

    if (izq != nullptr && der != nullptr) return raiz; // Bifurcación encontrada
    return (izq != nullptr) ? izq : der;
}
```

---

## 5. Espejo de un Árbol (*Mirror / Invert Tree*)

Intercambia recursivamente el subárbol izquierdo con el derecho de cada nodo:

```cpp
void invertirArbol(Nodo* raiz) {
    if (raiz == nullptr) return;

    swap(raiz->izq, raiz->der);

    invertirArbol(raiz->izq);
    invertirArbol(raiz->der);
}
```

---

## 6. Resumen de Complejidades

| Algoritmo | Complejidad Temporal | Complejidad Espacial |
| :--- | :---: | :---: |
| **Recorrido por Niveles (BFS)** | $O(n)$ | $O(w)$ donde $w$ es el ancho máximo |
| **Reconstruir desde Pre+In** | $O(n^2)$ naive / $O(n)$ con hash map | $O(n)$ pila recursiva |
| **Validar BST** | $O(n)$ | $O(h)$ |
| **LCA en BST** | $O(h)$ | $O(h)$ |
| **LCA en Árbol General** | $O(n)$ | $O(h)$ |
| **Invertir Árbol** | $O(n)$ | $O(h)$ |
