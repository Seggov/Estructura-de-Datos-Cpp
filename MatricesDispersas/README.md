# Unidad 14: Matrices Poco Pobladas (Sparse Matrices) en C++

Una **Matriz Poco Poblada** (*Sparse Matrix*) es aquella en la que la gran mayoría de sus celdas contienen el valor cero (o nulo). Almacenarla en una matriz bidimensional tradicional `M[N][M]` desperdicia memoria de forma crítica ($O(N \cdot M)$).

---

## Índice
1. [Definición y Justificación](#1-definición-y-justificación)
2. [Formato de Coordenadas (COO - Coordinate Format)](#2-formato-de-coordenadas-coo---coordinate-format)
3. [Formato de Fila Comprimida (CSR - Compressed Sparse Row)](#3-formato-de-fila-comprimida-csr---compressed-sparse-row)
4. [Representación por Listas Cruzadas (Ortogonales)](#4-representación-por-listas-cruzadas-ortogonales)
5. [Operaciones Fundamentales en C++](#5-operaciones-fundamentales-en-c)
   - [Acceso a un Elemento](#acceso-a-un-elemento)
   - [Suma de Dos Matrices Dispersas](#suma-de-dos-matrices-dispersas)
   - [Transposición](#transposición)
6. [Tabla Comparativa de Representaciones](#6-tabla-comparativa-de-representaciones)

---

## 1. Definición y Justificación

Si en una matriz de $10.000 \times 10.000$ enteros solo hay $5.000$ valores distintos de cero:
* **Matriz Densa:** $100.000.000 \times 4\text{ bytes} \approx 400\text{ MB}$ de memoria RAM.
* **Matriz Sparse:** Guardar únicamente los 5.000 datos no nulos consume menos de $100\text{ KB}$.

> [!TIP]
> Como regla general, si más del **70% al 80%** de los elementos de una matriz son nulos, debe utilizarse una estructura dispersa.

---

## 2. Formato de Coordenadas (COO - Coordinate Format)

Almacena los $k$ elementos no nulos en tres arreglos paralelos o en un vector de estructuras:

```cpp
#include <iostream>
#include <vector>
using namespace std;

struct Elemento {
    int fila;
    int col;
    int valor;
};

class SparseMatrixCOO {
public:
    int filas, cols;
    vector<Elemento> elementos; // Tamaño k

    SparseMatrixCOO(int r, int c) : filas(r), cols(c) {}

    void insertar(int f, int c, int v) {
        if (v != 0) {
            elementos.push_back({f, c, v});
        }
    }

    int obtener(int f, int c) const {
        for (const auto& e : elementos) {
            if (e.fila == f && e.col == c) return e.valor;
        }
        return 0; // Si no está guardado, su valor es 0
    }
};
```

---

## 3. Formato de Fila Comprimida (CSR - Compressed Sparse Row)

Es el estándar de la industria científica (usado en SciPy, BLAS). Utiliza tres arreglos:
1. `valores`: Array con los $k$ valores no nulos.
2. `columnas`: Array con los índices de columna de cada valor en `valores`.
3. `fila_ptr`: Array de tamaño $N + 1$, donde `fila_ptr[i]` indica el índice en `valores` donde comienza la fila $i$.

```text
Matriz:
[ 0, 0, 3 ]
[ 4, 0, 0 ]
[ 0, 5, 0 ]

valores:   [ 3, 4, 5 ]
columnas:  [ 2, 0, 1 ]
fila_ptr:  [ 0, 1, 2, 3 ]
```

---

## 4. Representación por Listas Cruzadas (Ortogonales)

Cada celda no nula es un nodo con dos punteros: uno hacia el siguiente elemento no nulo de la misma **fila** (`sigCol`) y otro hacia el siguiente de la misma **columna** (`sigFila`).

```cpp
struct NodoCruzado {
    int fila;
    int col;
    int valor;
    NodoCruzado* derecha; // Siguiente en la misma fila
    NodoCruzado* abajo;   // Siguiente en la misma columna

    NodoCruzado(int f, int c, int v) 
        : fila(f), col(c), valor(v), derecha(nullptr), abajo(nullptr) {}
};
```
Ideal cuando la matriz sufre inserciones y eliminaciones dinámicas frecuentes durante la ejecución.

---

## 5. Operaciones Fundamentales en C++

### Transposición de Matriz COO
Transponer una matriz consiste en intercambiar filas por columnas: $(i, j, v) \rightarrow (j, i, v)$.

```cpp
SparseMatrixCOO transponer(const SparseMatrixCOO& mat) {
    SparseMatrixCOO transpuesta(mat.cols, mat.filas);
    for (const auto& e : mat.elementos) {
        transpuesta.insertar(e.col, e.fila, e.valor);
    }
    return transpuesta;
}
```

---

## 6. Tabla Comparativa de Representaciones

| Formato | Memoria | Acceso a $(i, j)$ | Inserción Dinámica | Mejor Caso de Uso |
| :--- | :---: | :---: | :---: | :--- |
| **Densa tradicional** | $O(N \cdot M)$ | $O(1)$ | $O(1)$ | Matrices con muchos valores |
| **COO** | $O(k)$ | $O(k)$ | $O(1)$ al final | Carga y construcción simple |
| **CSR** | $O(k + N)$ | $O(\log(\text{elementos fila}))$ | $O(k)$ (costoso reacomodar) | Multiplicación matriz-vector |
| **Listas Cruzadas** | $O(k)$ | $O(\text{elementos fila})$ | $O(\text{elementos fila})$ | Inserciones y borrados continuos |
