#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char *argv[]) {
  int fd[2];
  char message[] = "Hello!";
  char buffer[30];
  if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    int rc = fork();
    if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    close (fd[1]);
    ssize_t bytes_read = read(fd[0], buffer, sizeof(buffer));
    if (read > 0) {
        printf("Parent received: %.*s (pid:%d)\n", (int)bytes_read, buffer,(int) getpid());
        
    } else {
            perror("read");
    }
        
    close(fd[0]);
} else {
        close(fd[0]);  
        ssize_t bytes_written = write(fd[1], message, strlen(message) + 1);
        if (bytes_written > 0) {
            printf("child sent: %.*s (pid:%d) \n", (int)bytes_written, message,(int) getpid());
        } else {
            perror("write");
        }

        close(fd[1]);

    
        wait(NULL);
    }

    return 0;
}