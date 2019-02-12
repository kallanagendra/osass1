#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#define MAX 20
 

int top=-1,stack[MAX];
void push();
int pop();

void push(int val)
{
	
	
	if(top==MAX-1)
	{
		printf("\nStack is full!!");
	}
	else
	{
		top=top+1;
		stack[top]=val;
	}
}
 
int pop()
{
	int temp;
	if(top==-1)
	{
		printf("\nStack is empty!!");
	}
	else
	{
		temp = stack[top];
		top=top-1;
	}
	return temp;
}


int main (int argc, char *argv[]) {
 pid_t childpid = 0;
 int i, n, c;
 char errorstr[20];
 char *input = "input.dat", *output = "output.dat";
 FILE *infptr,*oufptr;
 int pids[20];
 
 
 
 while ((c = getopt (argc, argv, "hpi:o:")) != -1)
    switch (c)
      {
      case 'h':
		printf("\nOPTIONS :\n");
        printf("-h for HELP \n-p to test perror\n");
		printf("./logParse -i [input filr] -o output file\n");
        return 1;
      case 'p':
		snprintf(errorstr,20,"%s : Error ",argv[0]);
	    errno = ENOENT;
        perror(errorstr);
        return 1;
      case 'i':
        input = optarg;
        break;
	   case 'o':
        output = optarg;
        break;
      case '?':
        if (optopt == 'o')
			fprintf (stderr, "Option -%c requires an argument.\n", optopt);
		else if (optopt == 'i')
			fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        return 1;
      default:
        abort ();
      }

	infptr = fopen(input, "r");
    if(infptr == NULL)
    {
      fprintf(stderr,"File Open ERROR \n");
      exit(1);
    }
	oufptr = fopen(output, "w");
    if(oufptr == NULL)
    {
      fprintf(stderr,"File Open ERROR \n");
      exit(1);
    }
	fclose(oufptr);
	fscanf (infptr, "%d", &n);
	
	int status;
	int l;
 
 for (i = 0; i < n; i++)
 {
	 
 if ((pids[i] = fork()) == 0)
 {
	 
	  
	  char ignore[1024];

	  oufptr = fopen(output, "a");
	  int k;
	  for(k = 0; k < i*2 + 1; k++)
	  fgets(ignore, sizeof(ignore), infptr);
	  
	 
	  fscanf(infptr, "%d", &l);
	  //fprintf(stderr, "\nL :  %d",l);
	 
	 int m,num;
	 fprintf(oufptr," Child : %d : ",getpid());
	 //fprintf(stderr,"%s  ",':');
	 for (m = 0; m < l; m++)
	{
		fscanf (infptr, "%d", &num);
		push(num);
		
		
	}
	 for (m = 0; m < l; m++)
	{
		fprintf(oufptr,"%d ",pop());
		
	}
	fprintf(oufptr,"\n");
	fclose(oufptr);
	 exit(-1);
 }
 
 waitpid(pids[i], &status,0);
 }
 oufptr = fopen(output, "a");
 fprintf(oufptr," All Childern where : ");
for(i = 0; i< n; i++)
{
	fprintf(oufptr," %d ",pids[i]);
	
}
fprintf(oufptr," Parent : %d ",getpid());
 
 fclose(infptr);
 fclose(oufptr);
 return 0;
}
