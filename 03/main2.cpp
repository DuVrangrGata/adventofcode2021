#include <stdio.h>
#include <string>
#include <fstream>
#include <cassert>
#include <cstring>
#include <math.h>
#include <vector>

int
convert_binary_string_to_decimal(const std::string& binary, size_t size)
{
  double multiplier = pow(2, (size - 1));

  int result = 0;

  for (size_t i = 0; i < size; i++) {

    if(binary[i] == '1') {
      result += multiplier;
    }

    multiplier /= 2;

  }

  return result;

}

struct recursive_result {

  std::string oxygen_result;
  std::string co2_result;

};

enum search_for {
  MOST,
  LEAST,
  BOTH
};

recursive_result
split_most_least_common(const std::vector<std::string>& in, size_t index, search_for sf)
{

  std::vector<std::string> zeros;
  std::vector<std::string> ones;


  // Make two new vectors, containing all strings
  // with zeros or ones at index
  for (std::string s : in) {

    if (s[index] == '1') {
      ones.push_back(s);
    } else {
      zeros.push_back(s);
    }

  }

  fprintf(stdout, "Recursion Mode: %d, Num_of_Zeros: %ld, Num_of_Ones: %ld, Current_index: %ld\n", (int)sf, zeros.size(), ones.size(), index);

  if (zeros.size() > ones.size()) {
    switch(sf) {
    // We are searching for the most common value
    // The most common value at index is zero
    case MOST:
      // When only one element left it is the result
      // In this case for oxygen, just leave co2 empty
      if (zeros.size() == 1) {
	recursive_result tempresult = {zeros[0], ""};
	return tempresult;
      }

      // continue splitting in search for most common value
      return split_most_least_common(zeros, index+1, MOST);
    // We are searching for the least common value
    // The least common value at index is one
    case LEAST:
      // When only one element left it is the result
      // In this case for co2, just leave oxygen empty
      if (ones.size() == 1) {
	recursive_result tempresult = {"", ones[0]};
	return tempresult;
      }

      return split_most_least_common(ones, index+1, LEAST);
    case BOTH:
      // the inital call searches for both least and most common
      // in this case zeros are most common and ones are least
      recursive_result r1 = split_most_least_common(zeros, index+1, MOST);
      recursive_result r2 = split_most_least_common(ones, index+1, LEAST);

      recursive_result endresult = {r1.oxygen_result, r2.co2_result};

      return endresult;
    }

  } else {
    switch(sf) {
    // We are searching for the most common value
    // The most common value at index is one
    case MOST:
      // When only one element left it is the result
      // In this case for oxygen, just leave co2 empty
      if (ones.size() == 1) {
	recursive_result tempresult = {ones[0], ""};
	return tempresult;
      }

      return split_most_least_common(ones, index+1, MOST);
    // We are searching for the least common value
    // The least common value at index is zero
    case LEAST:
      // When only one element left it is the result
      // In this case for co2, just leave oxygen empty
      if (zeros.size() == 1) {
	recursive_result tempresult = {"", zeros[0]};
	return tempresult;
      }

      return split_most_least_common(zeros, index+1, LEAST);
    case BOTH:
      // the inital call searches for both least and most common
      // in this case ones are most common and zeros are least
      recursive_result r1 = split_most_least_common(zeros, index+1, LEAST);
      recursive_result r2 = split_most_least_common(ones, index+1, MOST);

      recursive_result endresult = {r1.co2_result, r2.oxygen_result};

      return endresult;
    }
  }

  // Every possible outcome return already
  fprintf(stderr, "This should never be reached");
  exit(1);
}


int main() {
  std::string line;

  std::ifstream stream("input.txt", std::ifstream::in);

  if (!stream.is_open()) {
    fprintf(stderr, "Failed to open file");
    exit(1);
  }

  std::vector<std::string> filecontent;

  // Just read in whole file
  while (getline(stream, line)) {
    filecontent.push_back(line);
  }

  // start recursion
  recursive_result r = split_most_least_common(filecontent, 0, BOTH);

  int oxygen_generator_rating = convert_binary_string_to_decimal(r.oxygen_result, r.oxygen_result.length());
  int co2_scrubber_rating = convert_binary_string_to_decimal(r.co2_result, r.co2_result.length());

  fprintf(stdout, "Success: %d", oxygen_generator_rating * co2_scrubber_rating);

  return 0;
}
