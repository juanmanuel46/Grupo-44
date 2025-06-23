#ifndef CLIENTE_H
#define CLIENTE_H

class Cliente {
private:
    int id;
    char nombre[30];
    char apellido[30];
    char dni[15];
    char telefono[20];
    bool estado;

public:
    Cliente();
    void cargar();
    void mostrar();
    int getId();
    void setId(int);
    bool getEstado();
    void setEstado(bool);

    bool guardarEnDisco();
    bool leerDeDisco(int pos);
    bool modificarEnDisco(int pos);
};

#endif


