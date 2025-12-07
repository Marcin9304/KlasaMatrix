#include "matrix.h"
#include <cstdlib> // rand, srand
#include <ctime>   // time
#include <cmath>   // static_cast, floor
#include <memory>  // make_unique (dodane dla poprawności kompilacji)

// =========================================================
// KONSTRUKTORY I DESTRUKTOR
// =========================================================

// Konstruktor domyślny
matrix::matrix(void) : n(0), capacity(0), data(nullptr) {
}

// Konstruktor alokujący macierz n na n
matrix::matrix(int n) : n(0), capacity(0), data(nullptr) {
    alokuj(n);
}

// Konstruktor alokujący i przepisujący dane z tabeli
matrix::matrix(int n, int* t) : n(0), capacity(0), data(nullptr) {
    alokuj(n);
    if (t != nullptr) {
        for (int i = 0; i < n * n; i++) {
            data[i] = t[i];
        }
    }
}

// Konstruktor kopiujący (głęboka kopia)
matrix::matrix(matrix& m) : n(0), capacity(0), data(nullptr) {
    alokuj(m.n);
    for (int i = 0; i < n * n; i++) {
        data[i] = m.data[i];
    }
}

// Destruktor
matrix::~matrix(void) {
    // unique_ptr automatycznie zwalnia pamięć
}

// =========================================================
// ZARZĄDZANIE PAMIĘCIĄ
// =========================================================

// Metoda alokuj (Kluczowa logika optymalizacji)
matrix& matrix::alokuj(int n) {
    if (n < 0) return *this;
    int req_size = n * n; // Wymagana wielkość

    if (data == nullptr) {
        // Sytuacja 1: Macierz pusta, alokujemy nową
        this->n = n;
        this->capacity = req_size;
        data = make_unique<int[]>(req_size);
        for (int i = 0; i < req_size; i++) data[i] = 0;
    }
    else {
        // Sytuacja 2: Macierz już istnieje
        if (this->capacity < req_size) {
            // Pamięci jest za mało -> realokacja
            data.reset(); // Zwolnij starą
            this->n = n;
            this->capacity = req_size;
            data = make_unique<int[]>(req_size);
            for (int i = 0; i < req_size; i++) data[i] = 0;
        }
        else {
            // Pamięci jest więcej lub tyle samo -> zostawiamy alokację
            // Zmieniamy tylko logiczny wymiar n
            this->n = n;
            // capacity pozostaje bez zmian (stare, większe)
        }
    }
    return *this;
}

// =========================================================
// METODY DOSTĘPU I MODYFIKACJI
// =========================================================

// Wstawianie wartości
matrix& matrix::wstaw(int x, int y, int wartosc) {
    if (x >= 0 && x < n && y >= 0 && y < n) {
        data[x * n + y] = wartosc;
    }
    return *this;
}

// Pobieranie wartości
int matrix::pokaz(int x, int y) {
    if (x >= 0 && x < n && y >= 0 && y < n) {
        return data[x * n + y];
    }
    return 0; // Wartość błędu
}

// Transpozycja (odwrócenie)
matrix& matrix::dowroc(void) {
    auto temp = make_unique<int[]>(n * n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // Zamiana wiersza z kolumną
            temp[j * n + i] = data[i * n + j];
        }
    }
    // Przepisanie z powrotem
    for (int k = 0; k < n * n; k++) {
        data[k] = temp[k];
    }
    return *this;
}

// Losowanie 0-9
matrix& matrix::losuj(void) {
    for (int i = 0; i < n * n; i++) {
        data[i] = rand() % 10;
    }
    return *this;
}

// Losowanie x elementów
matrix& matrix::losuj(int x) {
    // Czyścimy macierz przed losowaniem miejsc
    for (int i = 0; i < n * n; i++) data[i] = 0;

    if (x > n * n) x = n * n;

    int wstawione = 0;
    while (wstawione < x) {
        int r = rand() % n;
        int c = rand() % n;
        // Jeśli komórka jest pusta (0), wstawiamy
        if (pokaz(r, c) == 0) {
            wstaw(r, c, rand() % 10);
            wstawione++;
        }
    }
    return *this;
}

// =========================================================
// METODY WYPEŁNIAJĄCE (Szablony)
// =========================================================

// Diagonalna
matrix& matrix::diagonalna(int* t) {
    if (!t) return *this;
    for (int i = 0; i < n * n; i++) data[i] = 0;
    for (int i = 0; i < n; i++) {
        wstaw(i, i, t[i]);
    }
    return *this;
}

// Diagonalna przesunięta o k
matrix& matrix::diagonalna_k(int k, int* t) {
    if (!t) return *this;
    for (int i = 0; i < n * n; i++) data[i] = 0;

    int t_idx = 0;
    for (int i = 0; i < n; i++) {
        int j = i + k; // Przesunięcie kolumny
        if (j >= 0 && j < n) {
            wstaw(i, j, t[t_idx++]);
        }
    }
    return *this;
}

// Kolumna
matrix& matrix::kolumna(int x, int* t) {
    if (x >= 0 && x < n && t) {
        for (int i = 0; i < n; i++) {
            wstaw(i, x, t[i]);
        }
    }
    return *this;
}

// Wiersz
matrix& matrix::wiersz(int y, int* t) {
    if (y >= 0 && y < n && t) {
        for (int j = 0; j < n; j++) {
            wstaw(y, j, t[j]);
        }
    }
    return *this;
}

// Przekątna (1 na środku)
matrix& matrix::przekatna(void) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) wstaw(i, j, 1);
            else wstaw(i, j, 0);
        }
    }
    return *this;
}

// Pod przekątną
matrix& matrix::pod_przekatna(void) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i > j) wstaw(i, j, 1);
            else wstaw(i, j, 0);
        }
    }
    return *this;
}

// Nad przekątną
matrix& matrix::nad_przekatna(void) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i < j) wstaw(i, j, 1);
            else wstaw(i, j, 0);
        }
    }
    return *this;
}

// Szachownica
matrix& matrix::szachownica(void) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // Jeśli suma indeksów jest nieparzysta -> 1, parzysta -> 0
            if ((i + j) % 2 != 0) wstaw(i, j, 1);
            else wstaw(i, j, 0);
        }
    }
    return *this;
}

// =========================================================
// OPERATORY WEWNĘTRZNE (Modyfikują obiekt *this)
// =========================================================

// A + B
matrix& matrix::operator+(matrix& m) {
    if (this->n == m.n) {
        for (int i = 0; i < n * n; i++) {
            data[i] += m.data[i];
        }
    }
    return *this;
}

// A * B (Mnożenie macierzowe)
matrix& matrix::operator*(matrix& m) {
    if (this->n != m.n) return *this;

    // Używamy bufora tymczasowego, bo wynik komórki zależy od całego wiersza
    auto temp = make_unique<int[]>(n * n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int sum = 0;
            for (int k = 0; k < n; k++) {
                sum += this->pokaz(i, k) * m.pokaz(k, j);
            }
            temp[i * n + j] = sum;
        }
    }
    // Przepisanie wyniku
    for (int i = 0; i < n * n; i++) data[i] = temp[i];
    return *this;
}

// A + int
matrix& matrix::operator+(int a) {
    for (int i = 0; i < n * n; i++) data[i] += a;
    return *this;
}

// A * int
matrix& matrix::operator*(int a) {
    for (int i = 0; i < n * n; i++) data[i] *= a;
    return *this;
}

// A - int
matrix& matrix::operator-(int a) {
    for (int i = 0; i < n * n; i++) data[i] -= a;
    return *this;
}

// =========================================================
// OPERATORY FRIEND (Zewnętrzne - tworzą nową macierz)
// =========================================================

// int + A
matrix operator+(int a, matrix& m) {
    matrix wynik(m.n);
    // Dostęp do m.n i m.pokaz jest możliwy (friend)
    for (int i = 0; i < m.n; i++) {
        for (int j = 0; j < m.n; j++) {
            wynik.wstaw(i, j, a + m.pokaz(i, j));
        }
    }
    return wynik;
}

// int * A
matrix operator*(int a, matrix& m) {
    matrix wynik(m.n);
    for (int i = 0; i < m.n; i++) {
        for (int j = 0; j < m.n; j++) {
            wynik.wstaw(i, j, a * m.pokaz(i, j));
        }
    }
    return wynik;
}

// int - A
matrix operator-(int a, matrix& m) {
    matrix wynik(m.n);
    for (int i = 0; i < m.n; i++) {
        for (int j = 0; j < m.n; j++) {
            wynik.wstaw(i, j, a - m.pokaz(i, j));
        }
    }
    return wynik;
}

// =========================================================
// POZOSTAŁE OPERATORY
// =========================================================

// A++
matrix& matrix::operator++(int) {
    for (int i = 0; i < n * n; i++) data[i]++;
    return *this;
}

// A--
matrix& matrix::operator--(int) {
    for (int i = 0; i < n * n; i++) data[i]--;
    return *this;
}

// Przypisania złożone
matrix& matrix::operator+=(int a) { return *this + a; }
matrix& matrix::operator-=(int a) { return *this - a; }
matrix& matrix::operator*=(int a) { return *this * a; }

// Operator funkcyjny (część całkowita z double)
matrix& matrix::operator()(double a) {
    int val = static_cast<int>(a);
    for (int i = 0; i < n * n; i++) data[i] += val;
    return *this;
}

// =========================================================
// OPERATORY PORÓWNANIA
// =========================================================

// A == B
bool matrix::operator==(const matrix& m) {
    if (n != m.n) return false;
    for (int i = 0; i < n * n; i++) {
        if (data[i] != m.data[i]) return false;
    }
    return true;
}

// A > B
bool matrix::operator>(const matrix& m) {
    if (n != m.n) return false;
    // Warunek: KAŻDY element musi być większy
    for (int i = 0; i < n * n; i++) {
        if (data[i] <= m.data[i]) return false;
    }
    return true;
}

// A < B
bool matrix::operator<(const matrix& m) {
    if (n != m.n) return false;
    // Warunek: KAŻDY element musi być mniejszy
    for (int i = 0; i < n * n; i++) {
        if (data[i] >= m.data[i]) return false;
    }
    return true;
}

// =========================================================
// OPERATOR STRUMIENIOWY
// =========================================================

// Wypisanie macierzy
ostream& operator<<(ostream& o, matrix& m) {
    for (int i = 0; i < m.n; i++) {
        for (int j = 0; j < m.n; j++) {
            o << m.pokaz(i, j) << "\t";
        }
        o << endl;
    }
    return o;
}