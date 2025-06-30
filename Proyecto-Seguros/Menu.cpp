#include <iostream>
#include <cstdlib>
#include <limits>
#include <cctype>
#include "Menu.h"
#include "Fecha.h"
#include "ArchivosClientes.h"
#include "ArchivosVehiculos.h"
#include "ArchivosSiniestro.h"
#include "ArchivosCompania.h"
#include "ArchivosPoliza.h"

using namespace std;

// Función auxiliar para mostrar dinero de forma legible
void mostrarDinero(float cantidad) {
    if (cantidad == 0) {
        cout << "0.00";
        return;
    }

    // Convertir a entero para evitar notación científica
    long long pesos = (long long)cantidad;
    int centavos = (int)((cantidad - pesos) * 100);

    cout << pesos;
    if (centavos > 0) {
        cout << "." << centavos;
    }
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
            system("pause");
        }
    } while (!salirSubmenu);
}

void menuPolizas() {
    ArchivoPoliza archivoPol;

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
            case 1:
                archivoPol.listarRegistros();
                break;
            case 2:
                archivoPol.agregarRegistro();
                break;
            case 3:
                archivoPol.modificarDatosPoliza();
                break;
            case 4:
                {
                    int numero;
                    cout << "Ingrese el numero de poliza a eliminar: ";
                    cin >> numero;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    archivoPol.bajaLogica(numero);
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
            system("pause");
        }
    } while (!salirSubmenu);
}

void menuSiniestros() {
    ArchivoSiniestro archivoSin;

    int opcion;
    bool salirSubmenu = false;
    do {
        system("cls");
        cout << "Siniestros\n";
        cout << "-----------------------------\n";
        cout << "1 - Listar Siniestros\n";
        cout << "2 - Agregar Siniestro\n";
        cout << "3 - Modificar Siniestro\n";
        cout << "4 - Eliminar Siniestro\n";
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
                    cout << "Ingrese el ID del siniestro a eliminar: ";
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
            system("pause");
        }
    } while (!salirSubmenu);
}

void menuVehiculos() {
    ArchivoVehiculo archivoVeh;

    int opcion;
    bool salirSubmenu = false;
    do {
        system("cls");
        cout << "Vehiculos\n";
        cout << "-----------------------------\n";
        cout << "1 - Listar Vehiculos\n";
        cout << "2 - Agregar Vehiculo\n";
        cout << "3 - Modificar Vehiculo\n";
        cout << "4 - Eliminar Vehiculo\n";
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
                    cout << "Ingrese el ID del vehiculo a eliminar: ";
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
            system("pause");
        }
    } while (!salirSubmenu);
}

void menuCompanias() {
    ArchivoCompania archivoCom;
    int opcion;
    bool salirSubmenu = false;
    do {
        system("cls");
        cout << "Companias\n";
        cout << "-----------------------------\n";
        cout << "1 - Listar Companias\n";
        cout << "2 - Agregar Compania\n";
        cout << "3 - Modificar Compania\n";
        cout << "4 - Eliminar Compania\n";
        cout << "----------------------------\n";
        cout << "0 - Volver al menu principal\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

         switch(opcion) {
            case 1:
                archivoCom.listarRegistros();
                break;
            case 2:
                archivoCom.agregarRegistro();
                break;
            case 3:
                archivoCom.modificarDatosCompania();
                break;
            case 4:
                {
                    int id;
                    cout << "Ingrese el ID de la compania a eliminar: ";
                    cin >> id;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    archivoCom.bajaLogica(id);
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
            system("pause");
        }
    } while (!salirSubmenu);
}

void menuVencimientos() {
    ArchivoPoliza archivoPol;
    archivoPol.listarProximosVencimientos(30);
}

void menuInformes() {
    ArchivoPoliza archivoPol;
    int opcion;
    bool salirSubmenu = false;
    do {
        system("cls");
        cout << "-----------------------------------------\n";
        cout << "             Informes\n";
        cout << "-----------------------------------------\n";
        cout << "1 - Listado de polizas por siniestros\n";
        cout << "2 - Recaudacion de ventas anuales\n";
        cout << "3 - Recaudacion de ventas mensuales\n";
        cout << "4 - Recaudacion de ventas semanales\n";
        cout << "5 - Recaudacion de ventas personalizada\n";
        cout << "-----------------------------------------\n";
        cout << "0 - Volver al menu principal\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(opcion) {
            case 1:
                archivoPol.listarPolizasConSiniestros();
                break;
            case 2:
                {
                    int anio;
                    cout << "Ingrese el anio para la recaudacion: ";
                    cin >> anio;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    float recaudacion = archivoPol.calcularRecaudacionAnual(anio);
                    system("cls");
                    cout << "-----------------------------------------" << endl;
                    cout << "    RECAUDACION ANUAL " << anio << endl;
                    cout << "-----------------------------------------" << endl;
                    cout << "Total recaudado: $";
                    mostrarDinero(recaudacion);
                    cout << endl;
                    cout << "-----------------------------------------" << endl;
                    system("pause");
                }
                break;
            case 3:
                {
                    int mes, anio;
                    cout << "Ingrese el mes (1-12): ";
                    cin >> mes;
                    cout << "Ingrese el anio: ";
                    cin >> anio;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    if (mes >= 1 && mes <= 12) {
                        float recaudacion = archivoPol.calcularRecaudacionMensual(mes, anio);
                        system("cls");
                        cout << "-----------------------------------------" << endl;
                        cout << "    RECAUDACION MENSUAL " << mes << "/" << anio << endl;
                        cout << "-----------------------------------------" << endl;
                        cout << "Total recaudado: $";
                        mostrarDinero(recaudacion);
                        cout << endl;
                        cout << "-----------------------------------------" << endl;
                    } else {
                        cout << "Mes invalido. Debe estar entre 1 y 12." << endl;
                    }
                    system("pause");
                }
                break;
            case 4:
                {
                    int semana, anio;
                    cout << "Ingrese la semana (1-52): ";
                    cin >> semana;
                    cout << "Ingrese el anio: ";
                    cin >> anio;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    if (semana >= 1 && semana <= 52) {
                        float recaudacion = archivoPol.calcularRecaudacionSemanal(semana, anio);
                        system("cls");
                        cout << "-----------------------------------------" << endl;
                        cout << "    RECAUDACION SEMANAL " << semana << "/" << anio << endl;
                        cout << "-----------------------------------------" << endl;
                        cout << "Total recaudado: $";
                        mostrarDinero(recaudacion);
                        cout << endl;
                        cout << "-----------------------------------------" << endl;
                    } else {
                        cout << "Semana invalida. Debe estar entre 1 y 52." << endl;
                    }
                    system("pause");
                }
                break;
            case 5:
                {
                    Fecha fechaInicio, fechaFin;
                    cout << "Ingrese la fecha de inicio:" << endl;
                    fechaInicio.cargar();
                    cout << "Ingrese la fecha de fin:" << endl;
                    fechaFin.cargar();

                    float recaudacion = archivoPol.calcularRecaudacionPersonalizada(fechaInicio, fechaFin);
                    system("cls");
                    cout << "-----------------------------------------" << endl;
                    cout << "    RECAUDACION PERSONALIZADA" << endl;
                    cout << "    Desde: " << fechaInicio.toString() << endl;
                    cout << "    Hasta: " << fechaFin.toString() << endl;
                    cout << "-----------------------------------------" << endl;
                    cout << "Total recaudado: $";
                    mostrarDinero(recaudacion);
                    cout << endl;
                    cout << "-----------------------------------------" << endl;
                    system("pause");
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
        if (opcion >= 1 && opcion <= 5) {
            system("pause");
        }
    } while (!salirSubmenu);
}
