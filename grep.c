#include <stdio.h>
#include <string.h>

int main() {
    char pattern[100];
    char filename[100];
    char line[1000];
    FILE *fp;
    
    printf("Enter the search pattern: ");
    fgets(pattern, 100, stdin);
    pattern[strcspn(pattern, "\n")] = 0; // remove newline character
    
    printf("Enter the filename to search within: ");
    fgets(filename, 100, stdin);
    filename[strcspn(filename, "\n")] = 0; // remove newline character
    
    fp = fopen(filename, "r");
    
    if (fp == NULL) {
        printf("File not found.\n");
        return 0;
    }
    
    printf("Lines matching '%s' in file %s:\n", pattern, filename);
    
    while (fgets(line, 1000, fp) != NULL) {
        if (strstr(line, pattern) != NULL) {
            printf("%s", line);
        }
    }
    
    fclose(fp);
    
    return 0;
}
