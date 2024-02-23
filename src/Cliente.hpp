/**
 * @file Cliente.hpp
 * @brief Declaración de la clase Cliente
 */

#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include "Cuenta.hpp"
#include <string>

/**
 * @class Cliente
 * @brief Clase que representa a un cliente del banco
 */
class Cliente {
public:
    std::string nombre; /**< Nombre del cliente */
    std::string identificacion; /**< Número de identificación del cliente */
    Cuenta cuentaColones; /**< Cuenta en colones del cliente */
    Cuenta cuentaDolares; /**< Cuenta en dólares del cliente */

    /**
     * @brief Constructor de la clase Cliente
     * @param nombre Nombre del cliente
     * @param identificacion Número de identificación del cliente
     * @param cuentaColones Cuenta en colones del cliente
     * @param cuentaDolares Cuenta en dólares del cliente
     */
    Cliente(const std::string& nombre, const std::string& identificacion,
            const Cuenta& cuentaColones, const Cuenta& cuentaDolares);

    /**
     * @brief Método para mostrar información del cliente
     */
    void mostrarInformacion() const;

    /**
     * @brief Método para depositar en la cuenta de colones del cliente
     * @param cantidad Cantidad a depositar
     */
    void depositarEnCuentaColones(double cantidad);

    /**
     * @brief Método para depositar en la cuenta de dólares del cliente
     * @param cantidad Cantidad a depositar
     */
    void depositarEnCuentaDolares(double cantidad);

    /**
     * @brief Método para retirar de la cuenta de colones del cliente
     * @param cantidad Cantidad a retirar
     * @return True si el retiro fue exitoso, False si hubo un error
     */
    bool retirarDeCuentaColones(double cantidad);

    /**
     * @brief Método para retirar de la cuenta de dólares del cliente
     * @param cantidad Cantidad a retirar
     * @return True si el retiro fue exitoso, False si hubo un error
     */
    bool retirarDeCuentaDolares(double cantidad);

    /**
     * @brief Método para solicitar un préstamo
     * @param monto Monto del préstamo solicitado
     */
    void solicitarPrestamo(double monto);

    /**
     * @brief Método para actualizar el archivo CSV después de cada transacción
     */
    void actualizarArchivo();
};

#endif // CLIENTE_HPP

