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
  if (argvCheck[1][0] <= '9' && argvCheck[1][0] > '2')
  {
    throw std::out_of_range("First argument is out of range\n");
  }
  if (argvCheck[1][0] < '0' || argvCheck[1][0] > '9')
  {
    throw std::invalid_argument("First argument is not a number\n");
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
  
}