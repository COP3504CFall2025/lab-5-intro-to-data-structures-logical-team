#pragma once

#include <cstddef>
#include <stdexcept>
#include <iostream>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{

	private:
		size_t capacity_;
		
		size_t front_;
		size_t back_;

		size_t size_; // just for user convenience, but not actually used in calculations

		T* array_;

		static constexpr size_t scale_factor_ = 2;

		ABQ& m_copy (const ABQ &other)
		{
			if (&other == this) return *this;

			delete[] array_;

			capacity_ = other.capacity_;
			front_ = 0;
			back_ = other.size_; // yes, this line should say other.size_
			size_ = other.size_;

			array_ = new T[capacity_];

			int j = front_;
			for (size_t i = 0; i < size_; ++i)
			{
				array_[i] = other.array_[j];
				j = (j + 1) % capacity_;
			}

			return *this;
		}
		ABQ& m_move (ABQ &&other) noexcept
		{
			if (&other == this) return *this;

			delete[] array_;

			capacity_ = other.capacity_;
			front_ = other.front_;
			back_ = other.back_;
			array_ = other.array_;
			size_ = other.size_;

			other.capacity_ = 0;
			other.front_ = 0;
			other.back_ = 0;
			other.size_ = 0;
			other.array_ = new T[0];

			return *this;
		}

	public:
		// Constructors + Big 5
		ABQ()
			: capacity_(0), front_(0), back_(0), size_(0), array_(new T[0])
		{}

		explicit ABQ(const size_t capac)
			: capacity_(capac), front_(0), back_(0), size_(0), array_(new T[capac])
		{}

		ABQ(const ABQ& other)
			: capacity_(0), front_(0), back_(0), size_(0), array_(nullptr)
		{
			m_copy(other);
		}
		ABQ& operator=(const ABQ& other)
		{
			return m_copy(other);
		}
		ABQ(ABQ&& other) noexcept
			: capacity_(0), front_(0), back_(0), size_(0), array_(nullptr)
		{
			m_move(std::move(other));
		}
		ABQ& operator=(ABQ&& other) noexcept
		{
			return m_move(std::move(other));
		}
		~ABQ() noexcept override
		{
			delete[] array_;
		}

		// Getters
		[[nodiscard]] size_t getSize() const noexcept override
		{
			return size_;
		}
		[[nodiscard]] size_t getMaxCapacity() const noexcept
		{
			return capacity_;
		}
		[[nodiscard]] T* getData() const noexcept
		{
			return array_;
		}

		// Insertion
		void enqueue(const T& el) override
		{
			if (capacity_ == 0)
			{
				capacity_ = 1;

				delete[] array_;
				array_ = new T[1];
			}
			if (size_ == capacity_)
			{
				T* oldData = array_;
				size_t oldCapac = capacity_;

				capacity_ *= scale_factor_;

				array_ = new T[capacity_];

				size_t j = front_;
				for (size_t i = 0; i < size_; ++i)
				{
					array_[i] = oldData[j];
					j = (j + 1) % oldCapac;
				}

				front_ = 0;
				back_ = size_;

				delete[] oldData;
			}

			array_[back_ % capacity_] = el;

			back_ = back_ % capacity_ + 1;
			++size_;
		}

		// Access
		T peek() const override
		{
			if (size_ == 0) throw std::runtime_error("cannot peek into empty queue");

			return array_[front_];
		}

		// Deletion
		T dequeue() override
		{
			if (size_ == 0) throw std::runtime_error("cannot dequeue from empty queue");

			size_t retInd = back_ - 1;

			--back_;
			if (back_ == 0) back_ = capacity_;

			--size_;

			return array_[retInd];
		}

		void PrintForward ()
		{
			size_t j = front_;
			for (size_t i = 0; i < size_; ++i)
			{
				std::cout << array_[j] << std::endl;
				j = (j + 1) % capacity_;
			}
		}

		void PrintReverse ()
		{
			size_t j = back_ - 1;
			for (size_t i = 0; i < size_; ++i)
			{
				std::cout << array_[j] << std::endl;
				if (j == 0) j = capacity_ - 1;
				else --j;
			}
		}

};
