#include "Vehiculo.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <limits>

using namespace std;

Vehiculo::Vehiculo() {
    idVehiculo = 0;
    strcpy(marca, "");
    strcpy(version, "");
    anio = 0;
    activo = true;
    strcpy(patente, "");
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

void Vehiculo::cargarId() {
    cout << "Ingrese ID del vehiculo: ";
    cin >> idVehiculo;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void Vehiculo::cargarDatos() {
    cout << "Ingrese marca: ";
    cin.getline(marca, 30);

    cout << "Ingrese version: ";
    cin.getline(version, 30);

    cout << "Ingrese anio: ";
    cin >> anio;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Patente: ";
    cin.getline(patente, sizeof(patente));

    activo = true;
}

void Vehiculo::cargarDatosSinPatente() {
    cout << "Ingrese marca: ";
    cin.getline(marca, 30);
    cout << "Ingrese version: ";
    cin.getline(version, 30);
    cout << "Ingrese anio: ";
    cin >> anio;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    activo = true;
}

void Vehiculo::cargar() {
    cargarId();
    cargarDatos();
}

void Vehiculo::mostrar() {
    cout << "ID del vehiculo: " << idVehiculo << endl;
    cout << "Marca: " << marca << endl;
    cout << "Version: " << version << endl;
    cout << "Anio: " << anio << endl;
    cout << "Patente: " << patente << endl;
    cout << "--------------------------------\n";
}
