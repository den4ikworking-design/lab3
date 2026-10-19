#include <iostream>
#include "guesser.h"
using namespace std;

const int MAXC = 5040; // 10*9*8*7 чисел из 4 различных цифр

// Заполняет список всех возможных чисел, возвращает их количество
static int buildCandidates(int cand[MAXC][LEN]) {
    int n = 0;
    for (int a = 0; a < 10; a++)
        for (int b = 0; b < 10; b++) {
            if (b == a) continue;
            for (int c = 0; c < 10; c++) {
                if (c == a || c == b) continue;
                for (int d = 0; d < 10; d++) {
                    if (d == a || d == b || d == c) continue;
                    cand[n][0] = a; cand[n][1] = b;
                    cand[n][2] = c; cand[n][3] = d;
                    n++;
                }
            }
        }
    return n;
}

// Оставляет только числа, дающие тот же ответ на догадку
static int filterCandidates(int cand[MAXC][LEN], int n, const int guess[LEN],
                            int bulls, int cows) {
    int m = 0;
    for (int i = 0; i < n; i++) {
        int b, c;
        countBullsCows(cand[i], guess, b, c);
        if (b == bulls && c == cows) {
            for (int k = 0; k < LEN; k++) cand[m][k] = cand[i][k];
            m++;
        }
    }
    return m;
}

static void printNumber(const int x[LEN]) {
    for (int i = 0; i < LEN; i++) cout << x[i];
}

int playComputer() {
    static int cand[MAXC][LEN];
    int n = buildCandidates(cand);
    cout << "Загадайте число из " << LEN << " различных цифр.\n"
         << "Отвечайте на вопросы: сколько быков и сколько коров." << endl;
    int tries = 0;
    while (n > 0) {
        int guess[LEN];
        for (int k = 0; k < LEN; k++) guess[k] = cand[0][k];
        tries++;
        cout << "Попытка " << tries << ": ";
        printNumber(guess);
        cout << endl << "Быков и коров (два числа через пробел): ";
        int b, c;
        if (!(cin >> b >> c)) return -1; // ввод закончился
        if (b == LEN) {
            cout << "Угадал за " << tries << " попыток!" << endl;
            return tries;
        }
        n = filterCandidates(cand, n, guess, b, c);
    }
    cout << "Ответы противоречивы: подходящих чисел не осталось." << endl;
    return -1;
}

int autoGuess(const int secret[LEN]) {
    static int cand[MAXC][LEN];
    int n = buildCandidates(cand);
    int tries = 0;
    while (n > 0) {
        int guess[LEN];
        for (int k = 0; k < LEN; k++) guess[k] = cand[0][k];
        tries++;
        int b, c;
        countBullsCows(secret, guess, b, c);
        if (b == LEN) return tries;
        n = filterCandidates(cand, n, guess, b, c);
    }
    return -1;
}
