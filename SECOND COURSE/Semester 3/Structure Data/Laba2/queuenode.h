#pragma once

namespace StructureData
{
	class QueueNode
	{
		private:
			
			// информационное поле элемента очереди
			int q_info;

			//указатель на следующий элемент очереди
			QueueNode* q_next;
			
			//Указатель на начальный элемент очереди
			static QueueNode* q_BeginEven;
			static QueueNode* q_BeginOdd;

			//Указатель на конечный элемент очереди
			static QueueNode* q_EndEven;
			static QueueNode* q_EndOdd;

		public:

			// инициализация очереди
			QueueNode();
			
			// Добавление элемента в очередь, в которой структурированны 3 подочереди
			const QueueNode& EnQueueEven(int);
			const QueueNode& EnQueueOdd(int);

			// Возвращение элемента из очереди
			int DeQueueEven();
			int DeQueueOdd();

			// Проверка на пустую очередь
			bool IsEmptyEven();
			bool IsEmptyOdd();

			// Проверка на заполненую очередь
			bool IsFullEven();
			bool IsFullOdd();

			// Возвращение верхушки очереди
			int Top();
	};

}	
