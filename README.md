# spell_checker
This is a spell checker using edit distance to see if the word is a correct match or to find the nearest word match in the input dictionary file. 

spell_checker.c

Repeatedly read 2 strings from the user.
The strings must be separated by a space.
The program will compute the edit distance between them,
print the cost table, the cost and the alignment.

After that, read 2 file names (one for a dictionary file and
one for a file to be spell-checked); spell-check all the words in the text file
and write the corrected text to an output file.

This file primarity contains main() and handle the printing and calling of funtions form the fuction library


spell.c

It is the function library which contains functions for calculating and implementing editdistance and using it for finding the correct match or closest match of the word in the input dictonary

spell.h

Header file for function Library

Added some test cases along with it
