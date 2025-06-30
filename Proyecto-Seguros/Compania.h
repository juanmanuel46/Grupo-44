#ifndef COMPANIA_H_INCLUDED
#define COMPANIA_H_INCLUDED

class Compania {
private:
    char _nombre[20];
    int _id;
    float _comision;
    bool _activo;

public:
    Compania();
    // Getters

    // Setters
    void setNombre(const char* nombre);
    void setId(int id);
    void setComision(float comision);
    void setActivo(bool valor);

    // Funciones
    void cargar();
    void cargarId();
    void cargarDatos();
};

