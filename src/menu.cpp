#include <iostream>
#include "funciones.hpp"
#include <limits>

using namespace std;

int main() {
    int opcion;

    do {
        cout << "\nMenu Principal:\n"
             << "1. Atender a un cliente\n"
             << "2. Solicitar informacion general sobre prestamos\n"
             << "3. Agregar nuevo cliente\n"
             << "0. Salir\n"
             << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                atenderCliente();
                break;
            case 2:
                solicitarInformacionPrestamos();
                break;
            case 3:
                agregarCliente();
                break;
            case 0:
                cout << "Saliendo del programa. ¡Hasta luego!\n";
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo.\n";
                cin.clear();  // Limpiar el estado de error
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Descartar la entrada incorrecta
        }
    } while (opcion != 0);

    return 0;
}

