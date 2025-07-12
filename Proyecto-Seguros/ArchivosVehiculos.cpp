#include "ArchivosVehiculos.h"
#include "Vehiculo.h"
#include <iostream>
#include <cstring>
#include <limits>
#include <fstream>

using namespace std;

int ArchivoVehiculo::buscarVehiculo(int idVehiculo) {
    Vehiculo obj;
    FILE *pVehiculo;
    pVehiculo = fopen(nombre, "rb");

    if (pVehiculo == nullptr) {
        return -2;
    }

    int pos = 0;
    while (fread(&obj, tamanioRegistro, 1, pVehiculo) == 1) {
        if (obj.getIdVehiculo() == idVehiculo) {
            fclose(pVehiculo);
            return pos;
        }
        pos++;
    }

    fclose(pVehiculo);
    return -1;
}

int ArchivoVehiculo::buscarPatente(const char* patente) {
    Vehiculo obj;
    FILE *pVehiculo;
    pVehiculo = fopen(nombre, "rb");

    if (pVehiculo == nullptr) {
        return -2;
    }

    int pos = 0;
    while (fread(&obj, tamanioRegistro, 1, pVehiculo) == 1) {
        if (strcmp(obj.getPatente(), patente) == 0) {
            fclose(pVehiculo);
            return pos;
        }
        pos++;
    }

    fclose(pVehiculo);
    return -1;
}

int ArchivoVehiculo::agregarRegistro() {
    Vehiculo nuevoVehiculo;
    cout << "--- AGREGAR VEHICULO ---" << endl;

    nuevoVehiculo.cargarId();

    int resultado = buscarVehiculo(nuevoVehiculo.getIdVehiculo());
    if (resultado >= 0) {  // Solo si encontró un registro existente (posición válida >= 0)
        cout << "Error: ya existe un vehiculo con el ID " << nuevoVehiculo.getIdVehiculo() << "." << endl;
        system("pause");
        return -2;
    }

    nuevoVehiculo.cargarDatos();

    FILE *pVehiculo;
    pVehiculo = fopen(nombre, "ab");
    if (pVehiculo == nullptr) {
        cout << "No se pudo abrir el archivo para escribir." << endl;
        return -1;
    }

    int escribio = fwrite(&nuevoVehiculo, tamanioRegistro, 1, pVehiculo);
    fclose(pVehiculo);

    if (escribio == 1) {
        cout << "\nVehiculo guardado con exito.\n" << endl;
    }
    system("pause");
    return escribio;
}

bool ArchivoVehiculo::listarRegistros() {
    Vehiculo obj;
    FILE *pVehiculo;
    pVehiculo = fopen(nombre, "rb");

    if (pVehiculo == nullptr) {
        cout << "No se pudo abrir el archivo de vehiculos." << endl;
        cout << "No hay vehiculos cargados." << endl;
        system("pause");
        return false;
    }

    bool hayVehiculosActivos = false;
    system("cls");
    cout << "LISTADO DE VEHICULOS" << endl;
    cout << "--------------------------------" << endl;

    while (fread(&obj, tamanioRegistro, 1, pVehiculo) == 1) {
        if (obj.getActivo()) {
            obj.mostrar();
            hayVehiculosActivos = true;
        }
    }

    fclose(pVehiculo);

    if (!hayVehiculosActivos) {
        cout << "No hay vehiculos cargados para mostrar." << endl;
    }
    return true;
}

Vehiculo ArchivoVehiculo::leerRegistro(int pos) {
    Vehiculo obj;
    FILE *pVehiculo;
    pVehiculo = fopen(nombre, "rb");

    obj.setIdVehiculo(-1);

    if (pVehiculo == nullptr) {
        return obj;
    }

    fseek(pVehiculo, pos * tamanioRegistro, SEEK_SET);
    fread(&obj, tamanioRegistro, 1, pVehiculo);
    fclose(pVehiculo);

    return obj;
}

bool ArchivoVehiculo::modificarRegistro(Vehiculo reg, int pos) {
    FILE *pVehiculo;
    pVehiculo = fopen(nombre, "rb+");
    if (pVehiculo == nullptr) {
        return false;
    }

    fseek(pVehiculo, pos * tamanioRegistro, SEEK_SET);
    int escribio = fwrite(&reg, tamanioRegistro, 1, pVehiculo);
    fclose(pVehiculo);

    return escribio == 1;
}

bool ArchivoVehiculo::modificarDatosVehiculo() {
    int idBuscado;
    system("cls");
    cout << "--- MODIFICAR VEHICULO ---" << endl;
    cout << "Ingrese el ID del vehiculo a modificar: ";
    cin >> idBuscado;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    int pos = buscarVehiculo(idBuscado);

    if (pos < 0) {
        cout << "Vehiculo con ID " << idBuscado << " no encontrado o error al leer archivo." << endl;
        system("pause");
        return false;
    }

    Vehiculo v = leerRegistro(pos);

    if (!v.getActivo()) {
        cout << "El vehiculo con ID " << idBuscado << " esta dado de baja y no puede ser modificado." << endl;
        system("pause");
        return false;
    }

    cout << "\nVehiculo encontrado:" << endl;
    v.mostrar();
    cout << "\nIngrese los NUEVOS datos:" << endl;

    v.cargarDatos();

    if (modificarRegistro(v, pos)) {
        cout << "\nVehiculo modificado exitosamente." << endl;
    } else {
        cout << "\nError al modificar el vehiculo." << endl;
    }
    system("pause");
    return true;
}

bool ArchivoVehiculo::bajaLogica() {
    int idBuscado;
    system("cls");
    cout << "--- ELIMINAR VEHICULO ---" << endl;
    cout << "Ingrese el ID del vehiculo a eliminar: ";
    cin >> idBuscado;

    int pos = buscarVehiculo(idBuscado);
    if (pos < 0) {
        cout << "No se encontro el vehiculo con ID " << idBuscado << " o hubo un error." << endl;
        system("pause");
        return false;
    }

    Vehiculo reg = leerRegistro(pos);

    if(!reg.getActivo()){
        cout << "El vehiculo con ID " << idBuscado << " ya se encuentra dado de baja." << endl;
        system("pause");
        return false;
    }

    cout << "Vehiculo encontrado:" << endl;
    reg.mostrar();
    char confirmacion;
    cout << "Esta seguro de eliminar este vehiculo (S/N)? ";
    cin >> confirmacion;
    confirmacion = toupper(confirmacion);

    if(confirmacion == 'S'){
        reg.setActivo(false);
        if (modificarRegistro(reg, pos)) {
            cout << "Vehiculo eliminado exitosamente." << endl;
        } else {
            cout << "Error al intentar dar de baja al vehiculo." << endl;
        }
    } else {
        cout << "Eliminacion cancelada por el usuario." << endl;
    }

    system("pause");
    return true;
}

int ArchivoVehiculo::contarRegistros() {
    FILE *pVehiculo;
    pVehiculo = fopen(nombre, "rb");

    if (pVehiculo == nullptr) {
        return -1;
    }

    fseek(pVehiculo, 0, SEEK_END);
    int tam = ftell(pVehiculo);
    fclose(pVehiculo);

    return tam / tamanioRegistro;
}

bool ArchivoVehiculo::exportarCSV(const char* nombreArchivo) {
    Vehiculo obj;
    FILE *pVehiculo;
    pVehiculo = fopen(nombre, "rb");
    
    if (pVehiculo == nullptr) {
        cout << "No se pudo abrir el archivo de vehiculos." << endl;
        return false;
    }
    
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "No se pudo crear el archivo CSV." << endl;
        fclose(pVehiculo);
        return false;
    }
    
    // Escribir encabezados
    archivo << "ID_Vehiculo,Marca,Version,Anio,Patente,Activo\n";
    
    // Escribir datos
    while (fread(&obj, tamanioRegistro, 1, pVehiculo) == 1) {
        if (obj.getActivo()) {
            archivo << obj.getIdVehiculo() << ","
                   << obj.getMarca() << ","
                   << obj.getVersion() << ","
                   << obj.getAnio() << ","
                   << obj.getPatente() << ","
                   << (obj.getActivo() ? "Si" : "No") << "\n";
        }
    }
    
    fclose(pVehiculo);
    archivo.close();
    cout << "Archivo CSV exportado exitosamente: " << nombreArchivo << endl;
    return true;
}
