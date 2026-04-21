#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <clocale>

using std::cout;
using std::cin;
using std::endl;
using std::string;


void ClearMaboy() {
    #ifdef _WIN32
        system("cls");
        system("chcp 65001 > nul");
    #else
        system("clear");
    #endif
}

void Sleep(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

int main() {
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    srand(time(0));


    int monsterHP = 150;
    int monsterDamage = 20;
    int choice;
    int playerHP, playerDamage;
    int classChoice;

    cout << "Выбери класс:\n";
    cout << "1 - Воин (много HP)\n";
    cout << "2 - Лучник (больше урон)\n";
    cout << "3 - Маг (магия)\n";
    cin >> classChoice;

    switch (classChoice) {
        case 1:
            playerHP = 120;
            playerDamage = 12;
            cout << "Ты выбрал Воина!\n";
            Sleep(1500);
            break;

        case 2:
            playerHP = 80;
            playerDamage = 25;
            cout << "Ты выбрал Лучника!\n";
            Sleep(1500);
            break;

        case 3:
            playerHP = 60;
            playerDamage = 25;
            cout << "Ты выбрал Мага!\n";
            Sleep(1500);
            break;

        default:
            cout << "Неверный выбор, ты стал крестьянином\n";
            playerHP = 100;
            playerDamage = 10;
            Sleep(1500);
    }

    cout << "Появился монстр!\n";
    Sleep(1500);

    while (playerHP > 0 && monsterHP > 0) {
        ClearMaboy();
        cout << "\nТвое HP: " << playerHP << endl;
        cout << "HP монстра: " << monsterHP << endl;

        cout << "\nВыбери действие:\n";
        cout << "1 - Атака\n";
        cout << "2 - Лечение\n";
        cout << "3 - Супер удар\n";
        if (classChoice == 3) {
            cout << "4 - Магия\n";
            cout << "5 - Фаер бол\n";
        }
        cout << (classChoice == 3 ? "6" : "4") << " - Сбежать\n";
        cin >> choice;

        bool validAction = true;

        switch (choice) {
            case 1: {
                int damage = rand() % playerDamage + 20;
                monsterHP -= damage;
                cout << "Ты нанес " << damage << " урона!\n";
                Sleep(1500);
                break;
            }

            case 2: {
                int heal = rand() % 10 + 12;
                playerHP += heal;
                cout << "Ты вылечился на " << heal << " HP!\n";
                Sleep(1500);
                break;
            }

            case 3: {
                int success = rand() % 2;
                if (success == 0) {
                    cout << "Супер удар промахнулся!\n";
                    Sleep(1500);
                    break;
                }
                if (success == 1) {
                    cout << "Супер удар сработал!\n";
                    Sleep(1500);
                    int damage = (rand() % 30 + 20) * 2;
                    monsterHP -= damage;
                    cout << "СУПЕР УДАР! Урон: " << damage << endl;
                    Sleep(1500);
                    break;
                }
            }

            case 4:
                if (classChoice == 3) {
                    cout << "Магия может сработать непредсказуемо...\n";
                    Sleep(1000);
                    int magicEffect = rand() % 3;
                    if (magicEffect == 0) {
                        cout << "Магия усилила твою атаку!\n";
                        playerDamage += 15;
                    } else if (magicEffect == 1) {
                        cout << "Магия исцелила тебя!\n";
                        playerHP += 20;
                    } else if (magicEffect == 2) {
                        cout << "Магия ослабила монстра!\n";
                        monsterDamage -= 10;
                    } else{
                        cout << "Магия не сработала...\n";
                    }
                    Sleep(2000); 
                    break;
                } else {
                    cout << "Ты сбежал!\n";
                    exit(0);
                }

            case 5:
                if (classChoice == 3) {
                    cout << "Ты используешь Фаер бол!\n";
                    Sleep(1500);
                    int damage = rand() % 30 + 10;
                    monsterHP -= damage;
                    cout << "Фаер бол нанес " << damage << " урона!\n";
                    Sleep(1500);
                    break;
                } else {
                    cout << "Ты сбежал!\n";
                    return 0;
                }

            case 6:
                if (classChoice == 3) {
                    cout << "Ты сбежал!\n";
                    exit(0);
                } else {
                    cout << "Неверный выбор!\n";
                    validAction = false;
                }
                break;

            default:
                cout << "Неверный выбор!\n";
                Sleep(1500);
                validAction = false;
        }

        // Ход монстра
        if (validAction && monsterHP > 0) {
            int monsterAction = rand() % 2;
            int damage = rand() % monsterDamage + 1;
            switch (monsterAction) {
                case 0:
                    cout << "Монстр атакует!\n";
                    Sleep(1500);
                    playerHP -= damage;
                    cout << "Монстр ударил на " << damage << "!\n";
                    Sleep(1500);
                    break;
                case 1:
                    cout << "Монстр излечился!\n";
                    Sleep(1500);
                    int heal = rand() % 10 + 5;
                    monsterHP += heal;
                    cout << "Монстр восстановил " << heal << " HP!\n";
                    Sleep(1500);
                    break;
            }
        }
    }

    if (playerHP > 0) {
        cout << "\nТы победил монстра!";
        Sleep(1500);
        exit(0);
    } else {
        cout << "\nТы проиграл...";
        Sleep(1500);
        exit(0);
    }

    return 0;
}