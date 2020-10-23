#include <stdio.h>
#include <minwindef.h>

#define PRINTABLE condition > 0
#define PRINT fprintf(out, "%c", character)

int main() {
    enum {TEXT = 2,
          STRING = 1,
          ONE_LINE_COMMENT = 0,
          MULTI_LINE_COMMENT = -1,
          SUPPOSEDLY_COMMENT = -2,
          SUPPOSEDLY_TEXT = -3}
          condition = TEXT;
    char path[MAX_PATH] = "../files/",
         filename[MAX_PATH - 22],
         uncommented_filename[MAX_PATH] = "../files/uncommented_",
         character;
    FILE *in,
         *out;

    scanf("%s", filename);
    strcat(path, filename);
    strcat(uncommented_filename, filename);
    in = fopen(path, "r");
    out = fopen(uncommented_filename, "w");

    while(fscanf(in, "%c", &character) != EOF) {
        if(condition == TEXT) {
            if(character == '"')
                condition = STRING;
            if(character == '/') {
                condition = SUPPOSEDLY_COMMENT;
                continue;
            }
        }
        else if(condition == STRING && character == '"')
            condition = TEXT;
        else if(condition == ONE_LINE_COMMENT && character == '\n')
            condition = TEXT;
        else if(condition == MULTI_LINE_COMMENT) {
            if (character == '*') {
                condition = SUPPOSEDLY_TEXT;
                continue;
            }
        }
        else if(condition == SUPPOSEDLY_COMMENT) {
            if(character == '/')
                condition = ONE_LINE_COMMENT;
            if(character == '*')
                condition = MULTI_LINE_COMMENT;
        }
        else if(condition == SUPPOSEDLY_TEXT && character == '/') {
            condition = TEXT;
            continue;
        }
        if(PRINTABLE)
            PRINT;
    }

    fclose(in);
    fclose(out);
    return 0;
}