#include <stdio.h>
#include "log.h"

void log(char* message)
{
    printf("Message Logged: %s\n", message);
    fflush(stdout);
}

void err(char* message)
{
    printf("Error Detected: %s\n", message);
    fflush(stdout);
}