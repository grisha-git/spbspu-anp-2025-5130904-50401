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
std::istream & reading(std::istream & input, int & target)
{
  return input >> target;
}
void readingRowsCols(std::istream & input, int * matrixSize)
{
  reading(input, matrixSize[0]);
  if (!input)
  {
    throw std::invalid_argument("Input error");
  }
  reading(input, matrixSize[1]);
  if (!input)
  {
    throw std::invalid_argument("Input error");
  }
}
void readingMatrix(std::istream & input, int * matrix, const size_t rows, const size_t cols)
{
  for (size_t i = 0; i < rows * cols; ++i)
  {
    reading(input, matrix[i]);
    if (!input)
    {
      throw std::invalid_argument("Input error");
    }
  }
  int try_value = 0;
  reading(input, try_value);
  if (input || !input.eof())
  {
    throw std::out_of_range("Too much arguments");
  }
}
bool isFinish(size_t lim_u, size_t lim_r, size_t lim_d, size_t lim_l)
{
  bool temp = lim_u == lim_r;
  temp = temp && lim_u == lim_d;
  temp = temp && lim_u == lim_l;
  return temp;
}
void LFT_BOT_CLK(int * new_matrix, const size_t & rows, const size_t & cols)
{ 
  size_t lastVisitedUp = 0;
  size_t lastVisitedDown = rows + 1;
  size_t lastVisitedRight = cols + 1;
  size_t lastVisitedLeft = 0;
  size_t position = (rows - 1) * cols;
  int minus_counter = 1;
  //furst up
  new_matrix[position] -= minus_counter;
  ++minus_counter;
  for (size_t i = 0; i < rows - 1; ++i)
  {
    position -= cols;
    new_matrix[position] -= minus_counter;
    ++minus_counter;
  }
  ++lastVisitedLeft;
  while (true)
  {
    for (size_t i = 0; i < lastVisitedRight - lastVisitedLeft - 1; ++i)
    {
      position += 1;
      new_matrix[position] -= minus_counter;
      ++minus_counter;
    }
    ++lastVisitedUp;
    if (lastVisitedDown - lastVisitedUp == 1)
    {
      return;
    }
    for (size_t i = 0; i < lastVisitedDown - lastVisitedUp - 1; ++i)
    {
      position += cols;
      new_matrix[position] -= minus_counter;
      ++minus_counter;
    }
    --lastVisitedRight;
    if (lastVisitedRight - lastVisitedLeft == 1)
    {
      return;
    }
    for (size_t i = 0; i < lastVisitedRight - lastVisitedLeft - 1; ++i)
    {
      position -= 1;
      new_matrix[position] -= minus_counter;
      ++minus_counter;
    }
    --lastVisitedDown;
    if (lastVisitedRight - lastVisitedLeft == 1)
    {
      return;
    }
    for (size_t i = 0; i < lastVisitedDown - lastVisitedUp - 1; ++i)
    {
      position -= cols;
      new_matrix[position] -= minus_counter;
      ++minus_counter;
    }
    ++lastVisitedLeft;
    if (lastVisitedRight - lastVisitedLeft == 1)
    {
      return;
    }
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
  if (!input)
  {
    std::cout << "File error\n";
    return 2;
  }
  int matrixSize[2] = {};
  try
  {
    readingRowsCols(input, matrixSize);
  }
  catch (std::invalid_argument& e)
  {
    std::cerr << e.what() << '\n';
    return 2;
  }
  size_t rows = matrixSize[0];
  size_t cols = matrixSize[1];
  int tempMatrix1[rows * cols] = {};
  int * tempMatrix2 = nullptr;
  try
  {
    tempMatrix2 = new int [rows * cols];
  }
  catch(const std::bad_alloc &e)
  {
      std::cerr << e.what() << '\n';
  }
  int * matrix = argv[1][0] == '1' ? tempMatrix1 : tempMatrix2; 
  try
  {
    readingMatrix(input, matrix, rows, cols);
  }
  catch (const std::bad_alloc& e)
  {
    std::cerr << "Memory error\n";
    return 2;
  }
  catch (const std::invalid_argument& e)
  {
    std::cerr << e.what() << '\n';
    return 2;
  }
  catch (const std::out_of_range& e)
  {
    std::cerr << e.what() << '\n';
    return 2;
  }
  LFT_BOT_CLK(matrix, rows, cols);
  if (argv[1][0] == '2')
  {
    delete [] matrix;
  }
}