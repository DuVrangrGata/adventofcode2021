#include<stdio.h>
#include<limits.h>
#include<string>
#include<fstream>
#include<vector>
#include<numeric>

int main()
{
  std::string line;

  std::ifstream stream("input.txt", std::ifstream::in);

  if (!stream.is_open()) {
    fprintf(stderr, "Failed to open file");
    exit(1);
  }

  int counter = 0;

  // Variable Sliding Window Size
  const int SLIDING_WINDOW_SIZE = 3;

  // Assume no overflow will happen
  std::vector<int> sliding_window(SLIDING_WINDOW_SIZE, INT_MAX / 3);

  int last_size = INT_MAX;

  // Reading in the first window is always smaller than the inital INT_MAX value
  // Because we just care about bigger sized following windows we can read in
  // the inital SLIDING_WINDOW_SIZE values in the normal loop
  while (getline(stream, line)) {

    // Assume input file has correct format
    int current_number = std::stoi(line);

    sliding_window.erase(sliding_window.begin());

    sliding_window.push_back(current_number);

    int current_size = std::accumulate(sliding_window.begin(), sliding_window.end(), 0);

    if (current_size > last_size) {
      counter++;
    }

    last_size = current_size;

  }

  fprintf(stdout, "Success: %d", counter);

  return 0;
}
