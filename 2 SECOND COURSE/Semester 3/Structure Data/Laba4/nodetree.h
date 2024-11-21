#pragma once
#include <fstream>
#include <iostream>

int getInt(int left = -2'147'483'648, int right = 2'147'483'647);


class NodeTree
{
private:
    int* key;
    NodeTree* Left;
    NodeTree* Right;
public:
    // CreateTree()
    NodeTree(int* number = nullptr) : key{ number }, Left { nullptr }, Right{ nullptr } { }
    ~NodeTree();
    const NodeTree& AddNode(int number);


    //считывание с клавиатуры
    const NodeTree& inputDataTree();
    //считывание из файла
    const NodeTree& inputFileTree(std::string fileName = "bintree.txt");
    //заполнение рандомом
    const NodeTree& randomTree(int size = 15);

    const NodeTree& PrintTree(int height=5);
    bool Delete(int number);
    NodeTree* Del(NodeTree& P);
    int countGreater(int N = 0) const;
    NodeTree* Search_Tree(NodeTree& P, int number);
};
