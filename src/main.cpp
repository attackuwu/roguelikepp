/* Часть проекта Roguelike++ (https://github.com/attackuwu/roguelikepp) */
/* Создан attackuwu под лицензией MIT */

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <algorithm>

/*Функция для задержки*/
void delay(double seconds) {
    std::this_thread::sleep_for(std::chrono::duration<double>(seconds));
}

class Humanoid {
public:
    std::string name;
    long health;
    long attack;
    long armor;
    bool isAlive = true;
};

void typewrite(const std::string& text, int delayMs = 35) {
    for (char c : text) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }
    std::cout << '\n';
}

long inflictDamage(const Humanoid& self, Humanoid& target) {
    if (!self.isAlive) {
        typewrite(self.name + " уже мертв и не может атаковать.");
        return 0L;
    }

    if (!target.isAlive) {
        typewrite(target.name + " уже мертв.");
        return 0L;
    }

    long effectiveAttack = std::max(0L, self.attack);
    long effectiveArmor = std::max(0L, target.armor);
    long dmg = std::max(0L, effectiveAttack - effectiveArmor);

    if (dmg == 0L) {
        typewrite(self.name + " атакует " + target.name + ", но не пробивает броню!");
        return 0L;
    }

    if (dmg >= target.health) {
        target.health = 0L;
        target.isAlive = false;
        typewrite(self.name + " наносит " + std::to_string(dmg) + " урона и убивает " + target.name + "!");
    } else {
        target.health -= dmg;
        typewrite(self.name + " наносит " + std::to_string(dmg) + " урона по " + target.name + ". Осталось HP: " + std::to_string(target.health));
    }

    return dmg;
}

Humanoid createPerson(const std::string& name, long health, long attack, long armor, bool isAlive) {
    return Humanoid{name, health, attack, armor, isAlive};
}
int main() {

    /*Регистрация персонажа*/

    /*-------------------------------------------------------------------*/
    typewrite("Roguelike++ 0.01\n");
    typewrite("Добро пожаловать в Roguelike++!\n");
    typewrite("Создайте своего персонажа.\n");

    std::string playerName;
    std::cout << "Введите имя вашего персонажа: ";
    std::cin >> playerName;

    typewrite("Имя персонажа: " + playerName);
    typewrite("Верно? (y/n): ");
    char confirmation;
    std::cin >> confirmation;

    if (confirmation != 'y' && confirmation != 'Y') {
        std::cout << "Попробуйте снова.\n";
        return 0;
    }
    typewrite("Отлично. Создаем персонажа...\n");

    Humanoid player = createPerson(playerName, 100, 10, 5, true);

    typewrite("Персонаж создан!\n");
    typewrite("Имя: " + player.name);
    typewrite("Здоровье: " + std::to_string(player.health));
    typewrite("Атака: " + std::to_string(player.attack));
    typewrite("Броня: " + std::to_string(player.armor));

    /*-------------------------------------------------------------------*/

    /* Кат-сцена */

    typewrite("Вы просыпаетесь в темной комнате. Перед вами стоит таинственная фигура.");
    delay(2);
    typewrite("Фигура говорит: 'Добро пожаловать, " + player.name + ".'");
    delay(2);
    typewrite("Фигура продолжает: 'Твое приключение начинается прямо сейчас.'");
    delay(2);
    typewrite("Вы чувствуете, как ваше сердце начинает биться быстрее...");
    delay(2);
    std::cout << "Что вы будете делать дальше?\n";
    std::cout << "1. Подойти к фигуре\n";
    std::cout << "2. Осмотреть комнату (НЕ РЕАЛИЗОВАНО)\n";
    std::cout << "3. Попытаться убежать (НЕ РЕАЛИЗОВАНО)\n";

    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1: {
            typewrite("Вы подходите к фигуре...");
            delay(1);
            typewrite("Из тени капюшона на вас смотрят два тусклых янтарных глаза.");
            delay(1);
            typewrite("Фигура говорит: 'Ты очнулся в Склепе Пепла, " + player.name + ". Обратной дороги нет.'");
            delay(1.5);
            typewrite("Фигура продолжает: 'За этой дверью бродит Страж Порога. Без оружия ты не проживешь и минуты.'");
            delay(1);
            typewrite("Фигура протягивает вам два предмета из-под плаща. Что возьмете?");
            std::cout << "1. Ржавый тесак (+6 к атаке)\n";
            std::cout << "2. Пробитый башенный щит (+4 к броне, +2 к атаке)\n";

            int itemChoice = 0;
            std::cin >> itemChoice;

            if (itemChoice == 1) {
                player.attack += 6;
                typewrite("Вы сжимаете рукоять тесака. Тяжелый, но острый. Ваша атака теперь: " + std::to_string(player.attack));
            } else {
                player.armor += 4;
                player.attack += 2;
                typewrite("Вы берете щит и короткий клинок. Ваша броня: " + std::to_string(player.armor) + ", атака: " + std::to_string(player.attack));
            }

            delay(1.5);
            typewrite("Фигура говорит: 'Теперь ты готов. Иди, пока факелы не погасли.'");
            delay(1);

            char ready;
            typewrite("Открыть тяжелую железную дверь? (y/n): ");
            std::cin >> ready;

            if (ready == 'Y' || ready == 'y') {
                typewrite("Вы с усилием толкаете дверь. Петли оглушительно скрипят...");
                delay(1.5);
                typewrite("В тусклом свете коридора на вас бросается Страж Порога!");
                delay(1);

                Humanoid guard = createPerson("Страж Порога", 45, 11, 3, true);

                while (player.isAlive && guard.isAlive) {
                    delay(1);
                    std::cout << "\n--- Ваш ход ---\n";
                    std::cout << "1. Атаковать\n";
                    std::cout << "2. Глухая оборона (+3 к броне на этот ход)\n";

                    int action = 0;
                    std::cin >> action;

                    long bonusArmor = 0;
                    if (action == 2) {
                        bonusArmor = 3;
                        player.armor += bonusArmor;
                        typewrite("Вы поднимаете защиту и готовитесь к удару.");
                    } else {
                        inflictDamage(player, guard);
                    }

                    if (guard.isAlive) {
                        delay(1);
                        inflictDamage(guard, player);
                    }

                    if (bonusArmor > 0) {
                        player.armor -= bonusArmor;
                    }
                }

                delay(1);
                if (player.isAlive) {
                    typewrite("Страж Порога рушится на каменный пол. Путь вглубь Склепа открыт!");
                } else {
                    typewrite("Тьма поглощает вас... Ваше приключение окончено.");
                    return 0;
                }
            } else {
                typewrite("Вы отступаете назад. Фигура лишь усмехается: 'Страх убивает быстрее клинка.'");
            }
            
            break;
        }
        //case 2:
        //    typewrite("Вы осматриваете комнату.");
        //    break;
        // case 3:
        //     typewrite("Вы пытаетесь убежать, но дверь заперта.");
        //     break;
        default:
            typewrite("Неверный выбор.");
            break;
    }
}