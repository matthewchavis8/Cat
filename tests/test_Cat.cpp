#include <gtest/gtest.h>
#include "../include/Cat.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <string>

/**
 * Test for Cat struct
 * 
 * T1: Test file parsing with default
 * T2: Test file parsing with numbers
 * T3: Test Convert Cat into C style array
 * T4: Test Write to file
 * T5: Test file redirection '>'
 * T6: Test Reverse Parse
 * T7: Test mark end of line
 * T8: Test ignore blank lines
 */

// Fixture for Cat object
class CatTest : public ::testing::Test {
  protected:
    Cat cat;

    void SetUp () override {

      std::ofstream tmp_file1("test_file.txt");
      tmp_file1 << "I can read this file!";
      tmp_file1.close();

      std::ofstream tmp_file2("tmp.txt");
      tmp_file2.close();

      std::ofstream tmp_file3("test_file_with_blank.txt");
      tmp_file3 << "I can read this file!";
      tmp_file3 << "\n\n\n";
      tmp_file3 << "Hello World!";
      tmp_file3.close();
    } 

    void TearDown () override {
      cat.line_number_mode = false;
      cat.write_mode = false;
      cat.reverse_parse_mode = false;
      cat.ignore_blank_line_mode = false;

      std::remove("test_file.txt");
      std::remove("tmp.txt");
      std::remove("test_file_with_blank.txt");
    }
};

// Test Cat is set up correctly
TEST_F (CatTest, test_setup) {
  EXPECT_TRUE(cat.content.empty());
  EXPECT_TRUE(!cat.line_number_mode);
  EXPECT_TRUE(!cat.write_mode);
  EXPECT_EQ(cat.line_count, 1);
}

// Test Cat object into C style array
TEST_F(CatTest, test_convert_cat_into_c_style_array) {
  cat.content = {"Hello", "World"};
  const char* result { cat };
  EXPECT_STREQ(result, "Hello\nWorld\n");
}

// Test file parsing with default
TEST_F (CatTest, test_parse_with_default) {
  cat.parse_file("test_file.txt");

  const char* result { cat };
  EXPECT_STREQ(result, "I can read this file!\n\n");
}

// Test file parsing with numbers
TEST_F (CatTest, test_parse_with_numbers) {
  cat.line_number_mode = true;
  cat.parse_file("test_file.txt");

  const char* result { cat };
  EXPECT_STREQ(result, "1: I can read this file!\n\n");
}

// Test file redirection
TEST_F (CatTest, test_redirect_to_file) {
  
  std::vector<std::string> args {
    "test_file.txt",
    ">",
    "tmp.txt"
  };

  cat.redirect_to_file(args, cat);

  std::ifstream file("tmp.txt");
  std::ostringstream res;
  std::string line;

  while (std::getline(file, line))
    res << line << '\n';
  file.close();

  std::string output = res.str();
  EXPECT_STREQ(output.c_str(), "I can read this file!\n\n");
}

// Test reverse parsing
TEST_F (CatTest, test_reverse_parse) {
  cat.reverse_parse_mode = true;
  cat.content = {"Hello", "World"};

  const char* result { cat };

  EXPECT_STREQ(result, "World\nHello\n");
}

// Test mark end of line mode
TEST_F (CatTest, test_mark_end_of_line) {
  cat.mark_end_of_line_mode = true;
  cat.parse_file("test_file.txt");

  const char* result { cat };

  EXPECT_STREQ(result, "I can read this file!$\n\n");
}

// Test Ignore blank lines mode
TEST_F (CatTest, test_ignore_blank_lines) {
  cat.ignore_blank_line_mode = true;
  cat.parse_file("test_file_with_blank.txt");

  const char* result { cat };

  EXPECT_STREQ(result, "I can read this file!\nHello World!\n\n");
}