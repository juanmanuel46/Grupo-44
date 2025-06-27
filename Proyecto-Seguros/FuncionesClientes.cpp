#include <iostream>
#include <fstream>
#include "Cliente.h"
#include <cstdlib>
#include <limits>

using namespace std;

void agregarCliente() {
    Cliente nuevoCliente;
    cout << "--- AGREGAR CLIENTE ---\n";

    nuevoCliente.cargarId();

    Cliente c;
    ifstream archivo("clientes.dat", ios::binary);
    if (archivo) {
        while (archivo.read(reinterpret_cast<char*>(&c), sizeof(Cliente))) {
            if (c.getIdCliente() == nuevoCliente.getIdCliente()) {
                cout << "Error: ya existe un cliente con el ID " << c.getIdCliente() << ".\n";
                archivo.close();
                system("pause");
                return;
            }
        }
        archivo.close();
    }

    nuevoCliente.cargarDatos();

    ofstream archi("clientes.dat", ios::app | ios::binary);
    if (!archi) {
        cout << "No se pudo abrir el archivo para escribir.\n";
        system("pause");
        return;
    }

    archi.write(reinterpret_cast<char*>(&nuevoCliente), sizeof(Cliente));
    archi.close();

    cout << "\nCliente guardado con éxito.\n\n";
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
        if (cli.getActivo()) {
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
}

void modificarCliente() {
    Cliente cli;
    string entrada;
    bool encontrado = false;
    bool intentarDeNuevo = true;

    while (intentarDeNuevo) {
        system("cls");
        cout << "--- MODIFICAR CLIENTE ---\n";
        cout << "Ingrese el ID del cliente a modificar (Ingrese S para cancelar): ";
        getline(cin, entrada);

        if (entrada == "S" || entrada == "s") {
            cout << "Modificación de cliente cancelada.\n";
            intentarDeNuevo = false;
            break;
        }

        int idBuscado;
        try {
            idBuscado = stoi(entrada);
        } catch (...) {
            cout << "Entrada inválida. Debe ingresar un número o 'S' para salir.\n";
            system("pause");
            continue;
        }

        fstream archi("clientes.dat", ios::in | ios::out | ios::binary);
        if (!archi) {
            cout << "Error al abrir archivo de clientes.\n";
            system("pause");
            intentarDeNuevo = false;
            break;
        }

        int pos = 0;
        encontrado = false;

        while (archi.read(reinterpret_cast<char*>(&cli), sizeof(Cliente))) {
            if (cli.getIdCliente() == idBuscado) {
                encontrado = true;
                if (cli.getActivo()) {
                    cout << "\nCliente encontrado:\n";
                    cli.mostrar();
                    cout << "\nIngrese los NUEVOS datos:\n";

                    int originalId = cli.getIdCliente();
                    cli.cargar();
                    cli.setIdCliente(originalId);

                    archi.seekp(pos * sizeof(Cliente));
                    archi.write(reinterpret_cast<char*>(&cli), sizeof(Cliente));

                    cout << "\nCliente modificado exitosamente.\n";
                } else {
                    cout << "El cliente con ID " << idBuscado << " está dado de baja y no puede ser modificado.\n";
                }
                system("pause");
                break;
            }
            pos++;
        }
        archi.close();

        if (!encontrado) {
            cout << "Cliente con ID " << idBuscado << " no encontrado. Intente de nuevo.\n";
            system("pause");
        } else {
            intentarDeNuevo = false;
        }
    }
}

void eliminarCliente() {
    Cliente cli;
    int idBuscado;
    bool encontrado = false;
    bool intentarDeNuevo = true;

    do {
        system("cls");
        cout << "--- ELIMINAR CLIENTE (Baja Logica) ---\n";
        cout << "Ingrese el ID del cliente a eliminar (Ingrese 0 para cancelar): ";
        cin >> idBuscado;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (idBuscado == 0) {
            cout << "Eliminacion de cliente cancelada.\n";
            intentarDeNuevo = false;
            system("pause");
            break;
        }

        fstream archi("clientes.dat", ios::in | ios::out | ios::binary);
        if (!archi) {
            cout << "Error al abrir archivo de clientes. Es posible que no exista.\n";
            system("pause");
            intentarDeNuevo = false;
            break;
        }

        int pos = 0;
        encontrado = false;

        while (archi.read(reinterpret_cast<char*>(&cli), sizeof(Cliente))) {
            if (cli.getIdCliente() == idBuscado) {
                encontrado = true;
                if (cli.getActivo()) {
                    cout << "Cliente encontrado:\n";
                    cli.mostrar();
                    char confirmacion;
                    cout << "¿Esta seguro de eliminar este cliente (S/N)? ";
                    cin >> confirmacion;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    confirmacion = toupper(confirmacion);

                    if (confirmacion == 'S') {
                        cli.setActivo(false);
                        archi.seekp(pos * sizeof(Cliente));
                        archi.write(reinterpret_cast<char*>(&cli), sizeof(Cliente));

                        cout << "Cliente eliminado exitosamente.\n";
                    } else {
                        cout << "Eliminacion cancelada por el usuario.\n";
                    }
                } else {
                    cout << "El cliente con ID " << idBuscado << " ya se encuentra dado de baja logica.\n";
                }
                system("pause");
                break;
            }
            pos++;
        }

        archi.close();

        if (!encontrado) {
            cout << "Cliente con ID " << idBuscado << " no encontrado. Intente de nuevo.\n";
            system("pause");
        } else {
            intentarDeNuevo = false;
        }

    } while (intentarDeNuevo);
}

