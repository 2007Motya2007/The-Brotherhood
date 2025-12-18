#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <stdexcept>
#include <algorithm>

using namespace std;

// ==================== КЛАСС С ПОЛНОЙ ИНКАПСУЛЯЦИЕЙ ====================
class BankAccount {
private:
    // 1. Приватные поля для целостности данных
    string accountNumber;  // Можно менять только через специальный метод
    string ownerName;      // Можно менять только при строгой проверке
    double balance;        // Доступ только через методы с валидацией
    const double minBalance = 50.0;  // Константное поле (аналог readonly)

    // 2. Приватные вспомогательные методы
    bool isValidAmount(double amount) const {
        return amount > 0;
    }

public:
    // ==================== КОНСТРУКТОРЫ ====================

    // 3. Основной конструктор с валидацией
    BankAccount(const string& accNum, const string& owner, double initialBalance)
        : accountNumber(accNum), ownerName(owner) {

        if (accNum.empty()) {
            throw invalid_argument("Номер счета не может быть пустым");
        }
        if (owner.empty()) {
            throw invalid_argument("Имя владельца не может быть пустым");
        }
        if (initialBalance < minBalance) {
            throw invalid_argument("Начальный баланс должен быть не менее " +
                to_string(minBalance));
        }

        balance = initialBalance;
        cout << "Создан счет " << accountNumber << " для " << ownerName
            << " с балансом " << balance << endl;
    }

    // 4. Конструктор по умолчанию (delegating constructor)
    BankAccount() : BankAccount("000000", "Неизвестный", minBalance) {}

    // 5. Конструктор копирования (глубокое копирование)
    BankAccount(const BankAccount& other)
        : accountNumber(other.accountNumber + "_copy"),
        ownerName(other.ownerName),
        balance(other.balance),
        minBalance(other.minBalance) {
        cout << "Счет скопирован: " << accountNumber << endl;
    }

    // 6. Конструктор перемещения
    BankAccount(BankAccount&& other) noexcept
        : accountNumber(move(other.accountNumber)),
        ownerName(move(other.ownerName)),
        balance(other.balance),
        minBalance(other.minBalance) {

        other.balance = 0;
        cout << "Счет перемещен: " << accountNumber << endl;
    }

    // ==================== СВОЙСТВА (GETTERS/SETTERS) ====================

    // 7. Read-only свойства (только геттеры)
    string getAccountNumber() const { return accountNumber; }
    double getMinBalance() const { return minBalance; }

    // 8. Свойства с геттером и сеттером
    string getOwnerName() const { return ownerName; }

    void setOwnerName(const string& newName) {
        if (newName.empty()) {
            throw invalid_argument("Имя не может быть пустым");
        }
        if (newName.length() < 2) {
            throw invalid_argument("Имя слишком короткое");
        }

        cout << "Смена владельца с " << ownerName
            << " на " << newName << endl;
        ownerName = newName;
    }

    // 9. Read-only свойство для баланса
    double getBalance() const { return balance; }

    // ==================== МЕТОДЫ ДЛЯ ОПЕРАЦИЙ ====================

    void deposit(double amount) {
        if (!isValidAmount(amount)) {
            throw invalid_argument("Сумма депозита должна быть положительной");
        }

        balance += amount;
        cout << "Внесено " << amount << " на счет " << accountNumber
            << ". Новый баланс: " << balance << endl;
    }

    void withdraw(double amount) {
        if (!isValidAmount(amount)) {
            throw invalid_argument("Сумма снятия должна быть положительной");
        }

        double newBalance = balance - amount;
        if (newBalance < minBalance) {
            throw runtime_error("Недостаточно средств. Минимальный баланс: " +
                to_string(minBalance));
        }

        balance = newBalance;
        cout << "Снято " << amount << " со счета " << accountNumber
            << ". Новый баланс: " << balance << endl;
    }

    void transferTo(BankAccount& other, double amount) {
        cout << "Перевод " << amount << " со счета " << accountNumber
            << " на счет " << other.accountNumber << endl;

        withdraw(amount);      // Проверка доступности средств
        other.deposit(amount); // Зачисление получателю
    }

    // ==================== ПЕРЕГРУЗКА ОПЕРАТОРОВ ====================

    // Оператор присваивания
    BankAccount& operator=(const BankAccount& other) {
        if (this != &other) {
            // Не копируем accountNumber (уникальный идентификатор)
            ownerName = other.ownerName;
            balance = other.balance;
        }
        return *this;
    }

    // Оператор вывода
    friend ostream& operator<<(ostream& os, const BankAccount& acc) {
        os << "Счет: " << acc.accountNumber
            << "\nВладелец: " << acc.ownerName
            << "\nБаланс: " << acc.balance
            << "\nМин. баланс: " << acc.minBalance;
        return os;
    }

    // ==================== ДЕСТРУКТОР ====================
    ~BankAccount() {
        cout << "Счет " << accountNumber << " закрыт. Финальный баланс: "
            << balance << endl;
    }
};

// ==================== КЛАСС С "READONLY" ПОЛЯМИ ЧЕЗ CONST ====================
class Configuration {
private:
    // Поля, инициализируемые только в конструкторе (аналог readonly)
    const string appName;
    const string appVersion;
    const int maxConnections;

    // Обычные приватные поля
    mutable int accessCount;  // mutable - может меняться даже в const методах

public:
    // Единственный способ установить значения const полей - список инициализации
    Configuration(const string& name, const string& version, int maxConn)
        : appName(name), appVersion(version), maxConnections(maxConn),
        accessCount(0) {

        if (maxConn <= 0) {
            throw invalid_argument("Максимальное число соединений должно быть > 0");
        }
    }

    // Конструктор по умолчанию удален - не хотим объекты без инициализации
    Configuration() = delete;

    // Только геттеры для const полей
    string getAppName() const {
        ++accessCount;  // Можно изменить mutable поле в const методе
        return appName;
    }

    string getAppVersion() const { return appVersion; }
    int getMaxConnections() const { return maxConnections; }
    int getAccessCount() const { return accessCount; }

    // Нет сеттеров для const полей - они неизменяемы!

    // Const метод - гарантирует не изменение состояния объекта
    void display() const {
        cout << "\n=== Конфигурация ===" << endl;
        cout << "Приложение: " << appName << " v" << appVersion << endl;
        cout << "Макс. соединений: " << maxConnections << endl;
        cout << "Чтений конфигурации: " << accessCount << endl;
    }
};

// ==================== КЛАСС С ПРОДВИНУТЫМИ СВОЙСТВАМИ ====================
class Temperature {
private:
    double celsius;

    // Валидация
    bool isValidCelsius(double temp) const {
        return temp >= -273.15;  // Абсолютный ноль
    }

public:
    // Делегирующий конструктор
    Temperature(double temp = 0.0) {
        setCelsius(temp);  // Используем сеттер для валидации
    }

    // Свойство Celsius с валидацией
    double getCelsius() const { return celsius; }

    void setCelsius(double temp) {
        if (!isValidCelsius(temp)) {
            throw invalid_argument("Температура не может быть ниже -273.15°C");
        }
        celsius = temp;
    }

    // Вычисляемые свойства (read-only)
    double getFahrenheit() const {
        return celsius * 9.0 / 5.0 + 32.0;
    }

    double getKelvin() const {
        return celsius + 273.15;
    }

    // Свойство с разной логикой get/set
    double getFahrenheitProperty() const {
        return getFahrenheit();
    }

    void setFahrenheitProperty(double fahr) {
        setCelsius((fahr - 32.0) * 5.0 / 9.0);
    }

    void display() const {
        cout << celsius << "°C = " << getFahrenheit() << "°F = "
            << getKelvin() << "K" << endl;
    }
};

// ==================== КЛАСС С ИНДЕКСАТОРОМ (СВОЙСТВО С ПАРАМЕТРОМ) ====================
class Student {
private:
    string name;
    double grades[5];  // Оценки за 5 предметов
    int id;

public:
    Student(int studentId, const string& studentName)
        : id(studentId), name(studentName) {
        fill(begin(grades), end(grades), 0.0);  // Инициализируем нулями
    }

    // Индексатор (свойство с параметром)
    double getGrade(int subjectIndex) const {
        if (subjectIndex < 0 || subjectIndex >= 5) {
            throw out_of_range("Индекс предмета должен быть от 0 до 4");
        }
        return grades[subjectIndex];
    }

    void setGrade(int subjectIndex, double grade) {
        if (subjectIndex < 0 || subjectIndex >= 5) {
            throw out_of_range("Индекс предмета должен быть от 0 до 4");
        }
        if (grade < 0 || grade > 5) {
            throw invalid_argument("Оценка должна быть от 0 до 5");
        }
        grades[subjectIndex] = grade;
    }

    // Вычисляемое свойство (средний балл)
    double getAverageGrade() const {
        double sum = 0;
        for (double grade : grades) {
            sum += grade;
        }
        return sum / 5.0;
    }

    // Read-only свойства
    int getId() const { return id; }
    string getName() const { return name; }

    void display() const {
        cout << "\nСтудент #" << id << ": " << name << endl;
        cout << "Оценки: ";
        for (int i = 0; i < 5; ++i) {
            cout << grades[i] << " ";
        }
        cout << "\nСредний балл: " << getAverageGrade() << endl;
    }
};

// ==================== ИММУТАБЕЛЬНЫЙ КЛАСС (ПОЛНАЯ НЕИЗМЕНЯЕМОСТЬ) ====================
class ImmutablePoint {
private:
    const double x;  // Все поля const
    const double y;

public:
    // Единственный конструктор
    ImmutablePoint(double xCoord, double yCoord) : x(xCoord), y(yCoord) {}

    // Только геттеры
    double getX() const { return x; }
    double getY() const { return y; }

    // Методы не меняют состояние, возвращают новый объект
    ImmutablePoint translate(double dx, double dy) const {
        return ImmutablePoint(x + dx, y + dy);
    }

    // Вычисляемые свойства
    double distanceToOrigin() const {
        return sqrt(x * x + y * y);
    }

    void display() const {
        cout << "Точка(" << x << ", " << y << ")" << endl;
    }
};

// ==================== ДЕМОНСТРАЦИЯ ====================
void demonstrateDataIntegrity() {
    cout << "=== ДЕМОНСТРАЦИЯ ЦЕЛОСТНОСТИ ДАННЫХ ===" << endl;

    try {
        // 1. Создание объектов с валидацией в конструкторе
        cout << "\n1. СОЗДАНИЕ БАНКОВСКОГО СЧЕТА:" << endl;
        BankAccount account1("1234567890", "Иван Иванов", 1000.0);

        // Попытка создать невалидный счет
        try {
            BankAccount invalid("", "Тест", 10.0);
        }
        catch (const exception& e) {
            cout << "Ожидаемая ошибка: " << e.what() << endl;
        }

        // 2. Использование свойств
        cout << "\n2. РАБОТА СО СВОЙСТВАМИ:" << endl;
        cout << "Номер счета (readonly): " << account1.getAccountNumber() << endl;
        cout << "Текущий владелец: " << account1.getOwnerName() << endl;

        account1.setOwnerName("Петр Петров");
        cout << "Новый владелец: " << account1.getOwnerName() << endl;

        // Попытка установить невалидное имя
        try {
            account1.setOwnerName("");
        }
        catch (const exception& e) {
            cout << "Ошибка валидации: " << e.what() << endl;
        }

        // 3. Работа с балансом
        cout << "\n3. ОПЕРАЦИИ С БАЛАНСОМ:" << endl;
        account1.deposit(500.0);
        cout << "Текущий баланс: " << account1.getBalance() << endl;

        try {
            account1.withdraw(2000.0);  // Слишком много
        }
        catch (const exception& e) {
            cout << "Ошибка снятия: " << e.what() << endl;
        }

        account1.withdraw(200.0);

        // 4. Конфигурация с const полями
        cout << "\n4. КОНФИГУРАЦИЯ (READONLY ПОЛЯ):" << endl;
        Configuration config("MyApp", "2.1.0", 100);
        config.display();

        // config.getAppName() возвращает копию, но не позволяет изменить поле
        string name = config.getAppName();  // OK
        // config.appName = "NewName";      // ОШИБКА: приватное const поле

        config.display();  // accessCount увеличился

        // 5. Temperature с вычисляемыми свойствами
        cout << "\n5. ТЕМПЕРАТУРА И ВЫЧИСЛЯЕМЫЕ СВОЙСТВА:" << endl;
        Temperature temp(25.0);
        temp.display();

        cout << "В Фаренгейтах: " << temp.getFahrenheit() << "°F" << endl;
        cout << "В Кельвинах: " << temp.getKelvin() << "K" << endl;

        temp.setCelsius(100.0);
        cout << "После изменения: ";
        temp.display();

        // 6. Студент с индексатором
        cout << "\n6. СТУДЕНТ С ИНДЕКСАТОРОМ:" << endl;
        Student student(1, "Анна Сидорова");
        student.setGrade(0, 4.5);
        student.setGrade(1, 5.0);
        student.setGrade(2, 3.8);

        cout << "Оценка за предмет 0: " << student.getGrade(0) << endl;
        cout << "Средний балл: " << student.getAverageGrade() << endl;

        student.display();

        // 7. Иммутабельный объект
        cout << "\n7. ИММУТАБЕЛЬНЫЙ ОБЪЕКТ:" << endl;
        ImmutablePoint point(3.0, 4.0);
        point.display();
        cout << "Расстояние до начала координат: " << point.distanceToOrigin() << endl;

        ImmutablePoint newPoint = point.translate(2.0, -1.0);
        cout << "После перемещения: ";
        newPoint.display();

        // 8. Копирование и перемещение
        cout << "\n8. КОПИРОВАНИЕ И ПЕРЕМЕЩЕНИЕ:" << endl;
        BankAccount original("111111", "Оригинал", 500.0);
        BankAccount copy = original;  // Копирующий конструктор
        BankAccount moved = move(original);  // Перемещающий конструктор

        // 9. Работа через указатели
        cout << "\n9. РАБОТА ЧЕРЕЗ УМНЫЕ УКАЗАТЕЛИ:" << endl;
        auto accountPtr = make_unique<BankAccount>("999999", "Владелец умного указателя", 750.0);

        // Доступ через указатель
        accountPtr->deposit(250.0);
        cout << "Баланс через указатель: " << accountPtr->getBalance() << endl;

        // 10. Перегрузка оператора вывода
        cout << "\n10. ПЕРЕГРУЗКА ОПЕРАТОРА ВЫВОДА:" << endl;
        cout << account1 << endl;

    }
    catch (const exception& e) {
        cerr << "Критическая ошибка: " << e.what() << endl;
    }
}

// ==================== ПРИМЕР С СИНГЛТОНОМ (ДОПОЛНИТЕЛЬНО) ====================
class AppSettings {
private:
    // Приватный конструктор
    AppSettings() : theme("Dark"), language("Russian"), fontSize(14) {
        cout << "Настройки приложения инициализированы" << endl;
    }

    // Удаленные конструкторы копирования и присваивания
    AppSettings(const AppSettings&) = delete;
    AppSettings& operator=(const AppSettings&) = delete;

    string theme;
    string language;
    int fontSize;

public:
    // Единственный экземпляр
    static AppSettings& getInstance() {
        static AppSettings instance;  // Создается при первом вызове
        return instance;
    }

    // Свойства
    string getTheme() const { return theme; }
    void setTheme(const string& newTheme) {
        if (newTheme == "Dark" || newTheme == "Light") {
            theme = newTheme;
        }
    }

    string getLanguage() const { return language; }
    int getFontSize() const { return fontSize; }

    void display() const {
        cout << "\n=== Настройки приложения ===" << endl;
        cout << "Тема: " << theme << endl;
        cout << "Язык: " << language << endl;
        cout << "Размер шрифта: " << fontSize << endl;
    }
};

int main() {
    cout << "ДЕМОНСТРАЦИЯ ЦЕЛОСТНОСТИ ДАННЫХ В C++" << endl;
    cout << "====================================\n" << endl;

    demonstrateDataIntegrity();

    cout << "\n=== ДОПОЛНИТЕЛЬНО: СИНГЛТОН ===" << endl;
    AppSettings& settings = AppSettings::getInstance();
    settings.display();

    cout << "\n====================================" << endl;
    cout << "Демонстрация завершена успешно!" << endl;

    return 0;
}