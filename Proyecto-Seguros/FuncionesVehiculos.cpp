#include <iostream>
#include <fstream>
#include <limits>
#include <cstdlib>
#include "Vehiculo.h"
#include "FuncionesVehiculos.h"

using namespace std;

void agregarVehiculo() {
    Vehiculo v;
    cout << "--- AGREGAR VEHICULO ---\n";
    v.cargar();
    if (v.guardarEnDisco()) {
        cout << "Vehiculo guardado correctamente.\n";
    } else {
        cout << "Error al guardar el vehiculo.\n";
    }
    system("pause");
}

void listarVehiculos() {
    Vehiculo v;
    int pos = 0;
    bool hayVehiculos = false;

    cout << "--- LISTADO DE VEHICULOS ---\n";
    while (v.leerDeDisco(pos)) {
         if (v.getActivo()) {
            cout << "Vehiculo #" << pos + 1 << endl;
            v.mostrar();
            hayVehiculos = true;
         }
        pos++;
    }

    if (!hayVehiculos) {
        cout << "No hay vehiculos cargados.\n";
    }

    system("pause");
}

void modificarVehiculo() {
    Vehiculo v;
    int idBuscado;
    bool encontrado = false;
    bool intentarDeNuevo = true;

    do {
        system("cls");
        cout << "--- MODIFICAR VEHICULO ---\n";
        cout << "Ingrese el ID del vehiculo a modificar (Ingrese 0 para cancelar): ";
        cin >> idBuscado;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (idBuscado == 0) {
            cout << "Modificacion de vehiculo cancelada.\n";
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
                    cout << "Ingrese los NUEVOS datos:\n";

                    int originalId = v.getIdVehiculo();
                    v.cargar();
                    v.setIdVehiculo(originalId);
                    v.setActivo(true);

                    archi.seekp(pos * sizeof(Vehiculo));
                    archi.write(reinterpret_cast<char*>(&v), sizeof(Vehiculo));

                    cout << "Vehiculo modificado exitosamente.\n";
                } else {
                    cout << "El vehiculo con ID " << idBuscado << " se encuentra dado de baja logica y no puede ser modificado.\n";
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

                        cout << "Vehiculo eliminado logicamente (dado de baja) exitosamente.\n";
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
