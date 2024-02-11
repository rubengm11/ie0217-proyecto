#include "Cliente.hpp"
#include <iostream>
#include <limits>

// Constructor
Cliente::Cliente(const std::string& nombre, const std::string& identificacion, const Cuenta& cuentaColones, const Cuenta& cuentaDolares)
: nombre(nombre), identificacion(identificacion), cuentaColones(cuentaColones), cuentaDolares(cuentaDolares) {}

// Método para depositar en cuenta de colones, asegurándose de que la cantidad no sea negativa
void Cliente::depositarEnCuentaColones(double cantidad) {
    if (cantidad > 0) {
        cuentaColones.depositar(cantidad);
    } else {
        std::cerr << "Error: La cantidad a depositar no puede ser negativa." << std::endl;
    }
}

// Método para depositar en cuenta de dólares, con validación similar
void Cliente::depositarEnCuentaDolares(double cantidad) {
    if (cantidad > 0) {
        cuentaDolares.depositar(cantidad);
    } else {
        std::cerr << "Error: La cantidad a depositar no puede ser negativa." << std::endl;
    }
}

// Método para retirar de cuenta de colones, validando que la cantidad sea positiva y no exceda el saldo
bool Cliente::retirarDeCuentaColones(double cantidad) {
    if (cantidad <= 0) {
        std::cerr << "Error: La cantidad a retirar debe ser positiva." << std::endl;
        return false;
    }
    return cuentaColones.retirar(cantidad);
}

// Método similar para la cuenta en dólares
bool Cliente::retirarDeCuentaDolares(double cantidad) {
    if (cantidad <= 0) {
        std::cerr << "Error: La cantidad a retirar debe ser positiva." << std::endl;
        return false;
    }
    return cuentaDolares.retirar(cantidad);
}

// Ejemplo de método para solicitar un préstamo, con validación básica
void Cliente::solicitarPrestamo(double monto) {
    if (monto > 0) {
        // Aquí podrías implementar lógica adicional para determinar si el préstamo puede ser aprobado
        prestamos.push_back(monto);
        std::cout << "Préstamo solicitado por " << monto << ". Pendiente de aprobación." << std::endl;
    } else {
        std::cerr << "Error: El monto del préstamo debe ser positivo." << std::endl;
    }
}

// Método para mostrar información del cliente
void Cliente::mostrarInformacion() const {
    std::cout << "Cliente: " << nombre << " [" << identificacion << "]" << std::endl;
    // Asumiendo que cuentaColones y cuentaDolares tienen un método 'consultarSaldo'
    std::cout << "Cuenta en Colones - Saldo: " << cuentaColones.consultarSaldo() << std::endl;
    std::cout << "Cuenta en Dólares - Saldo: " << cuentaDolares.consultarSaldo() << std::endl;
    std::cout << "Préstamos asociados: " << std::endl;
    for (auto& prestamo : prestamos) {
        std::cout << "- " << prestamo << std::endl;
    }
}