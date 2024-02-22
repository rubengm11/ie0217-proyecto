#include "Prestamo.hpp"
#include <cmath>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>

// Contructor por default
Prestamo::Prestamo() {}

// Constructor por copia de la clase reciviendo parametros
Prestamo::Prestamo(Tipo tipo, double tasaInteresAnual, int cantidadCuotas, long montoPrestamo)
    : tipoPrestamo(tipo), tasaInteresAnual(tasaInteresAnual), cantidadCuotas(cantidadCuotas), montoPrestamo(montoPrestamo) {}

double Prestamo::calcularCuotaMensual()
{
    double tasaInteresMensual = tasaInteresAnual / 12 / 100;
    double cuotaMensual = (montoPrestamo * tasaInteresMensual) / (1 - pow(1 + tasaInteresMensual, -cantidadCuotas));
    return cuotaMensual;
}

// Metodo para guardar información del préstamo en el archivo de texto prestamos.csv
void Prestamo::guardarPrestamo(int moneda, std::string idCliente)
{
    
    // Leemos el archivo para contar el número de líneas
    std::ifstream archivoLectura("./src/prestamos.csv");

    int numeroLineas = 0;
    std::string linea;

    // Lee el archivo línea por línea y cuenta las líneas
    while (std::getline(archivoLectura, linea))
    {
        numeroLineas++;
    }

    // Cierra el archivo de lectura
    archivoLectura.close();

    std::ofstream archivo("./src/prestamos.csv", std::ios::app);

    // Verifica si el archivo se abrió correctamente
    if (!archivo.is_open())
    {
        std::cerr << "Error al abrir el archivo prestamos.csv" << std::endl;
        return;
    }

    // Escribe la nueva línea en el archivo
    archivo << idCliente << ',' << moneda << tipoPrestamo << idCliente << numeroLineas << ',' << montoPrestamo
            << ',' << tasaInteresAnual << ',' << cantidadCuotas << ',' << cantidadCuotas << std::endl;

    // Cierra el archivo
    archivo.close();
}
    // Metodo para seleccionar prestamos
    void Prestamo::guardarPrestamosCliente(std::string idCliente)
{
    // Abrir el archivo prestamos.csv en modo lectura
    std::ifstream archivoLectura("./src/prestamos.csv");

    // Verificar si el archivo se abrió correctamente
    if (!archivoLectura.is_open())
    {
        std::cerr << "Error al abrir el archivo prestamos.csv" << std::endl;
        return;
    }

    // Crear y abrir el archivo prestamoscli.csv en modo escritura
    std::ofstream archivo("./src/prestamoscli.csv");

    // Verificar si el archivo se abrió correctamente
    if (!archivo.is_open())
    {
        std::cerr << "Error al abrir el archivo prestamoscli.csv" << std::endl;
        return;
    }

    // Escribir el encabezado del archivo CSV
    archivo << "id_cliente,id_prestamo,monto,tasa_interes,numero_cuotas,cuotas_restantes" << std::endl;

    // Leer el archivo para encontrar los préstamos del cliente
    std::string linea;
    while (std::getline(archivoLectura, linea))
    {
        std::istringstream iss(linea);
        std::string idClienteFromFile, idPrestamo, monto, tasaInteres, numCuotas, cuotasRestantes;

        // Leer los valores de cada columna
        std::getline(iss, idClienteFromFile, ',');
        std::getline(iss, idPrestamo, ',');
        std::getline(iss, monto, ',');
        std::getline(iss, tasaInteres, ',');
        std::getline(iss, numCuotas, ',');
        std::getline(iss, cuotasRestantes, ',');

        // Si el préstamo pertenece al cliente actual, escribirlo en el archivo prestamoscli.csv
        if (idCliente == idClienteFromFile)
        {
            archivo << idClienteFromFile << ',' << idPrestamo << ',' << monto << ',' << tasaInteres << ',' << numCuotas << ',' << cuotasRestantes << std::endl;
        }
    }

    // Cerrar los archivos
    archivoLectura.close();
    archivo.close();

    std::cout << "Los préstamos del cliente " << idCliente << " se han guardado en el archivo prestamoscli.csv" << std::endl;
}



// Metodo para abonar a un préstamo propio
void Prestamo::abonarPrestamoPropio(std::string idCliente)
{
    // Abrir el archivo prestamos.csv en modo lectura y escritura
    std::fstream file("./src/prestamos.csv", std::ios::in | std::ios::out);

    // Revision de apertura del archivo
    if (!file.is_open())
    {
        std::cerr << "Error al abrir el archivo prestamos.csv" << std::endl;
        return;
    }

    // Leer el encabezado del archivo
    std::string line;
    getline(file, line);

    // Mostrar al usuario los préstamos disponibles para abonar
    std::cout << "Prestamos disponibles para el cliente " << idCliente << ":" << std::endl;

    // Leer el archivo para contar el número de líneas
    std::ifstream archivoLectura("./src/prestamos.csv");

    // Cierra el archivo de lectura
    archivoLectura.close();

    // Leer el archivo
    while (getline(file, line))
    {
        std::istringstream iss(line);
        std::string idClienteFromFile, idPrestamo, monto, tasaInteres, numCuotas, cuotasRestantes;

        // Leer los valores de cada columna
        getline(iss, idClienteFromFile, ',');
        getline(iss, idPrestamo, ',');
        getline(iss, monto, ',');
        getline(iss, tasaInteres, ',');
        getline(iss, numCuotas, ',');
        getline(iss, cuotasRestantes, ',');

        // Si el préstamo pertenece al cliente actual, mostrarlo
        if (idCliente == idClienteFromFile)
        {
            std::cout << "ID Prestamo: " << idPrestamo << " - Monto: " << monto
                      << " - Cuotas restantes: " << cuotasRestantes << std::endl;
        }
    }

    // Cerrar el archivo antes de volver a abrirlo
    file.close();

    // Abrir el archivo nuevamente en modo lectura y escritura
    file.open("./src/prestamos.csv", std::ios::in | std::ios::out);

    // Pedir al usuario que elija a cuál préstamo abonar (propio
    std::cout << "Ingrese el ID del prestamo al que desea abonar: ";
    std::string idPrestamoAbonar;
    std::cin >> idPrestamoAbonar;

    // Estructura usada para almacenar las lineasa del archivo
    std::vector<std::string> lines;

    while (getline(file, line))
    {
        // Definicion de variables para valores de culumnas de cada interaccion
        std::istringstream iss(line);
        std::string idClienteFromFile, idPrestamo, monto, tasaInteres, numCuotas, cuotasRestantes;

        // Leer los valores de cada columna
        getline(iss, idClienteFromFile, ',');
        getline(iss, idPrestamo, ',');
        getline(iss, monto, ',');
        getline(iss, tasaInteres, ',');
        getline(iss, numCuotas, ',');
        getline(iss, cuotasRestantes, ',');

        // Si el préstamo pertenece al cliente actual, almacenar la línea
        if (idCliente == idClienteFromFile && idPrestamo == idPrestamoAbonar)
        {
            int cuotasRestantesInt = std::stoi(cuotasRestantes);
            cuotasRestantesInt--;

            // Modificar la línea con la nueva cuotaRestante restandole 1 en el proceso
            line = idClienteFromFile + ',' + idPrestamo + ',' + monto + ',' + tasaInteres + ',' + numCuotas + ',' + std::to_string(cuotasRestantesInt);
        }

        // Almacenar la línea (modificada o no) en el vector
        lines.push_back(line);
    }

    // Cerrar el archivo antes de escribir
    file.close();

    // Verificar si el archivo ha cambiado
    std::ifstream originalFile("./src/prestamos.csv");
    std::string originalContent((std::istreambuf_iterator<char>(originalFile)), std::istreambuf_iterator<char>());
    originalFile.close();

    std::ostringstream modifiedContent;

    // Escribir el contenido modificado
    for (const auto &l : lines)
    {
        modifiedContent << l << std::endl;
    }

    // Comparar el contenido original con el modificado
    if (originalContent != modifiedContent.str())
    {
        // Abrir el archivo en modo de escritura
        std::ofstream outFile("./src/prestamos.csv");

        // Escribir todas las líneas en el archivo
        for (const auto &l : lines)
        {
            outFile << l << std::endl;
        }

        // Cerrar el archivo después de usarlo
        outFile.close();

        std::cout << "Abono realizado con éxito." << std::endl;
    }
    else
    {
        // En caso de que el contenido no sea igual
        std::cout << "El ID del prestamo no coincide con los prestamos asociados al usuario" << std::endl;
    }
}

// Metodo para abonar a un préstamo ageno
void Prestamo::abonarPrestamoAgeno(std::string idClienteAbonador, std::string idPrestamoAbonar)
{
    // Abrir el archivo prestamos.csv en modo lectura y escritura
    std::fstream file("./src/prestamos.csv", std::ios::in | std::ios::out);

    if (!file.is_open())
    {
        std::cerr << "Error al abrir el archivo prestamos.csv" << std::endl;
        return;
    }

    // Leer el encabezado del archivo
    std::string line;
    getline(file, line);

    // Estructura utilizada para almacenar las líneas del archivo
    std::vector<std::string> lines;

    // Almacenar el encabezado en el vector
    lines.push_back(line);

    // Leer el archivo
    while (getline(file, line))
    {
        // Definicion de variables para valores de culumnas de cada interacción
        std::istringstream iss(line);
        std::string idClienteFromFile, idPrestamo, monto, tasaInteres, numCuotas, cuotasRestantes;

        // Leer los valores de cada columna
        getline(iss, idClienteFromFile, ',');
        getline(iss, idPrestamo, ',');
        getline(iss, monto, ',');
        getline(iss, tasaInteres, ',');
        getline(iss, numCuotas, ',');
        getline(iss, cuotasRestantes, ',');

        // Si el préstamo pertenece al cliente actual, almacenar la línea
        if (idClienteAbonador != idClienteFromFile && idPrestamo == idPrestamoAbonar)
        {
            int cuotasRestantesInt = std::stoi(cuotasRestantes);
            cuotasRestantesInt--;

            // Modificar la línea con la nueva cuotaRestante
            line = idClienteFromFile + ',' + idPrestamo + ',' + monto + ',' + tasaInteres + ',' + numCuotas + ',' + std::to_string(cuotasRestantesInt);
        }

        // Almacenar la línea (modificada o no) en el vector
        lines.push_back(line);
    }

    // Cerrar el archivo antes de escribir
    file.close();

    // Verificar si el archivo ha cambiado
    std::ifstream originalFile("./src/prestamos.csv");
    std::string originalContent((std::istreambuf_iterator<char>(originalFile)), std::istreambuf_iterator<char>());
    originalFile.close();

    std::ostringstream modifiedContent;

    // Escribir el contenido modificado
    for (const auto &l : lines)
    {
        modifiedContent << l << std::endl;
    }

    // Comparar el contenido original con el modificado
    if (originalContent != modifiedContent.str())
    {
        // Abrir el archivo en modo de escritura
        std::ofstream outFile("./src/prestamos.csv");

        // Escribir todas las líneas en el archivo
        for (const auto &l : lines)
        {
            outFile << l << std::endl;
        }

        // Cerrar el archivo después de usarlo
        outFile.close();

        std::cout << "Abono realizado con éxito." << std::endl;
    }
    else
    {
        // En caso de que el contenido no sea igual
        std::cout << "El ID del prestamo coincide con los prestamos asociados al usuario abonador" << std::endl;
    }
}
