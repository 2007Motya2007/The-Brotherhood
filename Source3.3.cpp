print("\n=== BREAK È CONTINUE Â FOR ===")

# Break â öèêëå for
print("\n1. Break â öèêëå for:")
for i in range(10) :
    if i == 5 :
        print("Äîñòèãíóòî 5, ïðåðûâàåì öèêë")
        break
        print(f"i = {i}")

        # Continue â öèêëå for
        print("\n2. Continue â öèêëå for:")
        for i in range(10) :
            if i % 2 == 0 : # Ïðîïóñêàåì ÷åòíûå ÷èñëà
                continue
                print(f"Íå÷åòíîå ÷èñëî: {i}")

                # Âëîæåííûå öèêëû ñ break
                print("\n3. Âëîæåííûå öèêëû ñ break:")
                for i in range(3) :
                    print(f"\nÂíåøíèé öèêë: i = {i}")
                    for j in range(5) :
                        if j == 2 :
                            print("  Âíóòðåííèé öèêë: äîñòèãíóòî 2, ïðåðûâàåì âíóòðåííèé öèêë")
                            break
                            print(f"  Âíóòðåííèé öèêë: j = {j}")
