#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include "Cuenta.hpp"
#include <string>
#include <vector>

class Cliente {
private:
    std::string nombre;
    std::string identificacion;
    Cuenta cuentaColones;
    Cuenta cuentaDolares;
    std::vector<double> prestamos;

public:
    // Constructor
    Cliente(const std::string& nombre, const std::string& identificacion, const Cuenta& cuentaColones, const Cuenta& cuentaDolares);

    // Métodos
    void depositarEnCuentaColones(double cantidad);
    void depositarEnCuentaDolares(double cantidad);
    bool retirarDeCuentaColones(double cantidad);
    bool retirarDeCuentaDolares(double cantidad);
    void solicitarPrestamo(double monto);

    // Métodos para mostrar información (opcional)
    void mostrarInformacion() const;
};

#endif