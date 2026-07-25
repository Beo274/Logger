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
cmake -S . -B build_static -DBUILD_SHARED_LIBS=OFF -DCMAKE_INSTALL_PREFIX=./logger_sdk
cmake --build build_static --target LoggerLib -j
cmake --install build_static --component sdk
```
Готовый файл .so появится в build_static/

### Статическая сборка библиотеки
```
cmake -S . -B build_shared -DBUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX=./logger_sdk
cmake --build build_shared --target LoggerLib -j
cmake --install build_shared --component sdk
```
Готовый файл .a появится в build_shared/

> [!TIP]
> Для полной очистки результатов сборки выполните
> ```
>rm -rf build* logger_sdk
> ```

## Инструкция по применению ℹ️
### Логгер
После сборки любым из способов в корне проекта появится папка  logger_sdk
Эту папку нужно скопировать в ваш проект и добавить следующие команды в CMakeLists.txt
```
target_include_directories(my_app PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/logger_sdk/include
)

target_link_directories(my_app PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/logger_sdk/lib
)
target_link_libraries(my_app PRIVATE logger_lib)

find_package(Threads REQUIRED)
target_link_libraries(my_app PRIVATE Threads::Threads)

# Для динамически собранной библиотеки
set_target_properties(my_app PROPERTIES
    BUILD_WITH_INSTALL_RPATH TRUE
    INSTALL_RPATH "$ORIGIN/logger_sdk/lib"
)
```
Теперь разработчик может подключить логгер в своем коде:
```
#include "Logger.h"
#include "LoggerStrategy.h"

# Вариант записи в сокет
LoggerStrategy *strategy = new SocketLoggerStrategy(std::string ip, int port);
# Вариант записи в файл
LoggerStrategy *strategy = new FileLoggerStrategy(std::string file_name);
# Инициализация логгера
Logger::getInstance().init(LoggerStrategy strategy, LogLevel level);
# После этого можно использовать логгер
Logger::getInstance().debug() << "Сообщение";
Logger::getInstance().info() << "Сообщение";
Logger::getInstance().warning() << "Сообщение";
```

### Приложение для проверки (1) ✅
1. Запуск
```
./LoggerApp имя_файла_логов уровень_логирования_по_умолчанию
```
2. Выбор способа логирования: введите f для логирования в файл, введите s для логирования в сокет (по-умолчанию адрес 127.0.0.1 и порт 9000)
3. Выбор уровня лога для сообщения: введите d для уровня DEBUG, i для INFO, w для WARNING
4. Ввод сообщения лога
5. Выбор количества дублирований этого сообщения. Сделано для проверки потокобезопасности логгера. Выбор ограничен количеством ядер процессора на устройстве. После выбора будет воспроиведена дополнительная логика, которая помимо сообщения отправляет сообщения о загрузке ресурсов. Сделано для наглядной демонстрации потокобезопасности логгера
6. После ввода всех данных будет предложено нажать ENTER, чтобы продолжить. После нажатия консоль очистится и приложение перейдет на шаг №3
>[!NOTE]
> В любой момент можно ввести 'q' и выйти из приложения

### Приложение сбора статистики логам (2) 📊
1. Запуск
```
./StatisticsApp ip_адрес номер_сообщения_N порт таймаут_T_в_секундах
```
Для работы с приложением №1 необходимо использовать адрес 127.0.0.1 и порт 9000
2. Ожиданиие подключение. В этот момент ожидается запуск приложения №1, выбор логирования в сокет (Ввод 's' на шаге 2) и отправка сообщений
3. Полученные сообщения отобразятся в консоли
4. После прохождения таймаута Т будет выведена статистика по полученным сообщениям:
   - Количество принятых сообщений
   - Максимальная длина среди полученных сообщений
   - Минимальная длина среди полученных сообщений
   - Средняя длина среди полученных сообщений
   - Количество сообщений каждого уровня логирования
   - Количество принятых сообщений за последний час
5. При получении N-ого сообщения также будет выведена статистика
   
 
