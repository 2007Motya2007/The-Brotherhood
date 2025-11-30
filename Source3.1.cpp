print("=== ÖÈÊË WHILE ===")

# Áàçîâûé öèêë while
counter = 1
print("\n1. Áàçîâûé öèêë while:")
while counter <= 5:
print(f"Ñ÷åò÷èê: {counter}")
counter += 1

# Öèêë while ñ óñëîâèåì
print("\n2. Öèêë while ñ óñëîâèåì:")
number = 10
while number > 0:
print(f"×èñëî: {number}")
number -= 2

# Áåñêîíå÷íûé öèêë ñ break
print("\n3. Öèêë while ñ break:")
count = 0
while True:  # Áåñêîíå÷íûé öèêë
count += 1
print(f"Èòåðàöèÿ: {count}")
if count >= 3:
print("Äîñòèãíóò ïðåäåë, âûõîäèì èç öèêëà")
break

# Öèêë while ñ continue
print("\n4. Öèêë while ñ continue:")
num = 0
while num < 10:
num += 1
if num % 2 == 0 : # Ïðîïóñêàåì ÷åòíûå ÷èñëà
continue
print(f"Íå÷åòíîå ÷èñëî: {num}")

# Öèêë while ñ else
print("\n5. Öèêë while ñ else:")
attempt = 0
while attempt < 3:
print(f"Ïîïûòêà {attempt + 1}")
attempt += 1
else:

print("Öèêë çàâåðøåí íîðìàëüíî")
