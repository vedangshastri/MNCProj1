	#include<stdio.h>
	#include<stdlib.h>
	#include<netdb.h>
	#include<string.h>
	#include<sys/types.h>
	#include<sys/socket.h>//inet_ntoa()
	#include<netinet/in.h>//inet_ntoa()
	#include<unistd.h>
	#include<arpa/inet.h> //inet_ntoa()
	#include<netinet/in.h>

	/*Function Declarations*/
	struct list
	{
		unsigned short id;
		char hostname[40];
		char IPAddr[4];
		unsigned short p_no;
		unsigned short c;  //Connected to the server
	};
	struct list lst[5];
	void REGISTER();
	void HELPF();
	void CREATOR();
	int SerSock, CliSock;					//Server and CLient Descriptors
		struct sockaddr_in SAddr;				//Structure for address of Self
		struct sockaddr_in CliAddr;				//Structure for client address
		char choice[25];
		unsigned short port;
		int CliLen,commLen;
		int i,spc_count=0,k;
		char SRbuf[1000],STbuf[1000];
		char CTbuf[1000],CRbuf[1000];
		char comm[40],para1[20],para2[20];							//1000 bytes buffer as mentioned in the project document
		int RecvMsgSz;
		int MsgLen,lcount=0;
		char ClAddr[4];
		void DISPLAY(struct in_addr Addr,unsigned short port);
		
	   				 		struct hostent *he;
	    					struct in_addr **addr_list;
							char s[30];
							
	   	void command(char cmd[])
	   	{
	   		commLen=strlen(cmd);
		
	   	for(i=0;i<strlen(cmd);i++)
							{cmd[i]=tolower(cmd[i]);}
						for(i=0;i<strlen(cmd);i++)
						{
							if(spc_count==0)
							{
							while(cmd[i]==' ')
							{
								spc_count++;
								strncpy(choice,cmd,i);
								k=i+1;
								
								break;
							}
						  	
							}
							else
							
						    {
							while(cmd[i]==' ')
								{	
									spc_count++;
									strncpy(para1,cmd+k,i-k);
									
									strncpy(para2,cmd+i+1,commLen-i-1);
									break;
								}

							}
						}
						if(spc_count==0)
						{
							strcpy(choice,cmd);
						}
						else
						{if(spc_count==1)
							strncpy(para1,cmd+k,i-k);

						}
						spc_count=0;
	   	}
	int main(int argc, char *argv[])
	{
		


		memset(comm,0,40);
		memset(para1,0,20);
		memset(para2,0,20);
		for(i=0;i<5;i++)
		{
			memset(&lst[i],0,sizeof(struct list));
		}

						lst[0].id=1;
						strcpy(lst[0].hostname,"timberlake.cse.buffalo.edu");

						
						lst[0].c=1;
		
		//Create Socket
			
			if(argc!=3)
			{
				perror("Number of arguments should be 2... Try again!!");
				exit(1);
			}
			if (strcasecmp(argv[1],"s")==0)
			{


				SerSock=socket(AF_INET,SOCK_STREAM,0);
				if(SerSock<0)
				{
					perror("Failed to create Server socket");
					exit(1);
				}
				printf("\nServer Side");		
				printf("\nSocket Created");
				memset(&SAddr,0,sizeof(SAddr));//Setting 0s thorughout

				port=atoi(argv[2]);
				SAddr.sin_family=AF_INET;
				SAddr.sin_port=htons(port);
				SAddr.sin_addr.s_addr=htonl(INADDR_ANY);	//Assigning values to structaddr_in
				lst[0].p_no=port;
				//Bind port number to IP addr
				if(bind(SerSock,(struct sockaddr *) &SAddr, sizeof(SAddr))<0)
				{
					perror("Binding failed.");
					exit(1);
				}
				printf("\nBinding completed");
				for(;;)
				{
				//Listen to the port
				if(listen(SerSock,5)<0)
				{
					perror("Listening failed");
					exit(1);
				}
				printf("\nListening completed");
				
				//Accept phase
				
					CliLen=sizeof(CliAddr);
					
					if((CliSock=accept(SerSock,(struct sockaddr*) &CliAddr, &CliLen))<0)
					{
					 	perror("Acceptance failed");
					}
					else
					{
						if( (RecvMsgSz=recv(CliSock,SRbuf,sizeof(SRbuf),0) )<0)
						{
							perror("\nReceive fail");
						}
						else
						{	printf("\nAttemptReceiving.....%d",RecvMsgSz);
							if(RecvMsgSz==0)
							{
								printf("\nConnection closed");
							}
							else
							{
								strcpy(ClAddr,inet_ntoa(CliAddr.sin_addr));

								printf("\nMessage received: %d bytes capacity from %s\n ",RecvMsgSz,ClAddr);
								

							}
							setvbuf (stdout, NULL, _IONBF, 0);
							
							command(SRbuf);
							printf("\nMessage %s %s",SRbuf,choice);
							if(strcmp(choice,"register")==0)
							{
									REGISTER();
									
							}
							

						}
						close(CliSock);
					}
				}

			}
			else
			{
				if(strcasecmp(argv[1],"c")==0)
				{
					
					
					CliSock=socket(AF_INET,SOCK_STREAM,0);
							if(CliSock<0)
							{
								perror("Failed to create client socket");
								exit(1);

							}
							printf("Socket Created\n");
							memset(&CliAddr,0,sizeof(CliAddr));//Setting 0s thorughout

							port=atoi(argv[2]);
							CliAddr.sin_family=AF_INET;
							CliAddr.sin_port=port;
							CliAddr.sin_addr.s_addr=htonl(INADDR_ANY);
								while(1)
						{
								scanf("%s",s);
		   						if ((he = gethostbyname(s)) == NULL) {  // get the host info
		       					 herror("gethostbyname");
		        				return 2;
		    					}

		    // print information about this host:

		    printf("Given Name: %s\n", he->h_name);
		    printf("Associated IP addresses: ");
		    addr_list = (struct in_addr **)he->h_addr_list;
		    for(i = 0; addr_list[i] != NULL; i++) {
		        printf("%s ", inet_ntoa(*addr_list[i]));
		    }
			printf("\n");
			char SeAddr[4];
			strcpy(SeAddr,inet_ntoa(*addr_list[0]));
			printf("\n%s\n",SeAddr);
								
								SAddr.sin_family=AF_INET;
								SAddr.sin_port=htons(port);
								inet_aton(SeAddr,&SAddr.sin_addr);

			if(connect(CliSock,(struct sockaddr *) &SAddr,sizeof(SAddr))<0)
			{
				perror("\nConnection failed");
				exit(1);
			}
							printf("\nClient side: Enter message ");
							scanf(" %[^\n]s",CTbuf);
							MsgLen=sizeof(CTbuf);
							//printf("%d %s",MsgLen,CTbuf);
							if(send(CliSock,CTbuf,MsgLen,0)<0)
							{
								perror("Sending failed");
							}
							MsgLen=sizeof(CRbuf);
							if((MsgLen=recv(CliSock,CRbuf,MsgLen,0))<0)
							{
								perror("Receive problem");
							}
							if(MsgLen==0)
							{
								printf("\nConnection Closed");
							}
							else{
								printf("\n%sabcd\n",CRbuf);
							}
							
							close(CliSock);
					printf("\n[PA]$ ");
					scanf("%[^\n]s",comm);

							
							
			commLen=strlen(comm);
			
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
										spc_count++;
										strncpy(para1,comm+k,i-k);
										
										strncpy(para2,comm+i+1,commLen-i-1);
										break;
									}

								}
							}
							if(spc_count==0)
							{
								strcpy(choice,comm);
							}
							else
							{if(spc_count==1)
								strncpy(para1,comm+k,i-k);

							}
							spc_count=0;

								

							if(strcmp(choice,"help")==0)
									HELPF();
								
							
							/*if(strcmp(choice,"creator")==0)
								CREATOR();
							
							if(strcmp(choice,"display")==0)
								DISPLAY(&CliAddr.sin_addr,port);*/

							//if(strcmp(choice,"register")==0)
								
							/*if(strcmp(choice,"connect")==0)
								CONNECT();
							if(strcmp(ch,"list")==0)
								
							if(strcmp(ch,"terminate")==0)
								if(strcmp(ch,"quit")==0)
									if(strcmp(ch,"get")==0)
										if(strcmp(ch,"put")==0)
											if(strcmp(ch,"sync")==0)
								
								
						else
						{
							printf("\nBad Command... Type 'Help' for command list");
						

						}*/	
						}
				}
				else
				{
					printf("\nInvalid Choice");
				}
			}
				
		}

		/*Function Definitions*/

		void CREATOR()
		{
			
			printf("\n\n\t\t\tName: Vedang Shastri");
			printf("\n\t\t\tUBIT Name: vedangsh");
			printf("\n\t\t\tUBemail: vedangsh@buffalo.edu");
		}
		void REGISTER()
		{				struct hostent *tmp; 
							
							++lcount;
							lst[lcount].id=lcount;
							tmp=gethostbyaddr(&CliAddr.sin_addr,sizeof(CliAddr.sin_addr),AF_INET);
							strcpy(lst[lcount].hostname,tmp->h_name);
							lst[lcount].IPAddr;
							
							lst[lcount].c=1; //Connected to the server
							strcpy(lst[lcount].IPAddr,inet_ntoa(CliAddr.sin_addr));
							for(i=0;i<5;i++)
							{
							snprintf(CTbuf,sizeof(CTbuf),"List from Server: %u  %s  %s  %u ",lst[i].id,lst[i].hostname,lst[i].IPAddr,lst[i].p_no);
							setvbuf (stdout, NULL, _IONBF, 0);
							
							if(send(SerSock,CTbuf,sizeof(CTbuf),0)<0)
								perror("Sending error");
							memset(CTbuf,0,sizeof(CTbuf));
							}
		}
		void DISPLAY(struct in_addr Addr,unsigned short port)
		{
			printf("\n\nThis process is running on %s address.\nPort Number: %u ",inet_ntoa(Addr),port);
		}
		void HELPF()
		{
			
		}
