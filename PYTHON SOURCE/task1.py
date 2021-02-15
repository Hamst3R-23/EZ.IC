names = input().split(" ")                  # Участники
numbers = []

for i in input().split(" "):                # Места
    a = int(i)
    numbers.append(a)

for i in range(len(numbers)):
    if numbers[i] < len(names):
        print(numbers[i],"место занял", names[numbers[i] - 1], end = '\n') # Такой участник на таком месте существует
    else:
        print(numbers[i],"место никто не занял", end = '\n')               # Такого места нет




