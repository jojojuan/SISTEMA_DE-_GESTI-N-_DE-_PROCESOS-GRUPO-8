#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Proceso {
    int id;
    string nombre;
    string estado;
};

vector<Proceso> cola;

void enqueue(Proceso p) {
    cola.push_back(p);
    cout << "Proceso encolado: " << p.id << " - " << p.nombre << " - " << p.estado << endl;
}

Proceso* buscar(int id) {
    for(int i = 0; i < cola.size(); i++) {
        if(cola[i].id == id) {
            return &cola[i];
        }
    }
    return NULL;
}

bool update(int id, string nuevoNombre, string nuevoEstado) {
    Proceso* p = buscar(id);
    if(p != NULL) {
        p->nombre = nuevoNombre;
        p->estado = nuevoEstado;
        return true;
    }
    return false;
}

void mostrarCola() {
    cout << "\nContenido de la cola:\n";
    for(int i = 0; i < cola.size(); i++) {
        cout << "ID: " << cola[i].id << ", Nombre: " << cola[i].nombre 
             << ", Estado: " << cola[i].estado << endl;
    }
}

int main() {
    // Crear y agregar procesos
    Proceso p1 = {1, "Proceso A", "Listo"};
    Proceso p2 = {2, "Proceso B", "En espera"};
    Proceso p3 = {3, "Proceso C", "Ejecutando"};
    
    enqueue(p1);
    enqueue(p2);
    enqueue(p3);

    mostrarCola();

    cout << "\n--- Actualizacion de proceso ---\n";
    int idActualizar;
    string nuevoNombre, nuevoEstado;

    cout << "Ingrese ID del proceso a actualizar: ";
    cin >> idActualizar;
    cin.ignore(); // limpiar buffer

    cout << "Nuevo nombre: ";
    getline(cin, nuevoNombre);

    cout << "Nuevo estado: ";
    getline(cin, nuevoEstado);

    if(update(idActualizar, nuevoNombre, nuevoEstado)) {
        cout << "Proceso actualizado correctamente.\n";
    } else {
        cout << "Proceso no encontrado.\n";
    }

    mostrarCola();

    system("pause");
    return 0;
}
