#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>

char readbuf[10];
int writebuf = 9999;

int main()
{
    setvbuf(stdout, (char *)NULL, _IONBF, 0);
    int fd = open("/dev/vuart", O_RDWR);
    assert(fd >= 0);
    int ret;
    ret = read(fd, &readbuf, sizeof(readbuf));
    assert(ret >= 0);
    fflush(stdout);
    printf("read %d : %s\n", ret, readbuf);
    fflush(stdout);
    sleep(1);
    printf("write: %d\n", writebuf);
    ret = write(fd, &writebuf, sizeof(writebuf));
    assert(ret >= 0);
    ret = close(fd);
    assert(ret >= 0);
    return 0;
}