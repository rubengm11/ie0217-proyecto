#include "CDP.hpp"

CDP::CDP(double monto, int plazo, double interes, const std::string& id_usuario)
    : monto(monto), plazo(plazo), interes(interes), id_usuario(id_usuario) {}

void CDP::crearCDP() {
    std::ofstream archivo("./src/cdp.csv", std::ios::app);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo.\n";
        return;
    }

    archivo << id_usuario << "," << monto << "," << plazo << "," << interes << "\n";

    std::cout << "Nuevo CDP creado:\n";
    std::cout << "ID Usuario: " << id_usuario << "\n";
    std::cout << "Monto: " << monto << "\n";
    std::cout << "Plazo: " << plazo << " meses\n";
    std::cout << "Tasa de interés: " << interes << "%\n";

    archivo.close();
}

void CDP::eliminarCDP() {
    // Implementación para eliminar un CDP
    // Deberías implementar la lógica para leer el archivo, buscar el CDP y eliminar la línea correspondiente.
    // Ten en cuenta que este ejemplo asume un formato simple y podría necesitar mejoras para manejar casos más complejos.
}
