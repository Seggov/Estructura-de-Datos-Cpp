# Unidad 00: Herramientas y Técnicas de Debugging en C++

> 📍 **Navegación:** [🏠 Menú Principal](../README.md) \| [📘 Guía Prueba 1](../Prueba_1/README.md) \| [📙 Guía Prueba 2](../Prueba_2/README.md)

---


## Índice
1. [Banderas Esenciales del Compilador (GCC / Clang)](#1-banderas-esenciales-del-compilador-gcc--clang)
2. [Anatomía del Segmentation Fault](#2-anatomía-del-segmentation-fault)
3. [Memory Leaks y Detección con Sanitizers](#3-memory-leaks-y-detección-con-sanitizers)
4. [Uso de AddressSanitizer (ASan)](#4-uso-de-addresssanitizer-asan)
5. [Depuración Interactiva con GDB / LLDB](#5-depuración-interactiva-con-gdb--lldb)
6. [Programación Defensiva en Estructuras Dinámicas](#6-programación-defensiva-en-estructuras-dinámicas)
7. [Resumen de Comandos Útiles](#7-resumen-de-comandos-útiles)

---

## 1. Banderas Esenciales del Compilador (GCC / Clang)

Al compilar tus proyectos de C++, no uses solo `g++ main.cpp`. Agrega banderas estrictas que te alerten de errores potenciales antes de ejecutar:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic -g main.cpp -o app
```

* `-std=c++17`: Habilita el estándar moderno de C++.
* `-Wall`: Activa todas las advertencias comunes de código dudoso.
* `-Wextra`: Activa advertencias adicionales (variables no usadas, conversiones con signo, etc.).
* `-g`: Incluye información y símbolos de depuración para poder ver números de línea exactos en GDB o crash reports.

---

## 2. Anatomía del Segmentation Fault

Un **Segmentation Fault (SIGSEGV)** ocurre cuando el programa intenta leer o escribir en una dirección de memoria a la que el sistema operativo no le dio permiso.

### Causa 1: Desreferenciar `nullptr`
```cpp
struct Nodo {
    int valor;
    Nodo* sig;
};

Nodo* actual = nullptr;
cout << actual->valor; // 💥 CRASH: Acceso a dirección 0x0
```
**Solución:** Validar siempre con `if (actual != nullptr)` antes de acceder a miembros.

### Causa 2: Acceso fuera de los límites de un arreglo
```cpp
int lista[5] = {1, 2, 3, 4, 5};
cout << lista[10]; // 💥 Comportamiento indefinido o Segmentation fault
```

### Causa 3: Desbordamiento de Pila (*Stack Overflow*) por Recursión Infinita
Típico al implementar recorridos o búsquedas en árboles sin caso base:
```cpp
void recorrer(Nodo* raiz) {
    // ❌ Olvidar: if (raiz == nullptr) return;
    recorrer(raiz->izq);
}
```

---

## 3. Memory Leaks y Detección con Sanitizers

Una fuga de memoria (*Memory Leak*) ocurre cuando reservas memoria en el Heap con `new` y pierdes el puntero sin haber invocado `delete`.

```cpp
void fuga() {
    int* buffer = new int[1000];
    // Olvido de delete[] buffer;
} // 'buffer' desaparece del stack, pero los 1000 ints siguen atrapados en el Heap
```

---

## 4. Uso de AddressSanitizer (ASan)

La herramienta más moderna y rápida para detectar accesos inválidos y memory leaks integrada directamente en GCC y Clang:

```bash
g++ -fsanitize=address -g main.cpp -o app_sanitizer
./app_sanitizer
```

Si tu programa tiene un desbordamiento o fuga, ASan detendrá la ejecución al instante y te mostrará el archivo y la línea exacta del error:
```text
==12345==ERROR: AddressSanitizer: heap-use-after-free on address 0x602000000010
READ of size 4 at 0x602000000010 thread T0
    #0 0x401234 in main main.cpp:18
```

---

## 5. Depuración Interactiva con GDB / LLDB

GDB permite pausar el programa en puntos estratégicos (*breakpoints*), inspeccionar variables y rastrear llamadas:

```bash
# Iniciar depuración
gdb ./app

# Comandos esenciales dentro de GDB:
(gdb) break main            # Poner punto de interrupción en la función main
(gdb) break Lista.cpp:45    # Poner breakpoint en línea 45 de Lista.cpp
(gdb) run                   # Iniciar ejecución
(gdb) next                  # Ejecutar la siguiente línea (sin entrar a funciones)
(gdb) step                  # Entrar dentro de la función actual
(gdb) print ptr             # Ver el valor/dirección del puntero 'ptr'
(gdb) print *ptr            # Ver el contenido al que apunta 'ptr'
(gdb) backtrace             # (bt) Ver la pila de llamadas en el momento exacto del crash
(gdb) quit                  # Salir de GDB
```

---

## 6. Programación Defensiva en Estructuras Dinámicas

1. **Inicialización inmediata:** Siempre inicializa punteros al declararlos (`Nodo* sig = nullptr;`).
2. **Nulificación tras liberación:**
   ```cpp
   delete nodo;
   nodo = nullptr; // Evita el dangling pointer
   ```
3. **Aserciones en tiempo de depuración:** Utiliza `<cassert>` para validar precondiciones:
   ```cpp
   #include <cassert>
   void eliminarPrimero(Nodo*& cabeza) {
       assert(cabeza != nullptr && "Error: No se puede eliminar de una lista vacía");
       Nodo* temp = cabeza;
       cabeza = cabeza->sig;
       delete temp;
   }
   ```

---

## 7. Resumen de Comandos Útiles

| Herramienta | Comando | Utilidad |
| :--- | :--- | :--- |
| **GCC con advertencias** | `g++ -Wall -Wextra -g *.cpp` | Detección estática de errores |
| **AddressSanitizer** | `g++ -fsanitize=address -g *.cpp` | Detección dinámica de memoria |
| **Valgrind (Linux/WSL)**| `valgrind --leak-check=full ./app` | Análisis exhaustivo de fugas |
| **GDB** | `gdb ./app` | Depurador paso a paso |
