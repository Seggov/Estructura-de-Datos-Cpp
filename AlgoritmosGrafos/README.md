# Unidad 12: Algoritmos Fundamentales en Grafos

Esta unidad contiene los algoritmos clásicos de recorrido, optimización de caminos y árboles de expansión mínima que constituyen el núcleo de la evaluación práctica de Grafos.

---

## Índice
1. [Búsqueda en Profundidad (DFS - Depth First Search)](#1-búsqueda-en-profundidad-dfs---depth-first-search)
   - [Implementación Recursiva](#implementación-recursiva)
   - [Detección de Ciclos](#detección-de-ciclos)
2. [Búsqueda en Anchura (BFS - Breadth First Search)](#2-búsqueda-en-anchura-bfs---breadth-first-search)
   - [Implementación con Cola](#implementación-con-cola)
   - [Camino Mínimo en Grafos No Ponderados](#camino-mínimo-en-grafos-no-ponderados)
3. [Algoritmo de Dijkstra (Camino Más Corto Ponderado)](#3-algoritmo-de-dijkstra-camino-más-corto-ponderado)
   - [Lógica con Min-Heap / Cola de Prioridad](#lógica-con-min-heap--cola-de-prioridad)
   - [Implementación en C++](#implementación-en-c)
4. [Árbol de Expansión Mínima (MST)](#4-árbol-de-expansión-mínima-mst)
   - [Algoritmo de Kruskal y Disjoint Set (DSU)](#algoritmo-de-kruskal-y-disjoint-set-dsu)
   - [Algoritmo de Prim](#algoritmo-de-prim)
5. [Tabla Comparativa de Algoritmos](#5-tabla-comparativa-de-algoritmos)

---

## 1. Búsqueda en Profundidad (DFS - Depth First Search)

Explora tan lejos como sea posible por cada rama antes de retroceder (*backtracking*). Utiliza la pila de llamadas (*call stack*) de la recursión.

```cpp
#include <iostream>
#include <vector>
using namespace std;

void dfs(int u, const vector<vector<int>>& ady, vector<bool>& visitado) {
    visitado[u] = true;
    cout << u << " ";

    for (int vecino : ady[u]) {
        if (!visitado[vecino]) {
            dfs(vecino, ady, visitado);
        }
    }
}
```
* **Complejidad:** $O(V + E)$ con lista de adyacencia.
* **Aplicaciones:** Conectividad de componentes, caminos posibles, ordenamiento topológico, detección de ciclos.

---

## 2. Búsqueda en Anchura (BFS - Breadth First Search)

Explora todos los vecinos directos a distancia 1, luego a distancia 2, etc., en forma de ondas concéntricas. **Garantiza encontrar el camino con menor número de aristas en grafos no ponderados**.

```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void bfs(int inicio, const vector<vector<int>>& ady, int numVertices) {
    vector<bool> visitado(numVertices, false);
    vector<int> distancia(numVertices, -1);
    queue<int> cola;

    visitado[inicio] = true;
    distancia[inicio] = 0;
    cola.push(inicio);

    while (!cola.empty()) {
        int u = cola.front();
        cola.pop();

        for (int v : ady[u]) {
            if (!visitado[v]) {
                visitado[v] = true;
                distancia[v] = distancia[u] + 1;
                cola.push(v);
            }
        }
    }
}
```

---

## 3. Algoritmo de Dijkstra (Camino Más Corto Ponderado)

Encuentra las distancias mínimas desde un único nodo origen hacia todos los demás vértices en un grafo con **pesos no negativos** ($w \ge 0$).

### Implementación en C++ usando `std::priority_queue`

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

const int INF = INT_MAX;

// Representamos cada arista como pair<peso, verticeDestino>
typedef pair<int, int> ii; 

vector<int> dijkstra(int origen, int V, const vector<vector<pair<int, int>>>& ady) {
    vector<int> dist(V, INF);
    // Min-heap ordenado por distancia acumulada (menor distancia primero)
    priority_queue<ii, vector<ii>, greater<ii>> pq;

    dist[origen] = 0;
    pq.push({0, origen});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // Si ya encontramos un camino más corto previamente, ignorar
        if (d > dist[u]) continue;

        for (auto& arista : ady[u]) {
            int v = arista.first;
            int peso = arista.second;

            // Relajación de la arista
            if (dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}
```
* **Complejidad:** $O((V + E) \log V)$ usando un Heap binario.

---

## 4. Árbol de Expansión Mínima (MST)

Un **MST (Minimum Spanning Tree)** es un subgrafo que conecta todos los vértices de un grafo ponderado conexo con exactamente $V - 1$ aristas y minimizando la suma total de sus pesos.

### Algoritmo de Kruskal y Disjoint Set (DSU)
1. Ordenar todas las aristas de menor a mayor peso.
2. Añadir la arista de menor peso siempre que **no forme un ciclo** (verificado eficientemente con una estructura Union-Find / DSU).
3. Parar cuando se hayan seleccionado $V - 1$ aristas.

```cpp
struct DSU {
    vector<int> padre;
    DSU(int n) {
        padre.resize(n);
        for (int i = 0; i < n; i++) padre[i] = i;
    }
    int buscar(int i) {
        if (padre[i] == i) return i;
        return padre[i] = buscar(padre[i]); // Compresión de camino
    }
    bool unir(int i, int j) {
        int root_i = buscar(i);
        int root_j = buscar(j);
        if (root_i != root_j) {
            padre[root_i] = root_j;
            return true; // Se unieron con éxito
        }
        return false; // Ya estaban conectados (formaría ciclo)
    }
};
```
* **Complejidad de Kruskal:** $O(E \log E)$.

---

## 5. Tabla Comparativa de Algoritmos

| Algoritmo | Propósito Principal | Estructura de Apoyo | Complejidad Temporal |
| :--- | :--- | :---: | :---: |
| **DFS** | Exploración exhaustiva, conectividad | Pila / Recursión | $O(V + E)$ |
| **BFS** | Camino más corto en grafos sin peso | Cola (`queue`) | $O(V + E)$ |
| **Dijkstra** | Camino más corto ponderado ($w \ge 0$) | Min-Heap (`priority_queue`) | $O((V + E) \log V)$ |
| **Kruskal** | Árbol de Expansión Mínima (MST) | Disjoint Set Union (DSU) | $O(E \log E)$ |
| **Prim** | Árbol de Expansión Mínima (MST) | Min-Heap | $O((V + E) \log V)$ |
