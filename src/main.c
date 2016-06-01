# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include "IOFiles.h"
#include "MyStrOp.h"
void ReadingCommandLineArguements(int argc, char**, char**, char **, int*,int* );

int main( int argc, char* argv [] ){
	char *TheWord, *FileName, **FileCharacters=NULL;
	int *ByteOffset = NULL;
	FILE* FileToOpen=NULL;
	int NumberOfLines=0;
	int NumOfLineAfter_forAAgr;
	int ArrayOfOptions[8]={0};
	char *res = NULL;
	ReadingCommandLineArguements(argc, argv,& TheWord,& FileName, ArrayOfOptions,&NumOfLineAfter_forAAgr);
	if ((FileToOpen =(strcmp(FileName,"") ?fopen(FileName, "rt"): stdin )) == NULL){
		exit(1);
	}
	PuttingFileCharactersInMatrix(FileToOpen, &NumberOfLines, &FileCharacters,&ByteOffset);
	fclose(FileToOpen);
	free(FileName);
	SearchAndPrintLinesThatContainTheWord(FileCharacters, ByteOffset, NumberOfLines, TheWord, ArrayOfOptions, NumOfLineAfter_forAAgr);
	 free(TheWord);
	free(FileCharacters);
	free(ByteOffset); 
	return 0;
}


void ReadingCommandLineArguements (int argc, char* argv[], char** TheWord, char** FileName,\
	int* ArrayOfOptions,int *NumOfLinesAfter_forAArgument){
		int i = 1;
	for (i = 1; i < argc; i++){
		if ((i < argc - 1) && strcmp(argv[i], "-A") == 0){
			ArrayOfOptions[A] = 1;
			*NumOfLinesAfter_forAArgument = atoi(argv[++i]);
		}
		else if (strcmp(argv[i], "-b") == 0){
			ArrayOfOptions[B] = 1;
		}
		else if (strcmp(argv[i], "-c") == 0){
			ArrayOfOptions[C] = 1;
		}
		else if (strcmp(argv[i], "-i") == 0){
			ArrayOfOptions[I] = 1;
		}
		else if (strcmp(argv[i], "-n") == 0){
			ArrayOfOptions[N] = 1;
		}
		else if (strcmp(argv[i], "-v") == 0){
			ArrayOfOptions[V] = 1;
		}
		else if (strcmp(argv[i], "-x") == 0){
			ArrayOfOptions[X] = 1;
		}
		else if (strcmp(argv[i], "-E") == 0){
			ArrayOfOptions[E] = 1;
		}
		else{
			*TheWord = StrClone(argv[i]);
			i++;
			*FileName =  StrClone((i < argc) ? argv[i]:"");
		}
	}
}