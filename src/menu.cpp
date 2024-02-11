#include <iostream>
#include "funciones.hpp"
#include <limits>

using namespace std;

int main() {
    int opcion;

    do {
        cout << "\nMenú Principal:\n"
             << "1. Atender a un cliente\n"
             << "2. Solicitar información general sobre préstamos\n"
             << "0. Salir\n"
             << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                atenderCliente();
                break;
            case 2:
                solicitarInformacionPrestamos();
                break;
            case 0:
                cout << "Saliendo del programa. ¡Hasta luego!\n";
                break;
            default:
                cout << "Opción no válida. Intente de nuevo.\n";
                cin.clear();  // Limpiar el estado de error
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Descartar la entrada incorrecta
        }
    } while (opcion != 0);

    return 0;
}

