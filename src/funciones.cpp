#include <iostream>
#include "funciones.hpp"
#include <limits>
#include "CDP.hpp"

using namespace std;

void atenderCliente() {
    int idCliente;
    cout << "Ingrese el número de identificación del cliente: ";
    while (!(cin >> idCliente)) {
        cout << "Entrada inválida. Por favor, ingrese un número válido: ";
        cin.clear();  // Limpiar el estado de error
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Descartar la entrada incorrecta
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

    cout << "Atendiendo al cliente con ID: " << idCliente << "\n";
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
