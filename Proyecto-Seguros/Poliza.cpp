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
    strcpy(_detalleCobertura, "");
    _importeMensual = 0.0f;
    _activo = true;
}

// Getters corregidos
int Poliza::getNumeroPoliza()  { return _numeroPoliza; }
int Poliza::getDni()  { return _dni; }
const char* Poliza::getPatente()  { return _patente; }
const Fecha& Poliza::getFechaInicio()  { return _fechaInicio; }
const Fecha& Poliza::getFechaVencimiento()  { return _fechaVencimiento; }
const char* Poliza::getNombre()  { return _nombre; }
const char* Poliza::getApellido()  { return _apellido; }  // A�adido (faltaba en .h)
const char* Poliza::getDetalleCobertura()  { return _detalleCobertura; }
float Poliza::getImporteMensual()  { return _importeMensual; }
bool Poliza::isActivo()  { return _activo; }  // Corregido: _activo

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
void Poliza::setApellido(const char* apellido) {  // A�adido (faltaba en .h)
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


void Poliza::mostrar()  {
    cout << "Nro de poliza: " << _numeroPoliza << endl;
    cout << "DNI: " << _dni << endl;
    cout << "Patente: " << _patente << endl;
    cout << "Fecha de inicio: " << _fechaInicio.toString() << endl;
    cout << "Fecha de vencimiento: " << _fechaVencimiento.toString() << endl;
    cout << "Detalle de cobertura: " << _detalleCobertura << endl;
    cout << "Importe mensual: " << _importeMensual << endl;
    cout << "Estado: " << (_activo ? "Activa" : "Inactiva") << endl;
    cout << "-------------------------\n";
}



void Poliza::cargarId() {
    cout << "Ingrese numero de poliza: ";
    cin >> _numeroPoliza;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

}
void Poliza::cargarDNI() {
    cout << "Ingrese DNI del titular: ";
    cin >> _dni;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void Poliza::cargarPatente(){

    cout << "Ingrese patente del vehiculo: ";
    cin.getline(_patente, 10);
}

void Poliza::cargarDatos(){

    cout << "Ingrese detalle de cobertura: ";
    cin.getline(_detalleCobertura, 40);

    cout << "Ingrese fecha de inicio:" << endl;
    _fechaInicio.cargar();

    cout << "Ingrese fecha de vencimiento:" << endl;
    _fechaVencimiento.cargar();

    cout << "Ingrese importe mensual: ";
    cin >> _importeMensual;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout <<"¿La poliza esta activa? (1 para si, 0 para no): ";
    cin >>_activo;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void Poliza::cargar() {
    cargarId();
    cargarDNI();
    cargarPatente();
    cargarDatos();
}
