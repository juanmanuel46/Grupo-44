#include "Cliente.h"
#include <iostream>
#include <cstring>
#include <limits>

using namespace std;

Cliente::Cliente() {
    idCliente = 0;
    strcpy(nombre, "");
    strcpy(apellido, "");
    dni = 0;
    fechaNacimiento = 0;
    strcpy(domicilio, "");
    strcpy(email, "");
    strcpy(telefono, "");
    activo = true;
}

// Getters

int Cliente::getIdCliente() const {
    return idCliente;
}

const char* Cliente::getNombre() const {
    return nombre;
}

const char* Cliente::getApellido() const {
    return apellido;
}

int Cliente::getDni() const {
    return dni;
}

int Cliente::getFechaNacimiento() const {
    return fechaNacimiento;
}

bool Cliente::getActivo() const {
    return activo;
}

const char* Cliente::getDomicilio() const {
    return domicilio;
}

const char* Cliente::getEmail() const {
    return email;
}

const char* Cliente::getTelefono() const {
    return telefono;
}

// Setters

void Cliente::setIdCliente(int valor) {
    idCliente = valor;
}

void Cliente::setNombre(const char* valor) {
    strncpy(nombre, valor, sizeof(nombre) - 1);
    nombre[sizeof(nombre) - 1] = '\0';
}

void Cliente::setApellido(const char* valor) {
    strncpy(apellido, valor, sizeof(apellido) - 1);
    apellido[sizeof(apellido) - 1] = '\0';
}

void Cliente::setDni(int valor) {
    dni = valor;
}

void Cliente::setFechaNacimiento(int valor) {
    fechaNacimiento = valor;
}

void Cliente::setActivo(bool valor) {
    activo = valor;
}

void Cliente::setDomicilio(const char* valor) {
    strncpy(domicilio, valor, sizeof(domicilio) - 1);
    domicilio[sizeof(domicilio) - 1] = '\0';
}

void Cliente::setEmail(const char* valor) {
    strncpy(email, valor, sizeof(email) - 1);
    email[sizeof(email) - 1] = '\0';
}

void Cliente::setTelefono(const char* valor) {
    strncpy(telefono, valor, sizeof(telefono) - 1);
    telefono[sizeof(telefono) - 1] = '\0';
}

// Métodos funcionales

void Cliente::mostrar() const {
    cout << "ID Cliente: " << idCliente << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Apellido: " << apellido << endl;
    cout << "DNI: " << dni << endl;
    cout << "Fecha de nacimiento: " << fechaNacimiento << endl;
    cout << "Domicilio: " << domicilio << endl;
    cout << "Email: " << email << endl;
    cout << "Telefono: " << telefono << endl;
    cout << "-------------------------\n";
}

void Cliente::cargarId() {
    cout << "Ingrese ID del cliente: ";
    cin >> idCliente;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Cliente::cargarDatos() {
    cout << "Nombre: ";
    cin.getline(nombre, sizeof(nombre));

    cout << "Apellido: ";
    cin.getline(apellido, sizeof(apellido));

    cout << "DNI: ";
    cin >> dni;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    cout << "Fecha de nacimiento (AAAAMMDD): ";
    cin >> fechaNacimiento;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    cout << "Domicilio: ";
    cin.getline(domicilio, sizeof(domicilio));

    cout << "Email: ";
    cin.getline(email, sizeof(email));

    cout << "Telefono: ";
    cin.getline(telefono, sizeof(telefono));

    activo = true;
}

void Cliente::cargar() {
    cargarId();
    cargarDatos();
}
