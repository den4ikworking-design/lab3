#include <iostream>
#include <cstdlib>
#include <cstring>
#include "game.h"
using namespace std;

void generateSecret(int secret[LEN]) {
    bool used[10] = {false};
    for (int i = 0; i < LEN; i++) {
        int d;
        do {
            d = rand() % 10;
        } while (used[d]);
        used[d] = true;
        secret[i] = d;
    }
}

bool parseGuess(const char *s, int guess[LEN]) {
    if ((int)strlen(s) != LEN) return false;
    bool used[10] = {false};
    for (int i = 0; i < LEN; i++) {
        if (s[i] < '0' || s[i] > '9') return false;
        int d = s[i] - '0';
        if (used[d]) return false;
        used[d] = true;
        guess[i] = d;
    }
    return true;
}

void countBullsCows(const int secret[LEN], const int guess[LEN],
                    int &bulls, int &cows) {
    bulls = 0;
    cows = 0;
    for (int i = 0; i < LEN; i++)
        for (int j = 0; j < LEN; j++)
            if (guess[i] == secret[j]) {
                if (i == j) bulls++;
                else cows++;
            }
}

static const char *word(int n, const char *one, const char *few,
                        const char *many) {
    if (n % 10 == 1 && n % 100 != 11) return one;
    if (n % 10 >= 2 && n % 10 <= 4 && (n % 100 < 10 || n % 100 >= 20))
        return few;
    return many;
}

void printResult(int bulls, int cows) {
    cout << bulls << " " << word(bulls, "бык", "быка", "быков") << " и "
         << cows << " " << word(cows, "корова", "коровы", "коров") << endl;
}

int playUser() {
    int secret[LEN], guess[LEN];
    generateSecret(secret);
    cout << "Компьютер загадал число из " << LEN
         << " различных цифр. Угадывайте!" << endl;
    int tries = 0;
    while (true) {
        cout << "Ваш вариант: ";
        char buf[100];
        if (!(cin >> buf)) return -1; // ввод закончился
        if (!parseGuess(buf, guess)) {
            cout << "Нужно ввести " << LEN << " различных цифры." << endl;
            continue;
        }
        tries++;
        int b, c;
        countBullsCows(secret, guess, b, c);
        printResult(b, c);
        if (b == LEN) break;
    }
    cout << "Угадали за " << tries << " попыток!" << endl;
    return tries;
}
