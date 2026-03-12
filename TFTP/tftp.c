/* Common file for server & client */

#include "tftp.h"

extern int mode;
extern int pack_num;

// Function for the Sending file //
void send_file(int sockfd, struct sockaddr_in client_addr, socklen_t client_len, char *filename) 
{

	// Opening the file in read mode //
	int fd = open(filename,O_RDONLY);
	tftp_packet pck;
	// Clearing the values //
	memset(&pck,0,sizeof(pck));
	// for mode 1 - NORMAL MODE //
	if(mode == 1)
	{
		int bytes;
		do
		{
			// Clearing the DATA //
			memset(&pck,0,sizeof(pck));
			// reading the bytes //
			bytes = read(fd,pck.body.data_packet.data,512);
			pck.body.data_packet.block_number = pack_num;
			// declaring the temp variable for backup //
			tftp_packet temp;
			// copying data to temp variable //
			memcpy(&temp,&pck,sizeof(pck));
			pck.opcode = DATA;
			// sending the bytes untill receive all the bytes //
			do
			{
				// sending the bytes //
				sendto(sockfd,&temp,sizeof(temp),0,(struct sockaddr *)&client_addr,client_len);
				printf(" Bytes READ: %d\n",bytes);
				memset(&pck,0,sizeof(pck));
				// receiveing the acknowledgement //
				recvfrom(sockfd,&pck,sizeof(pck),0,(struct sockaddr *)&client_addr,&client_len);
				// checking the condition //
			} while (bytes != pck.body.ack_packet.block_number);
			// incrementing the Packet number //
			pack_num++;

		} while (bytes == 512);      

	}
	else if(mode == 2)
	{
		int bytes;
		do
		{
			// Clearing the DATA //
			memset(&pck,0,sizeof(pck));

			// reading the bytes //
			bytes = read(fd,pck.body.data_packet.data,1);
			pck.body.data_packet.block_number = pack_num;
			// declaring the temp variable for backup //
			tftp_packet temp;
			// copying data to temp variable //
			memcpy(&temp,&pck,sizeof(pck));
			pck.opcode = DATA;
			// sending the bytes untill receive all the bytes //
			do
			{
				// sending the bytes //
				sendto(sockfd,&temp,sizeof(temp),0,(struct sockaddr *)&client_addr,client_len);
				printf(" Bytes READ: %d\n",bytes);
				memset(&pck,0,sizeof(pck));
				// receiveing the acknowledgement //
				recvfrom(sockfd,&pck,sizeof(pck),0,(struct sockaddr *)&client_addr,&client_len);
				// checking the condition //
			} while (bytes != pck.body.ack_packet.block_number);
			// incrementing the Packet number //
			pack_num++;

		} while (bytes == 1);      

	}
	else if(mode == 3)
	{
		int bytes;
		do
		{
			// Clearing the DATA //
			memset(&pck,0,sizeof(pck));
			char buff[512];
			memset(buff,0,512);
			pck.body.data_packet.block_number = pack_num;
			int i;
			char ch;
			// reading the bytes //
			for (i=0;i<512 && read(fd,&ch,1);)
			{
				if(ch == '\n')
				{
					buff[i++] = '\r';
				}
				buff[i++] = ch;
			}
			memcpy(pck.body.data_packet.data,buff,i);
			// declaring the temp variable for backup //
			tftp_packet temp;
			// copying data to temp variable //
			memcpy(&temp,&pck,sizeof(pck));
			bytes = i;
			pck.opcode = DATA;
			// sending the bytes untill receive all the bytes //
			do
			{
				// sending the bytes //
				sendto(sockfd,&temp,sizeof(temp),0,(struct sockaddr *)&client_addr,client_len);
				printf(" Bytes READ: %d\n",bytes);
				memset(&pck,0,sizeof(pck));
				// receiveing the acknowledgement //
				recvfrom(sockfd,&pck,sizeof(pck),0,(struct sockaddr *)&client_addr,&client_len);
				// checking the condition //
			} while (bytes != pck.body.ack_packet.block_number);
			// incrementing the Packet number //
			pack_num++;

		} while (bytes == 512);	
	}
	printf("... FILE SENT SUCCESSFULLY ...\n");
	// closeing the file //
	close(fd);
}

// Function for reciving the file //
void receive_file(int sockfd, struct sockaddr_in client_addr, socklen_t client_len, char *filename) 
{

	// Opening the file 
	int fd = open(filename,O_CREAT | O_WRONLY | O_EXCL ,0644);

	if(fd == -1)
	{
		// creating and opening the file //
		fd = open(filename, O_WRONLY | O_TRUNC );
	}
	tftp_packet pck;
	int bytes;

	// For Mode 1 and 3 (Normal and netascii)
	if(mode == 1 || mode == 3)
	{
		// int bytes;
		do
		{ 
			memset(&pck,0,sizeof(pck));
			// Reciving the data //
			recvfrom(sockfd,&pck,sizeof(pck),0,(struct sockaddr *)&client_addr,&client_len);
			// writing to the file //
			bytes = write(fd,pck.body.data_packet.data,strlen(pck.body.data_packet.data));
			printf(" Bytes Written: %d and Pack Number is %d\n",bytes,pck.body.data_packet.block_number);
			memset(&pck,0,sizeof(pck));
			pck.body.ack_packet.block_number = bytes;
			pck.opcode = ACK;
			// sending the ACK //
			sendto(sockfd,&pck,sizeof(pck),0,(struct sockaddr *)&client_addr,client_len);

		} while (bytes == 512);
	}
	else if(mode ==  2)
	{
		// int bytes;
		do
		{ 
			memset(&pck,0,sizeof(pck));
			// Reciving the data //
			recvfrom(sockfd,&pck,sizeof(pck),0,(struct sockaddr *)&client_addr,&client_len);
			// writing to the file //
			bytes = write(fd,pck.body.data_packet.data,strlen(pck.body.data_packet.data));
			printf(" Bytes Written: %d and Pack Number is %d\n",bytes,pck.body.data_packet.block_number);
			memset(&pck,0,sizeof(pck));
			pck.body.ack_packet.block_number = bytes;
			pck.opcode = ACK;
			// sending the ACK //
			sendto(sockfd,&pck,sizeof(pck),0,(struct sockaddr *)&client_addr,client_len);

		} while (bytes == 1);
	}
	// Closing the File //
	close(fd);
	printf("... FILE RECEIVED SUCCESSFULLY ...\n");
}
