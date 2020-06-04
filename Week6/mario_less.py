def main():
    num = get_int()  # Getting the input
    for x in list("#" * i for i in range(1, num + 1)):
        # rjust makes sure the string is width num else it shifts the whole string to the right
        print(x.rjust(num)) 
    
    
def get_int():
    temp = True
    # Repeat until the input is valid integer and between 1 and 8 inclusive
    while temp:
        try:
            # try will run the function and stop if it fails
            num = int(input("Height: "))
            # If within the range
            if not (num < 1 or num > 8):
                temp = False
        except:
            # Rerun the while loop if not and integer
            pass
    return num
            

main()
