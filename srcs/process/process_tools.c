#include <shell42.h>
#include "../includes/get_input.h"


void ft_process_tab_status(char *stat[6])
{
	stat[0] = "\x1B[00;31minitialised\x1B[00m";
	stat[1] = "\x1B[00;34mrunning fg\x1B[00m";
	stat[2] = "\x1B[00;34mrunning bg\x1B[00m";
	stat[3] = "\x1B[1;32mdone\x1B[00m";
	stat[4] = "\x1B[1;36msuspended\x1B[00m";
	stat[5] = "\x1B[00;31mkilled\033[00m";
}
