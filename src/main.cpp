/* Часть проекта Roguelike++ (https://github.com/attackuwu/roguelikepp) */
/* Создан attackuwu под лицензией MIT */
/* Roguelike++ 0.012 */
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
                    delay(1.5);

                    typewrite("Вы переводите дыхание и вдруг замечаете то, чего не видели в бою.");
                    typewrite("Под истлевшим доспехом стража — плащ с вышитым гербом. На наплечнике выцарапано имя.");
                    delay(1);
                    typewrite("«Эйден, первый из Стражей». И дата, которой триста лет.");
                    delay(1.5);

                    typewrite("Коридор ведет вас в галерею. Стены покрыты именами — сотни, тысячи имен, выбитых в камне.");
                    delay(1);
                    typewrite("Вы идете вдоль них, пока взгляд не упирается в последнее. Оно свежее: камень еще не успел потемнеть.");
                    delay(1.5);
                    typewrite("На нем выбито ваше имя.");
                    delay(2);
                    typewrite("«" + player.name + "». Кто-то высек его задолго до того, как вы вошли в этот склеп.");
                    delay(2);

                    typewrite("В конце галереи — зал с потухшей кузницей. На наковальне лежит уголек.");
                    typewrite("Он тлеет изнутри, и от него по камню расползаются тонкие трещины, похожие на вены.");
                    delay(1.5);
                    typewrite("Из темноты за спиной раздается знакомый голос: «Ты дошел дальше, чем я думал.»");
                    typewrite("Фигура стоит у входа. Капюшон опущен. Вы видите лицо — усталое, человеческое.");
                    delay(1);
                    typewrite("«Меня зовут Эйден. Я победил Стража триста лет назад. И занял его место.»");
                    delay(1.5);
                    typewrite("«Уголек Первого Огня дает силу. Но всякий, кто его коснется, становится новым Стражем.»");
                    delay(1);
                    typewrite("«Склеп не хочет смерти. Он хочет стража. Выбирай.»");

                    std::cout << "\n1. Взять уголек. Сила превыше всего.\n";
                    std::cout << "2. Погасить уголек. Пусть этот круг разорвется.\n";
                    std::cout << "3. Отступить в тень и не трогать его.\n";

                    int emberChoice = 0;
                    std::cin >> emberChoice;

                    if (emberChoice == 1) {
                        player.attack += 10;
                        typewrite("Вы касаетесь уголька. Боль пронзает руку, но вместе с ней приходит сила.");
                        delay(1.5);
                        typewrite("Трещины на камне вспыхивают и тянутся к вам, оплетая запястья, как кандалы.");
                        typewrite("Эйден закрывает глаза: «Прости.» И рассыпается пеплом.");
                        delay(2);
                        typewrite("У входа в зал что-то шевелится. Из темноты выходит новый путник — испуганный, с факелом в руке.");
                        typewrite("Он смотрит на вас и спрашивает: «Кто вы?»");
                        delay(2);
                        typewrite("Вы хотите назвать свое имя. Но из горла вырывается чужой голос:");
                        typewrite("«Я — Страж Порога. Обратной дороги нет.»");
                        delay(2);
                        typewrite("Где-то в галерее камень принимает новую трещину. Ваше имя на стене гаснет.");
                        typewrite("А рядом появляется другое, только что выцарапанное имя.");
                        typewrite("Круг замкнулся. Ваше приключение окончено.");
                        return 0;
                    } else if (emberChoice == 2) {
                        player.health = std::min(100L, player.health + 25);
                        player.armor += 2;
                        typewrite("Вы накрываете уголек ладонью. Ожог — но вы не отпускаете.");
                        delay(1.5);
                        typewrite("Свет уходит внутрь камня и гаснет. Вместе с ним гаснут трещины на стенах.");
                        delay(1);
                        typewrite("Эйден вздрагивает и медленно опускается на колени. «Триста лет... Я слышу тишину.»");
                        typewrite("Его фигура теряет четкость, как рисунок на песке под ветром. «Спасибо, " + player.name + ".»");
                        delay(2);
                        typewrite("Склеп вздыхает. Потолок осыпается пеплом, а в дальнем конце галереи открывается проход наверх.");
                        typewrite("Вы поднимаетесь по ступеням и выходите на рассвет. Воздух пахнет дождем и травой.");
                        delay(1.5);
                        typewrite("За спиной нет ни склепа, ни двери. Только холм и камень на вершине, с которого кто-то стер все имена.");
                        typewrite("Кроме одного. Вашего. И оно не высечено в камне, а написано угольком. Совсем свежее.");
                        typewrite("Вы улыбаетесь и идете прочь. Этот путь окончен — но только этот.");
                        return 0;
                    } else {
                        typewrite("Вы отступаете в тень. Уголек тлеет, Эйден молчит, склеп ждет.");
                        delay(1.5);
                        typewrite("«Понимаю,» — тихо говорит он. «Свобода — это тоже выбор. Живи с ним.»");
                        typewrite("Фигура растворяется в темноте. Вы стоите в тишине, слушая, как стучит собственное сердце.");
                        typewrite("Никто не гонится за вами. Никто не ждет. Впервые за всю ночь вы можете решить все сами.");
                        typewrite("Вы разворачиваетесь и уходите в темноту — не как путник, а как человек, который сам выбрал свою дорогу.");
                    }
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