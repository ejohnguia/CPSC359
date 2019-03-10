from numpy import zeros

def makeTable(rows, columns):
    table = zeros([rows, columns], dtype = object)
    return table

def addPresent(table):
    #add PRESENT STATES
    rowCounter = 0
    for row in table:
        #001
        if 3 < rowCounter < 8:
            row[2] = 1
        #010
        elif 7 < rowCounter < 12:
            row[1] = 1
        #011
        elif 11 < rowCounter < 16:
            row[1] = 1
            row[2] = 1
        #100
        elif 15 < rowCounter < 20:
            row[0] = 1
        #101
        elif 19 < rowCounter < 24:
            row[0] = 1
            row[2] = 1
        #110
        elif 23 < rowCounter < 28:
            row[0] = 1
            row[1] = 1
        #111
        elif 27 < rowCounter < 32:
            row[0] = 1
            row[1] = 1
            row[2] = 1
        rowCounter += 1

def addInput(table):
    rowCounter = 0
    for row in table:
        #01
        if rowCounter == 1:
            row[4] = 1
        #10
        elif rowCounter == 2:
            row[3] = 1
        #11
        elif rowCounter == 3:
            row[3] = 1
            row[4] = 1
            rowCounter = 0
            continue
        rowCounter += 1

def addNext(table):
    for row in table:
        if row[4] ==  0:
            a = row[0]
            b = row[1]
            c = row[2]
        elif row[3] == 1 and row[4] == 1:
            a,b,c = grayCodePrevState(row[0],row[1],row[2])
        elif row[3] == 0 and row[4] == 1:
            a,b,c = grayCodeNextState(row[0],row[1],row[2])
        row[5] = a
        row[6] = b
        row[7] = c

def addFFValues(table, FF):
    if FF == 'jk':
        for row in table:
            for digit in range (3):
                j, k = JKflipflop(row[digit], row[digit + 5])

                adjust = digit + digit
                row[adjust + 8] = j
                row[adjust + 9] = k
    elif FF == 't':
        for row in table:
            for digit in range (3):
                f1 = Tflipflop(row[digit], row[digit + 5])

                row[digit + 8] = f1
    return table

def convertLaTeX(table):
    for row in table:
        line = ""
        for i in row:
            line += (str(i) + " & ")
        line = line[:-3]
        print (line + '\\\ \hline')

############## Manipulation functions
def getColumns(table):
    column = int(input("Which column do you need? "))
    line = ""
    for row in table:
        line += (str(row[column]) + ", ")
    line = line[:-2]

    line1 = line[:len(line) // 2]
    line1 = line1[:-1]
    line2 = line[len(line) // 2:]
    line2 = line2[1:]
    print("{" + line1 + "}")
    print("{" + line2 + "}")

########## Static Values

def grayCodeNextState(a,b,c):
    if a == 0:
        if b == 0:
            if c == 0:
                return (0, 0, 1)
            elif c == 1:
                return (0, 1, 1)
        elif b == 1:
            if c == 0:
                return (1, 1, 0)
            elif c == 1:
                return (0, 1, 0)
    elif a == 1:
        if b == 0:
            if c == 0:
                return (0, 0, 0)
            elif c == 1:
                return (1, 0, 0)
        elif b == 1:
            if c == 0:
                return (1, 1, 1)
            elif c == 1:
                return (1, 0, 1)

def grayCodePrevState(a,b,c):
    if a == 0:
        if b == 0:
            if c == 0:
                return (1, 0, 0)
            elif c == 1:
                return (0, 0, 0)
        elif b == 1:
            if c == 0:
                return (0, 1, 1)
            elif c == 1:
                return (0, 0, 1)
    elif a == 1:
        if b == 0:
            if c == 0:
                return (1, 0, 1)
            elif c == 1:
                return (1, 1, 1)
        elif b == 1:
            if c == 0:
                return (0, 1, 0)
            elif c == 1:
                return (1, 1, 0)        

def JKflipflop(presentState, nextState):
    if presentState == 0:
        if nextState == 0:
            return (0, 'X')
        elif nextState == 1:
            return (1, 'X')
    elif presentState == 1:
        if nextState == 0:
            return ('X', 1)
        elif nextState == 1:
            return ('X', 0)

def Tflipflop(presentState, nextState):
    if presentState == 0:
        if nextState == 0:
            return (0)
        elif nextState == 1:
            return (1)
    elif presentState == 1:
        if nextState == 0:
            return (1)
        elif nextState == 1:
            return (0)

########## Main Function

def main():
    table = makeTable(32, 11)
    addPresent(table)
    addInput(table)
    addNext(table)
    addFFValues(table, 't')
    # convertLaTeX(table)

############## Manipulate the table
    getColumns(table)

if __name__ == '__main__':
    main()