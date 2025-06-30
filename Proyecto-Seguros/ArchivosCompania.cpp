#include "ArchivosCompania.h"
#include "Compania.h"
#include <iostream>
#include <cstring>

using namespace std;

int ArchivoCompania::buscarCompania(int idCompania) {
    Compania obj;
    FILE *pCompania;
    pCompania = fopen(nombre, "rb");

    if (pCompania == nullptr) {
        return -2; 
    }

    int pos = 0;
    while (fread(&obj, tamanioRegistro, 1, pCompania) == 1) {
        if (obj.getId() == idCompania) {
            fclose(pCompania);
            return pos;
        }
        pos++;
    }

    fclose(pCompania);
    return -1; 
}

int ArchivoCompania::agregarRegistro() {
    Compania nuevaCompania;
    cout << "--- AGREGAR COMPANIA ---" << endl;

    nuevaCompania.cargarId();

    int resultado = buscarCompania(nuevaCompania.getId());
    if (resultado >= 0) {
        cout << "Error: ya existe una compania con el ID " << nuevaCompania.getId() << "." << endl;
        system("pause");
        return -2; 
    }
    
    nuevaCompania.cargarDatos(); 

    FILE *pCompania;
    pCompania = fopen(nombre, "ab");
    if (pCompania == nullptr) {
        cout << "No se pudo abrir el archivo para escribir." << endl;
        return -1; 
    }

    int escribio = fwrite(&nuevaCompania, tamanioRegistro, 1, pCompania);
    fclose(pCompania);

    if (escribio == 1) {
        cout << "\nCompania guardada con exito.\n" << endl;
    }
    system("pause");
    return escribio;
}

bool ArchivoCompania::listarRegistros() {
    Compania obj;
    FILE *pCompania;
    pCompania = fopen(nombre, "rb");

    if (pCompania == nullptr) {
        cout << "No se pudo abrir el archivo de companias." << endl;
        cout << "No hay companias cargadas." << endl;
        system("pause");
        return false;
    }
    
    bool hayCompaniasActivas = false;
    system("cls");
    cout << "LISTADO DE COMPANIAS" << endl;
    cout << "--------------------------------" << endl;

    while (fread(&obj, tamanioRegistro, 1, pCompania) == 1) {
        if (obj.getActivo()) {
            obj.mostrar();
            hayCompaniasActivas = true;
        }
    }

    fclose(pCompania);

    if (!hayCompaniasActivas) {
        cout << "No hay companias cargadas para mostrar." << endl;
    }
    return true;
}

Compania ArchivoCompania::leerRegistro(int pos) {
    Compania obj;
    FILE *pCompania;
    pCompania = fopen(nombre, "rb");
    
    // Inicialización por si falla la apertura o lectura
    obj.setId(-1); 

    if (pCompania == nullptr) {
        return obj;
    }

    fseek(pCompania, pos * tamanioRegistro, SEEK_SET);
    fread(&obj, tamanioRegistro, 1, pCompania);
    fclose(pCompania);

    return obj;
}

bool ArchivoCompania::modificarRegistro(Compania reg, int pos) {
    FILE *pCompania;
    pCompania = fopen(nombre, "rb+"); // rb+ para leer y escribir
    if (pCompania == nullptr) {
        return false;
    }

    fseek(pCompania, pos * tamanioRegistro, SEEK_SET);
    int escribio = fwrite(&reg, tamanioRegistro, 1, pCompania);
    fclose(pCompania);

    return escribio == 1;
}

bool ArchivoCompania::modificarDatosCompania() {
    int idBuscado;
    system("cls");
    cout << "--- MODIFICAR COMPANIA ---" << endl;
    cout << "Ingrese el ID de la compania a modificar: ";
    cin >> idBuscado;
    cin.ignore(); // Limpiar el buffer de entrada

    int pos = buscarCompania(idBuscado);

    if (pos == -1) {
        cout << "Compania con ID " << idBuscado << " no encontrada." << endl;
        system("pause");
        return false;
    }
    if (pos == -2) {
        cout << "Error al abrir el archivo de companias." << endl;
        system("pause");
        return false;
    }

    Compania com = leerRegistro(pos);

    if (!com.getActivo()) {
        cout << "La compania con ID " << idBuscado << " esta dada de baja y no puede ser modificada." << endl;
        system("pause");
        return false;
    }

    cout << "\nCompania encontrada:" << endl;
    com.mostrar();
    cout << "\nIngrese los NUEVOS datos:" << endl;
    

    com.cargarDatos(); // Asumo que carga todos los datos excepto el ID y estado.

    if (modificarRegistro(com, pos)) {
        cout << "\nCompania modificada exitosamente." << endl;
    } else {
        cout << "\nError al modificar la compania." << endl;
    }
    system("pause");
    return true;
}

bool ArchivoCompania::bajaLogica(int idCompania) {
    int pos = buscarCompania(idCompania);
    if (pos < 0) {
        cout << "No se encontro la compania con ID " << idCompania << " o hubo un error." << endl;
        system("pause");
        return false;
    }
    
    Compania reg = leerRegistro(pos);
    
    if(!reg.getActivo()){
        cout << "La compania con ID " << idCompania << " ya se encuentra dada de baja." << endl;
        system("pause");
        return false;
    }

    cout << "Compania encontrada:" << endl;
    reg.mostrar();
    char confirmacion;
    cout << "Esta seguro de eliminar esta compania (S/N)? ";
    cin >> confirmacion;
    cin.ignore(); // Limpiar el buffer de entrada
    confirmacion = toupper(confirmacion);

    if(confirmacion == 'S'){
        reg.setActivo(false);
        if (modificarRegistro(reg, pos)) {
            cout << "Compania eliminada exitosamente." << endl;
        } else {
            cout << "Error al intentar dar de baja a la compania." << endl;
        }
    } else {
        cout << "Eliminacion cancelada por el usuario." << endl;
    }

    system("pause");
    return true;
}

int ArchivoCompania::contarRegistros() {
    FILE *pCompania;
    pCompania = fopen(nombre, "rb");

    if (pCompania == nullptr) {
        return -1;
    }

    fseek(pCompania, 0, SEEK_END);
    int tam = ftell(pCompania);
    fclose(pCompania);

    return tam / tamanioRegistro;
}



