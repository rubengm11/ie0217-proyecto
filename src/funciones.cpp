#include <iostream>
#include <limits>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include "funciones.hpp"
#include "Cliente.hpp"
#include "Cuenta.hpp"
#include "Prestamo.hpp"
#include "CDP.hpp"
#include <vector>

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

void agregarCliente(){
    cout << "Agregando un nuevo cliente" << endl;
    string nombre, numeroID;
    int tieneCuentaColones, tieneCuentaDolares;
    int saldoCuentaColones, saldoCuentaDolares;

    // Solicitar al usuario los datos del nuevo cliente
    std::cout << "Ingrese el nombre del cliente: ";
    std::getline(std::cin >> std::ws, nombre);

    do {
        std::cout << "Ingrese el número de identificación (9 dígitos): ";
        std::getline(std::cin >> std::ws, numeroID);

        if (numeroID.length() != 9) {
            std::cout << "Número de identificación inválido. Debe tener 9 dígitos numéricos.\n";
        } else {
            break;
        }
    } while (true);

    do {
        std::cout << "¿Tiene cuenta en colones? (1 para sí, 0 para no): ";
        std::cin >> tieneCuentaColones;

        if (std::cin.fail() || (tieneCuentaColones != 0 && tieneCuentaColones != 1)) {
            std::cin.clear();  // Limpiar el estado de error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Descartar la entrada incorrecta
            std::cout << "Opción inválida. Por favor, ingrese 1 para sí o 0 para no.\n";
        } else {
            break;  // Salir del bucle si la entrada es válida
        }
    } while (true);
    

    do {
        std::cout << "¿Tiene cuenta en dolares? (1 para sí, 0 para no): ";
        std::cin >> tieneCuentaDolares;

        if (std::cin.fail() || (tieneCuentaDolares != 0 && tieneCuentaDolares != 1)) {
            std::cin.clear();  // Limpiar el estado de error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Descartar la entrada incorrecta
            std::cout << "Opción inválida. Por favor, ingrese 1 para sí o 0 para no.\n";
        } else {
            break;  // Salir del bucle si la entrada es válida
        }
    } while (true);

    while (true){
        if (!tieneCuentaColones & !tieneCuentaDolares){
            cout << "El cliente debe tener al menos una cuenta.\n";
            break;

        } else {
            if (tieneCuentaColones) {
                do {
                    std::cout << "Ingrese el saldo en colones: ";
                    std::cin >> saldoCuentaColones;

                    if (std::cin.fail() || saldoCuentaColones < 0) {
                        std::cin.clear();  // Limpiar el estado de error
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Descartar la entrada incorrecta
                        std::cout << "Entrada inválida. Por favor, ingrese un número positivo.\n";
                    } else {
                        break;  // Salir del bucle si la entrada es válida
                    }
                } while (true);
        } else {
            saldoCuentaColones = 0;
        }

        if (tieneCuentaDolares) {
            do {
                std::cout << "Ingrese el saldo en dolares: ";
                std::cin >> saldoCuentaDolares;

                if (std::cin.fail() || saldoCuentaDolares < 0) {
                    std::cin.clear();  // Limpiar el estado de error
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Descartar la entrada incorrecta
                    std::cout << "Entrada inválida. Por favor, ingrese un número positivo.\n";
                } else {
                    break;  // Salir del bucle si la entrada es válida
                }
            } while (true);
        } else {
            saldoCuentaDolares = 0;
        }

        // Abrir el archivo en modo apendizaje para agregar el nuevo cliente
        std::ofstream archivo("./src/clientes.csv", std::ios::app);

        if (!archivo.is_open()) {
            std::cerr << "Error al abrir el archivo.\n";
            return;
        }

        // Escribir los datos del nuevo cliente en el archivo
        archivo << nombre << "," << numeroID << ","
                << tieneCuentaColones << "," << tieneCuentaDolares << ","
                << saldoCuentaColones << "," << saldoCuentaDolares << "\n";

        archivo.close();

        std::cout << "Cliente agregado exitosamente.\n";

        // Escritura en el archivo de registro bancario
        std::ofstream archivoRegistro("./src/registro_bancario.txt", std::ios::app);

        if (!archivoRegistro.is_open()) {
            std::cerr << "Error al abrir el archivo.\n";
            return;
        }

        // Escribir los datos del nuevo cliente en el archivo
        archivoRegistro << "\nTipo de operacion: Creacion de nuevo cliente\n" << "Nombre: " << nombre << "\nIdentificacion: " << numeroID << "\n";

        archivoRegistro.close();
        break;

        }
    }


    
}

void crearCDP(string id_cliente){
    bool moneda;
    double monto;
    int plazo;
    double interes;

    do {
        cout << "Ingrese la moneda del CDP (0: colones, 1: dolares): ";
        cin >> moneda;

        // Verificar si la entrada es válida
        if (cin.fail() || moneda > 1 || moneda < 0) {
            cin.clear();  // Limpiar el estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  
            cout << "Error: Ingrese una moneda válida." << std::endl;
        } else {
            break;  // Salir del bucle si la entrada es válida
        }
    } while (true);

    do {
        // Pedir al usuario que ingrese el monto y manejar errores
        std::cout << "Ingrese el monto (debe ser un número positivo): ";
        std::cin >> monto;

        // Verificar si la entrada es válida
        if (std::cin.fail() || monto <= 0) {
            std::cin.clear();  // Limpiar el estado de error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Descartar la entrada incorrecta
            std::cout << "Error: Ingrese un monto válido. Debe ser un número positivo." << std::endl;
        } else {
            break;  // Salir del bucle si la entrada es válida
        }
    } while (true);
   
    do {
        // Pedir al usuario que ingrese el plazo y manejar errores
        std::cout << "Ingrese el plazo en meses (debe ser un número entero positivo): ";
        std::cin >> plazo;

        // Verificar si la entrada es válida
        if (std::cin.fail() || plazo <= 0) {
            std::cin.clear();  // Limpiar el estado de error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Descartar la entrada incorrecta
            std::cout << "Error: Ingrese un plazo válido. Debe ser un número entero positivo." << std::endl;
        } else {
            break;  // Salir del bucle si la entrada es válida
        }
    } while (true);

    do {
        // Pedir al usuario que ingrese el interés y manejar errores
        std::cout << "Ingrese la tasa de interés (debe ser un número positivo y menor a 20): ";
        std::cin >> interes;

        // Verificar si la entrada es válida
        if (std::cin.fail() || interes <= 0 || interes >= 20) {
            std::cin.clear();  // Limpiar el estado de error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Descartar la entrada incorrecta
            std::cout << "Error: Ingrese un interés válido. Debe ser un número positivo y menor a 20." << std::endl;
        } else {
            break;  // Salir del bucle si la entrada es válida
        }
    } while (true);



    CDP miCDP(monto, plazo, interes, id_cliente, moneda);
    miCDP.crearCDP();
}

    Prestamo prestamoSolicitado;
    string idPrestamoAbonar;


void realizarTransaccion(int tipoTransaccion, string id_cliente, Cliente& clienteActual) {
    switch (tipoTransaccion) {
        case 1:{
            cout << "Realizando Depósito...\n";
            // Lógica para depósito
            bool esDepositoEnColones;

            do {
                cout << "¿El depósito es en colones? (1: Sí, 0: No): ";
                cin >> esDepositoEnColones;
                // Verificar si la entrada es válida
                if (cin.fail() || esDepositoEnColones > 1 || esDepositoEnColones < 0) {
                    cin.clear();  // Limpiar el estado de error
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  
                    cout << "Error: Ingrese una opcion válida." << std::endl;
                } else {
                    break;  // Salir del bucle si la entrada es válida
                }
            } while (true);

            double monto;
            cout << "Ingrese el monto a depositar: ";
            while (!(cin >> monto) || monto <= 0) {
                cout << "Monto inválido. Por favor, ingrese un monto válido: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            if (esDepositoEnColones) {
                clienteActual.depositarEnCuentaColones(monto);
                // Escritura en el archivo de registro bancario
                std::ofstream archivoRegistro("./src/registro_bancario.txt", std::ios::app);

                if (!archivoRegistro.is_open()) {
                std::cerr << "Error al abrir el archivo.\n";
                return;
                }

                // Escribir los datos del nuevo cliente en el archivo
                archivoRegistro << "\nTipo de operacion: Deposito\n" << "ID cliente: " << id_cliente << "\nMoneda: " << "Colones" << "\nMonto: " << monto << "\n";
                archivoRegistro.close();

            } else {
                clienteActual.depositarEnCuentaDolares(monto);
                // Escritura en el archivo de registro bancario
                std::ofstream archivoRegistro("./src/registro_bancario.txt", std::ios::app);

                if (!archivoRegistro.is_open()) {
                std::cerr << "Error al abrir el archivo.\n";
                return;
                }

                // Escribir los datos del nuevo cliente en el archivo
                archivoRegistro << "\nTipo de operacion: Deposito\n" << "ID cliente: " << id_cliente << "\nMoneda: " << "Dolares" << "\nMonto: " << monto << "\n";
                archivoRegistro.close();
            }
            break;
            }
        case 2:{
            bool esRetiroEnColones;
            do {
                cout << "¿El retiro es en colones? (1: Sí, 0: No): ";
                cin >> esRetiroEnColones;
                // Verificar si la entrada es válida
                if (cin.fail() || esRetiroEnColones > 1 || esRetiroEnColones < 0) {
                    cin.clear();  // Limpiar el estado de error
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  
                    cout << "Error: Ingrese una opcion válida." << std::endl;
                } else {
                    break;  // Salir del bucle si la entrada es válida
                }
            } while (true);
            double monto;
            cout << "Ingrese el monto a retirar: ";
            while (!(cin >> monto) || monto <= 0) {
                cout << "Monto inválido. Por favor, ingrese un monto válido: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            bool resultado;
            if (esRetiroEnColones) {
                resultado = clienteActual.retirarDeCuentaColones(monto);
                // Escritura en el archivo de registro bancario
                std::ofstream archivoRegistro("./src/registro_bancario.txt", std::ios::app);

                if (!archivoRegistro.is_open()) {
                std::cerr << "Error al abrir el archivo.\n";
                return;
                }

                // Escribir los datos del nuevo cliente en el archivo
                archivoRegistro << "\nTipo de operacion: Retiro\n" << "ID cliente: " << id_cliente << "\nMoneda: " << "Colones" << "\nMonto: " << monto << "\n";
                archivoRegistro.close();
            } else {
                resultado = clienteActual.retirarDeCuentaDolares(monto);
                // Escritura en el archivo de registro bancario
                std::ofstream archivoRegistro("./src/registro_bancario.txt", std::ios::app);

                if (!archivoRegistro.is_open()) {
                std::cerr << "Error al abrir el archivo.\n";
                return;
                }

                // Escribir los datos del nuevo cliente en el archivo
                archivoRegistro << "\nTipo de operacion: Deposito\n" << "ID cliente: " << id_cliente << "\nMoneda: " << "Dolares" << "\nMonto: " << monto << "\n";
                archivoRegistro.close();
            }
            if (!resultado) {
                cout << "No se pudo completar el retiro." << endl;
            }
            break;
        }
        case 3: {
            cout << "Realizando Transferencia...\n";
            double montoTransferir;
            string idClienteDestino;
            int tipoMoneda;
            bool esRetiroExitoso = false, clienteEncontrado = false, tieneCuentaEnMoneda = false;

            do {
            cout << "Ingrese el monto a transferir: ";
            if (!(cin >> montoTransferir) || montoTransferir <= 0) {
                cout << "Error: Por favor ingrese un valor numerico positivo." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            } while (montoTransferir <= 0);

            do {
                cout << "Ingrese el tipo de moneda (1 para Colones, 2 para Dólares): ";
                cin >> tipoMoneda;
                // Verificar si la entrada es válida
                if (cin.fail() || tipoMoneda > 2 || tipoMoneda < 1) {
                    cin.clear();  // Limpiar el estado de error
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  
                    cout << "Error: Ingrese una opcion válida." << std::endl;
                } else {
                    break;  // Salir del bucle si la entrada es válida
                }
            } while (true);


            cout << "Ingrese el ID del cliente destino: ";
            cin >> idClienteDestino;

            // Verificar que el monto es positivo y el tipo de moneda es válido
            if (montoTransferir <= 0 || (tipoMoneda != 1 && tipoMoneda != 2)) {
                cout << "Operación inválida.\n";
                break;
            }

            vector<string> lineasActualizadas;
            string linea;
            fstream archivoClientes("./src/clientes.csv", ios::in);
            if (!archivoClientes.is_open()) {
                cout << "Error al abrir el archivo.\n";
                break;
            }

            // Leer todo el archivo y buscar al cliente destino al mismo tiempo
            while (getline(archivoClientes, linea)) {
            stringstream ss(linea);
            string segmento;
            vector<string> segmentos;
            while (getline(ss, segmento, ',')) {
                segmentos.push_back(segmento);
            }

            if (segmentos[1] == idClienteDestino && ((tipoMoneda == 1 && segmentos[2] == "1") || (tipoMoneda == 2 && segmentos[3] == "1"))) {
                clienteEncontrado = true;
                tieneCuentaEnMoneda = true;
                // Actualizar el saldo del cliente destino
                double saldoActual = stod(segmentos[tipoMoneda + 3]);
                saldoActual += montoTransferir; // Asumiendo que segmentos[4] o segmentos[5] contiene el saldo
                int saldoSinDecimales = static_cast<int>(round(saldoActual)); // Redondea y convierte a entero
                segmentos[tipoMoneda + 3] = to_string(saldoSinDecimales);
            }

            // Reconstruir la línea y agregarla a lineasActualizadas
            string lineaActualizada;
            for (size_t i = 0; i < segmentos.size(); i++) {
                lineaActualizada += segmentos[i];
                if (i < segmentos.size() - 1) lineaActualizada += ",";
            }
            lineasActualizadas.push_back(lineaActualizada);
            }



            archivoClientes.close();

            // Verificar si el cliente destino fue encontrado y tiene cuenta en la moneda especificada
            if (!clienteEncontrado || !tieneCuentaEnMoneda) {
                cout << "Cliente destino no encontrado o no tiene cuenta en la moneda especificada.\n";
                break;
            }

            // Intentar retirar fondos solo después de verificar que el cliente destino es válido
            esRetiroExitoso = (tipoMoneda == 1) ? clienteActual.retirarDeCuentaColones(montoTransferir) 
                                                : clienteActual.retirarDeCuentaDolares(montoTransferir);
            if (!esRetiroExitoso) {
                cout << "Fondos insuficientes para realizar la transferencia.\n";
                break;
            }

            // Abrir el archivo nuevamente, esta vez para escribir
            archivoClientes.open("./src/clientes.csv", ios::out | ios::trunc);
            if (!archivoClientes.is_open()) {
                cout << "Error al abrir el archivo para actualización.\n";
                break;
            }

            // Escribir todas las líneas actualizadas de vuelta al archivo
            for (const auto& lineaActualizada : lineasActualizadas) {
                archivoClientes << lineaActualizada << "\n";
            }
            archivoClientes.close();

            cout << "Transferencia realizada con éxito.\n";

            // Escritura en el archivo de registro bancario
            std::ofstream archivoRegistro("./src/registro_bancario.txt", std::ios::app);

            if (!archivoRegistro.is_open()) {
            std::cerr << "Error al abrir el archivo.\n";
            return;
            }

            // Escribir los datos del nuevo cliente en el archivo
            archivoRegistro << "\nTipo de operacion: Transferencia\n" << "Cuenta origen: " << id_cliente << "\nCuenta destino: " 
                            << idClienteDestino << "\nMoneda (1 Colones, 2 Dólares): " << tipoMoneda << "\nMonto: " << montoTransferir << "\n";
            archivoRegistro.close();
            break;
        }
            
        case 4:
            cout << "Generando Reporte sobre préstamos propios en el archivo prestamoscli.csv ...\n";
            prestamoSolicitado.guardarPrestamosCliente(id_cliente);
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
    do {
        std::cout << "Seleccione la moneda a solicitar del préstamo:\n";
        std::cout << "0: Solicitar en colones\n";
        std::cout << "1: Solicitar en dólares\n";
        std::cout << "Ingrese su elección: ";

        // Verificar si la entrada es un entero y está dentro del rango correcto
        while (!(std::cin >> moneda) || (moneda != 0 && moneda != 1)) {
            std::cout << "Entrada inválida. Por favor, seleccione 0 o 1: ";
            std::cin.clear(); // Limpiar el estado de error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descartar la entrada incorrecta
        }

    } while (moneda != 0 && moneda != 1);
        long monto;
         do {
        cout << "Seleccione el monto a solicitar:\n";
        if (!(cin >> monto) || monto <= 0) {
            cout << "Error: Por favor ingrese un valor numerico positivo." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        } while (monto <= 0);

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
            cout << "Realizando Abono a préstamo propio...\n";
            prestamoSolicitado.abonarPrestamoPropio(id_cliente);
           
        break;
        case 8:
            // Lógica para abono a préstamo de otra persona
            cout << "Realizando Abono a préstamo de otra persona...\n";
            cout << "Digite el Id del Prestamo a Abonar:\n";
            cin >> idPrestamoAbonar;

            prestamoSolicitado.abonarPrestamoAgeno(id_cliente, idPrestamoAbonar);
            break;
        default:
            cout << "Opción no válida. Por favor, ingrese un número del 1 al 8.\n";
    }
}


void atenderCliente() {
    ifstream archivo("./src/clientes.csv");
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo de clientes." << endl;
        return;
    }

    string linea;
    char delimitador = ',';
    getline(archivo, linea);
    
    string id_cliente;
    cout << "Ingrese el número de identificación: ";
    cin >> id_cliente;

    string nombre, numero_id, tiene_cuenta_colones, tiene_cuenta_dolares, saldo_cuenta_colones, saldo_cuenta_dolares;
    Cliente clienteActual("", "", Cuenta(0.0, ""), Cuenta(0.0, ""));
    bool clienteEncontrado = false;

    while (getline(archivo, linea)) {
        stringstream stream(linea);
        Cliente_struc cliente;

        getline(stream, nombre, delimitador);
        getline(stream, numero_id, delimitador);
        getline(stream, tiene_cuenta_colones, delimitador);
        getline(stream, tiene_cuenta_dolares, delimitador);
        getline(stream, saldo_cuenta_colones, delimitador);
        getline(stream, saldo_cuenta_dolares, delimitador);

        if (numero_id == id_cliente) {
            clienteEncontrado = true;

            double saldo_colones = stod(saldo_cuenta_colones);
            double saldo_dolares = stod(saldo_cuenta_dolares);
            clienteActual = Cliente(nombre, numero_id, Cuenta(saldo_colones, "CRC"), Cuenta(saldo_dolares, "USD"));

            cout << "\nCliente encontrado, bienvenido(a) " << nombre << endl;

            int tipoTransaccion;
            mostrarMenu();


            while (!(cin >> tipoTransaccion) || tipoTransaccion < 1 || tipoTransaccion > 8) {
                cout << "Entrada inválida. Por favor, ingrese un número válido del 1 al 8: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            cout << "Realizando la transacción número: " << tipoTransaccion << "\n";

            realizarTransaccion(tipoTransaccion, id_cliente, clienteActual);
        }
    }
    archivo.close();

    if (!clienteEncontrado) {
        cout << "No se encontró al cliente en el archivo para actualizar." << endl;
        archivo.close();
        atenderCliente();
    } else {
        clienteActual.actualizarArchivo();
    }
}


 
// Se inicia la funcion solicitar, que llama a la clase prestamo y la utiliza.
void solicitarInformacionPrestamos() {
    int num_info_prest;
    do {
        std::cout << "Digite que tipo de opcion deseada\n";
        std::cout << "1. Ver la informacion de prestamos hechos por el banco\n";
        std::cout << "2. Ver la informacion de un prestamo personalizado\n";
        cin >> num_info_prest;
        // Verificar si la entrada es válida
        if (cin.fail() || num_info_prest > 2 || num_info_prest < 1) {
            cin.clear();  // Limpiar el estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  
            cout << "Error: Ingrese una opcion válida." << std::endl;
        } else {
            break;  // Salir del bucle si la entrada es válida
          }
    } while (true);
 
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
                case 1:
                    tipo = Prestamo::PERSONAL;
                    tasaInteresAnual = 8;
                    cantidadCuotas = 36;
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
                case 2:
                    tipo = Prestamo::PERSONAL;
                    tasaInteresAnual = 6.5;
                    cantidadCuotas = 48;
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
                case 1:
                    tipo = Prestamo::PERSONAL;
                    tasaInteresAnual = 3.8;
                    cantidadCuotas = 300;
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
                case 2:
                    tipo = Prestamo::PERSONAL;
                    tasaInteresAnual = 4;
                    cantidadCuotas = 336;
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
                case 1:
                    tipo = Prestamo::PERSONAL;
                    tasaInteresAnual = 5.2;
                    cantidadCuotas = 78;
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
                case 2:
                    tipo = Prestamo::PERSONAL;
                    tasaInteresAnual = 4.5;
                    cantidadCuotas = 90;
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
    ofstream archivo("./src/tabla_prestamo_solicitado.csv");
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
