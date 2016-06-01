#include "regEx.h"
int regEx_temp(char *s1, char *s2, int x_stauts);
void replaceOneChar(char* s, char **cps, int index, int skipInd, char ch);
int orSection(char *s1,char *s2, int i, char *pre, char *post, int x_status);
int closeBrackets(char *s1, char *s2, int i, char *pre, char *post, int x_status);
int dotSection(char *s1, char *s2, int i, char *pre, char *post, int x_status);
int charRangeSection(char *s1, char *s2, int i, char *pre, char *post, int x_status);

int regEx(char *s1, char* s2, int x_status, char *pre, char *post){
	int res = 1, i = 0;
	char ch, *newPre; 
	for (i = 0;  i < strlen(s2); i++){
		if (s2[i] == '\\'){
			i++;continue;
		}
		if (s2[i] == '|'){
			return orSection(s1, s2, i, pre, post, x_status);
		}
		if (s2[i] == '('){
			return closeBrackets(s1, s2, i, pre, post, x_status);
		}
		else if (s2[i] == '.'){
			return dotSection(s1, s2, i, pre, post, x_status);
		}
		else if (s2[i] == '['){
			return charRangeSection(s1, s2, i, pre, post, x_status);
		}
	}
	newPre= (char*) malloc(2 * sizeof(char) *(strlen(pre) + strlen(s2) + 1));
	if (newPre == NULL){
		exit(1);
	}
	sprintf(newPre, "%s%s", pre, s2);
	cleanStr(newPre);
	if (strcmp(post, "")){
		return regEx(s1, post, x_status, newPre, "");
	}
	res = mystrcmp(s1, newPre, x_status);
	free(newPre);
	return res;
}


void replaceOneChar(char* s,char **cps, int index, int skipInd, char ch){
	char temp[10];
	int len = strlen(s);
	char *newS = (char*) malloc(sizeof(char) *(len+ 10 - skipInd));
	strcpy(newS, s);
	newS[strlen(newS)] = 0;
	newS[index] = '\0';
	if (ch == '.' || ch == '{' || ch == '}' ||
		ch == '[' || ch == ']' || ch == '\\' ||
		ch == '|'|| ch=='(' ||ch ==')'){
			sprintf(temp, "%c%c%c", '\\', ch, '\0');
	}
	else{
		sprintf(temp, "%c%c", ch, '\0');
	}
	sprintf(newS, "%s%s%s",newS ,temp,&s[index + skipInd + 1] );
	*cps=newS;
}



int orSection(char *s1,char *s2, int i, char *pre, char *post,int x_status){
	
	int t1, t2;
	char *cpypre=NULL, *cpypost=NULL;
	if (NULL == (cpypre = (char*) malloc(sizeof(char) * (1 + strlen(pre)))) ||
		NULL == (cpypost = (char*) malloc(sizeof(char) * (1 + strlen(post))))){
			exit(EXIT_FAILURE);
	}
	s2[i] = 0;
	strcpy(cpypre, pre);
	strcpy(cpypost, post);
	t1= regEx(s1, s2, x_status, cpypre, cpypost);
	strcpy(cpypre, pre);
	strcpy(cpypost, post);
	t2 = regEx(s1, &(s2[i + 1]), x_status, cpypre,cpypost);
	s2[i] = '|';
	return t1&t2;
}

int closeBrackets(char *s1,char *s2,int i,char *pre,char *post,int x_status){
	int k = i,res;
	char *newPre, *newPost;
	while (s2[k] != ')' && k < strlen(s2)){
		k++;
	}
	s2[i] = '\0';
	s2[k] = '\0';
	newPre = (char*) malloc(sizeof(char) *(strlen(pre) + strlen(s2) + 1));
	newPost = (char*) malloc(sizeof(char) *(strlen(post) + strlen(&s2[k + 1]) + 1));
	
	sprintf(newPre, "%s%s", pre, s2);
	sprintf(newPost, "%s%s", post, &s2[k + 1]);
	res = regEx(s1, &s2[i + 1], x_status, newPre, newPost);
	free(newPre);
	free(newPost);
	s2[i] = '(';
	s2[k] = ')';
	return res;
}

int dotSection(char *s1, char *s2, int i, char *pre, char *post, int x_status){
	char ch, *cpys2_1 = NULL;
	int res = 1;
	for (ch = BEGIN_CHAR; res && ch < END_CHAR; ch++){
		replaceOneChar(s2, &cpys2_1, i, 0, ch);
		res &= regEx(s1, cpys2_1, x_status, pre, post);
	}
	return res;
}

int charRangeSection(char *s1, char *s2, int i, char *pre, char *post, int x_status){
	char ch,*cpys2_1 = NULL;
	char begCh, endCh;
	int j = i,res=1;
	if (s2[j + 1] == '\\'){
		j++;
	}
	begCh = s2[j + 1];
	while (s2[j] != ']' && j < strlen(s2)){
		if (s2[j + 1] == '\\'){
			j++;
		}
		j++;
	}
	endCh = s2[j - 1];
	for (ch = begCh; res& ch <= endCh; ch++){
		replaceOneChar(s2, &cpys2_1, i, j - i, ch);
		res &= regEx(s1, cpys2_1, x_status, pre, post);
	}
	return res;
}