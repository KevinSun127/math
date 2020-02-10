#include "matrix.h"
//displays possible options to user
void displayMenu()
{
  // Choices:
    // 1. 'm' calls multiplication
    // 2. 'a' calls addition
    // 3. 's' calls subtraction
    // 4. 'r' resets the working matrix
    // 5. 'd' displays the working matrix
    // 6. 'f' starts fraction conversion
    // 7. 'i' returns inverse

  std::cout << "Options:" << std::endl;
  std::cout << "m: mutliply" << std::endl;
  std::cout <<"a: add" << std::endl;
  std::cout <<"s: subtract" << std::endl;
  std::cout <<"r: reset"<<std::endl;
  std::cout<<"d: display matrix"<<std::endl;
  std::cout<<"f: fraction-to_double" << std::endl;
  std::cout<<"i: inverse" << std::endl;
}

//checks whether user choice is a viable one
bool find(const char& item, const char* list, const size_t len)
{
  for(size_t i = 0; i < len; ++i)
  {
    if(list[i] == item)
      return true;
  }
  return false;
}

//asks user for row, column values
Matrix promptValues()
{
  int row, col;
  std::cout << "Enter Non-Negative Number of Rows." << std::endl;
  while(!(std::cin >> row) || row <= 0 || row%1 != 0)
  {
    std::cin.clear();
    std::cin.ignore();
    std::cout << "Enter Non-Negative Integer of Rows." << std::endl;
  }
  std::cout << "Enter Non-Negative Integer of Columns." << std::endl;
  while(!(std::cin >> col) || col <= 0 || col%1 != 0)
  {
    std::cin.clear();
    std::cin.ignore();
    std::cout << "Enter Non-Negative Number of Columns." << std::endl;
  }
  std::cout << std::endl;

  //declares new matrix, has the user enter values into it
  Matrix initialMatrix(row, col);

  while(!initialMatrix.enterValues())
  {
    std::cin.clear();
    std::cin.ignore();
  }

  return initialMatrix;
}


int main(){
  char choice;
  char choices[] = {'m', 'a', 's', 'r', 'd', 'f', 'i'};

  std::cout << "Initial Matrix:" << std::endl;
  Matrix initialMatrix = promptValues();

  do
  {
    std::string buffer;
    // acquires user decision
    displayMenu();
    getline(std::cin, buffer);
    std::cin >> choice;
    std::cout << std::endl;

    //if the user wants to restart with a fresh matrix
    if(choice == 'r')
    {
      std::cout << "Reseting Initial Matrix:" << std::endl;
      initialMatrix = promptValues();
    }

    else if(choice == 'm')
    {
      std::cout << "Creating Next Matrix" << std::endl;
      Matrix secondMatrix = promptValues();

      //rows of matrix 1 must equal columns of matrix 2
      if(initialMatrix.colCount() == secondMatrix.rowCount())
      {
        std::cout << "Multiplying!" << std::endl;
        std::cout << (initialMatrix*=secondMatrix) << std::endl;
      }
      else
      {
        std::cout << "Re-enter matrix. Rows do not match columns" << std::endl;
      }
    }
    else if(choice == 'a')
    {
      //creates second matrix
      std::cout << "Creating Next Matrix" << std::endl;
      Matrix secondMatrix = promptValues();

      //adds matrix if the dimesnions are identical
      if(initialMatrix.rowCount() == secondMatrix.rowCount() &&
        initialMatrix.colCount() == secondMatrix.colCount())
      {
        std::cout << "Adding!" << std::endl;
        std::cout << (initialMatrix+=secondMatrix) << std::endl;
      }

      else
      {
        std::cout << "Dimensions must be identical." << std::endl;
      }
    }
    else if(choice == 's')
    {
      //creates second matrix
      std::cout << "Creating Next Matrix" << std::endl;
      Matrix secondMatrix = promptValues();

      //adds matrix if the dimesnions are identical
      if(initialMatrix.rowCount() == secondMatrix.rowCount() &&
        initialMatrix.colCount() == secondMatrix.colCount())
      {
        std::cout << "Subtracting!" << std::endl;
        std::cout << (initialMatrix-=secondMatrix) << std::endl;
      }

      else
      {
        std::cout << "Dimensions must be identical." << std::endl;
      }
    }

    //displays matrix
    else if(choice == 'd')
    {
      std::cout << initialMatrix << std::endl;
    }

    else if(choice == 'f')
    {
      std::cout << "Enter Fraction" << std::endl;
      char slash;
      int num, denom;
      std::cin >> num >> slash >> denom;
      std::cout << (num*1.0)/denom << std::endl;
    }

    else if(choice == 'i')
    {
      std::cout << "Inverse!" << std::endl;
      std::cout << (initialMatrix=initialMatrix.inverse()) << std::endl;
    }

  } while(find(choice, choices, 7));

  return 0;
}


//Unimplemented Save Prompt
bool savePrompt()
{
  char choice;
  std::cout << "Save Value? [y/n]" << std::endl;
  std::cin >> choice;
  if(choice == 'y')
    return true;
  return false;
}
