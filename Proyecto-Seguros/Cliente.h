#ifndef CLIENTE_H
#define CLIENTE_H

class Cliente {
private:
    int idCliente;
    char nombre[20];
    char apellido[20];
    int dni;
    int fechaNacimiento;
    bool activo;
    char domicilio[30];
    char email[30];
    char telefono[20];

public:
    Cliente();

    // Getters
    int getIdCliente() const;
    const char* getNombre() const;
    const char* getApellido() const;
    int getDni() const;
    int getFechaNacimiento() const;
    bool getActivo() const;
    const char* getDomicilio() const;
    const char* getEmail() const;
    const char* getTelefono() const;

    // Setters
    void setIdCliente(int valor);
    void setNombre(const char* valor);
    void setApellido(const char* valor);
    void setDni(int valor);
    void setFechaNacimiento(int valor);
    void setActivo(bool valor);
    void setDomicilio(const char* valor);
    void setEmail(const char* valor);
    void setTelefono(const char* valor);

    // Funciones
    void mostrar() const;
    void cargar();
    void cargarId();
    void cargarDatos();
};

#endif



