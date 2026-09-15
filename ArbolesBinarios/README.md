# Unidad 07: Árboles Binarios y Árboles Binarios de Búsqueda (ABB) en C++

Los árboles son estructuras de datos jerárquicas y no lineales. Un **Árbol Binario** restringe a cada nodo a tener como máximo dos hijos: hijo izquierdo e hijo derecho.

---

## Índice
1. [Terminología Esencial de Árboles](#1-terminología-esencial-de-árboles)
2. [Estructura del Nodo](#2-estructura-del-nodo)
3. [Árbol Binario de Búsqueda (ABB / BST)](#3-árbol-binario-de-búsqueda-abb--bst)
   - [Propiedad de Orden](#propiedad-de-orden)
   - [Inserción Recursiva](#inserción-recursiva)
   - [Búsqueda en el ABB](#búsqueda-en-el-abb)
   - [Eliminación de un Nodo (Los 3 Casos)](#eliminación-de-un-nodo-los-3-casos)
4. [Recorridos en Profundidad (DFS)](#4-recorridos-en-profundidad-dfs)
   - [Inorden (In-Order)](#inorden-in-order)
   - [Preorden (Pre-Order)](#preorden-pre-order)
   - [Postorden (Post-Order)](#postorden-post-order)
5. [Cálculo de Altura, Tamaño y Hojas](#5-cálculo-de-altura-tamaño-y-hojas)
6. [Destructor: Liberación Postorden](#6-destructor-liberación-postorden)
7. [Complejidad Algorítmica y Casos Degenerados](#7-complejidad-algorítmica-y-casos-degenerados)

---

## 1. Terminología Esencial de Árboles

```text
               [ 50 ]          <── Raíz (Nivel 0, sin padre)
              /      \
          [ 30 ]    [ 70 ]     <── Nivel 1 (Hijos de 50)
         /     \        \
      [ 20 ]  [ 40 ]   [ 80 ]  <── Nivel 2 (Hojas: nodos sin descendientes)
```

* **Raíz (*Root*):** El nodo superior del árbol. No tiene nodo padre.
* **Hoja (*Leaf*):** Nodo cuyos punteros izquierdo y derecho son `nullptr`.
* **Nivel:** Distancia en aristas desde la raíz (la raíz está en nivel 0).
* **Altura ($h$):** Cantidad máxima de aristas o niveles desde la raíz hasta la hoja más profunda.
* **Grado de un nodo:** Número de hijos directos que posee (en binarios: 0, 1 o 2).

---

## 2. Estructura del Nodo

```cpp
struct NodoArbol {
    int dato;
    NodoArbol* izq;
    NodoArbol* der;

    NodoArbol(int valor) : dato(valor), izq(nullptr), der(nullptr) {}
};
```

---

## 3. Árbol Binario de Búsqueda (ABB / BST)

### Propiedad de Orden
Para cualquier nodo $X$ del árbol:
$$\text{Todos los nodos en Subárbol Izquierdo} < X < \text{Todos los nodos en Subárbol Derecho}$$

### Inserción Recursiva
```cpp
NodoArbol* insertar(NodoArbol* raiz, int valor) {
    if (raiz == nullptr) {
        return new NodoArbol(valor);
    }
    if (valor < raiz->dato) {
        raiz->izq = insertar(raiz->izq, valor);
    } else if (valor > raiz->dato) {
        raiz->der = insertar(raiz->der, valor);
    }
    return raiz;
}
```

### Búsqueda en el ABB
```cpp
bool buscar(NodoArbol* raiz, int buscado) {
    if (raiz == nullptr) return false;
    if (raiz->dato == buscado) return true;

    if (buscado < raiz->dato) {
        return buscar(raiz->izq, buscado);
    } else {
        return buscar(raiz->der, buscado);
    }
}
```

### Eliminación de un Nodo (Los 3 Casos)

1. **Caso 1: Nodo Hoja (0 hijos):** Se libera con `delete` y se retorna `nullptr`.
2. **Caso 2: Nodo con 1 solo hijo:** Se reemplaza el nodo por su único hijo.
3. **Caso 3: Nodo con 2 hijos:** Se busca el **sucesor inorden** (el menor elemento del subárbol derecho) o el predecesor inorden (el mayor del subárbol izquierdo), se copia su valor al nodo actual y se elimina recursivamente el sucesor en el subárbol derecho.

```cpp
NodoArbol* obtenerMinimo(NodoArbol* nodo) {
    NodoArbol* actual = nodo;
    while (actual && actual->izq != nullptr) {
        actual = actual->izq;
    }
    return actual;
}

NodoArbol* eliminar(NodoArbol* raiz, int valor) {
    if (raiz == nullptr) return nullptr;

    if (valor < raiz->dato) {
        raiz->izq = eliminar(raiz->izq, valor);
    } else if (valor > raiz->dato) {
        raiz->der = eliminar(raiz->der, valor);
    } else {
        // Encontramos el nodo a eliminar
        // Casos 1 y 2: Sin hijo izquierdo o sin hijo derecho
        if (raiz->izq == nullptr) {
            NodoArbol* temp = raiz->der;
            delete raiz;
            return temp;
        } else if (raiz->der == nullptr) {
            NodoArbol* temp = raiz->izq;
            delete raiz;
            return temp;
        }

        // Caso 3: Dos hijos
        NodoArbol* temp = obtenerMinimo(raiz->der);
        raiz->dato = temp->dato; // Copia el dato del sucesor
        raiz->der = eliminar(raiz->der, temp->dato); // Elimina el sucesor
    }
    return raiz;
}
```

---

## 4. Recorridos en Profundidad (DFS)

### Inorden (In-Order): `Izq -> Raíz -> Der`
En un ABB, el recorrido inorden visita los elementos en **orden estrictamente creciente**.
```cpp
void inorden(NodoArbol* raiz) {
    if (raiz == nullptr) return;
    inorden(raiz->izq);
    cout << raiz->dato << " ";
    inorden(raiz->der);
}
```

### Preorden (Pre-Order): `Raíz -> Izq -> Der`
Útil para serializar, guardar o clonar la estructura exacta del árbol.
```cpp
void preorden(NodoArbol* raiz) {
    if (raiz == nullptr) return;
    cout << raiz->dato << " ";
    preorden(raiz->izq);
    preorden(raiz->der);
}
```

### Postorden (Post-Order): `Izq -> Der -> Raíz`
Útil para cálculo de espacio en disco, evaluación de árboles de expresiones matemáticas y **liberación de memoria** (primero destruye a los hijos antes que al padre).
```cpp
void postorden(NodoArbol* raiz) {
    if (raiz == nullptr) return;
    postorden(raiz->izq);
    postorden(raiz->der);
    cout << raiz->dato << " ";
}
```

---

## 5. Cálculo de Altura, Tamaño y Hojas

```cpp
int calcularAltura(NodoArbol* raiz) {
    if (raiz == nullptr) return 0; // O -1 si la altura se define por aristas
    return 1 + max(calcularAltura(raiz->izq), calcularAltura(raiz->der));
}

int contarNodos(NodoArbol* raiz) {
    if (raiz == nullptr) return 0;
    return 1 + contarNodos(raiz->izq) + contarNodos(raiz->der);
}

int contarHojas(NodoArbol* raiz) {
    if (raiz == nullptr) return 0;
    if (raiz->izq == nullptr && raiz->der == nullptr) return 1;
    return contarHojas(raiz->izq) + contarHojas(raiz->der);
}
```

---

## 6. Destructor: Liberación Postorden

```cpp
void destruirArbol(NodoArbol*& raiz) {
    if (raiz == nullptr) return;
    destruirArbol(raiz->izq);
    destruirArbol(raiz->der);
    delete raiz;
    raiz = nullptr;
}
```

---

## 7. Complejidad Algorítmica y Casos Degenerados

| Operación | Caso Promedio (Árbol Equilibrado) | Peor Caso (Árbol Degenerado / Sesgado) |
| :--- | :---: | :---: |
| **Búsqueda** | $O(\log n)$ | $O(n)$ |
| **Inserción** | $O(\log n)$ | $O(n)$ |
| **Eliminación**| $O(\log n)$ | $O(n)$ |

> [!WARNING]
> Si los elementos se insertan ya ordenados (ej: `10, 20, 30, 40, 50`), un ABB simple se degenera en una **lista enlazada**, perdiendo toda su ventaja logarítmica. Para solucionar esto se crearon los **Árboles AVL**.
