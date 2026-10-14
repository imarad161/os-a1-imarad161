#include "kernel/types.h"
#include "kernel/uproc.h"
#include "user/user.h"

struct uproc procs[64];

char * 
state_name(int state)
{
switch (state) {
case 1:
return "used";
case 2:
return "sleeping";
case 3:
return "runnable";
case 4: 
return "running";
case 5:
return "zombie";
default:
return "unused";
}
}
int main(void)
{
int n = getprocs(procs, 64);

if (n < 0) {
printf("ps: getprocs failed\n");
exit(1);
}
printf("PID\tPPID\tSTATE\tSIZE\tNAME\n");

for (int i = 0; i < n; i++) {
printf("%d\t%d\t%s\t%lu\t%s\n",
procs[i].pid,
procs[i].ppid,
state_name(procs[i].state),
procs[i].sz,
procs[i].name);
}

exit(0);
}
