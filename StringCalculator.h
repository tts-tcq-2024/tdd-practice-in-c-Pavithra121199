#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdexcept>

// Function to extract the custom delimiter from the input string
void extract_custom_delimiter_string(const char* input_string, char* delimiter_str) {
    if (input_string[0] == '/' && input_string[1] == '/') {
        const char* start_ptr = input_string + 2; // Skip over '//'
        const char* end_ptr = strchr(start_ptr, '\n'); // Find the newline character
        if (end_ptr) {
            strncpy(delimiter_str, start_ptr, end_ptr - start_ptr); // Copy the custom delimiter
            delimiter_str[end_ptr - start_ptr] = '\0'; // Null terminate the delimiter string
        }
    } else {
        strcpy(delimiter_str, ","); // Default delimiter is ","
    }
}

// Function to extract the number portion from the input string
void extract_number_part(const char* input_string, char* numbers_str) {
    const char* start_ptr = strchr(input_string, '\n'); // Find the newline character
    if (start_ptr) {
        start_ptr++; // Move past the newline character
        strcpy(numbers_str, start_ptr); // Copy the number part
    } else {
        strcpy(numbers_str, input_string); // If no newline, copy the entire string
    }
}

// Function to parse the input string to extract the delimiter and numbers
void parse_input_string(const char* input_string, char* delimiter_str, char* numbers_str) {
    extract_custom_delimiter_string(input_string, delimiter_str); 
    extract_number_part(input_string, numbers_str); 
}

// Function to split the number string based on the delimiter and convert to integers
void split_numbers_by_delimiter(const char* str, const char* delimiter_str, int* numbers_array, int* count_ptr) {
    char* copy_str = strdup(str); // Duplicate the string for tokenization
    char* token = strtok(copy_str, delimiter_str); // Get the first token
    while (token) {
        numbers_array[(*count_ptr)++] = atoi(token); // Convert token to integer and store in array
        token = strtok(NULL, delimiter_str); // Get the next token
    }
    free(copy_str); // Free the duplicated string
}

// Function that throws an exception on negative numbers
void check_for_negative_numbers(int* numbers_array, int size) {
    for (int i = 0; i < size; ++i) {
        if (numbers_array[i] < 0) {
            throw std::runtime_error("negatives not allowed"); // Throw an exception for negative numbers
        }
    }
}

// Function to sum valid numbers (ignoring those greater than 1000)
int sum_valid_numbers_and_ignore_large(int* num_array, int num_count) {
    int sum = 0;
    for (int i = 0; i < num_count; i++) {
        if (num_array[i] <= 1000) {
            sum += num_array[i]; 
        }
    }
    return sum;
}

// Main function to add numbers from the input string 
int add(const char* input_string) {
    if (*input_string == '\0') {
        return 0;
    }
    char delimiter_str[10] = {0};
    char numbers_str[1000] = {0}; 
    parse_input_string(input_string, delimiter_str, numbers_str);
    int num_array[1000];
    int num_count = 0;
    split_numbers_by_delimiter(numbers_str, delimiter_str, num_array, &num_count); 
    check_for_negative_numbers(num_array, num_count);
    return sum_valid_numbers_and_ignore_large(num_array, num_count); 
   
}
