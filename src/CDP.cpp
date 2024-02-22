#include "CDP.hpp"

CDP::CDP(double monto, int plazo, double interes, const std::string& id_usuario, bool moneda)
    : monto(monto), plazo(plazo), interes(interes), id_usuario(id_usuario), moneda(moneda) {}

void CDP::crearCDP() {
    std::ofstream archivo("./src/cdp.csv", std::ios::app);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo.\n";
        return;
    }

    archivo << id_usuario << "," << moneda << "," << monto << "," << plazo << "," << interes << "\n";

    std::cout << "Nuevo CDP creado:\n";
    std::cout << "ID Usuario: " << id_usuario << "\n";
    std::cout << "Moneda: " << moneda << std::endl;
    std::cout << "Monto: " << monto << "\n";
    std::cout << "Plazo: " << plazo << " meses\n";
    std::cout << "Tasa de interés: " << interes << "%\n";

    archivo.close();
}

