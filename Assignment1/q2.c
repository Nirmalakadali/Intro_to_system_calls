#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#define APPROX_BYTES 1000
#define ll long long int
int main(int argc, char *argv[])
{
    // allocating memory to store the path given
    char *way_to_folder = (char *)malloc(APPROX_BYTES);
    // initialising path to zero
    way_to_folder[0] = '\0';
    // initialing the var to traverse through command line names
    int var = 1;
    while (var < argc - 2)
    {
        // concatenating the strings in the command line to get the path of the input file of there is space in it
        strcat(way_to_folder, argv[var]);
        // if traverse not going to the end of the command line arguments
        if (var != argc - 3)
        {
            // concatenat ethe space givrn and folder path
            strcat(way_to_folder, " ");
        }
        // incrementing
        var++;
    }
    int slash;
    // storing length of the path into the slash variable
    slash = strlen(way_to_folder) - 1;
    while (slash >= 0)
    {
        // finding the index of the last farword slash
        if (way_to_folder[slash] == '/')
        {
            // obtaining input file
            break;
        }
        slash--;
    }
    char error[100] = "input file error";
    char empty[10] = "\0";
    // opening the input file in read and write mode
    ll fd = open(way_to_folder, O_RDONLY);
    if (fd < 0)
    {
        write(0, error, 100);
        sprintf(empty, "\n");
        write(1, empty, 10);
        return 0;
    }

    // creating a directory with name Assignment and giving read and write permission to it
    mkdir("Assignment", 0700);

    ll m = atoi(argv[argc - 2]);
    ll n = atoi(argv[argc - 1]);
    // string to storw the progress
    char *P = (char *)malloc(sizeof(char));
    // allocating memory using malloc to store the input file name
    char *filename = (char *)malloc(1000);
    ll j = 0;
    // updating input filename as the text file that if the last command string
    if (slash == -1)
    {
        filename = way_to_folder;
        // if input file given directly without path then assigning way_to_folder to filename.
    }
    else
    {
        // assigning path of the input file
        slash++;
        while (slash != strlen(way_to_folder))
        {
            // storing input file name given in command line into the filename variable
            filename[j] = way_to_folder[slash];
            // incsize_of_fileenting way_to_folder index
            slash++;
            // incsize_of_fileenting storing filename index
            j++;
        }
    }
    // storing the output file
    char folder_name[APPROX_BYTES] = "Assignment/2_";
    // concatenating folder name and the input file to get output filename as Assignment/1_filename.txt
    strcat(folder_name, filename);
    long long int fd3 = open(folder_name, O_CREAT | O_TRUNC, 0600); // Creating the Output file if not present and truncating it if it is present
    close(fd3);

    // Creating the Output file if not present and truncating it if it is present opening in read and write mode and over write if content already present
    ll fd2 = open(folder_name, O_RDWR | O_APPEND);
    // print the error on terminal using perror syscall if anyfile is not opening
    if (fd2 == -1 || fd3 == -1)
    {
        perror("Error in output file operation");
        // terminating program if there is an error in opening files
        return 0;
    }
    char *original_array, *reversed_array;
    // Allocating memory to store the characters read from the input file
    original_array = (char *)malloc(APPROX_BYTES);
    // Allocating memory to store the reversed characters.
    reversed_array = (char *)malloc(APPROX_BYTES);
    // setting the file pointer of input file into the initial
    // initializing fsize variable to read the number of charecters in the file
    ll fsize = lseek(fd, 0, SEEK_END);
    // dividing file into chunks till the first index
    ll size_of_file = m % APPROX_BYTES;
    // storing the chunck in t  variable
    ll t  = size_of_file;
    // checking file is freater than our approx bytes if remainder >1
    ll check_remainder = m / APPROX_BYTES;
    // chuncks in charcter size
    ll characters = 1000;
    lseek(fd, 0, SEEK_SET);
    // variable to store value printing and reading
    long double monitoring_value = 0;
    // variable to store progress percentage
    long double progress_value;
    // initialising a variable to traverse the array
    ll z = 0;
    // first loop is to go from the staring to first index
    while (z <= check_remainder)
    {
        // checking file is still greater than z means some chuncks till left
        if (!z)
        {
            characters = t ;
        }
        // if that is thelast chunk then sizeof file is characters read
        else
        {
            characters = 1000;
        }
        // set to initial of the chunck
        lseek(fd, 0, SEEK_SET);
        // till the end of the m-t  in chunck
        lseek(fd, m - t , SEEK_CUR);
        ll fr;
        fr = read(fd, original_array, characters);

        ll y = 0;
        // loop to reverse and store in reversed array
        while (y < fr)
        {
            // reversing and storing in reversed array from original array
            reversed_array[fr - y - 1] = original_array[y];
            y++;
        }
        // writing into the output file using reversed array
        write(fd2, reversed_array, fr);
        // number of characters read from original file
        monitoring_value += fr;
        // percentage of read characters from the total file
        progress_value = (monitoring_value / fsize) * 100;
        // storing into p array using sprintf
        sprintf(P, "\r%0.2Lf%%", progress_value);
        t  += 1000;
        // writing progress on the terminal
        write(1, P, 15);
        z++;
    }
    // reinitialising chunck size
    ll characters1 = 1000;
    // checking the filesize approximately from start index to end index
    ll check_remainder1 = (n - m + 1) / 1000;
    // remaninder
    ll size_of_file1 = (n - m + 1) % 1000;
    ll divide = 0;
    // to store the percentage
    long double progress_value1;
    ll w = 0;
    // loop to write from start index to end index without reversing
    while (w <= check_remainder1)
    {
        // setting same character size if w<0
        if (w == check_remainder1)
        {
            characters1 = size_of_file1;
        }
        // end of the file reading process
        else
        {
            characters1 = 1000;
        }
        // setting cursor positioning to beginnning of the every chunk
        lseek(fd, 0, SEEK_SET);
        // till the m+divide for every chunck
        lseek(fd, m + divide, SEEK_CUR);
        ll fr1;
        // reading into original array from the file
        fr1 = read(fd, original_array, characters1);
        // writing into the output file
        write(fd2, original_array, fr1);
        // incrementing read charctaers value
        monitoring_value += fr1;
        // updating progress of the read and write
        progress_value1 = (monitoring_value / fsize) * 100;
        // incrementing to next chunk
        divide += 1000;
        // storing progress value into the array p
        sprintf(P, "\r%0.2Lf%%", progress_value);
        // printing on the terminal
        write(1, P, 15);
        w++;
    }
    // checking the filesize approximately from start end index to end of the file
    ll size_of_file2 = (fsize - n - 1) % APPROX_BYTES;
    // calculation to check file is big or small
    ll check_remainder2 = (fsize - n - 1) / APPROX_BYTES;
    ll characters2 = 1000;
    long double progress_value3;
    // initialising a variable to traverse the array
    ll h = 0;
    // loop to read and write characters from end index to the end of the file
    while (h <= check_remainder2)
    {
        // if chunks are so many left
        if (!h)
        {
            characters2 = size_of_file2;
        }
        // if chunk is final
        else
        {
            characters2 = 1000;
        }
        // setting cursor positioning to beginnning of the every chunk

        lseek(fd, 0, SEEK_SET);
        // till the end of the every chunk
        lseek(fd, fsize - size_of_file2, SEEK_CUR);
        // reading characters using original array
        ll fr2;
        fr2 = read(fd, original_array, characters2);
        ll p = 0;
        // loop to reverse the characters
        while (p < fr2)
        {
            reversed_array[fr2 - p - 1] = original_array[p];
            p++;
        }
        // writing into the output file
        write(fd2, reversed_array, fr2);
        // incrementing the read values
        monitoring_value += fr2;
        // updating progress
        progress_value3 = (monitoring_value / fsize) * 100;
        // updating chunk end
        size_of_file2 += 1000;
        // storing the progress into the p array
        sprintf(P, "\r%0.2Lf%%", progress_value3);
        // writing progress on terminal
        write(1, P, 15);
        h++;
    }
    if (slash != -1)
    {
        // free up the memory which we allocated for filename and path
        free(filename);
        free(way_to_folder);
    }
    else
    {
        // else free up the memory allocated to the path because file already stored after the abouve if and else condition so we dont need to store the path anymore
        free(way_to_folder);
    }
    // free up the original array
    free(original_array);
    // free up the reversed array
    free(reversed_array);
    // closing input file
    close(fd);
    // closing output file
    close(fd2);
    //newline
    char empty10[10] = "\0";
    sprintf(empty10, "\n");
    write(1, empty10, 10);
    return 0;
}

