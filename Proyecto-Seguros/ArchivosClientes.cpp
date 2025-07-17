#include "ArchivosClientes.h"
#include "Cliente.h"
#include <iostream>
#include <cstring>
#include <limits>
#include <fstream>

using namespace std;

int ArchivoCliente::buscarCliente(int idCliente) {
    Cliente obj;
    FILE *pCliente;
    pCliente = fopen(nombre, "rb");

    if (pCliente == nullptr) {
        return -2;
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
    return -1;
}

int ArchivoCliente::buscarClienteDni(int dniCliente) {
    Cliente obj;
    FILE *pCliente;
    pCliente = fopen(nombre, "rb");

    if (pCliente == nullptr) {
        return -2;
    }

    int pos = 0;
    while (fread(&obj, tamanioRegistro, 1, pCliente) == 1) {
        if (obj.getDni() == dniCliente) {
            fclose(pCliente);
            return pos;
        }
        pos++;
    }

    fclose(pCliente);
    return -1;
}

int ArchivoCliente::agregarRegistro() {
    Cliente nuevoCliente;
    cout << "--- AGREGAR CLIENTE ---" << endl;

    nuevoCliente.cargarId();

    int resultado = buscarCliente(nuevoCliente.getIdCliente());
    if (resultado >= 0) {  
        cout << "Error: ya existe un cliente con el ID " << nuevoCliente.getIdCliente() << "." << endl;
        system("pause");
        return -2;
    }


    nuevoCliente.cargarDatos();

    FILE *pCliente;
    pCliente = fopen(nombre, "ab");
    if (pCliente == nullptr) {
        cout << "No se pudo abrir el archivo para escribir." << endl;
        return -1;
    }

    int escribio = fwrite(&nuevoCliente, tamanioRegistro, 1, pCliente);
    fclose(pCliente);

    if (escribio == 1) {
        cout << "\nCliente guardado con exito.\n" << endl;
    }
    system("pause");
    return escribio;
}

int ArchivoCliente::agregarRegistro(int dni) {
    Cliente nuevoCliente;
    cout << "--- AGREGAR CLIENTE ---" << endl;
    cout << "DNI del cliente: " << dni << endl;

    // Bucle para pedir ID hasta que sea único
    bool idValido = false;
    while (!idValido) {
        nuevoCliente.cargarId();
        
        int resultado = buscarCliente(nuevoCliente.getIdCliente());
        if (resultado >= 0) {  
            cout << "Error: ya existe un cliente con el ID " << nuevoCliente.getIdCliente() << "." << endl;
            cout << "Desea ingresar un ID diferente? (S/N): " << endl;
            char respuesta;
            cin >> respuesta;
            respuesta = toupper(respuesta);


            if(respuesta == 'S'){
                cout << "Ingrese un nuevo ID para el cliente:" << endl;
                // El bucle continuará para pedir otro ID
            } else if(respuesta == 'N'){
                cout << "Operacion cancelada." << endl;
                system("pause");
                return -2;
            }
        } else {
            // ID es único, salir del bucle
            idValido = true;
        }
    }

    // Crear nuevo cliente con ID único
    nuevoCliente.setDni(dni);
    nuevoCliente.cargarDatosSinDni();

    FILE *pCliente;
    pCliente = fopen(nombre, "ab");
    if (pCliente == nullptr) {
        cout << "No se pudo abrir el archivo para escribir." << endl;
        return -1;
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

Cliente ArchivoCliente::leerRegistro() {
    Cliente obj;
    FILE *pCliente;
    pCliente = fopen(nombre, "rb");

    // Inicialización por si falla la apertura o lectura
    obj.setIdCliente(-1);

    if (pCliente == nullptr) {
        return obj;
    }

    fseek(pCliente, -1* tamanioRegistro, SEEK_END);
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

bool ArchivoCliente::modificarRegistro(Cliente reg) {
    FILE *pCliente;
    pCliente = fopen(nombre, "rb+"); // rb+ para leer y escribir
    if (pCliente == nullptr) {
        return false;
    }

    fseek(pCliente, -1* tamanioRegistro, SEEK_END);
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
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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

bool ArchivoCliente::exportarCSV(const char* nombreArchivo) {
    Cliente obj;
    FILE *pCliente;
    pCliente = fopen(nombre, "rb");

    if (pCliente == nullptr) {
        cout << "No se pudo abrir el archivo de clientes." << endl;
        return false;
    }

    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "No se pudo crear el archivo CSV." << endl;
        fclose(pCliente);
        return false;
    }

    // Escribir encabezados
    archivo << "ID,Nombre,Apellido,DNI,Fecha_Nacimiento,Activo,Domicilio,Email,Telefono\n";

    // Escribir datos
    while (fread(&obj, tamanioRegistro, 1, pCliente) == 1) {
        if (obj.getActivo()) {
            Fecha fecha = obj.getFechaNacimiento();
            archivo << obj.getIdCliente() << ","
                   << obj.getNombre() << ","
                   << obj.getApellido() << ","
                   << obj.getDni() << ","
                   << fecha.getDia() << "/" << fecha.getMes() << "/" << fecha.getAnio() << ","
                   << (obj.getActivo() ? "Si" : "No") << ","
                   << obj.getDomicilio() << ","
                   << obj.getEmail() << ","
                   << obj.getTelefono() << "\n";
        }
    }

    fclose(pCliente);
    archivo.close();
    cout << "Archivo CSV exportado exitosamente: " << nombreArchivo << endl;
    return true;
}
