/**
 * @file CDP.cpp
 * @brief Implementación de la clase CDP (Certificado de Depósito a Plazo)
 */

#include "CDP.hpp"

/**
 * @brief Constructor de la clase CDP
 * @param monto Monto del certificado
 * @param plazo Plazo en meses del certificado
 * @param interes Tasa de interés del certificado
 * @param id_usuario Identificación del usuario asociado al certificado
 * @param moneda Tipo de moneda del certificado (true para dólares, false para colones)
 */
CDP::CDP(double monto, int plazo, double interes, const std::string& id_usuario, bool moneda)
    : monto(monto), plazo(plazo), interes(interes), id_usuario(id_usuario), moneda(moneda) {}

/**
 * @brief Método para crear un nuevo Certificado de Depósito a Plazo (CDP)
 */
void CDP::crearCDP() {
    // Abrir el archivo en modo apendizaje para agregar el nuevo CDP
    std::ofstream archivo("./src/cdp.csv", std::ios::app);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo.\n";
        return;
    }

    // Escribir los datos del nuevo CDP en el archivo
    archivo << id_usuario << "," << moneda << "," << monto << "," << plazo << "," << interes << "\n";

    std::cout << "Nuevo CDP creado:\n";
    std::cout << "ID Usuario: " << id_usuario << "\n";
    std::cout << "Moneda: " << moneda << std::endl;
    std::cout << "Monto: " << monto << "\n";
    std::cout << "Plazo: " << plazo << " meses\n";
    std::cout << "Tasa de interés: " << interes << "%\n";

    // Cerrar el archivo
    archivo.close();

    // Abrir el archivo de registro en modo apendizaje para agregar la información del nuevo CDP
    std::ofstream archivoRegistro("./src/registro_bancario.txt", std::ios::app);
    if (!archivoRegistro.is_open()) {
        std::cerr << "Error al abrir el archivo de registro.\n";
        return;
    }

    // Escribir los datos del nuevo CDP en el archivo de registro
    archivoRegistro << "\nTipo de operación: Creación de Certificado de Depósito a Plazo\n"
                    << "Identificación: " << id_usuario << "\nMoneda: " << moneda << "\nMonto: "
                    << monto << "\nPlazo: " << plazo << "\nInterés: " << interes << "\n";

    // Cerrar el archivo de registro
    archivoRegistro.close();
}
