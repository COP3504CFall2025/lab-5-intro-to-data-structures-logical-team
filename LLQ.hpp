#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T>
{

	private:
		LinkedList<T> list;

	public:
		// Constructor
		LLQ() {}
		// Default big-five are fine, because this class doesn't directly manage dynamic data

		void PrintForward ()
		{
			list.PrintForward();
		}

		void PrintReverse ()
		{
			list.PrintReverse();
		}

		// Insertion
		void enqueue(const T& el) override
		{
			list.AddTail(el);
		}

		// Deletion
		T dequeue() override
		{
			Node<T>* dequeuedPtr = list.head;
			if (!dequeuedPtr) throw std::runtime_error("cannot dequeue from empty queue");

			// need to copy the object before removing it from linked list
			// because removing it will deallocate the original object
			T dequeued = dequeuedPtr->data;

			list.RemoveHead();

			return dequeued;
		}

		// Access
		T peek() const override
		{
			Node<T>* peeked = list.head;
			if (!peeked) throw std::runtime_error("cannot peek into empty queue");

			return peeked->data;
		}

		// Getter
		std::size_t getSize() const noexcept override
		{
			return list.getCount();
		}

};
