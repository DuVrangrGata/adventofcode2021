#include <cstdio>
#include <string>
#include <fstream>

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

  int result = 0;

  while(getline(stream, line)) {

    size_t len = line.find('|');
    // Erase delim and empty space
    line.erase(0, len + 2);

    while((len = line.find(' ')) != std::string::npos) {

      // Count 'easy' numbers
      if (len == 2 || len == 3 || len == 4 || len == 7) result++;
      line.erase(0, len + 1);
    }

    // One last number
    len = line.length();
    if (len == 2 || len == 3 || len == 4 || len == 7) result++;

  }

  printf("Success: %d\n", result);

  return 0;
}
