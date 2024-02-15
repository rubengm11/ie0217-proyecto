#ifndef PRESTAMO_HPP
#define PRESTAMO_HPP

class Prestamo {
public:
    enum Tipo { PERSONAL, HIPOTECARIO, PRENDARIO };

    Prestamo(Tipo tipo, double tasaInteresAnual, int cantidadCuotas, double montoPrestamo);

    double calcularCuotaMensual();

private:
    Tipo tipoPrestamo;
    double tasaInteresAnual;
    int cantidadCuotas;
    double montoPrestamo;
};

#endif
