#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Proceso {
    int id;
    string nombre;
};

vector<Proceso> cola;

void enqueue(const Proceso & p) {
    cola.push_back(p);
    cout << "Proceso encolado: " << p.id << " - " << p.nombre << endl;
}

int main() {
    Proceso p1 = {1, "Proceso A"};
    Proceso p2 = {2, "Proceso B"};
    enqueue(p1);
    enqueue(p2);
    return 0;
}

