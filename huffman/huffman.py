class level:
    def __init__(self, db, chr):
        self.db = db
        self.chr = chr
        self.bal = None
        self.jobb = None
        self.irany = ''

chars = []

print("Adja meg a stringet: ")

stringInput = str(input())

chars = list(stringInput)

charsSorted = []

for x in chars:
    if x in charsSorted:
        continue
    else:
        charsSorted.append(x)

chrdb = []
levelek = []

for x in range(len(chars)):
    chars.sort()

d = {x : chars.count(x) for x in chars}
chrdb = list(d.values())

print(f"Karakterek: {charsSorted}")
print(f"Karakterek gyakorisága: {chrdb}")

for x in range(len(charsSorted)):
    levelek.append(level(chrdb[x], charsSorted[x]))

while len(levelek) != 1:
    levelek = sorted(levelek, key=lambda x: x.db)
    level1 = levelek[0]
    level2 = levelek[1]
    level1.irany = 0
    level2.irany = 1
    ujLevel = level(level1.db+level2.db, '')
    ujLevel.bal = level1
    ujLevel.jobb = level2
    levelek.remove(level1)
    levelek.remove(level2)
    levelek.append(ujLevel)

codetbl = []

def codeTable(level, string = ''):
    printLevel = string + str(level.irany)
    if(level.bal):
        codeTable(level.bal, printLevel)
    if(level.jobb):
        codeTable(level.jobb, printLevel)
    if(not level.bal and not level.jobb):
        codetbl.append(tuple((level.chr, printLevel)))

def codeString(string):
    coded = ""
    for x in string:
        for y in range(len(codetbl)):
            if(x == codetbl[y][0]):
                coded += codetbl[y][1]
    return coded

codeTable(levelek[0])
print(f"Szótár: {codetbl}")
codedString = codeString(stringInput)
print(f"A string kódolva: {codeString(stringInput)}")

def huffmanDecode():
    re = ""
    code = codedString
    while len(code) > 0:
        for x in range (len(codetbl)):
            if(code.startswith(str(codetbl[x][1]))):
                re += str(codetbl[x][0])
                code = code[len(str(codetbl[x][1])):]
    return re

decoded = huffmanDecode()
print(f"A string kódja dekódolva: {decoded}")