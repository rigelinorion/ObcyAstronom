#include "includes.inc"
#include "utils.h"

extern char program_path[255];

void _system(char* cmdline){
    char buffer[255];
    sprintf(buffer, "%s%s", program_path, cmdline);
    system(buffer);
}
void _system_sh(char* cmdline){
    char buffer[255];
    sprintf(buffer, "sh %s%s", program_path, cmdline);
    system(buffer);
}
void _system_su_sh(char* cmdline){
    char buffer[255];
    sprintf(buffer, "sudo sh %s%s", program_path, cmdline);
    system(buffer);
}
void _system_suh(char* cmdline){
    char buffer[255];
    sprintf(buffer, "sudo %s%s", program_path, cmdline);
    system(buffer);
}