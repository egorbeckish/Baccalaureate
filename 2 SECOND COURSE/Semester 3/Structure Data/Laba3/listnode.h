namespace StructureData
{
	struct Node
	{
		int l_info;
		Node* l_next;
	};

	class ListNode
	{
		private:

			int l_id;
			static int l_value_id;

		public:

			Node* Begin;

			ListNode();
			~ListNode();

			void Insert(int element);
			void Insert_Begin(Node* p, int element);
			void Show(Node *p);
			int Delete(Node* p);
			Node* FindItem(int element);
	};
}
