#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
int main() {
	while(1) {
		int pid = fork();
		if(pid) {
			int status;
			waitpid(pid, &status, 0);
			printf("Child returned %d\n", WEXITSTATUS(status));
		}
		else {
			char* buff = malloc(2097152);
			char** args = malloc(999999 * sizeof(char*));
			fgets(buff, 2097152, stdin);
			int argc = 0;
			args[argc++] = strtok(buff, " \n");
			while(args[argc++] = strtok(NULL, " \n"));
			execvp(args[0], args);
			printf("Still alive, execvp failed with return code %d\n", errno);
			return 0;
		}
	}
}
