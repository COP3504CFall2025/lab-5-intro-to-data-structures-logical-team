#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T>
{

	private:
		LinkedList<T> list;

	public:
		// Constructor
		LLS() {}
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
		void push(const T& item) override
		{
			list.AddHead();
		}

		// Deletion
		T pop() override
		{
			T* poppedPtr = list.getHead();
			if (!poppedPtr) throw std::runtime_error("cannot pop from empty stack");

			// need to copy the object before removing it from linked list
			// because removing it will deallocate the original object
			T popped = *poppedPtr;

			list.RemoveHead();

			return popped;
		}

		// Access
		T peek() const override
		{
			T* peeked = list.getHead();

			if (peeked) return *peeked;
			else throw std::runtime_error("cannot peek into empty stack");
		}

		//Getters
		std::size_t getSize() const noexcept override
		{
			return list.getCount();
		}

};


