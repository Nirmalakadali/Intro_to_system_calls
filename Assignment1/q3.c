#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#define APPROX_BYTES 100000
#define ll long long int
int main(int argc, char *argv[])
{
    // struct is using to check permissions for two files and directory
    struct stat file;
    // opening old file
    ll input_file = open(argv[2], O_RDONLY);
    char string2[4][10000];
    // copying every argument into the second string
    // new file
    strcpy(string2[0], argv[1]);
    // old file
    strcpy(string2[1], argv[2]);
    // directory
    strcpy(string2[2], argv[3]);
    // checking directory is created or not
    if ((stat(argv[3], &file) == 0) && S_ISDIR(file.st_mode))
        write(1, "Directory is created: Yes\n", strlen("Directory is created: Yes\n"));
    else
    {
        write(1, "Directory is created: No\n", strlen("Directory is created: No\n"));
    }

    // checking is their any error
    if (input_file < 0)
    {
        // printing error using perror
        perror("Fileoperation error\n");
    }
    // just creating temporary file to reverse the original file
    ll temp_file = open("out.txt", O_CREAT | O_TRUNC, 0600);
    close(temp_file);
    // opening in read and write mode
    ll temp_f = open("out.txt", O_RDWR | O_APPEND);
    // checking temporray file have any error
    if (temp_f < 0 || temp_file < 0)
    {
        // if file have any error print the error message
        perror("Fileoperation error\n");
    }
    // reading number of characters in the old file
    ll fsize1 = lseek(input_file, 0, SEEK_END);
    ll size_of_file1 = fsize1 % APPROX_BYTES;
    ll check_remainder1 = fsize1 / APPROX_BYTES;
    // read and reverse arrays
    char *original_array1, *reversed_array1;
    // allocating memory to the arrays
    original_array1 = (char *)malloc(APPROX_BYTES);
    reversed_array1 = (char *)malloc(APPROX_BYTES);
    // posistioning the pointer to the initial of the file again
    lseek(input_file, 0, SEEK_SET);
    // if file is larger
    if (check_remainder1 > 0)
    {
        ll fd1, characters = 100000;
        ll divide = size_of_file1;
        ll i = 0;
        while (i <= check_remainder1)
        {
            if (i > 0)
            {
                characters = 100000;
            }
            else if (i == 0)
            {
                characters = size_of_file1;
            }
            // reading every chunck and chaning every poniter
            lseek(input_file, 0, SEEK_SET);
            lseek(input_file, fsize1 - divide, SEEK_CUR);
            fd1 = read(input_file, original_array1, characters);
            ll j = 0;
            original_array1[fd1] = '\0';
            while (j < fd1)
            {
                // reversing the content in the file
                reversed_array1[fd1 - j - 1] = original_array1[j];
                j++;
            }

            reversed_array1[fd1] = '\0';
            // writing into the temporary file
            write(temp_f, reversed_array1, fd1);
            divide += 100000;
            i++;
        }
    }
    // if file is smaller
    else if (check_remainder1 == 0)
    {
        // reading total strings into the array
        ll fd1 = read(input_file, original_array1, size_of_file1);
        original_array1[fd1] = '\0';
        ll i = 0;
        while (i < fd1)
        {
            // reversing the content of the file
            reversed_array1[fd1 - i - 1] = original_array1[i];
            i++;
        }
        reversed_array1[fd1] = '\0';
        // writing into the temporary file
        write(temp_f, reversed_array1, fd1);
    }
    // closing files and dealocating the allocated memory
    free(original_array1);
    free(reversed_array1);
    close(input_file);
    close(temp_f);
    // now again opening the reversed file above
    ll input = open("out.txt", O_RDONLY);
    // new file given through the command line
    ll reverse_file = open(argv[1], O_RDONLY);
    // checking if there is any error in opened files
    if (reverse_file < 0 || input < 0)
    {
        perror("Error in file operation\n");
        return 0;
    }
    // storing size of the two files
    ll fsize = lseek(input, 0, SEEK_END);
    ll fsiz = lseek(reverse_file, 0, SEEK_END);
    // flag is to check if there is any dismatched charcter
    ll flag;
    // if two files have not same size then those files are not reverse to each other
    if (fsize != fsiz)
    {
        flag = 0;
    }
    // again taking how many chunks we can made
    ll size_of_file = fsize % APPROX_BYTES;
    ll check_remainder = fsize / APPROX_BYTES;
    // initialising arrays and allocating memory to it
    char *original_array, *reversed_array;
    original_array = (char *)malloc(APPROX_BYTES);
    reversed_array = (char *)malloc(APPROX_BYTES);
    // positioning the pointers to initial of both files
    lseek(input, 0, SEEK_SET);
    lseek(reverse_file, 0, SEEK_SET);

    // if file is big
    if (check_remainder > 0)
    {
        ll id1, characters = 100000;
        ll divide = size_of_file;
        ll i = 0;
        // checking the chunks
        while (i <= check_remainder)
        {
            // for evry chunck
            if (i > 0)
            {
                characters = 100000;
            }
            // final chunck
            else if (i == 0)
            {
                characters = size_of_file;
            }
            // positioning the pointer to the initial to the some chunck for one file
            lseek(input, 0, SEEK_SET);
            lseek(input, fsize - divide, SEEK_CUR);
            id1 = read(input, original_array, characters);
            // positioning the pointer to the initial to the some chunck for another file
            lseek(reverse_file, 0, SEEK_SET);
            lseek(reverse_file, fsize - divide, SEEK_CUR);
            ll ff = read(reverse_file, reversed_array, characters);
            ll j = 0, k = 0;
            original_array[id1] = '\0';
            reversed_array[ff] = '\0';
            while (j < id1 && k < ff)
            {
                // if there is any dismatched charcter than break the condition then print no
                if (reversed_array[k] != original_array[j])
                {
                    flag = 0;
                    break;
                }
                flag = 1;
                j++;
                k++;
            }
            divide += 100000;
            i++;
        }
    }
    // if file is smaller
    else if (check_remainder == 0)
    {

        // reading from temporary file and new file
        ll id3 = read(input, original_array, size_of_file);
        ll ff = read(reverse_file, reversed_array, size_of_file);
        original_array[id3] = '\0';
        reversed_array[ff] = '\0';
        ll i = 0, j = 0;
        while (i < id3 && j < ff)
        {
            // printf("%c %c \n",reversed_array[i],original_array[j]);
            //  if there is any dismatched charcter than break the condition then print no
            if (reversed_array[j] != original_array[i])
            {
                flag = 0;
                break;
            }
            flag = 1;
            i++;
            j++;
        }
    }
    // if new file is reverse to the original file then print yes
    if (flag == 1)
    {
        write(1, "Whether file contents are reversed in newfile: Yes\n\n", strlen("Whether file contents are reversed in newfile: Yes\n\n"));
    }
    // if new file is not reverse to the original file then print no
    else if (flag == 0)
    {
        write(1, "Whether file contents are reversed in newfile: No\n\n", strlen("Whether file contents are reversed in newfile: No\n\n"));
    }
    // deallocating memory and deleting temporary file and closing new file and old file
    free(original_array);
    free(reversed_array);
    close(input_file);
    unlink("out.txt");
    close(reverse_file);
    int i = 0;
     // naming input files and directory
    char string[4][10000] = {"Newfile", "Oldfile", "Directory"};
    // checking permissions using for  loop for old file new file and directory
    while (i < 3)
    {
        // evrery file
        stat(string2[i], &file);
        // checking read permission in the file for user
        write(1, "User has read permission on ", strlen("User has read permission on "));
        write(1, string[i], strlen(string[i]));
        write(1, (file.st_mode & S_IRUSR) ? "    : Yes\n" : "   : No\n", strlen((file.st_mode & S_IRUSR) ? "    : Yes\n" : "   : No\n"));
        // checking write permission in the file for user
        write(1, "User has write permission on ", strlen("User has write permission on "));
        write(1, string[i], strlen(string[i]));
        write(1, (file.st_mode & S_IWUSR) ? "   : Yes\n" : "   : No\n", strlen((file.st_mode & S_IWUSR) ? "   : Yes\n" : "   : No\n"));
        // checking execute permission in the file for user
        write(1, "User has execute permission on ", strlen("User has execute permission on "));
        write(1, string[i], strlen(string[i]));
        write(1, (file.st_mode & S_IXUSR) ? " : Yes\n\n" : " : No\n\n", strlen((file.st_mode & S_IXUSR) ? " : Yes\n\n" : " : No\n\n"));
        // checking read permission in the file for group
        write(1, "Group has read permission on ", strlen("Group has read permission on "));
        write(1, string[i], strlen(string[i]));
        write(1, (file.st_mode & S_IRGRP) ? "    : Yes\n" : "   : No\n", strlen((file.st_mode & S_IRGRP) ? "    : Yes\n" : "   : No\n"));
        // checking write permission in the file for group
        write(1, "Group has write permission on ", strlen("Group has write permission on "));
        write(1, string[i], strlen(string[i]));
        write(1, (file.st_mode & S_IWGRP) ? "  : Yes\n" : "  : No\n", strlen((file.st_mode & S_IRGRP) ? "  : Yes\n" : "  : No\n"));
        // checking execute permission in the file for group
        write(1, "Group has execute permission on ", strlen("Group has execute permission on "));
        write(1, string[i], strlen(string[i]));
        write(1, (file.st_mode & S_IXGRP) ? ": Yes\n\n" : ": No\n\n", strlen((file.st_mode & S_IXUSR) ? ": Yes\n\n" : ": No\n\n"));
        // checking read permission in the file for others
        write(1, "Others has read permission on ", strlen("Others has read permission on "));
        write(1, string[i], strlen(string[i]));
        write(1, (file.st_mode & S_IROTH) ? "   : Yes\n" : "  : No\n", strlen((file.st_mode & S_IRGRP) ? "   : Yes\n" : "  : No\n"));
        // checking write permission in the file for others
        write(1, "Others has write permission on ", strlen("Others has write permission on "));
        write(1, string[i], strlen(string[i]));
        write(1, (file.st_mode & S_IWOTH) ? "   : Yes\n" : "  : No\n", strlen((file.st_mode & S_IRGRP) ? "   : Yes\n" : "  : No\n"));
        // checking execute permission in the file for others
        write(1, "Others has execute permission on ", strlen("Others has execute permission on "));
        write(1, string[i], strlen(string[i]));
        write(1, (file.st_mode & S_IXOTH) ? ": Yes\n" : ": No\n", strlen((file.st_mode & S_IXUSR) ? ": Yes\n" : ": No\n"));
        write(1, "\n", strlen("\n"));
        i++;
    }
    return 0;
}