#pragma once
#include <vector>
#include <utility>
#include <set>
#include "ListNode.h"
#include "Stack.h"

namespace Graphs
{
	template <class T>
	class Graph
	{
	private:
		std::vector<ListNode<T>> AdjacencyLists;
	public:
		Graph(const std::vector<ListNode<T>>& List)
		{
			for (unsigned i = 0; i < List.size(); i++)
				AdjacencyLists.push_back(List[i]);
		}

		std::vector<T> Euler()
		{
			Stack<T> stack1, stack2;
			stack1.push(AdjacencyLists[0][0]);
			int iter = 0;
			while (!stack1.isEmpty())
			{
				if (AdjacencyLists[stack1.getHead() - 1].getSize() != 1)
				{
					T v = AdjacencyLists[stack1.getHead() - 1][0];
					T w = AdjacencyLists[stack1.getHead() - 1][1];
					stack1.push(w);
					AdjacencyLists[v - 1].deleteNode(&AdjacencyLists[v - 1]);
					AdjacencyLists[w - 1].deleteNode(AdjacencyLists[w - 1].find(v));
				}
				else
				{
					stack2.push(stack1.getHead());
					stack1.pop();
				}
				
			}
			return Stack<T>::getPointerOnArray(stack2);
		}

	};

	template <class T>
	class Graph<std::pair<T, T>>
	{
	private:
		std::vector<ListNode<std::pair<T, T>>> AdjacencyLists; 
	public:
		Graph(const std::vector<ListNode<std::pair<T, T>>>& List)
		{
			for (unsigned i = 0; i < List.size(); i++)
				AdjacencyLists.push_back(List[i]);
		}

		std::vector<std::pair<T, T>> Euler()
		{
			Stack<std::pair<T, T>> stack1, stack2;
			stack1.push(AdjacencyLists[0][0]);
			int iter = 0;
			while (!stack1.isEmpty())
			{
				if (AdjacencyLists[stack1.getHead().first - 1].getSize() != 1)
				{
					std::pair<T, T> v = AdjacencyLists[stack1.getHead().first - 1][0];
					std::pair<T, T> w = AdjacencyLists[stack1.getHead().first - 1][1];
					stack1.push(w);
					AdjacencyLists[v.first - 1].deleteNode(&AdjacencyLists[v.first - 1]);
					AdjacencyLists[w.first - 1].deleteNode(AdjacencyLists[w.first - 1].find(v));
				}
				else
				{
					stack2.push(stack1.getHead());
					stack1.pop();
				}
			}
			return Stack<std::pair<T, T>>::getPointerOnArray(stack2);
		}

		std::vector<T> Dijkstra(T start)
		{
			std::vector<T> shortestD;
			for (int i = 0; i < AdjacencyLists.size(); i++)
				shortestD.push_back(INT_MAX);

			shortestD[start - 1] = 0;
			std::set<T> S_m, T_m;
			S_m.insert(start);
			T prev = start;
			for (int i = 0; i < AdjacencyLists.size(); i++)
				if (AdjacencyLists[i][0].first != start)
					T_m.insert(AdjacencyLists[i][0].first);


			while (!T_m.empty())
			{
				T min_vertex = *T_m.begin();
				for (auto& element : T_m)
				{

					if (AdjacencyLists[prev - 1].find(element).second != INT_MAX)
						shortestD[element - 1] = std::min(shortestD[element - 1],
							shortestD[prev - 1] + AdjacencyLists[prev - 1].find(element).second);
					if (shortestD[min_vertex - 1] > shortestD[element - 1]) min_vertex = element;

				}
				if (shortestD[min_vertex - 1] == INT_MAX) break;
				prev = min_vertex;
				S_m.insert(prev); T_m.erase(prev);
			}
			return shortestD;
		}
	};
}