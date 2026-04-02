#include <stdio.h>
#include "funzioni.h"

int main(void) {
    Producto inv[CAP]; // Array di struct
    int n_productos = 0;
    int op;

    const char *ruta_bd = "datos.csv";

    do {
        // Puliamo lo schermo a ogni iterazione
        clearScreen();

        // Colore: testo bianco (15) su sfondo blu (1) per l'intestazione
        setColor(15, 1);
        printf("\n=== MENU MAQUINA EXPENDEDORA ===\n");
        resetStyle(); // Torniamo al colore normale

        printf("1. Cargar productos (ruta por defecto)\n");
        printf("2. Listar productos\n");
        printf("3. Anadir producto\n");
        printf("4. Modificar producto (precio/stock/nombre)\n");
        printf("5. Guardar productos\n");
        printf("6. Salir\n");

        if (!leer_entero("\nOpcion: ", &op)) return 0;

        switch (op) {
            case 1:
                if (cargar_texto(ruta_bd, inv, CAP, &n_productos)) {
                    setColor(10, 0); // Verde chiaro
                    printf("Datos cargados: %d productos.\n", n_productos);
                } else {
                    setColor(12, 0); // Rosso chiaro
                    printf("Error al leer %s.\n", ruta_bd);
                }
                resetStyle();
                break;
            case 2:
                listar_productos(inv, n_productos);
                break;
            case 3:
                alta_producto(inv, &n_productos);
                break;
            case 4:
                modificar_producto(inv, n_productos);
                break;
            case 5:
                if (guardar_texto(ruta_bd, inv, n_productos)) {
                    setColor(10, 0); // Verde chiaro
                    printf("Datos guardados correctamente en %s.\n", ruta_bd);
                } else {
                    setColor(12, 0); // Rosso chiaro
                    printf("Error al intentar guardar el archivo.\n");
                }
                resetStyle();
                break;
            case 6:
                setColor(14, 0); // Giallo
                printf("Bye\n");
                resetStyle();
                break;
            default:
                setColor(12, 0); // Rosso
                printf("Opcion no valida\n");
                resetStyle();
                break;
        }

        // Pausa prima di pulire lo schermo per far leggere all'utente cosa è successo
        if(op != 6) {
            printf("\nPresiona ENTER para continuar...");
            getchar(); // Aspetta che l'utente prema invio
        }

    } while (op != 6);

    return 0;
}