#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    if (argc != 3) {
        perror("Error: Nombre inadequat de paràmetres\n");
        exit(-1);
    }

    int fd1 = open(argv[1], O_RDONLY);
    if (fd1 < 0) {
        perror("Error obrint el fitxer 1");
        exit(-1);
    }

    int fd2 = open(argv[2], O_RDONLY);
    if (fd2 < 0) {
        perror("Error obrint el fitxer 2");
        exit(-1);  
    }
    int fitxers_iguals = 1;
    char buffer1, buffer2;
    ssize_t bytes_read1, bytes_read2;
    int bytes_counter = 0,lines_counter = 1;
    while ((bytes_read1 = read(fd1, &buffer1, 1)) > 0 && (bytes_read2 = read(fd2, &buffer2, 1)) > 0 && fitxers_iguals == 1) {
        bytes_counter ++;
        if (buffer1 =='\n') {
            lines_counter++;
        }
        if (buffer1 != buffer2) {
            printf("%s %s són diferents: byte %i, línia %i\n",argv[1], argv[2], bytes_counter, lines_counter);
            fitxers_iguals = 0;
        }

    }
    close(fd1);
    close(fd2);
}