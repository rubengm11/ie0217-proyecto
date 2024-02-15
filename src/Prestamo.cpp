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

