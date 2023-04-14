#include <iostream>
#include <malloc.h>


using namespace std;

struct Paciente {
    int year;
    float copago;
    Paciente *izq;
    Paciente *der;
};

void insertarPaciente(Paciente *&arbol, int year, float copago) {
    if (arbol == NULL) {
        arbol = (Paciente*) malloc(sizeof(Paciente));
        arbol->year = year;
        arbol->copago = copago;
        arbol->izq = NULL;
        arbol->der = NULL;
    } else {
        if (year < arbol->year) {
            insertarPaciente(arbol->izq, year, copago);
        } else {
            insertarPaciente(arbol->der, year, copago);
        }
    }
}

void calcularTotalCopago(Paciente *arbol, float &total) {
    if (arbol != NULL) {
        calcularTotalCopago(arbol->izq, total);
        total += arbol->copago;
        calcularTotalCopago(arbol->der, total);
    }
}

float calcularPromedioCopago(Paciente *arbol) {
    float total = 0;
    int count = 0;
    calcularTotalCopago(arbol, total);
    while (arbol != NULL) {
        count++;
        arbol = arbol->izq;
    }
    return total / count;
}

void calcularPromedioCopagoPorYear(Paciente *arbol) {
    if (arbol != NULL) {
        calcularPromedioCopagoPorYear(arbol->izq);
        float promedio = calcularPromedioCopago(arbol);
        cout << "Promedio de copago para pacientes nacidos en el ano " << arbol->year << ": " << promedio << endl;
        calcularPromedioCopagoPorYear(arbol->der);
    }
}

int main() {
    Paciente *arbol = NULL;
    int opcion = 0;
    do {
        cout << "Menu:" << endl;
        cout << "1. Agregar paciente" << endl;
        cout << "2. Calcular valor cancelado por paciente" << endl;
        cout << "3. Calcular promedio cancelado por pacientes agrupados por ano de nacimiento" << endl;
        cout << "4. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        switch (opcion) {
            case 1: {
                int year;
                float copago;
                cout << "Ingrese el ano de nacimiento del paciente: ";
                cin >> year;
                cout << "Ingrese el valor cancelado por cita por concepto de copago: ";
                cin >> copago;
                insertarPaciente(arbol, year, copago);
                break;
            }
            case 2: {
                float total = 0;
                calcularTotalCopago(arbol, total);
                cout << "El valor total cancelado por pacientes es: " << total << endl;
                break;
            }
            case 3: {
                calcularPromedioCopagoPorYear(arbol);
                break;
            }
            case 4: {
                cout << "Saliendo del programa..." << endl;
                break;
            }
            default: {
                cout << "Opcion invalida. Intente de nuevo." << endl;
                break;
            }
        }
    } while (opcion != 4);
    return 0;
}