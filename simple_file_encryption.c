#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// I know I don't need to do this, just practicing with the preprocessor directives
#define A 65
#define Z 90
#define a 97
#define z 122

int KEY = 0;

bool encrypt(FILE *input_file);
bool decrypt(FILE *input_file);
int get_key(void);

int main(int argc, char *argv[])
{
    // 1. Check argc == 2
    if (argc != 2)
    {
        printf("./simple_file_encryption input_filename\n");
        return 1;
    }

    // 2. Open File
    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL)
    {
        printf("Error opening input file\n");
        return 1;
    }
    // 3. OPTION: ENCRYPT OR DECRYPT
    int option_buffer;
    int key;
    do
    {
        printf("Enter 1 to encrypt the file, 2 to decrypt\n");
        scanf("%i", &option_buffer);
    }
    while (option_buffer != 1 && option_buffer != 2);
    printf("Option selected: %i\n", option_buffer);

    if (option_buffer == 1)
    {
        encrypt(input_file);
    }
    else if (option_buffer == 2)
    {
        decrypt(input_file);
    }
    return 0;
}

bool encrypt(FILE *input_file)
{
    char line_buffer[2048];
    int length;

    // Create a temporary .txt file to save the encrypted text
    FILE *encrypted_file = fopen("encrypted.txt", "w");
    if (encrypted_file == NULL)
    {
        printf("Error creating temp.txt\n");
        return false;
    }
    // get key
    get_key();
    // 1.Read file line by line
    while (fgets(line_buffer, sizeof(line_buffer), input_file) != NULL)
    {
        // encrypt
        // I got to go char by char I guess??
        length = strlen(line_buffer);
        for (int i = 0; i < length; i++)
        {
            // encrypt each char
            // select chars lower / upper. non-letter characters leave unchanged
            if (line_buffer[i] >= A && line_buffer[i] <= Z)
            {
                // UPPERCASE    
                line_buffer[i] = A + (line_buffer[i] - A + KEY) % 26;
                fputc(line_buffer[i], encrypted_file);
            }
            else if (line_buffer[i] >= a && line_buffer[i] <= z)
            {
                // LOWERCASE
                line_buffer[i] = a + (line_buffer[i] - a + KEY) % 26;
                fputc(line_buffer[i], encrypted_file);
            }
            else
            {
                fputc(line_buffer[i], encrypted_file);
            }        
        }
    }
    fclose(encrypted_file);
    printf("A file encrypted.txt has been created with the encrypted content of your input file\n");
    return true;
}

bool decrypt(FILE *input_file)
{
    char line_buffer[2048];
    int length;

    // Create a temporary .txt file to save the decrypted text
    FILE *decrypted_file = fopen("decrypted.txt", "w");
    if (decrypted_file == NULL)
    {
        printf("Error creating temp.txt\n");
        return false;
    }
    // get key_index
    get_key();
    // 1. Read file line by line
    while (fgets(line_buffer, sizeof(line_buffer), input_file) != NULL)
    {
        length = strlen(line_buffer);

        for (int i = 0; i < length; i++)
        {
            // decrypt each char
            // select chars lower / upper. non-letter characters remain unchanged
            if (line_buffer[i] >= A && line_buffer[i] <= Z)
            {
                // UPPERCASE
                line_buffer[i] = A + (line_buffer[i] - A  - KEY + 26) % 26;
                
                fputc(line_buffer[i], decrypted_file);
            }
            else if (line_buffer[i] >= a && line_buffer[i] <= z)
            {
                // LOWERCASE
                line_buffer[i] = a + (line_buffer[i] - a  - KEY + 26) % 26;
                fputc(line_buffer[i], decrypted_file);
            }
            else
            {
                fputc(line_buffer[i], decrypted_file);
            }
        }
    }
    fclose(decrypted_file);
    printf("A file decrypted.txt has been created with the encrypted content of your input file\n");
    return true;
}

int get_key(void)
{
    do
    {
        printf("Please enter the key, between 1 and 25 (inclusive)\n");
        scanf("%i", &KEY);
    }
    while (KEY < 1 || KEY > 25);
    return 0;
}