/* Name : Ranjitha M G
   Dtae:28/10/2025
   Register number : 25021_227
Description : The MP3 Tag Reader and Editor is a C program used to read and modify ID3v2 tags in MP3 files.
It supports two operations: View to display tag information and Edit to update tag values.
This tool efficiently manages song details like Title, Artist, Album, Year, Genre, and Comment.*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "mp3_header.h"

void write_little_endian_to_big(int value, unsigned char *bytes)
{
    bytes[0] = (value >> 24) & 0xFF;
    bytes[1] = (value >> 16) & 0xFF;
    bytes[2] = (value >> 8) & 0xFF;
    bytes[3] = value & 0xFF;
}

Status edit_mp3_tag(const char *filename, const char *frame_id, const char *new_value)
{
    FILE *fp = fopen(filename, "rb");
    if (!fp)
    {
        perror("Error opening original file");
        return READ_FAILURE;
    }

    // Load entire file into memory
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    rewind(fp);

    unsigned char *buffer = (unsigned char *)malloc(file_size);
    if (!buffer)
    {
        fclose(fp);
        return READ_FAILURE;
    }

    fread(buffer, 1, file_size, fp);
    fclose(fp);

    int tag_size = ((buffer[6] & 0x7F) << 21) | ((buffer[7] & 0x7F) << 14) |
                   ((buffer[8] & 0x7F) << 7) | (buffer[9] & 0x7F);

    long pos = 10; // Skip header
    while (pos + 10 < file_size)
    {
        char id[5] = {0};
        memcpy(id, &buffer[pos], 4);

        int frame_size = convert_big_to_little_endian(&buffer[pos + 4]);
        if (frame_size <= 0 || frame_size > 1024)
            break;

        if (strncmp(id, frame_id, 4) == 0)
        {
            int new_len = strlen(new_value);
            int diff = new_len - (frame_size - 1);
            int new_tag_size = tag_size + diff;

            long new_file_size = file_size + diff;
            unsigned char *new_buf = (unsigned char *)malloc(new_file_size);
            if (!new_buf)
                return READ_FAILURE;

                   // Copy up to frame
            memcpy(new_buf, buffer, pos + 10 + 1);
            memcpy(&new_buf[pos + 10 + 1], new_value, new_len);

                  // Fill any extra space
            for (int i = new_len; i < frame_size - 1 + diff; i++)
                new_buf[pos + 11 + i] = 0;

                 // Copy rest of file
            memcpy(&new_buf[pos + 10 + 1 + new_len],
                   &buffer[pos + 10 + frame_size],
                   file_size - (pos + 10 + frame_size));

                   // Update frame size and header
            write_little_endian_to_big(new_len + 1, &new_buf[pos + 4]);
            new_buf[6] = (new_tag_size >> 21) & 0x7F;
            new_buf[7] = (new_tag_size >> 14) & 0x7F;
            new_buf[8] = (new_tag_size >> 7) & 0x7F;
            new_buf[9] = new_tag_size & 0x7F;

            char temp_file[256];
            snprintf(temp_file, sizeof(temp_file), "%s_temp.mp3", filename);
            FILE *out = fopen(temp_file, "wb");
            fwrite(new_buf, 1, new_file_size, out);
            fclose(out);

            free(buffer);
            free(new_buf);
            remove(filename);
            rename(temp_file, filename);

            return READ_SUCCESS;
        }
        pos += 10 + frame_size;
    }

    free(buffer);
    return READ_FAILURE;
}

