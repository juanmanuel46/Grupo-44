#pragma once
#include "Cliente.h"
#include <string.h>

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