#include "Prestamo.hpp"
#include <cmath>
#include <iostream>
#include <iomanip>

Prestamo::Prestamo(Tipo tipo, double tasaInteresAnual, int cantidadCuotas, double montoPrestamo)
    : tipoPrestamo(tipo), tasaInteresAnual(tasaInteresAnual), cantidadCuotas(cantidadCuotas), montoPrestamo(montoPrestamo) {}

double Prestamo::calcularCuotaMensual() {
    double tasaInteresMensual = tasaInteresAnual / 12 / 100;
    double cuotaMensual = (montoPrestamo * tasaInteresMensual) / (1 - pow(1 + tasaInteresMensual, -cantidadCuotas));
    return cuotaMensual;
}

int main() {
    // Se pide al usuario los datos del préstamo
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

    // Se crea el objeto Prestamo con los datos ingresados por el usuario
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

    // Se imprime la tabla 
    std::cout << std::setw(8) << "Mes" << std::setw(15) << "Cuota Mensual" << std::setw(15) << "Intereses" << std::setw(15) << "Deuda" << std::setw(20) << "Montante Restante\n";
    std::cout << std::string(70, '-') << std::endl;

    // Se calculan e imprimen los valores de las cuotas en pantalla
    double deuda = montoPrestamo;
    for (int i = 1; i <= cantidadCuotas; ++i) {
        double cuotaMensual = prestamo.calcularCuotaMensual();
        double intereses = deuda * (tasaInteresAnual / 12 / 100);
        double amortizacion = cuotaMensual - intereses;
        deuda -= amortizacion;

        std::cout << std::setw(8) << i << std::fixed << std::setprecision(2) << std::setw(15) << cuotaMensual <<  std::setw(15) << intereses <<  std::setw(15) << amortizacion  << std::setw(20) << deuda << "\n";
    }

    return 0;
}