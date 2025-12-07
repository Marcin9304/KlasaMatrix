#include "matrix.h"
#include <cstdlib> // rand, srand
#include <ctime>   // time
#include <cmath>   // static_cast, floor

// =========================================================
// KONSTRUKTORY I DESTRUKTOR
// =========================================================

[cite_start]// Konstruktor domyślny [cite: 6-7]
matrix::matrix(void) : n(0), capacity(0), data(nullptr) {
}

[cite_start]// Konstruktor alokujący macierz n na n [cite: 8-10]
matrix::matrix(int n) : n(0), capacity(0), data(nullptr) {
    alokuj(n);
}

[cite_start]// Konstruktor alokujący i przepisujący dane z tabeli [cite: 11-13]
matrix::matrix(int n, int* t) : n(0), capacity(0), data(nullptr) {
    alokuj(n);
    if (t != nullptr) {
        for (int i = 0; i < n * n; i++) {
            data[i] = t[i];
        }
    }
}

[cite_start]// Konstruktor kopiujący (głęboka kopia) [cite: 14, 16]
matrix::matrix(matrix& m) : n(0), capacity(0), data(nullptr) {
    alokuj(m.n);
    for (int i = 0; i < n * n; i++) {
        data[i] = m.data[i];
    }
}

[cite_start]// Destruktor [cite: 15, 17]
matrix::~matrix(void) {
    // unique_ptr automatycznie zwalnia pamięć
}

// =========================================================
// ZARZĄDZANIE PAMIĘCIĄ
// =========================================================

// Metoda alokuj (Kluczowa logika optymalizacji) [cite: 19-24]
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
            // [cite: 23] Pamięci jest za mało -> realokacja
            data.reset(); // Zwolnij starą
            this->n = n;
            this->capacity = req_size;
            data = make_unique<int[]>(req_size);
            for (int i = 0; i < req_size; i++) data[i] = 0;
        }
        else {
            // [cite: 24] Pamięci jest więcej lub tyle samo -> zostawiamy alokację
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

[cite_start]// Wstawianie wartości [cite: 22]
matrix& matrix::wstaw(int x, int y, int wartosc) {
    if (x >= 0 && x < n && y >= 0 && y < n) {
        data[x * n + y] = wartosc;
    }
    return *this;
}

[cite_start]// Pobieranie wartości [cite: 22, 24]
int matrix::pokaz(int x, int y) {
    if (x >= 0 && x < n && y >= 0 && y < n) {
        return data[x * n + y];
    }
    return 0; // Wartość błędu
}

[cite_start]// Transpozycja (odwrócenie) [cite: 23, 25]
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

[cite_start]// Losowanie 0-9 [cite: 26-28]
matrix& matrix::losuj(void) {
    for (int i = 0; i < n * n; i++) {
        data[i] = rand() % 10;
    }
    return *this;
}

[cite_start]// Losowanie x elementów [cite: 29-32]
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

[cite_start]// Diagonalna [cite: 33-35]
matrix& matrix::diagonalna(int* t) {
    if (!t) return *this;
    for (int i = 0; i < n * n; i++) data[i] = 0;
    for (int i = 0; i < n; i++) {
        wstaw(i, i, t[i]);
    }
    return *this;
}

[cite_start]// Diagonalna przesunięta o k [cite: 36-39]
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

[cite_start]// Kolumna [cite: 40-41]
matrix& matrix::kolumna(int x, int* t) {
    if (x >= 0 && x < n && t) {
        for (int i = 0; i < n; i++) {
            wstaw(i, x, t[i]);
        }
    }
    return *this;
}

[cite_start]// Wiersz [cite: 41-42]
matrix& matrix::wiersz(int y, int* t) {
    if (y >= 0 && y < n && t) {
        for (int j = 0; j < n; j++) {
            wstaw(y, j, t[j]);
        }
    }
    return *this;
}

[cite_start]// Przekątna (1 na środku) [cite: 43-46]
matrix& matrix::przekatna(void) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) wstaw(i, j, 1);
            else wstaw(i, j, 0);
        }
    }
    return *this;
}

[cite_start]// Pod przekątną [cite: 47]
matrix& matrix::pod_przekatna(void) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i > j) wstaw(i, j, 1);
            else wstaw(i, j, 0);
        }
    }
    return *this;
}

[cite_start]// Nad przekątną [cite: 52]
matrix& matrix::nad_przekatna(void) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i < j) wstaw(i, j, 1);
            else wstaw(i, j, 0);
        }
    }
    return *this;
}

[cite_start]// Szachownica [cite: 53-58]
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

[cite_start]// A + B [cite: 59-60]
matrix& matrix::operator+(matrix& m) {
    if (this->n == m.n) {
        for (int i = 0; i < n * n; i++) {
            data[i] += m.data[i];
        }
    }
    return *this;
}

[cite_start]// A * B (Mnożenie macierzowe) [cite: 61-62]
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

[cite_start]// A + int [cite: 63-64]
matrix& matrix::operator+(int a) {
    for (int i = 0; i < n * n; i++) data[i] += a;
    return *this;
}

[cite_start]// A * int [cite: 65-66]
matrix& matrix::operator*(int a) {
    for (int i = 0; i < n * n; i++) data[i] *= a;
    return *this;
}

[cite_start]// A - int [cite: 67-68]
matrix& matrix::operator-(int a) {
    for (int i = 0; i < n * n; i++) data[i] -= a;
    return *this;
}

// =========================================================
// OPERATORY FRIEND (Zewnętrzne - tworzą nową macierz)
// =========================================================

[cite_start]// int + A [cite: 70-71]
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

[cite_start]// int * A [cite: 72-73]
matrix operator*(int a, matrix& m) {
    matrix wynik(m.n);
    for (int i = 0; i < m.n; i++) {
        for (int j = 0; j < m.n; j++) {
            wynik.wstaw(i, j, a * m.pokaz(i, j));
        }
    }
    return wynik;
}

[cite_start]// int - A [cite: 74-75]
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

[cite_start]// A++ [cite: 76-78]
matrix& matrix::operator++(int) {
    for (int i = 0; i < n * n; i++) data[i]++;
    return *this;
}

[cite_start]// A-- [cite: 79-81]
matrix& matrix::operator--(int) {
    for (int i = 0; i < n * n; i++) data[i]--;
    return *this;
}

[cite_start]// Przypisania złożone [cite: 82-87]
matrix& matrix::operator+=(int a) { return *this + a; }
matrix& matrix::operator-=(int a) { return *this - a; }
matrix& matrix::operator*=(int a) { return *this * a; }

[cite_start]// Operator funkcyjny (część całkowita z double) [cite: 88-90]
matrix& matrix::operator()(double a) {
    int val = static_cast<int>(a);
    for (int i = 0; i < n * n; i++) data[i] += val;
    return *this;
}

// =========================================================
// OPERATORY PORÓWNANIA
// =========================================================

[cite_start]// A == B [cite: 92-95]
bool matrix::operator==(const matrix& m) {
    if (n != m.n) return false;
    for (int i = 0; i < n * n; i++) {
        if (data[i] != m.data[i]) return false;
    }
    return true;
}

[cite_start]// A > B [cite: 101]
bool matrix::operator>(const matrix& m) {
    if (n != m.n) return false;
    // Warunek: KAŻDY element musi być większy
    for (int i = 0; i < n * n; i++) {
        if (data[i] <= m.data[i]) return false;
    }
    return true;
}

[cite_start]// A < B [cite: 102-103]
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

[cite_start]// Wypisanie macierzy [cite: 91]
ostream& operator<<(ostream& o, matrix& m) {
    for (int i = 0; i < m.n; i++) {
        for (int j = 0; j < m.n; j++) {
            o << m.pokaz(i, j) << "\t";
        }
        o << endl;
    }
    return o;
}