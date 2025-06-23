#include "Cliente.h"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

Cliente::Cliente() {
    id = 0;
    memset(nombre, 0, sizeof(nombre));
    memset(apellido, 0, sizeof(apellido));
    memset(dni, 0, sizeof(dni));
    memset(telefono, 0, sizeof(telefono));
    estado = true;
}

void Cliente::cargar() {
    cout << "ID: ";
    cin >> id;
    cin.ignore();

    cout << "Nombre: ";
    cin.getline(nombre, sizeof(nombre));

    cout << "Apellido: ";
    cin.getline(apellido, sizeof(apellido));

    cout << "DNI: ";
    cin.getline(dni, sizeof(dni));

    cout << "Telefono: ";
    cin.getline(telefono, sizeof(telefono));
    estado = true;
}

void Cliente::mostrar() {
    if (estado) {
        cout << "ID: " << id << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Apellido: " << apellido << endl;
        cout << "DNI: " << dni << endl;
        cout << "Telefono: " << telefono << endl;
        cout << "-------------------------\n";
    }
}

int Cliente::getId() {
    return id;
}

void Cliente::setId(int nuevoId) {
    id = nuevoId;
}

bool Cliente::getEstado() {
    return estado;
}

void Cliente::setEstado(bool nuevoEstado) {
    estado = nuevoEstado;
}

bool Cliente::guardarEnDisco() {
    ofstream archi("clientes.dat", ios::app | ios::binary);
    if (!archi.is_open()) return false;
    archi.write(reinterpret_cast<char*>(this), sizeof(*this));
    archi.close();
    return true;
}

bool Cliente::leerDeDisco(int pos) {
    ifstream archi("clientes.dat", ios::binary);
    if (!archi.is_open()) return false;
    archi.seekg(pos * sizeof(*this));
    bool exito = archi.read(reinterpret_cast<char*>(this), sizeof(*this)).good();
    archi.close();
    return exito;
}

bool Cliente::modificarEnDisco(int pos) {
    fstream archi("clientes.dat", ios::in | ios::out | ios::binary);
    if (!archi.is_open()) return false;
    archi.seekp(pos * sizeof(*this));
    archi.write(reinterpret_cast<char*>(this), sizeof(*this));
    archi.close();
    return true;
}
