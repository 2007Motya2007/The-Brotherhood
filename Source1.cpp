# Логический тип данных(bool)
a = True
b = False
print("a =", a, type(a))  # a = True <class 'bool'>
print("b =", b, type(b))  # b = False <class 'bool'>

# Сравнения
x = 5
y = 10
print("\nСравнения:")
print("x == y:", x == y)  # False
print("x != y:", x != y)  # True
print("x < y:", x < y)    # True
    print("x >= y:", x >= y)  # False

    # Логические операции
    p = True
    q = False
    print("\nЛогические операции:")
    print("p and q:", p and q)  # False(полная операция)
    print("p or q:", p or q)    # True(полная операция)
    print("not p:", not p)      # False

    # Сокращенные операции(short - circuit)
    def check() :
    print("Функция вызвана!")
    return True

    print("\nСокращенные операции:")
    result1 = q and check()  # check() не вызывается, так как q False
    print("Результат 1:", result1)

    result2 = p or check()   # check() не вызывается, так как p True
    print("Результат 2:", result2)

    # Конструкция if - else
    print("\nКонструкция if-else:")
    temperature = 25
    if temperature > 30:
print("Жарко")
elif temperature > 20:
print("Комфортно")  # Этот блок выполнится
    else:
print("Прохладно")

# Вложенные условия с логическими операторами
age = 20
has_license = True
print("\nПроверка вождения:")
if age >= 18 and has_license:
print("Можно водить машину")  # Этот блок выполнится
else:
print("Нельзя водить машину")

# Использование not
is_rainy = False
if not is_rainy:
print("Зонт не нужен")  # Этот блок выполнится