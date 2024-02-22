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

struct Cliente_struc {
    string nombre, numero_id, tiene_cuenta_colones, tiene_cuenta_dolares, saldo_cuenta_colones, saldo_cuenta_dolares;
};

void mostrarMenu() {
    cout << "Seleccione el tipo de transacción:\n"
         << "1. Depósito\n"
         << "2. Retiro\n"
         << "3. Transferencia\n"
         << "4. Reporte sobre préstamos propios\n"
         << "5. CDP\n"
         << "6. Solicitar un prestamo\n"
         << "7. Abono a préstamo propio\n"
         << "8. Abono a préstamo de otra persona\n";

}

void crearCDP(string id_cliente){
    double monto;
    int plazo;
    double interes;
    cout << "Ingrese el monto del CDP: ";
    cin >> monto;
    cout << "Ingrese el plazo del CDP en meses: ";
    cin >> plazo;

    cout << "Ingrese la tasa de interés del CDP (%): ";
    cin >> interes;


    CDP miCDP(monto, plazo, interes, id_cliente);
    miCDP.crearCDP();


}

    Prestamo prestamoSolicitado;
    string idPrestamoAbonar;

void realizarTransaccion(int tipoTransaccion, string id_cliente) {
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
            crearCDP(id_cliente);
            break;
        case 6:
        int prestamorequerido;
        do {
        std::cout << "Seleccione uno de los prestamos a solicitar:\n";
        std::cout << "Prestamos Personales:\n";
        std::cout << "0: Personal tasa de interes del 10%, 24 cuotas\n";
        std::cout << "1: Personal tasa de interes del 8%, 36 cuotas\n";
        std::cout << "2: Personal tasa de interes del 6.5%, 48 cuotas\n";
        std::cout << "Prestamos Hipotecarios:\n";
        std::cout << "3: Hipotecario tasa de interes del 4.5%, 360 cuotas\n";
        std::cout << "4: Hipotecario tasa de interes del 3.8%, 300 cuotas\n";
        std::cout << "5: Hipotecario tasa de interes del 4%, 336 cuotas\n";
        std::cout << "Prestamos Prendarios:\n";
        std::cout << "6: Prendario tasa de interes del 6%, 60 cuotas\n";
        std::cout << "7: Prendario tasa de interes del 5.2%, 78 cuotas\n";
        std::cout << "8: Prendario tasa de interes del 4.5%, 90 cuotas\n";
        // Verificar si la entrada es un entero y está dentro del rango correcto
        while (!(std::cin >> prestamorequerido) || prestamorequerido < 0 || prestamorequerido > 8) {
            std::cout << "Entrada inválida. Por favor, ingrese un número entero dentro del rango 0-8.\n";
            std::cin.clear(); // Limpiar el estado de error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descartar la entrada incorrecta
        }
    } while (prestamorequerido < 0 || prestamorequerido > 8);

        int moneda;
        cout << "Seleccione la moneda a solicitar del prestamo:\n";
        cout << "0: solicitar en colones\n";
        cout << "1: solicitar en dolares\n";
        cin >> moneda;

        long monto;
        cout << "Seleccione el monto a solicitar:\n";
        cin >> monto;

        switch (prestamorequerido)
        {
        case 0: // Personal tasa de interés del 10%, 24 cuotas
            prestamoSolicitado = Prestamo(Prestamo::PERSONAL, 10.0, 24, monto);
            break;

        case 1: // Personal tasa de interés del 8%, 36 cuotas
            prestamoSolicitado = Prestamo(Prestamo::PERSONAL, 8.0, 36, monto);
            break;

        case 2: // Personal tasa de interés del 6.5%, 48 cuotas
            prestamoSolicitado = Prestamo(Prestamo::PERSONAL, 6.5, 48, monto);
            break;

        case 3: // Hipotecario tasa de interés del 4.5%, 360 cuotas
            prestamoSolicitado = Prestamo(Prestamo::HIPOTECARIO, 4.5, 360, monto);
            break;

        case 4: // Hipotecario tasa de interés del 3.8%, 300 cuotas
            prestamoSolicitado = Prestamo(Prestamo::HIPOTECARIO, 3.8, 300, monto);
            break;

        case 5: // Hipotecario tasa de interés del 4%, 336 cuotas
            prestamoSolicitado = Prestamo(Prestamo::HIPOTECARIO, 4.0, 336, monto);
            break;

        case 6: // Prendario tasa de interés del 6%, 60 cuotas
            prestamoSolicitado = Prestamo(Prestamo::PRENDARIO, 6.0, 60, monto);
            break;

        case 7: // Prendario tasa de interés del 5.2%, 78 cuotas
            prestamoSolicitado = Prestamo(Prestamo::PRENDARIO, 5.2, 78, monto);
            break;

        case 8: // Prendario tasa de interés del 4.5%, 90 cuotas
            prestamoSolicitado = Prestamo(Prestamo::PRENDARIO, 4.5, 90, monto);
            break;

        default:
            cout << "Opción no válida\n";
            return; // Salir del programa con un código de error
        }

        prestamoSolicitado.guardarPrestamo(moneda, id_cliente);
        cout << "\nRealizando Solicitud de prestamo propio...\n";
        break;
        case 7:
            // Funcion para abonar un prestamo propio
            prestamoSolicitado.abonarPrestamoPropio(id_cliente);
            cout << "Realizando Abono a préstamo de otra propio...\n";
        break;
        case 8:
            // Lógica para abono a préstamo de otra persona
            cout << "Digite el Id del Prestamo a Abonar:\n";
            cin >> idPrestamoAbonar;

            prestamoSolicitado.abonarPrestamoAgeno(id_cliente, idPrestamoAbonar);
            cout << "Realizando Abono a préstamo de otra persona...\n";
            break;
        default:
            cout << "Opción no válida. Por favor, ingrese un número del 1 al 8.\n";
    }
}

void atenderCliente() {
    ifstream archivo("./src/clientes.csv");
    string linea;
    char delimitador = ',';
    getline(archivo, linea);

    string id_cliente;
    cout << "Ingrese el número de identificación: ";
    cin >> id_cliente;

    bool clienteEncontrado = false;

    while (getline(archivo, linea)) {
        stringstream stream(linea);
        Cliente_struc cliente;

        getline(stream, cliente.nombre, delimitador);
        getline(stream, cliente.numero_id, delimitador);
        getline(stream, cliente.tiene_cuenta_colones, delimitador);
        getline(stream, cliente.tiene_cuenta_dolares, delimitador);
        getline(stream, cliente.saldo_cuenta_colones, delimitador);
        getline(stream, cliente.saldo_cuenta_dolares, delimitador);

        if (cliente.numero_id == id_cliente) {
            clienteEncontrado = true;
            cout << "\nCliente encontrado, bienvenido (a) " << cliente.nombre << endl;

            int tipoTransaccion;
            mostrarMenu();

            while (!(cin >> tipoTransaccion) || tipoTransaccion < 1 || tipoTransaccion > 7) {
                cout << "Entrada inválida. Por favor, ingrese un número válido del 1 al 7: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            cout << "Realizando la transacción número: " << tipoTransaccion << "\n";
            realizarTransaccion(tipoTransaccion, id_cliente);

        }
    }

    if (!clienteEncontrado) {
        cout << "Cliente no encontrado, intente de nuevo" << endl;
        archivo.close();
        atenderCliente();
    }
    archivo.close();
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
