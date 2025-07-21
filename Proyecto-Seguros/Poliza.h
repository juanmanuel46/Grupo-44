

#ifndef POLIZA_H_INCLUDED
#define POLIZA_H_INCLUDED

#include <cstring>
#include "Fecha.h"

class Poliza{

private:
    int _numeroPoliza;
    int _dni;
    char _patente[10];
    char _compania[30];
    Fecha _fechaInicio;
    Fecha _fechaVencimiento;
    char _detalleCobertura[50];
    float _importeMensual;
    bool _activo;


public:

    Poliza();
    // Getters (const para seguridad)
    int getNumeroPoliza() ;
    int getDni() ;
    const char* getPatente() ;
    const char* getCompania() ;
    const Fecha& getFechaInicio() ;
    const Fecha& getFechaVencimiento() ;
    const char* getDetalleCobertura() ;
    float getImporteMensual() ;
    bool isActivo() ;



    // Setters
    void setNumeroPoliza(int numeroPoliza);
    void setDni(int dni);
    void setPatente(const char* patente);
    void setCompania(const char* compania);
    void setFechaInicio(const Fecha& fecha);
    void setFechaVencimiento(const Fecha& fecha);
    void setDetalleCobertura(const char* detalle);
    void setImporteMensual(float importe);
    void setActivo(bool estado);



    void cargar();
    void cargarId();
    void cargarDNI();
    void cargarPatente();
    void cargarCompania();
    void cargarDatos();
    void mostrar() ;

};










#endif // POLIZA_H_INCLUDED

