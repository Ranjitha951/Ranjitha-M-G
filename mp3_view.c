/* Name : Ranjitha M G
   Dtae:28/10/2025
   Register number : 25021_227
Description : The MP3 Tag Reader and Editor is a C program used to read and modify ID3v2 tags in MP3 files.
It supports two operations: View to display tag information and Edit to update tag values.
This tool efficiently manages song details like Title, Artist, Album, Year, Genre, and Comment.*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mp3_header.h"

int convert_big_to_little_endian(unsigned char *bytes)
{
	return (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3];
}
// function to read mp3 ID3v2 tag data frome file
Status read_mp3_tag(const char *filename, ID3v2Tag *tag)
{
	FILE *fp = fopen(filename, "r");
	if(!fp)
	{
		perror("Error opening file");
		return READ_FAILURE;
	}
	fseek(fp, 10, SEEK_SET); // skip ID3 header
	while (!feof(fp))
	{
		unsigned char frame_header[10];
		if (fread(frame_header, 1, 10, fp) != 10)
			break;
		char frame_id[5] = {0};
		strncpy(frame_id, (char *)frame_header, 4);
		int frame_size = convert_big_to_little_endian(&frame_header[4]);
		if (frame_size < 1 || frame_size > 1024)
			break;
		fgetc(fp);               // skip encoding byte
	        char buffer[1024] = {0};
		fread(buffer, 1, frame_size - 1, fp);
		if (strcmp(frame_id, "TIT2") == 0)
			strncpy(tag->title, buffer, sizeof(tag->title));
		else if (strcmp(frame_id, "TPE1") == 0)
			strncpy(tag->artist, buffer, sizeof(tag->artist));
		else if (strcmp(frame_id, "TALB") == 0)
			strncpy(tag->album, buffer, sizeof(tag->album));
		else if (strcmp(frame_id, "TYER") == 0)
			strncpy(tag->year, buffer, sizeof(tag->year));
		else if (strcmp(frame_id, "TCON") == 0)
			strncpy(tag->content_type, buffer, sizeof(tag->content_type));
		else if (strcmp(frame_id, "COMM") == 0)
			strncpy(tag->composer, buffer, sizeof(tag->composer));
	}
	fclose(fp);
	return READ_SUCCESS;
}
void print_tag(const ID3v2Tag *tag)
{
	printf("It is mp3 file\n");
	printf("------------------------------------------------\n");
	printf("MP3 Tag Reader and Editor for ID3v2\n");
       printf("--------------------------------------------------\n");
       printf("Title          :         %s\n", tag->title); 
       printf("Artist         :         %s\n", tag->artist); 
       printf("Album          :         %s\n", tag->album);
       printf("Year           :         %s\n", tag->year); 
       printf("Music          :         %s\n", tag->content_type); 
       printf("Comment        :         %s\n", tag->composer); 
       printf("------------------------------------------------------\n");
}
