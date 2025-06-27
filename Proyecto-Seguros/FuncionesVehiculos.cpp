#include <iostream>
#include <fstream>
#include <limits>
#include <cstdlib>
#include "Vehiculo.h"
#include "FuncionesVehiculos.h"

using namespace std;

void agregarVehiculo() {
    Vehiculo nuevoVehiculo;
    cout << "--- AGREGAR VEHICULO ---\n";

    nuevoVehiculo.cargarId();

    Vehiculo v;
    ifstream archivo("vehiculos.dat", ios::binary);
    if (archivo) {
        while (archivo.read(reinterpret_cast<char*>(&v), sizeof(Vehiculo))) {
            if (v.getIdVehiculo() == nuevoVehiculo.getIdVehiculo()) {
                cout << "Error: ya existe un vehiculo con el ID " << v.getIdVehiculo() << ".\n";
                archivo.close();
                system("pause");
                return;
            }
        }
        archivo.close();
    }

    nuevoVehiculo.cargarDatos();

    ofstream archi("vehiculos.dat", ios::app | ios::binary);
    if (!archi) {
        cout << "No se pudo abrir el archivo para escribir.\n";
        system("pause");
        return;
    }

    archi.write(reinterpret_cast<char*>(&nuevoVehiculo), sizeof(Vehiculo));
    archi.close();

    cout << "\nVehiculo guardado con éxito.\n\n";
    system("pause");
}

void listarVehiculos() {
    Vehiculo v;
    int pos = 0;
    bool hayVehiculosActivos = false;

    system("cls");
    cout << "LISTADO DE VEHICULOS\n";
    cout << "--------------------------------\n";

    ifstream archi("vehiculos.dat", ios::binary);
    if (!archi.is_open()) {
        cout << "No se pudo abrir el archivo para lectura.\n";
        cout << "No hay vehiculos cargados.\n";
        system("pause");
        return;
    }

    while (archi.read(reinterpret_cast<char*>(&v), sizeof(Vehiculo))) {
        if (v.getActivo()) {
            cout << "Vehiculo #" << pos + 1 << endl;
            v.mostrar();
            hayVehiculosActivos = true;
        }
        pos++;
    }

    archi.close();

    if (!hayVehiculosActivos) {
        cout << "No hay vehiculos activos cargados para mostrar.\n";
    }
}

void modificarVehiculo() {
    Vehiculo v;
    string entrada;
    bool encontrado = false;
    bool intentarDeNuevo = true;

    while (intentarDeNuevo) {
        system("cls");
        cout << "--- MODIFICAR VEHICULO ---\n";
        cout << "Ingrese el ID del vehiculo a modificar (Ingrese S para cancelar): ";
        getline(cin, entrada);

        if (entrada == "S" || entrada == "s") {
            cout << "Modificación de vehiculo cancelada.\n";
            intentarDeNuevo = false;
            break;
        }

        int idBuscado;
        try {
            idBuscado = stoi(entrada);
        } catch (...) {
            cout << "Entrada invalida. Debe ingresar un numero o 'S' para salir.\n";
            system("pause");
            continue;
        }

        fstream archi("vehiculos.dat", ios::in | ios::out | ios::binary);
        if (!archi) {
            cout << "Error al abrir archivo de vehiculos. Es posible que no exista.\n";
            system("pause");
            intentarDeNuevo = false;
            break;
        }

        int pos = 0;
        encontrado = false;

        while (archi.read(reinterpret_cast<char*>(&v), sizeof(Vehiculo))) {
            if (v.getIdVehiculo() == idBuscado) {
                encontrado = true;
                if (v.getActivo()) {
                    cout << "\nVehiculo encontrado:\n";
                    v.mostrar();
                    cout << "\nIngrese los NUEVOS datos:\n";

                    int originalId = v.getIdVehiculo();
                    v.cargar();
                    v.setIdVehiculo(originalId);
                    v.setActivo(true);

                    archi.seekp(pos * sizeof(Vehiculo));
                    archi.write(reinterpret_cast<char*>(&v), sizeof(Vehiculo));

                    cout << "\nVehiculo modificado exitosamente.\n";
                } else {
                    cout << "El vehiculo con ID " << idBuscado << " esta dado de baja y no puede ser modificado.\n";
                }
                system("pause");
                break;
            }
            pos++;
        }
        archi.close();

        if (!encontrado) {
            cout << "Vehiculo con ID " << idBuscado << " no encontrado. Intente de nuevo.\n";
            system("pause");
        } else {
            intentarDeNuevo = false;
        }
    }
}

void eliminarVehiculo() {
    Vehiculo v;
    int idBuscado;
    bool encontrado = false;
    bool intentarDeNuevo = true;

    do {
        system("cls");
        cout << "--- ELIMINAR VEHICULO (Baja Logica) ---\n";
        cout << "Ingrese el ID del vehiculo a eliminar (Ingrese 0 para cancelar): ";
        cin >> idBuscado;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (idBuscado == 0) {
            cout << "Eliminacion de vehiculo cancelada.\n";
            intentarDeNuevo = false;
            system("pause");
            break;
        }

        fstream archi("vehiculos.dat", ios::in | ios::out | ios::binary);
        if (!archi) {
            cout << "Error al abrir archivo de vehiculos. Es posible que no exista.\n";
            system("pause");
            intentarDeNuevo = false;
            break;
        }

        int pos = 0;
        encontrado = false;

        while (archi.read(reinterpret_cast<char*>(&v), sizeof(Vehiculo))) {
            if (v.getIdVehiculo() == idBuscado) {
                encontrado = true;
                if (v.getActivo()) {
                    cout << "Vehiculo encontrado:\n";
                    v.mostrar();
                    char confirmacion;
                    cout << "¿Esta seguro de eliminar este vehiculo (S/N)? ";
                    cin >> confirmacion;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    confirmacion = toupper(confirmacion);

                    if (confirmacion == 'S') {
                        v.setActivo(false);

                        archi.seekp(pos * sizeof(Vehiculo));
                        archi.write(reinterpret_cast<char*>(&v), sizeof(Vehiculo));

                        cout << "Vehiculo eliminado exitosamente.\n";
                    } else {
                        cout << "Eliminacion cancelada por el usuario.\n";
                    }
                } else {
                    cout << "El vehiculo con ID " << idBuscado << " ya se encuentra dado de baja logica.\n";
                }
                system("pause");
                break;
            }
            pos++;
        }
        archi.close();

        if (!encontrado) {
            cout << "Vehiculo con ID " << idBuscado << " no encontrado. Intente de nuevo.\n";
            system("pause");
        } else {
            intentarDeNuevo = false;
        }

    } while (intentarDeNuevo);
}
