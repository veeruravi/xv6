#include "types.h"
#include "stat.h"
#include "user.h"
int main()
{
	int x,y;
	int pid = fork();
	if(pid==0)
	{
		int v=100000000;
		while(v>0)
		{
			v--;
		}
	}
	waitx(&x,&y);
	printf(1,"%d %d\n",x,y);
	exit();
}
