#include <iostream>
#include <string>

using namespace std;

// Estructura para representar un proceso en la pila
struct Nodo {
    int id;
    string nombre;
    Nodo* siguiente;
};

// Puntero al tope de la pila
Nodo* tope = NULL;

// Función para insertar un nuevo proceso en la pila (push)
void IngresarPila(int id, const string& nombre) {
    Nodo* nuevo = new Nodo;
    nuevo->id = id;
    nuevo->nombre = nombre;
    nuevo->siguiente = tope;
    tope = nuevo;
    cout << "? Proceso agregado a la pila: " << id << " - " << nombre << endl;
}

// Función para actualizar el nombre de un proceso por ID
bool ActualizarPila(int id, const string& nuevoNombre) {
    Nodo* actual = tope;
    while (actual != NULL) {
        if (actual->id == id) {
            actual->nombre = nuevoNombre;
            cout << "?? Proceso actualizado: " << id << " - " << nuevoNombre << endl;
            return true;
        }
        actual = actual->siguiente;
    }
    cout << "? Proceso no encontrado con ID: " << id << endl;
    return false;
}
// Función para eliminar el proceso del tope de la pila (pop)
bool EliminarProceso() {
if(tope == NULL){
    cout <<"No hay procesos para eliminar.\n;
return false;
    }
    Nodo*temp = tope ;
    cout<<"Proceso eliminado:<< temp -> <<"-"<<"temp -> nombre<< endl;
    tope = tope ->siguiente;
    delete temp;
    return true;
}

// Función para buscar un proceso por nombre
void BuscarPorNombre(const string& nombreBuscado) {
    Nodo* actual = tope;
    bool encontrado = false;
    cout << "\n Buscando proceso con nombre: " << nombreBuscado << endl;

    while (actual != NULL) {
        if (actual->nombre == nombreBuscado) {
            cout << " Proceso encontrado - ID: " << actual->id << ", Nombre: " << actual->nombre << endl;
            encontrado = true;
            break;
        }
        actual = actual->siguiente;
    }

    if (!encontrado) {
        cout << " No se encontró ningún proceso con ese nombre.\n";
    }
}

// Función para mostrar los procesos en la pila
void MostrarPila() {
    Nodo* actual = tope;
    cout << "\n?? Procesos en la pila:\n";
    if (actual == NULL) {
        cout << "(La pila está vacía)\n";
        return;
    }

    while (actual != NULL) {
        cout << "ID: " << actual->id << ", Nombre: " << actual->nombre << endl;
        actual = actual->siguiente;
    }
}

// Función para liberar memoria al final
void LiberarMemoria() {
    while (tope != NULL) {
        Nodo* temp = tope;
        tope = tope->siguiente;
        delete temp;
    }
}

int main() {
    int opcion, id;
    string nombre;

    do {
        cout << "\n=== GESTOR DE MEMORIA - PILA ===\n";
        cout << "1. Ingresar proceso\n";
        cout << "2. Actualizar proceso\n";
        cout << "3. Mostrar pila\n";
        cout << "4.Eliminar proceso del tope\n;
        cout << "5.Buscar proceso por nombre\n;
        cout << "6. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingrese ID del proceso: ";
                cin >> id;
                cin.ignore(); // Limpiar salto de línea pendiente
                cout << "Ingrese nombre del proceso: ";
                getline(cin, nombre);
                IngresarPila(id, nombre);
                break;

            case 2:
                cout << "Ingrese ID del proceso a actualizar: ";
                cin >> id;
                cin.ignore(); // Limpiar salto de línea pendiente
                cout << "Ingrese nuevo nombre del proceso: ";
                getline(cin, nombre);
                ActualizarPila(id, nombre);
                break;

            case 3:
                MostrarPila();
                break;
            case 4:
                EliminarProceso();
                break;
            case 5:
                cin.ignore();
                cout <<"Ingrese el nombre del proceso a buscar:";
                getline(cin,nombre);
                BuscarPorNombre(nombre);
                break;

            case 6:
                cout << "Saliendo del programa...\n";
                break;

            default:
                cout << " Opción inválida. Intente nuevamente.\n";
        }

    } while (opcion != 0);

    LiberarMemoria();
    return 0;
}
