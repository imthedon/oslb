#include <stdio.h>

int main() {
    FILE *source_file, *target_file;
    char source_filename[100], target_filename[100], c;

    printf("Enter source file path: ");
    scanf("%s", source_filename);

    printf("Enter target file path: ");
    scanf("%s", target_filename);

    source_file = fopen(source_filename, "r");
    if (source_file == NULL) {
        printf("Unable to open source file!\n");
        return 1;
    }

    target_file = fopen(target_filename, "w");
    if (target_file == NULL) {
        printf("Unable to open target file!\n");
        fclose(source_file);
        return 1;
    }

    while ((c = fgetc(source_file)) != EOF) {
        fputc(c, target_file);
    }

    printf("File copied successfully.\n");

    fclose(source_file);
    fclose(target_file);

    return 0;
}
