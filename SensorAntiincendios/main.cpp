#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
using namespace std;

// Constantes para los límites
const float TEMP_LIMITE = 50.0;
const float HUMEDAD_LIMITE = 20.0;
const int HUMO_LIMITE = 1;
const int MAX_EVENTOS = 100;

// Variables globales
float tanqueAgua = 100.0;
string eventos[MAX_EVENTOS]; // Arreglo para almacenar eventos
int numEventos = 0; // Contador para el número de eventos registrados

// Función para agregar eventos al arreglo
bool registrarEvento(const string &evento) {
    if (numEventos < MAX_EVENTOS) {
        eventos[numEventos] = evento;
        numEventos++;
        return true; // Evento registrado correctamente
    } else {
        return false; // Error: Arreglo de eventos lleno
    }
}

// Función para mostrar eventos almacenados
string mostrarEventos() {
    string resultado = "\nRegistro de eventos:\n";
    for (int i = 0; i < numEventos; i++) {
        resultado += eventos[i] + "\n";
    }
    return resultado;
}

// Función para capturar datos de sensores
bool capturarDatos(float &temperatura, float &humedad, int &humo) {
    cout << "Ingrese la temperatura actual: "; cin >> temperatura;
    cout << "Ingrese la humedad actual: "; cin >> humedad;
    cout << "Ingrese el nivel de humo (1=presente, 0=ausente): "; cin >> humo;
    return true; // Datos capturados correctamente
}

// Función para evaluar condiciones de riesgo
bool evaluarCondiciones(float temperatura, float humedad, int humo) {
    return (temperatura > TEMP_LIMITE || humedad < HUMEDAD_LIMITE || humo >= HUMO_LIMITE);
}

// Función para activar riego
bool activarRiego() {
    if (tanqueAgua > 0) {
        cout << "Riego activado.\n";
        tanqueAgua -= 10.0;
        registrarEvento("Riego activado.");
        return true;
    } else {
        cout << "Error: Agua insuficiente en el tanque.\n";
        return false;
    }
}

// Función para gestionar el agua
string gestionarAgua() {
    if (tanqueAgua < 20.0) {
        tanqueAgua += 30.0;
        registrarEvento("Tanque recargado con agua de lluvia.");
        return "Tanque recargado con agua de lluvia. Nivel actual: " + to_string(tanqueAgua) + "%";
    } else {
        return "Tanque de agua en buen estado. Nivel actual: " + to_string(tanqueAgua) + "%";
    }
}

// Función para mostrar el menú de opciones
string mostrarMenu() {
    return "\nSistema de Monitoreo de Incendios\n"
           "1. Monitorear el entorno\n"
           "2. Gestionar el agua\n"
           "3. Ver registro de eventos\n"
           "4. Salir\n"
           "Seleccione una opción: ";
}

// Función principal del programa
int main() {
    int opcion;
    float temperatura, humedad;
    int humo;

    do {
        cout << mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1:
                if (capturarDatos(temperatura, humedad, humo)) {
                    if (evaluarCondiciones(temperatura, humedad, humo)) {
                        cout << "Condiciones peligrosas detectadas. Activando riego.\n";
                        activarRiego();
                        registrarEvento("Riesgo de incendio detectado.");
                    } else {
                        cout << "Condiciones normales.\n";
                        registrarEvento("Monitoreo sin incidentes.");
                    }
                }
                break;
            case 2:
                cout << gestionarAgua() << endl;
                break;
            case 3:
                cout << mostrarEventos() << endl;
                break;
            case 4:
                cout << "Saliendo del sistema.\n";
                break;
            default:
                cout << "Opción no válida. Intente nuevamente.\n";
        }
    } while (opcion != 4);

    return 0;
}
