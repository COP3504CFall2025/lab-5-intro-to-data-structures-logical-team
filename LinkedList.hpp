#pragma once
#include <iostream>

template <typename T>
struct Node
{
	T data;
	Node* prev;
	Node* next;
};


template <typename T>
class LinkedList
{

	public:

		// Behaviors
		void printForward() const
		{
			for (Node<T>* el = head; el != nullptr; el = el->next)
			{
				std::cout << el->data << std::endl;
			}
		}
		void PrintReverse() const
		{
			for (Node<T>* el = tail; el != nullptr; el = el->prev)
			{
				std::cout << el->data << std::endl;
			}
		}

		// Accessors
		[[nodiscard]] unsigned int getCount() const
		{
			return count;
		}
		Node<T>* getHead()
		{
			return head;
		}
		Node<T>* getHead() const
		{
			return head;
		}
		Node<T>* getTail()
		{
			return tail;
		}
		Node<T>* getTail() const
		{
			return tail;
		}

		// Insertion
		void addHead (const T& data) { AddHead(data); }
		void addTail (const T& data) { AddTail(data); }

		void AddHead(const T& data)
		{
			Node<T>* prevHead = head;
			head = new Node<T>{.data = data, .prev = nullptr, .next = prevHead};

			++count;

			if (prevHead) prevHead->prev = head;
			else tail = head;
		}
		void AddTail(const T& data)
		{
			Node<T>* prevTail = tail;
			tail = new Node<T>{.data = data, .prev = prevTail, .next = nullptr};

			++count;

			if (prevTail) prevTail->next = tail;
			else head = tail;
		}

		// Removal
		bool removeHead () { return RemoveHead(); }
		bool removeTail () { return RemoveTail(); }

		bool RemoveHead()
		{
			if (!head) return false;

			Node<T>* removable = head;
			Node<T>* newHead = removable->next;

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

			Node<T>* removable = tail;
			Node<T>* newTail = removable->prev;

			if (newTail) newTail->next = nullptr;
			else head = nullptr;

			tail = newTail;

			--count;

			delete removable;

			return true;
		}

		void clear () { Clear(); }
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
		Node<T>* head;
		Node<T>* tail;
		unsigned int count;

		LinkedList<T>& m_copy (const LinkedList<T> &other)
		{
			if (&other == this) return *this;

			Clear();

			for (Node<T>* el = other.head; el != nullptr; el = el->next)
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


