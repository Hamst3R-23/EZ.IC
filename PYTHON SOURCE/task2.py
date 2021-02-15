tasks = input().split(",")
Jenya = []
Sasha = []

for i in range(len(tasks) // 2):             # Дела Жени
    Jenya.append(tasks[i])

if len(tasks) % 2 == 1:                      # Если дел нечетное кол-во
    Jenya.append(tasks[len(tasks)//2])

for i in range(len(tasks) // 2, len(tasks)): # Дела Саши
    Sasha.append(tasks[i])


print("Саша:", end = '')
for i in range(len(Sasha)):                  # Вывод Саши
    print(Sasha[i], end = ", ")

print()
print("Женя: ", end = '')
for i in range(len(Jenya)):                  # Вывод Жени   
    print(Jenya[i], end = ", ")

