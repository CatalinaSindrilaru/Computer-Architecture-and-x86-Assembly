_NAME: Sindrilaru Catalina-Maria_

_GROUP: 312CA_
***
# Homework 2 - ACS Cat Invasion

## Task 1 - Simple cipher
***
To find the encrypted string, I added the given number to each character in
the plain string. For that, I used a label `while_loop`. At each step, I 
retained the current character from plain string and I added the given number
stored in edx register. Then I verified if the new character (the ascii code)
is is still in alphabet or not. If it is not, I decreses the character by 26.
At the final of the label, I put the character in the enc_string (stored in
edi register), and then increase both the esi and edi register (to move to the
next character). I repetead that until I reached the end of the plain string.

## Task 2 - Points
***
### Points distance

To calculate the distance between two points I checked which of the two 
coordinates are different and I make the difference between them, considering
that the other coordinates are identical. For that I initially saved in dx
register the coordinate x for the first point and then in cx register the 
coordinate x for the second point. If these two coordinated are different,
I  decreased from the higher value the lower value and put the result in the
eax register. If the x coordinated for the points are not different, I made
same calculation for y coordinates and then stored the difference in eax register.

### Road

I calculated the distance between two points similar to the previous exercise.
I kept in esi at which points from vector I was. After I calculated the distance
between two consecutive points, I stored the distance on the esi position in
vector of distances (stored in ebx register). I took into account that if two
points  coincide, the distance between them is 0.

### Is square

I checked if the numbers in the distance vector are perfect squares, and if so
I put 1, otherwise I put 0 in the sq vector. I retained in edx the current value
from the vector of distances (I started from the final). I calculated all the
perfect square to my number and if it is not equal to any, I considered it is not
a perfect square. If it is equal to a perfect square, I put 1 in sq vector. I made
this untill the end of the vector of distances.

## Task 3 - Beaufort Encryption
***
To find the encrypted string, I retained the current letter from the key (ascii code)
in al register and decreased it by the current letter from the plain string. If the
result is a negative one, I added 26 to readuce the value between 0 and 26 (in alphabet).
I added 65 (code ascii for 'A') and then I stored this value in the encrypted string.
I increments both ebx and esi (I passed to the next character in the plain string and
also in the encrypted string). An important step was when I need to start over the key
string and I did this by retaining in edi register at what letter I was and if I reached
the last letter, I made the edi 0 to start over the string.

# Task 4 - Spiral Encryption
***
In order to encrypt the desired string, it was necessary to pars in spiral a matrix,
and add each element to the character in the appropriate position to result
in the encrypted string. At the begining, I copied plain string into the encrypted
string. I created the label `matrix` which will be repeated as long as there are
non-traversed elements in the matrix.  I approached the problem in the classic mode,
going through the matrix in the following way: top line, left column, bottom line,
right column. I repeated the algorithm, modifying the start and end indexes for rows
and columns, as appropriate. I took an element from the matrix in the following way:
if I need the key[i][j] and the key is saved in ecx register, I accessed the item
like this [ecx + (i * n + j) * 4], where also i, n, j are stored in some registers 
(4 is because tis a matrix of ints). After I reached to one element, I added it to 
the encrypted string (which initially contained the plain string).