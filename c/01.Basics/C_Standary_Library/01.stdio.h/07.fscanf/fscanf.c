#include <stdio.h>

int main(){
    FILE *file = fopen("input.txt", "r");
    char s[100];
    if(file == NULL){
        printf("Error opening file!\n");
        return 1;
    }
    fscanf(file, "%s\n", &s);
    printf("Read interget: %s\n", s);
    fclose(file);
    return 0;
}
