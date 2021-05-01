# speller-
Speller is a C program that traverses through a text file (dictionary is taken as input in this program) and finds wrongly spelled words and corrects them using another file. 

sub files used in this program are :
    Dctionary.c: c program to open and traverse through a text file. also calls the speller function.
    Dictionary.h: headers for Dictionary.c
    Speller.c: creates a node, loads a file and calculates the words and time to find it and unloads the text file.
