#include "ArchivosClientes.h"
#include "Cliente.h"
#include <iostream>
#include <cstring>

using namespace std;

int ArchivoCliente::buscarCliente(int idCliente) {
    Cliente obj;
    FILE *pCliente;
    pCliente = fopen(nombre, "rb");

    if (pCliente == nullptr) {
        return -2; // Error de archivo
    }

    int pos = 0;
    while (fread(&obj, tamanioRegistro, 1, pCliente) == 1) {
        if (obj.getIdCliente() == idCliente) {
            fclose(pCliente);
            return pos;
        }
        pos++;
    }

    fclose(pCliente);
    return -1; // No encontrado
}

int ArchivoCliente::agregarRegistro() {
    Cliente nuevoCliente;
    cout << "--- AGREGAR CLIENTE ---" << endl;

    nuevoCliente.cargarId(); // Asumo que este método pide y carga solo el ID.

    if (buscarCliente(nuevoCliente.getIdCliente()) != -1) {
        cout << "Error: ya existe un cliente con el ID " << nuevoCliente.getIdCliente() << "." << endl;
        system("pause");
        return -2; // ID Duplicado
    }
    
    nuevoCliente.cargarDatos(); // Asumo que este método pide y carga el resto de los datos.

    FILE *pCliente;
    pCliente = fopen(nombre, "ab");
    if (pCliente == nullptr) {
        cout << "No se pudo abrir el archivo para escribir." << endl;
        return -1; // Error de apertura en modo escritura
    }

    int escribio = fwrite(&nuevoCliente, tamanioRegistro, 1, pCliente);
    fclose(pCliente);

    if (escribio == 1) {
        cout << "\nCliente guardado con exito.\n" << endl;
    }
    system("pause");
    return escribio;
}

bool ArchivoCliente::listarRegistros() {
    Cliente obj;
    FILE *pCliente;
    pCliente = fopen(nombre, "rb");

    if (pCliente == nullptr) {
        cout << "No se pudo abrir el archivo de clientes." << endl;
        cout << "No hay clientes cargados." << endl;
        system("pause");
        return false;
    }
    
    bool hayClientesActivos = false;
    system("cls");
    cout << "LISTADO DE CLIENTES" << endl;
    cout << "--------------------------------" << endl;

    while (fread(&obj, tamanioRegistro, 1, pCliente) == 1) {
        if (obj.getActivo()) {
            obj.mostrar();
            hayClientesActivos = true;
        }
    }

    fclose(pCliente);

    if (!hayClientesActivos) {
        cout << "No hay clientes cargados para mostrar." << endl;
    }
    return true;
}

Cliente ArchivoCliente::leerRegistro(int pos) {
    Cliente obj;
    FILE *pCliente;
    pCliente = fopen(nombre, "rb");
    
    // Inicialización por si falla la apertura o lectura
    obj.setIdCliente(-1); 

    if (pCliente == nullptr) {
        return obj;
    }

    fseek(pCliente, pos * tamanioRegistro, SEEK_SET);
    fread(&obj, tamanioRegistro, 1, pCliente);
    fclose(pCliente);

    return obj;
}

bool ArchivoCliente::modificarRegistro(Cliente reg, int pos) {
    FILE *pCliente;
    pCliente = fopen(nombre, "rb+"); // rb+ para leer y escribir
    if (pCliente == nullptr) {
        return false;
    }

    fseek(pCliente, pos * tamanioRegistro, SEEK_SET);
    int escribio = fwrite(&reg, tamanioRegistro, 1, pCliente);
    fclose(pCliente);

    return escribio == 1;
}

bool ArchivoCliente::modificarDatosCliente() {
    int idBuscado;
    system("cls");
    cout << "--- MODIFICAR CLIENTE ---" << endl;
    cout << "Ingrese el ID del cliente a modificar: ";
    cin >> idBuscado;

    int pos = buscarCliente(idBuscado);

    if (pos == -1) {
        cout << "Cliente con ID " << idBuscado << " no encontrado." << endl;
        system("pause");
        return false;
    }
    if (pos == -2) {
        cout << "Error al abrir el archivo de clientes." << endl;
        system("pause");
        return false;
    }

    Cliente cli = leerRegistro(pos);

    if (!cli.getActivo()) {
        cout << "El cliente con ID " << idBuscado << " esta dado de baja y no puede ser modificado." << endl;
        system("pause");
        return false;
    }

    cout << "\nCliente encontrado:" << endl;
    cli.mostrar();
    cout << "\nIngrese los NUEVOS datos:" << endl;

    cli.cargarDatos(); // Asumo que carga todos los datos excepto el ID y estado.

    if (modificarRegistro(cli, pos)) {
        cout << "\nCliente modificado exitosamente." << endl;
    } else {
        cout << "\nError al modificar el cliente." << endl;
    }
    system("pause");
    return true;
}


bool ArchivoCliente::bajaLogica(int idCliente) {
    int pos = buscarCliente(idCliente);
    if (pos < 0) {
        cout << "No se encontro el cliente con ID " << idCliente << " o hubo un error." << endl;
        system("pause");
        return false;
    }
    
    Cliente reg = leerRegistro(pos);
    
    if(!reg.getActivo()){
        cout << "El cliente con ID " << idCliente << " ya se encuentra dado de baja." << endl;
        system("pause");
        return false;
    }

    cout << "Cliente encontrado:" << endl;
    reg.mostrar();
    char confirmacion;
    cout << "Esta seguro de eliminar este cliente (S/N)? ";
    cin >> confirmacion;
    confirmacion = toupper(confirmacion);

    if(confirmacion == 'S'){
        reg.setActivo(false);
        if (modificarRegistro(reg, pos)) {
            cout << "Cliente eliminado exitosamente." << endl;
        } else {
            cout << "Error al intentar dar de baja al cliente." << endl;
        }
    } else {
        cout << "Eliminacion cancelada por el usuario." << endl;
    }

    system("pause");
    return true;
}

int ArchivoCliente::contarRegistros() {
    FILE *pCliente;
    pCliente = fopen(nombre, "rb");

    if (pCliente == nullptr) {
        return -1;
    }

    fseek(pCliente, 0, SEEK_END);
    int tam = ftell(pCliente);
    fclose(pCliente);

    return tam / tamanioRegistro;
}