#pragma once
#include <iostream>
#include <memory> // unique_ptr
#include <algorithm>
#include <vector>

using namespace std;

/// @brief Klasa reprezentujaca macierz kwadratowa z zarzadzaniem pamiecia dynamiczna.
/// [cite: 2] Klasa korzysta z unique_ptr.
class matrix {
private:
    /// @brief Wskaznik unique_ptr na tablice dynamiczna przechowujaca dane macierzy.
    unique_ptr<int[]> data;

    /// @brief Aktualny logiczny wymiar macierzy (n x n).
    int n;

    /// @brief Rzeczywista zaalokowana wielkosc tablicy (pojemnosc).
    /// Uzywana do optymalizacji metody alokuj.
    int capacity;

public:
    // --- Konstruktory i Destruktor ---

    /// @brief Konstruktor domyslny bez alokacji pamieci [cite: 6-7].
    matrix(void);

    /// @brief Konstruktor przeciazeniowy alokuje macierz o wymiarach n na n [cite: 8-10].
    /// @param n Wielkosc macierzy.
    matrix(int n);

    /// @brief Konstruktor przeciazeniowy alokuje pamiec i przepisuje dane z tabeli [cite: 11-13].
    /// @param n Wielkosc macierzy.
    /// @param t Wskaznik na tablice danych.
    matrix(int n, int* t);

    /// @brief Konstruktor kopiujacy[cite: 14, 16].
    /// Wykonuje gleboka kopie danych.
    /// @param m Referencja do macierzy kopiowanej.
    matrix(matrix& m);

    /// @brief Destruktor[cite: 15, 17].
    /// Pamiec jest zwalniana automatycznie przez unique_ptr.
    ~matrix(void);

    // --- Zarzadzanie pamiecia ---

    /// @brief Zarzadza alokacja pamieci dla macierzy .
    /// Jesli pamieci jest za malo, realokuje ja. Jesli jest wystarczajaco, pozostawia bez zmian.
    /// @param n Nowy wymiar macierzy.
    /// @return Referencja do obiektu macierzy.
    matrix& alokuj(int n);

    // --- Metody dostepu i modyfikacji ---

    /// @brief Wstawia wartosc do komorki macierzy[cite: 22].
    /// @param x Numer wiersza.
    /// @param y Numer kolumny.
    /// @param wartosc Wartosc do wstawienia.
    /// @return Referencja do macierzy.
    matrix& wstaw(int x, int y, int wartosc);

    /// @brief Zwraca wartosc elementu x, y[cite: 22, 24].
    /// @param x Numer wiersza.
    /// @param y Numer kolumny.
    /// @return Wartosc int z danej komorki.
    int pokaz(int x, int y);

    /// @brief Zamienia wiersze z kolumnami (transpozycja)[cite: 23, 25].
    /// @return Referencja do macierzy.
    matrix& dowroc(void);

    /// @brief Wypelnia macierz losowymi cyframi od 0 do 9 [cite: 26-28].
    /// @return Referencja do macierzy.
    matrix& losuj(void);

    /// @brief Wypelnia losowymi cyframi (0-9) tylko x elementow macierzy [cite: 29-32].
    /// Algorytm losuje miejsca wstawienia.
    /// @param x Liczba elementow do wylosowania.
    /// @return Referencja do macierzy.
    matrix& losuj(int x);

    // --- Wypelnianie ksztaltami ---

    /// @brief Wpisuje dane z tabeli po przekatnej, reszta 0 [cite: 33-35].
    /// @param t Tablica wartosci na przekatna.
    /// @return Referencja do macierzy.
    matrix& diagonalna(int* t);

    /// @brief Wpisuje dane z tabeli po przekatnej przesunietej o k [cite: 36-39].
    /// k=0 srodek, k>0 gora, k<0 dol.
    /// @param k Przesuniecie przekatnej.
    /// @param t Tablica wartosci.
    /// @return Referencja do macierzy.
    matrix& diagonalna_k(int k, int* t);

    /// @brief Przepisuje dane z tabeli do kolumny x [cite: 40-41].
    /// @param x Numer kolumny.
    /// @param t Tablica danych.
    /// @return Referencja do macierzy.
    matrix& kolumna(int x, int* t);

    /// @brief Przepisuje dane z tabeli do wiersza y [cite: 41-42].
    /// @param y Numer wiersza.
    /// @param t Tablica danych.
    /// @return Referencja do macierzy.
    matrix& wiersz(int y, int* t);

    /// @brief Uzupelnia macierz: 1 na przekatnej, 0 poza[cite: 43, 46].
    /// @return Referencja do macierzy.
    matrix& przekatna(void);

    /// @brief Uzupelnia macierz: 1 pod przekatna, 0 nad i na przekatnej[cite: 47].
    /// @return Referencja do macierzy.
    matrix& pod_przekatna(void);

    /// @brief Uzupelnia macierz: 1 nad przekatna, 0 pod i na przekatnej[cite: 52].
    /// @return Referencja do macierzy.
    matrix& nad_przekatna(void);

    /// @brief Uzupelnia macierz wzorem szachownicy (0101...) [cite: 53-58].
    /// @return Referencja do macierzy.
    matrix& szachownica(void);

    // --- Operatory Arytmetyczne ---

    /// @brief Dodawanie dwoch macierzy (A+B) [cite: 59-60].
    matrix& operator+(matrix& m);

    /// @brief Mnozenie dwoch macierzy (A*B) [cite: 61-62].
    matrix& operator*(matrix& m);

    /// @brief Dodawanie liczby do macierzy (A+int) [cite: 63-64].
    matrix& operator+(int a);

    /// @brief Mnozenie macierzy przez liczbe (A*int) [cite: 65-66].
    matrix& operator*(int a);

    /// @brief Odejmowanie liczby od macierzy (A-int) [cite: 67-68].
    matrix& operator-(int a);

    // --- Friend Operators (int op A) ---

    /// @brief Dodawanie int + Macierz [cite: 70-71].
    friend matrix operator+(int a, matrix& m);

    /// @brief Mnozenie int * Macierz [cite: 72-73].
    friend matrix operator*(int a, matrix& m);

    /// @brief Odejmowanie int - Macierz [cite: 74-75].
    friend matrix operator-(int a, matrix& m);

    // --- Inkrementacja / Dekrementacja ---

    /// @brief Postinkrementacja A++ (wszystkie liczby +1) [cite: 76-78].
    matrix& operator++(int);

    /// @brief Postdekrementacja A-- (wszystkie liczby -1) [cite: 79-81].
    matrix& operator--(int);

    // --- Operatory przypisania zlozonego ---

    /// @brief Kazdy element powiekszamy o a (A+=a) [cite: 82-83].
    matrix& operator+=(int a);

    /// @brief Kazdy element pomniejszamy o a (A-=a) [cite: 84-85].
    matrix& operator-=(int a);

    /// @brief Kazdy element mnozymy o a (A*=a) [cite: 86-87].
    matrix& operator*=(int a);

    // --- Operator funkcyjny ---

    /// @brief Wszystkie cyfry powiekszone o czesc calkowita z wpisanej cyfry [cite: 88-90].
    matrix& operator()(double);

    // --- Operatory Porownania ---

    /// @brief Sprawdza czy kazdy element macierzy spelnia rownosc [cite: 92-99].
    bool operator==(const matrix& m);

    /// @brief Sprawdza czy kazdy element spelnia nierownosc A > B[cite: 101].
    bool operator>(const matrix& m);

    /// @brief Sprawdza czy kazdy element spelnia nierownosc A < B [cite: 102-103].
    bool operator<(const matrix& m);

    // --- Operator strumieniowy ---

    /// @brief Wypisanie macierzy do strumienia[cite: 91].
    friend ostream& operator<<(ostream& o, matrix& m);
};