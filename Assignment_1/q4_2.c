#include <sys/stat.h> // means system stat used for S_IRUSR, S_IWUSR, S_IRGRP, S_IROTH // system stat is used to get information about a file
#include <fcntl.h> // means file control
#include <stdio.h>

int main() {
    char filename[] = "example.txt"; // filename is a character array
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; // what do these mean? 
    // S_IRUSR means read permission for the owner of the file, 
    // S_IWUSR means write permission for the owner of the file, 
    // S_IRGRP means read permission for the group owner of the file, 
    // S_IROTH means read permission for other users
    // the operator | is bitwise OR operator which is used to combine multiple permission flags into a single 
    // mode_t value.
    // Each permission flag (like S_IRUSR, S_IWUSR, S_IRGRP, S_IROTH) corresponds to a specific bit pattern. 
    // When these flags are combined using the bitwise OR operator, the result is a new bit pattern that 
    // includes all the permissions specified by the flags.
    // The mode_t type is used to represent file permissions. It is an integer type, but it is not guaranteed
    int file_descriptor = creat(filename,mode); // creat is used to create a file

    if (file_descriptor == -1) {
        perror("Error creating file"); //perror is used to print the error message to stderr
        return 1;
    }

    // close the file when done
    close(file_descriptor);
    return 0;
}