#include <stdio.h>
#include <stdlib.h>  // Necesario para malloc() y free()

int main() {
    int *numeros;  // Puntero a entero
    int n, i;

    printf("¿Cuántos números quieres almacenar? ");
    scanf("%d", &n);

    // Asignar memoria dinámica para n enteros
    numeros = (int*) malloc(n * sizeof(int));

    // Verificar si malloc falló
    if (numeros == NULL) {
        printf("Error: no se pudo asignar memoria.\n");
        return 1;
    }

    // Llenar el arreglo
    for (i = 0; i < n; i++) {
        printf("Introduce el número %d: ", i + 1);
        scanf("%d", &numeros[i]);
    }

    // Mostrar los números
    printf("\nNúmeros ingresados:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", numeros[i]);
    }

    // Liberar la memoria asignada
    free(numeros);

    return 0;
}
