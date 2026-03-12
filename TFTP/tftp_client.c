#include "tftp.h"
#include "tftp_client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdio_ext.h>
#include <sys/wait.h>
#include <fcntl.h>

// Global Variables Declaration //
int mode = 1;
int pack_num = 1;
int main() 
{
	char command[256];
	tftp_client_t client;
	memset(&client, 0, sizeof(client));  // Initialize client structure //

	// Main loop for command-line interface
	while (1) {
		__fpurge(stdin);
		printf("MENU:\n1. Connect\n2. Put\n3. Get\n4. Mode\n5. Exit\nEnter the Command: ");
		// printf("tftp> ");
		fgets(command, sizeof(command), stdin);

		// Remove newline character
		command[strcspn(command, "\n")] = 0;

		// Process the command
		process_command(&client, command);
	}

	return 0;
}

// Function to process commands
void process_command(tftp_client_t *client, char *command) 
{
    
	if(strcmp(command,"connect") == 0) // Command is connect //
	{
        // Collecting IP address from the user //
		printf("Enter the server IP address:");
		scanf("%s",client->server_ip);

        //  Calling function to Validate the IP Address
		if(validate_server_ip(client->server_ip) == FAILURE)
		{
			printf("... Invalid IP address format ...\n");
			return;
		}
        // IP address valid its time to connect
		printf("... IP ADDRESS VALID  ... \n");
        // Calling the function to Connect to the server //
		connect_to_server(client,client->server_ip,PORT);
	}
    // If the Command is put  Read from the Client and Write in Server // 
	else if(strcmp(command,"put") == 0)
	{
		// printf("----------->PUT<----------------\n");
        // Creating the clild to exwcute the LS command to know what are the files present in Client.
		// printf(GREEN"");
		pid_t pid = fork();
		if(pid > 0)
		{
			wait(NULL);
		}
		else if(pid == 0)
		{
			// printf(GREEN"");
            // Executing the LS command //
			execlp("ls","ls",NULL);
		}

		printf("Enter the file name from the above files:");
		char filename[30];
		__fpurge(stdin);
        // Reading the file name from the user.//
		scanf("%s",filename);
        // Calling the put file function //
		put_file(client,filename);
	}
    // if the command is get Read from the Server and Write in Client //
	else if(strcmp(command,"get") == 0)
	{
		// printf("-----------> GET <----------------\n");
		printf("Enter the file name:");
		char filename[30];
		__fpurge(stdin);
        // Reading File name from the user //
		scanf("%s",filename);
        // Calling the get file function //
		get_file(client,filename);
	}
    // if the commad is mode //
	else if(strcmp(command,"mode") == 0)
	{
		// printf("-----------> MODE <----------------\n");
		printf("MENU:\n1. Normal\n2. Octet\n3. Netascii\n");
		printf("Enter the Option:");
        // Collecting the mode value //
		scanf("%d",&mode);
		printf("CURRENT MODE = %d\n",mode);
	}
    // if the command is exit //
	else if(strcmp(command,"exit") == 0)
	{
        printf("---------> Disconnecting to the Server <---------\n");
        // calling the disconnect function //
        disconnect(client);
		printf("-----------> PROGRAM EXITING <----------------\n");
        // exiting from the program ...//
		exit(0);
	}
    // Other than above commands all are invalid commands //
	else
	{
		printf("... INVALID OPERATION ...\n");
	}
}

// This function is to initialize socket with given server IP, no packets sent to server in this function
void connect_to_server(tftp_client_t *client, char *ip, int port) 
{
	// Creating  UDP socket //
	client->sockfd = socket(AF_INET,SOCK_DGRAM,0);

    // initlizing the values for members //
	client->server_addr.sin_family = AF_INET;
	client->server_addr.sin_port = htons(PORT);
	client->server_addr.sin_addr.s_addr = inet_addr(client->server_ip);

	// Set up server address //
}

void put_file(tftp_client_t *client, char *filename) 
{
	// Send WRQ request to server(Client should write to server) and send file 
    // checking the file is present or not //
	int fd = open(filename,O_CREAT | O_RDONLY | O_EXCL, 0644);
	if(fd != -1)
	{
		printf("... Please provide the valid file ...\n");
		return;
	}
    // storing the sizeof struct sockaddr_in in server_len variable.
	client->server_len = sizeof(client->server_addr);
    
    //Calling the Send the request function //  
	send_request(client->sockfd,client->server_addr,filename,WRQ);
	
    // send the request for the server //

}

void get_file(tftp_client_t *client, char *filename) 
{
	// Send RRQ to the Server (Client should read from server) and recive file 
	// printf("Send Request sent\n");

    //Calling the Send the request function // 
	send_request(client->sockfd,client->server_addr,filename,RRQ);

}

// Function to disconnect the client from the server //
void disconnect(tftp_client_t *client) 
{

	// close fd
    close(client->sockfd);

}

// Function for the sending the Request to server // 
void send_request(int sockfd, struct sockaddr_in server_addr, char *filename, int opcode)
{
	// Updating the packet number when you send the file.//
	pack_num = 1;
	tftp_packet pck;
	// clearing the garbage values //
	memset(&pck,0,sizeof(pck));
	// initilizing the variables
	pck.opcode = opcode;
	strcpy(pck.body.request.filename,filename);
	// printf("Filename: %s\n",pck.body.request.filename);
	pck.body.request.mode = mode;
	// sending request to the server //
	sendto(sockfd,&pck,sizeof(pck),0,(struct sockaddr *)&server_addr,sizeof(server_addr));
	// calling the receive_request function //
	receive_request(sockfd,server_addr,filename,opcode);

}

// Function for the recving the Request from the server //
void receive_request(int sockfd, struct sockaddr_in server_addr, char *filename, int opcode)
{
	tftp_packet pck;
	// clearing the garbage values //
	memset(&pck,0,sizeof(pck));
	socklen_t len = sizeof(server_addr);
	// receiving the acknowledgement //
	recvfrom(sockfd,&pck,sizeof(pck),0,(struct sockaddr *)&server_addr,&len);
	// Checking opcode for the condition //
	if(pck.opcode == ACK)
	{
		// Write request recived so sending the file
		if(pck.body.ack_packet.block_number == WRITE)
		{
			printf("READY TO SEND\n");
			send_file(sockfd,server_addr,len,filename);    
		}
		// Read request recived so receiveing the file
		else if(pck.body.ack_packet.block_number == READ)
		{
			printf("READY TO RECIVE\n");
			receive_file(sockfd,server_addr,len,filename);
		}
		else
		{
			return;
		}
	}
	// This is for ERROR
	else if(pck.opcode == ERROR)
	{
		printf("Error\n");
		printf("%s\n",pck.body.error_packet.error_msg);
	}
}


// validating the server IP address //
int validate_server_ip(char *ip_add)
{
	int count = 0;
    // Running the loop till end //
	for(int i = 0; ip_add[i]; i++)
	{
		if(ip_add[i] == '.')
		{
            // Incrementing the dot count.//
			count++;
		}
        // verifying all the characters is digits or not //
		if(!((ip_add[i] >= '0' && ip_add[i] <= '9') || ip_add[i] == '.'))
		{
			return FAILURE;
		}
	}
    // if count of dots is more than 3 then it is not correct IP address //
	if(count != 3)
	{
		return FAILURE;
	}
	return SUCCESS;
}
