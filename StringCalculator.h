#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdexcept>

int is_empty_string(const char* input) {
    return (input == NULL || input[0] == '\0');
}

void extract_custom_delimiter(const char* input, char* delimiter) {
    int i = 2;           // Start after the initial delimiter //
    delimiter[0] = '\0';
    while (input[i] != '\0' && input[i] != '\n') {
        strncat(delimiter, &input[i], 1);
        i++;
    }
}

void has_custom_delimiter(const char* input, char* delimiter) {
    if (input[0] == '/' && input[1] == '/')
        extract_custom_delimiter(input, delimiter);
    else
        strcpy(delimiter, ",\n");
}

int value_less_than_thousand(int value) {
    return (value < 1000) ? value : 0;
}

void check_negative_values(int value) {
    if (value<0) {
        throw std::runtime_error("negatives not allowed");
    }
}

int process_input(const char* input, const char* delimiter) {
    char* duplicate_input = strdup(input);
    int sum = 0;
    char* input_segment = strtok(duplicate_input, delimiter);
    while (input_segment != NULL) {
        int value = atoi(input_segment);
        check_negative_values(value);
        sum += value_less_than_thousand(value);
        input_segment = strtok(NULL, delimiter);
    }
    free(duplicate_input);
    return sum;
}

int add(const char* input) {
    char delimiter[20];
    if (is_empty_string(input)) {
        return 0;
    }
    has_custom_delimiter(input, delimiter);
    int sum = process_input(input, delimiter);
    return sum;
}
