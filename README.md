# 🗡️ Roguelike++

![Version](https://img.shields.io/badge/version-v0.012--alpha-orange?style=for-the-badge)
![C++](https://img.shields.io/badge/C%2B%2B-20-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-3.20%2B-064F8C?style=for-the-badge&logo=cmake&logoColor=white)
![GitHub last commit](https://img.shields.io/github/last-commit/attackuwu/roguelikepp?style=for-the-badge&color=success)

Небольшой консольный текстовый рогалик, написанный на чистом **C++20** без сторонних библиотек и лишнего обвеса. Делается с нуля как пет-проект для прокачки ООП, наследования, работы с памятью и сборки через CMake.

---

## 🎮 Что уже работает в альфе
- **Создание персонажа:** ввод имени, инициализация базовых статов (HP, атака, броня).
- **Боевая система:** расчёт урона с учётом брони цели (`inflictDamage`) через класс `Humanoid`.
- **Завязка сюжета:** атмосферные паузы на потоках (`std::this_thread::sleep_for`) и первые развилки через `switch`.

## ⚙️ Сборка + запуск

Нужен только компилятор с поддержкой C++20 (`g++` или `clang++`) и `cmake`.

```bash
git clone https://github.com/attackuwu/roguelikepp.git
cd roguelikepp
cmake -B build && cmake --build build # не обязательно
./build/roguelike
```

## 👨‍🦽‍➡️ Обычный запуск:
- Заходите на **[Github Release](https://github.com/attackuwu/roguelikepp/releases)**, скачивай бинарник и играй! (обязательно надо открывать в терминале)
