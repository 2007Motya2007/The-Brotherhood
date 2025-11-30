print("\n=== ÖÈÊË FOR ===")

# Öèêë for ïî äèàïàçîíó
print("\n1. Öèêë for ïî äèàïàçîíó:")
for i in range(5) :
    print(f"i = {i}")

    # Öèêë for ïî äèàïàçîíó ñ ïàðàìåòðàìè
    print("\n2. Öèêë for ïî äèàïàçîíó ñ ïàðàìåòðàìè:")
    for i in range(2, 8) : # îò 2 äî 7
        print(f"i = {i}")

        print("\n3. Öèêë for ïî äèàïàçîíó ñ øàãîì:")
        for i in range(1, 10, 2) : # îò 1 äî 9 ñ øàãîì 2
            print(f"i = {i}")

            # Öèêë for ïî ñïèñêó
            print("\n4. Öèêë for ïî ñïèñêó:")
            fruits = ["ÿáëîêî", "áàíàí", "àïåëüñèí", "âèíîãðàä"]
            for fruit in fruits :
print(f"Ôðóêò: {fruit}")

# Öèêë for ïî ñòðîêå
print("\n5. Öèêë for ïî ñòðîêå:")
word = "Python"
for letter in word :
print(f"Áóêâà: {letter}")

# Öèêë for ïî ñëîâàðþ
print("\n6. Öèêë for ïî ñëîâàðþ:")
person = { "èìÿ": "Àííà", "âîçðàñò" : 25, "ãîðîä" : "Ìîñêâà" }
for key, value in person.items() :
    print(f"{key}: {value}")
