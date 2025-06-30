

#ifndef POLIZA_H_INCLUDED
#define POLIZA_H_INCLUDED

#include <cstring>
#include "Fecha.h"

class Poliza{

private:
    int _numeroPoliza;
    int _dni;
    char _patente[10];
    Fecha _fechaInicio;
    Fecha _fechaVencimiento;
    char _nombre[10];
    char _apellido[10];
    char _detalleCobertura[50];
    float _importeMensual;
    bool _activo;


public:

    Poliza();
    // Getters (const para seguridad)
    int getNumeroPoliza() const;
    int getDni() const;
    const char* getPatente() const;
    const Fecha& getFechaInicio() const;
    const Fecha& getFechaVencimiento() const;
    const char* getNombre() const;
    const char* getApellido() const;
    const char* getDetalleCobertura() const;
    float getImporteMensual() const;
    bool isActivo() const;

    // Setters
    void setNumeroPoliza(int numeroPoliza);
    void setDni(int dni);
    void setPatente(const char* patente);
    void setFechaInicio(const Fecha& fecha);
    void setFechaVencimiento(const Fecha& fecha);
    void setNombre(const char* nombre);
    void setApellido(const char* apellido);
    void setDetalleCobertura(const char* detalle);
    void setImporteMensual(float importe);
    void setActivo(bool estado);



    void cargar();
    void cargarId();
    void cargarDatos();
    void mostrar() const;

};










#endif // POLIZA_H_INCLUDED

