#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>


template <typename T>
class LLDQ : public DequeInterface<T>
{
	private:
		LinkedList<T> list;

	public:
		// Constructor
		LLDQ() {}
		// Default big-five are fine, because this class doesn't directly manage dynamic data

		void PrintForward ()
		{
			list.PrintForward();
		}

		void PrintReverse ()
		{
			list.PrintReverse();
		}

		// Core Insertion Operations
		void pushFront(const T& el) override
		{
			list.AddHead(el);
		}

		void pushBack(const T& el) override
		{
			list.AddTail(el);
		}

		// Core Removal Operations
		T popFront() override
		{
			T* poppedPtr = list.getHead();
			if (!poppedPtr) throw std::runtime_error("cannot pop from empty deque"); 

			list.RemoveHead();

			return *poppedPtr;
		}
		T popBack() override
		{
			T* poppedPtr = list.getTail();
			if (!poppedPtr) throw std::runtime_error("cannot pop from empty deque");

			list.RemoveTail();

			return *poppedPtr;
		}

		// Element Accessors
		const T& front() const override
		{
			T* frontPtr = list.getHead();
			if (!frontPtr) throw std::runtime_error("cannot access front of empty deque");

			return *frontPtr;
		}
		const T& back() const override
		{
			T* backPtr = list.getTail();
			if (!backPtr) throw std::runtime_error("cannot access back of empty deque");

			return *backPtr;
		}

		// Getter
		std::size_t getSize() const noexcept override
		{
			return list.getCount();
		}
};






