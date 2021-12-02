
#include<stdio.h>
#include<string>
#include<fstream>
#include<sstream>

enum identifier {
  FORWARD,
  UP,
  DOWN,
  // This should never occur
  UNKNOWN
};

// Parse String for switch Statement
identifier get_identifier(const std::string & in)
{

  if (in == "forward") {
    return FORWARD;
  } else if (in == "up") {
    return UP;
  } else if (in == "down") {
    return DOWN;
  }

  return UNKNOWN;
}

int main()
{

  std::string line;

  std::ifstream stream("input.txt", std::ifstream::in);

  if (!stream.is_open()) {
    fprintf(stderr, "Failed to open file");
    exit(1);
  }

  int horizontal = 0;
  int depth = 0;

  while (getline(stream, line)) {

    // Parse String
    std::stringstream ss(line);
    std::string iden;
    int amount;
    ss >> iden>> amount;

    switch(get_identifier(iden)) {
    case FORWARD:
      horizontal += amount;
      break;
    case UP:
      depth -= amount;
      break;
    case DOWN:
      depth += amount;
      break;
    case UNKNOWN:
    default:
      // Do not handle incorrectly formated input
      fprintf(stderr, "This should never be reached");
      exit(1);
      break;
    }
  }

  fprintf(stdout, "Success: %d", horizontal * depth);

  return 0;
}
