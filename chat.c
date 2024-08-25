// Chat Network Application 
// Jason Losh

//-----------------------------------------------------------------------------
// Compile notes for C
//-----------------------------------------------------------------------------

// gcc -std=gnu11 -Wall -o chat chat.c udp3.c kbhit.c

//-----------------------------------------------------------------------------
// Device includes, defines, and assembler directives
//-----------------------------------------------------------------------------

#include <stdlib.h>          // EXIT_ codes
#include <stdbool.h>         // bool
#include <stdio.h>           // printf, scanf
#include <string.h>          // strlen, strcmp

#include "kbhit.h"           // kbhit
#include "udp3.h"            // udp3 library

#define LOCAL_PORT  5000     // port from which this program receives data
#define REMOTE_PORT 5000     // port to which this program sends data

//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    char* remoteIp;
    char str[100];
    bool quit = false;

    // Verify arguments are good
    bool goodArguments = (argc == 2);
    if (goodArguments)
    {
        remoteIp = argv[1];
    }
    else
    {
        printf("usage: chat IPV4_ADDRESS\n");
        printf("  where:\n");
        printf("  IPV4_ADDRESS is address of the remote machine\n");
        exit(EXIT_FAILURE);
    }

    // Open listener port
    // TODO: Open local udp listener port
    // TODO: Show an error and exit if the port cannot be opened

    // Print heading so that sent and received messages are in different columns
    printf("Sent\t\t\t\t\t\tReceived\n");
    
    // Start chat loop until someone types a string starting with QUIT
    while(!quit)
    {
        // send string
        // TODO: Add code:
        //       if keyboard has been hit:
        //       - read a string from the keyboard and send
        //       - send the string to the remote port
        //       - leave while loop if a string starting with QUIT was sent

        // receive text
        // TODO: Add code:
        //       if data is received:
        //       - print to the right column
        //       - leave while loop if a string starting with QUIT is received
    }

    // TODO: Close udp listener port
    return EXIT_SUCCESS;
}
