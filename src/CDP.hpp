#ifndef CDP_HPP
#define CDP_HPP

class CDP {
private:
    double tasaInteres;
    double monto;
    int plazo;

public:
    // Constructor
    CDP(double tasa, double monto, int plazo);

    // Métodos para obtener información
    double getTasaInteres() const;
    double getMonto() const;
    int getPlazo() const;

    // Otros métodos que puedas necesitar
};

#endif
