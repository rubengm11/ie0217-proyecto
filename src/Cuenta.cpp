#include "Cuenta.hpp"
#include <iostream>
#include <limits>

// Definición e inicialización de la variable estática para la tasa de cambio
double Cuenta::tasaDeCambio = 0.0;

// Constructor: Inicializa una cuenta con un tipo (ejemplo: "Dolares" o "Colones") y saldo inicial
Cuenta::Cuenta(const std::string& tipo, double saldoInicial) : tipo(tipo), saldo(saldoInicial) {}

// Método para establecer la tasa de cambio; valida que la tasa sea positiva antes de actualizarla
void Cuenta::establecerTasaDeCambio(double tasa) {
    if (tasa > 0) {
        tasaDeCambio = tasa;
        std::cout << "Tasa de cambio actualizada a: " << tasa << std::endl;
    } else {
        std::cout << "Error: La tasa de cambio debe ser positiva." << std::endl;
    }
}

// Método para depositar dinero en la cuenta; valida que el monto a depositar sea positivo
void Cuenta::depositar(double cantidad) {
    if (cantidad > 0) {
        saldo += cantidad;
        std::cout << "Depósito realizado con éxito. Nuevo saldo: " << saldo << " " << tipo << "." << std::endl;
    } else {
        std::cout << "Error: El monto a depositar debe ser positivo." << std::endl;
    }
}

// Método para retirar dinero de la cuenta; valida que la cantidad a retirar sea positiva y que haya saldo suficiente
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

// Método para realizar una transacción de esta cuenta a otra; realiza el retiro y luego el depósito en la cuenta destino
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

// Método para consultar el saldo actual de la cuenta
double Cuenta::consultarSaldo() const {
    return saldo;
}

// Método para obtener el tipo de moneda de la cuenta
std::string Cuenta::obtenerTipo() const {
    return tipo;
}

// Método para convertir el saldo de la cuenta entre dos monedas, utilizando la tasa de cambio establecida
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
