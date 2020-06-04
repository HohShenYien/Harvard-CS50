def main():
    dollars = get_float()
    # converting into int for easier manipulation
    cents = int(dollars * 100)
    total = 0
    # simplifying further my code
    div = [25, 10, 5, 1]
    for i in div:
        # Getting the quotients
        total += cents//i
        # Getting the remainders
        cents %= i
    print(total)
        
    
def get_float():
    # repeating the while loop until a valid float is obtained
    while True:
        try:
            cent = float(input("Change owed: "))
            # Only taking positive floats
            if cent > 0:
                return cent
        except:
            pass      
        

main()
