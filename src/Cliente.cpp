#include "Cliente.hpp"
#include <iostream>
#include <limits>

// Constructor
Cliente::Cliente(const std::string& nombre, const std::string& identificacion,
                 const Cuenta& cuentaColones, const Cuenta& cuentaDolares)
    : nombre(nombre), identificacion(identificacion), 
      cuentaColones(cuentaColones), cuentaDolares(cuentaDolares) {}

// Métodos para depositar en cuentas ya sea en colones o en dolares
void Cliente::depositarEnCuentaColones(double cantidad) {
    if (cantidad > 0) {
        cuentaColones.depositar(cantidad);
        std::cout << "Depósito realizado con éxito en cuenta de colones." << std::endl;
    } else {
        std::cerr << "Error: La cantidad a depositar no puede ser negativa." << std::endl;
    }
}

void Cliente::depositarEnCuentaDolares(double cantidad) {
    if (cantidad > 0) {
        cuentaDolares.depositar(cantidad);
        std::cout << "Depósito realizado con éxito en cuenta de dólares." << std::endl;
    } else {
        std::cerr << "Error: La cantidad a depositar no puede ser negativa." << std::endl;
    }
}

// Métodos para retirar de cuentas
bool Cliente::retirarDeCuentaColones(double cantidad) {
    if (cantidad > 0) {
        if (cuentaColones.retirar(cantidad)) {
            std::cout << "Retiro realizado con éxito de cuenta de colones." << std::endl;
            return true;
        } else {
            std::cout << "Error: Saldo insuficiente para el retiro." << std::endl;
        }
    } else {
        std::cerr << "Error: La cantidad a retirar debe ser positiva." << std::endl;
    }
    return false;
}

bool Cliente::retirarDeCuentaDolares(double cantidad) {
    if (cantidad > 0) {
        if (cuentaDolares.retirar(cantidad)) {
            std::cout << "Retiro realizado con éxito de cuenta de dólares." << std::endl;
            return true;
        } else {
            std::cout << "Error: Saldo insuficiente para el retiro." << std::endl;
        }
    } else {
        std::cerr << "Error: La cantidad a retirar debe ser positiva." << std::endl;
    }
    return false;
}

// Método para solicitar préstamos
void Cliente::solicitarPrestamo(double monto) {
    if (monto > 0) {
        // Aquí se añade lógica para solicitar y aprobar el préstamo
        std::cout << "Préstamo solicitado con éxito, pendiente de aprobación." << std::endl;
    } else {
        std::cerr << "Error: El monto del préstamo debe ser positivo." << std::endl;
    }
}

// Método para mostrar información del cliente
void Cliente::mostrarInformacion() const {
    std::cout << "Información del Cliente:" << std::endl;
    std::cout << "Nombre: " << nombre << std::endl;
    std::cout << "Identificación: " << identificacion << std::endl;
    std::cout << "Saldo en cuenta de colones: " << cuentaColones.consultarSaldo() << std::endl;
    std::cout << "Saldo en cuenta de dólares: " << cuentaDolares.consultarSaldo() << std::endl;
    // Mostrar información de préstamos si es necesario ........... workinggg
}
