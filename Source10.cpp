#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <any>  // C++17 для аналога boxing
#include <variant>  // C++17 для type-safe union
#include <functional>

using namespace std;

// ==================== СТРУКТУРЫ (VALUE TYPES) ====================

// Структура в C++ - тип значения (хранится в стеке, если не использовать new)
struct Point {
    // Публичные поля по умолчанию (в отличие от class)
    double x;
    double y;

    // Конструкторы
    Point() : x(0), y(0) {
        cout << "Point создан конструктором по умолчанию" << endl;
    }

    Point(double x, double y) : x(x), y(y) {
        cout << "Point создан с параметрами (" << x << ", " << y << ")" << endl;
    }

    // Методы в структурах
    void display() const {
        cout << "Point(" << x << ", " << y << ")" << endl;
    }

    double distanceToOrigin() const {
        return sqrt(x * x + y * y);
    }

    // Перегрузка операторов
    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

// Структура с различными способами инициализации
struct Person {
    string name;
    int age;
    double height;

    // Конструктор с списком инициализации (рекомендуемый способ)
    Person(const string& n, int a, double h) : name(n), age(a), height(h) {
        cout << "Person создан: " << name << endl;
    }

    // Конструктор с default значениями
    Person() : name("Unknown"), age(0), height(0.0) {}

    void display() const {
        cout << name << ", " << age << " лет, рост " << height << " м" << endl;
    }
};

// ==================== РАЗЛИЧНЫЕ СПОСОБЫ ИНИЦИАЛИЗАЦИИ СТРУКТУР ====================

void demonstrateInitialization() {
    cout << "\n=== СПОСОБЫ ИНИЦИАЛИЗАЦИИ СТРУКТУР ===" << endl;

    // 1. Инициализация по умолчанию
    Point p1;  // Вызов конструктора по умолчанию
    p1.display();

    // 2. Прямая инициализация
    Point p2(3.5, 4.2);
    p2.display();

    // 3. Uniform initialization (C++11)
    Point p3{ 2.0, 5.0 };
    p3.display();

    // 4. Copy initialization
    Point p4 = Point(1.0, 2.0);
    p4.display();

    // 5. Aggregate initialization (если нет пользовательских конструкторов)
    struct SimplePoint {
        double x, y;
    };

    SimplePoint sp1 = { 10.0, 20.0 };  // Aggregate initialization
    cout << "SimplePoint: " << sp1.x << ", " << sp1.y << endl;

    // 6. Designated initializers (C++20)
#if __cplusplus >= 202002L
    SimplePoint sp2 = { .x = 5.0, .y = 6.0 };
    cout << "Designated init: " << sp2.x << ", " << sp2.y << endl;
#endif

    // 7. Value initialization
    Point p5{};  // Инициализация нулями
    p5.display();
}

// ==================== ТИПЫ ЗНАЧЕНИЙ VS ССЫЛОЧНЫЕ ТИПЫ ====================

void demonstrateValueVsReference() {
    cout << "\n=== ТИПЫ ЗНАЧЕНИЙ VS ССЫЛОЧНЫЕ ТИПЫ ===" << endl;

    // ТИП ЗНАЧЕНИЯ (value type) - копируется при присваивании
    cout << "\n1. ТИП ЗНАЧЕНИЯ (структура):" << endl;
    Point original(1.0, 2.0);
    Point copy = original;  // Копирование значения

    cout << "До изменения:" << endl;
    cout << "original: "; original.display();
    cout << "copy: "; copy.display();

    copy.x = 100.0;  // Изменяем копию

    cout << "\nПосле изменения копии:" << endl;
    cout << "original: "; original.display();  // Оригинал не изменился!
    cout << "copy: "; copy.display();

    // ССЫЛОЧНЫЕ ТИПЫ в C++
    cout << "\n2. ССЫЛОЧНЫЕ ТИПЫ в C++:" << endl;

    // а) Ссылка (reference) - аналог ref в C#
    Point& refToOriginal = original;  // Ссылка - псевдоним для существующего объекта
    refToOriginal.x = 999.0;

    cout << "После изменения через ссылку:" << endl;
    cout << "original: "; original.display();  // Оригинал изменился!
    cout << "refToOriginal: "; refToOriginal.display();

    // б) Указатель (pointer) - содержит адрес памяти
    Point* ptrToOriginal = &original;  // Получаем адрес
    ptrToOriginal->y = 888.0;  // Доступ через ->

    cout << "\nПосле изменения через указатель:" << endl;
    cout << "original: "; original.display();  // Оригинал изменился!
    cout << "*ptrToOriginal: "; ptrToOriginal->display();

    // в) Умные указатели (smart pointers) - ссылочные типы с автоматическим управлением памятью
    cout << "\n3. УМНЫЕ УКАЗАТЕЛИ (smart pointers):" << endl;

    // unique_ptr - эксклюзивное владение
    unique_ptr<Point> uniquePtr = make_unique<Point>(5.0, 6.0);
    cout << "unique_ptr: "; uniquePtr->display();

    // shared_ptr - разделяемое владение с подсчетом ссылок
    shared_ptr<Point> sharedPtr1 = make_shared<Point>(7.0, 8.0);
    shared_ptr<Point> sharedPtr2 = sharedPtr1;  // Оба указывают на один объект

    cout << "shared_ptr1 use_count: " << sharedPtr1.use_count() << endl;
    cout << "shared_ptr2: "; sharedPtr2->display();

    // weak_ptr - слабая ссылка (не увеличивает счетчик)
    weak_ptr<Point> weakPtr = sharedPtr1;
    cout << "weak_ptr expired: " << weakPtr.expired() << endl;
}

// ==================== ПЕРЕДАЧА ПО ЗНАЧЕНИЮ, ССЫЛКЕ И УКАЗАТЕЛЮ ====================

// Аналог ref параметров в C#
void modifyByValue(Point p) {  // Копирование
    p.x += 10;
    cout << "Внутри modifyByValue: "; p.display();
}

void modifyByReference(Point& p) {  // Ссылка (аналог ref)
    p.x += 10;
    cout << "Внутри modifyByReference: "; p.display();
}

void modifyByPointer(Point* p) {  // Указатель
    if (p) {  // Проверка на nullptr
        p->x += 10;
        cout << "Внутри modifyByPointer: "; p->display();
    }
}

void modifyByConstReference(const Point& p) {  // Константная ссылка
    // p.x += 10;  // ОШИБКА: нельзя изменить const объект
    cout << "Внутри modifyByConstReference: "; p.display();
}

void demonstrateParameterPassing() {
    cout << "\n=== ПЕРЕДАЧА ПАРАМЕТРОВ (АНАЛОГ REF В C#) ===" << endl;

    Point point(1.0, 2.0);

    cout << "Исходная точка: "; point.display();

    modifyByValue(point);
    cout << "После modifyByValue: "; point.display();  // Не изменилась

    modifyByReference(point);
    cout << "После modifyByReference: "; point.display();  // Изменилась!

    modifyByPointer(&point);
    cout << "После modifyByPointer: "; point.display();  // Изменилась!

    modifyByConstReference(point);
}

// ==================== BOXING/UNBOXING В C++ ====================

// В C++ нет прямых аналогов boxing/unboxing, но есть похожие концепции

// 1. Использование указателей для "boxing" типов значений
void boxingWithPointers() {
    cout << "\n=== BOXING С ПОМОЩЬЮ УКАЗАТЕЛЕЙ ===" << endl;

    // "Boxing" - помещаем тип значения в кучу
    int value = 42;
    int* boxed = new int(value);  // Выделяем память в куче (boxing)

    cout << "Исходное значение: " << value << endl;
    cout << "Boxed значение (через указатель): " << *boxed << endl;

    // "Unboxing" - получаем значение обратно
    int unboxed = *boxed;  // Разыменование (unboxing)
    cout << "Unboxed значение: " << unboxed << endl;

    delete boxed;  // Важно освободить память!
}

// 2. Использование std::any (C++17) для type-safe boxing
#include <any>
void boxingWithAny() {
    cout << "\n=== BOXING С ПОМОЩЬЮ STD::ANY ===" << endl;

    // Boxing различных типов в any
    std::any boxedInt = 42;
    std::any boxedDouble = 3.14;
    std::any boxedString = string("Hello");
    std::any boxedPoint = Point(1.0, 2.0);

    // Unboxing с проверкой типа
    if (boxedInt.type() == typeid(int)) {
        int unboxedInt = std::any_cast<int>(boxedInt);
        cout << "Unboxed int: " << unboxedInt << endl;
    }

    try {
        double unboxedDouble = std::any_cast<double>(boxedDouble);
        cout << "Unboxed double: " << unboxedDouble << endl;

        // Ошибка при неправильном unboxing
        // int wrong = std::any_cast<int>(boxedDouble); // Выбросит исключение
    }
    catch (const bad_any_cast& e) {
        cout << "Ошибка unboxing: " << e.what() << endl;
    }
}

// 3. Использование std::variant (C++17) для type-safe union
#include <variant>
void boxingWithVariant() {
    cout << "\n=== BOXING С ПОМОЩЬЮ STD::VARIANT ===" << endl;

    // Variant может хранить один из указанных типов
    using Number = variant<int, double, string>;

    Number num1 = 42;          // Хранит int
    Number num2 = 3.14;        // Хранит double
    Number num3 = "Hello";     // Хранит const char*, который преобразуется в string

    // Visit pattern для обработки разных типов
    auto visitor = [](auto&& arg) {
        using T = decay_t<decltype(arg)>;
        if constexpr (is_same_v<T, int>) {
            cout << "Integer: " << arg << endl;
        }
        else if constexpr (is_same_v<T, double>) {
            cout << "Double: " << arg << endl;
        }
        else if constexpr (is_same_v<T, string>) {
            cout << "String: " << arg << endl;
        }
        };

    visit(visitor, num1);
    visit(visitor, num2);
    visit(visitor, num3);

    // Безопасное получение значения
    if (holds_alternative<int>(num1)) {
        int value = get<int>(num1);
        cout << "Получен int: " << value << endl;
    }
}

// ==================== СТРУКТУРЫ С РАЗНЫМИ ХАРАКТЕРИСТИКАМИ ====================

// POD (Plain Old Data) структура - совместима с C
struct PODStruct {
    int x;
    double y;
    char name[32];
};  // Не имеет конструкторов, виртуальных функций и т.д.

// Структура с методами
struct Employee {
    string name;
    int id;
    double salary;

    Employee(const string& n, int i, double s) : name(n), id(i), salary(s) {}

    // Методы
    void giveRaise(double percentage) {
        salary *= (1.0 + percentage / 100.0);
    }

    void display() const {
        cout << "Employee #" << id << ": " << name
            << ", зарплата: " << salary << endl;
    }
};

// Структура с перегрузкой операторов
struct Complex {
    double real;
    double imag;

    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    // Перегрузка операторов
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex operator*(const Complex& other) const {
        return Complex(
            real * other.real - imag * other.imag,
            real * other.imag + imag * other.real
        );
    }

    void display() const {
        cout << real << " + " << imag << "i" << endl;
    }
};

// ==================== ПРАКТИЧЕСКИЙ ПРИМЕР: РАБОТА С ГЕОМЕТРИЧЕСКИМИ ФИГУРАМИ ====================

// Базовая структура для фигур
struct Shape {
    enum class Type { CIRCLE, RECTANGLE, TRIANGLE } type;

    // Union для хранения разных данных в одной памяти (аналог variant для C)
    union Data {
        struct { double radius; } circle;
        struct { double width, height; } rectangle;
        struct { double base, height; } triangle;
    } data;

    // Создание фигур
    static Shape createCircle(double radius) {
        Shape s;
        s.type = Type::CIRCLE;
        s.data.circle = { radius };
        return s;
    }

    static Shape createRectangle(double width, double height) {
        Shape s;
        s.type = Type::RECTANGLE;
        s.data.rectangle = { width, height };
        return s;
    }

    // Метод для вычисления площади
    double area() const {
        switch (type) {
        case Type::CIRCLE:
            return 3.14159 * data.circle.radius * data.circle.radius;
        case Type::RECTANGLE:
            return data.rectangle.width * data.rectangle.height;
        case Type::TRIANGLE:
            return 0.5 * data.triangle.base * data.triangle.height;
        default:
            return 0;
        }
    }

    void display() const {
        switch (type) {
        case Type::CIRCLE:
            cout << "Круг радиусом " << data.circle.radius;
            break;
        case Type::RECTANGLE:
            cout << "Прямоугольник " << data.rectangle.width
                << "x" << data.rectangle.height;
            break;
        case Type::TRIANGLE:
            cout << "Треугольник основание " << data.triangle.base
                << " высота " << data.triangle.height;
            break;
        }
        cout << ", площадь: " << area() << endl;
    }
};

// ==================== ШАБЛОННЫЕ СТРУКТУРЫ ====================

template<typename T>
struct Pair {
    T first;
    T second;

    Pair(const T& a, const T& b) : first(a), second(b) {}

    T sum() const { return first + second; }
    T product() const { return first * second; }

    void display() const {
        cout << "(" << first << ", " << second << ")" << endl;
    }
};

// Специализация для строк
template<>
struct Pair<string> {
    string first;
    string second;

    Pair(const string& a, const string& b) : first(a), second(b) {}

    string concatenate() const { return first + " " + second; }

    void display() const {
        cout << first << " и " << second << endl;
    }
};

// ==================== ГЛАВНАЯ ФУНКЦИЯ ====================

int main() {
    cout << "ДЕМОНСТРАЦИЯ СТРУКТУР И ССЫЛОЧНЫХ ТИПОВ В C++" << endl;
    cout << "=============================================\n" << endl;

    // Демонстрация инициализации
    demonstrateInitialization();

    // Демонстрация типов значений и ссылок
    demonstrateValueVsReference();

    // Демонстрация передачи параметров
    demonstrateParameterPassing();

    // Демонстрация boxing/unboxing
    boxingWithPointers();
    boxingWithAny();
    boxingWithVariant();

    // Практические примеры
    cout << "\n=== ПРАКТИЧЕСКИЕ ПРИМЕРЫ ===" << endl;

    // 1. Работа с Employee
    cout << "\n1. СТРУКТУРА EMPLOYEE:" << endl;
    Employee emp("Иван Петров", 1001, 50000.0);
    emp.display();
    emp.giveRaise(10.0);
    cout << "После повышения: ";
    emp.display();

    // 2. Работа с Complex
    cout << "\n2. КОМПЛЕКСНЫЕ ЧИСЛА:" << endl;
    Complex c1(2.0, 3.0);
    Complex c2(1.0, 4.0);

    cout << "c1 = "; c1.display();
    cout << "c2 = "; c2.display();

    Complex sum = c1 + c2;
    Complex product = c1 * c2;

    cout << "c1 + c2 = "; sum.display();
    cout << "c1 * c2 = "; product.display();

    // 3. Работа с фигурами
    cout << "\n3. ГЕОМЕТРИЧЕСКИЕ ФИГУРЫ:" << endl;
    Shape circle = Shape::createCircle(5.0);
    Shape rectangle = Shape::createRectangle(4.0, 6.0);

    circle.display();
    rectangle.display();

    // 4. Шаблонные структуры
    cout << "\n4. ШАБЛОННЫЕ СТРУКТУРЫ:" << endl;

    Pair<int> intPair(3, 4);
    cout << "Int pair: ";
    intPair.display();
    cout << "Сумма: " << intPair.sum() << ", произведение: " << intPair.product() << endl;

    Pair<double> doublePair(2.5, 3.5);
    cout << "Double pair: ";
    doublePair.display();

    Pair<string> stringPair("Hello", "World");
    cout << "String pair: ";
    stringPair.display();
    cout << "Конкатенация: " << stringPair.concatenate() << endl;

    // 5. Массивы структур
    cout << "\n5. МАССИВЫ СТРУКТУР:" << endl;
    Point points[3] = {
        Point(1, 2),
        Point(3, 4),
        Point(5, 6)
    };

    for (int i = 0; i < 3; ++i) {
        cout << "points[" << i << "] = ";
        points[i].display();
    }

    // 6. Вектор структур
    cout << "\n6. ВЕКТОР СТРУКТУР:" << endl;
    vector<Person> people;
    people.push_back(Person("Анна", 25, 1.65));
    people.push_back(Person("Борис", 30, 1.80));
    people.push_back(Person("Виктор", 35, 1.75));

    for (const auto& person : people) {
        person.display();
    }

    // 7. Ссылки на элементы массива
    cout << "\n7. ССЫЛКИ НА ЭЛЕМЕНТЫ МАССИВА:" << endl;
    int numbers[] = { 10, 20, 30, 40, 50 };

    // Ссылка на элемент массива
    int& refToElement = numbers[2];  // refToElement ссылается на numbers[2]
    refToElement = 999;

    cout << "После изменения через ссылку:" << endl;
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    // 8. Возврат ссылки из функции
    cout << "\n8. ВОЗВРАТ ССЫЛКИ ИЗ ФУНКЦИИ:" << endl;

    auto getLargest = [](vector<int>& vec) -> int& {
        if (vec.empty()) {
            throw runtime_error("Вектор пуст");
        }

        int& largest = vec[0];
        for (int& num : vec) {
            if (num > largest) {
                largest = num;
            }
        }
        return largest;
        };

    vector<int> values = { 1, 5, 3, 9, 2 };
    int& largestRef = getLargest(values);
    cout << "Наибольший элемент: " << largestRef << endl;

    largestRef = 100;  // Изменяем через ссылку
    cout << "После изменения наибольшего элемента:" << endl;
    for (int num : values) {
        cout << num << " ";
    }
    cout << endl;

    cout << "\n=============================================" << endl;
    cout << "Демонстрация завершена!" << endl;

    return 0;
}