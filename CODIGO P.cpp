#include <iostream>
#include <string>
#include <limits>

using namespace std;

// Estructura para el nodo de la lista enlazada de procesos
struct NodoProceso {
    int id;
    string nombre;
    int prioridad;
    int memoria;
    NodoProceso* siguiente;
    
    NodoProceso(int i, string n, int p, int m) : 
        id(i), nombre(n), prioridad(p), memoria(m), siguiente(NULL) {}
};

// Estructura para el nodo de la cola de prioridad
struct NodoCola {
    NodoProceso* proceso;
    NodoCola* siguiente;
    
    NodoCola(NodoProceso* p) : proceso(p), siguiente(NULL) {}
};

// Clase para el Gestor de Procesos (Lista Enlazada)
class GestorProcesos {
private:
    NodoProceso* inicio;
    
public:
    GestorProcesos() : inicio(NULL) {}
    
    void insertarProceso(int id, string nombre, int prioridad, int memoria) {
        NodoProceso* nuevo = new NodoProceso(id, nombre, prioridad, memoria);
        if (!inicio || inicio->prioridad < prioridad) {
            nuevo->siguiente = inicio;
            inicio = nuevo;
        } else {
            NodoProceso* actual = inicio;
            while (actual->siguiente && actual->siguiente->prioridad >= prioridad) {
                actual = actual->siguiente;
            }
            nuevo->siguiente = actual->siguiente;
            actual->siguiente = nuevo;
        }
        cout << "Proceso " << id << " insertado correctamente.\n";
    }
    
    void eliminarProceso(int id) {
        if (!inicio) {
            cout << "No hay procesos para eliminar.\n";
            return;
        }
        
        if (inicio->id == id) {
            NodoProceso* temp = inicio;
            inicio = inicio->siguiente;
            delete temp;
            cout << "Proceso " << id << " eliminado.\n";
            return;
        }
        
        NodoProceso* actual = inicio;
        while (actual->siguiente && actual->siguiente->id != id) {
            actual = actual->siguiente;
        }
        
        if (actual->siguiente) {
            NodoProceso* temp = actual->siguiente;
            actual->siguiente = temp->siguiente;
            delete temp;
            cout << "Proceso " << id << " eliminado.\n";
        } else {
            cout << "Proceso no encontrado.\n";
        }
    }
    
    NodoProceso* buscarProceso(int id) {
        NodoProceso* actual = inicio;
        while (actual) {
            if (actual->id == id) return actual;
            actual = actual->siguiente;
        }
        return NULL;
    }
    
    void modificarPrioridad(int id, int nuevaPrioridad) {
        NodoProceso* proceso = buscarProceso(id);
        if (proceso) {
            proceso->prioridad = nuevaPrioridad;
            cout << "Prioridad del proceso " << id << " actualizada.\n";
        } else {
            cout << "Proceso no encontrado.\n";
        }
    }
    
    void mostrarProcesos() {
        if (!inicio) {
            cout << "No hay procesos registrados.\n";
            return;
        }
        
        cout << "\nLista de Procesos:\n";
        NodoProceso* actual = inicio;
        while (actual) {
            cout << "ID: " << actual->id 
                 << ", Nombre: " << actual->nombre 
                 << ", Prioridad: " << actual->prioridad 
                 << ", Memoria: " << actual->memoria << "MB\n";
            actual = actual->siguiente;
        }
    }
};

// Clase para el Planificador de CPU (Cola de Prioridad)
class PlanificadorCPU {
private:
    NodoCola* frente;
    
public:
    PlanificadorCPU() : frente(NULL) {}
    
    void encolarProceso(NodoProceso* proceso) {
        NodoCola* nuevo = new NodoCola(proceso);
        if (!frente || proceso->prioridad > frente->proceso->prioridad) {
            nuevo->siguiente = frente;
            frente = nuevo;
        } else {
            NodoCola* actual = frente;
            while (actual->siguiente && 
                   actual->siguiente->proceso->prioridad >= proceso->prioridad) {
                actual = actual->siguiente;
            }
            nuevo->siguiente = actual->siguiente;
            actual->siguiente = nuevo;
        }
        cout << "Proceso " << proceso->id << " encolado en CPU.\n";
    }
    
    void ejecutarProceso() {
        if (!frente) {
            cout << "No hay procesos en la cola de CPU.\n";
            return;
        }
        
        NodoCola* temp = frente;
        frente = frente->siguiente;
        cout << "Ejecutando proceso: " << temp->proceso->id 
             << " (" << temp->proceso->nombre << ")\n";
        delete temp;
    }
    
    void mostrarColaCPU() {
        if (!frente) {
            cout << "Cola de CPU vacía.\n";
            return;
        }
        
        cout << "\nCola de CPU:\n";
        NodoCola* actual = frente;
        while (actual) {
            cout << "ID: " << actual->proceso->id 
                 << ", Nombre: " << actual->proceso->nombre 
                 << ", Prioridad: " << actual->proceso->prioridad << "\n";
            actual = actual->siguiente;
        }
    }
};

// Clase para el Gestor de Memoria (Pila)
class GestorMemoria {
private:
    int* memoria;
    int tope;
    int capacidad;
    
public:
    GestorMemoria(int cap) : capacidad(cap), tope(-1) {
        memoria = new int[capacidad];
    }
    
    ~GestorMemoria() {
        delete[] memoria;
    }
    
    bool asignarMemoria(int cantidad) {
        if (tope + cantidad >= capacidad) {
            cout << "Memoria insuficiente.\n";
            return false;
        }
        tope += cantidad;
        cout << "Memoria asignada: " << cantidad << "MB\n";
        return true;
    }
    
    void liberarMemoria(int cantidad) {
        if (tope - cantidad < -1) {
            cout << "No hay suficiente memoria para liberar.\n";
            return;
        }
        tope -= cantidad;
        cout << "Memoria liberada: " << cantidad << "MB\n";
    }
    
    void mostrarEstadoMemoria() {
        cout << "\nEstado de la Memoria:\n";
        cout << "Memoria total: " << capacidad << "MB\n";
        cout << "Memoria usada: " << (tope + 1) << "MB\n";
        cout << "Memoria libre: " << (capacidad - (tope + 1)) << "MB\n";
    }
};

int main() {
    GestorProcesos gestor;
    PlanificadorCPU cpu;
    GestorMemoria memoria(1024); // 1GB de memoria total
    
    int opcion;
    do {
        cout << "\n=== Sistema de Gestion de Procesos ===\n";
        cout << "1. Insertar nuevo proceso\n";
        cout << "2. Eliminar proceso\n";
        cout << "3. Buscar proceso\n";
        cout << "4. Modificar prioridad\n";
        cout << "5. Mostrar todos los procesos\n";
        cout << "6. Encolar proceso en CPU\n";
        cout << "7. Ejecutar siguiente proceso\n";
        cout << "8. Mostrar cola de CPU\n";
        cout << "9. Asignar memoria\n";
        cout << "10. Liberar memoria\n";
        cout << "11. Mostrar estado de memoria\n";
        cout << "0. Salir\n";
        cout << "Ingrese una opcion: ";
        
        cin >> opcion;
        cin.ignore();
        
        switch(opcion) {
            case 1: {
                int id, prioridad, mem;
                string nombre;
                cout << "ID del proceso: ";
                cin >> id;
                cout << "Nombre del proceso: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "Prioridad (1-10): ";
                cin >> prioridad;
                cout << "Memoria necesaria (MB): ";
                cin >> mem;
                gestor.insertarProceso(id, nombre, prioridad, mem);
                break;
            }
            case 2: {
                int id;
                cout << "ID del proceso a eliminar: ";
                cin >> id;
                gestor.eliminarProceso(id);
                break;
            }
            case 3: {
                int id;
                cout << "ID del proceso a buscar: ";
                cin >> id;
                NodoProceso* p = gestor.buscarProceso(id);
                if (p) {
                    cout << "Proceso encontrado:\n";
                    cout << "ID: " << p->id << ", Nombre: " << p->nombre 
                         << ", Prioridad: " << p->prioridad << "\n";
                } else {
                    cout << "Proceso no encontrado.\n";
                }
                break;
            }
            case 4: {
                int id, nuevaPrioridad;
                cout << "ID del proceso: ";
                cin >> id;
                cout << "Nueva prioridad (1-10): ";
                cin >> nuevaPrioridad;
                gestor.modificarPrioridad(id, nuevaPrioridad);
                break;
            }
            case 5:
                gestor.mostrarProcesos();
                break;
            case 6: {
                int id;
                cout << "ID del proceso a encolar: ";
                cin >> id;
                NodoProceso* p = gestor.buscarProceso(id);
                if (p) {
                    cpu.encolarProceso(p);
                } else {
                    cout << "Proceso no encontrado.\n";
                }
                break;
            }
            case 7:
                cpu.ejecutarProceso();
                break;
            case 8:
                cpu.mostrarColaCPU();
                break;
            case 9: {
                int cantidad;
                cout << "Cantidad de memoria a asignar (MB): ";
                cin >> cantidad;
                memoria.asignarMemoria(cantidad);
                break;
            }
            case 10: {
                int cantidad;
                cout << "Cantidad de memoria a liberar (MB): ";
                cin >> cantidad;
                memoria.liberarMemoria(cantidad);
                break;
            }
            case 11:
                memoria.mostrarEstadoMemoria();
                break;
            case 0:
                cout << "Saliendo del sistema...\n";
                break;
            default:
                cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);
    
    system("pause");
    return 0;
}
