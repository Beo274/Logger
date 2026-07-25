# Проект библиотеки логирования 📝
### Что входит в этот проект:
1. Библиотека логирования liblogger
2. Тестовое приложение для проверки работы библиотеки
3. Приложение для сбора статистики при отправке логов в сокет

## Сборка проекта 🛠️
### Сборка всего проекта
```
cmake -S . -B build
cmake --build build -j
```
> После этого появится папка build/ и бинарные файлы обоих приложений будут находится в папке build/bin

### Динамическая сборка библиотеки
```
cmake -S . -B build_shared -DBUILD_SHARED_LIBS=ON
cmake --build build_shared --target logger_lib -j
```
Готовый файл .so появится в build_shared/

### Статическая сборка библиотеки
```
cmake -S . -B build_static -DBUILD_SHARED_LIBS=OFF
cmake --build build_static --target logger_lib -j
```
Готовый файл .a появится в build_shared/

> [!TIP]
> Для полной очистки результатов сборки выполните
> ```
>rm -rf build*
> ```
 
