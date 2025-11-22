#include <iostream>
#include <iomanip>

char* getline(std::istream& input, size_t* size)
{
  bool isSkipws = input.flags() & std::ios_base::skipws;
  if (isSkipws)
  {
    input >> std::noskipws;
  }
  size_t extendedSize = 5;
  char* data = reinterpret_cast< char* > (malloc(sizeof(char) * extendedSize));
  if (data == nullptr)
  {
    return data;
  }
  size_t readen = 0;
  input >> data[0];
  while (data[readen] != '\n')
  {
    if (readen == extendedSize - 1)
    {
      extendedSize += 5;
      char* newData = reinterpret_cast< char* > (malloc(sizeof(char) * extendedSize));
      if (newData == nullptr)
      {
        return nullptr;
      }
      for (size_t i = 0; i < extendedSize - 5; ++i)
      {
        newData[i] = data[i];
      }
      free(data);
      data = newData;
    }
    ++readen;
    input >> data[readen];
  }
  data[readen] = '\0';
  if(isSkipws)
  {
    input >> std::skipws;
  }
  *size = readen + 1;
  return data;
}
int main()
{
  size_t size = 0;

  char* array = getline(std::cin, &size);
  if (array == nullptr)
  {
    std::cerr << "Memory error\n";
    return 1;
  }
  std::cout << array;
  std::cout << size;
}