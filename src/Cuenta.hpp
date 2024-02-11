#ifndef CUENTA_HPP
#define CUENTA_HPP

#include <string>

class Cuenta {
private:
    std::string tipo; // "Dolares" o "Colones"
    double saldo;
    static double tasaDeCambio; // Tasa de cambio de Colones a Dólares

public:
    Cuenta(const std::string& tipo, double saldoInicial);
    static void establecerTasaDeCambio(double tasa);
    void depositar(double cantidad);
    bool retirar(double cantidad);
    bool transaccion(double cantidad, Cuenta &cuentaDestino);
    double consultarSaldo() const;
    std::string obtenerTipo() const;
    void convertirSaldo(const std::string& nuevaMoneda);
};

#endif // CUENTA_HPP