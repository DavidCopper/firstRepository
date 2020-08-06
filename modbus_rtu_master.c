#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <modbus.h>

int main(int argc, char *argv)
{
    uint16_t tab_reg[1024] = {0};
    memset(tab_reg, 0, 1024);
    modbus_t *ctx = NULL;

    int rc;
    int i;
    ctx = modbus_new_rtu("/dev/ttymxc2", 9600, 'N', 8, 1);
    if(ctx == NULL)
    {
        fprintf(stderr, "Unable to allocate libmodbus contex\n");
        return -1;
    }

    modbus_set_debug(ctx, 1);
    modbus_set_slave(ctx, 1);

    if(modbus_connect(ctx) == -1)
    {
        fprintf(stderr, "Connection failed:%s\n", modbus_strerror(errno));
        return -1;
    }

    while(1)
    {
        printf("\n--------------------\n");
        rc = modbus_read_registers(ctx, 0, 32, tab_reg);
        if(rc == -1)
        {
            fprintf(stderr, "%s\n", modbus_strerror(errno));
            return -1;
        }
    
    
    for(i = 0; i< 10; i++)
    {
        printf("reg[%d] = %d\n", tab_reg[i]);
    }
    sleep(1);
    }
    modbus_close(ctx);
    modbus_free(ctx);
    return 0;
}