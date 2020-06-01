## This folder contains problem set 4
Below I will mention some notable challenges I encounter when solving the problems

1. **filter_less_helper.c**
  * This is an interesting problems. Most notably the part where I need to consider all 3 RGB values.
  * The formula is clear for every of the functions. The main problem is regarding rounding issues. So I searched a while 
    to realise that using either float or double to contain the values instead of int as the int data type will round down 
    everytime before I manage to use the round() function.

2. **filter_more_helper.c**
  * I think quite a lot of the functions needed here can be obtained from filter_less_helper.c, so I just copy and paste.
  * The last part was about finding edges. The algorithm is clear and amaze me! It's simple but effective. So for this problem 
    I mainly used a 3d array (or somewhat similar to a matrix) to contain the data. The many for loops just make it a bit messy 
    for me.
    
3. **recover.c**
  * This is a challenging problem in terms of understanding the newly introduces functions and handling memory problems.
    Initially, I made an error by referring to an address instead of the value which gave me a segmentation fault, with some
    searching, I made a correction and solved it.
