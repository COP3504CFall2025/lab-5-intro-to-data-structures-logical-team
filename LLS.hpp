#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
	private:
		LinkedList<T> list;

	public:
		// Constructor
		LLS() {}

		// Insertion
		void push(const T& item) override
		{
			list.AddHead();
		}

		// Deletion
		T pop() override
		{
			T* popped = list.getHead();
			list.RemoveHead();

			if (popped) return *popped;
			else throw std::runtime_error("cannot pop from empty stack");
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


