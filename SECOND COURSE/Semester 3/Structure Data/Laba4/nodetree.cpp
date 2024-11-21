#include "nodetree.h"
#include <time.h>

int getInt(int left, int right)
{
    while (true) // цикл продолжается до тех пор, пока пользователь не введет корректное значение
    {
        int number;
        std::cin >> number;

        // Проверка на предыдущее извлечение
        if (std::cin.fail()) // если предыдущее извлечение оказалось неудачным,
        {
            std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
            std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
        }
        else
        {
            std::cin.ignore(32767, '\n'); // удаляем лишние значения
            if (number >= left && number <= right) return number;
        }
        std::cout << "\n\tOh... Input value not correct. Try again!\n\t";
    }
}

const NodeTree& NodeTree::AddNode(int number)
{
    if (!key)
    {
        key = new int;
        *key = number;
    }
    else if (number < *key)
         {
            if(!Left) Left = new NodeTree;
            Left->AddNode(number);
         }
         else
         {
             if(!Right) Right = new NodeTree;
             Right->AddNode(number);
         }
    return *this;
}

bool NodeTree::Delete(int number)
{
    if (number < *key) { if (Left->Delete(number)) Left = nullptr; }
    else if (number > *key) { if (Right->Delete(number)) Right = nullptr; }
    else
        if (!Left && !Right)
        {
            delete this;
            return true;
        }
        else if (!Left)
        {
            delete key;
            *this = *Right;
        }
        else if (!Right)
        {
            delete key;
            *this = *Left;
        }
        else Right = Right->Del(*this);


    return false;
}

NodeTree* NodeTree::Search_Tree(NodeTree& P, int number)
{
    if (*key == number) { *this; }
    if (number < *key) { return Search_Tree(*Left, number); }
    else { return Search_Tree(*Right, number); }
}

NodeTree* NodeTree::Del(NodeTree& P)
{
    if (!Left)
    {
        delete P.key;
        P.key = key;
        key = nullptr;
        return Right;
    }
    else { Left = Left->Del(P); return this; }
}

NodeTree::~NodeTree()
{
    if (key)
    {
        delete Left;
        delete Right;
        delete key;
        key = nullptr;
    }
}


const NodeTree& NodeTree::PrintTree(int h)
{
    
    if(Right) Right->PrintTree(h + 1);
    for (int i = 0; i < h; i++) std::cout << ' ';
    std::cout << *key  << std::endl;
    if(Left) Left->PrintTree(h + 1);
    return *this;
}

//заполнение рандомом
const NodeTree& NodeTree::randomTree(int size)
{
    srand(time(NULL));
    rand();
    for(; size > 0; size--) AddNode(rand() % 100);
    return *this;
}


//считывание с клавиатуры
const NodeTree& NodeTree::inputDataTree()
{
    int number, size;
    std::cout << "\n\tHow many elements will be written to the tree: ";
    size = getInt(1);
    do {
        number = getInt();
        AddNode(number);
        size--;
    } while (size > 0);
    return *this;
}

//считывание из файла
const NodeTree& NodeTree::inputFileTree(std::string fileName)
{
    std::ifstream FileIn(fileName);
    if (!FileIn.is_open())
        throw "\n\tInput file <", fileName, "> can't open!\n";
    else
    {
        int number;
        while (!FileIn.eof())
        {// Проводим полное считывание данных в дерево
            FileIn >> number;
            std::cout << "Enter number: " << number << std::endl;
            AddNode(number);
        }
    }
    FileIn.close();
    return *this;
}

/*необходимо подсчитать число элементов, больше заданного, которое вводится с клавиатуры.*/
int NodeTree::countGreater(int number) const
{
    int counter = 0;
    if (*key > number) counter++;
    if (Right) counter += Right->countGreater(number);
    if (Left) counter += Left->countGreater(number);
    return counter;
}
