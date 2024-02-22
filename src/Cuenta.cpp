#include "Cuenta.hpp"
#include <iostream>
#include <limits>

// Inicialización de la variable estática para la tasa de cambio
double Cuenta::tasaDeCambio = 0.0;

// Constructor
// Implementación del constructor
Cuenta::Cuenta(double saldoInicial, const std::string& tipoMoneda) : saldo(saldoInicial), tipo(tipoMoneda) {}

// Establecer la tasa de cambio
void Cuenta::establecerTasaDeCambio(double tasa) {
    if (tasa <= 0) {
        std::cerr << "Error: La tasa de cambio debe ser positiva." << std::endl;
        return;
    }
    tasaDeCambio = tasa;
    std::cout << "Tasa de cambio actualizada a: " << tasa << std::endl;
}

// Depositar dinero
void Cuenta::depositar(double cantidad) {
    if (cantidad <= 0) {
        std::cerr << "Error: El monto a depositar debe ser positivo." << std::endl;
        return;
    }
    saldo += cantidad;
    std::cout << "Depósito realizado con éxito. Nuevo saldo: " << saldo << " " << tipo << "." << std::endl;
    
}

// Retirar dinero
bool Cuenta::retirar(double cantidad) {
    if (cantidad <= 0) {
        std::cerr << "Error: La cantidad a retirar debe ser positiva." << std::endl;
        return false;
    }
    if (cantidad > saldo) {
        std::cerr << "Error: Saldo insuficiente para el retiro." << std::endl;
        return false;
    }
    saldo -= cantidad;
    std::cout << "Retiro realizado con éxito. Saldo restante: " << saldo << " " << tipo << "." << std::endl;
    return true;
}

// Transacción entre cuentas
bool Cuenta::transaccion(double cantidad, Cuenta &cuentaDestino) {
    if (!retirar(cantidad)) return false;
    cuentaDestino.depositar(cantidad);
    std::cout << "Transacción realizada con éxito." << std::endl;
    return true;
    
}

// Consultar saldo
double Cuenta::consultarSaldo() const {
    return saldo;
}

// Obtener tipo de moneda
std::string Cuenta::obtenerTipo() const {
    return tipo;
}

// Convertir saldo entre monedas
void Cuenta::convertirSaldo(const std::string& nuevaMoneda) {
    if (tasaDeCambio <= 0) {
        std::cerr << "Error: La tasa de cambio no ha sido establecida." << std::endl;
        return;
    }
    if (tipo == nuevaMoneda) {
        std::cout << "La cuenta ya está en " << nuevaMoneda << "." << std::endl;
        return;
    }
    saldo = (nuevaMoneda == "Dolares" && tipo == "Colones") ? saldo / tasaDeCambio : saldo * tasaDeCambio;
    tipo = nuevaMoneda;
    std::cout << "Conversión realizada. Nuevo saldo: " << saldo << " " << tipo << "." << std::endl;
}



