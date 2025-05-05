#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

using namespace std;

atomic<bool> S1(false), S2(false);
atomic<int> turno(1);
int suma = 0;

void esperar(int ms) {
    this_thread::sleep_for(chrono::milliseconds(ms));
}

void P1() {
    while (true) {
        S1 = true;
        turno = 2;
        while (S2 && turno == 2) {
            cout << "Esperando(P1)...." << endl;
            esperar(500);
        }

        cout << "El proceso 1 se encuentra en su seccion critica (SC):" << endl;
        suma += 1;
        cout << "La suma total es: " << suma << endl;
        esperar(1000);

        S1 = false;
    }
}

void P2() {
    while (true) {
        S2 = true;
        turno = 1;
        while (S1 && turno == 1) {
            cout << "Esperando(P2)...." << endl;
            esperar(500);
        }

        cout << "El proceso 2 se encuentra en su seccion critica (SC):" << endl;
        suma += 2;
        cout << "La suma total es: " << suma << endl;
        esperar(1000);

        S2 = false;
    }
}

int main() {
    thread t1(P1);
    thread t2(P2);

    t1.join();
    t2.join();

    return 0;
}
