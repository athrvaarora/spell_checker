#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "spell.h"

/*  Suggestions
- When you work with 2D arrays, be careful. Either manage the memory yourself,
or work with local 2D arrays. Note C99 allows parameters as array sizes as long
as they are declared before the array in the parameter list. See:
https://www.geeksforgeeks.org/pass-2d-array-parameter-c/

Worst case time complexity to compute the edit distance from T test words
 to D dictionary words where all words have length MAX_LEN:
Student answer:  Theta((MAX_LEN)^2) or theta(T*D*(MAX_LEN)^2)


Worst case to do an unsuccessful binary search in a dictionary with D words,
when all dictionary words and the searched word have length MAX_LEN Student
answer:  Theta(log_2(D)*MAX_LEN)
*/

/* You can write helper functions here */

/*
Parameters:
first_string - pointer to the first string (displayed vertical in the table)
second_string - pointer to the second string (displayed horizontal in the table)
print_table - If 1, the table with the calculations for the edit distance will
be printed. If 0 (or any value other than 1)it will not print the table (See
sample run) Return:  the value of the edit distance (e.g. 3)
*/
// void printtable(int **table, char *first_string, char *second_string) {}
int min(int a, int b)
{
	return (a > b) ? b : a;
}
void printable(int **table, char *first_string, char *second_string)
{
	int len1 = strlen(first_string);
	int len2 = strlen(second_string);
	printf("   |   |");
	for (int i = 0; i < len2; i++)
	{
		printf("%3c|", second_string[i]);
	}
	printf("\n");
	for (int a = 0; a <= 4 * (len2 + 2) - 1; a++)
	{
		printf("-");
	}

	printf("\n   |");
	for (int b = 0; b <= len2; b++)
	{
		printf("%3d|", table[0][b]);
	}
	printf("\n");
	for (int a = 0; a <= 4 * (len2 + 2) - 1; a++)
	{
		printf("-");
	}
	printf("\n");
	for (int k = 0, f = 1; k <= len1, f <= len1; k++, f++)
	{
		for (int j = 0; j <= len2; j++)
		{
			if (j == 0)
			{
				printf("%3c|", first_string[k]);
			}
			printf("%3d|", table[f][j]);
		}
		printf("\n");
		for (int a = 0; a <= 4 * (len2 + 2) - 1; a++)
		{
			printf("-");
		}
		printf("\n");
	}
	printf("\n");
}
int edit_distance(char *first_string, char *second_string,int print_table)
{ 
	int length_1 = strlen(first_string);
	int length_2 = strlen(second_string);
	int arr1[length_1 + 1][length_2 + 1];
	int i, j;
	int **table;
	int return_value;
	if (length_1 == 0)
	{
		return length_2;
	}
	if (length_2 == 0)
	{
		return length_1;
	}
	table = (int **)malloc(sizeof(int *) * (length_1 + 1));
	for (i = 0; i <= length_1; i++)
	{
		table[i] = malloc(sizeof(int) * (length_2 + 1));
	}
	for (i = 0; i <= length_1; i++)
	{

		for (j = 0; j <= length_2; j++)
		{

			if (i == 0)
			{
				table[i][j] = j;
			}
			else if (j == 0)
			{
				table[i][j] = i;
			}
			else if (first_string[i - 1] == second_string[j - 1])
			{
				table[i][j] = table[i - 1][j - 1];
			}
			else
			{
				table[i][j] = 1 + min(table[i][j - 1], min(table[i - 1][j], table[i - 1][j - 1]));
			}
		}
	}
	return_value = table[length_1][length_2];
	if (print_table == 1)
	{
		printable(table, first_string, second_string);
	}
	for (i = 0; i < length_1 + 1; i++)
	{
		free(table[i]);
	}
	free(table);
	return return_value;
}

/*
Parameters:
testname - string containing the name of the file with the paragraph to spell
check, includes .txt e.g. "text1.txt" dictname - name of file with dictionary
words. Includes .txt, e.g. "dsmall.txt" printOn - If 1 it will print EXTRA
debugging/tracing information (in addition to what it prints when 0):
dictionary as read from the file dictionary AFTER sorting in lexicographical
order for every word searched in the dictionary using BINARY SEARCH shows all
the "probe" words and their indices indices See sample run. If 0 (or anything
other than 1) does not print the above information, but still prints the
number of probes. See sample run.
*/

int comparestr(const void *a, const void *b)
{
	const char *aa = *(const char **)a;
	const char *bb = *(const char **)b;
	return strcmp(aa, bb);
}
int binary_search(char result[], int max_size, int *index, char *load[],int printOn)
{
	*index = 0;
	int length = strlen(result);
	char copy_result[100];
	for (int i = 0; i < length; i++)
	{
		copy_result[i] = tolower(result[i]);
	}
	copy_result[length] = '\0';
	int left = 0;
	int right = max_size - 1;
	int mid = 0;
	while (left <= right)
	{
		mid = (left + right) / 2;
    	int cmp = strcmp(copy_result,load[mid]);
    	if(printOn==1)
    	{
      		printf("dict[%d] = %s\n",mid,load[mid]);
    	}
    	if (cmp == 0)
		{
      *index+=1;
			return mid;
		}
		if (cmp < 0)
		{
			right = mid - 1;
			*index += 1;
		}
		else
		{
			left = mid + 1;
			*index += 1;
		}
	}
  return -1;
}
void editdistance_array(char *load[], int dictonary_size, char *word_searching,int editdistancearray[])
{
	for (int i = 0; i < dictonary_size; i++)
	{
		editdistancearray[i] = edit_distance(word_searching, load[i], 0);
	}
//	return editdistancearray;
}
int minumvalueof_array(int *editdistancearray, int array_size)
{
	int min = editdistancearray[0];
	for (int i = 0; i < array_size; i++)
	{
		if (editdistancearray[i] < min)
		{
			min = editdistancearray[i];
		}
	}
	return min;
}
void menuoption()
{
  printf("-1. Type correction ");
  printf("\n 0. Leave the words as it is(donot fix the spelling)\n");
  
}
void spell_check(char *testname, char *dictname, int printOn)
{
	// Write your code here

	FILE *fptr, *testfptr;
	char testfiledata[100000];
	char result[1000][100];

	fptr = fopen(dictname, "r");
	testfptr = fopen(testname, "r");
	if (fptr == NULL)
	{
		printf("Could not open File %s. Exit\n", dictname);
		exit(0);
	}
	if (testfptr == NULL)
	{
		printf("Could not open File %s. Exit\n", testname);
		exit(0);
	}
  	char outfile[100]="out_";
  	strcat(outfile,testname);
  	FILE *outfp = fopen(outfile,"w"); 
  	printf("Corrected file name is: %s",outfile);
	fgets(testfiledata, sizeof(testfiledata), testfptr);
	printf("\n\nLoading the dictonary file: %s\n\n", dictname);
	int size = 0;
	fscanf(fptr, "%d", &size);
	printf("Dictionary has size %d\n", size);
	char *load[size];
	for (int i = 0; i < size; i++)
	{
		load[i] = (char *)malloc(sizeof(char *) * 101);
	}
	for (int i = 0; i < size; i++)
	{
		fscanf(fptr, "%s", load[i]);
	}
	if (printOn == 1)
	{
		printf("Original dictionary :");
		printf("\n");
		for (int j = 0; j < size; j++)
		{
			printf("%d.  %s\n", j, load[j]);
		}
	}
	qsort(load, size, sizeof(char *), comparestr);
	if (printOn == 1)
	{
		printf("\n\nSorted Dictionary (alphabetical order) :");
		printf("\n");
		for (int j = 0; j < size; j++)
		{
			printf("%d.   %s\n", j, load[j]);
		}
	}
  	int count = 0, index_arr = 0;
  	char word[101];
  	char input_word[100];
  	int index = 0;
  	int choice =0;
  	int editdistancearray[size];
  	bool was_char = true;
  	char characters[20];
  	int j=0;
  	for (int i = 0; i <= strlen(testfiledata); i++)
  	{
    	if (testfiledata[i] == ' ' || testfiledata[i] == '?' || testfiledata[i] == '.' || testfiledata[i] == ',' || testfiledata[i] == '!') 
    	{
      		if (!was_char) 
      		{
        		word[j] = '\0';   
        		count++;
        		if(printOn ==1)
        		{
          			printf("\nBinary Search for : %s\n",word);
        		}
        		int search_result = binary_search(word, size, &index, load,printOn);
		    	printf("--- > |%s| (words compared when searching : %d)\n", word, index);
		    	if (search_result != -1)
		    	{
			    	printf("    - OK\n");
           			fprintf(outfp, "%s",word);
           			//fprintf(outfp, "%c", testfiledata[i]);
		    	}
		    	else
		    	{
            		menuoption();
            		editdistance_array(load,size,word,editdistancearray);
            		int minimum_editdistance =  minumvalueof_array(editdistancearray,size);
            		printf(" Minimum distance: %d (computed edit distances: %d)\n",minimum_editdistance,size);
            		printf(" Words that give minimum edit distance\n");
            		int *arr_indexes=malloc(size*sizeof(int));
            		int iter =0;
            		for(int i =0; i<size;i++)
             		{
               			if(editdistancearray[i]==minimum_editdistance)
               			{
                 			arr_indexes[iter]= i;
                 			iter++;
               			}
             		}
            		for(int p =0;p<iter;p++)
              		{
                		printf(" %d- %s\n",p+1,load[arr_indexes[p]]);
              		}
            		printf("Enter your choice (from the above options) ");
            		scanf("%d",&choice);
          			switch(choice)
            		{
              			case -1:
              				printf("Enter Correct word: ");
              				scanf("%s",input_word);
              				strcpy(word,input_word);
              				break;
            			case 0:
              				break;
            			default:
              				strcpy(word, load[arr_indexes[choice - 1]]);
              				break;
					      }	
            		fprintf(outfp, "%s",word);
            		//fprintf(outfp, "%c", testfiledata[i]);     
        			free(arr_indexes);
		  
        		}
        		j=0;
          		index_arr++;
        	}
          fprintf(outfp, "%c", testfiledata[i]);
        	characters[i] = testfiledata[i];
        	was_char = true;
    	}
    	else
    	{
      	word[j] = testfiledata[i];
      	j++;
      	was_char = false;
    	}  
  	}
    fclose(outfp);
	fclose(fptr);
	fclose(testfptr);
	for (int i = 0; i < size; i++)
	{
		free(load[i]);
		load[i] = NULL;
	}
	free(*load);
}
