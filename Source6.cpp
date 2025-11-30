using System;

namespace OOPDemo
{
    // Базовый класс
    public class Person
    {
        // Поля (обычно private)
        private string _id;

        // Свойства (public с контролем доступа)
        public string Name{ get; set; }
        public int Age{ get; private set; }
        public string Email{ get; set; }

            // Статическое поле - общее для всех экземпляров
        private static int _personCount = 0;

        // Конструкторы
        public Person()
        {
            _personCount++;
            _id = $"P{_personCount:000}";
            Console.WriteLine($"Создан человек с ID: {_id}");
        }

        // Конструктор с параметрами
        public Person(string name, int age, string email = "") : this()
        {
            Name = name;
            Age = age;
            Email = email;
        }

        // Статическое свойство
        public static int PersonCount = > _personCount;

        // Методы
        public void DisplayInfo()
        {
            Console.WriteLine($"ID: {_id}, Имя: {Name}, Возраст: {Age}, Email: {Email}");
        }

        public void CelebrateBirthday()
        {
            Age++;
            Console.WriteLine($"{Name} празднует день рождения! Теперь ему {Age} лет.");
        }

        // Статический метод
        public static void DisplayTotalCount()
        {
            Console.WriteLine($"Всего создано людей: {_personCount}");
        }

        // Финализатор
        ~Person()
        {
            Console.WriteLine($"Человек {_id} удален из памяти");
        }
    }

    class BasicClassDemo
    {
        public static void Demo()
        {
            Console.WriteLine("=== КЛАССЫ И КОНСТРУКТОРЫ ===");

            // Создание объектов
            Person person1 = new Person();
            person1.Name = "Иван";
            person1.DisplayInfo();

            Person person2 = new Person("Мария", 25, "maria@mail.ru");
            person2.DisplayInfo();

            Person person3 = new Person("Петр", 30);
            person3.DisplayInfo();

            // Вызов методов
            person2.CelebrateBirthday();
            person2.DisplayInfo();

            // Статический метод
            Person.DisplayTotalCount();
        }
    }
}
using System;

namespace OOPDemo
{
    // Базовый класс
    public class Animal
    {
        public string Name{ get; set; }
        public int Age{ get; set; }

            // Виртуальный метод - может быть переопределен
            public virtual void MakeSound()
        {
            Console.WriteLine("Животное издает звук");
        }

        // Обычный метод
        public void Sleep()
        {
            Console.WriteLine($"{Name} спит");
        }
    }

    // Производный класс
    public class Dog : Animal
    {
        public string Breed{ get; set; }

            // Переопределение виртуального метода
            public override void MakeSound()
        {
            Console.WriteLine($"{Name} гавкает: Гав-гав!");
        }

        // Новый метод
        public void Fetch()
        {
            Console.WriteLine($"{Name} приносит палку");
        }
    }

    // Еще один производный класс
    public class Cat : Animal
    {
        public bool IsIndoor{ get; set; }

            public override void MakeSound()
        {
            Console.WriteLine($"{Name} мяукает: Мяу-мяу!");
        }

        public void ClimbTree()
        {
            Console.WriteLine($"{Name} лазает по деревьям");
        }
    }

    class InheritanceDemo
    {
        public static void Demo()
        {
            Console.WriteLine("\n=== НАСЛЕДОВАНИЕ И ПОЛИМОРФИЗМ ===");

            Dog dog = new Dog
            {
                Name = "Бобик",
                Age = 3,
                Breed = "Овчарка"
            };

            Cat cat = new Cat
            {
                Name = "Мурка",
                Age = 2,
                IsIndoor = true
            };

            // Полиморфизм - работа с объектами через базовый класс
            Animal[] animals = { dog, cat };

            foreach(Animal animal in animals)
            {
                animal.MakeSound(); // Вызовется переопределенный метод
                animal.Sleep();

                // Проверка типа и приведение
                if (animal is Dog d)
                {
                    d.Fetch();
                }
                else if (animal is Cat c)
                {
                    c.ClimbTree();
                }

                Console.WriteLine();
            }
        }
    }
}
using System;

namespace OOPDemo
{
    public class Calculator
    {
        // Динамические поля (принадлежат экземпляру)
        private string _model;
        private int _usageCount;

        // Статические поля (принадлежат классу)
        private static string _brand = "CalcCorp";
        private static int _totalCalculations = 0;
        private static int _instanceCount = 0;

        // Конструктор
        public Calculator(string model)
        {
            _model = model;
            _usageCount = 0;
            _instanceCount++;
            Console.WriteLine($"Создан калькулятор {_brand} {_model}. Всего экземпляров: {_instanceCount}");
        }

        // Динамические методы
        public int Add(int a, int b)
        {
            _usageCount++;
            _totalCalculations++;
            return a + b;
        }

        public int Multiply(int a, int b)
        {
            _usageCount++;
            _totalCalculations++;
            return a * b;
        }

        public void DisplayUsage()
        {
            Console.WriteLine($"Калькулятор {_model} использован {_usageCount} раз");
        }

        // Статические методы
        public static void DisplayTotalCalculations()
        {
            Console.WriteLine($"Всего выполнено расчетов: {_totalCalculations}");
        }

        public static void DisplayInstanceCount()
        {
            Console.WriteLine($"Всего создано калькуляторов: {_instanceCount}");
        }

        public static void ChangeBrand(string newBrand)
        {
            _brand = newBrand;
            Console.WriteLine($"Бренд изменен на: {newBrand}");
        }

        // Статическое свойство
        public static string Brand = > _brand;

        // Статический конструктор
        static Calculator()
        {
            Console.WriteLine("Статический конструктор Calculator вызван");
            _totalCalculations = 0;
            _instanceCount = 0;
        }
    }

    class StaticVsInstanceDemo
    {
        public static void Demo()
        {
            Console.WriteLine("\n=== СТАТИЧЕСКИЕ И ДИНАМИЧЕСКИЕ ЧЛЕНЫ ===");

            Console.WriteLine($"Бренд калькуляторов: {Calculator.Brand}");

            Calculator calc1 = new Calculator("Pro-100");
            Calculator calc2 = new Calculator("Basic-50");

            // Использование динамических методов
            int result1 = calc1.Add(5, 3);
            int result2 = calc1.Multiply(4, 6);
            int result3 = calc2.Add(10, 20);

            Console.WriteLine($"Результаты: {result1}, {result2}, {result3}");

            // Динамические методы показывают состояние экземпляра
            calc1.DisplayUsage();
            calc2.DisplayUsage();

            // Статические методы показывают общее состояние
            Calculator.DisplayTotalCalculations();
            Calculator.DisplayInstanceCount();

            // Изменение статического поля
            Calculator.ChangeBrand("SuperCalc");
            Console.WriteLine($"Новый бренд: {Calculator.Brand}");
        }
    }
}
using System;

namespace OOPDemo
{
    // Статический класс - не может иметь экземпляров
    public static class MathHelper
    {
        // Статические поля
        public static readonly double Pi = 3.14159;
        public static readonly double E = 2.71828;

        // Статический конструктор
        static MathHelper()
        {
            Console.WriteLine("Статический класс MathHelper инициализирован");
        }

        // Статические методы
        public static double CircleArea(double radius)
        {
            return Pi * radius * radius;
        }

        public static double CircleCircumference(double radius)
        {
            return 2 * Pi * radius;
        }

        public static double Power(double baseValue, double exponent)
        {
            return Math.Pow(baseValue, exponent);
        }

        public static bool IsPrime(int number)
        {
            if (number <= 1) return false;
            if (number == 2) return true;
            if (number % 2 == 0) return false;

            for (int i = 3; i <= Math.Sqrt(number); i += 2)
            {
                if (number % i == 0)
                    return false;
            }

            return true;
        }

        // Статическое свойство
        public static string Version = > "1.0.0";
    }

    // Еще один статический класс для утилит
    public static class StringUtils
    {
        public static string Reverse(string input)
        {
            char[] chars = input.ToCharArray();
            Array.Reverse(chars);
            return new string(chars);
        }

        public static bool IsPalindrome(string text)
        {
            string clean = text.ToLower().Replace(" ", "");
            return clean == Reverse(clean);
        }

        public static int WordCount(string text)
        {
            if (string.IsNullOrWhiteSpace(text))
                return 0;

            return text.Split(new char[] { ' ', '.', ',', '!', '?' },
                StringSplitOptions.RemoveEmptyEntries).Length;
        }
    }

    class StaticClassDemo
    {
        public static void Demo()
        {
            Console.WriteLine("\n=== СТАТИЧЕСКИЕ КЛАССЫ ===");

            Console.WriteLine($"Версия MathHelper: {MathHelper.Version}");
            Console.WriteLine($"Pi = {MathHelper.Pi}");
            Console.WriteLine($"E = {MathHelper.E}");

            double radius = 5.0;
            Console.WriteLine($"Площадь круга радиусом {radius}: {MathHelper.CircleArea(radius):F2}");
            Console.WriteLine($"Длина окружности радиусом {radius}: {MathHelper.CircleCircumference(radius):F2}");

            Console.WriteLine($"2^10 = {MathHelper.Power(2, 10)}");

            // Проверка простых чисел
            Console.WriteLine("\nПростые числа до 20:");
            for (int i = 1; i <= 20; i++)
            {
                if (MathHelper.IsPrime(i))
                {
                    Console.Write($"{i} ");
                }
            }
            Console.WriteLine();

            // Работа со строками
            string testString = "А роза упала на лапу Азора";
            Console.WriteLine($"\nИсходная строка: {testString}");
            Console.WriteLine($"Перевернутая: {StringUtils.Reverse(testString)}");
            Console.WriteLine($"Палиндром: {StringUtils.IsPalindrome(testString)}");
            Console.WriteLine($"Количество слов: {StringUtils.WordCount(testString)}");
        }
    }
}
using System;
using System.Collections.Generic;
using System.Text;

namespace OOPDemo
{
    // Статический класс для методов расширения
    public static class ExtensionMethods
    {
        // Метод расширения для string
        public static string ToTitleCase(this string str)
        {
            if (string.IsNullOrEmpty(str))
                return str;

            string[] words = str.Split(' ');
            for (int i = 0; i < words.Length; i++)
            {
                if (!string.IsNullOrEmpty(words[i]))
                {
                    words[i] = char.ToUpper(words[i][0]) + words[i].Substring(1).ToLower();
                }
            }
            return string.Join(" ", words);
        }

        public static bool IsNullOrEmpty(this string str)
        {
            return string.IsNullOrEmpty(str);
        }

        public static string Repeat(this string str, int count)
        {
            if (count <= 0) return string.Empty;

            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < count; i++)
            {
                sb.Append(str);
            }
            return sb.ToString();
        }

        // Метод расширения для int
        public static bool IsEven(this int number)
        {
            return number % 2 == 0;
        }

        public static bool IsPrime(this int number)
        {
            return MathHelper.IsPrime(number);
        }

        public static int Squared(this int number)
        {
            return number * number;
        }

        // Метод расширения для List<T>
        public static void PrintAll<T>(this List<T> list)
        {
            Console.WriteLine($"Список ({list.Count} элементов):");
            foreach(T item in list)
            {
                Console.WriteLine($"  {item}");
            }
        }

        public static List<T> Shuffle<T>(this List<T> list)
        {
            Random rng = new Random();
            List<T> shuffled = new List<T>(list);

            for (int i = shuffled.Count - 1; i > 0; i--)
            {
                int randomIndex = rng.Next(i + 1);
                T temp = shuffled[i];
                shuffled[i] = shuffled[randomIndex];
                shuffled[randomIndex] = temp;
            }

            return shuffled;
        }

        // Метод расширения для DateTime
        public static string ToReadableString(this DateTime dateTime)
        {
            TimeSpan diff = DateTime.Now - dateTime;

            if (diff.TotalMinutes < 1)
                return "только что";
            if (diff.TotalHours < 1)
                return $"{(int)diff.TotalMinutes} минут назад";
            if (diff.TotalDays < 1)
                return $"{(int)diff.TotalHours} часов назад";
            if (diff.TotalDays < 7)
                return $"{(int)diff.TotalDays} дней назад";

            return dateTime.ToString("dd.MM.yyyy HH:mm");
        }

        public static bool IsWeekend(this DateTime dateTime)
        {
            return dateTime.DayOfWeek == DayOfWeek.Saturday ||
                dateTime.DayOfWeek == DayOfWeek.Sunday;
        }
    }

    class ExtensionMethodsDemo
    {
        public static void Demo()
        {
            Console.WriteLine("\n=== МЕТОДЫ РАСШИРЕНИЯ ===");

            // Работа со строками
            string text = "hello world of programming";
            Console.WriteLine($"Исходная строка: {text}");
            Console.WriteLine($"В Title Case: {text.ToTitleCase()}");
            Console.WriteLine($"Повтор 3 раза: {"abc".Repeat(3)}");
            Console.WriteLine($"Пустая строка: {"".IsNullOrEmpty()}");

            // Работа с числами
            int number = 17;
            Console.WriteLine($"\nЧисло {number}:");
            Console.WriteLine($"  Четное: {number.IsEven()}");
            Console.WriteLine($"  Простое: {number.IsPrime()}");
            Console.WriteLine($"  Квадрат: {number.Squared()}");

            // Работа со списками
            List<string> fruits = new List<string>
            {
                "яблоко", "банан", "апельсин", "виноград", "киви"
            };

            Console.WriteLine("\nИсходный список фруктов:");
            fruits.PrintAll();

            Console.WriteLine("\nПеремешанный список:");
            fruits.Shuffle().PrintAll();

            // Работа с датами
            DateTime pastDate = DateTime.Now.AddHours(-5).AddDays(-3);
            Console.WriteLine($"\nДата {pastDate}:");
            Console.WriteLine($"  В читаемом формате: {pastDate.ToReadableString()}");
            Console.WriteLine($"  Выходной: {pastDate.IsWeekend()}");

            DateTime weekendDate = new DateTime(2024, 1, 6); // Суббота
            Console.WriteLine($"Дата {weekendDate.ToShortDateString()} - выходной: {weekendDate.IsWeekend()}");
        }
    }
}
using System;
using System.Collections.Generic;

namespace OOPDemo
{
    // Интерфейс
    public interface IShape
    {
        double Area();
        double Perimeter();
        void Display();
    }

        // Абстрактный класс
        public abstract class Shape : IShape
    {
        public string Name{ get; set; }
        public string Color{ get; set; }

            protected Shape(string name, string color)
        {
            Name = name;
            Color = color;
        }

        // Абстрактные методы - должны быть реализованы в производных классах
        public abstract double Area();
        public abstract double Perimeter();

        // Виртуальный метод - может быть переопределен
        public virtual void Display()
        {
            Console.WriteLine($"Фигура: {Name}, Цвет: {Color}");
            Console.WriteLine($"  Площадь: {Area():F2}, Периметр: {Perimeter():F2}");
        }

        // Статический метод для создания фигур
        public static Shape CreateShape(string type, params double[] parameters)
        {
            return type.ToLower() switch
            {
                "circle" when parameters.Length >= 1 = > new Circle(parameters[0]),
                    "rectangle" when parameters.Length >= 2 = > new Rectangle(parameters[0], parameters[1]),
                    "triangle" when parameters.Length >= 3 = > new Triangle(parameters[0], parameters[1], parameters[2]),
                    _ = > throw new ArgumentException("Неизвестный тип фигуры или недостаточно параметров")
            };
        }
    }

    // Конкретные классы
    public class Circle : Shape
    {
        public double Radius{ get; set; }

            public Circle(double radius) : base("Круг", "Синий")
        {
            Radius = radius;
        }

        public override double Area()
        {
            return Math.PI * Radius * Radius;
        }

        public override double Perimeter()
        {
            return 2 * Math.PI * Radius;
        }

        public override void Display()
        {
            base.Display();
            Console.WriteLine($"  Радиус: {Radius:F2}");
        }
    }

    public class Rectangle : Shape
    {
        public double Width{ get; set; }
        public double Height{ get; set; }

            public Rectangle(double width, double height) : base("Прямоугольник", "Зеленый")
        {
            Width = width;
            Height = height;
        }

        public override double Area()
        {
            return Width * Height;
        }

        public override double Perimeter()
        {
            return 2 * (Width + Height);
        }

        public override void Display()
        {
            base.Display();
            Console.WriteLine($"  Ширина: {Width:F2}, Высота: {Height:F2}");
        }
    }

    public class Triangle : Shape
    {
        public double SideA{ get; set; }
        public double SideB{ get; set; }
        public double SideC{ get; set; }

            public Triangle(double a, double b, double c) : base("Треугольник", "Красный")
        {
            SideA = a;
            SideB = b;
            SideC = c;
        }

        public override double Area()
        {
            // Формула Герона
            double s = Perimeter() / 2;
            return Math.Sqrt(s * (s - SideA) * (s - SideB) * (s - SideC));
        }

        public override double Perimeter()
        {
            return SideA + SideB + SideC;
        }

        public override void Display()
        {
            base.Display();
            Console.WriteLine($"  Стороны: {SideA:F2}, {SideB:F2}, {SideC:F2}");
        }
    }

    class ComprehensiveDemo
    {
        public static void Demo()
        {
            Console.WriteLine("\n=== КОМПЛЕКСНЫЙ ПРИМЕР ===");

            // Создание фигур через фабричный метод
            List<Shape> shapes = new List<Shape>
            {
                Shape.CreateShape("circle", 5.0),
                Shape.CreateShape("rectangle", 4.0, 6.0),
                Shape.CreateShape("triangle", 3.0, 4.0, 5.0)
            };

            // Использование полиморфизма
            Console.WriteLine("Все фигуры:");
            foreach(Shape shape in shapes)
            {
                shape.Display();
                Console.WriteLine();
            }

            // Использование методов расширения
            Console.WriteLine("Статистика по фигурам:");
            Console.WriteLine($"Общая площадь: {shapes.TotalArea():F2}");
            Console.WriteLine($"Общий периметр: {shapes.TotalPerimeter():F2}");
            Console.WriteLine($"Самая большая площадь: {shapes.FindLargestArea()?.Name ?? "нет фигур"}");
        }
    }

    // Методы расширения для коллекций фигур
    public static class ShapeExtensions
    {
        public static double TotalArea(this IEnumerable<Shape> shapes)
        {
            double total = 0;
            foreach(Shape shape in shapes)
            {
                total += shape.Area();
            }
            return total;
        }

        public static double TotalPerimeter(this IEnumerable<Shape> shapes)
        {
            double total = 0;
            foreach(Shape shape in shapes)
            {
                total += shape.Perimeter();
            }
            return total;
        }

        public static Shape FindLargestArea(this IEnumerable<Shape> shapes)
        {
            Shape largest = null;
            foreach(Shape shape in shapes)
            {
                if (largest == null || shape.Area() > largest.Area())
                {
                    largest = shape;
                }
            }
            return largest;
        }
    }

    // Главный класс программы
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("ДЕМОНСТРАЦИЯ ООП В C#");
            Console.WriteLine("=====================\n");

            BasicClassDemo.Demo();
            InheritanceDemo.Demo();
            StaticVsInstanceDemo.Demo();
            StaticClassDemo.Demo();
            ExtensionMethodsDemo.Demo();
            ComprehensiveDemo.Demo();

            Console.WriteLine("\n=====================");
            Console.WriteLine("Демонстрация завершена!");

            // Ожидание завершения финализаторов
            GC.Collect();
            GC.WaitForPendingFinalizers();

            Console.ReadKey();
        }
    }
}