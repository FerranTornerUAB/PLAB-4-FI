#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Comprovem si s'ha passat un argument
    if (argc < 2) {
        perror("Error: Falten parametres\n");
        exit(-1);
    }

    // Obrim el fitxer amb els permisos adequats
    int fd = open(argv[1], O_WRONLY | O_CREAT, 0644);
    if (fd < 0) {
        perror("Error obrint el fitxer");
        exit(-1);
    }

    char buffer; // Variable on es guardarà el caràcter llegit de l'entrada estàndard.
    ssize_t bytes_read, bytes_written; // Variables per emmagatzemar els bytes llegits i escrits.

    // Llegim caràcters d'un en un de l'entrada estàndard
    while ((bytes_read = read(STDIN_FILENO, &buffer, 1)) > 0) {
        // Escrivim el caràcter a la sortida estàndard
        bytes_written = write(STDOUT_FILENO, &buffer, 1); // Escriu el caràcter al terminal.
        if (bytes_written < 0) {
            perror("Error escrivint a la sortida estàndard");
            close(fd); // Tanquem el fitxer abans de sortir.
            exit(-1);
        }

        // Escrivim el caràcter al fitxer
        bytes_written = write(fd, &buffer, 1); // Escriu el caràcter al fitxer.
        if (bytes_written < 0) {
            perror("Error escrivint al fitxer");
            close(fd); // Tanquem el fitxer abans de sortir.
            exit(-1);
        }
    }

    return 0;
}
