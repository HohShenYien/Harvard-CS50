## This folder contains problem set 3
Below I will mention some notable challenges I encounter when solving the problems

1. **plurality.c**
  * This is a rather easy problem, which I believe can be further optimised using hashmap.
    However,since it wasn't taught and I do not know the syntax in c, I will use the linear
    search method to obtain the candidate's name.
  * The outline of the code is given by CS50 team.

2. **runoff.c**
 * Again, the outline of the code is given by CS50 team, so I just have to fill in the 
   blank functions.
 * The algorithm seems complex at first, however as I read through it wasn't as complex
   as I thought. So overall this is a rather moderate problem.
 * I made some mistakes of neglecting if the candidate is eliminated in is_tie function
   and in find_min function, I was able to solve it by wrapping the codes within an if block.
 * In find_min function, I mistakenly set min to 0 and compare all the votes with 0, thus
   making a mistake in it. I was able to solve it by initializing min into voter_count so as to
   get the maximum number to be compared to.

3. **tideman.c**
  * Wow this problem is really tough. Without my prior experience, I couldn't guarantee my pass on
    all of the tests. This problem tests on graphs, recursive function and sorting algorithm.
  * My main problems are detecting if there's any cycle as well as finding all of the winners
  * Firstly, the detection of cycle. I've got no idea how complex the graph will got as it is 
    behind the scene. Thus, I created a single way detection algorithm which failed. So I suspected
    that there will be multiple paths that somehow one of it will cycle. This forces me to create a
    recursive function to loop through the paths repetitively.(Initially I thought that the runtime complexity
    will be too high for this recursive funtion(also known as depth first search) but fortunately a maximum
    of 9 candidates limit the complexity of the graph.
  * Secondly the winner part. In the instruction, it assumes there's only one root, however, I followed and
    could not pass the last test. Through googling, I realized that others have faced this issue as well and the
    solution was finding all the winners. Thus, I created another recursive function to search for all the sources.
  * Overall, without a good grasp on recursive function and sorting algorithm, as well as some proficiency in coding
    graphs, this problem would be very difficult.
  * PS: I used selection sort for sorting the pairs because seems difficult to code mergesort in C as C cannot return
        array in function(I have only learnt about C in this course. Luckily, C was rather similar to java in some sense)
        quicksort seems to require yet another recursive function, so I decided to just code the easy selection sort.
