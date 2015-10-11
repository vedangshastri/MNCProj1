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
void HELPF();
void CREATOR();
int SerSock, CliSock;					//Server and CLient Descriptors
	struct sockaddr_in SAddr;				//Structure for address of Self
	struct sockaddr_in CliAddr;				//Structure for client address
	char choice[25];
	unsigned short port;
	int CliLen,commLen;
	int i,spc_count=0,k;
	char buf[1000];
	char comm[30],para1[20],para2[20];							//1000 bytes buffer as mentioned in the project document
	int RecvMsgSz;
	int MsgLen;
	char ClAddr[4];
int main(int argc, char *argv[])
{
	


	memset(comm,0,30);
	memset(para1,0,20);
	memset(para2,0,20);

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
			SAddr.sin_port=port;
			SAddr.sin_addr.s_addr=htonl(INADDR_ANY);	//Assigning values to structaddr_in
			
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
					if( (RecvMsgSz=recv(CliSock,buf,10,0) )<0)
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
							printf("\nMessage received: %d bytes from %s",RecvMsgSz,ClAddr);
							printf("\n");

						}
						printf("\nMessage %s",buf);

					}
					close(CliSock);
				}
			}

		}
		else
		{
			if(strcasecmp(argv[1],"c")==0)
			{
				while(1)
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

						  int i;
   				 struct hostent *he;
    				struct in_addr **addr_list;
						char s[30];
						scanf("%s",s);
   
    if ((he = gethostbyname(s)) == NULL) {  // get the host info
        herror("gethostbyname");
        return 2;
    }

    // print information about this host:
    printf("Official name is: %s\n", he->h_name);
    printf("    IP addresses: ");
    addr_list = (struct in_addr **)he->h_addr_list;
    for(i = 0; addr_list[i] != NULL; i++) {
        printf("%s ", inet_ntoa(*addr_list[i]));
    }
	printf("\n");
	char SeAddr[4];
	strcpy(SeAddr,inet_ntoa(*addr_list[0]));
	printf("\n%s\n",SeAddr);
						
						SAddr.sin_family=AF_INET;
						SAddr.sin_port=port;
						inet_aton(SeAddr,&SAddr.sin_addr);



				
					printf("\nClient side: Enter message");
					scanf("%s",buf);

					if(connect(CliSock,(struct sockaddr *) &SAddr,sizeof(SAddr))<0)
					{
						perror("\nConnection failed");
						exit(1);
					}
					MsgLen=sizeof(buf);
					if(send(CliSock,buf,sizeof(buf),0)<0)
					{
						perror("Sending failed");
					}

					printf("\n%s\n",buf);
					close(CliSock);
			/*printf("\nEnter command ");
			scanf("%[^\n]s",comm);*/

					
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

						

					if(strcmp(choice,"help")==0)
							HELPF();
						
					
					/*if(strcmp(choice,"creator")==0)
						CREATOR();
					
					if(strcmp(choice,"display")==0)
						DISPLAY();*/

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
	{


	}
	void HELPF()
	{
		int help_choice,a=0;
		printf("\n\t\t\tHelp Menu");
		printf("\nFollowing commands are available for you");
		printf("\n1.HELP\n2.CREATOR\n3.DISPLAY\n4.REGISTER\n5.CONNECT\n6.LIST\n7.TERMINATE\n8.GET\n9.QUIT\n10.PUT\n11.SYN\n0.EXIT");
		while(1)
		{	
		printf("\n\nEnter a number for help about that command\n");
		scanf("%d",&help_choice);
		
		switch(help_choice)
		{
			case 0:
				return ;
			case 1:
				printf("\nHELP");
				printf("\nDisplays help information about all the commands and a menu driven prompt");
				break;
			case 2:
				printf("\nCREATOR");
				printf("\nDisplays information about creator- Full Name, UBIT Name and UB email address");
				break;
			case 3:
				printf("\nDISPLAY");
				printf("\nDisplays the IP address of this process, and the port on which this process is listening for incoming connections");
				break;
			case 4:
				printf("\nREGISTER");
				printf("\nSYNTAX: REGISTER <server IP><port number>");
				printf("\n\nThe REGISTER command takes 2 arguments.");
				printf("The first argument is the IP address of the server and the second argument is the listening port of the server.");
				printf("\n\nThis command is used by the client to register itself with the server and to get the IP and listening port numbers");
				printf("\nof all other peers currently registered with the server.");
				printf("\nThe first task of every host is to register itself with the server by sending the server a TCP message containing its listening port number.");
				printf("\nThe server maintains a list of the IP address and the listening ports of all the registered clients.");
				printf("This list is called as 'Server-IP-List'.\n Whenever a new host registers or a registered host exits, the server updates its Server-IP-List appropriately");
				printf("and then sends this updated list to all the registered clients.");
				printf("\nHosts always listen to such updates from the server and update their own local copy of the available peers."); 
				printf("\nAny such update which is received by the host is be displayed by the client.");
				printf("\nIf the host closes the TCP connection with the server for any reason then that host should be removed from the “Server-IP-List” and the server should promptly inform all the remaining hosts.");
				break;
			case 5:
				printf("\nCONNECT");
				printf("\nSYNTAX: CONNECT <destination> <port no>");
				printf("\nThis command is used by the client to connect to another registered client. The destination IP address must be present in the server IP List.");
				break;
			case 6:
				printf("\nLIST");
				printf("\nDisplays a numbered list of all the connections this process is part of.");
				printf("\n\nThis numbered list will include connections initiated by this process and connections initiated by other processes. The output displays the hostname, IP address and the listening port of all the peers the process is connected to. Also, this should include the server details.");
				break;
			case 7:
				printf("\nTERMINATE");
				printf("\nSYNTAX: TERMINATE <connetion id>");
				printf("\n\nThis command will terminate the connection listed under the specified number when LIST is used to display all connections. Messages will be sent to both the nodes indiaction termination.");
				break;
			case 8:
				printf("\nGET");
				printf("\nSYNTAX: GET <connection id> <file>");
				printf("\n\nThis command will download a file from one host specified in the command.");
				break;
			case 9:
				printf("\nQUIT");
				printf("\nClose all connections and terminate this process. When a host exits, the server unregisters the host and sends the updated “Server-IP-List” to all the clients.");
				printf("Other hosts on receiving the updated list from the server should display the updated list.");
				break;
			case 10:
				printf("\nPUT");
				printf("\nSYNTAX:PUT <connection id> <file name>");
				printf("\nRequests a file from a host other than a server. Request to server is not allowed");
				break;
			case 11:
				printf("\nSYNC");
				printf("\nThis command will make sure that all peers are up-to-date with their CONNECTED peers.");
				break;
			deafult:
				printf("This is not a valid choice");
		}
		}
		
	}
