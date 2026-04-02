#include "funzioni.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>

// --- FUNZIONI DI LETTURA SICURA ---

/*
 * [ES]
 * Funcion: leer_entero
 * Descripcion: Solicita y lee un numero entero por teclado de forma segura. Evita cuelgues (crashes) o bucles infinitos si el usuario introduce letras o caracteres invalidos.
 * Parametros:
 * - prompt: Cadena de texto (mensaje) que se muestra al usuario.
 * - out: Puntero a la variable entera (int) donde se guardara el valor.
 * Retorno: Devuelve 1 si la lectura fue exitosa, o 0 si hubo un error.
 *
 * [IT]
 * Funzione: leer_entero
 * Descrizione: Richiede e legge un numero intero da tastiera in modo sicuro. Evita blocchi (crash) o cicli infiniti se l'utente inserisce lettere o caratteri non validi.
 * Parametri:
 * - prompt: Stringa di testo (messaggio) mostrata all'utente.
 * - out: Puntatore alla variabile intera (int) in cui verrà salvato il valore.
 * Ritorno: Restituisce 1 se la lettura ha avuto successo, o 0 in caso di errore.
 */

int leer_entero(const char *prompt, int *out) {
    char buf[128];
    for (;;) {
        printf("%s", prompt);
        if (!fgets(buf, sizeof(buf), stdin)) return 0; // EOF
        errno = 0; // variabile global de error en strol
        char *end = NULL;
        long v = strtol(buf, &end, 10);
        while (end && isspace((unsigned char)*end)) end++; // Saltar espacios finales
        if (errno == 0 && end && *end == '\0') {
            *out = (int)v;
            return 1;
        }
        printf("Valor invalido. Intenta de nuevo.\n");
    }
}

/*
 * [ES]
 * Funcion: leer_float
 * Descripcion: Solicita y lee un numero decimal (float) por teclado de forma segura.
 * Parametros:
 * - prompt: Mensaje que se muestra al usuario.
 * - out: Puntero a la variable float.
 * Retorno: Devuelve 1 si la lectura fue exitosa, o 0 si hubo un error.
 *
 * [IT]
 * Funzione: leer_float
 * Descrizione: Richiede e legge un numero decimale (float) da tastiera in modo sicuro.
 * Parametri:
 * - prompt: Messaggio mostrato all'utente.
 * - out: Puntatore alla variabile float.
 * Ritorno: Restituisce 1 se la lettura ha avuto successo, o 0 in caso di errore.
 */


int leer_float(const char *prompt, float *out) {
    char buf[128];
    for (;;) {
        printf("%s", prompt);
        if (!fgets(buf, sizeof(buf), stdin)) return 0;
        errno = 0; // variable global de error en strof
        char *end = NULL;
        float v = strtof(buf, &end);
        while (end && isspace((unsigned char)*end)) end++;
        if (errno == 0 && end && *end == '\0') {
            *out = v;
            return 1;
        }
        printf("Valor invalido. Intenta de nuevo.\n");
    }
}

/*
 * [ES]
 * Funcion: leer_cadena
 * Descripcion: Lee una cadena de texto (string) con espacios de forma segura, evitando desbordamientos de buffer (buffer overflow) y limpiando el salto de linea final.
 * Parametros:
 * - prompt: Mensaje al usuario.
 * - dst: Puntero al array de caracteres.
 * - cap: Capacidad maxima del array.
 * Retorno: Devuelve 1 si se leyo correctamente, o 0 en caso de error.
 *
 * [IT]
 * Funzione: leer_cadena
 * Descrizione: Legge una stringa di testo con spazi in modo sicuro, evitando buffer overflow e rimuovendo l'a capo finale.
 * Parametri:
 * - prompt: Messaggio per l'utente.
 * - dst: Puntatore all'array di caratteri.
 * - cap: Capacità massima dell'array.
 * Ritorno: Restituisce 1 se letta correttamente, o 0 in caso di errore.
 */


int leer_cadena(const char *prompt, char *dst, size_t cap) {
    printf("%s", prompt);
    if (!fgets(dst, cap, stdin)) return 0; // [cite: 160]
    size_t n = strlen(dst);
    if (n > 0 && dst[n - 1] == '\n') // quitar \n si existe
        dst[n - 1] = '\0';
    return 1;
}

// --- FUNZIONI DEL DOMINIO (PRODOTTI) ---


/*
 * [ES]
 * Funcion: imprimir_producto
 * Descripcion: Muestra por pantalla los datos formateados de un unico producto.
 * Parametros:
 * - p: Estructura Producto con los datos.
 * Retorno: Nada (void).
 *
 * [IT]
 * Funzione: imprimir_producto
 * Descrizione: Mostra a schermo i dati formattati di un singolo prodotto.
 * Parametri:
 * - p: Struttura Producto con i dati.
 * Ritorno: Nessuno (void).
 */

//NON LA STO UTILIZZANDO NEL CODICE, MA MAGARI TORNA UTILE

void imprimir_producto(const Producto p) {
    printf("ID:%d | %-20s | %.2f EUR | stock:%d\n", p.id, p.nombre, p.precio, p.stock);
}

/*
 * [ES]
 * Funcion: listar_productos
 * Descripcion: Muestra el inventario en formato de tabla colorida. Usa azul para el encabezado
 * y cambia el color de las filas segun el stock (rojo si es bajo, verde si es normal).
 * Parametros:
 * - arr: Puntero al array de productos.
 * - n: Cantidad actual de productos.
 * Retorno: Nada (void).
 *
 * [IT]
 * Funzione: listar_productos
 * Descrizione: Mostra l'inventario in formato tabella colorata. Usa il blu per l'intestazione
 * e cambia il colore delle righe in base allo stock (rosso se basso, verde se normale).
 * Parametri:
 * - arr: Puntatore all'array dei prodotti.
 * - n: Quantità attuale di prodotti.
 * Ritorno: Nessuno (void).
 */
void listar_productos(const Producto *arr, int n) {
    if (n == 0) {
        setColor(12, 0); // Rosso su nero
        printf("\n EL INVENTARIO ESTA VACIO \n");
        resetStyle();
        return;
    }

    // 1. Stampiamo l'intestazione con sfondo Blu (1) e testo Bianco (15)
    printf("\n");
    setColor(15, 1);
    // Usiamo %-Ns per incolonnare bene il testo (N = numero di spazi)
    printf(" %-5s | %-20s | %-10s | %-8s ", "ID", "NOMBRE", "PRECIO", "STOCK");
    resetStyle();
    printf("\n");

    // 2. Stampiamo i prodotti
    for (int i = 0; i < n; i++) {
        // Se lo stock è basso (es. meno di 5), coloriamo la riga di Giallo (14)
        // Altrimenti usiamo il Verde (10)
        if (arr[i].stock < 5) {
            setColor(14, 0);
        } else {
            setColor(10, 0);
        }

        printf(" %-5d | %-20s | %-10.2f | %-8d \n",
               arr[i].id,
               arr[i].nombre,
               arr[i].precio,
               arr[i].stock);
    }

    resetStyle(); // Fondamentale per non lasciare tutto verde!
    printf("----------------------------------------------------------\n");
}
/*
 * [ES]
 * Funcion: buscar_indice_por_id
 * Descripcion: Busca un producto especifico comparando su ID.
 * Parametros:
 * - arr: Array de productos.
 * - n: Numero de productos.
 * - id_buscado: ID a encontrar.
 * Retorno: Indice del producto si se encuentra, o -1 si no existe.
 *
 * [IT]
 * Funzione: buscar_indice_por_id
 * Descrizione: Cerca un prodotto specifico confrontando il suo ID.
 * Parametri:
 * - arr: Array dei prodotti.
 * - n: Numero di prodotti.
 * - id_buscado: ID da trovare.
 * Ritorno: Indice del prodotto se trovato, o -1 se non esiste.
 */


int buscar_indice_por_id(const Producto *arr, int n, int id_buscado) {
    for (int i = 0; i < n; i++) {
        if (arr[i].id == id_buscado) return i; // Trovato! Ritorna la posizione
    }
    return -1; // Non trovato
}

/*
 * [ES]
 * Funcion: alta_producto
 * Descripcion: Pide datos para un nuevo producto y lo añade al inventario.
 * Parametros:
 * - arr: Array de productos.
 * - n: Puntero al contador de productos.
 * Retorno: Nada (void).
 *
 * [IT]
 * Funzione: alta_producto
 * Descrizione: Chiede i dati per un nuovo prodotto e lo aggiunge all'inventario.
 * Parametri:
 * - arr: Array dei prodotti.
 * - n: Puntatore al contatore dei prodotti.
 * Ritorno: Nessuno (void).
 */


void alta_producto(Producto *arr, int *n) {
    if (*n >= CAP) {  // Controlla se c'è spazio
        printf("Error: Inventario lleno.\n");
        return;
    }
    Producto p = {0}; // Inicialización parcial para limpiar
    printf("\n--- NUEVO PRODUCTO ---\n");
    leer_entero("ID: ", &p.id);
    leer_cadena("Nombre: ", p.nombre, sizeof(p.nombre));
    leer_float("Precio: ", &p.precio);
    leer_entero("Stock: ", &p.stock);

    arr[*n] = p; // Copia campo a campo
    (*n)++;
    printf("Producto anadido correctamente.\n");
}

/*
 * [ES]
 * Funcion: modificar_producto
 * Descripcion: Pide un ID, busca el producto y permite modificar su nombre, precio y stock.
 * Parametros:
 * - arr: Array de productos.
 * - n: Numero actual de productos.
 * Retorno: Nada (void).
 *
 * [IT]
 * Funzione: modificar_producto
 * Descrizione: Chiede un ID, cerca il prodotto e ne permette la modifica (nome, prezzo, stock).
 * Parametri:
 * - arr: Array dei prodotti.
 * - n: Numero attuale di prodotti.
 * Ritorno: Nessuno (void).
 */


void modificar_producto(Producto *arr, int n) {
    int id;
    if (!leer_entero("\nID del producto a modificar: ", &id)) return;

    int idx = buscar_indice_por_id(arr, n, id);
    if (idx == -1) {
        printf("Producto no encontrado.\n");
        return;
    }

    Producto *p = &arr[idx]; // Puntero a un elemento del array
    printf("Modificando: %s\n", p->nombre);
    leer_cadena("Nuevo nombre: ", p->nombre, sizeof(p->nombre));
    leer_float("Nuevo precio: ", &p->precio); // Uso del operador ->
    leer_entero("Nuevo stock: ", &p->stock);
    printf("Producto modificado correctamente.\n");
}


/*
 * [ES]
 * Funcion: guardar_texto
 * Descripcion: Guarda todo el inventario en un archivo de texto en formato CSV (separador ';').
 * Parametros:
 * - ruta: Nombre del archivo (ej. "datos.csv").
 * - arr: Array de productos a guardar.
 * - n: Numero actual de productos.
 * Retorno: 1 si se guardo correctamente, 0 en caso de error.
 *
 * [IT]
 * Funzione: guardar_texto
 * Descrizione: Salva l'intero inventario in un file di testo in formato CSV (separatore ';').
 * Parametri:
 * - ruta: Nome del file (es. "datos.csv").
 * - arr: Array dei prodotti da salvare.
 * - n: Numero attuale di prodotti.
 * Ritorno: 1 se salvato correttamente, 0 in caso di errore.
 */


int guardar_texto(const char *ruta, const Producto *arr, int n) {
    FILE *f = fopen(ruta, "w");
    if (!f) return 0;
    for (int i = 0; i < n; i++) {
        fprintf(f, "%d;%s;%.2f;%d\n", arr[i].id, arr[i].nombre, arr[i].precio, arr[i].stock);
    }
    fclose(f);
    return 1;
}

/*
 * [ES]
 * Funcion: cargar_texto
 * Descripcion: Lee los productos desde un archivo CSV y los carga en el programa.
 * Parametros:
 * - ruta: Nombre del archivo.
 * - arr: Array donde guardar los productos.
 * - cap: Capacidad maxima del array.
 * - out_n: Puntero a la variable de cantidad leida.
 * Retorno: 1 si se leyo correctamente, 0 en caso de error.
 *
 * [IT]
 * Funzione: cargar_texto
 * Descrizione: Legge i prodotti da un file CSV e li carica nel programma.
 * Parametri:
 * - ruta: Nome del file.
 * - arr: Array in cui salvare i prodotti.
 * - cap: Capacità massima dell'array.
 * - out_n: Puntatore alla quantità letta.
 * Ritorno: 1 se letto correttamente, 0 in caso di errore.
 */


int cargar_texto(const char *ruta, Producto *arr, int cap, int *out_n) {
    FILE *f = fopen(ruta, "r");
    if (!f) return 0;
    char linea[256];
    int n = 0;
    while (n < cap && fgets(linea, sizeof(linea), f)) {
        size_t L = strlen(linea);
        if (L > 0 && linea[L-1] == '\n') linea[L-1] = '\0';

        Producto p = {0};
        // Usa il ; come separatore
        if (sscanf(linea, "%d; %31[^;];%f;%d", &p.id, p.nombre, &p.precio, &p.stock) == 4) {
            arr[n++] = p;
        }
    }
    fclose(f);
    *out_n = n;
    return 1;
}

// --- FUNCIONES DE INTERFAZ (ANSI) ---

/*
 * [ES]
 * Funciones de Interfaz (ANSI)
 * Descripcion: Funciones que envian codigos ANSI al terminal para limpiar la pantalla (clearScreen) y cambiar colores (setColor).
 * Parametros (setColor):
 * - fg: Color del texto.
 * - bg: Color de fondo.
 *
 * [IT]
 * Funzioni di Interfaccia (ANSI)
 * Descrizione: Funzioni che inviano codici ANSI al terminale per pulire lo schermo (clearScreen) e cambiare i colori (setColor).
 * Parametri (setColor):
 * - fg: Colore del testo.
 * - bg: Colore di sfondo.
 */

int ansiFg(int c) {
    return (c < 8) ? 30 + c : 90 + (c - 8);
}

int ansiBg(int c) {
    return (c < 8) ? 40 + c : 100 + (c - 8);
}

void setColor(int fg, int bg) {   //setColor(texto, fondo)
    printf("\x1b[%d;%dm", ansiFg(fg), ansiBg(bg));
}

void clearScreen(void) {
    printf("\x1b[2J\x1b[H");
}

void resetStyle(void) {
    printf("\x1b[0m");
}

void hideCursor(void) {
    printf("\x1b[?25l");
}

void showCursor(void) {
    printf("\x1b[?25h");
}

void gotoxy(int x, int y) {
    printf("\x1b[%d;%dH", y, x);
}