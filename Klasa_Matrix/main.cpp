#include "matrix.h"
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

/// @brief Funkcja glowna programu testujacego klase matrix.
/// Uruchamia wszystkie metody celem sprawdzenia poprawnosci.
int main() {
    srand(static_cast<unsigned int>(time(NULL))); // Inicjalizacja generatora liczb losowych

    cout << "=== TESTY PROJEKTU MATRIX ===" << endl;

    // --- 1. Test alokacji i losowania ---
    cout << "\n[TEST] Tworzenie macierzy 5x5 i losowanie:" << endl;
    matrix m1(5);
    m1.losuj();
    cout << m1;

    // --- 2. Test realokacji (metoda alokuj) ---
    cout << "\n[TEST] Zwiekszenie do 10x10 (wymusza realokacje):" << endl;
    m1.alokuj(10); // Powinno zwolnic stara i dac nowa
    m1.losuj();

    // POPRAWKA TUTAJ: Odkomentowano wypisywanie macierzy
    cout << m1;

    cout << "\n[TEST] Zmniejszenie do 3x3 (nie zwalnia pamieci, tylko zmienia n):" << endl;
    m1.alokuj(3);
    m1.losuj();
    cout << m1;

    // --- 3. Test duzej skali ---
    cout << "\n[TEST] Test na n=30:" << endl;
    matrix mBig(30);
    mBig.losuj();
    // Operacje na mBig...
    cout << "Macierz 30x30 utworzona pomyslnie." << endl;

    // Jeœli chcesz widzieæ te¿ tê du¿¹ macierz, odkomentuj liniê poni¿ej:
    // cout << mBig << endl;

    // --- 4. Miejsce na Wasze testy metod ---
    // Np. matrix m2(3); m2.szachownica(); cout << m2;
    // Np. m1 + m2;

    // Opcjonalne zatrzymanie konsoli (jeœli u¿ywasz Visual Studio i okno znika)
    // system("pause");

    return 0;
}