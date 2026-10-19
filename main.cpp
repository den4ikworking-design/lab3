#ifdef _WIN32
#include <windows.h>
#endif // _WIN32
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "game.h"
#include "guesser.h"
using namespace std;

int main(int argc, char *argv[]) {
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif // _WIN32
    srand(time(0));

    // Режим самопроверки: ./bulls test  — компьютер угадывает 20 случайных чисел
    if (argc > 1 && string(argv[1]) == "test") {
        int worst = 0, sum = 0;
        for (int i = 0; i < 20; i++) {
            int s[LEN];
            generateSecret(s);
            int t = autoGuess(s);
            sum += t;
            if (t > worst) worst = t;
        }
        cout << "Среднее число попыток: " << sum / 20.0
             << ", максимум: " << worst << endl;
        return 0;
    }

    int choice;
    do {
        cout << "\n=== Быки и коровы ===\n"
             << "1. Я угадываю число компьютера\n"
             << "2. Компьютер угадывает моё число\n"
             << "0. Выход\n> ";
        cin >> choice;
        if (choice == 1) playUser();
        else if (choice == 2) playComputer();
    } while (choice != 0 && cin);
    return 0;
}
