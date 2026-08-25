#include "simple_filetxt_analyse.h"



void print_help(const char *program)
{
    printf("\n");
    printf("========== simple_text_file_analyse ==========\n\n");

    printf("Usage:\n");
    printf("  %s [OPTION] <word> <file>\n\n", program);

    printf("Options:\n");
    printf("  -s, --search      Search for the word and display matching lines\n");
    printf("  -o, --occ         Count occurrences of the word in the file\n");
    printf("  -l, --lines       Count lines containing the word\n");
    printf("  -h, --help        Display this help message\n");

    printf("\nExamples:\n");
    printf("  %s -s PATTERN ur_file.txt\n", program);
    printf("  %s -o PATTERN ur_file.txt\n", program);
    printf("  %s -l PATTERN ur_file.txt\n", program);
    printf("  %s -h\n", program);

    printf("\n===============================================\n");
}
/*.........................................................................................................................................................................................*/	

int  max(int a,int b){
	return (a>b)?a:b;
	}

	/*.........................................................................................................................................................................................*/	

		int count_numberOfligne_containeTheWord_in_txtFile(FILE *f,char *word,int* table){
			if(!file_exist(f) || word==NULL) return 0;
			int occurent=0;
			char* ligne=(char*)malloc(1024*sizeof(char));
			if(ligne==NULL){
				printf("\nMEMORY ERROR");
				return 0;}
			while( (fgets(ligne,1024*sizeof(char),f ) )!=NULL){
				if(find_pattern_using_bad_rule(ligne,word,table)) occurent++;
				}
				rewind(f);
			return occurent;
			}
//===================================================================================================================
int count_word_occurent_in_txtFile(FILE *f,char *word,int* table){
	analyse A;
	A.idx_table=NULL; A.occurent=0;
	int occ=0;
			if(!file_exist(f) || word==NULL) return 0;
			char* ligne=(char*)malloc(1024*sizeof(char));
			if(ligne==NULL){
				printf("\nMEMORY ERROR");
				return 0;}
			while( (fgets(ligne,1024*sizeof(char),f ) )!=NULL){
				A=analysing_sentence(word,ligne,table);
				occ+=A.occurent;
				free(A.idx_table);
				A.idx_table=NULL;
				A.occurent=0;
				}
               
				rewind(f);
			return occ;
			}

/*.........................................................................................................................................................................................*/	
char* coloring_word(char* color,char* word,char* colorAfter){
	if(color==NULL || word==NULL){
		printf("\nERROR WHILE COLORING THE WORD\n"); 
		return NULL;}
          int lenCAF=strlen(colorAfter),lenC=strlen(color),lenW=strlen(word);
          int lenOFcoloredword=1+lenCAF+lenC+lenW;
          char* colored_word=(char*)malloc(sizeof(char)*lenOFcoloredword);
          if(colored_word==NULL) {
		printf("\nERROR WHILE COLORING THE WORD\n"); 
		return NULL;}
         colored_word[lenOFcoloredword-1]='\0';
         for(int i=0;i<lenC;i++) colored_word[i]=color[i];
         for(int i=lenC,j=0;j<lenW && i<lenC+lenW;j++,i++) colored_word[i]=word[j];
         for(int i=lenC+lenW,j=0;i<lenOFcoloredword-1 && j<lenCAF;i++,j++) colored_word[i]=colorAfter[j];
         return colored_word;
	}
/*.........................................................................................................................................................................................*/	
bool is_a_pdf(FILE* f){
		if(!file_exist(f))  return false;
		char first4char[5];first4char[4]='\0';char c; int i=0;
		while((c=fgetc(f))!=EOF && i!=4 ){
			first4char[i]=c;
			i++;}
		if(strcmp("%PDF",first4char)==0) {
			rewind(f); return true;
			}
		rewind(f);
		return false;
			
			}
	
	/*.........................................................................................................................................................................................*/	

	bool is_txt_file(FILE *f){
	
	if(!file_exist(f)){
		printf("\n ERROR file doesn't exist\n");
		return false;
		}
	char c;
	while((c=fgetc(f)) != EOF){
		if(c==0){ rewind(f);
			return false;
			}
		
		} rewind(f);
		return true;
	}
/*.........................................................................................................................................................................................*/	

	
/*.........................................................................................................................................................................................*/	

	int ligne_count(FILE *f){
	
	if(!file_exist(f)) return 0;
	
char c; int ligne=0;
	while((c=fgetc(f))!=EOF){
		
		if(c=='\n') ligne++;
		
		}
		rewind(f);
	return ligne;
	}
/*.........................................................................................................................................................................................*/	

bool file_exist(FILE *f){
	
	return (f!=NULL);
	
	}
/*.........................................................................................................................................................................................*/	

bool remove_backSlashN(char *file_name){
	int k=0; 
	k=strlen(file_name);
	
	if(k==0) return false;
	
	for(int i=0;i<k;i++){
		
		if(file_name[i]=='\n'){    file_name[i]='\0';break;  }
		} return false;
	}
/*.........................................................................................................................................................................................*/	

int* build_bad_table(char *word_search){
	
	int* the_bad_table= (int*)malloc(256*sizeof(int));
		if(word_search==NULL || the_bad_table==NULL) return NULL;
		
		int len=strlen(word_search);
		
		memset(the_bad_table,-1,256*sizeof(int));
		unsigned char c;
		for(int i=0;i<len;i++) {
			          c=word_search[i];
			       the_bad_table[(int)c]=i;
			                                         }
		
		           return the_bad_table;
		}
	/*.........................................................................................................................................................................................*/	
int bad_char_jumping(int *table ,unsigned char c,int len,int first_match){
		
		if(table==NULL) return 1;
		
		int k=len-table[(int)c]-1-first_match;
		
		return max(k,1);
		
		}
	/*.........................................................................................................................................................................................*/	
	
int count_word_occurent_in_sentence(char *sentence,char *word,int* bad_table){
	int k=0;
		if(sentence==NULL 
			|| word==NULL 
			) return 0;

		int lenW=strlen(word),lenS=strlen(sentence);

		if(lenW>lenS) return 0;
		int* table=bad_table;
		int i=lenW-1;
		while(i<lenS){
			for(int j=lenW-1;j>-1;j--){
				if(sentence[i - (lenW - 1 - j)]!=word[j] && j!=lenW-1){
					i+=bad_char_jumping(table,sentence[i - (lenW - 1 - j)],lenW,j);
					break;
					}
				if(sentence[i - (lenW - 1 - j)]!=word[j] && j==lenW-1){
					i+=bad_char_jumping(table,sentence[i - (lenW - 1 - j)],lenW,0);
					break;}
				if(j==0) {i+=lenW;k++;}
				
				}
				} 
	return k;
	}
	
/*.........................................................................................................................................................................................*/	

bool find_pattern_using_bad_rule(char *sentence,char  *word,int* bad_table){
	if(sentence==NULL || word==NULL ) return  false;
	int lenW=strlen(word),lenS=strlen(sentence);
		if( lenW>lenS) return false;
		
		int* table=bad_table;
		int i=lenW-1;
		while(i<lenS){
			for(int j=lenW-1;j>-1;j--){
				if(sentence[i - (lenW - 1 - j)]!=word[j] && j!=lenW-1){
					i+=bad_char_jumping(table,sentence[i - (lenW - 1 - j)],lenW,j);break;
					}
				if(sentence[i - (lenW - 1 - j)]!=word[j] && j==lenW-1){
					i+=bad_char_jumping(table,sentence[i - (lenW - 1 - j)],lenW,0);break;}
				if(j==0) return true;
				
				}
			}
			 
		return false;
		
		} 
		
/*.........................................................................................................................................................................................*/	
analyse analysing_sentence(char* word,char* sentence,int* bad_table){

	analyse word_analyse; 
	
	word_analyse.idx_table=NULL; 
	word_analyse.occurent=0;
	if(sentence==NULL || word==NULL){ 
		printf("\nERROR : INVALIDE WORD OR SENTENCE\n");
		return word_analyse;
		}
		int lenS=strlen(sentence),
		lenW=strlen(word);
	word_analyse.occurent=count_word_occurent_in_sentence(sentence,word,bad_table);

			  word_analyse.idx_table=(int*)malloc(word_analyse.occurent*sizeof(int));
			if(word_analyse.idx_table==NULL) { 
				printf("\n ERROR ALLOCATION IN FUNCTION analysing_ligne\n"); return word_analyse;
				}
				int* table=bad_table;
			int k=0, i=lenW-1;
		
		while(i<lenS){
			for(int j=lenW-1;j>-1;j--){
				if(sentence[i - (lenW - 1 - j)]!=word[j] && j!=lenW-1){
					i+=bad_char_jumping(table,sentence[i - (lenW - 1 - j)],lenW,j);break;
					}
				if(sentence[i - (lenW - 1 - j)]!=word[j] && j==lenW-1){
					i+=bad_char_jumping(table,sentence[i - (lenW - 1 - j)],lenW,0);break;}
				if(j==0) {  
					word_analyse.idx_table[k++]=i;
					i+=lenW;
				}
			
			}} 	
			
				return word_analyse;
	
	}

/*.........................................................................................................................................................................................*/	


	char* find_pattern_using_bad_rule_and_coloring(char *sentence,char  *word,int  *bad_table){
	if(sentence==NULL || word==NULL){ 
		printf("\nERROR : INVALIDE WORD OR SENTENCE\n");
		return NULL;
		}
    if(!find_pattern_using_bad_rule(sentence, word, bad_table)) return NULL;


	analyse analysing_sent=analysing_sentence(word,sentence,bad_table);

		int w_occ_in_S=analysing_sent.occurent;
		char* colored_word=coloring_word(GREEN,word,RED);
		if(colored_word == NULL){ 
			printf("\nERROR WHILE COLORING WORD\n");
			return NULL; }
			
		int lenCW=strlen(colored_word),
		    lenS=strlen(sentence),
		    lenW=strlen(word),
		    lenGRN=strlen(GREEN),
		    lenRED=strlen(RED),
		    lenRES=strlen(RESET);
		int lenColoredSent=lenS+w_occ_in_S*(lenRED+lenGRN)+lenRES+lenRED;
		char* colored_sentence=(char*)malloc(sizeof(char)*(lenColoredSent+1));
		if(colored_sentence==NULL){
			printf("\nERROR WHILE ALLOCATION FOR THE COLOREDsENTENCE\n");
			return NULL;}
			
			colored_sentence[lenColoredSent]='\0';
			for(int i=0;i<lenRED;i++) colored_sentence[i]=RED[i];
			for(int i=lenRES-1,j=lenColoredSent-1;i>-1 ;i--,j--) colored_sentence[j]=RESET[i];
		int* table=bad_table;
		if(table==NULL){
			printf("\n ERROR BUILDING BAD_RULE ' S TABLE \n"); 
			return NULL;}
		
			int last_copie_from=0; 
			int last_copie_at=lenRED;
			for(int i=0;i<analysing_sent.occurent;i++){
				while(last_copie_from<=analysing_sent.idx_table[i]-lenW) {
					colored_sentence[last_copie_at++]=sentence[last_copie_from++]; 
				}
				for(int j=0;j<lenCW && last_copie_at<lenColoredSent;j++) {
					colored_sentence[last_copie_at++]=colored_word[j];
					}
					last_copie_from+=lenW;
					}
				while(last_copie_from<lenS){
					colored_sentence[last_copie_at++]=sentence[last_copie_from++];
					}
				free(analysing_sent.idx_table);
				analysing_sent.idx_table=NULL;
				free(colored_word);
				return colored_sentence;
				
				}
		
void search_pattern_in_txtFile(FILE *f,char *word,int* table){

	if(is_a_pdf(f)){printf("\nPDF NOT SUPPORTED !\n");return;}

	if(!is_txt_file(f)){printf("\nSUPPORTE TXT FILE ONLY !\n");return;}

	if(!file_exist(f)){printf("\nFILE NOT FOUND !\n");return;}

	bool exist=false;

	char* buff=(char*)malloc(1025*sizeof(char));

	char* colored=NULL;

	while(fgets(buff,1024*sizeof(char),f) != NULL){

		if((colored=find_pattern_using_bad_rule_and_coloring(buff,word,table))!=NULL){

			printf("%s",colored);
			free(colored);
			 colored=NULL;
			if(!exist) exist=true;

			}
		
		
		} 
		free(buff);
		free(colored);
		rewind(f);
	if(!exist) printf("\n'%s' isn't in this file \n",word);
	}








//========================= MAIN ======================

int main(int argc, char **argv)
{
    
    if (argc == 2 &&
        strcmp(argv[1], "-h") == 0)
    {
        print_help(argv[0]);
        return 0;
    }


   
    if (argc != 4)
    {
        printf("ERROR: invalid arguments.\n");
        printf("Use '%s -h' for help.\n", argv[0]);
        return 1;
    }


    char *options = argv[1];
    char *word    = argv[2];
    char *filePath = argv[3];


   
    if (options[0] != '-')
    {
        printf("ERROR: option must start with '-'.\n");
        return 1;
    }


   
    bool search = false;
    bool occ    = false;
    bool lines  = false;


    for (int i = 1; options[i] != '\0'; i++)
    {
        switch (options[i])
        {
            case 's':
                search = true;
                break;

            case 'o':
                occ = true;
                break;

            case 'l':
                lines = true;
                break;

            default:
                printf("ERROR: unknown option '-%c'\n",
                       options[i]);

                printf("Use '%s -h' for help.\n",
                       argv[0]);

                return 1;
        }
    }


    
    if (!search && !occ && !lines)
    {
        printf("ERROR: no operation specified.\n");
        printf("Use '%s -h' for help.\n",
               argv[0]);

        return 1;
    }


    
    FILE *f = fopen(filePath, "r");

    if (f == NULL)
    {
        printf("ERROR: cannot open file '%s'\n",
               filePath);

        return 1;
    }


    
    int *table = build_bad_table(word);

    if (table == NULL)
    {
        printf("ERROR: unable to build bad-character table.\n");

        fclose(f);

        return 1;
    }


   
    if (search)
    {
        search_pattern_in_txtFile(
            f,
            word,
            table
        );
    }


    
    if (occ)
    {  printf("\nCalculating occurrences...\n");
        int number =
            count_word_occurent_in_txtFile(
                f,
                word,
                table
            );

        printf("\nNumber of occurrences of '%s' : %d\n",
               word,
               number);
    }


    /*
     * LINES
     */
    if (lines)
    {     printf("\nCounting lines containing the word...\n");

        int number =
            count_numberOfligne_containeTheWord_in_txtFile(
                f,
                word,
                table
            );

        printf("\nNumber of lines containing '%s' : %d\n",
               word,
               number);
    }


    
    free(table);
    fclose(f);

    return 0;
}
