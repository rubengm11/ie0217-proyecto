/**
 * @file Cuenta.hpp
 * @brief Declaración de la clase Cuenta
 */

#ifndef CUENTA_HPP
#define CUENTA_HPP

#include <string>

/**
 * @class Cuenta
 * @brief Clase que representa una cuenta bancaria
 */
class Cuenta {
private:
    std::string tipo; /**< Tipo de moneda de la cuenta */
    double saldo; /**< Saldo actual de la cuenta */
    static double tasaDeCambio; /**< Tasa de cambio para convertir entre monedas */

public:
    /**
     * @brief Constructor de la clase Cuenta
     * @param saldoInicial Saldo inicial de la cuenta
     * @param tipoMoneda Tipo de moneda de la cuenta
     */
    Cuenta(double saldoInicial, const std::string& tipoMoneda);

    /**
     * @brief Establecer la tasa de cambio para convertir entre monedas
     * @param tasa Tasa de cambio a establecer
     */
    void establecerTasaDeCambio(double tasa);

    /**
     * @brief Depositar dinero en la cuenta
     * @param cantidad Cantidad a depositar
     */
    void depositar(double cantidad);

    /**
     * @brief Retirar dinero de la cuenta
     * @param cantidad Cantidad a retirar
     * @return True si el retiro fue exitoso, False si hubo un error
     */
    bool retirar(double cantidad);

    /**
     * @brief Realizar una transacción entre cuentas
     * @param cantidad Cantidad a transferir
     * @param cuentaDestino Cuenta de destino para la transacción
     * @return True si la transacción fue exitosa, False si hubo un error
     */
    bool transaccion(double cantidad, Cuenta& cuentaDestino);

    /**
     * @brief Consultar el saldo de la cuenta
     * @return Saldo actual de la cuenta
     */
    double consultarSaldo() const;

    /**
     * @brief Obtener el tipo de moneda de la cuenta
     * @return Tipo de moneda de la cuenta
     */
    std::string obtenerTipo() const;

    /**
     * @brief Convertir el saldo entre monedas
     * @param nuevaMoneda Tipo de moneda al que se desea convertir el saldo
     */
    void convertirSaldo(const std::string& nuevaMoneda);
};

#endif // CUENTA_HPP
