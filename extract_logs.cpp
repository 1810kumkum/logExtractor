#include <bits/stdc++.h>
using namespace std;
std::streampos binary_search_log_start(std::ifstream &file, const std::string &date)
{
  std::streampos left = 0, right;
  file.seekg(0, std::ios::end);
  right = file.tellg();

  while (left < right)
  {
    std::streampos mid = left + (right - left) / 2;
    file.seekg(mid);

    // Move to the start of the line
    std::string dummy;
    std::getline(file, dummy);

    std::streampos pos = file.tellg();
    std::string line;
    if (std::getline(file, line) && line.compare(0, date.size(), date) >= 0)
    {
      right = mid; // Move left
    }
    else
    {
      left = pos; // Move right
    }
  }
  return left;
}

void extract_logs(const std::string &file_path, const std::string &date)
{
  std::filesystem::create_directory("output");
  std::ifstream log_file(file_path);
  std::ofstream output_file("output/output_" + date + ".txt");

  if (!log_file || !output_file)
  {
    std::cerr << "Error: Cannot open log file or create output file.\n";
    return;
  }

  // Find the starting position of logs for the given date
  std::streampos start_pos = binary_search_log_start(log_file, date);
  log_file.seekg(start_pos);

  std::string line;
  while (std::getline(log_file, line))
  {
    if (line.rfind(date, 0) != 0)
      break; // Stop when reaching the next date
    output_file << line << "\n";
  }

  std::cout << "Logs for " << date << " saved in output/output_" << date << ".txt\n";
}

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "Date input required\n";
    return 1;
  }
  extract_logs("./logs_2024.log", argv[1]);
  return 0;
}