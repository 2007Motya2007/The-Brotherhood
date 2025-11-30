print("\n=== BREAK И CONTINUE В FOR ===")

# Break в цикле for
print("\n1. Break в цикле for:")
for i in range(10) :
    if i == 5 :
        print("Достигнуто 5, прерываем цикл")
        break
        print(f"i = {i}")

        # Continue в цикле for
        print("\n2. Continue в цикле for:")
        for i in range(10) :
            if i % 2 == 0 : # Пропускаем четные числа
                continue
                print(f"Нечетное число: {i}")

                # Вложенные циклы с break
                print("\n3. Вложенные циклы с break:")
                for i in range(3) :
                    print(f"\nВнешний цикл: i = {i}")
                    for j in range(5) :
                        if j == 2 :
                            print("  Внутренний цикл: достигнуто 2, прерываем внутренний цикл")
                            break
                            print(f"  Внутренний цикл: j = {j}")