#include<stdio.h>
#include<limits.h>
#include<string>
#include<fstream>

int main()
{
  std::string line;

  std::ifstream stream("input.txt", std::ifstream::in);

  if (!stream.is_open()) {
    fprintf(stderr, "Failed to open file");
    exit(1);
  }

  // Assume no overflow will happen
  int last_number = INT_MAX;
  int counter = 0;

  while (getline(stream, line)) {

    int current_number = std::stoi(line);

    if (current_number > last_number) {
      counter++;
    }

    last_number = current_number;

  }

  fprintf(stdout, "Success: %d", counter);

  return 0;
}
