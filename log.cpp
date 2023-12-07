#include <stdio.h>
#include "log.h"

void log(char* message)
{
    printf("Message Logged: %s||\n", message);
    fflush(stdout);
}