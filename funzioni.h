#ifndef FUNZIONI_H
#define FUNZIONI_H

#include <stdio.h>
#include <stddef.h>

#define CAP 100

typedef struct {
    int id;
    char nombre[32];
    float precio;
    int stock;
} Producto;

// --- Funciones de lectura segura ---
int leer_entero(const char *prompt, int *out);
int leer_float(const char *prompt, float *out);
int leer_cadena(const char *prompt, char *dst, size_t cap);

// --- Funciones del dominio ---
void imprimir_producto(const Producto p);
void listar_productos(const Producto *arr, int n);
int buscar_indice_por_id(const Producto *arr, int n, int id_buscado);
void alta_producto(Producto *arr, int *n);
void modificar_producto(Producto *arr, int n);

// --- Funciones de Ficheros ---
int cargar_texto(const char *ruta, Producto *arr, int cap, int *out_n);
int guardar_texto(const char *ruta, const Producto *arr, int n);

// --- Funciones de Interfaz (ANSI) ---
void clearScreen(void);
void resetStyle(void);
void setColor(int fg, int bg);
void hideCursor(void);
void showCursor(void);
void gotoxy(int x, int y);

#endif // FUNZIONI_H