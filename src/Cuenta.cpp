#include "Cuenta.hpp"
#include <iostream>
#include <limits>

// Inicialización de la variable estática
double Cuenta::tasaDeCambio = 0.0;

Cuenta::Cuenta(const std::string& tipo, double saldoInicial) : tipo(tipo), saldo(saldoInicial) {}

void Cuenta::establecerTasaDeCambio(double tasa) {
    if (tasa > 0) {
        tasaDeCambio = tasa;
        std::cout << "Tasa de cambio actualizada a: " << tasa << std::endl;
    } else {
        std::cout << "Error: La tasa de cambio debe ser positiva." << std::endl;
    }
}

void Cuenta::depositar(double cantidad) {
    if (cantidad > 0) {
        saldo += cantidad;
        std::cout << "Depósito realizado con éxito. Nuevo saldo: " << saldo << " " << tipo << "." << std::endl;
    } else {
        std::cout << "Error: El monto a depositar debe ser positivo." << std::endl;
    }
}

bool Cuenta::retirar(double cantidad) {
    if (cantidad <= 0) {
        std::cout << "Error: La cantidad a retirar debe ser positiva." << std::endl;
        return false;
    } else if (cantidad > saldo) {
        std::cout << "Error: Saldo insuficiente para el retiro." << std::endl;
        return false;
    }
    saldo -= cantidad;
    std::cout << "Retiro realizado con éxito. Saldo restante: " << saldo << " " << tipo << "." << std::endl;
    return true;
}

bool Cuenta::transaccion(double cantidad, Cuenta &cuentaDestino) {
    if (cantidad <= 0) {
        std::cout << "Error: La cantidad de la transacción debe ser positiva." << std::endl;
        return false;
    }
    if (retirar(cantidad)) {
        cuentaDestino.depositar(cantidad);
        std::cout << "Transacción realizada con éxito." << std::endl;
        return true;
    }
    std::cout << "Error: Transacción fallida." << std::endl;
    return false;
}

double Cuenta::consultarSaldo() const {
    return saldo;
}

std::string Cuenta::obtenerTipo() const {
    return tipo;
}

void Cuenta::convertirSaldo(const std::string& nuevaMoneda) {
    if (tasaDeCambio <= 0) {
        std::cout << "Error: La tasa de cambio no ha sido establecida." << std::endl;
        return;
    }
    if (tipo != nuevaMoneda) {
        if (nuevaMoneda == "Dolares" && tipo == "Colones") {
            saldo /= tasaDeCambio; // Convierte de colones a dólares
            tipo = "Dolares";
        } else if (nuevaMoneda == "Colones" && tipo == "Dolares") {
            saldo *= tasaDeCambio; // Convierte de dólares a colones
            tipo = "Colones";
        }
        std::cout << "Conversión realizada. Nuevo saldo: " << saldo << " " << tipo << "." << std::endl;
    } else {
        std::cout << "La cuenta ya está en " << nuevaMoneda << "." << std::endl;
    }
}