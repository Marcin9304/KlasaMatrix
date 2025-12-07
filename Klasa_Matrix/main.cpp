#include "matrix.h"
#include <iostream>
#include <fstream> // Potrzebne do zapisu do pliku
#include <ctime>

using namespace std;

/// @brief Funkcja glowna programu testujacego klase matrix.
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

    // Teraz wyœwietlamy macierz, która dziêki setw(3) bêdzie równa
    cout << m1;

    cout << "\n[TEST] Zmniejszenie do 3x3 (nie zwalnia pamieci, tylko zmienia n):" << endl;
    m1.alokuj(3);
    m1.losuj();
    cout << m1;

    // --- 3. Test duzej skali ---
    cout << "\n[TEST] Test na n=30:" << endl;
    matrix mBig(30);
    mBig.losuj();

    // ZAPIS DO PLIKU (¿eby nie psuæ widoku w konsoli)
    cout << "Zapisuje macierz 30x30 do pliku 'wynik_matrix.txt'..." << endl;
    ofstream plik("wynik_matrix.txt");
    if (plik.is_open()) {
        plik << mBig;
        plik.close();
        cout << "SUKCES: Sprawdz plik 'wynik_matrix.txt' w folderze projektu." << endl;
    }
    else {
        cout << "BLAD: Nie udalo sie otworzyc pliku do zapisu." << endl;
    }

    // --- 4. Miejsce na Wasze testy metod ---
    // Np. matrix m2(3); m2.szachownica(); cout << m2;

    // Opcjonalne zatrzymanie konsoli
    // system("pause");

    return 0;
}