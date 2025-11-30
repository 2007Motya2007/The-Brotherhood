# Ëîãè÷åñêèé òèï äàííûõ(bool)
a = True
b = False
print("a =", a, type(a))  # a = True <class 'bool'>
print("b =", b, type(b))  # b = False <class 'bool'>

# Ñðàâíåíèÿ
x = 5
y = 10
print("\nÑðàâíåíèÿ:")
print("x == y:", x == y)  # False
print("x != y:", x != y)  # True
print("x < y:", x < y)    # True
    print("x >= y:", x >= y)  # False

    # Ëîãè÷åñêèå îïåðàöèè
    p = True
    q = False
    print("\nËîãè÷åñêèå îïåðàöèè:")
    print("p and q:", p and q)  # False(ïîëíàÿ îïåðàöèÿ)
    print("p or q:", p or q)    # True(ïîëíàÿ îïåðàöèÿ)
    print("not p:", not p)      # False

    # Ñîêðàùåííûå îïåðàöèè(short - circuit)
    def check() :
    print("Ôóíêöèÿ âûçâàíà!")
    return True

    print("\nÑîêðàùåííûå îïåðàöèè:")
    result1 = q and check()  # check() íå âûçûâàåòñÿ, òàê êàê q False
    print("Ðåçóëüòàò 1:", result1)

    result2 = p or check()   # check() íå âûçûâàåòñÿ, òàê êàê p True
    print("Ðåçóëüòàò 2:", result2)

    # Êîíñòðóêöèÿ if - else
    print("\nÊîíñòðóêöèÿ if-else:")
    temperature = 25
    if temperature > 30:
print("Æàðêî")
elif temperature > 20:
print("Êîìôîðòíî")  # Ýòîò áëîê âûïîëíèòñÿ
    else:
print("Ïðîõëàäíî")

# Âëîæåííûå óñëîâèÿ ñ ëîãè÷åñêèìè îïåðàòîðàìè
age = 20
has_license = True
print("\nÏðîâåðêà âîæäåíèÿ:")
if age >= 18 and has_license:
print("Ìîæíî âîäèòü ìàøèíó")  # Ýòîò áëîê âûïîëíèòñÿ
else:
print("Íåëüçÿ âîäèòü ìàøèíó")

# Èñïîëüçîâàíèå not
is_rainy = False
if not is_rainy:
print("Çîíò íå íóæåí")  # Ýòîò áëîê âûïîëíèòñÿ
