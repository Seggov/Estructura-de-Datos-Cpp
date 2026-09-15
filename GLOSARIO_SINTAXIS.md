# Glosario y Tarjeta de Referencia Rápida: Sintaxis C++ en Estructura de Datos

> 📍 **Navegación:** [🏠 Menú Principal](README.md) \| [📘 Guía Prueba 1](Prueba_1/README.md) \| [📙 Guía Prueba 2](Prueba_2/README.md)

---

## 1. Operadores y Símbolos Fundamentales de Memoria

| Símbolo | Nombre | Uso / Ejemplo | Significado |
| :--- | :--- | :--- | :--- |
| `&` | *Address-of* | `&var` | Obtiene la dirección de memoria de `var` |
| `&` | Referencia | `void f(int& x)` | Parámetro por referencia (alias directo sin copia) |
| `*` | Declaración | `int* ptr` | Declara un puntero a un entero |
| `*` | Desreferenciación | `*ptr = 10` | Accede al valor almacenado en la dirección apuntada |
| `->` | Flecha de acceso | `nodo->dato` | Equivale a `(*nodo).dato` para punteros a estructuras u objetos |
| `::` | Ámbito (*Scope*) | `Lista::insertar` | Especifica a qué clase o namespace pertenece un método o tipo |
| `nullptr` | Puntero Nulo | `ptr = nullptr` | Dirección inválida segura; evita punteros colgantes |

---

## 2. Asignación y Liberación en el Heap

```cpp
// Variable simple
Tipo* ptr = new Tipo(args);
delete ptr;
ptr = nullptr;

// Arreglo contiguo
Tipo* arr = new Tipo[tamano];
delete[] arr; // Siempre con corchetes
arr = nullptr;

// Matriz bidimensional N x M
int** mat = new int*[N];
for (int i = 0; i < N; i++) mat[i] = new int[M];

for (int i = 0; i < N; i++) delete[] mat[i];
delete[] mat;
mat = nullptr;
```

---

## 3. Contenedores de la STL Habituales

### `std::vector<T>` (`#include <vector>`)
* `vec.push_back(val)`: Agrega al final ($O(1)$ amortizado).
* `vec.pop_back()`: Elimina el último elemento ($O(1)$).
* `vec.size()`: Cantidad actual de elementos ($O(1)$).
* `vec.empty()`: Retorna `true` si el vector está vacío ($O(1)$).
* `vec[i]`: Acceso directo por índice ($O(1)$).
* `vec.clear()`: Vacía todos los elementos.

### `std::pair<T1, T2>` (`#include <utility>`)
* Creación: `pair<int, string> p = {10, "Ejemplo"};` o `make_pair(10, "Ejemplo");`
* Acceso: `p.first` y `p.second`.
* Uso típico: Aristas ponderadas en listas de adyacencia `pair<int, int>` (vecino, peso).

### `std::stack<T>` (`#include <stack>`)
* `s.push(val)`: Inserta en el tope ($O(1)$).
* `s.pop()`: Elimina el tope sin retornarlo ($O(1)$).
* `s.top()`: Retorna referencia al tope ($O(1)$).
* `s.empty()`: ¿Está vacía? ($O(1)$).

### `std::queue<T>` (`#include <queue>`)
* `q.push(val)`: Inserta al final ($O(1)$).
* `q.pop()`: Elimina el frente ($O(1)$).
* `q.front()`: Consulta el primer elemento ($O(1)$).
* `q.back()`: Consulta el último elemento ($O(1)$).
* `q.empty()`: ¿Está vacía? ($O(1)$).

### `std::priority_queue<T>` (`#include <queue>`)
* **Max-Heap (predeterminado):** `priority_queue<int> pq;`
* **Min-Heap (menores primero):** `priority_queue<int, vector<int>, greater<int>> pq;`
* `pq.push(val)`: Inserta elemento ($O(\log n)$).
* `pq.pop()`: Extrae el elemento extremo ($O(\log n)$).
* `pq.top()`: Consulta el elemento extremo ($O(1)$).

---

## 4. Algoritmos Auxiliares de `<algorithm>`

```cpp
#include <algorithm>

std::swap(a, b);            // Intercambia el contenido de dos variables
int m = std::max(x, y);     // Retorna el mayor
int n = std::min(x, y);     // Retorna el menor
std::sort(vec.begin(), vec.end()); // Ordena ascendentemente O(n log n)
```

---

## 5. Entrada y Salida Rápida para Competitiva / Certámenes

```cpp
#include <iostream>
using namespace std;

int main() {
    // Acelera drásticamente la entrada y salida por consola
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    return 0;
}
```
