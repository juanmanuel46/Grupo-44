#include "ArchivosSiniestro.h"
#include "siniestro.h"
#include <iostream>
#include <cstring>

using namespace std;

int ArchivoSiniestro::buscarSiniestro(int idSiniestro) {
    Siniestro obj;
    FILE *pSiniestro;
    pSiniestro = fopen(nombre, "rb");

    if (pSiniestro == nullptr) {
        return -2; 
    }

    int pos = 0;
    while (fread(&obj, tamanioRegistro, 1, pSiniestro) == 1) {
        if (obj.getIdSiniestro() == idSiniestro) {
            fclose(pSiniestro);
            return pos;
        }
        pos++;
    }

    fclose(pSiniestro);
    return -1; // No encontrado
}

int ArchivoSiniestro::agregarRegistro() {
    Siniestro nuevoSiniestro;
    cout << "--- AGREGAR SINIESTRO ---" << endl;

    nuevoSiniestro.cargarId();

    if (buscarSiniestro(nuevoSiniestro.getIdSiniestro()) != -1) {
        cout << "Error: ya existe un siniestro con el ID " << nuevoSiniestro.getIdSiniestro() << "." << endl;
        system("pause");
        return -2;
    }
    
    nuevoSiniestro.cargarDatos(); 

    FILE *pSiniestro;
    pSiniestro = fopen(nombre, "ab");
    if (pSiniestro == nullptr) {
        cout << "No se pudo abrir el archivo para escribir." << endl;
        return -1;
    }

    int escribio = fwrite(&nuevoSiniestro, tamanioRegistro, 1, pSiniestro);
    fclose(pSiniestro);

    if (escribio == 1) {
        cout << "\nSiniestro guardado con exito.\n" << endl;
    }
    system("pause");
    return escribio;
}

bool ArchivoSiniestro::listarRegistros() {
    Siniestro obj;
    FILE *pSiniestro;
    pSiniestro = fopen(nombre, "rb");

    if (pSiniestro == nullptr) {
        cout << "No se pudo abrir el archivo de siniestros." << endl;
        cout << "No hay siniestros cargados." << endl;
        system("pause");
        return false;
    }
    
    bool haySiniestrosActivos = false;
    system("cls");
    cout << "LISTADO DE SINIESTROS" << endl;
    cout << "--------------------------------" << endl;

    while (fread(&obj, tamanioRegistro, 1, pSiniestro) == 1) {
        if (obj.getActivo()) {
            obj.mostrar();
            haySiniestrosActivos = true;
        }
    }

    fclose(pSiniestro);

    if (!haySiniestrosActivos) {
        cout << "No hay siniestros cargados para mostrar." << endl;
    }
    return true;
}

Siniestro ArchivoSiniestro::leerRegistro(int pos) {
    Siniestro obj;
    FILE *pSiniestro;
    pSiniestro = fopen(nombre, "rb");
    
    obj.setIdSiniestro(-1); 

    if (pSiniestro == nullptr) {
        return obj;
    }

    fseek(pSiniestro, pos * tamanioRegistro, SEEK_SET);
    fread(&obj, tamanioRegistro, 1, pSiniestro);
    fclose(pSiniestro);

    return obj;
}

bool ArchivoSiniestro::modificarRegistro(Siniestro reg, int pos) {
    FILE *pSiniestro;
    pSiniestro = fopen(nombre, "rb+");
    if (pSiniestro == nullptr) {
        return false;
    }

    fseek(pSiniestro, pos * tamanioRegistro, SEEK_SET);
    int escribio = fwrite(&reg, tamanioRegistro, 1, pSiniestro);
    fclose(pSiniestro);

    return escribio == 1;
}

bool ArchivoSiniestro::modificarDatosSiniestro() {
    int idBuscado;
    system("cls");
    cout << "--- MODIFICAR SINIESTRO ---" << endl;
    cout << "Ingrese el ID del siniestro a modificar: ";
    cin >> idBuscado;

    int pos = buscarSiniestro(idBuscado);

    if (pos < 0) {
        cout << "Siniestro con ID " << idBuscado << " no encontrado o error al leer archivo." << endl;
        system("pause");
        return false;
    }

    Siniestro s = leerRegistro(pos);

    if (!s.getActivo()) {
        cout << "El siniestro con ID " << idBuscado << " esta dado de baja y no puede ser modificado." << endl;
        system("pause");
        return false;
    }

    cout << "\nSiniestro encontrado:" << endl;
    s.mostrar();
    cout << "\nIngrese los NUEVOS datos:" << endl;

    s.cargarDatos(); 

    if (modificarRegistro(s, pos)) {
        cout << "\nSiniestro modificado exitosamente." << endl;
    } else {
        cout << "\nError al modificar el siniestro." << endl;
    }
    system("pause");
    return true;
}

bool ArchivoSiniestro::bajaLogica() {
    int idBuscado;
    system("cls");
    cout << "--- ELIMINAR SINIESTRO ---" << endl;
    cout << "Ingrese el ID del siniestro a eliminar: ";
    cin >> idBuscado;
    
    int pos = buscarSiniestro(idBuscado);
    if (pos < 0) {
        cout << "No se encontro el siniestro con ID " << idBuscado << " o hubo un error." << endl;
        system("pause");
        return false;
    }
    
    Siniestro reg = leerRegistro(pos);
    
    if(!reg.getActivo()){
        cout << "El siniestro con ID " << idBuscado << " ya se encuentra dado de baja." << endl;
        system("pause");
        return false;
    }

    cout << "Siniestro encontrado:" << endl;
    reg.mostrar();
    char confirmacion;
    cout << "Esta seguro de eliminar este siniestro (S/N)? ";
    cin >> confirmacion;
    confirmacion = toupper(confirmacion);

    if(confirmacion == 'S'){
        reg.setActivo(false);
        if (modificarRegistro(reg, pos)) {
            cout << "Siniestro eliminado exitosamente." << endl;
        } else {
            cout << "Error al intentar dar de baja al siniestro." << endl;
        }
    } else {
        cout << "Eliminacion cancelada por el usuario." << endl;
    }

    system("pause");
    return true;
}

int ArchivoSiniestro::contarRegistros() {
    FILE *pSiniestro;
    pSiniestro = fopen(nombre, "rb");

    if (pSiniestro == nullptr) {
        return -1;
    }

    fseek(pSiniestro, 0, SEEK_END);
    int tam = ftell(pSiniestro);
    fclose(pSiniestro);

    return tam / tamanioRegistro;
}