#ifndef ARCHIVOSCOMPANIA_H_INCLUDED
#define ARCHIVOSCOMPANIA_H_INCLUDED


#pragma once
#include "Compania.h"
#include <string.h>

class ArchivoCompania {
private:
    char nombre[30];
    int tamanioRegistro;

public:
    ArchivoCompania(const char *n = "companias.dat") {
        strcpy(nombre, n);
        tamanioRegistro = sizeof(Compania);
    }

    int agregarRegistro();
    bool listarRegistros();
    int buscarCompania(int idCompania);
    Compania leerRegistro(int pos);
    bool modificarRegistro(Compania reg, int pos);
    int contarRegistros();
    bool bajaLogica(int idCompania);
    bool modificarDatosCompania();
};

#endif // ARCHIVOSCOMPANIA_H_INCLUDED

