#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <math.h>

void hangman_illus(int k) {
char illustration[7][2048] = {"+---+\n|   |\n    |\n    |\n    |\n    |\n", "+---+\n|   |\nO   |\n    |\n    |\n    |\n", "+---+\n|   |\nO   |\n|   |\n    |\n    |", "+---+\n |   |\n O   |\n/|   |\n     |\n     |", "+---+\n |   |\n O   |\n/|\\  |\n     |\n     |", "+---+\n |   |\n O   |\n/|\\  |\n/    |\n     |", "+---+\n |   |\n O   |\n/|\\  |\n/ \\  |\n     |"};
printf("%s", illustration[k]);
}

void read_hangman_words(const char *fname, char arr[1024][100], int *z) {
    FILE *fp = fopen(fname, "r");

    if (fp == NULL) {
	perror("Error Opening File");
	return;
    }

    int i = 0;
    while (fgets(arr[i], sizeof(arr[i]), fp) != NULL) {
	arr[i][strcspn(arr[i], "\n")] = '\0';
	i++;
    }
    *z = i;

    fclose(fp);
}

void display_word_state(const char randomword[100], int guessed[100]) {
    for (int i = 0; randomword[i] != '\0'; i++) {
        if (guessed[i] == 1) {
            printf("%c ", randomword[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

int char_check(char randomword[100], int len, char c) {
    for (int i = 0; i < len; i++) {
        if (randomword[i] == c) {
            return 1; 
        }
    }
    return 0;
}


void get_user_char(char randomword[100], int len, int lives) {
    int j, k = 0;
    char new_randomword[100];
    strcpy(new_randomword, randomword);

    int guessed[100] = {0};

    while (lives > 0) {
        printf("%d Lives Remaining!\n", lives);
        display_word_state(randomword, guessed);

        printf("Enter Your Character from A-Z or a-z: ");
        char c;
        scanf(" %c", &c); 

        int char_found = char_check(randomword, len, tolower(c));
        if (char_found) {
            printf("Congrats! Character Guessed Correctly..\n");
            for (j = 0; randomword[j] != '\0'; j++) {
                if (randomword[j] == tolower(c)) {
                    guessed[j] = 1;
                }
            }
        } else {
            printf("Sorry The Character Did Not Match! 1 life lost..\n\n");
            hangman_illus(k);
            k++;
            lives--;
        }
        int word_guessed = 1;
        for (j = 0; randomword[j] != '\0'; j++) {
            if (guessed[j] == 0) {
                word_guessed = 0;
                break;
            }
        }

        if (word_guessed) {
            printf("Congratulations! You Guessed the Word: %s\n", randomword);
            return;
        }
    }

    printf("Sorry! Game Ends..\n");
    printf("The Word Was %s\n", randomword);
}




int main() {
    srand(time(NULL));
    int difficulty, custom;
    char words[1024][100];
    int z = 0;
    read_hangman_words("words.txt", words, &z);
    
    int length = z;

    int num = rand() % length;
    
    char randomword[100]; 
    strcpy(randomword, words[num]);

    int len = strlen(randomword);
    printf("WELCOME TO HANGMAN GAME!\n");
    printf("Your Random Word which you need to guess has %d letters! GOODLUCK\n", len);
   
    get_user_char(randomword, len, 7);
    return 0; 
}
