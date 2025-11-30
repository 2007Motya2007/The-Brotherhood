print("\n=== ЦИКЛ FOR ===")

# Цикл for по диапазону
print("\n1. Цикл for по диапазону:")
for i in range(5) :
    print(f"i = {i}")

    # Цикл for по диапазону с параметрами
    print("\n2. Цикл for по диапазону с параметрами:")
    for i in range(2, 8) : # от 2 до 7
        print(f"i = {i}")

        print("\n3. Цикл for по диапазону с шагом:")
        for i in range(1, 10, 2) : # от 1 до 9 с шагом 2
            print(f"i = {i}")

            # Цикл for по списку
            print("\n4. Цикл for по списку:")
            fruits = ["яблоко", "банан", "апельсин", "виноград"]
            for fruit in fruits :
print(f"Фрукт: {fruit}")

# Цикл for по строке
print("\n5. Цикл for по строке:")
word = "Python"
for letter in word :
print(f"Буква: {letter}")

# Цикл for по словарю
print("\n6. Цикл for по словарю:")
person = { "имя": "Анна", "возраст" : 25, "город" : "Москва" }
for key, value in person.items() :
    print(f"{key}: {value}")