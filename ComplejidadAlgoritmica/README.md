# Unidad 04: Complejidad Algorítmica y Notación Asintótica

> 📍 **Navegación:** [🏠 Menú Principal](../README.md) \| [📘 Guía Prueba 1](../Prueba_1/README.md) \| [📙 Guía Prueba 2](../Prueba_2/README.md)

---


## Índice
1. [Notaciones Asintóticas: $O$, $\Omega$ y $\Theta$](#1-notaciones-asintóticas-o-omega-y-theta)
2. [Reglas para Calcular Big-O](#2-reglas-para-calcular-big-o)
3. [Jerarquía de Complejidades](#3-jerarquía-de-complejidades)
4. [Análisis Temporal de Bucles en C++](#4-análisis-temporal-de-bucles-en-c)
5. [Análisis de Algoritmos Recursivos](#5-análisis-de-algoritmos-recursivos)
6. [Complejidad Espacial (Memoria Auxiliar)](#6-complejidad-espacial-memoria-auxiliar)
7. [Tabla Comparativa de Estructuras y Operaciones](#7-tabla-comparativa-de-estructuras-y-operaciones)
8. [Ejercicios Resueltos Paso a Paso](#8-ejercicios-resueltos-paso-a-paso)

---

## 1. Notaciones Asintóticas: $O$, $\Omega$ y $\Theta$

| Notación | Nombre | Significado Práctico | Enfoque |
| :--- | :--- | :--- | :--- |
| **$O(f(n))$** | Big-O | Cota superior asintótica (Peor caso) | "A lo sumo tardará esto" |
| **$\Omega(f(n))$** | Big-Omega | Cota inferior asintótica (Mejor caso) | "Como mínimo tardará esto" |
| **$\Theta(f(n))$** | Big-Theta | Cota ajustada (Comportamiento exacto) | "El tiempo crece exactamente a esta tasa" |

> En la asignatura de Estructura de Datos, **Big-O** es la métrica reina porque ofrece una garantía de rendimiento en el peor escenario posible.

---

## 2. Reglas para Calcular Big-O

1. **Eliminar constantes multiplicativas:** $O(7n) \rightarrow O(n)$, $O(500) \rightarrow O(1)$.
2. **Conservar solo el término dominante:** Si un algoritmo realiza $f(n) = 3n^2 + 100n + 5000$ operaciones, la complejidad es $O(n^2)$.
3. **Regla de la suma (bloques secuenciales):** Si el Bloque A toma $O(n)$ y el Bloque B toma $O(n^2)$, el total es $O(n + n^2) = O(n^2)$.
4. **Regla del producto (bloques anidados):** Si un bucle externo se ejecuta $n$ veces y dentro hay un bucle que se ejecuta $m$ veces, la complejidad es $O(n \cdot m)$.

---

## 3. Jerarquía de Complejidades

De la más eficiente a la más lenta:

$$\mathcal{O}(1) < \mathcal{O}(\log n) < \mathcal{O}(n) < \mathcal{O}(n \log n) < \mathcal{O}(n^2) < \mathcal{O}(n^3) < \mathcal{O}(2^n) < \mathcal{O}(n!)$$

* **$O(1)$ - Constante:** Acceso por índice en arreglos, `push`/`pop` en pila.
* **$O(\log n)$ - Logarítmica:** Búsqueda binaria, operaciones en árboles balanceados (AVL).
* **$O(n)$ - Lineal:** Recorrer una lista enlazada, búsqueda secuencial.
* **$O(n \log n)$ - Lineal-logarítmica:** Algoritmos eficientes de ordenamiento (MergeSort, HeapSort, QuickSort promedio).
* **$O(n^2)$ - Cuadrática:** Algoritmos de ordenamiento cuadráticos (Burbuja, Selección, Inserción), matrices bidimensionales.
* **$O(2^n)$ - Exponencial:** Fibonacci recursivo ingenuo, subconjuntos.

---

## 4. Análisis Temporal de Bucles en C++

### Bucle Lineal: $O(n)$
```cpp
// Se ejecuta exactamente n veces
for (int i = 0; i < n; i++) {
    cout << i << "\n";
}
```

### Bucles Anidados Cuadráticos: $O(n^2)$
```cpp
// El bucle interno se repite n veces por cada una de las n iteraciones externas
for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        matriz[i][j] = 0;
    }
}
```

### Bucle Logarítmico: $O(\log n)$
```cpp
// La variable se duplica o se divide a la mitad en cada paso
for (int i = 1; i < n; i *= 2) {
    cout << i << "\n";
}
```

---

## 5. Análisis de Algoritmos Recursivos

Cuando una función se llama a sí misma, debemos plantear una relación de recurrencia.

### Ejemplo 1: Factorial Recursivo
```cpp
int factorial(int n) {
    if (n <= 1) return 1;          // O(1)
    return n * factorial(n - 1);    // T(n) = T(n - 1) + O(1)
}
```
* **Tiempo:** $T(n) = T(n - 1) + 1 \rightarrow O(n)$.
* **Espacio:** $O(n)$ por la pila de llamadas (*call stack*).

### Ejemplo 2: Búsqueda Binaria
```cpp
int busquedaBinaria(const vector<int>& arr, int inicio, int fin, int objetivo) {
    if (inicio > fin) return -1;
    int medio = inicio + (fin - inicio) / 2;

    if (arr[medio] == objetivo) return medio;
    if (arr[medio] > objetivo) 
        return busquedaBinaria(arr, inicio, medio - 1, objetivo);
    else 
        return busquedaBinaria(arr, medio + 1, fin, objetivo);
}
```
* En cada paso, el espacio de búsqueda se reduce a la mitad: $T(n) = T(n/2) + O(1) \rightarrow O(\log n)$.

---

## 6. Complejidad Espacial (Memoria Auxiliar)

Mide la cantidad de memoria **adicional** que requiere el algoritmo, sin contar la memoria de la entrada:

```cpp
// Complejidad Espacial O(1): Solo usa variables simples fijas
int suma(int arr[], int n) {
    int total = 0; // O(1)
    for (int i = 0; i < n; i++) {
        total += arr[i];
    }
    return total;
}

// Complejidad Espacial O(n): Crea un vector dinámico dependiente de n
vector<int> duplicarElementos(const vector<int>& arr) {
    vector<int> nuevo; // Crece proporcional a n -> O(n)
    for (int x : arr) nuevo.push_back(x * 2);
    return nuevo;
}
```

---

## 7. Tabla Comparativa de Estructuras y Operaciones

| Estructura de Datos | Acceso por índice | Búsqueda | Inserción (inicio) | Inserción (final) | Eliminación |
| :--- | :---: | :---: | :---: | :---: | :---: |
| **Arreglo estático / Vector** | $O(1)$ | $O(n)$ | $O(n)$ | $O(1)$ amortizado | $O(n)$ |
| **Lista Enlazada Simple** | $O(n)$ | $O(n)$ | $O(1)$ | $O(n)$ (u $O(1)$ con cola) | $O(n)$ / $O(1)$ |
| **Pila (Stack)** | N/A | $O(n)$ | $O(1)$ (`push`) | N/A | $O(1)$ (`pop`) |
| **Cola (Queue)** | N/A | $O(n)$ | $O(1)$ (`push`) | N/A | $O(1)$ (`pop`) |
| **Árbol Binario Búsqueda (ABB)**| N/A | $O(\log n)$ prom / $O(n)$ peor | $O(\log n)$ prom | N/A | $O(\log n)$ prom |
| **Árbol AVL (Balanceado)** | N/A | $O(\log n)$ siempre | $O(\log n)$ siempre | N/A | $O(\log n)$ siempre |
| **Montículo (Heap)** | $O(1)$ (máx/mín) | $O(n)$ | $O(\log n)$ | N/A | $O(\log n)$ (`extract`) |

---

## 8. Ejercicios Resueltos Paso a Paso

### Ejercicio 1: ¿Cuál es la complejidad del siguiente código?
```cpp
void misterio(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < n; j *= 2) {
            cout << "Paso\n";
        }
    }
}
```
* **Solución:**
  - El bucle externo recorre desde $i = 0$ hasta $n-1 \rightarrow n$ iteraciones.
  - El bucle interno multiplica $j$ por $2$ en cada iteración $\rightarrow \log_2(n)$ iteraciones.
  - Al estar anidados, multiplicamos ambas: $n \times \log_2(n) = \mathbf{O(n \log n)}$.
