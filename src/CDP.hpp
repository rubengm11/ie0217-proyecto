#ifndef CDP_HPP
#define CDP_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class CDP {
public:
    // Constructor
    CDP(double monto, int plazo, double interes, const std::string& id_usuario);

    // Métodos
    void crearCDP();
    void eliminarCDP();

private:
    // Atributos
    double monto;
    int plazo;
    double interes;
    std::string id_usuario;
};

#endif

