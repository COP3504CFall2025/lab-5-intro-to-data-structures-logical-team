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
		void printForward() const
		{
			for (Node* el = head; el != nullptr; el = el->next)
			{
				std::cout << el->data << std::endl;
			}
		}
		void printReverse() const
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

			// check if allocation failed
			if (!head)
			{
				head = prevHead;
				throw std::runtime_error("could not insert at head");
			}

			++count;

			if (prevHead) prevHead->prev = head;
		}
		void AddTail(const T& data)
		{
			Node* prevTail = tail;
			tail = new Node{.data = data, .prev = prevTail, .next = nullptr};

			// check if allocation failed
			if (!tail)
			{
				tail = prevTail;
				throw std::runtime_error("could not insert at tail");
			}

			++count;

			if (prevTail) prevTail->next = tail;
		}

		// Removal
		bool RemoveHead()
		{
			if (!head)
			{
				throw std::runtime_error("cannot remove head from empty linked list");
			}

			Node* removable = head;
			Node* newHead = removable->next;

			if (newHead)
			{
				newHead->prev = nullptr;
			}

			head = newHead;

			--count;

			delete removable;
		}
		bool RemoveTail()
		{
			if (!tail)
			{
				throw std::runtime_error("cannot remove tail from empty linked list");
			}

			Node* removable = tail;
			Node* newTail = removable->prev;

			if (newTail)
			{
				newTail->next = nullptr;
			}

			tail = newTail;

			--count;

			delete removable;
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

		LinkedList(const LinkedList<T>& other)
		{
			m_copy(other);
		}
		LinkedList(LinkedList<T>&& other) noexcept
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
				addTail(el->data);
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


