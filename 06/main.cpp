#include <cstdio>
#include <string>
#include <fstream>
#include <vector>

#define NUM_OF_DAYS 80

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

  std::vector<int> fish;

  // Just one line of input
  getline(stream, line);

  size_t pos = line.find(',');

  // Initial fish
  while(pos != std::string::npos) {
    fish.push_back(std::stoi(line.substr(0, pos)));
    line.erase(0, pos + 1);

    pos = line.find(',');
  }
  fish.push_back(std::stoi(line));

  // Fish pop growth
  for (int day = 0; day < NUM_OF_DAYS; day++) {
    for (size_t i = 0; i < fish.size(); i++) {
      if (fish[i] == 0) {
	fish[i] = 6;
	// New Fish gets decremented even
	// though it is not present on
	// that day, so state starts at 9
	// to compensate for that
	fish.push_back(9);
      } else {
	fish[i]--;
      }
    }
  }

  size_t result = fish.size();

  fprintf(stdout, "Success: %ld\n", result);

}
