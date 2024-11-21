#pragma once
#include <iostream>
#include <vector>

namespace Graphs
{
    template <class T>
    class Stack
    {
    private:
        Stack(const Stack&);
        Stack& operator=(const Stack&);
        struct Node
        {
            Node* next;
            T value;
            Node(Node* next, const T& value) : next(next), value(value) {}
        };
        Node* base;
        size_t size;
    public:
        Stack() : base(NULL), size(0) {}
        virtual ~Stack() { clear(); }

        bool isEmpty() const { return !base; }
        size_t getSize() const { return size; }
        const T& getHead() const { return base->value; }

        void pop()
        {
            Node* node = base;
            base = base->next;
            delete node;
            --size;
        }

        const T& push(const T& value)
        {
            base = new Node(base, value);
            ++size;
            return base->value;
        }

        void clear()
        {
            while (!isEmpty())
                pop();
            size = 0;
        }

        
        static std::ostream& print(std::ostream& out, Stack<T>& stack)
        {
            if (stack.getSize())
            {
                Stack<T> temp;
                do
                {
                    out << stack.getHead() << ' ';
                    temp.push(stack.getHead());
                    stack.pop();
                } while (!stack.isEmpty());
                out << "\n";

                do
                {
                    stack.push(temp.getHead());
                    temp.pop();
                } while (!temp.isEmpty());
            }
            return out;
        }

        static std::vector<T> getPointerOnArray(Stack<T>& stack)
        {
            if (stack.getSize())
            {
                size_t size = stack.size;
                std::vector<T> array;
                for (unsigned i = 0; i < size; i++)
                {
                    array.push_back(stack.getHead());
                    stack.pop();
                }

                for (int i = size - 1; i >= 0; i--)
                    stack.push(array[i]);
                return array;
            }
            return std::vector<T>();
        }
    };
}