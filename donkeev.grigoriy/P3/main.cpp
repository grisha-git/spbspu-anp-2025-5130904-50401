#include <iostream>
#include <fstream>

void inputProcessing(int argcCheck, char ** argvCheck)
{
  if (argcCheck > 4)
  {
    throw std::out_of_range("Too many arguments\n");
  }
  else if (argcCheck < 4)
  {
    throw std::out_of_range("Lack of arguments\n");
  }
  size_t i = 0;
  while (argvCheck[1][i] != '\0')
  {
    if (argvCheck[1][i] < '0' || argvCheck[1][i] > '9')
    {
      throw std::invalid_argument("First argument is not a number\n");;
    }
    ++i;
  }
  if (argvCheck[1][1] != '\0')
  {
    throw std::out_of_range("First argument is out of range\n");
  }
  if (argvCheck[1][0] != '1' && argvCheck[1][0] != '2')
  {
    throw std::out_of_range("First argument is out of range\n");
  }
}
int main(int argc, char ** argv)
{
  
  try
  {
    inputProcessing(argc, argv);
  }
  catch (const std::out_of_range &e)
  {
    std::cout << e.what();
    return 1;
  }
  catch (const std::invalid_argument &e)
  {
    std::cout << e.what();
    return 1;
  }
  std::ifstream input(argv[2]);
  std::ofstream output(argv[3]);
  std::cout << "My programm is working well!" << '\n';
}