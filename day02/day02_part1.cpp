#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <sstream>

const int MIN_DIFF = 1;
const int MAX_DIFF = 3;

int get_level(const std::string &line) {
    int value;
    std::vector<int> values_line;
    std::istringstream stream(line);
    bool is_sorted_ascending = true;
    bool is_sorted_descending = true;

    while (stream >> value)
        values_line.push_back(value);
    if (values_line.size() < 2)
      return 0;
    for (size_t i = 1; i < values_line.size(); ++i) {
      if (values_line[i] < values_line[i - 1])
	is_sorted_ascending = false;
      if (values_line[i] > values_line[i - 1])
	is_sorted_descending = false;
    }
    if (!is_sorted_ascending && !is_sorted_descending)
        return 0;
    for (size_t i = 1; i < values_line.size(); ++i) {
      int diff_ab = std::abs(values_line[i] - values_line[i - 1]);
      if (diff_ab < MIN_DIFF || diff_ab > MAX_DIFF)
	return 0;
    }
    return 1;
}

void read_file(const std::string& file) {
    std::string line;
    int safe_path = 0;
    std::ifstream input(file);
    if (!input.is_open()) {
        std::cerr << "Error: Failed to open file: " << file << std::endl;
        return;
    }
    while (std::getline(input, line)) {
      if (!line.empty()) 
	safe_path += get_level(line);
    }
    input.close();
    std::cout << safe_path << std::endl;
}

int main(int ac, const char *av[]) {
  if (ac != 2) {
    std::cerr << "Usage: ./day02_part1 <input_file>\n";
        return 1;
  }
  read_file(av[1]);
  return 0;
}
