#include <gtest/gtest.h>
#include "../include/Cat.hpp"
#include <fstream>

/**
 * Test for Cat struct
 * 
 * T1: Test file parsing with default
 * T2: Test file parsing with numbers
 * T3: Test Convert Cat into C style array
 * T4: Test Write to file
 */

// Fixture for Cat object
class CatTest : public ::testing::Test {
  protected:
    Cat cat;

    void SetUp () override {
      cat.is_line_numbers = false;
      cat.write_mode = false;
      cat.line_count = 1;

      std::ofstream tmp_file("test_file.txt");
      tmp_file << "I can read this file!";
      tmp_file.close();
    } 

    void TearDown () override {
      cat.is_line_numbers = false;
      cat.write_mode = false;
      cat.line_count = 1;

      std::remove("test_file.txt");
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
TEST_F(CatTest, test_parse_with_numbers) {
  cat.parse_file("test_file.txt");
  cat.is_line_numbers = true;

  const char* result { cat };
  EXPECT_STREQ(result, "I can read this file!\n\n");
}