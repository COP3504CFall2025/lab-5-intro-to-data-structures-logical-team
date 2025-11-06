#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>
#include <iostream>

template <typename T>
class ABDQ : public DequeInterface<T>
{
	private:
		T* data_;                 // underlying dynamic array
		std::size_t capacity_;    // total allocated capacity
		std::size_t size_;        // number of stored elements
		std::size_t front_;       // index of front element
		std::size_t back_;        // index after the last element (circular)

		static constexpr std::size_t SCALE_FACTOR = 2;

		T& m_copy (const T &other)
		{
			if (&other == this) return *this;

			capacity_ = other.capacity_;
			size_ = other.size_;

			front_ = 0;
			back_ = other.size_; // this is correct

			delete[] data_;

			data_ = new T[other.capacity_];

			size_t j = other.front_;
			for (size_t i = 0; i < other.size_; ++i)
			{
				data_[i] = other.data_[j];
				j = (j + 1) % other.capacity_;
			}

			return *this;
		}

		T& m_move (T &&other) noexcept
		{
			if (&other == this) return *this;

			delete[] data_;

			capacity_ = other.capacity_;
			size_ = other.size_;
			front_ = other.front_;
			back_ = other.back_;
			data_ = other.data_;

			other.capacity_ = 0;
			other.size_ = 0;
			other.front_ = 0;
			other.back_ = 0;
			other.data_ = nullptr;

			return *this;
		}

		void m_upscaleCapac (size_t offsetRight)
		{
			if (capacity_ == 0)
			{
				delete[] data_;

				capacity_ = 1;
				data_ = new T[1];

				return;
			}

			m_setCapac(capacity_ * SCALE_FACTOR, offsetRight);
		}

		void m_setCapac (size_t newCapac, size_t offsetRight)
		{
			T* newData = new T[newCapac];

			size_t j = front_;
			for (size_t i = 0; i < size_; ++i)
			{
				newData[(i + offsetRight) % newCapac] = data_[j];
				j = (j + 1) % capacity_;
			}

			front_ = offsetRight;
			back_ = (size_ + offsetRight) % capacity_;

			delete[] data_;

			capacity_ = newCapac;
			data_ = newData;
		}

	public:
		// Big 5
		ABDQ()
			: capacity_(1), size_(0), front_(0), back_(0)
		{
			data_ = new T[1];
		}

		explicit ABDQ(std::size_t capac)
			: capacity_(capac), size_(0), front_(0), back_(0)
		{
			data_ = new T[capac];
		}
		ABDQ(const ABDQ& other)
			: capacity_(0), size_(0), front_(0), back_(0), data_(nullptr)
		{
			m_copy(other);
		}
		ABDQ(ABDQ&& other) noexcept
			: capacity_(0), size_(0), front_(0), back_(0), data_(nullptr)
		{
			m_move(std::move(other));
		}
		ABDQ& operator= (const ABDQ& other)
		{
			return m_copy(other);
		}
		ABDQ& operator= (ABDQ&& other) noexcept
		{
			return m_move(std::move(other));
		}

		~ABDQ() override
		{
			delete[] data_;
		}

		// Insertion
		void pushFront(const T& el) override
		{
			if (size_ == capacity_) m_upscaleCapac(0);

			data_[back_] == el;

			++size_;
			back_ = back_ % capacity_ + 1;
		}
		void pushBack(const T& el) override
		{
			if (size_ == capacity_) m_upscaleCapac(1);

			if (front_ == 0) front_ = capacity_ - 1;
			else --front_;

			data_[front_] == el;

			++size_;
		}

		// Deletion
		T popFront() override
		{
			if (size_ == 0) throw std::runtime_error("cannot pop from empty deque");

			size_t oldFront = front_;

			--size_;
			front_ = (front_ + 1) % capacity_;

			return data_[oldFront];
		}
		T popBack() override
		{
			if (size_ == 0) throw std::runtime_error("cannot pop from empty deque");

			size_t oldBack = back_;

			--size_;
			--back_;
			if (back_ == 0) back_ = capacity_;

			return data_[oldBack - 1];
		}

		// Access
		const T& front() const override
		{
			return data_[front_];
		}
		const T& back() const override
		{
			return data_[back_ - 1];
		}

		void ensureCapacity ()
		{
			m_setCapac(size_ * 2, 0);
		}
		void shrinkIfNeeded ()
		{
			if (capacity_ == 0) return;

			if (size_ * 2 <= capacity_)
			{
				m_setCapac(capacity_ / 2);
			}
		}

		void PrintForward ()
		{
			size_t j = front_;
			for (size_t i = 0; i < size_; ++i)
			{
				std::cout << data_[j] << std::endl;
				j = (j + 1) % capacity_;
			}
		}

		void PrintReverse ()
		{

			size_t j = back_ - 1;
			for (size_t i = 0; i < size_; ++i)
			{
				std::cout << data_[j] << std::endl;
				if (j == 0) j = capacity_ - 1;
				else --j;
			}
		}

		// Getters
		std::size_t getSize() const noexcept override
		{
			return size_;
		}

};
