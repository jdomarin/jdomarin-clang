//Memory Management Schemes(First, Best & Worst Fit)

#include <stdio.h>
#include <curses.h>

#define maxm 100
#define minm 0

struct memory
{
int blknm,blksz,pro,flag;
}mem[10];

void ff();

void bf();

void wf();

void show();

int noblk, nopro, prosz[10];

int main(int argc, char* argv[])
{
int i;
printf("Enter the no.of memory blocks : ");
scanf("%d",&noblk);
for(i=0;i<noblk;i++)
{
printf("Mem. size of block %d : ",i+1);
scanf("%d",&mem[i].blksz);
}
printf("No.of Process : ");
scanf("%d",&nopro);
for(i=0;i<nopro;i++)
{
printf("Mem. size of Pro.%d : ", i+1);
scanf("%d",&prosz[i]);
}
printf("\ntFirst Fit\n\t=========\n");
ff();
printf("\n\tBest Fit\n\t========\n");
bf();
printf("\n\tWorst Fit\n\t=========\n");
wf();
getch();

return 0;
}


void ff()

{
int i, j;
for(i=0;i<10;i++)
mem[i].flag=0;
for(i=0;i<nopro;i++) {
	for(j=0;j<noblk;j++) {
		if(mem[j].flag != 1 && prosz[i]<=mem[j].blksz)
		{
			mem[j].pro = i+1;
			mem[j].flag = 1;
			break;
		}
	}
}
show();
}


void bf()
{
int i,j,k,min;
for(i=0;i<10;i++)
	mem[i].flag = 0;
for(i=0;i<nopro;i++)
{
min = maxm;
for(j=0;j<noblk;j++) {
	if(mem[j].blksz >= prosz[i] && mem[j].flag != 1)
{
		if(min>(mem[j].blksz-prosz[i]))
		{
			min = mem[j].blksz - prosz[i];
			k=j;
		}
		mem[k].pro = i+1;
		mem[k].flag = 1;
		}
	}
	show();
	}
}

void wf()
{
int i,j,k,max;
for(i=0;i<10;i++)
	mem[i].flag = 0;
for(i=0;i<nopro;i++)
{
max = minm;
for(j=0;j<noblk;j++) {
	if(mem[j].blksz >= prosz[i] && mem[j].flag != 1) {
		if(max<(mem[j].blksz-prosz[i])) {
			max = mem[j].blksz - prosz[i];
			k=j;
			}
		mem[k].pro = i+1;
		mem[k].flag = 1;
		}
	show();
	}
}
}

void show()
{
int i;
printf("\nMemory Block Process\nBlock Size Name\n");
for(i=0;i<noblk;i++)
	printf("%d\t%d\t%d\n",i+1,mem[i].blksz,mem[i].pro);
}
