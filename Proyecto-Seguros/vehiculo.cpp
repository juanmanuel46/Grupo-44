#include "Vehiculo.h"
#include <iostream>
#include <fstream>   // Para fstream (archivos)
#include <cstring>   // Para strcpy, memset
#include <limits>    // Para numeric_limits (en cin.ignore)

using namespace std;

Vehiculo::Vehiculo() {
    idVehiculo = 0;
    memset(marca, 0, sizeof(marca));
    memset(version, 0, sizeof(version));
    anio = 0;
    activo = true;
    memset(patente, 0, sizeof(patente));
}

void Vehiculo::cargar() {
    cout << "ID de Vehiculo: ";
    cin >> idVehiculo;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Marca: ";
    cin.getline(marca, sizeof(marca));

    cout << "Version: ";
    cin.getline(version, sizeof(version));

    cout << "Anio: ";
    cin >> anio;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Patente: ";
    cin.getline(patente, sizeof(patente));
}

void Vehiculo::mostrar() {
    cout << "ID: " << idVehiculo << endl;
    cout << "Marca: " << marca << endl;
    cout << "Version: " << version << endl;
    cout << "Anio: " << anio << endl;
    cout << "Patente: " << patente << endl;
    cout << "Estado (Activo): " << (activo ? "Si" : "No") << endl;
    cout << "--------------------------------\n";
}

int Vehiculo::getIdVehiculo() {
    return idVehiculo;
}

const char* Vehiculo::getMarca() {
    return marca;
}

const char* Vehiculo::getVersion() {
    return version;
}

int Vehiculo::getAnio() {
    return anio;
}

bool Vehiculo::getActivo() {
    return activo;
}

const char* Vehiculo::getPatente() {
    return patente;
}

void Vehiculo::setIdVehiculo(int valor) {
    idVehiculo = valor;
}

void Vehiculo::setMarca(const char* valor) {
    strncpy(marca, valor, sizeof(marca) - 1);
    marca[sizeof(marca) - 1] = '\0';
}

void Vehiculo::setVersion(const char* valor) {
    strncpy(version, valor, sizeof(version) - 1);
    version[sizeof(version) - 1] = '\0';
}

void Vehiculo::setAnio(int valor) {
    anio = valor;
}

void Vehiculo::setActivo(bool valor) {
    activo = valor;
}

void Vehiculo::setPatente(const char* valor) {
    strncpy(patente, valor, sizeof(patente) - 1);
    patente[sizeof(patente) - 1] = '\0';
}

bool Vehiculo::guardarEnDisco() {
    ofstream archi("vehiculos.dat", ios::app | ios::binary);
    if (!archi) return false;
    archi.write(reinterpret_cast<char*>(this), sizeof(*this));
    archi.close();
    return true;
}

bool Vehiculo::leerDeDisco(int pos) {
    ifstream archi("vehiculos.dat", ios::binary);
    if (!archi) return false;
    archi.seekg(pos * sizeof(*this));
    archi.read(reinterpret_cast<char*>(this), sizeof(*this));
    bool exito = archi.good();
    archi.close();
    return exito;
}
