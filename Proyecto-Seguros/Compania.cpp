#include "Compania.h"
#include <cstring>
#include <iostream>
#include <limits>

using namespace std;

Compania::Compania() {
    strcpy(_nombre, "");
    _id = 0;
    _comision = 0.0;
    _activo = true;
}

// Getters

const char* Compania::getNombre() const {
    return _nombre;
}

int Compania::getId() const {
    return _id;
}

float Compania::getComision() const {
    return _comision;
}

bool Compania::getActivo() const {
    return _activo;
}

// Setters

void Compania::setNombre(const char* nombre) {
    strncpy(_nombre, nombre, sizeof(_nombre) - 1);
    _nombre[sizeof(_nombre) - 1] = '\0';
}

void Compania::setId(int id) {
    _id = id;
}

void Compania::setComision(float comision) {
    _comision = comision;
}

void Compania::setActivo(bool valor) {
    _activo = valor;
}

// Métodos funcionales

void Compania::mostrar() const {
    cout << "ID Compania: " << _id << endl;
    cout << "Nombre: " << _nombre << endl;
    cout << "Comision: " << _comision << endl;
    cout << "-------------------------\n";
}

void Compania::cargarId() {
    cout << "Ingrese ID de la compania: ";
    cin >> _id;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Compania::cargarDatos() {
    cout << "Ingrese Nombre de la compania: ";
    cin.getline(_nombre, sizeof(_nombre));

    cout << "Ingrese Comision: ";
    cin >> _comision;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    _activo = true;
}

void Compania::cargar() {
    cargarId();
    cargarDatos();
}