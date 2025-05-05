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
        while (turno == 1) {
            while (S2) {
                cout << "P1 esperando..." << endl;
                esperar(500);
            }
            turno = 1;
        }
        cout << "P1 entra en la SECCIÓN CRÍTICA" << endl;
        suma += 1;
        cout << "Suma actual: " << suma << endl;
        esperar(1000);
        S1 = false;
        cout << "P1 fuera de la sección crítica\n" << endl;
        esperar(1000);
    }
}

void P2() {
    while (true) {
        S2 = true;
        while (turno == 2) {
            while (S1) {
                cout << "P2 esperando..." << endl;
                esperar(500);
            }
            turno = 2;
        }
        cout << "P2 entra en la SECCIÓN CRÍTICA" << endl;
        suma += 1;
        cout << "Suma actual: " << suma << endl;
        esperar(1000);
        S2 = false;
        cout << "P2 fuera de la sección crítica\n" << endl;
        esperar(1000);
    }
}

int main() {
    thread t1(P1);
    thread t2(P2);
    t1.join();
    t2.join();
    return 0;
}
