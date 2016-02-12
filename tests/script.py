import random
names = []
outputString = ""
with open("input.txt", "r", encoding = "utf-8") as fi:
    for line in fi:
        names.append(line)
outputString += "25\n\n"
for i in range(1, 25):
    representatives = random.randint(1,20)
    current = []
    outputString += str(representatives) + "\n"
    for j in range(1, representatives + 1):
        index = random.randint(0, representatives - 1)
        while names[index] in current:
            index = random.randint(0, representatives - 1)
        current.append(names[index])
    for j in range(0, representatives):
        outputString += current[j]
    for j in range(1, random.randint(1, 100)):
        ballot = []
        for k in range(1, representatives + 1):
            num = random.randint(1, representatives)
            while num in ballot:
                num = random.randint(1, representatives)
            ballot.append(num)
            outputString += str(num) + " "
        outputString += "\n"
    outputString += "\n"
print(outputString)

