#include <stdio.h>
#include<string.h>

int main()
{
    int i,k,spc_count=0,j;
    char comm[30],para1[20],para2[20],choice[20];
    scanf("%[^\n]s",comm);
	j=strlen(comm);
	memset(para1,0,20);
	memset(para2,0,20);
	memset(choice,0,20);
   	for(i=0;i<=strlen(comm);i++)
						{comm[i]=tolower(comm[i]);}
					for(i=0;i<strlen(comm);i++)
					{
						if(spc_count==0)
						{
						while(comm[i]==' ')
						{
							spc_count++;
							strncpy(choice,comm,i);
							k=i+1;
							
							break;
						}
					  	
						}
						else
						
					    {
						while(comm[i]==' ')
							{
								strncpy(para1,comm+k,i-k);
								
								strncpy(para2,comm+i+1,j-i-1);
								break;
							}

						}
					}
                    printf("\n%s_%s_%s\n",choice,para1,para2);
}
