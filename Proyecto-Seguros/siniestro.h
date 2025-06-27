#ifndef SINIESTRO_H_INCLUDED
#define SINIESTRO_H_INCLUDED
#include <string>

class Siniestro {
private:
    int idSiniestro;
    char desc_siniestro[50];
    float monto_reclamo;
    int id_poliza;
    bool activo;

public:
    Siniestro();

    void cargar();
    void cargarId();
    void cargarDatos();
    void mostrar() const;

    int getIdSiniestro() const;
    const char* getDescSiniestro() const;
    float getMontoReclamo() const;
    int getIDPoliza() const;
    bool getActivo() const;

    void setIdSiniestro(int valor);
    void setDescSiniestro(const char* texto);
    void setMontoReclamo(float monto);
    void setIDPoliza(int id);
    void setActivo(bool estado);
};

#endif

