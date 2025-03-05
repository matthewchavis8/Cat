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
 */

// Fixture for Cat object
class CatTest : public ::testing::Test {
  protected:
    Cat cat;

    void SetUp () override {
      cat.is_line_numbers = false;
      cat.write_mode = false;
      cat.line_count = 1;

      std::ofstream tmp_file1("test_file.txt");
      tmp_file1 << "I can read this file!";
      tmp_file1.close();

      std::ofstream tmp_file2("tmp.txt");
      tmp_file2.close();
    } 

    void TearDown () override {
      cat.is_line_numbers = false;
      cat.write_mode = false;
      cat.line_count = 1;

      std::remove("test_file.txt");
      std::remove("tmp.txt");
    }
};

// Test Cat is set up correctly
TEST_F (CatTest, test_setup) {
  EXPECT_TRUE(cat.content.empty());
  EXPECT_TRUE(!cat.is_line_numbers);
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
  cat.parse_file("test_file.txt");
  cat.is_line_numbers = true;

  const char* result { cat };
  EXPECT_STREQ(result, "I can read this file!\n\n");
}

// Test file redirection
TEST_F(CatTest, test_redirect_to_file) {
  
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
