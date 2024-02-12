#include "Prestamo.hpp"
#include <cmath>
#include <iostream>

Prestamo::Prestamo(Tipo tipo, double tasaInteresAnual, int cantidadCuotas, double montoPrestamo)
    : tipoPrestamo(tipo), tasaInteresAnual(tasaInteresAnual), cantidadCuotas(cantidadCuotas), montoPrestamo(montoPrestamo) {}

double Prestamo::calcularCuotaMensual() {
    double tasaInteresMensual = tasaInteresAnual / 12 / 100;
    double cuotaMensual = (montoPrestamo * tasaInteresMensual) / (1 - pow(1 + tasaInteresMensual, -cantidadCuotas));
    return cuotaMensual;
}
int main() {
    // Pedir al usuario los datos del préstamo
    int tipo;
    std::cout << "Tipo de prestamo (0: Personal, 1: Hipotecario, 2: Prendario): ";
    std::cin >> tipo;

    double tasaInteresAnual;
    std::cout << "Tasa de interes anual (%): ";
    std::cin >> tasaInteresAnual;

    int cantidadCuotas;
    std::cout << "Cantidad de cuotas (meses): ";
    std::cin >> cantidadCuotas;

    double montoPrestamo;
    std::cout << "Monto del prestamo: ";
    std::cin >> montoPrestamo;

    // Crear objeto Prestamo con los datos ingresados por el usuario
    Prestamo::Tipo tipoPrestamo;
    if (tipo == 0) {
        tipoPrestamo = Prestamo::PERSONAL;
    } else if (tipo == 1) {
        tipoPrestamo = Prestamo::HIPOTECARIO;
    } else if (tipo == 2) {
        tipoPrestamo = Prestamo::PRENDARIO;
    } else {
        std::cerr << "Tipo de prestamo invalido\n";
        return 1;
    }

    Prestamo prestamo(tipoPrestamo, tasaInteresAnual, cantidadCuotas, montoPrestamo);

    // Calcular la cuota mensual y mostrarla
    double cuotaMensual = prestamo.calcularCuotaMensual();
    std::cout << "La cuota mensual del prestamo es: $" << cuotaMensual << std::endl;

    return 0;
}