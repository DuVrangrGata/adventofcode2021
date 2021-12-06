#include <cstdio>
#include <string>
#include <fstream>

#define NUM_OF_DAYS 256

typedef unsigned long long u64;

int main(int argc, char** argv) {

  std::string filename = "input.txt";

  if (argc > 1) {
    filename = argv[1];
  }

  // Parse File
  std::string line;

  std::ifstream stream(filename, std::ifstream::in);

  if (!stream.is_open()) {
    fprintf(stderr, "Failed to open file");
    exit(1);
  }

  // Because the number of fish in each state can be very huge use u64
  u64 fish[9] = {0};

  // Just one line of input
  getline(stream, line);

  size_t pos = line.find(',');

  // Initialize fish count array
  while(pos != std::string::npos) {
    fish[std::stoi(line.substr(0, pos))]++;
    line.erase(0, pos + 1);

    pos = line.find(',');
  }
  fish[std::stoi(line)]++;

  // NOTE: Just using a vector with one element per fish
  // is by far not efficient enough any more

  // Use Array [num_of_zero_state_fish num_of_one_state_fish ... num_of_eight_state_fish]
  // Shift the indicies instead of swapping elements around

  // Keep track of where the zero state fish are
  // and calculate six state fish based on that
  int index_zero = 0;

  for (int day = 0; day < NUM_OF_DAYS; day++) {
    // the only thing that changes in the fish pop
    // every day is that the number of zero state
    // fish gets added to the num of six state fish
    int index_six = (index_zero + 7) % 9;

    fish[index_six] += fish[index_zero];

    index_zero = (index_zero + 1) % 9;
  }

  u64 result = 0;

  for (int i = 0; i < 9; i++) {
    result += fish[i];
  }

  fprintf(stdout, "Success: %lld\n", result);

}
