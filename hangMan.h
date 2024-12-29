 
#include <stdio.h>
#include <ctype.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "randomGen.h"
#include "charOps.h"
#include "socket.h"

#ifndef HANGMAN_H
#define HANGMAN_H

void initHangMan();
void drawHangman(int tries, char* buffer);

int getwelcomeNote(char* buffer);

int playGame(char *inputChar, char* buffer);

#endif // HANGMAN_H