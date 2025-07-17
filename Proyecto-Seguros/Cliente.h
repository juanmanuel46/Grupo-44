#ifndef CLIENTE_H
#define CLIENTE_H

#include "Fecha.h"

class Cliente {
private:
    int idCliente;
    char nombre[20];
    char apellido[20];
    int dni;
    Fecha fechaNacimiento;
    bool activo;
    char domicilio[30];
    char email[30];
    char telefono[20];

public:
    Cliente();

    // Getters
    int getIdCliente() ;
    const char* getNombre() ;
    const char* getApellido() ;
    int getDni() ;
    Fecha getFechaNacimiento() ;
    bool getActivo() ;
    const char* getDomicilio() ;
    const char* getEmail() ;
    const char* getTelefono() ;

    // Setters
    void setIdCliente(int valor);
    void setNombre(const char* valor);
    void setApellido(const char* valor);
    void setDni(int valor);
    void setFechaNacimiento(const Fecha& valor);
    void setActivo(bool valor);
    void setDomicilio(const char* valor);
    void setEmail(const char* valor);
    void setTelefono(const char* valor);

    // Funciones
    void mostrar() ;
    void cargar();
    void cargarId();
    void cargarDatos();
    void cargarDatosSinDni(); // Nueva función para cargar datos sin pedir DNI
    void buscarCliente(int getDni);
};

#endif
