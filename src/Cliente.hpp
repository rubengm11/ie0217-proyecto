#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include "Cuenta.hpp" // Asegúrate de que la ruta sea correcta según tu estructura de proyecto
#include <string>

class Cliente {
public:
    std::string nombre;
    std::string identificacion;
    Cuenta cuentaColones;
    Cuenta cuentaDolares;

    // Constructor
    Cliente(const std::string& nombre, const std::string& identificacion,
            const Cuenta& cuentaColones, const Cuenta& cuentaDolares);

    // Método para mostrar información del cliente
    void mostrarInformacion() const;

    // Métodos para depositar en cuentas
    void depositarEnCuentaColones(double cantidad);
    void depositarEnCuentaDolares(double cantidad);

    // Métodos para retirar de cuentas
    bool retirarDeCuentaColones(double cantidad);
    bool retirarDeCuentaDolares(double cantidad);

    // Método para solicitar préstamos
    void solicitarPrestamo(double monto);

    // Método para actualizar el archivo CSV después de cada transacción
    void actualizarArchivo();
};

#endif // CLIENTE_HPP
