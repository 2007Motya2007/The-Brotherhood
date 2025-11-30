using System;
using System.Collections.Generic;

class ListDemo
{
    static void Main()
    {
        Console.WriteLine("=== СПИСКИ (List<T>) ===");

        // Создание и инициализация списков
        List<int> numbers = new List<int>{ 1, 2, 3, 4, 5 };
        List<string> names = new List<string>();

        // Добавление элементов
        names.Add("Анна");
        names.Add("Борис");
        names.Add("Виктор");
        names.AddRange(new string[]{ "Дмитрий", "Елена" });

        Console.WriteLine("1. Исходный список имен:");
        foreach(string name in names)
        {
            Console.WriteLine($" - {name}");
        }

        // Доступ к элементам
        Console.WriteLine($"\n2. Первый элемент: {names[0]}");
        Console.WriteLine($"Последний элемент: {names[names.Count - 1]}");

        // Поиск элементов
        int index = names.IndexOf("Виктор");
        bool contains = names.Contains("Анна");
        Console.WriteLine($"Индекс 'Виктор': {index}");
        Console.WriteLine($"Содержит 'Анна': {contains}");

        // Удаление элементов
        names.Remove("Борис");
        names.RemoveAt(0);

        Console.WriteLine("\n3. После удаления элементов:");
        foreach(string name in names)
        {
            Console.WriteLine($" - {name}");
        }

        // Сортировка
        names.Sort();
        Console.WriteLine("\n4. После сортировки:");
        foreach(string name in names)
        {
            Console.WriteLine($" - {name}");
        }

        // Методы списка
        List<int> bigNumbers = numbers.FindAll(n = > n > 2);
        Console.WriteLine("\n5. Числа больше 2:");
        foreach(int num in bigNumbers)
        {
            Console.Write(num + " ");
        }

        // Преобразование в массив
        string[] namesArray = names.ToArray();
        Console.WriteLine($"\n\n6. Массив из списка: {string.Join(", ", namesArray)}");
    }
}
using System;
using System.Collections.Generic;

class DictionaryDemo
{
    static void Main()
    {
        Console.WriteLine("\n=== СЛОВАРИ (Dictionary<TKey, TValue>) ===");

        // Создание словаря
        Dictionary<string, string> countries = new Dictionary<string, string>
        {
            ["RU"] = "Россия",
            ["US"] = "США",
            ["DE"] = "Германия"
        };

        // Добавление элементов
        countries.Add("FR", "Франция");
        countries["CN"] = "Китай";

        Console.WriteLine("1. Содержимое словаря:");
        foreach(KeyValuePair<string, string> pair in countries)
        {
            Console.WriteLine($"  {pair.Key} -> {pair.Value}");
        }

        // Поиск элементов
        Console.WriteLine($"\n2. Поиск элементов:");
        if (countries.TryGetValue("RU", out string country))
        {
            Console.WriteLine($"Найдено: {country}");
        }

        Console.WriteLine($"Содержит ключ 'US': {countries.ContainsKey("US")}");
        Console.WriteLine($"Содержит значение 'Германия': {countries.ContainsValue("Германия")}");

        // Удаление элементов
        countries.Remove("DE");
        Console.WriteLine($"\n3. После удаления Германии:");
        foreach(var pair in countries)
        {
            Console.WriteLine($"  {pair.Key} -> {pair.Value}");
        }

        // Словарь с разными типами
        Dictionary<int, Person> people = new Dictionary<int, Person>
        {
            [1] = new Person("Иван", 25),
            [2] = new Person("Мария", 30),
            [3] = new Person("Петр", 35)
        };

        Console.WriteLine("\n4. Словарь объектов:");
        foreach(var person in people)
        {
            Console.WriteLine($"  ID {person.Key}: {person.Value.Name}, {person.Value.Age} лет");
        }

        // Методы словаря
        Console.WriteLine($"\n5. Количество элементов: {countries.Count}");
        Console.WriteLine($"Ключи: {string.Join(", ", countries.Keys)}");
        Console.WriteLine($"Значения: {string.Join(", ", countries.Values)}");
    }

    class Person
    {
        public string Name{ get; set; }
        public int Age{ get; set; }

            public Person(string name, int age)
        {
            Name = name;
            Age = age;
        }
    }
}
using System;
using System.Text;
using System.Diagnostics;

class StringsDemo
{
    static void Main()
    {
        Console.WriteLine("\n=== НЕИЗМЕНЯЕМОСТЬ СТРОК И STRINGBUILDER ===");

        // Демонстрация неизменяемости строк
        Console.WriteLine("1. НЕИЗМЕНЯЕМОСТЬ СТРОК:");
        string str1 = "Hello";
        string str2 = str1;

        Console.WriteLine($"str1: {str1}");
        Console.WriteLine($"str2: {str2}");
        Console.WriteLine($"str1 == str2: {str1 == str2}");
        Console.WriteLine($"ReferenceEquals: {object.ReferenceEquals(str1, str2)}");

        str1 += " World!"; // Создается новая строка
        Console.WriteLine($"\nПосле изменения str1:");
        Console.WriteLine($"str1: {str1}");
        Console.WriteLine($"str2: {str2}");
        Console.WriteLine($"str1 == str2: {str1 == str2}");
        Console.WriteLine($"ReferenceEquals: {object.ReferenceEquals(str1, str2)}");

        // Сравнение производительности
        Console.WriteLine("\n2. СРАВНЕНИЕ ПРОИЗВОДИТЕЛЬНОСТИ:");
        int iterations = 10000;

        // Медленный способ (создание новых строк)
        Stopwatch sw1 = Stopwatch.StartNew();
        string result1 = "";
        for (int i = 0; i < iterations; i++)
        {
            result1 += i.ToString() + " ";
        }
        sw1.Stop();
        Console.WriteLine($"Конкатенация строк: {sw1.ElapsedMilliseconds} мс");

        // Быстрый способ (StringBuilder)
        Stopwatch sw2 = Stopwatch.StartNew();
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < iterations; i++)
        {
            sb.Append(i).Append(" ");
        }
        string result2 = sb.ToString();
        sw2.Stop();
        Console.WriteLine($"StringBuilder: {sw2.ElapsedMilliseconds} мс");

        // Методы StringBuilder
        Console.WriteLine("\n3. МЕТОДЫ STRINGBUILDER:");
        StringBuilder text = new StringBuilder("Исходный текст");
        text.Append(" + добавленный текст");
        text.Insert(0, "Начало: ");
        text.Replace("текст", "STRING");
        text.Remove(5, 3);

        Console.WriteLine($"Результат: {text}");
        Console.WriteLine($"Длина: {text.Length}");
        Console.WriteLine($"Емкость: {text.Capacity}");

        // Очистка StringBuilder
        text.Clear();
        text.Append("Новый текст");
        Console.WriteLine($"После очистки: {text}");
    }
}
using System;

class FormattingDemo
{
    static void Main()
    {
        Console.WriteLine("\n=== СПЕЦИАЛЬНЫЕ СИМВОЛЫ И ФОРМАТИРОВАНИЕ ===");

        // Специальные символы
        Console.WriteLine("1. СПЕЦИАЛЬНЫЕ СИМВОЛЫ:");
        Console.WriteLine("Обычная строка");
        Console.WriteLine("Строка с \t табуляцией");
        Console.WriteLine("Строка с \n переносом строки");
        Console.WriteLine("Кавычки: \"текст в кавычках\"");
        Console.WriteLine("Обратный слеш: \\");
        Console.WriteLine("Путь: C:\\Users\\Name\\File.txt");

        // Verbatim строки
        Console.WriteLine("\n2. VERBATIM СТРОКИ:");
        Console.WriteLine(@"Это verbatim строка
            с сохранением форматирования
            и без обработки escape - последовательностей
            Путь : C:\Users\Name\File.txt");

            // Интерполяция строк
            string name = "Анна";
        int age = 25;
        double salary = 12345.6789;

        Console.WriteLine("\n3. ИНТЕРПОЛЯЦИЯ СТРОК:");
        Console.WriteLine($"Имя: {name}, Возраст: {age}, Зарплата: {salary:C}");

        // Форматированный вывод
        Console.WriteLine("\n4. ФОРМАТИРОВАННЫЙ ВЫВОД:");
        Console.WriteLine("Числа:");
        Console.WriteLine($"Decimal: {123:D6}");        // 000123
        Console.WriteLine($"Currency: {1234.56:C}");    // ?1 234,56
        Console.WriteLine($"Fixed: {1234.5678:F2}");    // 1234.57
        Console.WriteLine($"Percent: {0.123:P}");       // 12.30%

        Console.WriteLine("\nДаты:");
        DateTime now = DateTime.Now;
        Console.WriteLine($"Short date: {now:d}");
        Console.WriteLine($"Long date: {now:D}");
        Console.WriteLine($"Full date/time: {now:F}");
        Console.WriteLine($"Custom: {now:yyyy-MM-dd HH:mm:ss}");

        // Составное форматирование
        Console.WriteLine("\n5. СОСТАВНОЕ ФОРМАТИРОВАНИЕ:");
        Console.WriteLine("Имя: {0}, Возраст: {1}, Зарплата: {2:C}", name, age, salary);
        Console.WriteLine("Число: {0:N2}, Процент: {1:P0}", 1234.567, 0.85);
    }
}
using System;
using System.IO;
using System.Text;

class FilesAndDirectoriesDemo
{
    static void Main()
    {
        Console.WriteLine("\n=== ФАЙЛЫ И КАТАЛОГИ ===");

        string basePath = @"C:\Temp\Demo";
        string filePath = Path.Combine(basePath, "test.txt");
        string copyPath = Path.Combine(basePath, "test_copy.txt");

        try
        {
            // Создание каталога
            Console.WriteLine("1. РАБОТА С КАТАЛОГАМИ:");
            if (!Directory.Exists(basePath))
            {
                Directory.CreateDirectory(basePath);
                Console.WriteLine($"Создан каталог: {basePath}");
            }

            // Информация о каталоге
            DirectoryInfo dirInfo = new DirectoryInfo(basePath);
            Console.WriteLine($"Каталог: {dirInfo.FullName}");
            Console.WriteLine($"Создан: {dirInfo.CreationTime}");
            Console.WriteLine($"Атрибуты: {dirInfo.Attributes}");

            // Работа с файлами
            Console.WriteLine("\n2. РАБОТА С ФАЙЛАМИ:");

            // Запись в файл
            File.WriteAllText(filePath, "Привет, мир!\nЭто тестовый файл.");
            File.AppendAllText(filePath, "\nДобавленная строка.");

            // Чтение из файла
            string content = File.ReadAllText(filePath);
            Console.WriteLine("Содержимое файла:");
            Console.WriteLine(content);

            // Информация о файле
            FileInfo fileInfo = new FileInfo(filePath);
            Console.WriteLine($"\nИнформация о файле:");
            Console.WriteLine($"Имя: {fileInfo.Name}");
            Console.WriteLine($"Размер: {fileInfo.Length} байт");
            Console.WriteLine($"Расширение: {fileInfo.Extension}");

            // Копирование файла
            File.Copy(filePath, copyPath, true);
            Console.WriteLine($"Файл скопирован: {copyPath}");

            // Поиск файлов
            Console.WriteLine("\n3. ПОИСК ФАЙЛОВ:");
            string[] files = Directory.GetFiles(basePath, "*.txt");
            Console.WriteLine("Текстовые файлы в каталоге:");
            foreach(string file in files)
            {
                Console.WriteLine($" - {Path.GetFileName(file)}");
            }

            // Работа с путями
            Console.WriteLine("\n4. РАБОТА С ПУТЯМИ:");
            Console.WriteLine($"Полный путь: {Path.GetFullPath(filePath)}");
            Console.WriteLine($"Имя файла: {Path.GetFileName(filePath)}");
            Console.WriteLine($"Имя без расширения: {Path.GetFileNameWithoutExtension(filePath)}");
            Console.WriteLine($"Расширение: {Path.GetExtension(filePath)}");
            Console.WriteLine($"Каталог: {Path.GetDirectoryName(filePath)}");

            // Временные файлы
            string tempFile = Path.GetTempFileName();
            File.WriteAllText(tempFile, "Временный файл");
            Console.WriteLine($"\nСоздан временный файл: {tempFile}");

        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка: {ex.Message}");
        }
        finally
        {
            // Очистка (раскомментируйте для удаления созданных файлов)
            /*
            if (Directory.Exists(basePath))
            {
                Directory.Delete(basePath, true);
                Console.WriteLine("\nКаталог удален");
            }
            */
        }
    }
}
using System;
using System.IO;
using System.Text;

class EncodingDemo
{
    static void Main()
    {
        Console.WriteLine("\n=== КОДИРОВКИ ===");

        string text = "Привет, мир! Hello, World! 123 ?";
        string filePath = "encoding_test.txt";

        // Основные кодировки
        Console.WriteLine("1. ОСНОВНЫЕ КОДИРОВКИ:");

        Encoding[] encodings = {
            Encoding.UTF8,
            Encoding.UTF32,
            Encoding.Unicode, // UTF-16
            Encoding.ASCII,
            Encoding.GetEncoding("windows-1251") // Кириллица
        };

        foreach(Encoding encoding in encodings)
        {
            byte[] bytes = encoding.GetBytes(text);
            string decoded = encoding.GetString(bytes);

            Console.WriteLine($"\n{encoding.EncodingName}:");
            Console.WriteLine($"  Размер: {bytes.Length} байт");
            Console.WriteLine($"  Декодировано: {decoded}");
            Console.WriteLine($"  Совпадает с оригиналом: {text == decoded}");
        }

        // Определение кодировки файла
        Console.WriteLine("\n2. ОПРЕДЕЛЕНИЕ КОДИРОВКИ:");

        // Записываем файл в UTF-8 с BOM
        File.WriteAllText(filePath, text, Encoding.UTF8);

        // Читаем файл и определяем кодировку
        byte[] fileBytes = File.ReadAllBytes(filePath);
        Encoding detectedEncoding = DetectEncoding(fileBytes);
        Console.WriteLine($"Определенная кодировка: {detectedEncoding.EncodingName}");

        // Чтение файла в разных кодировках
        Console.WriteLine("\n3. ЧТЕНИЕ В РАЗНЫХ КОДИРОВКАХ:");

        try
        {
            string utf8Text = File.ReadAllText(filePath, Encoding.UTF8);
            Console.WriteLine($"UTF-8: {utf8Text}");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка UTF-8: {ex.Message}");
        }

        try
        {
            string asciiText = File.ReadAllText(filePath, Encoding.ASCII);
            Console.WriteLine($"ASCII: {asciiText}");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка ASCII: {ex.Message}");
        }

        // Конвертация между кодировками
        Console.WriteLine("\n4. КОНВЕРТАЦИЯ КОДИРОВОК:");

        string sourceText = "Русский текст";
        Encoding sourceEncoding = Encoding.GetEncoding("windows-1251");
        Encoding targetEncoding = Encoding.UTF8;

        byte[] sourceBytes = sourceEncoding.GetBytes(sourceText);
        byte[] targetBytes = Encoding.Convert(sourceEncoding, targetEncoding, sourceBytes);
        string convertedText = targetEncoding.GetString(targetBytes);

        Console.WriteLine($"Исходный текст: {sourceText}");
        Console.WriteLine($"После конвертации: {convertedText}");

        // BOM (Byte Order Mark)
        Console.WriteLine("\n5. BOM (BYTE ORDER MARK):");

        byte[] textBytes = Encoding.UTF8.GetBytes(text);
        byte[] textWithBOM = Encoding.UTF8.GetPreamble().Concat(textBytes).ToArray();

        Console.WriteLine($"Без BOM: {textBytes.Length} байт");
        Console.WriteLine($"С BOM: {textWithBOM.Length} байт");

        // Очистка
        if (File.Exists(filePath))
        {
            File.Delete(filePath);
            Console.WriteLine($"\nФайл {filePath} удален");
        }
    }

    static Encoding DetectEncoding(byte[] bytes)
    {
        if (bytes.Length >= 3 && bytes[0] == 0xEF && bytes[1] == 0xBB && bytes[2] == 0xBF)
            return Encoding.UTF8;
        if (bytes.Length >= 2 && bytes[0] == 0xFE && bytes[1] == 0xFF)
            return Encoding.BigEndianUnicode;
        if (bytes.Length >= 2 && bytes[0] == 0xFF && bytes[1] == 0xFE)
            return Encoding.Unicode;
        if (bytes.Length >= 4 && bytes[0] == 0 && bytes[1] == 0 && bytes[2] == 0xFE && bytes[3] == 0xFF)
            return Encoding.UTF32;

        // Попробуем определить по содержимому
        try
        {
            string text = Encoding.UTF8.GetString(bytes);
            if (!ContainsInvalidUTF8(bytes))
                return Encoding.UTF8;
        }
        catch { }

        return Encoding.Default;
    }

    static bool ContainsInvalidUTF8(byte[] bytes)
    {
        try
        {
            Encoding.UTF8.GetString(bytes);
            return false;
        }
        catch
        {
            return true;
        }
    }
}
using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

class ComprehensiveDemo
{
    static void Main()
    {
        Console.WriteLine("=== КОМПЛЕКСНЫЙ ПРИМЕР ===");

        // Работа с данными в памяти
        List<Person> people = new List<Person>
        {
            new Person("Иван", "иван@mail.ru", 25),
            new Person("Мария", "maria@gmail.com", 30),
            new Person("Петр", "petr@yandex.ru", 35)
        };

        // Сохранение в файл с форматированием
        string dataFile = "people_data.txt";
        StringBuilder csvBuilder = new StringBuilder();

        // Заголовок CSV
        csvBuilder.AppendLine("Имя;Email;Возраст");

        // Данные
        foreach(var person in people)
        {
            csvBuilder.AppendLine($"{person.Name};{person.Email};{person.Age}");
        }

        // Сохранение в файл с UTF-8 кодировкой
        File.WriteAllText(dataFile, csvBuilder.ToString(), Encoding.UTF8);
        Console.WriteLine($"Данные сохранены в файл: {dataFile}");

        // Чтение и обработка данных
        Console.WriteLine("\nЧтение данных из файла:");
        string[] lines = File.ReadAllLines(dataFile, Encoding.UTF8);

        Dictionary<string, Person> peopleDict = new Dictionary<string, Person>();

        for (int i = 1; i < lines.Length; i++) // Пропускаем заголовок
        {
            string[] parts = lines[i].Split(';');
            if (parts.Length == 3)
            {
                string name = parts[0];
                string email = parts[1];
                int age = int.Parse(parts[2]);

                peopleDict[email] = new Person(name, email, age);
            }
        }

        // Вывод словаря
        Console.WriteLine("\nДанные из словаря:");
        foreach(var pair in peopleDict)
        {
            Console.WriteLine($"  {pair.Key}: {pair.Value.Name}, {pair.Value.Age} лет");
        }

        // Форматированный отчет
        Console.WriteLine("\nФорматированный отчет:");
        string report = $"""
            ==== = ОТЧЕТ ==== =
            Количество людей : {people.Count}
        Средний возраст : {CalculateAverageAge(people) :F1}
    Старший: { GetOldestPerson(people).Name }
    Младший: { GetYoungestPerson(people).Name }
        ================ =
            """;

            Console.WriteLine(report);

        // Очистка
        File.Delete(dataFile);
        Console.WriteLine($"Файл {dataFile} удален");
    }

    static double CalculateAverageAge(List<Person> people)
    {
        if (people.Count == 0) return 0;
        double sum = 0;
        foreach(var person in people)
        {
            sum += person.Age;
        }
        return sum / people.Count;
    }

    static Person GetOldestPerson(List<Person> people)
    {
        Person oldest = people[0];
        foreach(var person in people)
        {
            if (person.Age > oldest.Age)
                oldest = person;
        }
        return oldest;
    }

    static Person GetYoungestPerson(List<Person> people)
    {
        Person youngest = people[0];
        foreach(var person in people)
        {
            if (person.Age < youngest.Age)
                youngest = person;
        }
        return youngest;
    }
}

class Person
{
    public string Name{ get; set; }
    public string Email{ get; set; }
    public int Age{ get; set; }

        public Person(string name, string email, int age)
    {
        Name = name;
        Email = email;
        Age = age;
    }
}