
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>


main() {

    FILE *fp= NULL;
    pid_t pid, sid;

    // Create child process
    pid = fork();

    // Indication of fork() failure
    if (pid < 0) {
        perror(" fork() failed: ");
        exit(1);
    }
    // PARENT PROCESS. Need to kill it.
    if (pid > 0) {
        printf("CHILD_PID: %d\n", pid);
        exit(0);
    }

    // CHILD PROCESS 
    // unmask the file mode (ngl, idk why)
    umask(0);

    //set new session
    sid = setsid();
    if(sid < 0) {
        perror(" setsid() failed: ");
        exit(1);
    }
    
    // Change the current working directory to root.
    chdir("/");
    // Close standart streams
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // Open a log file in write mode.
    fp = fopen ("log.txt", "w+");
    while (1) {
        sleep(1);
        fprintf(fp, "Logging info...\n");
        fflush(fp);

        // script functionality here
    }

    fclose(fp);
    return (0);

}
