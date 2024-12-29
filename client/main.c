#include <stdio.h>
#include <ctype.h>
#include "socket.h"


int main(int argc, char *argv)
{

    //SOCKET

    int ret, valread, client_fd;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE];

    client_fd = socket(AF_INET, SOCK_STREAM,0);
    if(client_fd < 0)
    {
        printf("socket creation failed\n");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    ret = inet_pton(AF_INET, LOCAL_HOST, &serv_addr.sin_addr);
    if (ret <= 0) {
        printf("Invalid address/ Address not supported \n");
        exit(EXIT_FAILURE);
    }
    ret = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if (ret < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    //For welcome mesage
    valread = read(client_fd, buffer, BUFFER_SIZE - 1);
    if (valread <= 0) {
        printf("read < 0 bytes Exiting %d...\n",valread);
        exit(EXIT_FAILURE);
    }
    buffer[valread] = '\0';
    printf("%s\n", buffer);
    while (1)
    {
        scan:
        clearbuf(buffer);
        scanf("%c", buffer);
        while (getchar() != '\n');
        if(buffer[0]== ' ' || buffer[0]== '\n')
        {
            printf("type only non space and newline char\n");
            goto scan;
        }
            
        send(client_fd, buffer, 1, 0);
        valread = read(client_fd, buffer, BUFFER_SIZE - 1);
        if (valread <= 0)
        {
            printf("read < 0 bytes Exiting %d...\n", valread);
            exit(EXIT_FAILURE);
        }
        buffer[valread] = '\0';
        printf("%s\n", buffer);
    }
    close(client_fd);
    

    // printf("Welcome to Hangman Game\n");
    // printf("Guess all the chars in the word\n");
    // printf("Hint: %s\n", wordList[random_choice].hint);
    // getCharList(wordList[random_choice].word, charList);
    // wordSize = wordLen(wordList[random_choice].word);
    // charListSize = wordLen(charList);

    // while (guessedSize < charListSize && wrongGuessLeft > 1)
    // {
    //     printf("guess the char:");
    //     scanf("%c", &inputChar);
    //     while (getchar() != '\n')
    //         ;
    //     if (charPresentinWord(toupper(inputChar), charList))
    //     {
    //         if (charPresentinWord(toupper(inputChar), guessedCharList) == 0)
    //         {
    //             guessedSize++;
    //             printf("Good guess!!");
    //             guessedCharList[guessedCharIter] = toupper(inputChar);
    //             guessedCharIter++;
    //         }
    //         else
    //         {
    //             printf("Good guess!!But you already guessed it before");
    //         }
    //     }
    //     else
    //     {
    //         wrongGuessLeft--;
    //         printf("Wrong guess!! only %d left\n", wrongGuessLeft);
    //     }

    //     if (inputChar == wordList[random_choice].word[wordIter])
    //     {
    //         while (inputChar == wordList[random_choice].word[wordIter])
    //         {
    //             wordIter++;
    //         }
    //     }
    //     drawHangman(6 - wrongGuessLeft);
    //     printf("%.*s\n", wordIter, wordList[random_choice].word);
    // }
    // if (guessedSize == charListSize)
    // {
    //     printf("congragulations!! You won. The word is %s\n", wordList[random_choice].word);
    // }
    // else
    // {
    //     printf("Lost!! You lost. The word is %s\n", wordList[random_choice].word);
    // }
}
