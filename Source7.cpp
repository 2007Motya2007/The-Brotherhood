#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

// ==================== БАЗОВЫЙ КЛАСС ====================
class Animal {
protected:
    string name;
    int age;

public:
    Animal(const string& name, int age) : name(name), age(age) {
        cout << "Создано животное: " << name << endl;
    }

    // Виртуальный метод - может быть переопределен
    virtual void makeSound() const {
        cout << name << " издает звук" << endl;
    }

    // Виртуальный деструктор - ОБЯЗАТЕЛЬНО для полиморфных классов
    virtual ~Animal() {
        cout << "Животное " << name << " уничтожено" << endl;
    }

    // Невиртуальный метод
    void sleep() const {
        cout << name << " спит" << endl;
    }

    // Геттеры
    string getName() const { return name; }
    int getAge() const { return age; }
};

// ==================== ПРОИЗВОДНЫЙ КЛАСС 1 ====================
class Mammal : public Animal {
protected:
    bool hasFur;
    int limbCount;

public:
    Mammal(const string& name, int age, bool hasFur, int limbs = 4)
        : Animal(name, age), hasFur(hasFur), limbCount(limbs) {
        cout << "  Это млекопитающее" << endl;
    }

    // Переопределение виртуального метода
    void makeSound() const override {
        cout << name << " (млекопитающее) издает характерный звук" << endl;
    }

    // Новый метод, специфичный для млекопитающих
    void feedMilk() const {
        cout << name << " кормит детенышей молоком" << endl;
    }

    bool hasFurCoat() const { return hasFur; }
};

// ==================== ПРОИЗВОДНЫЙ КЛАСС 2 ====================
class Bird : public Animal {
protected:
    double wingspan;
    bool canFly;

public:
    Bird(const string& name, int age, double wingspan, bool canFly = true)
        : Animal(name, age), wingspan(wingspan), canFly(canFly) {
        cout << "  Это птица" << endl;
    }

    // Переопределение виртуального метода
    void makeSound() const override {
        cout << name << " (птица) поет" << endl;
    }

    // Новый метод
    void fly() const {
        if (canFly) {
            cout << name << " летает с размахом крыльев " << wingspan << " м" << endl;
        }
        else {
            cout << name << " не умеет летать" << endl;
        }
    }
};

// ==================== МНОГОУРОВНЕВОЕ НАСЛЕДОВАНИЕ ====================
class Dog : public Mammal {
private:
    string breed;
    bool isTrained;

public:
    Dog(const string& name, int age, const string& breed, bool trained = false)
        : Mammal(name, age, true, 4), breed(breed), isTrained(trained) {
        cout << "    Конкретно это собака породы " << breed << endl;
    }

    // Полное переопределение метода
    void makeSound() const override {
        cout << name << " гавкает: Гав-гав!" << endl;
    }

    // Дополнительное поведение
    void fetch() const {
        cout << name << " приносит палку" << endl;
    }

    // Перегрузка метода (не путать с переопределением!)
    void fetch(const string& item) const {
        cout << name << " приносит " << item << endl;
    }

    string getBreed() const { return breed; }
    bool isWellTrained() const { return isTrained; }
};

class Cat : public Mammal {
private:
    bool isIndoor;

public:
    Cat(const string& name, int age, bool indoor = true)
        : Mammal(name, age, true), isIndoor(indoor) {
        cout << "    Конкретно это кот" << endl;
    }

    void makeSound() const override {
        cout << name << " мяукает: Мяу-мяу!" << endl;
    }

    void climbTree() const {
        if (!isIndoor) {
            cout << name << " лазает по деревьям" << endl;
        }
        else {
            cout << name << " домашний, не лазает по деревьям" << endl;
        }
    }
};

// ==================== ИНТЕРФЕЙСЫ (ЧИСТО ВИРТУАЛЬНЫЕ КЛАССЫ) ====================
// В C++ интерфейсы - это классы, содержащие только чистые виртуальные методы
class IFlyable {
public:
    virtual void fly() = 0;  // Чистый виртуальный метод
    virtual ~IFlyable() {}   // Виртуальный деструктор для интерфейса
};

class ISwimmable {
public:
    virtual void swim() = 0;
    virtual double getMaxDepth() const = 0;
    virtual ~ISwimmable() {}
};

// ==================== МНОЖЕСТВЕННОЕ НАСЛЕДОВАНИЕ ====================
class Duck : public Bird, public IFlyable, public ISwimmable {
private:
    string featherColor;

public:
    Duck(const string& name, int age, const string& color = "белый")
        : Bird(name, age, 0.8, true), featherColor(color) {
        cout << "    Конкретно это утка цвета " << color << endl;
    }

    // Переопределение метода Animal
    void makeSound() const override {
        cout << name << " крякает: Кря-кря!" << endl;
    }

    // Реализация интерфейса IFlyable
    void fly() override {
        cout << name << " летает по-утиному" << endl;
    }

    // Реализация интерфейса ISwimmable
    void swim() override {
        cout << name << " плавает в пруду" << endl;
    }

    double getMaxDepth() const override {
        return 3.0; // Утки могут нырять до 3 метров
    }

    // Свой метод
    void migrate() const {
        cout << name << " мигрирует на юг" << endl;
    }
};

// ==================== АБСТРАКТНЫЙ КЛАСС ====================
// Абстрактный класс содержит хотя бы один чистый виртуальный метод
class Shape {
protected:
    string color;

public:
    Shape(const string& color) : color(color) {}

    // Чистый виртуальный метод - делает класс абстрактным
    virtual double area() const = 0;

    // Другой чисто виртуальный метод
    virtual double perimeter() const = 0;

    // Виртуальный, но не чистый метод
    virtual void draw() const {
        cout << "Рисую фигуру цвета " << color << endl;
    }

    // Виртуальный деструктор
    virtual ~Shape() {
        cout << "Фигура уничтожена" << endl;
    }
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r, const string& color = "красный")
        : Shape(color), radius(r) {
    }

    // Реализация чисто виртуальных методов
    double area() const override {
        return 3.14159 * radius * radius;
    }

    double perimeter() const override {
        return 2 * 3.14159 * radius;
    }

    // Переопределение виртуального метода
    void draw() const override {
        cout << "Рисую круг радиусом " << radius
            << " цвета " << color << endl;
    }

    double getRadius() const { return radius; }
};

class Rectangle : public Shape {
private:
    double width, height;

public:
    Rectangle(double w, double h, const string& color = "синий")
        : Shape(color), width(w), height(h) {
    }

    double area() const override {
        return width * height;
    }

    double perimeter() const override {
        return 2 * (width + height);
    }

    void draw() const override {
        cout << "Рисую прямоугольник " << width << "x" << height
            << " цвета " << color << endl;
    }
};

// ==================== ДЕМОНСТРАЦИЯ ПРИНЦИПОВ ООП ====================
void demonstrateOOP() {
    cout << "\n=== ДЕМОНСТРАЦИЯ НАСЛЕДОВАНИЯ ===" << endl;

    // 1. ИНКАПСУЛЯЦИЯ - сокрытие реализации
    Dog dog("Бобик", 3, "овчарка", true);
    dog.makeSound();      // Публичный интерфейс
    dog.sleep();          // Унаследованный метод
    // dog.hasFur = true; // ОШИБКА: protected поле

    cout << "\n=== ДЕМОНСТРАЦИЯ ПОЛИМОРФИЗМА ===" << endl;

    // 2. ПОЛИМОРФИЗМ - работа через указатели на базовый класс
    vector<unique_ptr<Animal>> animals;
    animals.push_back(make_unique<Dog>("Шарик", 2, "дворняга"));
    animals.push_back(make_unique<Cat>("Мурка", 1));
    animals.push_back(make_unique<Duck>("Дональд", 1));

    for (const auto& animal : animals) {
        animal->makeSound();  // Вызовется переопределенный метод
        animal->sleep();      // Вызовется метод базового класса
    }

    // 3. Динамическое приведение типов (RTTI)
    cout << "\n=== ДИНАМИЧЕСКОЕ ПРИВЕДЕНИЕ ТИПОВ ===" << endl;
    for (const auto& animal : animals) {
        // Попытка привести к Dog
        if (auto dogPtr = dynamic_cast<Dog*>(animal.get())) {
            cout << "Это собака породы " << dogPtr->getBreed() << endl;
            dogPtr->fetch();
        }
        // Попытка привести к Duck
        else if (auto duckPtr = dynamic_cast<Duck*>(animal.get())) {
            cout << "Это утка, реализующая интерфейсы:" << endl;
            duckPtr->fly();   // Метод из IFlyable
            duckPtr->swim();  // Метод из ISwimmable
        }
    }

    cout << "\n=== ИЕРАРХИЯ НАСЛЕДОВАНИЯ ===" << endl;

    // Демонстрация иерархии
    Mammal whale("Кит", 10, false);
    whale.makeSound();
    whale.feedMilk();

    Bird penguin("Пингвин", 2, 0.5, false);
    penguin.makeSound();
    penguin.fly();  // Пингвин не умеет летать

    cout << "\n=== АБСТРАКТНЫЕ КЛАССЫ И ИНТЕРФЕЙСЫ ===" << endl;

    // Работа с абстрактными классами
    vector<unique_ptr<Shape>> shapes;
    shapes.push_back(make_unique<Circle>(5.0, "красный"));
    shapes.push_back(make_unique<Rectangle>(4.0, 6.0, "синий"));

    for (const auto& shape : shapes) {
        shape->draw();
        cout << "  Площадь: " << shape->area()
            << ", Периметр: " << shape->perimeter() << endl;
    }

    // Множественное наследование интерфейсов
    cout << "\n=== МНОЖЕСТВЕННОЕ НАСЛЕДОВАНИЕ ===" << endl;
    Duck wildDuck("Дикая утка", 1, "зеленый");

    // Работа через разные интерфейсы
    IFlyable* flyer = &wildDuck;
    ISwimmable* swimmer = &wildDuck;

    flyer->fly();
    swimmer->swim();
    cout << "Максимальная глубина: " << swimmer->getMaxDepth() << " м" << endl;

    cout << "\n=== ПРИНЦИП ПОДСТАНОВКИ ЛИСКОВ ===" << endl;

    // 4. LSP - объекты производных классов должны заменять объекты базовых
    Animal* animalPtr = new Dog("Рекс", 4, "лабрадор");
    animalPtr->makeSound();  // Работает корректно
    animalPtr->sleep();      // Работает корректно
    delete animalPtr;
}

// ==================== ДОПОЛНИТЕЛЬНЫЕ КОНЦЕПЦИИ ====================
// Виртуальное наследование (решение проблемы ромбовидного наследования)
class PoweredDevice {
public:
    int powerLevel;
    PoweredDevice(int power = 100) : powerLevel(power) {
        cout << "Устройство с мощностью " << powerLevel << endl;
    }
};

class Scanner : virtual public PoweredDevice {
public:
    Scanner(int power = 100) : PoweredDevice(power) {
        cout << "Сканер создан" << endl;
    }

    void scan() const {
        cout << "Сканирую документ (мощность: " << powerLevel << ")" << endl;
    }
};

class Printer : virtual public PoweredDevice {
public:
    Printer(int power = 100) : PoweredDevice(power) {
        cout << "Принтер создан" << endl;
    }

    void print() const {
        cout << "Печатаю документ (мощность: " << powerLevel << ")" << endl;
    }
};

// Множественное наследование с виртуальным базовым классом
class Copier : public Scanner, public Printer {
public:
    Copier(int power = 100) : PoweredDevice(power), Scanner(power), Printer(power) {
        cout << "Копир создан" << endl;
    }

    void copy() const {
        cout << "Копирую документ (общая мощность: " << powerLevel << ")" << endl;
        scan();
        print();
    }
};

// ==================== ГЛАВНАЯ ФУНКЦИЯ ====================
int main() {
    cout << "ДЕМОНСТРАЦИЯ ООП В C++" << endl;
    cout << "======================\n" << endl;

    demonstrateOOP();

    cout << "\n=== ВИРТУАЛЬНОЕ НАСЛЕДОВАНИЕ ===" << endl;
    Copier officeCopier(150);
    officeCopier.copy();
    // Без virtual наследование было бы две копии PoweredDevice

    cout << "\n=== ДОСТУП К ПЕРЕОПРЕДЕЛЕННЫМ МЕТОДАМ ===" << endl;

    // Вызов переопределенного метода
    Dog myDog("Дружок", 2, "такса");
    myDog.makeSound();

    // Явный вызов метода базового класса
    cout << "\nЯвный вызов метода базового класса:" << endl;
    myDog.Mammal::makeSound();
    myDog.Animal::makeSound();

    cout << "\n=== РАБОТА С КОЛЛЕКЦИЯМИ РАЗНЫХ ТИПОВ ===" << endl;

    // Пример SOLID принципов:
    // 1. Single Responsibility - каждый класс имеет одну ответственность
    // 2. Open/Closed - классы открыты для расширения, закрыты для модификации
    // 3. Liskov Substitution - продемонстрировано выше
    // 4. Interface Segregation - узкие интерфейсы (IFlyable, ISwimmable)
    // 5. Dependency Inversion - завись от абстракций, а не от конкретных классов

    // Демонстрация зависимости от абстракций
    vector<unique_ptr<IFlyable>> flyables;
    flyables.push_back(make_unique<Duck>("Уточка", 1));
    // flyables.push_back(make_unique<Dog>("...", ...)); // Ошибка: Dog не реализует IFlyable

    for (const auto& flyable : flyables) {
        flyable->fly();
    }

    cout << "\n======================" << endl;
    cout << "Демонстрация завершена!" << endl;

    return 0;
}