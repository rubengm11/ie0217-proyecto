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

    std::ofstream archivoRegistro("./src/registro_bancario.txt", std::ios::app);

    if (!archivoRegistro.is_open()) {
        std::cerr << "Error al abrir el archivo.\n";
        return;
    }

    // Escribir los datos del nuevo cliente en el archivo
    archivoRegistro << "\nTipo de operacion: Creacion de Certificado de deposito a plazo\n" << "Identificacion: " << id_usuario << "\nMoneda: " << moneda<< "\nMonto: "
                    << monto << "\nPlazo: " << plazo << "\nInteres: " << interes << "\n";

    archivoRegistro.close();



}