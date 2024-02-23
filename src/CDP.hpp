/**
 * @file CDP.hpp
 * @brief Declaración de la clase CDP (Certificado de Depósito a Plazo)
 */

#ifndef CDP_HPP
#define CDP_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

/**
 * @class CDP
 * @brief Clase que representa un Certificado de Depósito a Plazo (CDP)
 */
class CDP {
public:
    /**
     * @brief Constructor de la clase CDP
     * @param monto Monto del certificado
     * @param plazo Plazo en meses del certificado
     * @param interes Tasa de interés del certificado
     * @param id_usuario Identificación del usuario asociado al certificado
     * @param moneda Tipo de moneda del certificado (true para dólares, false para colones)
     */
    CDP(double monto, int plazo, double interes, const std::string& id_usuario, bool moneda);

    /**
     * @brief Método para crear un nuevo Certificado de Depósito a Plazo (CDP)
     */
    void crearCDP();

private:
    // Atributos
    double monto; /**< Monto del certificado */
    int plazo;    /**< Plazo en meses del certificado */
    double interes; /**< Tasa de interés del certificado */
    std::string id_usuario; /**< Identificación del usuario asociado al certificado */
    bool moneda; /**< Tipo de moneda del certificado (true para dólares, false para colones) */
};

#endif // CDP_HPP
