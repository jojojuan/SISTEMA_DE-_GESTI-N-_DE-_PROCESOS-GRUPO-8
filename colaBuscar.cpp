#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Proceso {
    int id;
    string nombre;
};

vector<Proceso> cola;

void enqueue(Proceso p) {
    cola.push_back(p);
    cout << "Proceso encolado: " << p.id << " - " << p.nombre << endl;
}

Proceso* buscar(int id) {
    for(int i = 0; i < cola.size(); i++) {
        if(cola[i].id == id) {
            return &cola[i];
        }
    }
    return NULL;
}

void mostrarTodos() {
    if(cola.empty()) {
        cout << "La cola esta vacia." << endl;
        return;
    }
    cout << "\nProcesos en la cola:" << endl;
    for(int i = 0; i < cola.size(); i++) {
        cout << "ID: " << cola[i].id << " - Nombre: " << cola[i].nombre << endl;
    }
}

int main() {
    // Agregar procesos de ejemplo
    Proceso p1 = {1, "Proceso A"};
    Proceso p2 = {2, "Proceso B"};
    Proceso p3 = {3, "Proceso C"};
    
    enqueue(p1);
    enqueue(p2);
    enqueue(p3);

    // Mostrar todos los procesos
    mostrarTodos();

    int idBuscado;
    cout << "\nIngrese ID a buscar: ";
    cin >> idBuscado;

    Proceso* resultado = buscar(idBuscado);
    if(resultado != NULL) {
        cout << "Proceso encontrado: " << resultado->id << " - " << resultado->nombre << endl;
    } else {
        cout << "Proceso no encontrado." << endl;
    }

    system("pause");
    return 0;
}
