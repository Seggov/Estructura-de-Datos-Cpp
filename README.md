# Repositorio Maestro: Estructura de Datos en C++

Bienvenido a la biblioteca y mapa de contenidos oficial para el curso de **Estructura de Datos en C++**. Este repositorio reúne conceptos teóricos, implementaciones completas en C++, análisis de complejidad algorítmica y guías intensivas clasificadas para la preparación de la **Prueba 1** y la **Prueba 2**.

---

## 🗺️ Mapa de Navegación del Repositorio

El contenido está modularizado en carpetas temáticas independientes. Cada carpeta cuenta con su propio `README.md` detallado con explicaciones, sintaxis y código funcional.

### 📚 Guías Centrales de Evaluación
* 🎯 [**Contenidos y Preparación para la Prueba 1**](Prueba_1/README.md)
* 🎯 [**Contenidos y Preparación para la Prueba 2**](Prueba_2/README.md)
* 📖 [**Material y Ejercicios Prácticos del Curso**](CodigoFuncionesAprenderYUtilizar/README.md)

---

### 📂 Unidades Temáticas (Orden Didáctico)

| Unidad | Carpeta | Temas Principales | Bloque de Evaluación |
| :---: | :--- | :--- | :---: |
| **00** | [**Debugging**](Debugging/README.md) | Banderas GCC, GDB, AddressSanitizer, prevención de SegFault | Fundamentos |
| **01** | [**Punteros**](Punteros/readme.md) | Punteros `T*`, Referencias `T&`, Memoria dinámica `new`/`delete`, `nullptr` | **Prueba 1** |
| **02** | [**LecturaArchivos**](LecturaArchivos/readme.md) | `<fstream>`, parseo CSV con `stringstream`, `stoi`, `stod` | **Prueba 1** |
| **03** | [**ConexionesClases**](ConexionesClases/readme.md) | POO, archivos `.hpp`/`.cpp`, constructores, destructores, composición | **Prueba 1** |
| **04** | [**ComplejidadAlgoritmica**](ComplejidadAlgoritmica/README.md) | Notación Big-O, análisis temporal y espacial de bucles y recursión | **Prueba 1** |
| **05** | [**NodosYListasEnlazadas**](NodosYListasEnlazadas/README.md) | Nodos, listas simples, dobles y circulares, operaciones primitivas | **Prueba 1** |
| **06** | [**PilasYColas**](PilasYColas/README.md) | Pila LIFO (`stack`), Cola FIFO (`queue`), implementación manual y STL | **Prueba 1** |
| **07** | [**ArbolesBinarios**](ArbolesBinarios/README.md) | Árboles Binarios, ABB (BST), inserción, eliminación (3 casos), inorden | **Prueba 2** |
| **08** | [**ArbolesAVL**](ArbolesAVL/README.md) | Árboles balanceados AVL, Factor de Balance, las 4 Rotaciones (LL, RR, LR, RL) | **Prueba 2** |
| **09** | [**HeapsYHeapSort**](HeapsYHeapSort/README.md) | Max/Min Heap en arreglo, `heapify`, `buildHeap`, `priority_queue`, HeapSort | **Prueba 2** |
| **10** | [**AlgoritmosArboles**](AlgoritmosArboles/README.md) | Recorrido BFS por niveles, reconstrucción Pre+In/Post+In, LCA, validar BST | **Prueba 2** |
| **11** | [**Grafos**](Grafos/readme.md) | Definición formal, dígrafos, matriz de adyacencia vs lista de adyacencia | **Prueba 2** |
| **12** | [**AlgoritmosGrafos**](AlgoritmosGrafos/README.md) | DFS, BFS, Dijkstra (caminos mínimos), Kruskal (DSU) y Prim (MST) | **Prueba 2** |
| **13** | [**MinimaxYAlfaBeta**](MinimaxYAlfaBeta/README.md) | Árboles de juego de dos jugadores, algoritmo Minimax y Poda Alfa-Beta | **Prueba 2** |
| **14** | [**MatricesDispersas**](MatricesDispersas/README.md) | Sparse Matrix, formato COO, CSR y listas cruzadas ortogonales | **Prueba 2** |

---

## 📖 Diccionario Cronológico de Conceptos y Funciones

A continuación se detalla cada concepto y función que se puede utilizar a lo largo del curso, ordenado paso a paso según el progreso pedagógico:

```text
Bloque 1 (Prueba 1):
  1. Punteros y Memoria Dinámica
  2. Flujos de Entrada/Salida y Parseo de Archivos
  3. Clases, Modularización y Encapsulamiento
  4. Análisis Asintótico y Big-O
  5. Estructuras Lineales: Nodos y Listas Enlazadas
  6. Pilas (Stacks) y Colas (Queues)

Bloque 2 (Prueba 2):
  7. Árboles Binarios y ABB
  8. Árboles Balanceados AVL
  9. Montículos (Heaps), Colas de Prioridad y HeapSort
  10. Algoritmos Avanzados en Árboles
  11. Grafos y Representaciones
  12. Algoritmos en Grafos (BFS, DFS, Dijkstra, Kruskal, Prim)
  13. Algoritmo Minimax y Poda Alfa-Beta
  14. Matrices Poco Pobladas (Sparse Matrices)
```

---

### 1. Punteros y Gestión de Memoria Dinámica

#### `&` (Operador Address-Of / Dirección)
Obtiene la dirección de memoria física donde reside una variable:
```cpp
int x = 42;
cout << "Direccion de x: " << &x << endl; // Ej: 0x7ffd12a4
```

#### `*` (Operador de Desreferenciación / Puntero)
Declara una variable puntero o accede al valor apuntado por la dirección de memoria:
```cpp
int x = 42;
int* ptr = &x;  // Declaración: ptr guarda la dirección de x
*ptr = 100;     // Desreferenciación: modifica x a través de ptr
```

#### `nullptr`
Literal de puntero nulo introducido en C++11. Representa que el puntero no apunta a ninguna dirección válida de memoria.
```cpp
int* p = nullptr;
if (p != nullptr) {
    *p = 5;
}
```

#### `new` y `delete`
Solicita memoria en el Heap (tiempo de ejecución) y la libera manualmente para evitar *Memory Leaks*:
```cpp
// Variable individual
int* ptr = new int(10);
delete ptr;
ptr = nullptr;

// Arreglo dinámico
int n = 5;
int* arr = new int[n];
delete[] arr; // OBLIGATORIO usar delete[] para arreglos
arr = nullptr;
```

#### `T**` (Doble Puntero / Puntero a Puntero)
Almacena la dirección de memoria de otro puntero. Indispensable para crear matrices dinámicas bidimensionales o pasar la cabeza de una lista enlazada por referencia en funciones en C estilo C puro.
```cpp
int filas = 3, cols = 4;
int** matriz = new int*[filas];
for (int i = 0; i < filas; i++) {
    matriz[i] = new int[cols];
}

// Liberación
for (int i = 0; i < filas; i++) {
    delete[] matriz[i];
}
delete[] matriz;
```

---

### 2. Flujos de Archivos y Parseo (`<fstream>`, `<sstream>`)

#### `std::ifstream` y `std::ofstream`
Flujos para lectura (`ifstream`) y escritura (`ofstream`) de archivos en disco:
```cpp
#include <fstream>
using namespace std;

// Lectura
ifstream entrada("datos.txt");
if (entrada.is_open()) {
    // Procesar...
    entrada.close();
}

// Escritura
ofstream salida("reporte.txt", ios::app); // ios::app para no sobreescribir
salida << "Resultado: " << 100 << endl;
salida.close();
```

#### `std::getline(flujo, variable, delimitador)`
Lee caracteres desde un flujo de entrada hasta topar con un salto de línea (`\n`) o un delimitador específico (como `,`):
```cpp
#include <sstream>
string linea = "12345678-9,Juan Perez,30";
stringstream ss(linea);

string rut, nombre, edadStr;
getline(ss, rut, ',');
getline(ss, nombre, ',');
getline(ss, edadStr, ',');
```

#### Conversiones Numéricas: `std::stoi`, `std::stod`, `std::to_string`
Convierte cadenas de texto a tipos numéricos primitivos y viceversa:
```cpp
int edad = stoi("25");
double precio = stod("19.95");
string texto = to_string(500);
```

---

### 3. Programación Orientada a Objetos en C++

#### Estructura Modular: `#pragma once`
Directiva que se coloca en la primera línea de archivos de cabecera (`.hpp`) para evitar que el compilador procese el mismo archivo varias veces:
```cpp
// Estudiante.hpp
#pragma once
#include <string>

class Estudiante {
private:
    std::string nombre;
    int matricula;

public:
    Estudiante(std::string nombre, int matricula);
    ~Estudiante();
    void estudiar();
};
```

#### Lista de Inicialización de Constructores
Permite inicializar los atributos de clase de forma eficiente y directa antes del cuerpo del constructor:
```cpp
Estudiante::Estudiante(std::string n, int m) : nombre(n), matricula(m) {
    // Cuerpo del constructor
}
```

#### Destructor (`~Clase()`)
Método especial que se ejecuta automáticamente cuando el objeto sale de ámbito o se destruye con `delete`. **Es el lugar donde se deben liberar todos los nodos de listas, árboles o grafos**:
```cpp
ListaEnlazada::~ListaEnlazada() {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        Nodo* aBorrar = actual;
        actual = actual->siguiente;
        delete aBorrar;
    }
}
```

#### Puntero `this` y Operador Flecha `->`
El operador `->` desreferencia un puntero a objeto y accede a sus miembros:
```cpp
Estudiante* est = new Estudiante("Lucas", 2026);
est->estudiar(); // Equivale a (*est).estudiar()
delete est;
```

---

### 4. Análisis Asintótico y Complejidad Big-O

| Notación | Nombre | Crecimiento con respecto a $n$ |
| :--- | :--- | :--- |
| **$O(1)$** | Tiempo constante | No depende de $n$ (acceso `arr[i]`, `push` en pila) |
| **$O(\log n)$** | Tiempo logarítmico | Divide el espacio a la mitad en cada paso (búsqueda binaria) |
| **$O(n)$** | Tiempo lineal | Recorre los $n$ elementos secuencialmente (recorrer lista) |
| **$O(n \log n)$** | Tiempo lineal-logarítmico | Ordenamiento óptimo (HeapSort, MergeSort) |
| **$O(n^2)$** | Tiempo cuadrático | Bucles anidados de dos niveles (BubbleSort, matriz $N \times N$) |
| **$O(2^n)$** | Tiempo exponencial | Algoritmos de fuerza bruta recursiva sin memorización |

---

### 5. Estructuras Lineales: Nodos y Listas Enlazadas

#### El `Nodo`
Unidad básica enlazada en memoria dinámica:
```cpp
struct Nodo {
    int dato;
    Nodo* siguiente;
    Nodo(int v) : dato(v), siguiente(nullptr) {}
};
```

#### Operaciones en Lista Simple:
```cpp
// 1. Inserción al inicio -> O(1)
void insertarInicio(Nodo*& cabeza, int valor) {
    Nodo* nuevo = new Nodo(valor);
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
}

// 2. Inserción al final -> O(n) sin tail / O(1) con tail
void insertarFinal(Nodo*& cabeza, int valor) {
    Nodo* nuevo = new Nodo(valor);
    if (cabeza == nullptr) {
        cabeza = nuevo;
        return;
    }
    Nodo* actual = cabeza;
    while (actual->siguiente != nullptr) {
        actual = actual->siguiente;
    }
    actual->siguiente = nuevo;
}

// 3. Búsqueda -> O(n)
bool buscar(Nodo* cabeza, int valor) {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        if (actual->dato == valor) return true;
        actual = actual->siguiente;
    }
    return false;
}

// 4. Eliminación -> O(n)
void eliminar(Nodo*& cabeza, int valor) {
    if (cabeza == nullptr) return;
    if (cabeza->dato == valor) {
        Nodo* aBorrar = cabeza;
        cabeza = cabeza->siguiente;
        delete aBorrar;
        return;
    }
    Nodo* actual = cabeza;
    while (actual->siguiente != nullptr && actual->siguiente->dato != valor) {
        actual = actual->siguiente;
    }
    if (actual->siguiente != nullptr) {
        Nodo* aBorrar = actual->siguiente;
        actual->siguiente = actual->siguiente->siguiente;
        delete aBorrar;
    }
}
```

---

### 6. Pilas (Stacks) y Colas (Queues)

#### Métodos de Pila (`std::stack<T>` o Pila Dinámica):
* `push(x)`: Apila un elemento en la cima ($O(1)$).
* `pop()`: Desapila el elemento de la cima ($O(1)$).
* `top()`: Consulta el elemento de la cima ($O(1)$).
* `empty()`: Comprueba si la pila no tiene elementos ($O(1)$).

```cpp
#include <stack>
stack<int> s;
s.push(10);
s.push(20);
int cima = s.top(); // 20
s.pop();
```

#### Métodos de Cola (`std::queue<T>` o Cola Dinámica):
* `push(x)` / `enqueue(x)`: Encola al final ($O(1)$).
* `pop()` / `dequeue()`: Desencola del frente ($O(1)$).
* `front()`: Consulta el primer elemento ($O(1)$).
* `back()`: Consulta el último elemento ($O(1)$).

```cpp
#include <queue>
queue<string> q;
q.push("Atencion 1");
q.push("Atencion 2");
string primero = q.front(); // "Atencion 1"
q.pop();
```

---

### 7. Árboles Binarios y ABB (BST)

#### Propiedad de Orden del ABB
Para cualquier nodo $N$:
$$\text{valores}(N \rightarrow \text{izq}) < N \rightarrow \text{dato} < \text{valores}(N \rightarrow \text{der})$$

#### Operaciones en ABB:
```cpp
struct NodoArbol {
    int dato;
    NodoArbol* izq;
    NodoArbol* der;
    NodoArbol(int v) : dato(v), izq(nullptr), der(nullptr) {}
};

// Inserción en ABB -> O(log n) promedio
NodoArbol* insertarABB(NodoArbol* raiz, int valor) {
    if (raiz == nullptr) return new NodoArbol(valor);
    if (valor < raiz->dato) raiz->izq = insertarABB(raiz->izq, valor);
    else if (valor > raiz->dato) raiz->der = insertarABB(raiz->der, valor);
    return raiz;
}

// Recorrido Inorden (produce elementos ordenados de menor a mayor)
void inorden(NodoArbol* raiz) {
    if (raiz == nullptr) return;
    inorden(raiz->izq);
    cout << raiz->dato << " ";
    inorden(raiz->der);
}
```

---

### 8. Árboles Balanceados AVL

#### Factor de Balance (FB)
$$\text{FB}(N) = \text{altura}(N \rightarrow \text{izq}) - \text{altura}(N \rightarrow \text{der}) \in \{-1, 0, 1\}$$

#### Las 4 Rotaciones:
* **LL (Rotación Simple Derecha):** Desbalance en el hijo izquierdo hacia la izquierda.
* **RR (Rotación Simple Izquierda):** Desbalance en el hijo derecho hacia la derecha.
* **LR (Rotación Doble Izq-Der):** Rotación izquierda en el hijo izquierdo, luego derecha en la raíz.
* **RL (Rotación Doble Der-Izq):** Rotación derecha en el hijo derecho, luego izquierda en la raíz.

```cpp
NodoAVL* rotacionDerecha(NodoAVL* z) {
    NodoAVL* y = z->izq;
    NodoAVL* T3 = y->der;
    y->der = z;
    z->izq = T3;
    z->altura = 1 + max(getAltura(z->izq), getAltura(z->der));
    y->altura = 1 + max(getAltura(y->izq), getAltura(y->der));
    return y;
}
```

---

### 9. Montículos (Heaps) y HeapSort

#### Mapeo Matemático de Índices en Arreglo:
* Hijo Izquierdo: $2i + 1$
* Hijo Derecho: $2i + 2$
* Padre: $\lfloor(i - 1) / 2\rfloor$

#### Función `heapify` (Hundir):
```cpp
void heapify(vector<int>& arr, int n, int i) {
    int mayor = i;
    int izq = 2 * i + 1;
    int der = 2 * i + 2;

    if (izq < n && arr[izq] > arr[mayor]) mayor = izq;
    if (der < n && arr[der] > arr[mayor]) mayor = der;

    if (mayor != i) {
        swap(arr[i], arr[mayor]);
        heapify(arr, n, mayor);
    }
}
```

#### Algoritmo `heapSort`:
```cpp
void heapSort(vector<int>& arr) {
    int n = arr.size();
    // 1. Construir Max-Heap -> O(n)
    for (int i = (n / 2) - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    // 2. Extracciones sucesivas -> O(n log n)
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
```

---

### 10. Algoritmos Avanzados en Árboles

#### Recorrido por Niveles (BFS con Cola)
```cpp
void recorridoPorNiveles(NodoArbol* raiz) {
    if (raiz == nullptr) return;
    queue<NodoArbol*> cola;
    cola.push(raiz);
    while (!cola.empty()) {
        NodoArbol* actual = cola.front();
        cola.pop();
        cout << actual->dato << " ";
        if (actual->izq != nullptr) cola.push(actual->izq);
        if (actual->der != nullptr) cola.push(actual->der);
    }
}
```

#### Validación de BST con Rango $(\min, \max)$
```cpp
bool esBSTValido(NodoArbol* raiz, long long minVal, long long maxVal) {
    if (raiz == nullptr) return true;
    if (raiz->dato <= minVal || raiz->dato >= maxVal) return false;
    return esBSTValido(raiz->izq, minVal, raiz->dato) &&
           esBSTValido(raiz->der, raiz->dato, maxVal);
}
```

---

### 11. Grafos y sus Representaciones

#### Matriz de Adyacencia vs Lista de Adyacencia:
```cpp
// Matriz de Adyacencia: Acceso O(1), Memoria O(V^2)
vector<vector<int>> matrizAdy(V, vector<int>(V, 0));
matrizAdy[u][v] = peso;

// Lista de Adyacencia: Vecinos O(grado(u)), Memoria O(V + E)
vector<vector<pair<int, int>>> listaAdy(V);
listaAdy[u].push_back({v, peso});
```

---

### 12. Algoritmos Clásicos en Grafos

#### DFS (Búsqueda en Profundidad):
```cpp
void dfs(int u, const vector<vector<int>>& ady, vector<bool>& visitado) {
    visitado[u] = true;
    for (int v : ady[u]) {
        if (!visitado[v]) dfs(v, ady, visitado);
    }
}
```

#### Dijkstra (Camino Más Corto con Pesos Positivos):
```cpp
vector<int> dijkstra(int origen, int V, const vector<vector<pair<int, int>>>& ady) {
    vector<int> dist(V, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[origen] = 0;
    pq.push({0, origen});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto& arista : ady[u]) {
            int v = arista.first;
            int peso = arista.second;
            if (dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}
```

---

### 13. Algoritmo Minimax y Poda Alfa-Beta

#### Minimax con Poda Alfa-Beta:
```cpp
int minimaxAlfaBeta(int prof, int nodo, bool esMax, int valores[], int alfa, int beta, int h) {
    if (prof == h) return valores[nodo];

    if (esMax) {
        int mejor = INT_MIN;
        for (int i = 0; i < 2; i++) {
            int val = minimaxAlfaBeta(prof + 1, nodo * 2 + i, false, valores, alfa, beta, h);
            mejor = max(mejor, val);
            alfa = max(alfa, mejor);
            if (beta <= alfa) break; // Poda Alfa
        }
        return mejor;
    } else {
        int mejor = INT_MAX;
        for (int i = 0; i < 2; i++) {
            int val = minimaxAlfaBeta(prof + 1, nodo * 2 + i, true, valores, alfa, beta, h);
            mejor = min(mejor, val);
            beta = min(beta, mejor);
            if (beta <= alfa) break; // Poda Beta
        }
        return mejor;
    }
}
```

---

### 14. Matrices Poco Pobladas (Sparse Matrices)

#### Formato COO (Coordinate List):
```cpp
struct ElementoCOO {
    int fila, col, valor;
};
vector<ElementoCOO> sparseCOO;
// Inserta solo valores no nulos
if (valor != 0) sparseCOO.push_back({f, c, valor});
```

---

## 📊 Tabla Maestra de Complejidades

| Estructura / Algoritmo | Acceso | Búsqueda | Inserción | Eliminación | Espacio |
| :--- | :---: | :---: | :---: | :---: | :---: |
| **Arreglo Contiguo (`vector`)** | $O(1)$ | $O(n)$ | $O(1)$ final / $O(n)$ inicio | $O(n)$ | $O(n)$ |
| **Lista Enlazada Simple** | $O(n)$ | $O(n)$ | $O(1)$ inicio / $O(n)$ final | $O(n)$ | $O(n)$ |
| **Lista Doblemente Enlazada** | $O(n)$ | $O(n)$ | $O(1)$ inicio / $O(1)$ final | $O(1)$ con nodo | $O(n)$ |
| **Pila (`std::stack`)** | $O(1)$ cima | $O(n)$ | $O(1)$ (`push`) | $O(1)$ (`pop`) | $O(n)$ |
| **Cola (`std::queue`)** | $O(1)$ frente | $O(n)$ | $O(1)$ (`push`) | $O(1)$ (`pop`) | $O(n)$ |
| **Árbol Binario Búsqueda (ABB)**| N/A | $O(\log n)$ prom / $O(n)$ peor | $O(\log n)$ prom / $O(n)$ peor | $O(\log n)$ prom | $O(n)$ |
| **Árbol Balanceado AVL** | N/A | $\mathbf{O(\log n)}$ siempre | $\mathbf{O(\log n)}$ siempre | $\mathbf{O(\log n)}$ siempre | $O(n)$ |
| **Montículo Binario (Heap)** | $O(1)$ raíz | $O(n)$ | $O(\log n)$ | $O(\log n)$ raíz | $O(n)$ |
| **HeapSort** | N/A | N/A | N/A | N/A | $\mathbf{O(1)}$ aux |
| **Dijkstra con Min-Heap** | N/A | N/A | N/A | N/A | $O(V)$ aux |
| **Minimax con Poda Óptima** | N/A | N/A | N/A | N/A | $O(b \cdot d)$ |
| **Sparse Matrix (COO / CSR)** | $O(k)$ / $O(\log k)$ | $O(k)$ | $O(1)$ al final | $O(k)$ | $\mathbf{O(k)}$ |

---

## 🎯 Recomendaciones para el Estudio y Certámenes

1. **Memoria primero:** Antes de compilar, revisa si cada `new` tiene su respectivo `delete`.
2. **Valida `nullptr`:** El 80% de los errores en certámenes son por intentar leer `actual->dato` cuando `actual == nullptr`.
3. **Dibuja la estructura:** En ejercicios de árboles AVL, HeapSort o Dijkstra, haz el dibujo esquemático antes de escribir código.
4. **Comprueba casos borde:** Lista vacía, árbol con un solo nodo, búsqueda de un elemento inexistente, valor en la raíz.
