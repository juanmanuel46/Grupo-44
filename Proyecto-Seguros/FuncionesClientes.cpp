#include <iostream>
#include <fstream>
#include "Cliente.h"
#include <cstdlib>
#include <limits>

using namespace std;

void agregarCliente() {
    Cliente cli;
    cli.cargar();
    if (cli.guardarEnDisco()) {
        cout << "Cliente guardado correctamente.\n";
    } else {
        cout << "Error al guardar el cliente.\n";
    }
    system("pause");
}

void listarClientes() {
    Cliente cli;
    int pos = 0;
    bool hayClientesActivos = false;

    system("cls");
    cout << "LISTADO DE CLIENTES\n";
    cout << "--------------------------------\n";

    ifstream archi("clientes.dat", ios::binary);
    if (!archi.is_open()) {
        cout << "No se pudo abrir el archivo de clientes.\n";
        cout << "No hay clientes cargados.\n";
        system("pause");
        return;
    }

    while (archi.read(reinterpret_cast<char*>(&cli), sizeof(Cliente))) {
        if (cli.getEstado()) {
            cout << "Cliente #" << pos + 1 << endl;
            cli.mostrar();
            hayClientesActivos = true;
        }
        pos++;
    }

    archi.close();

    if (!hayClientesActivos) {
        cout << "No hay clientes cargados para mostrar.\n";
    }

    system("pause");
}

void modificarCliente() {
    Cliente cli;
    int idBuscado;
    cout << "Ingrese el ID del cliente a modificar: ";
    cin >> idBuscado;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int pos = 0;
    bool encontrado = false;

    fstream archi("clientes.dat", ios::in | ios::out | ios::binary);
    if (!archi) {
        cout << "Error al abrir archivo de clientes para modificar.\n";
        system("pause");
        return;
    }

    while (archi.read(reinterpret_cast<char*>(&cli), sizeof(Cliente))) {
        if (cli.getId() == idBuscado) {
            encontrado = true;
            if (cli.getEstado()) {
                cout << "Cliente encontrado:\n";
                cli.mostrar();
                cout << "Ingrese los NUEVOS datos:\n";

                int originalId = cli.getId();
                cli.cargar();
                cli.setId(originalId);

                archi.seekp(pos * sizeof(Cliente));
                archi.write(reinterpret_cast<char*>(&cli), sizeof(Cliente));

                cout << "Cliente modificado exitosamente.\n";
            } else {
                cout << "El cliente con ID " << idBuscado << " se encuentra dado de baja logica y no puede ser modificado.\n";
            }
            break;
        }
        pos++;
    }

    archi.close();

    if (!encontrado) {
        cout << "Cliente no encontrado.\n";
    }

    system("pause");
}


void eliminarCliente() {
    Cliente cli;
    int idBuscado;
    cout << "Ingrese el ID del cliente a dar de baja (eliminacion logica): ";
    cin >> idBuscado;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int pos = 0;
    bool encontrado = false;

    fstream archi("clientes.dat", ios::in | ios::out | ios::binary);
    if (!archi) {
        cout << "Error al abrir archivo de clientes para eliminacion logica.\n";
        system("pause");
        return;
    }

    while (archi.read(reinterpret_cast<char*>(&cli), sizeof(Cliente))) {
        if (cli.getId() == idBuscado) {
            encontrado = true;
            if (cli.getEstado()) {
                cli.setEstado(false);
                archi.seekp(pos * sizeof(Cliente));
                archi.write(reinterpret_cast<char*>(&cli), sizeof(Cliente));

                cout << "Cliente con ID " << idBuscado << " dado de baja logicamente.\n";
            } else {
                cout << "El cliente con ID " << idBuscado << " ya se encuentra dado de baja logica.\n";
            }
            break;
        }
        pos++;
    }

    archi.close();

    if (!encontrado) {
        cout << "Cliente no encontrado.\n";
    }

    system("pause");
}
