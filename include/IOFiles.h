#ifndef IOFILES_H
#define IOFILES_H

#define MAX_LINE_LENGTH 1000

enum {A=0, B=1, C=2, I=3, N=4, V=5, X=6, E=7};


void PuttingFileCharactersInMatrix (FILE* FileToOpen, int* NumOfLines, char*** FileCharacters,int **);
void SearchAndPrintLinesThatContainTheWord(char** FileCharacters, int * ByteOffset, int NumOfLines, char* TheWord, \
	int* ArrayOfOptions, int NumOfLinesAfter_forAAr);

# endif