// Marcin Sarnecki 323034

#include <unistd.h>
#include "ip.h"
#include <iostream>
#include "router.h"

int main() {
    Router router; 
    router.Input();
    router.Create_Socket();
    router.Main_Loop();
    return 0;
}