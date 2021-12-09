#include <cstdio>
#include <string>
#include <fstream>
#include <vector>


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

  // Unknown num of lines at start
  std::vector<std::string> lines;

  while(getline(stream, line)) {
    lines.push_back(line);
  }

  int result = 0;

  for (size_t j = 0; j < lines.size(); j++) {
    for (size_t i = 0; i < lines[j].length(); i++) {

      char to_compare = lines[j][i];

      if (i > 0)                     if (lines[j][i-1] <= to_compare) continue;
      if (i < lines[j].length() - 1) if (lines[j][i+1] <= to_compare) continue;
      if (j > 0)                     if (lines[j-1][i] <= to_compare) continue;
      if (j < lines.size() - 1)      if (lines[j+1][i] <= to_compare) continue;

      //printf("[%ld,%ld], %c, %d\n", i, j, to_compare, (int)to_compare);

      result += (int)to_compare - 47;
    }
  }

  printf("Success: %d\n", result);
  return 0;
}
