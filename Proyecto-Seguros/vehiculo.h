#ifndef VEHICULO_H_INCLUDED
#define VEHICULO_H_INCLUDED
#include <cstring>

class Vehiculo {
private:
    int idVehiculo;
    char marca[50];
    char version[50];
    int anio;
    bool activo;
    char patente[10];

public:
    Vehiculo();

    void cargar();
    void cargarId();
    void cargarDatos();
    void mostrar();

    int getIdVehiculo();
    const char* getMarca();
    const char* getVersion();
    int getAnio();
    bool getActivo();
    const char* getPatente();

    void setIdVehiculo(int valor);
    void setMarca(const char* valor);
    void setVersion(const char* valor);
    void setAnio(int valor);
    void setActivo(bool valor);
    void setPatente(const char* valor);
};
#endif
