#pragma once
#include <iostream>

template <typename T>
class LinkedList
{

	public:

		struct Node
		{
			T data;
			Node* prev;
			Node* next;
		};

		// Behaviors
		void PrintForward() const
		{
			for (Node* el = head; el != nullptr; el = el->next)
			{
				std::cout << el->data << std::endl;
			}
		}
		void PrintReverse() const
		{
			for (Node* el = tail; el != nullptr; el = el->prev)
			{
				std::cout << el->data << std::endl;
			}
		}

		// Accessors
		[[nodiscard]] unsigned int getCount() const
		{
			return count;
		}
		Node* getHead()
		{
			return head;
		}
		const Node* getHead() const
		{
			return head;
		}
		Node* getTail()
		{
			return tail;
		}
		const Node* getTail() const
		{
			return tail;
		}

		// Insertion
		void AddHead(const T& data)
		{
			Node* prevHead = head;
			head = new Node{.data = data, .prev = nullptr, .next = prevHead};

			++count;

			if (prevHead) prevHead->prev = head;
			else tail = head;
		}
		void AddTail(const T& data)
		{
			Node* prevTail = tail;
			tail = new Node{.data = data, .prev = prevTail, .next = nullptr};

			++count;

			if (prevTail) prevTail->next = tail;
			else head = tail;
		}

		// Removal
		bool RemoveHead()
		{
			if (!head) return false;

			Node* removable = head;
			Node* newHead = removable->next;

			if (newHead) newHead->prev = nullptr;
			else tail = nullptr;

			head = newHead;

			--count;

			delete removable;

			return true;
		}
		bool RemoveTail()
		{
			if (!tail) return false;

			Node* removable = tail;
			Node* newTail = removable->prev;

			if (newTail) newTail->next = nullptr;
			else head = nullptr;

			tail = newTail;

			--count;

			delete removable;

			return true;
		}
		void Clear()
		{
			while (head) RemoveHead();
		}

		// Operators
		LinkedList<T>& operator=(LinkedList<T>&& other) noexcept
		{
			return m_move(std::move(other));
		}
		LinkedList<T>& operator=(const LinkedList<T>& other)
		{
			return m_copy(other);
		}

		// Construction/Destruction
		LinkedList() : head(nullptr), tail(nullptr), count(0) {}

		LinkedList(const LinkedList<T>& other) : head(nullptr), tail(nullptr), count(0)
		{
			m_copy(other);
		}
		LinkedList(LinkedList<T>&& other) noexcept : head(nullptr), tail(nullptr), count(0)
		{
			m_move(std::move(other));
		}

		~LinkedList()
		{
			Clear();
		}

	private:
		// Stores pointers to first and last nodes and count
		Node* head;
		Node* tail;
		unsigned int count;

		LinkedList<T>& m_copy (const LinkedList<T> &other)
		{
			if (&other == this) return *this;

			Clear();

			for (Node* el = other.head; el != nullptr; el = el->next)
			{
				AddTail(el->data);
			}

			return *this;
		}
		LinkedList<T>& m_move (LinkedList<T> &&other) noexcept
		{
			if (&other == this) return *this;

			Clear();

			head = other.head;
			tail = other.tail;
			count = other.count;

			other.head = nullptr;
			other.tail = nullptr;
			other.count = 0;

			return *this;
		}

};


