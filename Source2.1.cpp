print("=== ЦИКЛ WHILE ===")

# Базовый цикл while
counter = 1
print("\n1. Базовый цикл while:")
while counter <= 5:
print(f"Счетчик: {counter}")
counter += 1

# Цикл while с условием
print("\n2. Цикл while с условием:")
number = 10
while number > 0:
print(f"Число: {number}")
number -= 2

# Бесконечный цикл с break
print("\n3. Цикл while с break:")
count = 0
while True:  # Бесконечный цикл
count += 1
print(f"Итерация: {count}")
if count >= 3:
print("Достигнут предел, выходим из цикла")
break

# Цикл while с continue
print("\n4. Цикл while с continue:")
num = 0
while num < 10:
num += 1
if num % 2 == 0 : # Пропускаем четные числа
continue
print(f"Нечетное число: {num}")

# Цикл while с else
print("\n5. Цикл while с else:")
attempt = 0
while attempt < 3:
print(f"Попытка {attempt + 1}")
attempt += 1
else:
print("Цикл завершен нормально")