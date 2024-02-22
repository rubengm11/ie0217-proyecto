#ifndef CUENTA_HPP
#define CUENTA_HPP

#include <string>

class Cuenta {
private:
    std::string tipo;
    double saldo;
    static double tasaDeCambio;

public:
    // Constructor
    Cuenta(double saldoInicial, const std::string& tipoMoneda);

    // Métodos
    void establecerTasaDeCambio(double tasa);
    void depositar(double cantidad);
    bool retirar(double cantidad);
    bool transaccion(double cantidad, Cuenta& cuentaDestino);
    double consultarSaldo() const;
    std::string obtenerTipo() const;
    void convertirSaldo(const std::string& nuevaMoneda);
};

#endif // CUENTA_HPP

