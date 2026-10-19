#ifndef GAME_H
#define GAME_H

const int LEN = 4; // длина загадываемого числа

// Загадывает число из LEN различных цифр
void generateSecret(int secret[LEN]);

// Разбирает строку: true, если в ней ровно LEN различных цифр
bool parseGuess(const char *s, int guess[LEN]);

// Считает количество быков и коров
void countBullsCows(const int secret[LEN], const int guess[LEN],
                    int &bulls, int &cows);

// Выводит ответ вида "1 бык и 1 корова"
void printResult(int bulls, int cows);

// Игра: пользователь угадывает число. Возвращает число попыток
int playUser();

#endif
