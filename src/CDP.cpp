#include "CDP.hpp"

// Constructor
CDP::CDP(double tasa, double monto, int plazo) : tasaInteres(tasa), monto(monto), plazo(plazo) {}

// Métodos para obtener información
double CDP::getTasaInteres() const {
    return tasaInteres;
}

double CDP::getMonto() const {
    return monto;
}

int CDP::getPlazo() const {
    return plazo;
}
