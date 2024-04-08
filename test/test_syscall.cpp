#include <iostream>
#include <unistd.h> // For POSIX functions
#include <fcntl.h>  // For file control options
#include <string>
#include <chrono>

int main() {
    int fileDescriptor = open("example.txt", O_RDONLY); // Open the file in read-only mode
    if (fileDescriptor == -1) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    const int bufferSize = 1000; // Size of the buffer for reading
    char buffer[bufferSize];     // Buffer to store read data

    ssize_t bytesRead;
    auto start = std::chrono::high_resolution_clock::now(); // Start the timer
    bytesRead = read(fileDescriptor, buffer, bufferSize);
    auto end = std::chrono::high_resolution_clock::now(); // End the timer
    if (bytesRead == -1) {
        std::cerr << "Error while reading from the file." << std::endl;
        return 1;
    }
    close(fileDescriptor); // Close the file descriptor when done
    std::chrono::duration<double, std::micro> duration = end - start;
    std::cout << "Reading 100 bytes in one go took: " << duration.count() << " microseconds" << std::endl;

    fileDescriptor = open("example.txt", O_RDONLY); // Open the file in read-only mode
    int i = 0;
    start = std::chrono::high_resolution_clock::now(); // Start the timer
    while (i < 100) {
        bytesRead = read(fileDescriptor, &buffer[i], 1);
        //if (bytesRead == -1) {
        //std::cerr << "Error while reading from the file." << std::endl;
        //return 1;
        //}
        i++;
    }
    end = std::chrono::high_resolution_clock::now(); // End the timer
    duration = end - start;
    std::cout << "Reading 100 bytes, 1 byte at a time took: " << duration.count() << " microseconds" << std::endl;
    return 0;
}
