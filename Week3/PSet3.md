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
