#include <iostream>
#include <cstdlib>
#include <limits>
#include <cctype>
#include "Menu.h"
#include "ArchivosClientes.h"
#include "ArchivosVehiculos.h"
#include "ArchivosSiniestro.h"

using namespace std;

void menuPrincipal();
void menuClientes();
void menuPolizas();
void menuSiniestros();
void menuVehiculos();
void menuVencimientos();
void menuInformes();

bool preguntarVolverMenuPrincipal() {
    char opcionChar;
    do {
        cout << "\n Volver al menu principal? (S/N): ";
        cin >> opcionChar;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        opcionChar = toupper(opcionChar);

        if (opcionChar == 'S') {
            return true;
        } else if (opcionChar == 'N') {
            return false;
        } else {
            cout << "Opcion invalida. Por favor, ingrese 'S' para Si o 'N' para No.\n";
        }
    } while (true);
}

int main() {
    menuPrincipal();
    return 0;
}

void menuPrincipal() {
    int opcion;
    do {
        system("cls");
        cout << "Menu Principal\n";
        cout << "-----------------------------\n";
        cout << "1 - Clientes\n";
        cout << "2 - Polizas\n";
        cout << "3 - Siniestros\n";
        cout << "4 - Vehiculos\n";
        cout << "5 - Proximos Vencimientos\n";
        cout << "6 - Informes\n";
        cout << "-----------------------------\n";
        cout << "0 - Salir\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(opcion) {
            case 1: menuClientes(); break;
            case 2: menuPolizas(); break;
            case 3: menuSiniestros(); break;
            case 4: menuVehiculos(); break;
            case 5: menuVencimientos(); break;
            case 6: menuInformes(); break;
            case 0: cout << "Saliendo del programa...\n"; break;
            default: cout << "Opcion invalida.\n"; system("pause"); break;
        }
    } while(opcion != 0);
}

void menuClientes() {

    ArchivoCliente archivoCli; 

    int opcion;
    bool salirSubmenu = false;
    do {
        system("cls");
        cout << "Clientes\n";
        cout << "-----------------------------\n";
        cout << "1 - Listar Clientes\n";
        cout << "2 - Agregar Cliente\n";
        cout << "3 - Modificar Cliente\n";
        cout << "4 - Eliminar Cliente\n";
        cout << "----------------------------\n";
        cout << "0 - Volver al menu principal\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

         switch(opcion) {
            case 1:
                archivoCli.listarRegistros(); 
                break;
            case 2:
                archivoCli.agregarRegistro(); 
                break;
            case 3:
                archivoCli.modificarDatosCliente(); 
                break;
            case 4:
                { 
                    int id;
                    cout << "Ingrese el ID del cliente a eliminar: ";
                    cin >> id;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    archivoCli.bajaLogica(id); 
                }
                break;
            case 0:
                salirSubmenu = true;
                break;
            default:
                cout << "Opcion invalida.\n";
                system("pause");
                break;
        }
        if (opcion >= 1 && opcion <= 4) {
            if (preguntarVolverMenuPrincipal()) {
                salirSubmenu = true;}
        }
    } while (!salirSubmenu);
}

void menuPolizas() {
    int opcion;
    bool salirSubmenu = false;
    do {
        system("cls");
        cout << "Polizas\n";
        cout << "-----------------------------\n";
        cout << "1 - Listar Poliza\n";
        cout << "2 - Agregar Poliza\n";
        cout << "3 - Modificar Poliza\n";
        cout << "4 - Eliminar Poliza\n";
        cout << "----------------------------\n";
        cout << "0 - Volver al menu principal\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(opcion) {
            case 1: cout << "Listado de polizas...\n"; system("pause"); break;
            case 2: cout << "Agregar poliza...\n"; system("pause"); break;
            case 3: cout << "Modificar poliza...\n"; system("pause"); break;
            case 4: cout << "Eliminar poliza...\n"; system("pause"); break;
            case 0:
                salirSubmenu = true;
                break;
            default:
                cout << "Opcion invalida.\n";
                system("pause");
                break;
        }

        if (opcion >= 1 && opcion <= 4) {
            if (preguntarVolverMenuPrincipal()) {
                salirSubmenu = true;
            }
        }
    } while (!salirSubmenu);
}

void menuSiniestros() {

    ArchivoSiniestro archivoSin; 

    int opcion;
    bool salirSubmenu = false;
    do {
        system("cls");
        cout << "Clientes\n";
        cout << "-----------------------------\n";
        cout << "1 - Listar Clientes\n";
        cout << "2 - Agregar Cliente\n";
        cout << "3 - Modificar Cliente\n";
        cout << "4 - Eliminar Cliente\n";
        cout << "----------------------------\n";
        cout << "0 - Volver al menu principal\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

         switch(opcion) {
            case 1:
                archivoSin.listarRegistros(); 
                break;
            case 2:
                archivoSin.agregarRegistro(); 
                break;
            case 3:
                archivoSin.modificarDatosSiniestro(); 
                break;
            case 4:
                { 
                    int id;
                    cout << "Ingrese el ID del cliente a eliminar: ";
                    cin >> id;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    archivoSin.bajaLogica(); 
                }
                break;
            case 0:
                salirSubmenu = true;
                break;
            default:
                cout << "Opcion invalida.\n";
                system("pause");
                break;
        }
        if (opcion >= 1 && opcion <= 4) {
            if (preguntarVolverMenuPrincipal()) {
                salirSubmenu = true;}
        }
    } while (!salirSubmenu);
}

void menuSiniestros() {

    ArchivoVehiculo archivoVeh; 

    int opcion;
    bool salirSubmenu = false;
    do {
        system("cls");
        cout << "Clientes\n";
        cout << "-----------------------------\n";
        cout << "1 - Listar Clientes\n";
        cout << "2 - Agregar Cliente\n";
        cout << "3 - Modificar Cliente\n";
        cout << "4 - Eliminar Cliente\n";
        cout << "----------------------------\n";
        cout << "0 - Volver al menu principal\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

         switch(opcion) {
            case 1:
                archivoVeh.listarRegistros(); 
                break;
            case 2:
                archivoVeh.agregarRegistro(); 
                break;
            case 3:
                archivoVeh.modificarDatosVehiculo(); 
                break;
            case 4:
                { 
                    int id;
                    cout << "Ingrese el ID del cliente a eliminar: ";
                    cin >> id;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    archivoVeh.bajaLogica(); 
                }
                break;
            case 0:
                salirSubmenu = true;
                break;
            default:
                cout << "Opcion invalida.\n";
                system("pause");
                break;
        }
        if (opcion >= 1 && opcion <= 4) {
            if (preguntarVolverMenuPrincipal()) {
                salirSubmenu = true;}
        }
    } while (!salirSubmenu);
}

void menuVencimientos() {
    system("cls");
    cout << "Proximos Vencimientos\n";
    cout << "-----------------------------\n";
    cout << "Tabla con datos de poliza!\n";
    cout << "-----------------------------\n";
    system("pause");
    preguntarVolverMenuPrincipal();
}

void menuInformes() {
    int opcion;
    bool salirSubmenu = false;
    do {
        system("cls");
        cout << "Informes\n";
        cout << "---------------------------\n";
        cout << "1 - Listado de polizas por siniestros\n";
        cout << "2 - Recaudacion de ventas Anuales\n";
        cout << "3 - Recaudacion de ventas Mensuales\n";
        cout << "4 - Recaudacion de ventas Semanales\n";
        cout << "5 - Recaudacion de ventas Personalizado\n";
        cout << "----------------------------\n";
        cout << "0 - Volver al menu principal\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(opcion) {
            case 1: cout << "Listado de polizas por siniestros...\n"; system("pause"); break;
            case 2: cout << "Recaudacion anual...\n"; system("pause"); break;
            case 3: cout << "Recaudacion mensual...\n"; system("pause"); break;
            case 4: cout << "Recaudacion semanal...\n"; system("pause"); break;
            case 5: cout << "Recaudacion personalizada...\n"; system("pause"); break;
            case 0:
                salirSubmenu = true;
                break;
            default:
                cout << "Opcion invalida.\n";
                system("pause");
                break;
        }
        if (opcion >= 1 && opcion <= 5) {
            if (preguntarVolverMenuPrincipal()) {
                salirSubmenu = true;
            }
        }
    } while (!salirSubmenu);
}
