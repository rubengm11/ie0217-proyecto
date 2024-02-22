#include "Cliente.hpp"
#include <iostream>
#include <fstream>
#include <limits>
#include <sstream>
#include <vector>
#include <string>


// Constructor
Cliente::Cliente(const std::string& nombre, const std::string& identificacion,
                 const Cuenta& cuentaColones, const Cuenta& cuentaDolares)
    : nombre(nombre), identificacion(identificacion), 
      cuentaColones(cuentaColones), cuentaDolares(cuentaDolares) {}

// Métodos para depositar en cuentas ya sea en colones o en dólares
void Cliente::depositarEnCuentaColones(double cantidad) {
    if (cantidad > 0) {
        cuentaColones.depositar(cantidad);
        std::cout << "Depósito realizado con éxito en cuenta de colones.\n";
        // Mostrar el nuevo saldo
        std::cout << "Nuevo saldo en cuenta de colones: " << cuentaColones.consultarSaldo() << " CRC.\n";
        actualizarArchivo(); // Llamar a la función para actualizar el archivo después de la transacción
    } else {
        std::cerr << "Error: La cantidad a depositar no puede ser negativa.\n";
    }
}

void Cliente::depositarEnCuentaDolares(double cantidad) {
    if (cantidad > 0) {
        cuentaDolares.depositar(cantidad);
        std::cout << "Depósito realizado con éxito en cuenta de dólares.\n";
        // Mostrar el nuevo saldo
        std::cout << "Nuevo saldo en cuenta de dólares: " << cuentaDolares.consultarSaldo() << " USD.\n";
        actualizarArchivo(); // Llamar a la función para actualizar el archivo después de la transacción
    } else {
        std::cerr << "Error: La cantidad a depositar no puede ser negativa.\n";
    }
}

// Métodos para retirar de cuentas
bool Cliente::retirarDeCuentaColones(double cantidad) {
    if (cantidad > 0) {
        if (cuentaColones.retirar(cantidad)) {
            std::cout << "Retiro realizado con éxito de cuenta de colones.\n";
            // Mostrar el nuevo saldo
            std::cout << "Nuevo saldo en cuenta de colones: " << cuentaColones.consultarSaldo() << " CRC.\n";
            actualizarArchivo(); // Llamar a la función para actualizar el archivo después de la transacción
            return true;
        } else {
            std::cout << "Error: Saldo insuficiente para el retiro.\n";
        }
    } else {
        std::cerr << "Error: La cantidad a retirar debe ser positiva.\n";
    }
    return false;
}

bool Cliente::retirarDeCuentaDolares(double cantidad) {
    if (cantidad > 0) {
        if (cuentaDolares.retirar(cantidad)) {
            std::cout << "Retiro realizado con éxito de cuenta de dólares.\n";
            // Mostrar el nuevo saldo
            std::cout << "Nuevo saldo en cuenta de dólares: " << cuentaDolares.consultarSaldo() << " USD.\n";
            actualizarArchivo(); // Llamar a la función para actualizar el archivo después de la transacción
            return true;
        } else {
            std::cout << "Error: Saldo insuficiente para el retiro.\n";
        }
    } else {
        std::cerr << "Error: La cantidad a retirar debe ser positiva.\n";
    }
    return false;
}

// Método para solicitar préstamos
void Cliente::solicitarPrestamo(double monto) {
    if (monto > 0) {
        // Aquí se añade lógica para solicitar y aprobar el préstamo
        std::cout << "Préstamo solicitado con éxito, pendiente de aprobación." << std::endl;
        actualizarArchivo(); // Llamar a la función para actualizar el archivo después de la transacción
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

using namespace std;


void Cliente::actualizarArchivo() {
    std::vector<std::string> lineas;
    std::ifstream archivoLectura("./src/clientes.csv");
    std::ofstream archivoEscritura;
    std::string linea;
    bool clienteEncontrado = false;

    while (getline(archivoLectura, linea)) {
        std::stringstream ss(linea);
        std::string segmento;
        std::vector<std::string> segmentos;

        while(getline(ss, segmento, ',')) {
            segmentos.push_back(segmento);
        }

        // Asegúrate de que tienes suficientes segmentos para un cliente
        if (segmentos.size() >= 6 && segmentos[1] == this->identificacion) {
            // Reconstruye la línea manteniendo todos los campos excepto los saldos actualizados
            linea = segmentos[0] + "," + segmentos[1] + "," + segmentos[2] + "," + segmentos[3] + "," +
                    std::to_string(static_cast<int>(this->cuentaColones.consultarSaldo())) + "," +
                    std::to_string(static_cast<int>(this->cuentaDolares.consultarSaldo()));
            clienteEncontrado = true;
        }
        lineas.push_back(linea);
    }
    archivoLectura.close();

    if (clienteEncontrado) {
        archivoEscritura.open("./src/clientes.csv", std::ofstream::trunc);
        for (const auto& actualizada : lineas) {
            archivoEscritura << actualizada << std::endl;
        }
        archivoEscritura.close();
    } else {
        std::cerr << "No se encontró al cliente en el archivo para actualizar." << std::endl;
    }
}


