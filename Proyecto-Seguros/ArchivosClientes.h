#pragma once
#include "Cliente.h"
#include <string.h>
#ifndef ARCHIVOSCLIENTES_H_INCLUDED
#define ARCHIVOSCLIENTES_H_INCLUDED

class ArchivoCliente {
private:
    char nombre[30];
    int tamanioRegistro;

public:
    ArchivoCliente(const char *n = "clientes.dat") {
        strcpy(nombre, n);
        tamanioRegistro = sizeof(Cliente);
    }

    int agregarRegistro();
    bool listarRegistros();
    int buscarCliente(int idCliente);
    Cliente leerRegistro(int pos);
    bool modificarRegistro(Cliente reg, int pos);
    int contarRegistros();
    bool bajaLogica(int idCliente);
    bool modificarDatosCliente();
};

#endif // ARCHIVOSCLIENTES_H_INCLUDED
