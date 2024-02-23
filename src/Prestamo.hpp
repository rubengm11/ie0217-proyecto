/**
 * @file Prestamo.hpp
 * @brief Definición de la clase Prestamo
 */

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

    /**
     * @brief Constructor predeterminado de la clase Prestamo
     */
    Prestamo();

    /**
     * @brief Constructor de la clase Prestamo con parámetros
     * @param tipo Tipo de préstamo
     * @param tasaInteresAnual Tasa de interés anual del préstamo
     * @param cantidadCuotas Cantidad de cuotas del préstamo
     * @param montoPrestamo Monto del préstamo
     */
    Prestamo(Tipo tipo, double tasaInteresAnual, int cantidadCuotas, long montoPrestamo);

    /**
     * @brief Método para calcular la cuota mensual del préstamo
     * @return Cuota mensual calculada
     */
    double calcularCuotaMensual();

    /**
     * @brief Método para guardar información del préstamo en el archivo de texto prestamos.csv
     * @param moneda Moneda en la que se realiza el préstamo (1 para colones, 2 para dólares)
     * @param idCliente Identificación del cliente que solicita el préstamo
     */
    void guardarPrestamo(int moneda, std::string idCliente);

    /**
     * @brief Método para seleccionar préstamos de un cliente específico
     * @param idCliente Identificación del cliente
     */
    void guardarPrestamosCliente(std::string idCliente);

    /**
     * @brief Método para abonar a un préstamo propio
     * @param idCliente Identificación del cliente que abona al préstamo
     */
    void abonarPrestamoPropio(std::string idCliente);

    /**
     * @brief Método para abonar a un préstamo ajeno
     * @param idClienteAbonador Identificación del cliente que realiza el abono
     * @param idPrestamoAbonar Identificación del préstamo al que se abona
     */
    void abonarPrestamoAgeno(std::string idClienteAbonador, std::string idPrestamoAbonar);

private:
    // Tipo de préstamo (personal, hipotecario, prendario)
    Tipo tipoPrestamo;
    // Tasa de interés anual del préstamo
    double tasaInteresAnual;
    // Cantidad de cuotas del préstamo
    int cantidadCuotas;
    // Monto del préstamo (long para permitir números grandes)
    long montoPrestamo;
};

#endif // PRESTAMO_HPP

