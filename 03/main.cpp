#include <stdio.h>
#include <string>
#include <fstream>
#include <cassert>
#include <cstring>
#include <math.h>

int convert_binary_to_decimal(int* binary, size_t size) {

  double multiplier = pow(2, (size - 1));

  int result = 0;

  for (size_t i = 0; i < size; i++) {

    result += multiplier * binary[i];
    multiplier /= 2;

  }

  return result;
}


int main() {
  std::string line;

  std::ifstream stream("input.txt", std::ifstream::in);

  if (!stream.is_open()) {
    fprintf(stderr, "Failed to open file");
    exit(1);
  }

  // NOTE: To avoid using variable sized arrays, allocate memory by hand

  // Get inital line to calculate array size
  getline(stream, line);

  // This just works when no line has more characters then the first line
  // This doesn't support incorrect formated input files
  size_t num_of_bytes = line.length();

  // Allocate Memory
  int* counts = (int*)malloc(sizeof(int) * num_of_bytes);
  int* gamma_rate = (int*)malloc(sizeof(int) * num_of_bytes);
  int* epsilon_rate = (int*)malloc(sizeof(int) * num_of_bytes);

  // Initialize Memory
  memset(counts, 0, sizeof(int) * num_of_bytes);
  memset(gamma_rate, 0, sizeof(int) * num_of_bytes);
  memset(epsilon_rate, 0, sizeof(int) * num_of_bytes);

  // We already read one line
  size_t num_of_lines = 1;

  do {
    // Assert format of input file
    assert(line.length() == num_of_bytes);

    // Count the number of ones per char
    for (size_t i = 0; i < line.length(); i++) {
      char c = line[i];
      // Convert charcode to value as int: 48 = 0, 49 = 1
      counts[i] += (int)c - 48;
    }

    num_of_lines++;
    
  } while (getline(stream, line));



  // If the number of 1's is greater than the number of 0's
  // the fraction is greater than 0.5
  for (size_t i = 0; i < num_of_bytes; i++) {
    float fraction = counts[i] / (float)num_of_lines;

    if (fraction > 0.5) {
      gamma_rate[i] = 1;
      epsilon_rate[i] = 0;
    } else {
      gamma_rate[i] = 0;
      epsilon_rate[i] = 1;
    }
  }


  int gamma_rate_dec = convert_binary_to_decimal(gamma_rate, num_of_bytes);
  int epsilon_rate_dec = convert_binary_to_decimal(epsilon_rate, num_of_bytes);

  // Free Memory
  free(counts);
  free(gamma_rate);
  free(epsilon_rate);

  fprintf(stdout, "Success: %d", gamma_rate_dec * epsilon_rate_dec);

  return 0;
}
