#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdexcept>

// Function to find the start and end positions of the custom delimiter in the input string
void find_custom_delimiter_bounds(const char* input_string, const char** start_ptr, const char** end_ptr) {
    if (input_string[0] == '/') {
        *start_ptr = input_string + 2; // Skip over '//'
        *end_ptr = strchr(*start_ptr, '\n');
    } else {
        *start_ptr = NULL;
        *end_ptr = NULL;
    }
} 
// Function to extract the custom delimiter from the input string
void extract_custom_delimiter_string(const char* input_string, char* delimiter_str) {
    const char* start_ptr;
    const char* end_ptr;
    find_custom_delimiter_bounds(input_string, &start_ptr, &end_ptr);
    if (start_ptr && end_ptr) {
        strncpy(delimiter_str, start_ptr, end_ptr - start_ptr);
        delimiter_str[end_ptr - start_ptr] = '\0';
    } else {
        strcpy(delimiter_str, ",");
    }
}

// Function to extract the number portion from the input string
void extract_number_part(const char* input_string, char* numbers_str) {
    const char* start_ptr = input_string;
    if (input_string[0] == '/' && input_string[1] == '/') {
        start_ptr = strchr(input_string, '\n') + 1; // Skip over '//'
    }
    strcpy(numbers_str, start_ptr);
    for (char* ptr = numbers_str; *ptr; ++ptr) {
        if (*ptr == '\n') {           
            *ptr = ',';      // Replace '\n' with ','
        }
    }
}

// Function to parse the input string to extract the delimiter and numbers
void parse_input_string(const char* input_string, char* delimiter_str, char* numbers_str) {
    extract_custom_delimiter_string(input_string, delimiter_str);
    extract_number_part(input_string, numbers_str);
}

// Function to split the number string based on the delimiter and convert to integers
void split_numbers_by_delimiter(const char* str, const char* delimiter_str, int* numbers_array, int* count_ptr) {
    char* copy_str = strdup(str);
    char* token = strtok(copy_str, delimiter_str);
    while (token) {
        numbers_array[(*count_ptr)++] = atoi(token);
        token = strtok(NULL, delimiter_str);
    }
    free(copy_str);
}

// Function that throws an exception on negative numbers
void check_for_negative_numbers(int* numbers_array, int size) {
    for (int i = 0; i < size; ++i) {
        if (numbers_array[i] < 0) {
            throw std::runtime_error("negatives not allowed");
        }
    }
}

// Function to sum valid numbers (ignoring those greater than 1000)
void sum_valid_numbers(int* num_array, int num_count, int* sum_ptr) {
    for (int i = 0; i < num_count; i++) {
        if (num_array[i] <= 1000) {
            *sum_ptr += num_array[i];
        }
    }
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
    int sum = 0;
    sum_valid_numbers(num_array, num_count, &sum);
    return sum;
}
