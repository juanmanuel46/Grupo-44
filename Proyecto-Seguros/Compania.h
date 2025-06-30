#ifndef COMPANIA_H_INCLUDED
#define COMPANIA_H_INCLUDED

class Compania {
private:
    char _nombre[20];
    int _id;
    float _comision;

public:
    Compania();
    const char* getNombre();
    int getId();
    float getComision();

    void setNombre(const char* nombre);
    void setId(int id);
    void setComision(float comision);

    void cargar(int cantReg);
    void mostrar();
};

#endif // COMPANIA_H_INCLUDED