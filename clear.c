#include "main.h"

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