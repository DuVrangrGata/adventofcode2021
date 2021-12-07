#include <cstdio>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>


// Takes a sorted Vector and gives back the median value
float
median(std::vector<int> & in)
{
  // if size is odd, median is just the only middle value of vector
  if (in.size() % 2 != 0) {
    int median_index = in.size() / 2;
    return in[median_index];
  } else {
  //  if size is even, median is between the two middle values of vector
    int median_index_1 = in.size() / 2;
    // -1 accounts for the zero indexing
    int median_index_2 = median_index_1 - 1;
    return (float)(in[median_index_1] + in[median_index_2]) / (float)2;
  }
  return 0;
}

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

  // Just one line of input
  getline(stream, line);

  // unknown num of positions
  std::vector<int> positions;

  // Parse the line
  size_t pos;
  while((pos = line.find(',')) != std::string::npos) {
    positions.push_back(std::stoi(line.substr(0, pos)));
    line.erase(0, pos + 1);
  }
  positions.push_back(std::stoi(line));

  // calculate median of vector
  std::sort(positions.begin(), positions.end());
  int med = median(positions);

  int result = 0;

  // add distance to median to result
  for (int p : positions) {
    result += std::abs(p - med);
  }

  fprintf(stdout, "Success: %d\n", result);
}
