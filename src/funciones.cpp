#include <iostream>
#include "funciones.hpp"
#include <limits>
#include "CDP.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
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
            exit(0);
        }
    } else {
        cout << "Número de identificación no válido.\n";
        exit(0);
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

void solicitarInformacionPrestamos() {
    cout << "Imprimir informacion de prestamos";
}
