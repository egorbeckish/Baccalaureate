#include <iostream>
#include "nodetree.cpp"
#include <fstream>
#include <time.h>


int getInt(int left, int right);
int main()
{
    setlocale(LC_ALL, "Rus");
    std::cout << "\n\tIn program is formed binary search tree:"
              << "\n\tChoose way create tree (1,2 or 3):"
              << "\n\t1) input keyboard"
              << "\n\t2) read from file"
              << "\n\t3) generating a given number of elements with random values\n\t";
    int choice = getInt(1, 3);
    
    // std::ifstream input("input.txt");
    NodeTree BinaryTree;
    switch (choice) 
    {
    case 1://ввод с клавиатуры
        BinaryTree.inputDataTree();
        break;
    case 2://считывание из файла
        BinaryTree.inputFileTree("input.txt");
        break;
    case 3://заполнение рандомом
        BinaryTree.randomTree();
        break;
    default:
        std::cout << "\n\tOh... It's so bad...\n\t";
    }
    std::cout << "\n";
    BinaryTree.PrintTree();

    std::cout << "\n\tCount the number of elements greater than the specified one. Enter the specified element: ";
    int N;
    N = getInt();
    std::cout <<  "\n\tThe number of elements larger than the specified: " << BinaryTree.countGreater(N) << std::endl;
    std::cout << "\n\tEnter the item you would like to delete:\t";
    N = getInt();
    BinaryTree.Delete(N);
    std::cout << "\n";
    BinaryTree.PrintTree();

    return 0;
}
