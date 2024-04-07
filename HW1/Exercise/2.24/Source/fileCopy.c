#include <stdio.h>
#include <stdlib.h>

void copyFile(FILE *source, FILE *destination) {
    int character;
    while ((character = fgetc(source)) != EOF) {
        fputc(character, destination);
    }
}

int main(int argc, char *argv[]) {
    char *sourceFileName = argv[1];
    char *destinationFileName = argv[2];

    if (argc != 3) {
        printf("Please input as follows: %s [source_file] [destination_file]\n", argv[0]);
        return -1;
    }

    FILE *sourceFile = fopen(sourceFileName, "r");
    if (sourceFile == NULL) {
        printf("Error: Unable to open source file %s\n", sourceFileName);
        return -1;
    }

    FILE *destinationFile = fopen(destinationFileName, "w");
    if (destinationFile == NULL) {
        printf("Error: Unable to create destination file %s\n", destinationFileName);
        fclose(sourceFile);
        return -1;
    }

    copyFile(sourceFile, destinationFile);

    if (fclose(sourceFile) != 0) {
        printf("Error: Failed to close source file %s\n", sourceFileName);
        return -1;
    }
    if (fclose(destinationFile) != 0) {
        printf("Error: Failed to close destination file %s\n", destinationFileName);
        return -1;
    }

    return 0;
}
