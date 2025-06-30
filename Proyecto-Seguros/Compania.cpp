#include "Compania.h"
#include <cstring>
#include <iostream>


using namespace std;

Compania::Compania() {
    strcpy(_nombre, "");
    _id = 0;
    _comision = 0.0;
}

const char* Compania::getNombre() {
    return _nombre;
}

int Compania::getId() {
    return _id;
}

float Compania::getComision() {
    return _comision;
}

void Compania::setNombre(const char* nombre) {
    strcpy(_nombre, nombre);
}

void Compania::setId(int id) {
    _id = id;
}

void Compania::setComision(float comision) {
    _comision = comision;
}

void Compania::cargar(int cantReg) {
    _id = cantReg + 1;
    cout << "Ingrese Nombre de la compania" << endl;
    cin.ignore();
    cin.getline(_nombre, 20);
    cout << "Ingrese Comision: " << endl;
    cin >> _comision;
}

void Compania::mostrar() {
    cout << "Id Compania: " << _id << endl;
    cout << "Comision : " << _comision << endl;
}