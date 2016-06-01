#include "MyStrOp.h"

int ConvertToLowerCase(char* str){
	int chIndex;
	for (chIndex = 0; chIndex < strlen(str) + 1; chIndex++){
		char ch = str[chIndex];
		str[chIndex] = (ch >= 'A' && ch <= 'Z') ? (ch - 'A' + 'a') : ch;
	}
	return 0;
}


char *StrClone(char* str){
	char *cpy = (char*) malloc(sizeof(char) *(strlen(str) + 1));
	if (cpy == NULL){
		exit(1);
	}
	strcpy(cpy, str);
	return cpy;
}

int mystrcmp(char *s1, char *s2, int completeFit){
	int i = 0, j = 0, res = 1;
	if (!completeFit){
		for (i = 0; i < strlen(s1)+1; i++){
			res &= strncmp(&(s1[i]), s2, strlen(s2));
		}
	}
	else{
		res = strcmp(s1, s2);
	}
	return res;
}

char* cleanStr(char *s){
	int i, textState = 0, j = 0;
	for (i = 0; i <= strlen(s) + 1; i++){
		if (s[i] == '\\' && !textState){
			textState = 1;
			continue;
		}
		textState = 0;
		s[j++] = s[i];
	}
	return s;
}