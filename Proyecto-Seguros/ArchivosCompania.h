#ifndef ARCHIVOCOMPANIA_H_INCLUDED
#define ARCHIVOCOMPANIA_H_INCLUDED

#include "Compania.h"

class ArchivoCompania {
private:
    char _nombre[30];

public:
    // Constructor que recibe el nombre del archivo
    ArchivoCompania(const char *n = "companias.dat");

    // Métodos para interactuar con el archivo
    bool GrabarRegistro(Compania reg);
    Compania LeerRegistro(int pos);
    int BuscarRegistro(int id);
    int CantidadRegistros();
};

#endif // ARCHIVOCOMPANIA_H_INCLUDED