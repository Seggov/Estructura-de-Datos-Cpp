# Unidad 09: Heaps (Montículos), Colas de Prioridad y HeapSort en C++

Un **Heap** (o montículo binario) es un árbol binario casi completo que satisface la **propiedad de orden de heap**. Aunque conceptualmente es un árbol, se almacena eficientemente dentro de un simple arreglo contiguo sin necesidad de punteros explícitos.

---

## Índice
1. [Mapeo de Árbol Completo a Arreglo](#1-mapeo-de-árbol-completo-a-arreglo)
2. [Max-Heap vs Min-Heap](#2-max-heap-vs-min-heap)
3. [Operación Fundamental: `heapify` (Hundir)](#3-operación-fundamental-heapify-hundir)
4. [Construcción del Heap: `buildHeap` ($O(n)$)](#4-construcción-del-heap-buildheap-on)
5. [Inserción y Extracción ($O(\log n)$)](#5-inserción-y-extracción-olog-n)
6. [El Algoritmo de Ordenamiento HeapSort](#6-el-algoritmo-de-ordenamiento-heapsort)
7. [Colas de Prioridad en la STL (`std::priority_queue`)](#7-colas-de-prioridad-en-la-stl-stdpriority_queue)
8. [Complejidades Resumidas](#8-complejidades-resumidas)

---

## 1. Mapeo de Árbol Completo a Arreglo

Al ser un árbol binario completo (todos los niveles llenos salvo posiblemente el último, que se llena de izquierda a derecha), podemos calcular las posiciones familiares mediante aritmética simple:

| Relación | Fórmula de Índice |
| :--- | :--- |
| **Hijo Izquierdo de $i$** | $2i + 1$ |
| **Hijo Derecho de $i$** | $2i + 2$ |
| **Padre de $i$** | $\lfloor (i - 1) / 2 \rfloor$ |

```text
Árbol:                        Arreglo:
         [90] (0)             Índices:  0   1   2   3   4   5
        /        \            Valores: [90, 70, 80, 40, 50, 60]
     [70] (1)   [80] (2)
     /    \      /
  [40](3)[50](4)[60](5)
```

---

## 2. Max-Heap vs Min-Heap

* **Max-Heap:** Para todo nodo $i$, el valor del padre es mayor o igual que el de sus hijos:
  $$\text{arr}[\text{padre}(i)] \ge \text{arr}[i]$$
  La raíz siempre contiene el **valor máximo global**.
* **Min-Heap:** Para todo nodo $i$, el valor del padre es menor o igual que el de sus hijos:
  $$\text{arr}[\text{padre}(i)] \le \text{arr}[i]$$
  La raíz siempre contiene el **valor mínimo global**.

---

## 3. Operación Fundamental: `heapify` (Hundir)

Si un nodo en el índice $i$ viola la propiedad de heap pero sus dos subárboles son heaps válidos, `heapify` hace descender al nodo intercambiándolo con su hijo mayor (en un Max-Heap):

```cpp
#include <vector>
#include <algorithm>
using namespace std;

void heapify(vector<int>& arr, int n, int i) {
    int mayor = i;
    int izq = 2 * i + 1;
    int der = 2 * i + 2;

    // Si el hijo izquierdo es mayor que la raíz actual
    if (izq < n && arr[izq] > arr[mayor]) {
        mayor = izq;
    }

    // Si el hijo derecho es mayor que el mayor visto hasta ahora
    if (der < n && arr[der] > arr[mayor]) {
        mayor = der;
    }

    // Si el mayor no es la raíz
    if (mayor != i) {
        swap(arr[i], arr[mayor]);
        // Recursivamente acomodar el subárbol afectado
        heapify(arr, n, mayor);
    }
}
```

---

## 4. Construcción del Heap: `buildHeap` ($O(n)$)

Para convertir un arreglo cualquiera en un Max-Heap válido, aplicamos `heapify` empezando desde el último nodo no-hoja hacia atrás hasta la raíz (índice 0):

```cpp
void buildMaxHeap(vector<int>& arr) {
    int n = arr.size();
    // El último nodo que tiene hijos está en (n / 2) - 1
    for (int i = (n / 2) - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}
```
> [!NOTE]
> Aunque cada `heapify` toma $O(\log n)$, la suma matemática de las alturas de todos los nodos demuestra que `buildHeap` toma tiempo lineal **$O(n)$**, no $O(n \log n)$.

---

## 5. Inserción y Extracción ($O(\log n)$)

* **Inserción:** Se agrega el nuevo dato al final del arreglo y se le hace "flotar" (*percolate up*) comparándolo con su padre hasta que quede en la posición correcta.
* **Extracción de la Raíz:** Se guarda el valor de la raíz (`arr[0]`), se copia el último elemento del arreglo a la raíz, se reduce el tamaño del heap en 1 y se invoca `heapify(arr, n, 0)` para restablecer el orden.

---

## 6. El Algoritmo de Ordenamiento HeapSort

HeapSort ordena un arreglo in-place aprovechando la propiedad de la raíz del Max-Heap:

```cpp
#include <iostream>
#include <vector>
using namespace std;

void heapSort(vector<int>& arr) {
    int n = arr.size();

    // Paso 1: Transformar el arreglo desordenado en un Max-Heap -> O(n)
    for (int i = (n / 2) - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // Paso 2: Extraer elementos uno a uno del heap -> O(n log n)
    for (int i = n - 1; i > 0; i--) {
        // Mover el máximo actual (en la raíz arr[0]) al final del arreglo
        swap(arr[0], arr[i]);

        // Restaurar el heap en el subarreglo reducido [0 ... i-1]
        heapify(arr, i, 0);
    }
}
```

---

## 7. Colas de Prioridad en la STL (`std::priority_queue`)

La biblioteca estándar de C++ provee `std::priority_queue` en el encabezado `<queue>`, que implementa internamente un montículo:

```cpp
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
    // 1. Max-Heap por defecto (los mayores salen primero)
    priority_queue<int> maxHeap;
    maxHeap.push(30);
    maxHeap.push(10);
    maxHeap.push(50);
    cout << "Max elemento: " << maxHeap.top() << endl; // 50
    maxHeap.pop();

    // 2. Min-Heap (los menores salen primero)
    priority_queue<int, vector<int>, greater<int>> minHeap;
    minHeap.push(30);
    minHeap.push(10);
    minHeap.push(50);
    cout << "Min elemento: " << minHeap.top() << endl; // 10
    minHeap.pop();

    return 0;
}
```

---

## 8. Complejidades Resumidas

| Operación | Tiempo | Espacio Auxiliar |
| :--- | :---: | :---: |
| **`buildHeap`** | $O(n)$ | $O(1)$ |
| **`insert` (push)** | $O(\log n)$ | $O(1)$ |
| **`extractMax` / `extractMin`** | $O(\log n)$ | $O(1)$ |
| **`top` / consultar extremo** | $O(1)$ | $O(1)$ |
| **HeapSort** | $\mathbf{O(n \log n)}$ en todo caso | $\mathbf{O(1)}$ (In-place) |
