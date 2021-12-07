#include <cstdio>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>

// Takes a sorted vector and gives back the average value
float
average(std::vector<int> & in)
{
  int sum = 0;

  for (int i : in) {
    sum += i;
  }

  return (float)sum / (float)in.size();
}

// Gives back the sum of all integers from 1 to n
int
triangular_number(int n)
{
  return (n * (n+1)) / 2;
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

  // round the average down 
  int avg = average(positions);

  // NOTE: I'm not sure if rounded up or rounded down version of average is better
  //       So i am trying both and take the better result

  // Rounded down
  int result = 0;

  // add distance to median to result
  for (int p : positions) {
    result += triangular_number(std::abs(p - avg));
  }

  // Rounded up
  avg++;
  int tempresult = 0;

  // add distance to median to result
  for (int p : positions) {
    tempresult += triangular_number(std::abs(p - avg));
  }

  // Take better result
  if (tempresult < result) result = tempresult;

  fprintf(stdout, "Success: %d\n", result);
}
