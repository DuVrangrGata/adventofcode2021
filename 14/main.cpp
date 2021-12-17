#include <cstdio>
#include <string>
#include <fstream>
#include <vector>
#include <climits>
#include <cmath>
#include <cstring>

#define STEPS 10
#define NUM_OF_LETTERS 26

struct entry {
  bool initialized;
  int char_count[NUM_OF_LETTERS];
};

// calculate hash to index a lookuptable for each possible instruction
int
hash(int one, int two)
{
  return (one * NUM_OF_LETTERS) + two;
}

// add each element from the second ptr to the first one
void
merge_char_counts(int* merge_to, int* merge_from)
{
  for (int i = 0; i < NUM_OF_LETTERS; i++) {
    merge_to[i] += merge_from[i];
  }
}


// recursivly fill out dynamic programming table
int*
recursive_polymer_insertion(int a, int b, const int* lookup_table,
			    int depth, entry* dp_table)
{

  // max recursion is the number of pair insertion steps
  if (depth > STEPS) return NULL;

  int index = (a * STEPS * NUM_OF_LETTERS) + (depth * NUM_OF_LETTERS) + b;

  // look up new element from ab
  int to_insert = lookup_table[hash(a, b)];

  // if entry is already computed use that
  if (dp_table[index].initialized) {
    return dp_table[index].char_count;
  }

  // if no entry is precomputed, recursivly compute scenario 'an' and 'nb'
  // where n is the new looked up element
  int* char_count1 = recursive_polymer_insertion(a, to_insert, lookup_table, depth + 1, dp_table);
  int* char_count2 = recursive_polymer_insertion(to_insert, b, lookup_table, depth + 1, dp_table);

  // save result to table and return ptr to that cell
  if (char_count1 != NULL)
    merge_char_counts(dp_table[index].char_count, char_count1);

  if (char_count2 != NULL)
    merge_char_counts(dp_table[index].char_count, char_count2);

  // also count the new looked up char
  dp_table[index].char_count[to_insert]++;
  dp_table[index].initialized = 1;

  return dp_table[index].char_count;
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

  // first line is the starting polymer
  getline(stream, line);
  std::string current_polymer = line;

  // lookup table to save the instructions
  int* lookup_table = (int*)malloc(sizeof(int) * NUM_OF_LETTERS * NUM_OF_LETTERS);

  while(getline(stream, line)) {

    if (line.length() == 0) continue;

    // chars get converted to ints for saving -> A = 0, B = 1 ...
    int index = hash(((int)line[0] - 65), ((int)line[1] - 65));
    lookup_table[index] = ((int)line[6] - 65);
  }

  // the array holds the result and save the occurance of each english alphabet letter
  int char_counts[NUM_OF_LETTERS] = {0};
  int* char_counts_ptr = char_counts;

  // dynamic programming table holds each calculated char_count result
  // by taking the depth and the two chars as input

  const int SIZE_OF_DP_TABLE = sizeof(entry) * NUM_OF_LETTERS * NUM_OF_LETTERS * STEPS;

  entry* dynamic_programming_table = (entry*)malloc(SIZE_OF_DP_TABLE);
  memset(dynamic_programming_table, 0, SIZE_OF_DP_TABLE);

  for (size_t i = 0; i < current_polymer.length() - 1; i++) {

    // for each pair start a recursive call
    int* result_ptr = recursive_polymer_insertion((int)current_polymer[i] - 65,
    				(int)current_polymer[i+1] - 65,
    				lookup_table,
    				1,
    				dynamic_programming_table);

    // append resuls to char counts
    merge_char_counts(char_counts_ptr, result_ptr);
    // dont forget starting polymer chars
    char_counts[((int)current_polymer[i] - 65)]++;
  }

  char_counts[((int)current_polymer[current_polymer.length() - 1] - 65)]++;

  free(dynamic_programming_table);
  free(lookup_table);

  // now just calculate smallest and biggest element of char_counts
  int biggest_num = 0;
  int smallest_num = INT_MAX;

  for(int i = 0; i < NUM_OF_LETTERS; i++) {

    if (char_counts[i] == 0) continue;

    if (char_counts[i] > biggest_num) biggest_num = char_counts[i];
    if (char_counts[i] < smallest_num) smallest_num = char_counts[i];

  }

  printf("Success: %d\n", biggest_num - smallest_num);
  return 0;
}
