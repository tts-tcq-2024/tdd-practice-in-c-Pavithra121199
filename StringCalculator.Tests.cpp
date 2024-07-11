#include <gtest/gtest.h>
#include "StringCalculator.h"

TEST(StringCalculatorAddTests, ExpectZeroForEmptyInput) {
    int expectedresult = 0;
    const char* input = "";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

TEST(StringCalculatorAddTests, ExpectZeroForSingleZero) {
    int expectedresult = 0;
    const char* input = "0";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

TEST(StringCalculatorAddTests, ExpectSumForTwoNumbers) {
    int expectedresult = 3;
    const char* input = "1,2";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

TEST(StringCalculatorAddTests, ExpectSumWithNewlineDelimiter) {
    int expectedresult = 6;
    const char* input = "1\n2,3";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

TEST(StringCalculatorAddTests, IgnoreNumbersGreaterThan1000) {
    int expectedresult = 1;
    const char* input = "1,1001";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

TEST(StringCalculatorAddTests, ExpectSumWithCustomDelimiter) {
    int expectedresult = 3;
    const char* input = "//;\n1;2";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

TEST(StringCalculatorAddTests, ExpectSumWithCustomDelimiterAtStart) {
    int expectedresult = 2;
    const char* input = "\n2";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

TEST(StringCalculatorAddTests, ExpectSumWithDelimiterofAnyLength) {
    int expectedresult = 15;
    const char* input = "//[*]\n12***3";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

TEST(StringCalculatorCheckNegativesTests, ExpectExitOnNegativeNumbers) {
    const char* input = "1,-3,-4";
    // Redirect stderr to capture output
    testing::internal::CaptureStderr();
    // Call the function that triggers the error message
    add(input);
    // Get the captured stderr output
    std::string stderr_output = testing::internal::GetCapturedStderr();
    // Check if the error message contains the expected substring
    ASSERT_TRUE(stderr_output.find("negatives not allowed: -3 -4") != std::string::npos)
        << "Expected error message containing 'negatives not allowed: -3 -4', got: " << stderr_output;
}
