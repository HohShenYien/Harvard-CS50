## This folder contains problem set 2
Below I will mention some notable challenges I encounter when solving the problems

1. **readability.c**
* This problem was rather interesting and gives me some insights on difficulty level for reading. 
* The problem itself isn't too difficult, it's the uses of each of the details on problems (such as numbers of
  '.', '?' and '!' indicate number of sentences)
  
2. **caesar.c**
* I've actually done my own version of caesar cipher in Python. However, I did not use any command-line argument previously.
  So I have encountered the problem of segmentation fault in the problem at first. With some googling, I managed to find the error,
  which is to add the following code at the start, the other parts were fine for me.
  
```
  if (argc == 2)
```
