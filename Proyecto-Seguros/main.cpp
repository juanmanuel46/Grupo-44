#include <iostream>
#include <cstdlib>
#include <limits>
#include "Menu.h"

using namespace std;

void menuPrincipal();

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
        cout << "4 - Companias\n";
        cout << "5 - Vehiculos\n";
        cout << "6 - Proximos Vencimientos\n";
        cout << "7 - Informes\n";
        cout << "8 - Exportar a CSV\n";
        cout << "-----------------------------\n";
        cout << "0 - Salir\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(opcion) {
            case 1: menuClientes(); break;
            case 2: menuPolizas(); break;
            case 3: menuSiniestros(); break;
            case 4: menuCompanias(); break;
            case 5: menuVehiculos(); break;
            case 6: menuVencimientos(); break;
            case 7: menuInformes(); break;
            case 8: menuExportarCSV(); break;
            case 0: cout << "Saliendo del programa...\n"; break;
            default: cout << "Opcion invalida.\n"; system("pause"); break;
        }
    } while(opcion != 0);
}
