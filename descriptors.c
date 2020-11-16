//Program sprawdza które deskryptory są otwarte (0-1023) i dla otwartych wypisuje flagi oraz tryb dostepu

#include <stdio.h>
#include <fcntl.h>

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

void print_access_mode(int flags){
    printf(" Access mode: ");
    int accessMode = flags & O_ACCMODE;
    if ( accessMode == O_RDONLY )
        printf( "O_RDONLY " );
    else if ( accessMode == O_WRONLY )
        printf( "O_WRONLY " );
    else if ( accessMode == O_RDWR )
        printf( "O_RDWR " );
}

void print_flags(int flags){
    printf(", flags: "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(flags));
    printf( " -");
    if (flags & O_CLOEXEC)
        printf(" O_CLOEXEC");
    if (flags & O_CREAT)
        printf(" O_CREAT");
    if (flags & O_DIRECTORY)
        printf(" O_DIRECTORY");
    if (flags & O_EXCL)
        printf(" O_EXCL");
    if (flags & O_NOCTTY)
        printf(" O_NOCTTY");
    if (flags & O_NOFOLLOW)
        printf(" O_NOFOLLOW");
    if (flags & O_TRUNC)
        printf(" O_TRUNC");
    if (flags & O_APPEND)
        printf(" O_APPEND");
    if (flags & O_ASYNC)
        printf(" O_ASYNC");
    if (flags & O_DSYNC)
        printf(" O_DSYNC");
    if (flags & O_NONBLOCK)
        printf(" O_NONBLOCK");
    if (flags & O_SYNC)
        printf(" O_SYNC");
}

void print_info(int des, int flags){
    printf( "Descriptor %d:", des );
    print_access_mode(flags);
    print_flags(flags);
    printf("\n");
}

int main() {
    int flags;
    for ( int i = 0; i < 1024; i++ ) {
        flags = fcntl( i, F_GETFL );
        if ( flags == -1 )
            continue; //deskryptor zamkniety
        else
            print_info(i, flags);
    }
    return 0;
}
