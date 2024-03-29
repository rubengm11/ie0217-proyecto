/**
 * @file Prestamo.hpp
 * @brief Definición de la clase Prestamo y sus métodos relacionados.
 */
#include "Prestamo.hpp"
#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <limits>

/**
 * @brief Clase que representa un préstamo. Es el contructor por default
 */

Prestamo::Prestamo() {}

    /**
     * @brief Constructor por copia de la clase Prestamo, recibiendo los debidos parametros.
     * @param tipo Tipo de préstamo.
     * @param tasaInteresAnual Tasa de interés anual del préstamo.
     * @param cantidadCuotas Cantidad de cuotas del préstamo.
     * @param montoPrestamo Monto total del préstamo.
     */
Prestamo::Prestamo(Tipo tipo, double tasaInteresAnual, int cantidadCuotas, long montoPrestamo)
    : tipoPrestamo(tipo), tasaInteresAnual(tasaInteresAnual), cantidadCuotas(cantidadCuotas), montoPrestamo(montoPrestamo) {}

    /**
     * @brief Se calcula la cuota mensual del préstamo mediante la fórmula en cuestión.
     * @return La cuota mensual del préstamo.
     */
double Prestamo::calcularCuotaMensual()
{
    double tasaInteresMensual = tasaInteresAnual / 12 / 100;
    double cuotaMensual = (montoPrestamo * tasaInteresMensual) / (1 - pow(1 + tasaInteresMensual, -cantidadCuotas));
    return cuotaMensual;
}
    /**
     * @brief Se guarda información del préstamo en el archivo de texto prestamos.csv
     * @param moneda Tipo de moneda.
     * @param idCliente Identificación del cliente.
     */

void Prestamo::guardarPrestamo(int moneda, std::string idCliente)
{
    // Leemos el archivo para contar el número de líneas
    std::ifstream archivoLectura("./src/prestamos.csv");

    int numeroPrestamos = 1;
    std::string linea;

    // Lee el archivo línea por línea y cuenta los préstamos del cliente
    while (std::getline(archivoLectura, linea))
    {
        // Usar stringstream para dividir la línea en campos
        std::stringstream ss(linea);
        std::string campo;

        // Leer el primer campo que contiene el id_cliente, solo nos interesa
        std::getline(ss, campo, ',');

        // Si el id_cliente coincide con el proporcionado, sumamos 1 al contador de préstamos
        if (campo == idCliente)
        {
            numeroPrestamos++;
        }
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

    // Calcular la cuota mensual
    double cuotaMensual = calcularCuotaMensual();

    // Escribe la nueva línea en el archivo
    archivo << idCliente << ',' << moneda << tipoPrestamo << idCliente << numeroPrestamos << ',' << montoPrestamo
            << ',' << tasaInteresAnual << ',' << cantidadCuotas << ',' << cuotaMensual << ',' << cantidadCuotas << std::endl;

    // Cierra el archivo
    archivo.close();
    std::ofstream archivoRegistro("./src/registro_bancario.txt", std::ios::app);
        if (!archivoRegistro.is_open()) {
        std::cerr << "Error al abrir el archivo.\n";
        return;
        }

    // Escribir los datos del nuevo cliente en el archivo
        archivoRegistro << "\nTipo de operacion: Creacion prestamo \n" << "Identificacion: " << idCliente << "\nId Prestamo: " << moneda << tipoPrestamo << idCliente << numeroPrestamos
        << "\nMonto Total: "<< montoPrestamo << "\nCuotas: " << cantidadCuotas << "\nInteres: " << tasaInteresAnual << "\n";

        archivoRegistro.close();
}

    /**
     * @brief Se guardan los préstamos de el cliente en cuestion en un archivo CSV, llamado prestamoscli.csv.
     * @param idCliente Identificación del cliente.
     */

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
    archivo << "id_cliente,id_prestamo,monto,tasa_interes,numero_cuotas,couta_mensual,cuotas_restantes" << std::endl;

    // Leer el archivo para encontrar los préstamos del cliente
    std::string linea;
    while (getline(archivoLectura, linea))
    {
        std::istringstream iss(linea);
        std::string idClienteFromFile, idPrestamo, monto, tasaInteres, numCuotas, cuotaMen, cuotasRestantes;

        // Leer los valores de cada columna
        getline(iss, idClienteFromFile, ',');
        getline(iss, idPrestamo, ',');
        getline(iss, monto, ',');
        getline(iss, tasaInteres, ',');
        getline(iss, numCuotas, ',');
        getline(iss, cuotaMen, ',' );
        getline(iss, cuotasRestantes, ',');

        // Si el préstamo pertenece al cliente actual, escribirlo en el archivo prestamoscli.csv
        if (idCliente == idClienteFromFile)
        {
            archivo << idClienteFromFile << ',' << idPrestamo << ',' << monto << ',' << tasaInteres << ',' << numCuotas << ',' << cuotaMen << ',' << cuotasRestantes << std::endl;
        }
    }

    // Cerrar los archivos
    archivoLectura.close();
    archivo.close();

    std::cout << "Los préstamos del cliente " << idCliente << " se han guardado en el archivo prestamoscli.csv" << std::endl;
}

    /**
     * @brief Permite al cliente abonar a uno de sus préstamos. Hace los cambios prudentes en los archivos
     * requeridos
     * @param idCliente Identificación del cliente.
     */
void Prestamo::abonarPrestamoPropio(std::string idCliente)
{
    // Abrir el archivo prestamos.csv en modo lectura y escritura
    std::fstream file("./src/prestamos.csv", std::ios::in | std::ios::out);

    // Revisar la apertura del archivo
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
        std::string idClienteFromFile, idPrestamo, monto, tasaInteres, numCuotas, cuotaMen, cuotasRestantes;

        // Leer los valores de cada columna
        getline(iss, idClienteFromFile, ',');
        getline(iss, idPrestamo, ',');
        getline(iss, monto, ',');
        getline(iss, tasaInteres, ',');
        getline(iss, numCuotas, ',');
        getline(iss, cuotaMen, ',');
        getline(iss, cuotasRestantes, ',');

        // Si el préstamo pertenece al cliente actual, mostrarlo
        if (idCliente == idClienteFromFile)
        {
            std::cout << "ID Prestamo: " << idPrestamo << " - Monto: " << monto << " - Cuota Mensual: " << cuotaMen
                      << " - Numero de Cuotas restantes: " << cuotasRestantes << std::endl;
        }
    }

    // Cerrar el archivo antes de volver a abrirlo
    file.close();

    // Abrir el archivo nuevamente en modo lectura y escritura
    file.open("./src/prestamos.csv", std::ios::in | std::ios::out);

    // Pedir al usuario que elija a cuál préstamo abonar
    std::cout << "Ingrese el ID del prestamo al que desea abonar: ";
    std::string idPrestamoAbonar;
    std::cin >> idPrestamoAbonar;

    // Pedir al usuario la cantidad que desea abonar
    double cantidadAbonar;
    do {
        std::cout << "Ingrese la cantidad que desea abonar: ";
        if (!(std::cin >> cantidadAbonar) || cantidadAbonar <= 0) {
            std::cout << "Error: Por favor ingrese un valor numerico positivo." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        } while (cantidadAbonar <= 0);


    // Estructura usada para almacenar las lineasa del archivo
    std::vector<std::string> lines;

    while (getline(file, line))
    {
        std::istringstream iss(line);
        std::string idClienteFromFile, idPrestamo, monto, tasaInteres, numCuotas, cuotaMen, cuotasRestantes;

        // Leer los valores de cada columna
        getline(iss, idClienteFromFile, ',');
        getline(iss, idPrestamo, ',');
        getline(iss, monto, ',');
        getline(iss, tasaInteres, ',');
        getline(iss, numCuotas, ',');
        getline(iss, cuotaMen, ',');
        getline(iss, cuotasRestantes, ',');

        // Si el préstamo pertenece al cliente actual y es el seleccionado
        if (idCliente == idClienteFromFile && idPrestamo == idPrestamoAbonar)
        {
            double cuotaMensual = std::stod(cuotaMen);
            int cuotasRestantesInt = std::stoi(cuotasRestantes);

            // Si la cantidad abonada es mayor o igual a la cuota mensual, reducir las cuotas restantes
            if (cantidadAbonar >= cuotaMensual)
            {
                cuotasRestantesInt--;
                std::cout << "Abono realizado con éxito." << std::endl;
            }
            else
            {
                std::cout << "La cantidad abonada no es suficiente para reducir las cuotas restantes." << std::endl;
            }

            // Actualizar la línea con las cuotas restantes modificadas
            line = idClienteFromFile + ',' + idPrestamo + ',' + monto + ',' + tasaInteres + ',' + numCuotas + ',' + cuotaMen + ',' + std::to_string(cuotasRestantesInt);
                
                std::ofstream archivoRegistro("./src/registro_bancario.txt", std::ios::app);
                if (!archivoRegistro.is_open()) {
                    std::cerr << "Error al abrir el archivo.\n";
                    return;
                }

                // Escribir los datos del nuevo cliente en el archivo
                archivoRegistro << "\nTipo de operacion: Abono a prestamo propio \n" << "Identificacion: " << idClienteFromFile << "\nId Prestamo: " << idPrestamo <<"\nMonto Total: "
                                << monto <<"\nMonto abonado: " << cantidadAbonar << "\nCuotas Restanstes: " << std::to_string(cuotasRestantesInt) << "\nInteres: " << tasaInteres << "\n";

                archivoRegistro.close();
        }

        // Almacenar la línea en el vector
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
    }
    else
    {
        // En caso de que el contenido no sea igual
        std::cout << "El ID del prestamo no coincide con los prestamos asociados al usuario, no se puede abonar" << std::endl;
    }
   
}

    /**
     * @brief Permite a un cliente abonar a un préstamo de otro cliente. Modificando los archivos prudentes.
     * @param idClienteAbonador Identificación del cliente que realiza el abono.
     * @param idPrestamoAbonar Identificación del préstamo al que se realiza el abono.
     */

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

    // Pedir al usuario la cantidad que desea abonar
    double cantidadAbonar;
    do {
        std::cout << "Ingrese la cantidad que desea abonar: ";
        if (!(std::cin >> cantidadAbonar) || cantidadAbonar <= 0) {
            std::cout << "Error: Por favor ingrese un valor numerico positivo." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        } while (cantidadAbonar <= 0);

    // Estructura utilizada para almacenar las líneas del archivo
    std::vector<std::string> lines;

    // Almacenar el encabezado en el vector
    lines.push_back(line);

    // Leer el archivo
    while (getline(file, line))
    {
        // Definicion de variables para valores de culumnas de cada interacción
        std::istringstream iss(line);
        std::string idClienteFromFile, idPrestamo, monto, tasaInteres, numCuotas, cuotaMen, cuotasRestantes;

        // Leer los valores de cada columna
        getline(iss, idClienteFromFile, ',');
        getline(iss, idPrestamo, ',');
        getline(iss, monto, ',');
        getline(iss, tasaInteres, ',');
        getline(iss, numCuotas, ',');
        getline(iss, cuotaMen, ',' );
        getline(iss, cuotasRestantes, ',');


        // Si el préstamo pertenece al cliente actual, almacenar la línea
        if (idClienteAbonador != idClienteFromFile && idPrestamo == idPrestamoAbonar)
        {
            double cuotaMensual = std::stod(cuotaMen);
            int cuotasRestantesInt = std::stoi(cuotasRestantes);
            int montoInt = std::stoi(monto);
            // Si la cantidad abonada es mayor o igual a la cuota mensual, reducir las cuotas restantes
            if (cantidadAbonar >= cuotaMensual)
            {cuotasRestantesInt--;
            std::cout << "Abono realizado con éxito." << std::endl;
            }else
            {   monto = std::to_string(montoInt);
                std::cout << "La cantidad abonada no es suficiente para reducir las cuotas restantes o \n" << std::endl;
            }

            // Modificar la línea con la nueva cuotaRestante
            line = idClienteFromFile + ',' + idPrestamo + ',' + monto + ',' + tasaInteres + ',' + numCuotas + ',' + cuotaMen + ',' + std::to_string(cuotasRestantesInt);
            std::ofstream archivoRegistro("./src/registro_bancario.txt", std::ios::app);
                if (!archivoRegistro.is_open()) {
                    std::cerr << "Error al abrir el archivo.\n";
                    return;
                }
                // Escribir los datos del nuevo cliente en el archivo
                archivoRegistro << "\nTipo de operacion: Abono a prestamo ajeno \n" << "Identificacion: " << idClienteAbonador << "\nId Prestamo: " << idPrestamo << "\nMonto Total: "
                                << monto <<"\nMonto abonado: " << cantidadAbonar << "\nCuotas Restanstes: " << std::to_string(cuotasRestantesInt) << "\nInteres: " << tasaInteres << "\n";

                archivoRegistro.close();
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

    }
    else
    {
        // En caso de que el contenido no sea igual
        std::cout << "El ID del prestamo  no coincide con los prestamos asociados" << std::endl;
    }
}
