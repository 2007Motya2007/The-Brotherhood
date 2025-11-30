using System;

class Program
{
    static void Main()
    {
        Console.WriteLine("=== ОДНОМЕРНЫЕ МАССИВЫ И FOREACH ===");

        // Способы создания массивов
        int[] numbers1 = new int[5]; // Массив из 5 элементов
        int[] numbers2 = new int[] { 1, 2, 3, 4, 5 };
        int[] numbers3 = { 10, 20, 30, 40, 50 };

        // Инициализация массива
        for (int i = 0; i < numbers1.Length; i++)
        {
            numbers1[i] = (i + 1) * 10;
        }

        // Цикл foreach для перебора массива
        Console.WriteLine("\n1. Цикл foreach по numbers1:");
        foreach(int number in numbers1)
        {
            Console.Write(number + " ");
        }

        Console.WriteLine("\n\n2. Цикл foreach по numbers2:");
        foreach(int num in numbers2)
        {
            Console.Write(num + " ");
        }

        // Методы массива
        Console.WriteLine("\n\n3. Методы массива:");
        Array.Sort(numbers3);
        Array.Reverse(numbers3);

        Console.WriteLine("После сортировки и реверса:");
        foreach(int num in numbers3)
        {
            Console.Write(num + " ");
        }

        // Поиск в массиве
        int index = Array.IndexOf(numbers2, 3);
        Console.WriteLine($"\n\nИндекс элемента '3' в numbers2: {index}");

        // Копирование массивов
        int[] copiedArray = new int[numbers2.Length];
        Array.Copy(numbers2, copiedArray, numbers2.Length);

        Console.WriteLine("Скопированный массив:");
        foreach(int num in copiedArray)
        {
            Console.Write(num + " ");
        }
    }
}
using System;

// Ссылочный тип (class)
class Person
{
    public string Name{ get; set; }
    public int Age{ get; set; }

        public Person(string name, int age)
    {
        Name = name;
        Age = age;
    }

    public void Display()
    {
        Console.WriteLine($"Name: {Name}, Age: {Age}");
    }
}

// Тип-значение (struct)
struct Point
{
    public int X{ get; set; }
    public int Y{ get; set; }

        public Point(int x, int y)
    {
        X = x;
        Y = y;
    }

    public void Display()
    {
        Console.WriteLine($"Point: ({X}, {Y})");
    }
}

class ValueVsReferenceDemo
{
    static void Main()
    {
        Console.WriteLine("\n=== ТИПЫ-ЗНАЧЕНИЯ VS ССЫЛОЧНЫЕ ТИПЫ ===");

        // Типы-значения (хранятся в стеке)
        Console.WriteLine("\n1. ТИПЫ-ЗНАЧЕНИЯ (struct):");
        Point p1 = new Point(10, 20);
        Point p2 = p1; // Копирование значения

        p2.X = 100;
        Console.WriteLine("После изменения копии:");
        p1.Display(); // (10, 20) - оригинал не изменился
        p2.Display(); // (100, 20) - изменилась копия

        // Ссылочные типы (хранятся в куче)
        Console.WriteLine("\n2. ССЫЛОЧНЫЕ ТИПЫ (class):");
        Person person1 = new Person("Alice", 25);
        Person person2 = person1; // Копирование ссылки

        person2.Name = "Bob";
        Console.WriteLine("После изменения через ссылку:");
        person1.Display(); // Name: Bob, Age: 25 - изменился оригинал!
        person2.Display(); // Name: Bob, Age: 25

        // Сравнение
        Console.WriteLine("\n3. СРАВНЕНИЕ:");
        Point pointA = new Point(5, 5);
        Point pointB = new Point(5, 5);
        Console.WriteLine($"pointA == pointB: {pointA.Equals(pointB)}"); // True

        Person personA = new Person("John", 30);
        Person personB = new Person("John", 30);
        Console.WriteLine($"personA == personB: {personA.Equals(personB)}"); // False
        Console.WriteLine($"personA ссылка == personB ссылка: {object.ReferenceEquals(personA, personB)}"); // False

        // Null значения
        Console.WriteLine("\n4. NULL ЗНАЧЕНИЯ:");
        Person nullPerson = null; // Ссылочный тип может быть null
        // Point nullPoint = null; // ОШИБКА! Тип-значение не может быть null

        Point ? nullablePoint = null; // Nullable тип-значение
        Console.WriteLine($"nullablePoint: {nullablePoint}");
    }
}
using System;

class MultiDimensionalArrays
{
    static void Main()
    {
        Console.WriteLine("\n=== МНОГОМЕРНЫЕ МАССИВЫ ===");

        // Двумерный массив (матрица)
        Console.WriteLine("\n1. ДВУМЕРНЫЙ МАССИВ:");
        int[, ] matrix = new int[3, 4]
            {
                { 1, 2, 3, 4 },
                { 5, 6, 7, 8 },
                { 9, 10, 11, 12 }
            };

        // Перебор двумерного массива
        Console.WriteLine("Матрица 3x4:");
        for (int i = 0; i < matrix.GetLength(0); i++) // Строки
        {
            for (int j = 0; j < matrix.GetLength(1); j++) // Столбцы
            {
                Console.Write(matrix[i, j] + "\t");
            }
            Console.WriteLine();
        }

        // Трехмерный массив
        Console.WriteLine("\n2. ТРЕХМЕРНЫЙ МАССИВ:");
        int[, , ] cube = new int[2, 2, 3]
            {
                {
                    { 1, 2, 3 },
                    { 4, 5, 6 }
                },
            {
                {7, 8, 9},
                {10, 11, 12}
            }
            };

        // Перебор трехмерного массива
        for (int i = 0; i < cube.GetLength(0); i++)
        {
            Console.WriteLine($"Слой {i}:");
            for (int j = 0; j < cube.GetLength(1); j++)
            {
                for (int k = 0; k < cube.GetLength(2); k++)
                {
                    Console.Write(cube[i, j, k] + "\t");
                }
                Console.WriteLine();
            }
            Console.WriteLine();
        }

        // Инициализация без указания размеров
        int[, ] autoMatrix =
        {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        };

        Console.WriteLine("Автоматическая инициализация:");
        foreach(int element in autoMatrix)
        {
            Console.Write(element + " ");
        }
    }
}
using System;

class JaggedArrays
{
    static void Main()
    {
        Console.WriteLine("\n=== МАССИВЫ МАССИВОВ (ЗУБЧАТЫЕ) ===");

        // Создание зубчатого массива
        int[][] jaggedArray = new int[3][];

        // Инициализация подмассивов разной длины
        jaggedArray[0] = new int[] { 1, 2, 3 };
        jaggedArray[1] = new int[] { 4, 5 };
        jaggedArray[2] = new int[] { 6, 7, 8, 9 };

        // Перебор зубчатого массива
        Console.WriteLine("Зубчатый массив:");
        for (int i = 0; i < jaggedArray.Length; i++)
        {
            Console.Write($"Строка {i}: ");
            for (int j = 0; j < jaggedArray[i].Length; j++)
            {
                Console.Write(jaggedArray[i][j] + " ");
            }
            Console.WriteLine();
        }

        // Использование foreach
        Console.WriteLine("\nИспользование foreach:");
        foreach(int[] subArray in jaggedArray)
        {
            foreach(int element in subArray)
            {
                Console.Write(element + " ");
            }
            Console.WriteLine();
        }

        // Сравнение с многомерным массивом
        Console.WriteLine("\n3. СРАВНЕНИЕ С МНОГОМЕРНЫМ МАССИВОМ:");
        int[, ] rectangular = new int[3, 3]; // Все строки одинаковой длины
        int[][] jagged = new int[3][];      // Строки могут быть разной длины

        jagged[0] = new int[5];
        jagged[1] = new int[3];
        jagged[2] = new int[7];

        Console.WriteLine($"Многомерный массив: {rectangular.Length} элементов"); // 9
        Console.WriteLine($"Зубчатый массив: {jagged.Length} строк"); // 3
    }
}
using System;

class GarbageCollectorDemo
{
    class LargeObject
    {
        private byte[] data = new byte[1000000]; // 1MB
        public string Name{ get; set; }

            ~LargeObject() // Финализатор
        {
            Console.WriteLine($"Финализатор вызван для {Name}");
        }
    }

    static void DemonstrateGC()
    {
        Console.WriteLine("\n=== СБОРЩИК МУСОРА ===");

        // Создаем объекты
        Console.WriteLine("1. СОЗДАНИЕ ОБЪЕКТОВ:");
        for (int i = 0; i < 5; i++)
        {
            LargeObject obj = new LargeObject{ Name = $"Object_{i}" };
            Console.WriteLine($"Создан {obj.Name}");
        }

        // Принудительный вызов сборщика мусора
        Console.WriteLine("\n2. ВЫЗОВ GC.COLLECT():");
        Console.WriteLine($"Память до GC: {GC.GetTotalMemory(false)} байт");

        GC.Collect(); // Принудительная сборка мусора
        GC.WaitForPendingFinalizers(); // Ожидаем завершения финализаторов

        Console.WriteLine($"Память после GC: {GC.GetTotalMemory(true)} байт");

        // Мониторинг поколений объектов
        Console.WriteLine("\n3. ПОКОЛЕНИЯ ОБЪЕКТОВ:");
        LargeObject longLiveObject = new LargeObject{ Name = "LongLiveObject" };

        Console.WriteLine($"Поколение объекта: {GC.GetGeneration(longLiveObject)}");

        GC.Collect();
        Console.WriteLine($"Поколение после GC: {GC.GetGeneration(longLiveObject)}");

        // Использование using для автоматической очистки
        Console.WriteLine("\n4. USING ДЛЯ АВТОМАТИЧЕСКОЙ ОЧИСТКИ:");
        using (var resource = new DisposableResource())
        {
            resource.DoSomething();
        } // Dispose() вызывается автоматически

        // WeakReference - слабая ссылка
        Console.WriteLine("\n5. WEAKREFERENCE:");
        WeakReference weakRef = new WeakReference(new LargeObject{ Name = "WeakObject" });

        Console.WriteLine($"Слабая ссылка активна: {weakRef.IsAlive}");

        GC.Collect();
        GC.WaitForPendingFinalizers();

        Console.WriteLine($"Слабая ссылка активна после GC: {weakRef.IsAlive}");
    }

    class DisposableResource : IDisposable
    {
        public void DoSomething()
        {
            Console.WriteLine("Работа с ресурсом...");
        }

        public void Dispose()
        {
            Console.WriteLine("Ресурс освобожден!");
        }
    }

    static void Main()
    {
        DemonstrateGC();

        // Демонстрация всех концепций вместе
        Console.WriteLine("\n=== КОМПЛЕКСНЫЙ ПРИМЕР ===");

        // Массив ссылочных типов
        Person[] people = new Person[3]
        {
            new Person("Anna", 25),
            new Person("Bob", 30),
            new Person("Charlie", 35)
        };

        Console.WriteLine("Массив людей:");
        foreach(Person person in people)
        {
            person.Display();
        }

        // Зубчатый массив с типами-значениями
        Point[][] pointsGrid = new Point[2][]
        {
            new Point[] { new Point(1, 1), new Point(1, 2) },
            new Point[] { new Point(2, 1), new Point(2, 2), new Point(2, 3) }
        };

        Console.WriteLine("\nСетка точек:");
        foreach(Point[] row in pointsGrid)
        {
            foreach(Point point in row)
            {
                point.Display();
            }
        }
    }
}