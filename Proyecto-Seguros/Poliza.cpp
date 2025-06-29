#include "Poliza.h"
#include <iostream>
#include <limits>
#include <cstring>

using namespace std;

Poliza::Poliza() {
    _numeroPoliza = 0;
    _dni = 0;
    strcpy(_patente, "");
    _fechaInicio = Fecha();
    _fechaVencimiento = Fecha();
    strcpy(_nombre, "");
    strcpy(_apellido, "");
    strcpy(_detalleCobertura, "");
    _importeMensual = 0.0f;
    _activo = true;
}

// Getters corregidos
int Poliza::getNumeroPoliza() const { return _numeroPoliza; }
int Poliza::getDni() const { return _dni; }
const char* Poliza::getPatente() const { return _patente; }
const Fecha& Poliza::getFechaInicio() const { return _fechaInicio; }
const Fecha& Poliza::getFechaVencimiento() const { return _fechaVencimiento; }
const char* Poliza::getNombre() const { return _nombre; }
const char* Poliza::getApellido() const { return _apellido; }  // Añadido (faltaba en .h)
const char* Poliza::getDetalleCobertura() const { return _detalleCobertura; }
float Poliza::getImporteMensual() const { return _importeMensual; }
bool Poliza::isActivo() const { return _activo; }  // Corregido: _activo

// Setters corregidos
void Poliza::setNumeroPoliza(int numeroPoliza) { _numeroPoliza = numeroPoliza; }
void Poliza::setDni(int dni) { _dni = dni; }
void Poliza::setPatente(const char* patente) {
    strncpy(_patente, patente, 9);
    _patente[9] = '\0';
}
void Poliza::setFechaInicio(const Fecha& fecha) { _fechaInicio = fecha; }
void Poliza::setFechaVencimiento(const Fecha& fecha) { _fechaVencimiento = fecha; }
void Poliza::setNombre(const char* nombre) {
    strncpy(_nombre, nombre, 9);
    _nombre[9] = '\0';
}
void Poliza::setApellido(const char* apellido) {  // Añadido (faltaba en .h)
    strncpy(_apellido, apellido, 9);
    _apellido[9] = '\0';
}
void Poliza::setDetalleCobertura(const char* detalle) {
    strncpy(_detalleCobertura, detalle, 39);
    _detalleCobertura[39] = '\0';
}
void Poliza::setImporteMensual(float importe) { _importeMensual = importe; }
void Poliza::setActivo(bool estado) { _activo = estado; }


//////////////////////////////////////////////////////////////////////////////////////////////////////////


void Poliza::mostrar() const {
    cout << "Nro de poliza: " << _numeroPoliza << endl;
    cout << "DNI: " << _dni << endl;
    cout << "Patente: " << _patente << endl;
    cout << "Fecha de inicio: ";
//    _fechaInicio.mostrar();  // Suponiendo que hay un método mostrar() en la clase Fecha
    cout << "Fecha de vencimiento: ";
 //   _fechaVencimiento.mostrar();  // Igual que arriba
    cout << "Nombre: " << _nombre << endl;
    cout << "Apellido: " << _apellido << endl;
    cout << "Detalle de cobertura: " << _detalleCobertura << endl;
    cout << "Importe mensual: " << _importeMensual << endl;
    cout << "Estado: " << (_activo ? "Activa" : "Inactiva") << endl;
    cout << "-------------------------\n";

}



void Poliza::cargarId() {
    cout << "Ingrese número de póliza: ";
    cin >> _numeroPoliza;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

}


void Poliza::cargarDatos(){
    cout << "Ingrese DNI del titular: ";
    cin >> _dni;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Ingrese patente del vehículo: ";
    cin.getline(_patente, 10);

    cout << "Ingrese fecha de inicio:" << endl;
    //_fechaInicio.cargar();  // Debes tener un método cargar() en la clase Fecha

    cout << "Ingrese fecha de vencimiento:" << endl;
    //_fechaVencimiento.cargar();

    cout << "Ingrese nombre del titular: ";
    cin.getline(_nombre, 10);

    cout << "Ingrese apellido del titular: ";
    cin.getline(_apellido, 10);

    cout << "Ingrese detalle de cobertura: ";
    cin.getline(_detalleCobertura, 40);

    cout << "Ingrese importe mensual: ";
    cin >> _importeMensual;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "¿La póliza está activa? (1 para sí, 0 para no): ";
    cin >> _activo;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void Poliza::cargar() {
    cargarId();
    cargarDatos();
}
