#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- ESTRUCTURAS DE DATOS ---

typedef struct {
    int id;
    char nombre[30]; // Ej: Gasolina Premium, Diesel
    float precioPorLitro;
} Combustible;

typedef struct {
    int id;
    char marca[30];
    char modelo[30];
    int anio;
    char placa[15];
    float consumoCiudad;    // Litros por 100km
    float consumoCarretera; // Litros por 100km
    float costoSeguroAnio;
    float costoCambioPorKm; // Costo mantenimiento/aceite por km
    int tiempoDepreciacion; // Años
    float costoVehiculo;    // Precio de compra
    float kmPromedioAnio;
    float costoLimpieza;
    int idCombustible;      // Para saber qué combustible usa
} Vehiculo;

// --- VARIABLES GLOBALES (BASE DE DATOS EN MEMORIA) ---
Vehiculo listaVehiculos[100];
int cantidadVehiculos = 0;

Combustible listaCombustibles[10];
int cantidadCombustibles = 0;

// --- PROTOTIPOS DE FUNCIONES ---
void menuPrincipal();
void agregarVehiculo();
void listarVehiculos();
void modificarVehiculo();
void agregarCombustible();
void modificarCombustible();
void listarCombustibles();
void calcularViaje();
void cargarDatosEjemplo(); // Para no empezar vacio

// --- FUNCIÓN PRINCIPAL ---
int main() {
    cargarDatosEjemplo(); // Carga un par de datos para probar rápido
    menuPrincipal();
    return 0;
}

// --- IMPLEMENTACIÓN ---

void menuPrincipal() {
    int opcion;
    do {
        printf("\n=== SISTEMA CALCULO COSTO DE VIAJE ===\n");
        printf("1. Agregar Vehiculo\n");
        printf("2. Lista Vehiculo\n");
        printf("3. Modificar Vehiculo\n");
        printf("4. Agregar Combustible\n");
        printf("5. Modificar Combustible\n");
        printf("6. Lista Combustible\n");
        printf("7. Calcular Viaje\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1: agregarVehiculo(); break;
            case 2: listarVehiculos(); break;
            case 3: modificarVehiculo(); break;
            case 4: agregarCombustible(); break;
            case 5: modificarCombustible(); break;
            case 6: listarCombustibles(); break;
            case 7: calcularViaje(); break;
            case 0: printf("Saliendo...\n"); break;
            default: printf("Opcion no valida.\n");
        }
        system("pause"); // Pausa para leer en Windows
        system("cls");   // Limpiar pantalla en Windows
    } while(opcion != 0);
}

void agregarVehiculo() {
    if (cantidadVehiculos >= 100) {
        printf("Memoria llena.\n");
        return;
    }
    Vehiculo v;
    v.id = cantidadVehiculos + 1; // ID autoincremental

    printf("\n--- AGREGAR VEHICULO ---\n");
    printf("Marca: "); scanf(" %[^\n]", v.marca);
    printf("Modelo: "); scanf(" %[^\n]", v.modelo);
    printf("Ano: "); scanf("%d", &v.anio);
    printf("Placa: "); scanf(" %[^\n]", v.placa);
    printf("Consumo Ciudad (L/100km): "); scanf("%f", &v.consumoCiudad);
    printf("Consumo Carretera (L/100km): "); scanf("%f", &v.consumoCarretera);
    printf("Costo Seguro por Ano: "); scanf("%f", &v.costoSeguroAnio);
    printf("Costo Cambio/Mantenimiento por Km: "); scanf("%f", &v.costoCambioPorKm);
    printf("Tiempo Depreciacion (anios): "); scanf("%d", &v.tiempoDepreciacion);
    printf("Costo del Vehiculo (compra): "); scanf("%f", &v.costoVehiculo);
    printf("Km Promedio por Ano: "); scanf("%f", &v.kmPromedioAnio);
    printf("Costo Limpieza (promedio por viaje): "); scanf("%f", &v.costoLimpieza);

    // Asignar combustible
    listarCombustibles();
    printf("Ingrese el ID del combustible que usa: ");
    scanf("%d", &v.idCombustible);

    listaVehiculos[cantidadVehiculos] = v;
    cantidadVehiculos++;
    printf("Vehiculo agregado con exito (ID: %d).\n", v.id);
}

void listarVehiculos() {
    printf("\n--- LISTA DE VEHICULOS ---\n");
    printf("ID\tMarca\tModelo\tPlaca\n");
    printf("------------------------------------\n");
    for(int i = 0; i < cantidadVehiculos; i++) {
        printf("%d\t%s\t%s\t%s\n", listaVehiculos[i].id, listaVehiculos[i].marca, listaVehiculos[i].modelo, listaVehiculos[i].placa);
    }
}

void modificarVehiculo() {
    int id, encontrado = 0;
    listarVehiculos();
    printf("Ingrese ID del vehiculo a modificar: ");
    scanf("%d", &id);

    for(int i = 0; i < cantidadVehiculos; i++) {
        if(listaVehiculos[i].id == id) {
            printf("Modificando %s %s...\n", listaVehiculos[i].marca, listaVehiculos[i].modelo);
            printf("Nuevo Costo Seguro (Actual: %.2f): ", listaVehiculos[i].costoSeguroAnio);
            scanf("%f", &listaVehiculos[i].costoSeguroAnio);
            printf("Nuevo Km Promedio (Actual: %.2f): ", listaVehiculos[i].kmPromedioAnio);
            scanf("%f", &listaVehiculos[i].kmPromedioAnio);
            // Puedes agregar mas campos si quieres
            printf("Vehiculo actualizado.\n");
            encontrado = 1;
            break;
        }
    }
    if(!encontrado) printf("Vehiculo no encontrado.\n");
}

void agregarCombustible() {
    if (cantidadCombustibles >= 10) return;
    Combustible c;
    c.id = cantidadCombustibles + 1;
    printf("\n--- AGREGAR COMBUSTIBLE ---\n");
    printf("Nombre (ej. Gasolina 95): "); scanf(" %[^\n]", c.nombre);
    printf("Precio por Litro: "); scanf("%f", &c.precioPorLitro);

    listaCombustibles[cantidadCombustibles] = c;
    cantidadCombustibles++;
}

void listarCombustibles() {
    printf("\n--- LISTA DE COMBUSTIBLES ---\n");
    for(int i = 0; i < cantidadCombustibles; i++) {
        printf("%d. %s - Precio: $%.2f\n", listaCombustibles[i].id, listaCombustibles[i].nombre, listaCombustibles[i].precioPorLitro);
    }
}

void modificarCombustible() {
    int id;
    listarCombustibles();
    printf("ID combustible a modificar: ");
    scanf("%d", &id);
    // Logica simple: buscar por ID y cambiar precio
    for(int i=0; i<cantidadCombustibles; i++){
        if(listaCombustibles[i].id == id){
            printf("Nuevo precio para %s: ", listaCombustibles[i].nombre);
            scanf("%f", &listaCombustibles[i].precioPorLitro);
            printf("Actualizado.\n");
            return;
        }
    }
}

void calcularViaje() {
    int idVehiculo;
    float distanciaKM, porcCiudad, porcCarretera;
    Vehiculo v;
    int indiceV = -1;

    listarVehiculos();
    printf("\n--- CALCULAR VIAJE ---\n");
    printf("1. Elegir vehiculo (ID): ");
    scanf("%d", &idVehiculo);

    // Buscar vehiculo
    for(int i=0; i<cantidadVehiculos; i++) {
        if(listaVehiculos[i].id == idVehiculo) {
            v = listaVehiculos[i];
            indiceV = i;
            break;
        }
    }

    if(indiceV == -1) {
        printf("Vehiculo no encontrado.\n");
        return;
    }

    // Buscar precio combustible del vehiculo
    float precioCombustible = 0;
    for(int i=0; i<cantidadCombustibles; i++){
        if(listaCombustibles[i].id == v.idCombustible){
            precioCombustible = listaCombustibles[i].precioPorLitro;
            break;
        }
    }

    printf("2. Cantidad KM del viaje: ");
    scanf("%f", &distanciaKM);
    printf("3. %% KM en Ciudad (0-100): ");
    scanf("%f", &porcCiudad);

    porcCarretera = 100 - porcCiudad;

    // --- CALCULOS ---

    // 1. Consumo Combustible
    float litrosCiudad = (distanciaKM * (porcCiudad/100.0)) * (v.consumoCiudad / 100.0);
    float litrosCarretera = (distanciaKM * (porcCarretera/100.0)) * (v.consumoCarretera / 100.0);
    float costoTotalCombustible = (litrosCiudad + litrosCarretera) * precioCombustible;

    // 2. Depreciacion (Prorrateada por Km)
    // Depreciacion anual = Costo / Años. Depreciacion por KM = Depreciacion Anual / Km Anuales
    float depreciacionPorKm = (v.costoVehiculo / v.tiempoDepreciacion) / v.kmPromedioAnio;
    float costoDepreciacionViaje = depreciacionPorKm * distanciaKM;

    // 3. Seguro (Prorrateado por Km)
    float costoSeguroViaje = (v.costoSeguroAnio / v.kmPromedioAnio) * distanciaKM;

    // 4. Cambio/Mantenimiento
    float costoMantenimientoViaje = v.costoCambioPorKm * distanciaKM;

    // 5. Limpieza
    float costoLimpiezaViaje = v.costoLimpieza;

    // TOTALES
    float costoTotal = costoTotalCombustible + costoDepreciacionViaje + costoSeguroViaje + costoMantenimientoViaje + costoLimpiezaViaje;
    float costoPorKm = costoTotal / distanciaKM;

    // --- REPORTE SALIDA ---
    printf("\n=== RESULTADOS DEL CALCULO ===\n");
    printf("Vehiculo: %s %s\n", v.marca, v.modelo);
    printf("Distancia: %.2f Km\n", distanciaKM);
    printf("------------------------------\n");
    printf("Combustible:      $%.2f\n", costoTotalCombustible);
    printf("Depreciacion:     $%.2f\n", costoDepreciacionViaje);
    printf("Seguro:           $%.2f\n", costoSeguroViaje);
    printf("Mantenimiento:    $%.2f\n", costoMantenimientoViaje);
    printf("Limpieza:         $%.2f\n", costoLimpiezaViaje);
    printf("------------------------------\n");
    printf("1. COSTO TOTAL:   $%.2f\n", costoTotal);
    printf("2. COSTO POR KM:  $%.2f\n", costoPorKm);
    printf("==============================\n");
}

void cargarDatosEjemplo() {
    // Agregamos un combustible
    listaCombustibles[0].id = 1;
    strcpy(listaCombustibles[0].nombre, "Gasolina Premium");
    listaCombustibles[0].precioPorLitro = 150.50; // Ejemplo pesos
    cantidadCombustibles = 1;

    // Agregamos un vehiculo
    Vehiculo v;
    v.id = 1;
    strcpy(v.marca, "Toyota");
    strcpy(v.modelo, "Corolla");
    v.anio = 2020;
    strcpy(v.placa, "A123456");
    v.consumoCiudad = 10.5;
    v.consumoCarretera = 7.2;
    v.costoSeguroAnio = 25000;
    v.costoCambioPorKm = 2.5;
    v.tiempoDepreciacion = 5;
    v.costoVehiculo = 900000;
    v.kmPromedioAnio = 15000;
    v.costoLimpieza = 500;
    v.idCombustible = 1;

    listaVehiculos[0] = v;
    cantidadVehiculos = 1;
}
