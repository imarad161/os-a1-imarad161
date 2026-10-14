#include "kernel/types.h"
#include "kernel/sysinfo.h"
#include "user/user.h"

int main (void)
{
struct sysinfo info;

if (sysinfo(&info) < 0) {
printf("sysinfo failed\n");
exit(1);
}

printf("Free memory: %d bytes\n", (int)info.freemem);
printf("Number of processes: %d\n", (int)info.nproc);

exit(0);

}
