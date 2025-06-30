#include "ArchivoCompania.h"
#include "Compania.h"
#include <cstring>
#include <cstdio> // Se incluye cstdio para las funciones de archivo estilo C
#include <iostream>

using namespace std;

ArchivoCompania::ArchivoCompania(const char *n) {
    strcpy(_nombre, n);
}

bool ArchivoCompania::GrabarRegistro(Compania reg) {
    FILE *p;
    p = fopen(_nombre, "ab"); // "ab" para agregar en modo binario
    if (p == NULL) {
        return false;
    }
    bool escribio = fwrite(&reg, sizeof(Compania), 1, p);
    fclose(p);
    return escribio;
}

int ArchivoCompania::BuscarRegistro(int id) {
    FILE *p;
    Compania reg;
    int pos = 0;
    p = fopen(_nombre, "rb");
    if (p == NULL) {
        cout << "NO SE PUDO ABRIR EL ARCHIVO " << endl;
        return -2; // Error al abrir el archivo
    }
    while (fread(&reg, sizeof(Compania), 1, p) == 1) {
        if (reg.getId() == id) {
            fclose(p);
            return pos; // Retorna la posición si lo encuentra
        }
        pos++;
    }
    fclose(p);
    return -1; // Retorna -1 si no se encuentra el registro
}

Compania ArchivoCompania::LeerRegistro(int pos) {
    FILE *p;
    Compania reg;
    p = fopen(_nombre, "rb");
    if (p == NULL) {
        cout << "NO SE PUDO ABRIR EL ARCHIVO " << endl;
        // Devuelve un objeto vacío o con valores por defecto en caso de error
        return reg;
    }

    fseek(p, pos * sizeof(Compania), SEEK_SET);
    fread(&reg, sizeof(Compania), 1, p);
    fclose(p);
    return reg;
}

int ArchivoCompania::CantidadRegistros() {
    FILE *p;
    p = fopen(_nombre, "rb");
    if (p == NULL) {
        return 0; // Si el archivo no existe o no se puede abrir, no hay registros
    }

    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Compania);
    fclose(p);
    return cant;
}