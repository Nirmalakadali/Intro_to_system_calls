#include <stdio.h> 
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#define APPROX_BYTES 100000
#define ll long long int
int main(int argc, char *argv[])
{

    // allocating memory to store the path given
    char *way_to_folder = (char *)malloc(APPROX_BYTES);
    // initialising path to zero
    way_to_folder[0] = '\0';
    // initialing the var to traverse through command line names
    int var = 1;
    while (var < argc)
    {
        // concatenating the strings in the command line to get the path of the input file of there is space in it
        strcat(way_to_folder, argv[var]);
        // if traverse not going to the end of the command line arguments
        if (var != argc - 1)
        {
            // concatenatethe space givrn and folder path
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
            break;
        }
        slash--;
    }
    char error[100] = "input file error";
    char empty[10] = "\0";
    // opening the input file in read and write mode
    ll fd = open(way_to_folder, O_RDONLY);
    if (fd == -1)
    {
        write(0, error, 100);
        sprintf(empty, "\n");
        write(1, empty, 10);
        return 0;
    }
    // creating a directory with name Assignment and giving read and write permission to it
    mkdir("Assignment", 0700);
    // initialising varible to store the transfer
    long double monitoring_value = 0;
    // string to storw the progress
    char *P = (char *)malloc(sizeof(char));
    // allocating memory using malloc to store the input file name
    char *filename = (char *)malloc(10000);
    int j = 0;
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
            // incrementig way_to folder index
            slash++;
            // incrementing filename index
            j++;
        }
    }
    // storing the output file
    char folder_name[APPROX_BYTES] = "Assignment/1_";
    // concatenating folder name and the input file to get output filename as Assignment/1_filename.txt
    strcat(folder_name, filename);
    // Creating the Output file if not present and truncating it if it is present opening in read and write mode and over write if content already present
    long long int fd3 = open(folder_name, O_CREAT | O_TRUNC, 0600); 
    close(fd3);
    // chmod(folder_name,600);
    ll fd2 = open(folder_name, O_RDWR | O_APPEND);
    char error1[100] = "output file error";
    char empty1[10] = "\0";
    // print the error on terminal using write syscall if anyfile is not opening
    if (fd2 == -1 || fd3 == -1)
    {
        write(0, error1, 100);
        sprintf(empty1, "\n");
        write(1, empty1, 10);
        // terminating program if there is an error in opening files
        return 0;
    }

    // initializing fsize variable to read the number of charecters in the file
    ll fsize = lseek(fd, 0, SEEK_END);
    // dividing file into chunks
    ll size_of_file = fsize % APPROX_BYTES;
    ll check_remainder = fsize / APPROX_BYTES;
    char *original_array, *reversed_array;
    // Allocating memory to store the characters read from the input file
    original_array = (char *)malloc(APPROX_BYTES);
    // Allocating memory to store the reversed characters.
    reversed_array = (char *)malloc(APPROX_BYTES);
    // setting the file pointer of input file into the initial
    lseek(fd, 0, SEEK_SET);
    // if file is greater than divided chunks
    if (check_remainder > 0)
    {
        // initalising fd1  to read the number of character in a file , initialising number of character read is 100000
        ll fd1, characters = 100000;
        // storing size_of_file in divide to change the lseek pointer after reading the 10000 characters
        ll divide = size_of_file;
        // initialising variable to go through the original array(file) and reverse it
        ll i = 0;
        while (i <= check_remainder) // iterating over the parts of the file of size characters
        {
            if (i > 0)
            {
                // ifi !=0 then number of characters is like initialised above
                characters = 100000;
            }
            else if (i == 0)
            {
                // if i==0 then store size_of_file into the number of characters variable
                characters = size_of_file;
            }
            // positioning the pointer in the file to the initial position
            lseek(fd, 0, SEEK_SET);
            // positionig the file pointer at (fsize - divide)th byte to read untill that point for one time
            lseek(fd, fsize - divide, SEEK_CUR);
            // reading characters from the file and store it in the original array and also fd1  is to store the number of characters stored
            fd1 = read(fd, original_array, characters);
            // initialising a variable to traverse the array
            ll j = 0;
            // every string have null pointer at the end
            original_array[fd1] = '\0';
            // iterating through the array untill the number of characters read
            while (j < fd1)
            {
                // reversing the original array using index and storing it into the reversed array
                reversed_array[fd1 - j - 1] = original_array[j];
                // incrementing to the next storing charcater
                j++;
            }
            // every string have null character at the end as a terminating character
            reversed_array[fd1] = '\0';
            // writing reversed array into the output file
            write(fd2, reversed_array, fd1);
            // increasing the monitoring value after writing into the file
            monitoring_value += fd1;
            // percentage of progress
            long double perc = (monitoring_value / fsize) * 100;
            fflush(stdout);
            // writing the progress of transfering into the P array
            sprintf(P, "\r%0.6Lf%%", perc);
            // increasing the divide to 100000 to change the pointer after incsize_of_fileenting
            divide += 100000;
            // writing progress of reversing and transferring of a file on the screen using write syscall
            write(1, P, 15);
            // incrementing
            i++;
        }
    }
    // if file is less than divided chunks
    else if (check_remainder == 0)
    {

        // reading every string from the input file into the original array
        ll fd1 = read(fd, original_array, size_of_file);
        // end the end giving null character to the stored array
        original_array[fd1] = '\0';
        // initialising variable to go through the original array and reverse it
        ll i = 0;
        while (i < fd1)
        {
            // storing reversed array from the original array
            reversed_array[fd1 - i - 1] = original_array[i];
            // going to the next index through incsize_of_fileenting
            i++;
        }
        // at the end giving null character in the reversed array final index bcz strings end with null character
        reversed_array[fd1] = '\0';
        // writing reversed array into the output file
        write(fd2, reversed_array, fd1);
        // increasing the monitoing value to the end of the characters
        monitoring_value += fd1;
        // finl monitoring in percentage
        long double perc = (monitoring_value / fsize) * 100;
        // storing the progress of the file transfer using sprintf function into progress array
        sprintf(P, "\r%0.8Lf%%\n", perc);
        // printing on the terminal using write syscall
        write(1, P, 15);
    }
    // free up the original array
    free(original_array);
    // free up the reversed array
    free(reversed_array);
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
    // closing input file
    close(fd);
    // closing output file
    close(fd2);
    return 0;
}