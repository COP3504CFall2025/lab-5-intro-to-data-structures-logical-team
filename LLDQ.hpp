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
			list.printForward();
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
			Node<T>* poppedPtr = list.getHead();
			if (!poppedPtr) throw std::runtime_error("cannot pop from empty deque"); 

			list.RemoveHead();

			return poppedPtr->data;
		}
		T popBack() override
		{
			Node<T>* poppedPtr = list.getTail();
			if (!poppedPtr) throw std::runtime_error("cannot pop from empty deque");

			list.RemoveTail();

			return poppedPtr->data;
		}

		// Element Accessors
		T& front() const override
		{
			Node<T>* frontPtr = list.getHead();
			if (!frontPtr) throw std::runtime_error("cannot access front of empty deque");

			return frontPtr->data;
		}
		T& back() const override
		{
			Node<T>* backPtr = list.getTail();
			if (!backPtr) throw std::runtime_error("cannot access back of empty deque");

			return backPtr->data;
		}

		// Getter
		std::size_t getSize() const noexcept override
		{
			return list.getCount();
		}
};






