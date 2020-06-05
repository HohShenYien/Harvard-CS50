def main():
    # Putting in all the return strings into a list
    # so that the function just return an int
    return_type = ["INVALID", "AMEX", "MASTERCARD", "VISA"]
    nums = all_nums(get_nums())
    # Print invalid if failed Luhn algorithm
    if not luhn_check(nums):
        print(return_type[0])
        # Prevent the main function from proceeding to 11th line
        return
    print(return_type[check_card(nums)])
    

# A simple function to convert the numbers into a list
# This enables easier manipulation
def all_nums(n):
    nums = []
    while n > 0:
        nums.append(n % 10)
        n //= 10
    # Inverts the list because the numbers are put into the list
    # in an inverted order
    return nums[::-1]
    

# Repeats until getting a valid number    
def get_nums():
    while True:
        try:
            nums = int(input("Number: "))
            return nums
        except:
            pass

        
# Luhn algorithm implemented here        
def luhn_check(nums):
    # Copied the given list so that it can be changed in place
    my_nums = nums.copy()
    # every 2 numbers from 2nd last is multiplied by 2
    for i in range(-2, -len(nums) - 1, -2):
        my_nums[i] *= 2
    total = 0
    # Summing up the digits of the numbers in the list
    for i in my_nums:
        while i > 0:
            total += i % 10
            i //= 10
    # Checking if last digit of total is 0
    if total % 10 == 0:
        return True
    return False


# Finally, this checks the type of the card
def check_card(nums):
    if len(nums) == 15:
        if nums[0] == 3 and (nums[1] == 4 or nums[1] == 7):
            return 1
            
    elif len(nums) == 13 or len(nums) == 16:
        if nums[0] == 4:
            return 3
        elif len(nums) == 16:
            if nums[0] == 5:
                for i in range(1, 6):
                    if nums[1] == i:
                        return 2
    
    return 0
        

main()

