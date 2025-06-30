#include "ArchivosPoliza.h"
#include "Poliza.h"
#include "ArchivosSiniestro.h"
#include <iostream>
#include <cstring>
#include <ctime>
#include <limits>

using namespace std;

int ArchivoPoliza::buscarPoliza(int numeroPoliza) {
    Poliza obj;
    FILE *pPoliza;
    pPoliza = fopen(nombre, "rb");

    if (pPoliza == nullptr) {
        return -2;
    }

    int pos = 0;
    while (fread(&obj, tamanioRegistro, 1, pPoliza) == 1) {
        if (obj.getNumeroPoliza() == numeroPoliza) {
            fclose(pPoliza);
            return pos;
        }
        pos++;
    }

    fclose(pPoliza);
    return -1;
}

int ArchivoPoliza::agregarRegistro() {
    Poliza nuevaPoliza;
    cout << "--- AGREGAR POLIZA ---" << endl;

    nuevaPoliza.cargarId();

    int resultado = buscarPoliza(nuevaPoliza.getNumeroPoliza());
    if (resultado >= 0) {
        cout << "Error: ya existe una poliza con el numero " << nuevaPoliza.getNumeroPoliza() << "." << endl;
        system("pause");
        return -2;
    }

    nuevaPoliza.cargarDatos();

    FILE *pPoliza;
    pPoliza = fopen(nombre, "ab");
    if (pPoliza == nullptr) {
        cout << "No se pudo abrir el archivo para escribir." << endl;
        return -1;
    }

    int escribio = fwrite(&nuevaPoliza, tamanioRegistro, 1, pPoliza);
    fclose(pPoliza);

    if (escribio == 1) {
        cout << "\nPoliza guardada con exito.\n" << endl;
    }
    system("pause");
    return escribio;
}

bool ArchivoPoliza::listarRegistros() {
    Poliza obj;
    FILE *pPoliza;
    pPoliza = fopen(nombre, "rb");

    if (pPoliza == nullptr) {
        cout << "No se pudo abrir el archivo de polizas." << endl;
        cout << "No hay polizas cargadas." << endl;
        system("pause");
        return false;
    }

    bool hayPolizasActivas = false;
    system("cls");
    cout << "LISTADO DE POLIZAS" << endl;
    cout << "--------------------------------" << endl;

    while (fread(&obj, tamanioRegistro, 1, pPoliza) == 1) {
        if (obj.isActivo()) {
            obj.mostrar();
            hayPolizasActivas = true;
        }
    }

    fclose(pPoliza);

    if (!hayPolizasActivas) {
        cout << "No hay polizas cargadas para mostrar." << endl;
    }

    system("pause");
    return true;
}

Poliza ArchivoPoliza::leerRegistro(int pos) {
    Poliza obj;
    FILE *pPoliza;
    pPoliza = fopen(nombre, "rb");

    // Inicialización por si falla la apertura o lectura
    obj.setNumeroPoliza(-1);

    if (pPoliza == nullptr) {
        return obj;
    }

    fseek(pPoliza, pos * tamanioRegistro, SEEK_SET);
    fread(&obj, tamanioRegistro, 1, pPoliza);
    fclose(pPoliza);

    return obj;
}

bool ArchivoPoliza::modificarRegistro(Poliza reg, int pos) {
    FILE *pPoliza;
    pPoliza = fopen(nombre, "rb+"); // rb+ para leer y escribir
    if (pPoliza == nullptr) {
        return false;
    }

    fseek(pPoliza, pos * tamanioRegistro, SEEK_SET);
    int escribio = fwrite(&reg, tamanioRegistro, 1, pPoliza);
    fclose(pPoliza);

    return escribio == 1;
}

bool ArchivoPoliza::modificarDatosPoliza() {
    int numeroBuscado;
    system("cls");
    cout << "--- MODIFICAR POLIZA ---" << endl;
    cout << "Ingrese el numero de poliza a modificar: ";
    cin >> numeroBuscado;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    int pos = buscarPoliza(numeroBuscado);

    if (pos == -1) {
        cout << "Poliza con numero " << numeroBuscado << " no encontrada." << endl;
        system("pause");
        return false;
    }
    if (pos == -2) {
        cout << "Error al abrir el archivo de polizas." << endl;
        system("pause");
        return false;
    }

    Poliza pol = leerRegistro(pos);

    if (!pol.isActivo()) {
        cout << "La poliza con numero " << numeroBuscado << " esta dada de baja y no puede ser modificada." << endl;
        system("pause");
        return false;
    }

    cout << "\nPoliza encontrada:" << endl;
    pol.mostrar();
    cout << "\nIngrese los NUEVOS datos:" << endl;

    pol.cargarDatos(); // Carga todos los datos excepto el numero y estado.

    if (modificarRegistro(pol, pos)) {
        cout << "\nPoliza modificada exitosamente." << endl;
    } else {
        cout << "\nError al modificar la poliza." << endl;
    }
    system("pause");
    return true;
}

bool ArchivoPoliza::bajaLogica(int numeroPoliza) {
    int pos = buscarPoliza(numeroPoliza);
    if (pos < 0) {
        cout << "No se encontro la poliza con numero " << numeroPoliza << " o hubo un error." << endl;
        system("pause");
        return false;
    }

    Poliza reg = leerRegistro(pos);

    if(!reg.isActivo()){
        cout << "La poliza con numero " << numeroPoliza << " ya se encuentra dada de baja." << endl;
        system("pause");
        return false;
    }

    cout << "Poliza encontrada:" << endl;
    reg.mostrar();
    char confirmacion;
    cout << "Esta seguro de eliminar esta poliza (S/N)? ";
    cin >> confirmacion;
    confirmacion = toupper(confirmacion);

    if(confirmacion == 'S'){
        reg.setActivo(false);
        if (modificarRegistro(reg, pos)) {
            cout << "Poliza eliminada exitosamente." << endl;
        } else {
            cout << "Error al intentar dar de baja la poliza." << endl;
        }
    } else {
        cout << "Operacion cancelada." << endl;
    }

    system("pause");
    return true;
}

int ArchivoPoliza::contarRegistros() {
    FILE *pPoliza;
    pPoliza = fopen(nombre, "rb");
    if (pPoliza == nullptr) {
        return -1;
    }

    fseek(pPoliza, 0, SEEK_END);
    int cantBytes = ftell(pPoliza);
    fclose(pPoliza);

    return cantBytes / tamanioRegistro;
}

bool ArchivoPoliza::listarProximosVencimientos(int diasAnticipacion) {
    Poliza obj;
    FILE *pPoliza;
    pPoliza = fopen(nombre, "rb");

    if (pPoliza == nullptr) {
        cout << "No se pudo abrir el archivo de polizas." << endl;
        cout << "No hay polizas cargadas." << endl;
        system("pause");
        return false;
    }

    // Obtener fecha actual
    time_t ahora = time(0);
    tm* fechaActual = localtime(&ahora);
    int diaActual = fechaActual->tm_mday;
    int mesActual = fechaActual->tm_mon + 1; // tm_mon va de 0 a 11
    int anioActual = fechaActual->tm_year + 1900; // tm_year es años desde 1900

    bool hayVencimientos = false;
    system("cls");
    cout << "========================================" << endl;
    cout << "        PROXIMOS VENCIMIENTOS" << endl;
    cout << "========================================" << endl;
    cout << "    Tabla con polizas proximas a vencer" << endl;
    cout << "========================================" << endl;
    cout << "Fecha actual: " << diaActual << "/" << mesActual << "/" << anioActual << endl;
    cout << "Mostrando polizas que vencen en los proximos " << diasAnticipacion << " dias:" << endl;
    cout << "----------------------------------------" << endl;

    while (fread(&obj, tamanioRegistro, 1, pPoliza) == 1) {
        if (obj.isActivo()) {
            Fecha fechaVenc = obj.getFechaVencimiento();

            // Calcular días hasta vencimiento
            // Convertir fechas a días juliano aproximado para comparar
            int diasVencimiento = fechaVenc.getDia() + fechaVenc.getMes() * 30 + fechaVenc.getAnio() * 365;
            int diasActuales = diaActual + mesActual * 30 + anioActual * 365;
            int diferenciaDias = diasVencimiento - diasActuales;

            // Si vence dentro del rango especificado (incluyendo ya vencidas)
            if (diferenciaDias <= diasAnticipacion && diferenciaDias >= -30) {
<<<<<<< Updated upstream
            cout << "Poliza: " << obj.getNumeroPoliza()
             << " | Cliente: " << obj.getNombre() << " " << obj.getApellido()
             << " | Patente: " << obj.getPatente()
             << " | Vencimiento: " << fechaVenc.toString()
             << " | Estado: ";

            if (diferenciaDias < 0) {
                cout << "VENCIDA";
            } else if (diferenciaDias <= 7) {
                cout << "URGENTE";
            } else {
                cout << "PROXIMO";
            }
            cout << endl;

            hayVencimientos = true;

=======
                if (!hayVencimientos) {
                    cout << "Poliza - Cliente - Patente - Vencimiento - Estado" << endl;
                    cout << "----------------------------------------" << endl;
                }

                cout << "Poliza: " << obj.getNumeroPoliza()
                      << " | Cliente: " << obj.getNombre() << " " << obj.getApellido()
                     << " | Patente: " << obj.getPatente()
                     << " | Vencimiento: " << fechaVenc.toString()
                     << " | Estado: ";

                if (diferenciaDias < 0) {
                    cout << "VENCIDA";
                } else if (diferenciaDias <= 7) {
                    cout << "URGENTE";
                } else {
                    cout << "PROXIMO";
                }
                cout << endl;

                hayVencimientos = true;
>>>>>>> Stashed changes
            }
        }
    }

    fclose(pPoliza);


    if (!hayVencimientos) {
        cout << "No hay polizas proximas a vencer en los proximos " << diasAnticipacion << " dias." << endl;
    }

    cout << "========================================" << endl;
    cout << "0 - Volver al menu principal" << endl;
<<<<<<< Updated upstream

    system("pause");
=======
    system("Pause");
>>>>>>> Stashed changes
    return true;
}



bool ArchivoPoliza::listarPolizasConSiniestros() {
    system("cls");
    cout << "========================================" << endl;
    cout << "    POLIZAS CON SINIESTROS" << endl;
    cout << "========================================" << endl;


    ArchivoSiniestro archivoSin;
    bool hayResultados = false;

    FILE *pPoliza = fopen(nombre, "rb");
    if (pPoliza == nullptr) {
        cout << "No se pudo abrir el archivo de polizas." << endl;
        return false;
    }

    cout << "POLIZAS DISPONIBLES:" << endl;
    Poliza pol;
    while (fread(&pol, tamanioRegistro, 1, pPoliza) == 1) {
        if (pol.isActivo()) {
            cout << "Poliza ID: " << pol.getNumeroPoliza() << " - Cliente: " << pol.getNombre() << " " << pol.getApellido() << endl;
        }
    }

    cout << "\nSINIESTROS DISPONIBLES:" << endl;
    FILE *pSiniestro = fopen("siniestros.dat", "rb");
    if (pSiniestro != nullptr) {
        Siniestro sin;
        while (fread(&sin, sizeof(Siniestro), 1, pSiniestro) == 1) {
            if (sin.getActivo()) {
                cout << "Siniestro ID: " << sin.getIdSiniestro() << " - ID Poliza: " << sin.getIDPoliza()
                     << " - Monto: " << sin.getMontoReclamo() << endl;
            }
        }
        fclose(pSiniestro);
    }

    cout << "\nBUSCANDO COINCIDENCIAS:" << endl;
    cout << "----------------------------------------" << endl;

    // Volver al inicio del archivo de pólizas
    fseek(pPoliza, 0, SEEK_SET);

    while (fread(&pol, tamanioRegistro, 1, pPoliza) == 1) {
        if (pol.isActivo()) {
            // Buscar si esta póliza tiene siniestros
            bool tieneSiniestros = false;
            int cantSiniestros = 0;
            float montoTotal = 0;

            FILE *pSin = fopen("siniestros.dat", "rb");
            if (pSin != nullptr) {
                Siniestro sin;
                while (fread(&sin, sizeof(Siniestro), 1, pSin) == 1) {
                    if (sin.getActivo() && sin.getIDPoliza() == pol.getNumeroPoliza()) {
                        tieneSiniestros = true;
                        cantSiniestros++;
                        montoTotal += sin.getMontoReclamo();
                        cout << "COINCIDENCIA ENCONTRADA: Poliza " << pol.getNumeroPoliza()
                             << " con Siniestro ID " << sin.getIdSiniestro() << endl;
                    }
                }
                fclose(pSin);
            }

            if (tieneSiniestros) {
                if (!hayResultados) {
                    cout << "\nRESULTADOS FINALES:" << endl;
                    cout << "Poliza | Cliente | Patente | Cant.Siniestros | Monto Total" << endl;
                    cout << "--------------------------------------------------------" << endl;
                    hayResultados = true;
                }
                cout << pol.getNumeroPoliza() << " | "
                     << pol.getNombre() << " " << pol.getApellido() << " | "
                     << pol.getPatente() << " | "
                     << cantSiniestros << " | $"
                     << (long long)montoTotal << endl;
            }
        }
    }

    fclose(pPoliza);

    if (!hayResultados) {
        cout << "No hay polizas con siniestros registrados." << endl;
        cout << "Esto significa que ninguna poliza tiene siniestros con IDs coincidentes." << endl;
    }

    cout << "========================================" << endl;
    return true;
}

float ArchivoPoliza::calcularRecaudacionAnual(int anio) {
    FILE *pPoliza = fopen(nombre, "rb");
    if (pPoliza == nullptr) {
        return 0;
    }

    float recaudacion = 0;
    Poliza pol;

    while (fread(&pol, tamanioRegistro, 1, pPoliza) == 1) {
        if (pol.isActivo()) {
            Fecha fechaInicio = pol.getFechaInicio();
            Fecha fechaVenc = pol.getFechaVencimiento();

            // Solo contar si la póliza estuvo activa durante ese año
            if (fechaInicio.getAnio() <= anio && fechaVenc.getAnio() >= anio) {
                recaudacion += pol.getImporteMensual() * 12;
            }
        }
    }

    fclose(pPoliza);
    return recaudacion;
}

float ArchivoPoliza::calcularRecaudacionMensual(int mes, int anio) {
    FILE *pPoliza = fopen(nombre, "rb");
    if (pPoliza == nullptr) {
        return 0;
    }

    float recaudacion = 0;
    Poliza pol;

    while (fread(&pol, tamanioRegistro, 1, pPoliza) == 1) {
        if (pol.isActivo()) {
            Fecha fechaInicio = pol.getFechaInicio();
            Fecha fechaVenc = pol.getFechaVencimiento();

            // Verificar si la póliza estaba vigente en el mes/año consultado
            bool inicioAntes = (fechaInicio.getAnio() < anio) ||
                              (fechaInicio.getAnio() == anio && fechaInicio.getMes() <= mes);
            bool venceDepues = (fechaVenc.getAnio() > anio) ||
                              (fechaVenc.getAnio() == anio && fechaVenc.getMes() >= mes);

            if (inicioAntes && venceDepues) {
                recaudacion += pol.getImporteMensual();
            }
        }
    }

    fclose(pPoliza);
    return recaudacion;
}

float ArchivoPoliza::calcularRecaudacionSemanal(int semana, int anio) {
    // Implementación simple: calcular mes aproximado de la semana
    int mes = (semana - 1) / 4 + 1; // semanas 1-4=mes1, 5-8=mes2, etc.
    if (mes > 12) mes = 12;

    FILE *pPoliza = fopen(nombre, "rb");
    if (pPoliza == nullptr) {
        return 0;
    }

    float recaudacion = 0;
    Poliza pol;

    while (fread(&pol, tamanioRegistro, 1, pPoliza) == 1) {
        if (pol.isActivo()) {
            Fecha fechaInicio = pol.getFechaInicio();
            Fecha fechaVenc = pol.getFechaVencimiento();

            // Solo contar si la póliza estaba vigente en ese mes/año aproximado
            bool inicioAntes = (fechaInicio.getAnio() < anio) ||
                              (fechaInicio.getAnio() == anio && fechaInicio.getMes() <= mes);
            bool venceDepues = (fechaVenc.getAnio() > anio) ||
                              (fechaVenc.getAnio() == anio && fechaVenc.getMes() >= mes);

            if (inicioAntes && venceDepues) {
                recaudacion += pol.getImporteMensual() / 4; // Dividir por semanas del mes
            }
        }
    }

    fclose(pPoliza);
    return recaudacion;
}

float ArchivoPoliza::calcularRecaudacionPersonalizada(Fecha fechaInicio, Fecha fechaFin) {
    FILE *pPoliza = fopen(nombre, "rb");
    if (pPoliza == nullptr) {
        return 0;
    }

    float recaudacion = 0;
    Poliza pol;

    // Cálculo simple de meses entre fechas
    int mesesPeriodo = (fechaFin.getAnio() - fechaInicio.getAnio()) * 12 +
                       (fechaFin.getMes() - fechaInicio.getMes()) + 1;

    while (fread(&pol, tamanioRegistro, 1, pPoliza) == 1) {
        if (pol.isActivo()) {
            Fecha fechaInicPol = pol.getFechaInicio();
            Fecha fechaVencPol = pol.getFechaVencimiento();

            // Verificar si la póliza estuvo vigente durante el período consultado
            bool polizaIniciaAntes = (fechaInicPol.getAnio() < fechaFin.getAnio()) ||
                                    (fechaInicPol.getAnio() == fechaFin.getAnio() && fechaInicPol.getMes() <= fechaFin.getMes());
            bool polizaVenceDepues = (fechaVencPol.getAnio() > fechaInicio.getAnio()) ||
                                    (fechaVencPol.getAnio() == fechaInicio.getAnio() && fechaVencPol.getMes() >= fechaInicio.getMes());

            if (polizaIniciaAntes && polizaVenceDepues) {
                recaudacion += pol.getImporteMensual() * mesesPeriodo;
            }
        }
    }

    fclose(pPoliza);
    return recaudacion;
}
