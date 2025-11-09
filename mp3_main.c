/* Name : Ranjitha M G
   Dtae:28/10/2025
   Register number : 25021_227
Description : The MP3 Tag Reader and Editor is a C program used to read and modify ID3v2 tags in MP3 files.
It supports two operations: View to display tag information and Edit to update tag values.
This tool efficiently manages song details like Title, Artist, Album, Year, Genre, and Comment.*/


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "mp3_header.h"

// function to print usage mesg
void print_usage(const char *program)
{
    printf("--------------------------------------------------------\n");
    printf("ERROR:  INVALID ARGUMENTS\n");
    printf("Usage:\n");
    printf("To view please pass like: ./a.out -v <mp3_filename>\n");
    printf("To Edit please pass like: ./a.out -e -<option> <new_value> <mp3_filename>\n");
    printf("---------------------------------------------------------------------\n");
}

// function to check if a file has .mp3 file
int has_mp3_extension(const char *filename)
{
    const char *dot = strrchr(filename, '.');
    return (dot && strcmp(dot, ".mp3") == 0);
}

// valid year
int is_valid_year(const char *str)
{
    for (int i = 0; str[i]; i++)
        if (!isdigit(str[i]))
            return 0;
    return strlen(str) == 4;
}

 // main function to handle command line arguments
int main(int argc, char *argv[])
{
	if(argc == 2 && strcmp(argv[1], "--help") == 0)
{
        printf("Usage : mp3tag -[taAyCc] 'value' file_name\n");
        printf("mp3tag -v\n");
        printf("-t  Modifies a TItle tag\n");
        printf("-a  Modifies a Artist tag\n");
        printf("-A  Modifies a Album tag\n");
        printf("-y  Modifies a Year tag\n");
        printf("-C  Modifies a Composer tag\n");
        printf("-c  Modifies a Comment tag\n");
	return 0;
}
    // ----- VIEW OPERATION -----
    if (argc == 3 && strcmp(argv[1], "-v") == 0)
    {
        if (!has_mp3_extension(argv[2]))
        {
            printf("Error: Only .mp3 files allowed!\n");
            return READ_FAILURE;
        }

        ID3v2Tag tag = {0};
        if (read_mp3_tag(argv[2], &tag) == READ_SUCCESS)
            print_tag(&tag);
        else
            printf("Failed to read tags from: %s\n", argv[2]);
    }

    // ----- EDIT OPTION WITHOUT TAG -----
    else if (argc == 3 && strcmp(argv[1], "-e") == 0)
    {
	     if (!has_mp3_extension(argv[2]))
        {
            printf("Error: Only .mp3 files allowed!\n");
            return READ_FAILURE;
        }
        printf("--------------------------Select edit option----------------------------\n");
        printf("Please pass tag arguments which you want to edit\n");
        printf("eg: ./a.out -e -t/-a/-A/-y/-C/-c new_content mp3filename\n");
        return READ_FAILURE;
    }

    // ----- EDIT OPERATION -----
    else if (argc == 5 && strcmp(argv[1], "-e") == 0)
    {
        printf("-------------------------Select Edit Option-----------------------------\n");

        const char *flag = argv[2];
        const char *new_val = argv[3];
        const char *file = argv[4];
        const char *frame = NULL;

        if (!has_mp3_extension(file))
        {
            printf("Error: Only .mp3 files allowed!\n");
            return READ_FAILURE;
        }

        if (strcmp(flag, "-t") == 0)
        {
            frame = "TIT2";
            printf("--------------------Select Title Change Option-------------------\n");
            printf("Title : %s\n", new_val);
        }
        else if (strcmp(flag, "-a") == 0)
        {
            frame = "TPE1";
            printf("--------------------Selected Artist Change Option-----------------\n");
            printf("Artist : %s\n", new_val);
        }
        else if (strcmp(flag, "-A") == 0)
        {
            frame = "TALB";
            printf("---------------------Selected Album Change Option-----------------\n");
            printf("Album : %s\n", new_val);
        }
        else if (strcmp(flag, "-y") == 0)
        {
            if (!is_valid_year(new_val))
            {
                printf("Year must be 4 digits.\n");
                return READ_FAILURE;
            }
            frame = "TYER";
            printf("----------------------Selected Year Change Option-------------------------\n");
            printf("Year : %s\n", new_val);
        }
        else if (strcmp(flag, "-C") == 0)
        {
            frame = "TCON";
            printf("------------------------Selected Music Change Option---------------------------\n");
            printf("Music : %s\n", new_val);
        }
	 else if (strcmp(flag, "-c") == 0)
        {
            frame = "COMM";
            printf("------------------------Selected Composer Chnage Option------------------------\n");
            printf("Composer : %s\n", new_val);
        }
        else
        {
            printf("Unknown option!\n");
            print_usage(argv[0]);
            return READ_FAILURE;
        }

        if (edit_mp3_tag(file, frame, new_val) == READ_SUCCESS)
            printf("----------------------%s Changed Successfully--------------------------\n", 
                   strcmp(flag, "-y") == 0 ? "Year" : "Tag");
        else
            printf("Failed to edit tag.\n");
    }

    // ----- INVALID ARGUMENTS -----
    else
    {
        print_usage(argv[0]);
        return READ_FAILURE;
  }
  

    return READ_SUCCESS;
}

