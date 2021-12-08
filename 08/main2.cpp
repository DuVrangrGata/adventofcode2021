#include <cstdio>
#include <string>
#include <fstream>

// count the number of overlapping chars based on two strings
int
num_of_overlapping_chars(const std::string & x, const std::string & y)
{
  int result = 0;

  for (size_t i = 0; i < x.length(); i++) {
    for (size_t j = 0; j < y.length(); j++) {
      if (x[i] == y[j]) result++;
    }
  }

  return result;
}

// calculate the digit of 6 char long string representation
// based on overlapping chars with representions of one and four
int
parse_six_letter_repr(const std::string & repr, const std::string & one, const std::string & four)
{

  if (num_of_overlapping_chars(repr, one) == 1) return 6;
  if (num_of_overlapping_chars(repr, four) == 4) return 9;

  return 0;
}

// calculate the digit of 5 char long string representation
// based on overlapping chars with representions of one and four
int
parse_five_letter_repr(const std::string & repr, const std::string & one, const std::string & four)
{

  if (num_of_overlapping_chars(repr, one) == 2) return 3;
  if (num_of_overlapping_chars(repr, four) == 3) return 5;

  return 2;
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

  int result = 0;

  while(getline(stream, line)) {

    std::string repr_four;
    std::string repr_one;

    // Parse for representation of one and four
    while(repr_four.length() == 0 || repr_one.length() == 0) {

      size_t pos = line.find(' ');

      if (pos == 2) repr_one = line.substr(0, pos);
      if (pos == 4) repr_four = line.substr(0, pos);

      line.erase(0, pos + 1);
    }

    // Advanve to last four representions
    size_t pos = line.find('|');
    line.erase(0, pos + 2);

    // calculate digit based on representation
    for (int i = 1000; i >= 1; i /= 10) {
      pos = line.find(' ');
      std::string to_parse = line.substr(0, pos);

      int digit = -1;

      switch(to_parse.length()) {
      case 2:
	digit = 1;
	break;
      case 3:
	digit = 7;
	break;
      case 4:
	digit = 4;
	break;
      case 5:
	digit = parse_five_letter_repr(to_parse, repr_one, repr_four);
	break;
      case 6:
	digit = parse_six_letter_repr(to_parse, repr_one, repr_four);
	break;
      case 7:
	digit = 8;
	break;
      default:
	// incorrect input files are not supported
	fprintf(stderr, "This should not be reached\n");
	exit(1);
      }

      result += i * digit;

      line.erase(0, pos + 1);
    }
  }

  printf("Success: %d\n", result);

  return 0;
}
