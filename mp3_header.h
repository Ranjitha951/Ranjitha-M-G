#ifndef MP3_HEADER_H
#define MP3_HEADER_H

// Status enum for success/failure
typedef enum
{
    READ_FAILURE = 0,
    READ_SUCCESS = 1
} Status;

// Struct to hold MP3 tag data
typedef struct
{
    char title[128];
    char artist[128];
    char album[128];
    char year[5];          // 4 digits + null terminator
    char composer[128];
    char content_type[64]; 
} ID3v2Tag; 

// Function declarations
int convert_big_to_little_endian(unsigned char *bytes);
void write_little_endian_to_big(int value, unsigned char *bytes);

Status read_mp3_tag(const char *filename, ID3v2Tag *tag);
void print_tag(const ID3v2Tag *tag);
Status edit_mp3_tag(const char *filename, const char *frame_id, const char *new_value);

#endif // MP3_HEADER_H 
