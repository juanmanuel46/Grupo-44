#ifndef ARCHIVOSSINIESTRO_H_INCLUDED
#define ARCHIVOSSINIESTRO_H_INCLUDED

#include "siniestro.h" 
#include <string.h>

class ArchivoSiniestro {
private:
    char nombre[30];
    int tamanioRegistro;

public:
    ArchivoSiniestro(const char *n = "siniestros.dat") {
        strcpy(nombre, n);
        tamanioRegistro = sizeof(Siniestro);
    }

    int agregarRegistro();
    bool listarRegistros();
    int buscarSiniestro(int idSiniestro);
    Siniestro leerRegistro(int pos);
    bool modificarRegistro(Siniestro reg, int pos);
    int contarRegistros();
    bool bajaLogica();
    bool modificarDatosSiniestro();
    bool exportarCSV(const char* nombreArchivo = "siniestros.csv");
};


#endif // ARCHIVOSSINIESTRO_H_INCLUDED