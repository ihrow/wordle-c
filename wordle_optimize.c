// Wordle Game

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>


#define GRAY "\033[97;1;100m"
#define YELL "\033[97;1;43m"
#define GREEN "\033[97;1;42m"
#define RED "\033[97;1;31m"
#define B "\033[1m"
#define reset "\033[0m"

void gray(char c) {
    printf("%s %c %s ", GRAY, toupper(c), reset);
}
void yellow(char c) {
    printf("%s %c %s ", YELL, toupper(c), reset);
}
void green(char c) {
    printf("%s %c %s ", GREEN, toupper(c), reset);
}

void rules();

void game(char* guessed_word, int amount_of_words, char** words) {
    int amount_of_tries = 0;

    int color_code[6][5]; 
    // fill color_code with 0
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 5; j++) {
            color_code[i][j] = 0;
        }
    }

    char* guesses[6];

    while (amount_of_tries < 6) {
        char word[10];
        printf("\t\t\t\t\t\t");
        scanf("%s", word);

        if (strlen(word) != 5) {
            printf("\t\t\t\t\t\t");
            printf(RED "Wrong length! \n" reset);
            continue;
        }
        for (int i = 0; i < 5; i++) {
            word[i] = tolower(word[i]);
        }

        int found = 0;
        for (int i = 0; i < amount_of_words; i++) {
            if (strcmp(word, words[i]) == 0) {
                found = 1;
            }
        }

        if (found != 1) {
            printf("\t\t\t\t\t\t");
            printf("The word" B " %s " reset "is not in the list!\n", word);
            continue;
        }
        
        guesses[amount_of_tries] = strdup(word);
        
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (word[i] == guessed_word[j]) {
                    if (i == j) {
                        color_code[amount_of_tries][i] = 2;
                    } else {
                        if (color_code[amount_of_tries][i] != 0) {
                            continue;
                        }
                        color_code[amount_of_tries][i] = 1;
                    }
                }
            }
        }

        printf("\n");
        system("clear");
        for (int i = 0; i <= amount_of_tries; i++) {
            printf("\t\t\t\t\t\t");
            for (int j = 0; j < 5; j++) {
                if (color_code[i][j] == 1) {
                    yellow(guesses[i][j]);
                } else if (color_code[i][j] == 2) {
                    green(guesses[i][j]);
                } else {
                    gray(guesses[i][j]);
                }
            }
            printf("\n\n");
        }


        if (strcmp(word, guessed_word) == 0) {
            printf("\t\t\t\t\t\t");
            printf(B"\nWell done. Guessed it in: %d.\n" reset, amount_of_tries + 1);
            printf("\t\t\t\t\t\t");
            break;
        } 



        amount_of_tries++;
    }
    if (amount_of_tries == 6) {
        printf("\nThe word was: "B"%s\n" reset, guessed_word);
    }

}


// count amount of words in file
int count_words(char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 0;
    }

    int amount_of_words = 0;
    char c;
    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            amount_of_words++;
        }
    }
    fclose(fp);
    return amount_of_words;
}


// alocate memory for words array and fill it with words from file
char** fill_words(char* filename, int amount_of_words) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return NULL;
    }

    char** words = malloc(amount_of_words * sizeof(char*));
    for (int i = 0; i < amount_of_words; i++) {
        words[i] = malloc(6 * sizeof(char));
        fscanf(fp, "%s", words[i]);
    }

    fclose(fp);
    return words;
}

int main() {
    printf("\n");
    rules();

    int amount_of_words = count_words("words.txt");

    char **words = fill_words("words.txt", amount_of_words);

    // randomly select a word
    srand(time(NULL));

    char answer;
    int random_number = 0;
    do {
        random_number = rand() % amount_of_words;
        game(words[random_number], amount_of_words, words);
        printf("Do you want to play again? (y/n) ");
        scanf(" %c", &answer);
        answer = tolower(answer);
        system("clear");
    } while (answer != 'n');
    return 0;
}

void rules() {
    printf("Guess the" B " WORDLE " reset "in six tries.\n\n");
    printf("Each guess must be a valid five-letter word. Hit the enter button to submit.\n\n");
    printf("After each guess, the color of the tiles will change to show how close your guess was to the word.\n\n");
    printf(B "Examples:\n\n" reset);
    printf(GREEN " W " reset " " GRAY " E " reset " " GRAY " A " reset " " GRAY " R " reset " " GRAY " Y " reset);
    printf("\nThe letter" B " W " reset "is in the word and in the correct spot.\n\n");
    printf(GRAY " P " reset " " YELL " I " reset " " GRAY " L " reset " " GRAY " L " reset " " GRAY " S " reset);
    printf("\nThe letter" B " I " reset "is in the word, but in the wrong spot.\n\n");
    printf(GRAY " V " reset " " GRAY " A " reset " " GRAY " G " reset " " GRAY " U " reset " " GRAY " E " reset);
    printf( B "\nAll" reset " letters are not in the word.\n\n");
}

