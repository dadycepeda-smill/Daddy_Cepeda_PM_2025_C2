#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definimos la estructura del Producto
typedef struct {
    int id;
    char nombre[50];
    int cantidad;
    float precio;
} Producto;

// --- PROTOTIPOS DE FUNCIONES (Para cumplir el punto 1: Modularidad) ---
Producto* cargarInventario(const char* nombreArchivo, int* n);
void guardarProducto(const char* nombreArchivo, Producto p);
void mostrarInventario(Producto* inventario, int n);
void liberarMemoria(Producto* inventario);

int main() {
    char opcion;
    int cantidadProductos = 0;
    const char* NOMBRE_ARCHIVO = "inventario.txt";

    // 1. y 4. Leer archivo y cargar en memoria dinámica
    printf("--- Cargando inventario desde archivo ---\n");
    Producto* inventario = cargarInventario(NOMBRE_ARCHIVO, &cantidadProductos);

    if (inventario != NULL || cantidadProductos == 0) {
        printf("Inventario cargado exitosamente. Productos actuales: %d\n\n", cantidadProductos);
    } else {
        printf("No se pudo cargar el inventario o el archivo no existe aun.\n\n");
    }

    // 3. Preguntar si quiere escribir un producto nuevo
    printf("2. Desea agregar un producto nuevo al inventario? (s/n): ");
    scanf(" %c", &opcion); // El espacio antes de %c limpia el buffer

    if (opcion == 's' || opcion == 'S') {
        Producto nuevo;
        // Asignar ID automático (el siguiente disponible)
        nuevo.id = cantidadProductos + 1;

        printf("Ingrese nombre del producto: ");
        scanf("%s", nuevo.nombre);
        printf("Ingrese cantidad: ");
        scanf("%d", &nuevo.cantidad);
        printf("Ingrese precio: ");
        scanf("%f", &nuevo.precio);

        // Guardar en el archivo físico
        guardarProducto(NOMBRE_ARCHIVO, nuevo);

        // Actualizar la memoria dinámica (Aumentar el tamaño del arreglo en 1)
        cantidadProductos++;
        inventario = (Producto*) realloc(inventario, cantidadProductos * sizeof(Producto));

        // Verificar si realloc funcionó
        if (inventario != NULL) {
            inventario[cantidadProductos - 1] = nuevo; // Guardar en la última posición
            printf("Producto guardado y cargado en memoria.\n\n");
        } else {
            printf("Error al reasignar memoria RAM.\n");
        }
    }

    // 5. Preguntar si quiere imprimir los productos
    printf("3. Desea ver el reporte de productos en inventario? (s/n): ");
    scanf(" %c", &opcion);

    if (opcion == 's' || opcion == 'S') {
        mostrarInventario(inventario, cantidadProductos);
    }

    // Liberar memoria antes de salir
    liberarMemoria(inventario);

    printf("\nFin del programa.\n");
    return 0;
}

// --- IMPLEMENTACIÓN DE LAS FUNCIONES ---

// Función para leer el archivo y cargarlo en un arreglo dinámico
Producto* cargarInventario(const char* nombreArchivo, int* n) {
    FILE* archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        *n = 0;
        return NULL; // El archivo no existe todavía
    }

    Producto* lista = NULL;
    Producto temp;
    int contador = 0;

    // Leer línea por línea del archivo
    while (fscanf(archivo, "%d %s %d %f", &temp.id, temp.nombre, &temp.cantidad, &temp.precio) == 4) {
        contador++;
        // Redimensionar la memoria dinámica para alojar el nuevo producto
        // realloc: cambia el tamaño del bloque de memoria conservando los datos anteriores
        Producto* tempLista = (Producto*) realloc(lista, contador * sizeof(Producto));

        if (tempLista == NULL) {
            printf("Error: Memoria insuficiente.\n");
            free(lista);
            fclose(archivo);
            return NULL;
        }
        lista = tempLista;

        // Guardar el producto leído en la última posición
        lista[contador - 1] = temp;
    }

    fclose(archivo);
    *n = contador; // Actualizar la variable de cantidad en el main
    return lista; // Devolver el puntero al arreglo dinámico
}

// Función para agregar un producto al final del archivo de texto
void guardarProducto(const char* nombreArchivo, Producto p) {
    FILE* archivo = fopen(nombreArchivo, "a"); // "a" significa append (agregar al final)
    if (archivo == NULL) {
        printf("Error al abrir el archivo para guardar.\n");
        return;
    }
    fprintf(archivo, "%d %s %d %.2f\n", p.id, p.nombre, p.cantidad, p.precio);
    fclose(archivo);
}

// Función para mostrar la lista
void mostrarInventario(Producto* inventario, int n) {
    if (n == 0 || inventario == NULL) {
        printf("\nEl inventario esta vacio.\n");
        return;
    }

    printf("\n--- REPORTE DE INVENTARIO ---\n");
    printf("ID\tNombre\t\tCant.\tPrecio\n");
    printf("--------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%s\t\t%d\t$%.2f\n",
               inventario[i].id,
               inventario[i].nombre,
               inventario[i].cantidad,
               inventario[i].precio);
    }
    printf("--------------------------------------\n");
}

// Función para liberar la memoria dinámica
void liberarMemoria(Producto* inventario) {
    if (inventario != NULL) {
        free(inventario);
    }
}
