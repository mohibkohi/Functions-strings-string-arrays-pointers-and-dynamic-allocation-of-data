
/* 
 * File:   mokohi_hw3.c
 * Author: mohibkohi
 *
 * Created on May 8, 2016, 3:56 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// number of words in a typical Unix dictionary file
#define DICT_WORDS 99171

//Largest word
#define LONGEST_WORD 30

// number of replacement suggestions
#define SUGGESTIONS 10

void searchOneChar();
void searchWord();
void searchExtraCharacter();
void searchOneLessCharacter();
void searchMoreThanFive();
void beginningLetters();
void anyCharacter();

/*
 * Mian runs the program.
 * @para argc the number of arguments.
 * @para all the command line arguments.
 */
int main(int argc, char *argv[]) {

    //Command line arguments should be two.
    if ((argc - 1) < 2 || (argc - 1) > 2) {
        printf("Error Wrong number of arguments\n");
        exit(0);
    }

    //declare a array char to store string to be searched
    char findWord[strlen(argv[2]) + 1];
    //string copy the word from command line argument.
    strcpy(findWord, argv[2]);

    //strcat(argv[1], ".txt");

    FILE *fptr;
    fptr = fopen(argv[1], "r");

    // set up a string that will be used to read one word at a time from the dictionary file  
    char word[60];

    // set up a string array for the dictionary, where each row/word will be allocated dynamically based on the actual word length
    char dict[DICT_WORDS][LONGEST_WORD];

    // set up a string array for the top 10 suggestions, where each row/word will be allocated dynamically based on the actual word length
    char suggest[SUGGESTIONS][LONGEST_WORD];

    int index = 0;

    int count = 0;

    // while the reading of a word has been successful 
    while (fscanf(fptr, "%s", word) > 0 && index < DICT_WORDS) {

        // Determine the length of the word, including null character room
        //count = strlen(word) + 1;

        // Copy word into dynamically allocated storage
        //dict[index] = (char*) malloc(count * sizeof (char));
        strcpy(dict[index], word);

        // well, you have the word - start processing by storing it into the dict array - use malloc for each dict row
        // printf("%d %s\n", index, word); //if you want to print, feel free, but it will take a while
        index++;
    }

    int find = 0;

    //fir search to see if the word exists
    searchWord(&findWord, dict, index, &find);

    //printf("
    if (find == -1) {
        //if the word is found.
        printf("%s found\n", findWord);
    } else {
        //keep track of the size of suggest array and call each function.
        if (find < 10) {
            searchOneChar(&findWord, dict, suggest, index, &find);
        }

        if (find < 10) {
            searchExtraCharacter(&findWord, dict, suggest, index, &find);
        }
        if (find < 10) {
            searchOneLessCharacter(&findWord, dict, suggest, index, &find);
        }
        if (find < 10) {
            if (strlen(findWord) > 5) {
                searchMoreThanFive(&findWord, dict, suggest, index, &find);
            }
        }
        if (find < 10) {
            beginningLetters(&findWord, dict, suggest, index, &find);
        }

        if (find < 10) {
            anyCharacter(&findWord, dict, suggest, index, &find);
        }
    }
    
    
    //function should print only 10 or less elements.
    int k;

    if (find > 0) {
        printf("Suggestions:\n");
        if (find > 10) {
            find = 10;
        }

        //print suggest array content
        for (k = 0; k < find; k++) {
            printf("%s\n", suggest[k]);

        }
    }
    fclose(fptr);

    //free memories from suggest
    for (k = 0; k < find; k++) {
        //int x = (int) strlen(suggest[k]);
        //free(suggest[k]);
    }

    //free memories from dictionary.
    for (k = 0; k < index; k++) {
	//int x = (int) strlen(suggest[k]);
        //free(dict[k]);
    }

    return (EXIT_SUCCESS);
}

/**
 * Search and see if the word exists.
 * @param word to search for.
 * @param dict to search the word from.
 * @param index size of the dictionary.
 * @param size the size of suggest.
 * @pre Passes the a word to search from a dictionary with its size
 * as the function is searching its making sure the suggest size doesn't
 * exceed 10.
 * @post Increments the pointer size, if the word is found. 
 */
void searchWord(char *word, char dict[][LONGEST_WORD], int index, int *size) {
    //int result = 0;
    int i;
    for (i = 0; i < index; i++) {
        if (strcmp(word, dict[i]) == 0) {
            //result = 1;
            (*size)--;
            break;
        }
    }
}

/**
 * Search the dictionary for words with the same length as the 
 * word where only one letter substitution anywhere in the word 
 * would create a dictionary word.
 * @param word to search for.
 * @param dict to search the word from.
 * @param index size of the dictionary.
 * @param size the size of suggest.
 * @pre Passes a word to search from a dictionary with its size
 * as the function is searching its making sure the suggest size doesn't
 * exceed 10.
 * @post Adds the found word from dictionary to the suggest array and increments
 * the pointer size array for suggest size. 
 */
void searchOneChar(char *word, char dict[][LONGEST_WORD], char suggest[][LONGEST_WORD], int index, int *add) {
    //int result;
    int wSize, dSize, i, j;
    int count = 0;
    //length of the word to search.
    wSize = strlen(word);

    for (i = 0; i < index; i++) {

        //length of string at each line.
        dSize = strlen(dict[i]);

        //if the two words are the same size.
        if (wSize == dSize) {
            for (j = 0; j < wSize; j++) {
                if (word[j] != dict[i][j]) {
                    count++;
                }
            }
            if (*add < 10) {
                //if there is only one character difference
                if (count <= 1) {
                    // Copy word into dynamically allocated storage
                    //suggest[*add][0] = *(char*) malloc((wSize + 1) * sizeof (char));
                    strcpy(suggest[*add], dict[i]);
                    count = 0;
                    (*add)++;
                }
            }
            count = 0;
        }
    }
}

/**
 * Search all dictionary words that are longer by one letter only from the 
 * passed word and where the passed word constitutes the first letters of the 
 * dictionary word.
 * @param word to search for.
 * @param dict to search the word from.
 * @param index size of the dictionary.
 * @param size the size of suggest.
 * @pre Passes the a word to search from a dictionary with its size
 * as the function is searching its making sure the suggest size doesn't
 * exceed 10.
 * @post Adds the found word from dictionary to the suggest array and increments
 * the pointer size array for suggest size. 
 */
void searchExtraCharacter(char *word, char dict[][LONGEST_WORD], char suggest[][LONGEST_WORD], int index, int *add) {
    int wSize, dSize, i, j;
    int count = 0;
    //length of the word to search.
    wSize = strlen(word);

    for (i = 0; i < index; i++) {

        //length of string at each line.
        dSize = strlen(dict[i]);

        //if dictionary word is only one character longer.
        if ((wSize + 1) == (dSize)) {
            for (j = 0; j < wSize; j++) {
                if (word[j] == dict[i][j]) {
                    count++;
                }
            }
            if (*add < 10) {
                //if word size is the same as number of equal characters
                if (count == wSize) {
                    // Copy word into dynamically allocated storage
                    //suggest[*add][0] = *(char*) malloc((wSize + 1) * sizeof (char));
                    strcpy(suggest[*add], dict[i]);
                    count = 0;
                    (*add)++;
                }
            }
            count = 0;
        }
    }
}

/**
 * Search all dictionary words that are shorter by one letter only from the 
 * passed word and where the dictionary word constitutes the first letters of 
 * the passed word.
 * @param word to search for.
 * @param dict to search the word from.
 * @param index size of the dictionary.
 * @param size the size of suggest.
 * @pre Passes the a word to search from a dictionary with its size
 * as the function is searching its making sure the suggest size doesn't
 * exceed 10.
 * @post Adds the found word from dictionary to the suggest array and increments
 * the pointer size array for suggest size. 
 */
void searchOneLessCharacter(char *word, char dict[][LONGEST_WORD], char suggest[][LONGEST_WORD], int index, int *add) {
    int wSize, dSize, i, j;
    int count = 0;
    //length of the word to search.
    wSize = strlen(word);

    for (i = 0; i < index; i++) {

        //length of string at each line.
        dSize = strlen(dict[i]);

        //if dictionary word is only one character longer.
        if ((wSize - 1) == (dSize)) {            
            for (j = 0; j < wSize; j++) {
                if (word[j] == dict[i][j]) {
                    count++;
                   
                }
            }
            if (*add < 10) {
                 
                //if word size minus one is the same as number of equal characters
                if (count == (wSize - 1)) {
                    // Copy word into dynamically allocated storage
                   // suggest[*add][0] = *(char*) malloc((wSize + 1) * sizeof (char));
                    strcpy(suggest[*add], dict[i]);
                    count = 0;
                    (*add)++;

                }
            }
            count = 0;
        }
    }
}

/**
 * Search if the passed word is longer than 5 characters, all dictionary words 
 * of the same length as the original where two letter substitution anywhere in 
 * the passed word would create a dictionary word.
 * @param word to search for.
 * @param dict to search the word from.
 * @param index size of the dictionary.
 * @param size the size of suggest.
 * @pre Passes the a word to search from a dictionary with its size
 * as the function is searching its making sure the suggest size doesn't
 * exceed 10.
 * @post Adds the found word from dictionary to the suggest array and increments
 * the pointer size array for suggest size. 
 */
void searchMoreThanFive(char *word, char dict[][LONGEST_WORD], char suggest[][LONGEST_WORD], int index, int *add) {
    //int result;
    int wSize, dSize, i, j;
    int count = 0;
    //length of the word to search.
    wSize = strlen(word);
    for (i = 0; i < index; i++) {

        //length of string at each line.
        dSize = strlen(dict[i]);

        for (j = 0; j < wSize; j++) {
            if (word[j] != dict[i][j]) {
                count++;
            }
        }
        if (*add < 10) {
            //if there are two or more characters in the right place.
            if (count == 2 && wSize == dSize) {
                // Copy word into dynamically allocated storage
               // suggest[*add][0] = *(char*) malloc((dSize + 1));
                strcpy(suggest[*add], dict[i]);
                count = 0;
                (*add)++;
            }
        }
        count = 0;
    }
}

/**
 * Search all dictionary words in which the first length-1 letters of the passed
 * word appear in the beginning of the dictionary's word and the passed word
 * length-1 substring constitutes at least 50% of the dictionary's word.
 * @param word to search for.
 * @param dict to search the word from.
 * @param index size of the dictionary.
 * @param size the size of suggest.
 * @pre Passes the a word to search from a dictionary with its size
 * as the function is searching its making sure the suggest size doesn't
 * exceed 10.
 * @post Adds the found word from dictionary to the suggest array and increments
 * the pointer size array for suggest size. 
 */
void beginningLetters(char *word, char dict[][LONGEST_WORD], char suggest[][LONGEST_WORD], int index, int *add) {
    //int result;
    int wSize, dSize, i, j;
    double count = 0;
    //length of the word to search.
    wSize = strlen(word);

    for (i = 0; i < index; i++) {

        //length of string at each line.
        dSize = strlen(dict[i]);
        char temp[dSize];
        memcpy(temp, dict[i], dSize + 1);

        for (j = 0; j < wSize - 1; j++) {

            if (word[j] == temp[j]) {
                count += 1;
            }
        }
        //dictionary contains length - 1 characters and is at least 50%
        if (count / dSize > .5) {
            if (count == (wSize - 1) && dSize > wSize) {
                int k = 0;
                int bol = 0;

                for (k = 0; k < *add; k++) {

                    if (strcmp(temp, suggest[k]) == 0) {
                        bol = 1;
                        break;
                    }
                }
                if (bol == 0 && *add < 10) {
                    // Copy word into dynamically allocated storage
                   // suggest[*add][0] = *(char*) malloc((wSize + 1) * sizeof (char));
                    strcpy(suggest[*add], dict[i]);
                    count = 0;
                    (*add)++;
                }
            }
        }
        count = 0;
    }
}


/**
 * Search all dictionary words in which the first length-1 letters of the 
 * passed word appear anywhere in the dictionary's word and the passed word 
 * length-1 substring constitutes at least 50% of the dictionary's word.
 * @param word to search for.
 * @param dict to search the word from.
 * @param index size of the dictionary.
 * @param size the size of suggest.
 * @pre Passes the a word to search from a dictionary with its size
 * as the function is searching its making sure the suggest size doesn't
 * exceed 10.
 * @post Adds the found word from dictionary to the suggest array and increments
 * the pointer size array for suggest size. 
 */
void anyCharacter(char *word, char dict[][LONGEST_WORD], char suggest[][LONGEST_WORD], int index, int *add) {
    //int result;
    int wSize, dSize, i, j, l, m;
    double count = 0;
    //length of the word to search.

    wSize = strlen(word);
    for (i = 0; i < index; i++) {

        //length of string at each line.
        dSize = strlen(dict[i]);
        char temp[dSize];
        memcpy(temp, dict[i], dSize + 1);

        for (m = 0; m < wSize - 1; m++) {

            for (j = 0; j < dSize; j++) {

                if (word[m] == temp[j]) {
                    for (l = j; l < dSize; l++) {
                        if (word[m] == temp[l] && m != wSize - 1) {
                            count++;
                            m++;
                        } else {
                            j = dSize;
                            break;
                        }

                    }
                }
            }
        }
        if (count / dSize > .5) {
            //dictionary contains length - 1 characters and is at least 50%
            if (count == (wSize - 1) && (count / dSize) > .5) {
                int k = 0;
                int bol = 0;
                
                for (k = 0; k < *add; k++) {
               
                    if (strcmp(temp, suggest[k]) == 0) {
                        bol = 1;
                        break;
                    }
                }
                //if the bol equals 1.
                if (bol == 0 && *add < 10) {
                    // Copy word into dynamically allocated storage
                   // suggest[*add][0] = *(char*) malloc((wSize + 1) * sizeof (char));
                    strcpy(suggest[*add], dict[i]);
                    count = 0;
                    (*add)++;
                }
            }
        }
        count = 0;
    }
}
