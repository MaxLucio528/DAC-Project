#include "main.h"

// Function that clears the terminal screen.
void clear(){
    #ifndef POWERSHELL
        system("clear");
    #else
        #ifndef WINDOWS
            system("cls");
        #else
            system("clear");
        #endif
    #endif
}