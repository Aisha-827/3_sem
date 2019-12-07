#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	int txd[2];
	int rxd[2];
} dpipe_t;

int main() {
	dpipe_t dpipe;
	pipe(dpipe.txd);
	pipe(dpipe.rxd);
	int pid = fork();
	if(pid) {
		close(dpipe.txd[0]);
		close(dpipe.rxd[1]);
		while(1) {
			char msg[4096];
			fgets(msg, 4096, stdin);
			write(dpipe.txd[1], msg, 4096);
			char response[4096];
			read(dpipe.rxd[0], response, 4096);
			printf("Child sent: %s\n", response);
		}
	}
	else {
		close(dpipe.txd[1]);
		close(dpipe.rxd[0]);
		while(1) {
			char msg[4096];
			read(dpipe.txd[0], msg, 4096);
			char response[4096];
			sprintf(response, "ACK. LEN=%d", (int)strlen(msg) - 1);
			write(dpipe.rxd[1], response, 4096);
		}
	}
}
