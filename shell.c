#include <stdio.h>
#include<string.h>

int main()
{
    int i,k,spc_count=0;
    char comm[20],para1[20],para2[20],choice[20];
    scanf("%[^\n]s",comm);
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
							printf("%s",choice);
							break;
						}
					  
						}
						else
						
					    {
						while(comm[i]==' ')
							{
								strncpy(para1,comm,3);
								strncpy(para2,comm,2);
								break;
							}

						}
					}
                    printf("\n%s\t%s\t%sd",choice,para1,para2);
}







