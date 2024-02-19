#include <iostream>
#include "funciones.hpp"
#include "Prestamo.hpp"
#include <limits>
#include "CDP.hpp"
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;

struct Cliente {
    string nombre;
    string numero_id;
    bool tiene_cuenta_colones;
    bool tiene_cuenta_dolares;
    double saldo_cuenta_colones;
    double saldo_cuenta_dolares;
};

bool buscarCliente(const string& numero_id, const string& archivo) {
    ifstream file(archivo);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo.\n";
        return false;
    }

    string linea;
    while (getline(file, linea)) {
        istringstream ss(linea);
        Cliente cliente;
        char coma; 

        if (ss >> cliente.nombre >> coma >> cliente.numero_id >> coma >>
                   cliente.tiene_cuenta_colones >> coma >> cliente.tiene_cuenta_dolares >> coma >>
                   cliente.saldo_cuenta_colones >> coma >> cliente.saldo_cuenta_dolares) {
            if (cliente.numero_id == numero_id) {
                cout << "Cliente encontrado:\n";
                cout << "Nombre: " << cliente.nombre << "\n";
                cout << "Número de Identificación: " << cliente.numero_id << "\n";
                cout << "Cuenta en Colones: " << (cliente.tiene_cuenta_colones ? "Sí" : "No") << "\n";
                cout << "Cuenta en Dólares: " << (cliente.tiene_cuenta_dolares ? "Sí" : "No") << "\n";
                cout << "Saldo en Colones: " << cliente.saldo_cuenta_colones << "\n";
                cout << "Saldo en Dólares: " << cliente.saldo_cuenta_dolares << "\n";
                file.close();
                return true;
            }
        }
    }

    cout << "Cliente no encontrado.\n";
    file.close();
    return false;
}


void atenderCliente() {
    string numero_id;
    cout << "Ingrese el número de identificación (001-010): ";
    cin >> numero_id;

    if (numero_id.size() == 3 && numero_id >= "001" && numero_id <= "010") {
        if (!buscarCliente(numero_id, "./src/clientes.csv")) {
            cout << "El número de identificación no está en el archivo.\n";
            //exit(0);
        }
    } else {
        cout << "Número de identificación no válido.\n";
        //exit(0);
    }


    int tipoTransaccion;
    cout << "Seleccione el tipo de transacción:\n"
         << "1. Depósito\n"
         << "2. Retiro\n"
         << "3. Transferencia\n"
         << "4. Reporte sobre préstamos propios\n"
         << "5. CDP\n"
         << "6. Abono a préstamo propio\n"
         << "7. Abono a préstamo de otra persona\n";

    while (!(cin >> tipoTransaccion) || tipoTransaccion < 1 || tipoTransaccion > 7) {
        cout << "Entrada inválida. Por favor, ingrese un número válido del 1 al 7: ";
        cin.clear();  // Limpiar el estado de error
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Descartar la entrada incorrecta
    }

    cout << "Atendiendo al cliente con ID: " << numero_id << "\n";
    cout << "Realizando la transacción número: " << tipoTransaccion << "\n";


    switch (tipoTransaccion) {
        case 1:
            cout << "Realizando Depósito...\n";
            // Lógica para depósito
            break;
        case 2:
            cout << "Realizando Retiro...\n";
            // Lógica para retiro
            break;
        case 3:
            cout << "Realizando Transferencia...\n";
            // Lógica para transferencia
            break;
        case 4:
            cout << "Generando Reporte sobre préstamos propios...\n";
            // Lógica para reporte de préstamos propios
            break;
        case 5:
            cout << "Accediendo a Certificado de Depósito a Plazo (CDP)...\n";
            break;
        case 6:
            cout << "Realizando Abono a préstamo propio...\n";
            // Lógica para abono a préstamo propio
            break;
        case 7:
            cout << "Realizando Abono a préstamo de otra persona...\n";
            // Lógica para abono a préstamo de otra persona
            break;
        default:
            cout << "Opción no válida. Por favor, ingrese un número del 1 al 7.\n";
    }
    
}
// Se inicia la funcion solicitar, que llama a la clase prestamo y la utiliza.
void solicitarInformacionPrestamos() {
    int num_info_prest;
    do {
        std::cout << "Digite que tipo de opcion deseada\n";
        std::cout << "1. Ver la informacion de prestamos hechos por el banco\n";
        std::cout << "2. Ver la informacion de un prestamo personalizado\n";
        std::cin >> num_info_prest;
        if (num_info_prest != 1 && num_info_prest != 2) {
            std::cout << "Opcion no valida. Por favor, seleccione 1 o 2.\n";
        }
    } while (num_info_prest != 1 && num_info_prest != 2);
 
    double tasaInteresAnual;
    int cantidadCuotas;
    double montoPrestamo;
    int tipo;
    switch (num_info_prest){
    case 1:
        int tip_prest;
        do {
        std::cout << "Seleccione uno de los tipos de prestamos:\n";
        std::cout << "0: Personal\n";
        std::cout << "1: Hipotecario\n";
        std::cout << "2: Prendario\n";
        
        // Verificar si la entrada es un entero y está dentro del rango correcto
        while (!(std::cin >> tip_prest) || tip_prest < 0 || tip_prest > 2) {
            std::cout << "Entrada invalida. Por favor, ingrese un numero entero dentro del rango 0-2.\n";
            std::cin.clear(); // Limpiar el estado de error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descartar la entrada incorrecta
        }
        
    } while (tip_prest < 0 || tip_prest > 2);

       switch (tip_prest)
        {
        case 0:
        int prest_per;
        do {
        cout << "Seleccione uno de los prestamos personales:\n";
        cout << "0: tasa de interes del 10%, 24 cuotas\n";
        cout << "1: tasa de interes del 8%, 36 cuotas\n";
        cout << "2: tasa de interes del 6.5%, 48 cuotas\n";
        
        // Verificar si la entrada es un entero y está dentro del rango correcto
        while (!(std::cin >> prest_per) || prest_per < 0 || prest_per > 2) {
            std::cout << "Entrada invalida. Por favor, ingrese un numero entero dentro del rango 0-2.\n";
            std::cin.clear(); // Limpiar el estado de error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descartar la entrada incorrecta
        }
        } while (prest_per < 0 || prest_per > 2);
            switch (prest_per) {
                case 0:
                    tipo = Prestamo::PERSONAL;
                    tasaInteresAnual = 10;
                    cantidadCuotas = 24;
                    cout << "Ingrese el monto a solicitar:\n";
                    cin >> montoPrestamo;
                    break;
                case 1:
                    tipo = Prestamo::PERSONAL;
                    tasaInteresAnual = 8;
                    cantidadCuotas = 36;
                    cout << "Ingrese el monto a solicitar:\n";
                    cin >> montoPrestamo;
                    break;
                case 2:
                    tipo = Prestamo::PERSONAL;
                    tasaInteresAnual = 6.5;
                    cantidadCuotas = 48;
                    cout << "Ingrese el monto a solicitar:\n";
                    cin >> montoPrestamo;
                    break;
                default:
                    cout << "Opcion no valida. Por favor, seleccione una opcion valida.\n";
            }
        break;
        case 1:
        int prest_hip;
        do {
        std::cout << "Seleccione uno de los prestamos hipotecarios:\n";
        std::cout << "0: tasa de interes del 4.5%, 360 cuotas\n";
        std::cout << "1: tasa de interes del 3.8%, 300 cuotas\n";
        std::cout << "2: tasa de interes del 4%, 336 cuotas\n";
        
        // Verificar si la entrada es un entero y está dentro del rango correcto
        while (!(std::cin >> prest_hip) || prest_hip < 0 || prest_hip > 2) {
            std::cout << "Entrada invalida. Por favor, ingrese un numero entero dentro del rango 0-2.\n";
            std::cin.clear(); // Limpiar el estado de error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descartar la entrada incorrecta
        }
        
        } while (prest_hip < 0 || prest_hip > 2);
            switch (prest_hip) {
                case 0:
                    tipo = Prestamo::PERSONAL;
                    tasaInteresAnual = 4.5;
                    cantidadCuotas = 360;
                    cout << "Ingrese el monto a solicitar:\n";
                    cin >> montoPrestamo;
                    break;
                case 1:
                    tipo = Prestamo::PERSONAL;
                    tasaInteresAnual = 3.8;
                    cantidadCuotas = 300;
                    cout << "Ingrese el monto a solicitar:\n";
                    cin >> montoPrestamo;
                    break;
                case 2:
                    tipo = Prestamo::PERSONAL;
                    tasaInteresAnual = 4;
                    cantidadCuotas = 336;
                    cout << "Ingrese el monto a solicitar:\n";
                    cin >> montoPrestamo;
                    break;
                default:
                    cout << "Opcion no valida. Por favor, seleccione una opcion valida\n";
            }
        break;
        case 2:
            int prest_pre;
        do {
        std::cout << "Seleccione uno de los prestamos prendarios:\n";
        std::cout << "0: tasa de interes del 6%, 60 cuotas\n";
        std::cout << "1: tasa de interes del 5.2%, 78 cuotas\n";
        std::cout << "2: tasa de interes del 4.5%, 90 cuotas\n";
        // Verificar si la entrada es un entero y está dentro del rango correcto
        while (!(std::cin >> prest_pre) || prest_pre < 0 || prest_pre > 2) {
            std::cout << "Entrada invalida. Por favor, ingrese un numero entero dentro del rango 0-2.\n";
            std::cin.clear(); // Limpiar el estado de error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descartar la entrada incorrecta
        }
        } while (prest_pre < 0 || prest_pre > 2);
            switch (prest_pre) {
                case 0:
                    tipo = Prestamo::PERSONAL;
                    tasaInteresAnual = 6;
                    cantidadCuotas = 60;
                    cout << "Ingrese el monto a solicitar:\n";
                    cin >> montoPrestamo;
                    break;
                case 1:
                    tipo = Prestamo::PERSONAL;
                    tasaInteresAnual = 5.2;
                    cantidadCuotas = 78;
                    cout << "Ingrese el monto a solicitar:\n";
                    cin >> montoPrestamo;
                    break;
                case 2:
                    tipo = Prestamo::PERSONAL;
                    tasaInteresAnual = 4.5;
                    cantidadCuotas = 90;
                    cout << "Ingrese el monto a solicitar:\n";
                    cin >> montoPrestamo;
                    break;
                default:
                    cout << "Opcion no valida. Por favor, seleccione una opcion valida.\n";
            }
        break;
        default:
            break;
        }

    break;
    case 2:
    cout << "Introduzca los datos de interes :\n";
    int tipo;
    cout << "Tipo de prestamo (0: Personal, 1: Hipotecario, 2: Prendario): ";
    cin >> tipo;
    do {
        cout << "Seleccione uno de los prestamos prendarios:\n";
        cout << "Tipo de prestamo (0: Personal, 1: Hipotecario, 2: Prendario): ";
    // Verificar si la entrada es un entero y está dentro del rango correcto
    while (!(std::cin >> tipo) || tipo < 0 || tipo > 2) {
            std::cout << "Entrada invalida. Por favor, ingrese un numero entero dentro del rango 0-2.\n";
            std::cin.clear(); // Limpiar el estado de error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descartar la entrada incorrecta
    }
    } while (tipo < 0 || tipo > 2);
    // Solicitar y validar la tasa de interés anual
    do {
        cout << "Ingrese la tasa de interes anual (%): ";
        if (!(cin >> tasaInteresAnual) || tasaInteresAnual <= 0) {
            cout << "Error: Por favor ingrese un valor numerico positivo." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (tasaInteresAnual <= 0);

    // Solicitar y validar la cantidad de cuotas
    do {
        cout << "Ingrese la cantidad de cuotas (meses): ";
        if (!(cin >> cantidadCuotas) || cantidadCuotas <= 0) {
            cout << "Error: Por favor ingrese un valor numerico positivo." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (cantidadCuotas <= 0);

    // Solicitar y validar el monto del préstamo
    do {
        cout << "Ingrese el monto del prestamo: ";
        if (!(cin >> montoPrestamo) || montoPrestamo <= 0) {
            cout << "Error: Por favor ingrese un valor numerico positivo." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (montoPrestamo <= 0);
    break;
    default:
            cerr << "Opcion no valida\n";
            return;
    }
    // Se crea el objeto Prestamo con los datos ingresados
    Prestamo prestamo(Prestamo::PERSONAL, tasaInteresAnual, cantidadCuotas, montoPrestamo);
    // Se abre el archivo CSV para escritura
    ofstream archivo("tabla_prestamo_solicitado.csv");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo." << endl;
    }

    // Se escribe el encabezado de la tabla en el archivo CSV
    archivo << "Mes" << "," << "Cuota Mensual" << "," << "Intereses" << "," << "Deuda" << "," << "Monto Restante" << "\n";

    // Se calculan e imprimir los valores para cada mes
    double deuda = montoPrestamo;
    for (int i = 1; i <= cantidadCuotas; ++i) {
        double cuotaMensual = prestamo.calcularCuotaMensual();
        double intereses = deuda * (tasaInteresAnual / 12 / 100);
        double amortizacion = cuotaMensual - intereses;
        deuda -= amortizacion;
        
        // Se escribe la línea en el archivo CSV
        archivo << i << "," << fixed << setprecision(2) << cuotaMensual << "," << intereses << "," << amortizacion << "," << deuda << "\n";
    }

    // Se cierra el archivo
    archivo.close();

    cout << "Archivo CSV generado correctamentem se guarda como tabla_prestamo_solicitado.csv ." << endl;
    cout << "operacion terminada, volviendo al menu principal"<< endl;
}
