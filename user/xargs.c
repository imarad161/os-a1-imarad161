#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[])
{
char buf[512];
char *args[MAXARG];
int i, n;
int count = 0;

if (argc < 2) {
fprintf(2, "usage: xargs <command> [args...]\n");
exit(1);
}

for (i = 1; i < argc; i++) {
args[count++] = argv[i];
}

if (count + 1 >= MAXARG) {
fprintf(2, "xargs: too many arguments\n");
exit(1);
}

n = 0;

while (read(0, &buf[n], 1) == 1) {
if (buf[n] == '\n') {
buf[n] ='\0';

args[count] = buf;
args[count + 1] = 0;

if (fork() == 0) {
exec(args[0], args);
fprintf(2, "xargs: exec failed\n");
exit(1);
}

wait(0);
n = 0;
} else {
n++;
if (n >= sizeof(buf) - 1) {
fprintf(2, "xargs: input too long\n");
exit(1);
}
}
}

if (n > 0) {
buf[n] = '\0';
args[count] = buf;
args[count + 1] = 0;

if (fork() == 0) {
exec(args[0], args);
fprintf(2, "xargs: exec failed\n");
exit(1);
}

wait(0);
}
exit(0);
}
