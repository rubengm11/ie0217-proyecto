#ifndef PRESTAMO_HPP
#define PRESTAMO_HPP

#include <string>

// Clase Prestamo
class Prestamo
{
public:
    // Enum que define los tipos de préstamo posibles
    enum Tipo
    {
        PERSONAL,
        HIPOTECARIO,
        PRENDARIO
    };

    // Constructor predeterminado de la clase Prestamo
    Prestamo();

    // Constructor de la clase Prestamo con parámetros
    Prestamo(Tipo tipo, double tasaInteresAnual, int cantidadCuotas, long montoPrestamo);

    // Metodo para calcular la cuota mensual del préstamo
    double calcularCuotaMensual();

    // Metodo para guardar información del préstamo en el archivo de texto prestamos.csv
    void guardarPrestamo(int moneda, std::string idCliente);

    // Metodo para abonar a un préstamo propio
    void abonarPrestamoPropio(std::string idCliente);

    // Metodo para abonar a un préstamo ageno
    void abonarPrestamoAgeno(std::string idClienteAbonador, std::string idPrestamoAbonar);

private:
    // Tipo de préstamo (personal, hipotecario, prendario)
    Tipo tipoPrestamo;
    // Tasa de interés anual del préstamo
    double tasaInteresAnual;
    // Cantidad de cuotas del préstamo
    int cantidadCuotas;
    // Monto del préstamo (long para permita numeros grandes)
    long montoPrestamo;
};

#endif
