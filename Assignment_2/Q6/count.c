#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
int main(int argc, char *argv[]) {
    if (argc==1)
    {
        int ch;
        int nonAlphabeticCount = 0;
        while ((ch = getchar()) != EOF) {
            if (!isalpha(ch)) {
                nonAlphabeticCount++;
                printf("%c", ch);
            }
        }
        fprintf(stdout, "Count of non-alphabetic characters: %d\n", nonAlphabeticCount); 
    }else if(argc==2){
        // This means that there is an overlay
        printf("Overlay is there");
        char ch;
        int count = 0;
        int overlay = atoi(argv[1] + 1);
        if (overlay == 0) {
            fprintf(stderr, "Incorrect overlay");
            exit(1);
        }
        printf("Value of overlay is: %d", overlay);
        while((ch=getchar())!=EOF){
            if(--overlay==0){
                break;
            }
            if(!isalpha(ch)){
                count++;
                printf("%c", ch);
            }
        }
        printf("The number of non alphabetic characters are: %d\n", count);
    }else{
        fprintf(stderr, "Incorrect number of arguments");
        exit(1);
    }
    return 0;
}