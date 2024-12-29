
#include <stdio.h>
#include <ctype.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wordList.h"
#include "hangMan.h"
#include "randomGen.h"
#include "charOps.h"

extern struct WordWithHint wordList[];
int random_choice;
int wrongGuessLeft;
int wordSize, charListSize;
char charList[250], guessedCharList[250];
int guessedSize = 0;
int wordIter = 0, charListIter = 0, guessedCharIter = 0;

void initHangMan()
{
    clearCharList(charList);
    clearCharList(guessedCharList);
    random_choice = genIntRandomInRange(MAX_INDEX, 6);
    getCharList(wordList[random_choice].word, charList);
    wordSize = wordLen(wordList[random_choice].word);
    charListSize = wordLen(charList);
    wrongGuessLeft = 6;
    guessedSize = 0;
    wordIter = 0, charListIter = 0, guessedCharIter = 0;
}

void drawHangman(int tries, char *buffer)
{
    const char *hangmanParts[] = {"     _________", "    |         |",
                                  "    |         O", "    |        /|\\",
                                  "    |        / \\", "    |"};

    sprintf(buffer + strlen(buffer), "%s", "\n");
    for (int i = 0; i <= tries; i++)
    {
        sprintf(buffer + strlen(buffer), "%s\n", hangmanParts[i]);
    }
}

int getwelcomeNote(char *buffer)
{
    sprintf(buffer + strlen(buffer), "%s", "Welcome to Hangman Game\n");
    sprintf(buffer + strlen(buffer), "%s", "Guess all the chars in the word\n");
    sprintf(buffer + strlen(buffer), "%s %s \n", "Hint: ", wordList[random_choice].hint);
}

int playGame(char *inputChar, char *buffer)
{

    if (guessedSize < charListSize && wrongGuessLeft > 1)
    {
        if (charPresentinWord(toupper(*inputChar), charList))
        {
            if (charPresentinWord(toupper(*inputChar), guessedCharList) == 0)
            {
                guessedSize++;
                // sprintf(buffer + strlen(buffer), "%s\n", "Good guess!!");
                sprintf(buffer + strlen(buffer), "%s\n", "Good guess!!");
                guessedCharList[guessedCharIter] = toupper(*inputChar);
                guessedCharIter++;
            }
            else
            {
                sprintf(buffer + strlen(buffer), "%s", "Good guess!!But you already guessed it before");
            }
        }
        else
        {
            wrongGuessLeft--;
            sprintf(buffer + strlen(buffer), "%s %d %s", "Wrong guess!! only", wrongGuessLeft, "left\n");
        }

        if (*inputChar == wordList[random_choice].word[wordIter])
        {
            while (*inputChar == wordList[random_choice].word[wordIter])
            {
                wordIter++;
            }
        }
        drawHangman(6 - wrongGuessLeft, buffer);
        sprintf(buffer + strlen(buffer),"%.*s\n",wordIter, wordList[random_choice].word );
        if (guessedSize < charListSize)
        {
            return 1;
        }
            
    }
    printf("after 2 if\n");
    if (guessedSize == charListSize)
    {
        sprintf(buffer + strlen(buffer), "%s %s %s", "congragulations!! You won. The word is", wordList[random_choice].word, "\n");
        return -1;
    }
    
    if (wrongGuessLeft <= 1)
    {
        sprintf(buffer + strlen(buffer), "%s %s %s", "Lost!! You lost. The word is", wordList[random_choice].word, "\n");
        return -1;
    }
}
