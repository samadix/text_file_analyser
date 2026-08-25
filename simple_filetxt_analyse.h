#ifndef _SIMPLE_FILE_ANALYSER_H_
#define _SIMPLE_FILE_ANALYSER_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#define RED   "\x1B[31m"
#define GREEN "\x1B[32m"
#define RESET "\x1B[0m"
int max(int a ,int b);

typedef struct analysematching{
	int *idx_table;
	int occurent;
	} analyse;
void print_help(const char *program);
analyse analysing_sentence(char* word ,char* sentence,int*);

char* coloring_word(char* color,char* word,char* colorAfter);

int count_word_occurent_in_txtFile(FILE *f,char *word,int* table);

int count_word_occurent_in_sentence(char *sentence,char *word,int*);

bool remove_backSlashN(char *file_name);

bool is_a_pdf(FILE *f);
int count_numberOfligne_containeTheWord_in_txtFile(FILE *f,char *word,int* table);
bool file_exist(FILE *f);
bool is_txt_file(FILE *f);
int character_count(FILE *f);
int word_count(FILE *f);
int empty_ligne_count(FILE *f);
bool word_exist(FILE *f,char* w);
int *build_bad_table(char *word_search);
int bad_char_jumping(int *table ,unsigned char c,int len,int first_match);
bool find_pattern_using_bad_rule(char *sentence,char  *word,int*);
void search_pattern_in_txtFile(FILE *f,char *word,int*)	;
char* find_pattern_using_bad_rule_and_coloring(char *sentence,char *word,int  *bad_table);




#endif //_SIMPLE_FILE_ANALYSER_H_
