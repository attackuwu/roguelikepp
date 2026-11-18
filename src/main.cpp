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
void delay(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

class Humanoid {
public:
    std::string name;
    long health;
    long attack;
    long armor;
};

long inflictDamage(Humanoid& self, Humanoid& target) {
    long dmg = std::max(0L, self.attack - target.armor);
    target.health -= dmg;
    return dmg;
} // математически доказано бтв мтн хтн бмв ты кто такой это моя машина я мужчина это моя мужчина

int main() {

    /*Регистрация персонажа*/

    /*-------------------------------------------------------------------*/
    std::cout << "Roguelike++ 0.01\n";
    std::cout << "Добро пожаловать в Roguelike++!\n";
    std::cout << "Создайте своего персонажа.\n";

    std::string playerName;
    std::cout << "Введите имя вашего персонажа: ";
    std::cin >> playerName;

    std::cout << "Имя персонажа: " << playerName << "\n";
    std::cout << "Верно? (y/n): ";
    char confirmation;
    std::cin >> confirmation;

    if (confirmation != 'y' && confirmation != 'Y') {
        std::cout << "Попробуйте снова.\n";
        return 0;
    }
    std::cout << "Отлично. Создаем персонажа...\n";

    Humanoid player;
    player.name = playerName;
    player.health = 100;
    player.attack = 10;
    player.armor = 5;

    std::cout << "Персонаж создан!\n";
    std::cout << "Имя: " << player.name << "\n";
    std::cout << "Здоровье: " << player.health << "\n";
    std::cout << "Атака: " << player.attack << "\n";
    std::cout << "Броня: " << player.armor << "\n";

    /*-------------------------------------------------------------------*/

    /* Кат-сцена */

    std::cout << "Вы просыпаетесь в темной комнате. Перед вами стоит таинственная фигура.\n";
    delay(2);
    std::cout << "Фигура говорит: 'Добро пожаловать, " << player.name << ".'\n";
    delay(2);
    std::cout << "Фигура продолжает: 'Твое приключение начинается прямо сейчас.'\n";
    delay(2);
    std::cout << "Вы чувствуете, как ваше сердце начинает биться быстрее...\n";
    delay(2);
    std::cout << "Что вы будете делать дальше?\n";
    std::cout << "1. Подойти к фигуре\n";
    std::cout << "2. Осмотреть комнату\n";
    std::cout << "3. Попытаться убежать\n";

    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1:
            std::cout << "Вы подходите к фигуре.\n";
            break;
        case 2:
            std::cout << "Вы осматриваете комнату.\n";
            break;
        case 3:
            std::cout << "Вы пытаетесь убежать, но дверь заперта.\n";
            break;
        default:
            std::cout << "Неверный выбор.\n";
            break;
    }
}