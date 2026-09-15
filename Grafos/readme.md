# Unidad 11: Fundamentos y Representación de Grafos en C++

> 📍 **Navegación:** [🏠 Menú Principal](../README.md) \| [📘 Guía Prueba 1](../Prueba_1/README.md) \| [📙 Guía Prueba 2](../Prueba_2/README.md)

---


## Índice
1. [Terminología Formal](#1-terminología-formal)
2. [Clasificación de Grafos](#2-clasificación-de-grafos)
3. [Matriz de Adyacencia](#3-matriz-de-adyacencia)
   - [Estructura en Memoria](#estructura-en-memoria)
   - [Implementación en C++](#implementación-en-c)
4. [Lista de Adyacencia](#4-lista-de-adyacencia)
   - [Estructura en Memoria](#estructura-en-memoria-1)
   - [Implementación para Grafos Ponderados](#implementación-para-grafos-ponderados)
5. [Lista de Aristas](#5-lista-de-aristas)
6. [Comparación: ¿Cuándo usar cada representación?](#6-comparación-cuándo-usar-cada-representación)

---

## 1. Terminología Formal

* **Vértice ($u, v \in V$):** Punto o entidad individual.
* **Arista ($e = (u, v) \in E$):** Conexión que enlaza dos vértices.
* **Grado de un vértice ($\deg(v)$):** Número de aristas conectadas a $v$.
  * En dígrafos se divide en **grado de entrada** (*in-degree*) y **grado de salida** (*out-degree*).
* **Camino (*Path*):** Secuencia de vértices conectados por aristas consecutivas.
* **Ciclo:** Camino simple cerrado donde el vértice inicial coincide con el final.
* **Grafo Conexo:** Existe al menos un camino entre cualquier par de vértices.
* **Grafo Bipartito:** Los vértices se pueden dividir en dos conjuntos disjuntos de modo que no existan aristas entre vértices del mismo conjunto.

---

## 2. Clasificación de Grafos

```text
               ┌── No Dirigido (Aristas bidireccionales u <───> v)
               │
               ├── Dirigido / Dígrafo (Aristas con flecha u ───> v)
               │
GRAFOS ────────┼── Ponderado / Valorado (Cada arista tiene un peso o costo)
               │
               ├── No Ponderado (Todas las aristas tienen igual peso = 1)
               │
               └── Denso (|E| ≈ |V|²) vs Disperso (|E| << |V|²)
```

---

## 3. Matriz de Adyacencia

Es una matriz bidimensional $M$ de tamaño $|V| \times |V|$ donde:
* $M[u][v] = 1$ (o el peso $w$) si existe una arista directa desde $u$ hacia $v$.
* $M[u][v] = 0$ (o $\infty$) si no existe arista.

```cpp
#include <iostream>
#include <vector>
using namespace std;

class GrafoMatriz {
private:
    int numVertices;
    vector<vector<int>> matriz;
    bool esDirigido;

public:
    GrafoMatriz(int vertices, bool dirigido = false) 
        : numVertices(vertices), esDirigido(dirigido) {
        matriz.resize(vertices, vector<int>(vertices, 0));
    }

    void agregarArista(int u, int v, int peso = 1) {
        matriz[u][v] = peso;
        if (!esDirigido) {
            matriz[v][u] = peso;
        }
    }

    bool existeArista(int u, int v) const {
        return matriz[u][v] != 0;
    }

    void imprimir() const {
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                cout << matriz[i][j] << " ";
            }
            cout << "\n";
        }
    }
};
```

---

## 4. Lista de Adyacencia

Cada vértice mantiene una lista o vector con sus vecinos inmediatos. Es la representación estándar más eficiente para la gran mayoría de problemas prácticos.

### Implementación para Grafos Ponderados
Utilizamos un arreglo de vectores con pares `pair<int, int>` donde `.first` es el nodo vecino y `.second` es el peso de la arista:

```cpp
#include <iostream>
#include <vector>
using namespace std;

class GrafoLista {
private:
    int numVertices;
    bool esDirigido;
    // listaAdy[u] contiene pares (vecino, peso)
    vector<vector<pair<int, int>>> listaAdy;

public:
    GrafoLista(int vertices, bool dirigido = false) 
        : numVertices(vertices), esDirigido(dirigido) {
        listaAdy.resize(vertices);
    }

    void agregarArista(int u, int v, int peso = 1) {
        listaAdy[u].push_back({v, peso});
        if (!esDirigido) {
            listaAdy[v].push_back({u, peso});
        }
    }

    void imprimirVecinos(int u) const {
        cout << "Vecinos de " << u << ": ";
        for (auto& arista : listaAdy[u]) {
            cout << "-> (Nodo: " << arista.first << ", Peso: " << arista.second << ") ";
        }
        cout << "\n";
    }

    const vector<pair<int, int>>& getVecinos(int u) const {
        return listaAdy[u];
    }
};
```

---

## 5. Lista de Aristas

Una simple lista plana que almacena cada conexión como un trío `(u, v, peso)`:

```cpp
struct Arista {
    int origen;
    int destino;
    int peso;

    bool operator<(const Arista& otra) const {
        return peso < otra.peso; // Permite ordenar por peso para algoritmos como Kruskal
    }
};

vector<Arista> listaAristas;
```

---

## 6. Comparación: ¿Cuándo usar cada representación?

| Criterio | Matriz de Adyacencia | Lista de Adyacencia |
| :--- | :---: | :---: |
| **Memoria Espacial** | $O(V^2)$ (Inviable para $V > 10.000$) | $\mathbf{O(V + E)}$ (Óptimo para grafos dispersos) |
| **Consultar arista $(u, v)$** | $\mathbf{O(1)}$ instantáneo | $O(\text{grado}(u))$ |
| **Iterar sobre vecinos de $u$** | $O(V)$ | $\mathbf{O(\text{grado}(u))}$ |
| **Insertar / Borrar arista** | $O(1)$ | $O(\text{grado}(u))$ |
| **Uso recomendado** | Grafos muy densos ($E \approx V^2$) | Casi todos los problemas de certamen y grafos reales |
