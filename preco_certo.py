import random

wheel = [i for i in range(5, 101, 5)]

while True:
    print("Spin? Y/N")
    firstSpin = input()
    if(firstSpin == "Y"):
        firstResult = random.choice(wheel)
        print(firstResult)
        print("Spin again? Y/N")
        secondSpin = input()
        if(secondSpin == "Y"): 
            secondResult = random.choice(wheel)
            print(secondResult)
            total=firstResult+secondResult
            if(total<=100):
                print("Your total is", total, "and you are still in")
                break
            else:
                print("Your total is", total, "and you lose")
                break
        elif(secondSpin == "N"):
            total=firstResult
            if(total<=100):
                print("Your total is", total, "and you are still in")
                break
            else:
                print("Your total is", total, "and you lose")
                break
    elif(firstSpin == "N"):
        break


