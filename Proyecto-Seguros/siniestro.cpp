#include "siniestro.h"
#include <iostream>
#include <cstring>
#include <limits>

using namespace std;

Siniestro::Siniestro() {
    idSiniestro = 0;
    strcpy(desc_siniestro, "");
    monto_reclamo = 0.0f;
    id_poliza = 0;
    activo = true;
}

int Siniestro::getIdSiniestro()  {
    return idSiniestro;
}

const char* Siniestro::getDescSiniestro()  {
    return desc_siniestro;
}

float Siniestro::getMontoReclamo()  {
    return monto_reclamo;
}

int Siniestro::getIDPoliza()  {
    return id_poliza;
}

bool Siniestro::getActivo()  {
    return activo;
}

void Siniestro::setIdSiniestro(int valor) {
    idSiniestro = valor;
}

void Siniestro::setDescSiniestro(const char* texto) {
    strncpy(desc_siniestro, texto, sizeof(desc_siniestro) - 1);
    desc_siniestro[sizeof(desc_siniestro) - 1] = '\0';
}

void Siniestro::setMontoReclamo(float monto) {
    monto_reclamo = monto;
}

void Siniestro::setIDPoliza(int id) {
    id_poliza = id;
}

void Siniestro::setActivo(bool estado) {
    activo = estado;
}

void Siniestro::mostrar()  {
    cout << "ID Siniestro: " << idSiniestro << endl;
    cout << "Descripcion: " << desc_siniestro << endl;
    cout << "Monto a Reclamar: " << monto_reclamo << endl;
    cout << "ID Poliza: " << id_poliza << endl;
    cout << "-------------------------\n";
}

void Siniestro::cargarId() {
    cout << "Ingrese ID del Siniestro: ";
    cin >> idSiniestro;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Siniestro::cargarDatos() {
    cout << "Ingrese descripcion del siniestro: ";
    cin.getline(desc_siniestro, 50);

    cout << "Ingrese monto a reclamar: ";
    cin >> monto_reclamo;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    cout << "Ingrese ID de la poliza: ";
    cin >> id_poliza;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    activo = true;
}

void Siniestro::cargar() {
    cargarId();
    cargarDatos();
}




