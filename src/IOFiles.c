# include <stdio.h>
# include <string.h>
# include <stdlib.h>
#include "regEx.h"
# include "IOFiles.h"

void SearchingTheWordInEachLine(char* str, char *pat, \
	int *isLineContaiinTheWord, int *numOfHits_needsForCOperator, int *ArrayOfOptions);
void printFormat(char ** FileCharacters, int *LinesThatContainTheWord, int NumOfLines, int *ArrayOfOptions, \
	int *ByteOffset, int NumOfLinesAfter_forAAr);
void printLine(char *content, int index, int byteOffset, char sepChar, int doPrintIndex, int doPrintOffset);

void PuttingFileCharactersInMatrix (FILE* FileToOpen, int* NumOfLines, char*** FileCharacters,int **ByteOffset)
{
	int i=0, j=0,flag=1;
	int temp,flagToContinue=1;
	for (i = 0; flagToContinue; i++){
		(*FileCharacters) = (char**) realloc (*FileCharacters, (i+1) * sizeof(char*));
		(*ByteOffset) = (int*) realloc(*ByteOffset, (i + 2)*sizeof(int) );
		((*FileCharacters)[i])=(char*) malloc (MAX_LINE_LENGTH * sizeof(char));	
		if (i == 0){
			(*ByteOffset)[0] = 0;
		}
		if (fgets( (*FileCharacters)[i], MAX_LINE_LENGTH, FileToOpen)==NULL|| feof(FileToOpen)){
			*NumOfLines = i+1;
			flagToContinue=0;
		}
		temp = (*ByteOffset)[i];
		temp+=   (int) (sizeof(char) )*(1 + strlen((*FileCharacters)[i]));
		(*ByteOffset)[i + 1] = temp;

	}
}


void SearchAndPrintLinesThatContainTheWord(char** FileCharacters, int * ByteOffset, int NumOfLines, char* TheWord, \
	int* ArrayOfOptions, int NumOfLinesAfter_forAAr)
{
	int *LinesThatContainTheWord = (int*) malloc(sizeof(int) *NumOfLines), numOfHits_needsForCOperator=0;
	int i = 0;
	char* pat = StrClone(TheWord);
	for (i = 0; i < NumOfLines; i++){
		char *str = StrClone(FileCharacters[i]);
		SearchingTheWordInEachLine(str, pat, &LinesThatContainTheWord[i], \
			&numOfHits_needsForCOperator, ArrayOfOptions);
		free(str);
	}
	if (ArrayOfOptions[C] == 1){
		printf("%d\n", numOfHits_needsForCOperator);
	}
	else{
		printFormat(FileCharacters, LinesThatContainTheWord, NumOfLines, ArrayOfOptions, \
			ByteOffset, NumOfLinesAfter_forAAr);
	}
	free(pat);
	free(LinesThatContainTheWord);
}

void SearchingTheWordInEachLine(char* str, char *pat, \
	int *isLineContaiinTheWord, int *numOfHits_needsForCOperator, int *ArrayOfOptions){
		int tempRes = 0;
		if (str[strlen(str)-1] == '\n'){
			str[strlen(str)-1] = '\0';
		}
		
		if (ArrayOfOptions[I] == 1){
			ConvertToLowerCase(str);
			ConvertToLowerCase(pat);
		}
		tempRes=  !(
			(ArrayOfOptions[E] == 1) ?
			regEx(str, pat, ArrayOfOptions[X], "", "") :
			mystrcmp(str, pat, ArrayOfOptions[X])
			);
		*isLineContaiinTheWord = (ArrayOfOptions[V] == 1) ? !tempRes : tempRes;
		
		*numOfHits_needsForCOperator += *isLineContaiinTheWord;
}


void printFormat(char ** FileCharacters, int *LinesThatContainTheWord, int NumOfLines, int *ArrayOfOptions, \
	int *ByteOffset, int NumOfLinesAfter_forAAr){
		int i, j;
		for (i = 0;  i < NumOfLines; i++){
			if (LinesThatContainTheWord[i] == 0){
				continue;
			}
			printLine(FileCharacters[i], i, ByteOffset[i], ':', ArrayOfOptions[N], ArrayOfOptions[B]);
			for (j = 1; ArrayOfOptions[A] == 1 && j <= NumOfLinesAfter_forAAr &&
				i + j <= NumOfLines && LinesThatContainTheWord[i + j] != 1; j++){
					int index = i + j;
					printLine(FileCharacters[index], index, ByteOffset[index], '-', ArrayOfOptions[N], ArrayOfOptions[B]);
			}
		}
}

void printLine(char *content, int index, int byteOffset, char sepChar, int doPrintIndex, int doPrintOffset){
	if (doPrintIndex){
		printf("%d%c", index+1,sepChar);
	}
	if (doPrintOffset){
		printf("%d%c", byteOffset,sepChar);
	}
	printf("%s", content,sepChar);
}