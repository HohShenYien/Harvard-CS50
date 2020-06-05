def main():
    strings = input("Text: ")
    # initialising the values 
    words = 1
    letters = 0
    sentences = 0
    # Checking every characters
    for i in strings:
        if i == " ":
            words += 1
        elif i == "." or i == "!" or i == "?":
            sentences += 1
        elif i.isalpha():
            letters += 1
    # Calculating the averages
    L = letters / words * 100
    S = sentences / words * 100
    index = 0.0588 * L - 0.296 * S - 15.8
    # Round the floats
    level = round(index)
    if level < 1:
        print("Before Grade 1")
    elif level > 16:
        print("Grade 16+")
    else:
        print(f"Grade {level}")


main()
