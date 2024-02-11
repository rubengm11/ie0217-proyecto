#include <iostream>
#include "funciones.hpp"
#include <limits>

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
}

void solicitarInformacionPrestamos() {
    cout << "Imprimir informacion de prestamos";
}
