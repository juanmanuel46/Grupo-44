#pragma once
#include "Poliza.h"
#include <string.h>
#ifndef ARCHIVOSPOLIZA_H_INCLUDED
#define ARCHIVOSPOLIZA_H_INCLUDED

class ArchivoPoliza {
private:
    char nombre[30];
    int tamanioRegistro;

public:
    ArchivoPoliza(const char *n = "polizas.dat") {
        strcpy(nombre, n);
        tamanioRegistro = sizeof(Poliza);
    }

    int agregarRegistro();
    bool listarRegistros();
    int buscarPoliza(int numeroPoliza);
    Poliza leerRegistro(int pos);
    bool modificarRegistro(Poliza reg, int pos);
    int contarRegistros();
    bool bajaLogica(int numeroPoliza);
    bool modificarDatosPoliza();
    bool listarProximosVencimientos(int diasAnticipacion = 30);
    
    // Métodos para informes
    bool listarPolizasConSiniestros();
    float calcularRecaudacionAnual(int anio);
    float calcularRecaudacionMensual(int mes, int anio);
    float calcularRecaudacionSemanal(int semana, int anio);
    float calcularRecaudacionPersonalizada(Fecha fechaInicio, Fecha fechaFin);
    bool exportarCSV(const char* nombreArchivo = "polizas.csv");
};

#endif // ARCHIVOSPOLIZA_H_INCLUDED 