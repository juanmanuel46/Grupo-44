#include "funcionesSiniestro.h"
#include "siniestro.h"
#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

void agregarSiniestro() {
    Siniestro nuevoSiniestro;
    cout << "--- AGREGAR SINIESTRO ---\n";

    nuevoSiniestro.cargarId();

    Siniestro s;
    ifstream archivo("siniestros.dat", ios::binary);
    if (archivo) {
        while (archivo.read(reinterpret_cast<char*>(&s), sizeof(Siniestro))) {
            if (s.getIdSiniestro() == nuevoSiniestro.getIdSiniestro()) {
                cout << "Error: ya existe un siniestro con el ID " << s.getIdSiniestro() << ".\n";
                archivo.close();
                system("pause");
                return;
            }
        }
        archivo.close();
    }

    nuevoSiniestro.cargarDatos();

    ofstream archi("siniestros.dat", ios::app | ios::binary);
    if (!archi) {
        cout << "No se pudo abrir el archivo para escribir.\n";
        system("pause");
        return;
    }

    archi.write(reinterpret_cast<char*>(&nuevoSiniestro), sizeof(Siniestro));
    archi.close();

    cout << "\nSiniestro guardado con éxito.\n\n";
    system("pause");
}

void listarSiniestro() {
    Siniestro s;
    int pos = 0;
    bool haySiniestrosActivos = false;

    system("cls");
    cout << "LISTADO DE SINIESTROS\n";
    cout << "--------------------------------\n";

    ifstream archi("siniestros.dat", ios::binary);
    if (!archi.is_open()) {
        cout << "No se pudo abrir el archivo para lectura.\n";
        cout << "No hay siniestros cargados.\n";
        system("pause");
        return;
    }

    while (archi.read(reinterpret_cast<char*>(&s), sizeof(Siniestro))) {
        if (s.getActivo()) {
            cout << "Siniestro #" << pos + 1 << endl;
            s.mostrar();
            haySiniestrosActivos = true;
        }
        pos++;
    }

    archi.close();

    if (!haySiniestrosActivos) {
        cout << "No hay siniestros cargados para mostrar.\n";
    }
}

void modificarSiniestro() {
    Siniestro s;
    string entrada;
    bool encontrado = false;
    bool intentarDeNuevo = true;

    while (intentarDeNuevo) {
        system("cls");
        cout << "--- MODIFICAR SINIESTRO ---\n";
        cout << "Ingrese el ID del siniestro a modificar (Ingrese S para cancelar): ";
        getline(cin, entrada);

        if (entrada == "S" || entrada == "s") {
            cout << "Modificación de siniestro cancelada.\n";
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

        fstream archi("siniestros.dat", ios::in | ios::out | ios::binary);
        if (!archi) {
            cout << "Error al abrir archivo de siniestros.\n";
            system("pause");
            intentarDeNuevo = false;
            break;
        }

        int pos = 0;
        encontrado = false;

        while (archi.read(reinterpret_cast<char*>(&s), sizeof(Siniestro))) {
            if (s.getIdSiniestro() == idBuscado) {
                encontrado = true;

                cout << "\nSiniestro encontrado:\n";
                s.mostrar();

                if (s.getActivo()) {
                    cout << "\nIngrese los NUEVOS datos:\n";

                    int originalId = s.getIdSiniestro();
                    s.cargar();
                    s.setIdSiniestro(originalId);

                    archi.seekp(pos * sizeof(Siniestro));
                    archi.write(reinterpret_cast<char*>(&s), sizeof(Siniestro));

                    cout << "\nSiniestro modificado exitosamente.\n";
                } else {
                    cout << "El siniestro con ID " << idBuscado << " está dado de baja y no puede ser modificado.\n";
                }
                system("pause");
                break;
            }
            pos++;
        }
        archi.close();

        if (!encontrado) {
            cout << "Siniestro con ID " << idBuscado << " no encontrado. Intente de nuevo.\n";
            system("pause");
        } else {
            intentarDeNuevo = false;
        }
    }
}

void eliminarSiniestro() {
    Siniestro s;
    int idBuscado;
    bool encontrado = false;
    bool intentarDeNuevo = true;

    do {
        system("cls");
        cout << "--- ELIMINAR SINIESTRO (Baja Logica) ---\n";
        cout << "Ingrese el ID del siniestro a eliminar (Ingrese 0 para cancelar): ";
        cin >> idBuscado;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (idBuscado == 0) {
            cout << "Eliminacion de siniestro cancelada.\n";
            intentarDeNuevo = false;
            system("pause");
            break;
        }

        fstream archi("siniestros.dat", ios::in | ios::out | ios::binary);
        if (!archi) {
            cout << "Error al abrir archivo de siniestros. Es posible que no exista.\n";
            system("pause");
            intentarDeNuevo = false;
            break;
        }

        int pos = 0;
        encontrado = false;

        while (archi.read(reinterpret_cast<char*>(&s), sizeof(Siniestro))) {
            if (s.getIdSiniestro() == idBuscado) {
                encontrado = true;

                if (s.getActivo()) {
                    cout << "Siniestro encontrado:\n";
                    s.mostrar();
                    char confirmacion;
                    cout << "¿Está seguro de eliminar este siniestro (S/N)? ";
                    cin >> confirmacion;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    confirmacion = toupper(confirmacion);

                    if (confirmacion == 'S') {
                        s.setActivo(false);
                        archi.seekp(pos * sizeof(Siniestro));
                        archi.write(reinterpret_cast<char*>(&s), sizeof(Siniestro));

                        cout << "Siniestro eliminado exitosamente.\n";
                    } else {
                        cout << "Eliminacion cancelada por el usuario.\n";
                    }
                } else {
                    cout << "El siniestro con ID " << idBuscado << " ya se encuentra dado de baja logica.\n";
                }

                system("pause");
                break;
            }
            pos++;
        }

        archi.close();

        if (!encontrado) {
            cout << "Siniestro con ID " << idBuscado << " no encontrado. Intente de nuevo.\n";
            system("pause");
        } else {
            intentarDeNuevo = false;
        }

    } while (intentarDeNuevo);
}

