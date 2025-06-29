#ifndef ARCHIVOSVEHICULOS_H_INCLUDED
#define ARCHIVOSVEHICULOS_H_INCLUDED

#include "Vehiculo.h" 
#include <string.h>

class ArchivoVehiculo {
private:
    char nombre[30];
    int tamanioRegistro;

public:
    ArchivoVehiculo(const char *n = "vehiculos.dat") {
        strcpy(nombre, n);
        tamanioRegistro = sizeof(Vehiculo);
    }

    int agregarRegistro();
    bool listarRegistros();
    int buscarVehiculo(int idVehiculo);
    Vehiculo leerRegistro(int pos);
    bool modificarRegistro(Vehiculo reg, int pos);
    int contarRegistros();
    bool bajaLogica();
    bool modificarDatosVehiculo();
};

#endif // ARCHIVOSVEHICULOS_H_INCLUDED