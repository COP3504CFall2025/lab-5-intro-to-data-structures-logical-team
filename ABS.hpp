#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {

	public:
		// Big 5 + Parameterized Constructor
		ABS()
			: capacity_(1), curr_size_(0), array_(new T[1])
		{}

		explicit ABS(const size_t capac)
			: capacity_(capac), curr_size_(0), array_(new T[capac])
		{}

		ABS(const ABS& other)
			: capacity_(0), curr_size_(0), array_(nullptr)
		{
			m_copy(other);
		}
		ABS& operator=(const ABS& other)
		{
			return m_copy(other);
		}
		ABS(ABS&& other) noexcept
			: capacity_(0), curr_size_(0), array_(nullptr)
		{
			m_move(std::move(other));
		}
		ABS& operator=(ABS&& other) noexcept
		{
			return m_move(std::move(other));
		}
		~ABS() noexcept override
		{
			delete[] array_;
		}

		// Get the number of items in the ABS
		[[nodiscard]] size_t getSize() const noexcept override
		{
			return curr_size_;
		}

		// Get the max size of the ABS
		[[nodiscard]] size_t getMaxCapacity() const noexcept
		{
			return capacity_;
		}

		// Return underlying data for the stack
		[[nodiscard]] T* getData() const noexcept
		{
			return array_;
		}

		// Push item onto the stack
		void push(const T& el) override
		{

			if (capacity_ == 0)
			{
				capacity_ = 1;

				delete[] array_;
				array_ = new T[1];
			}
			else if (curr_size_ >= capacity_)
			{
				T* oldData = array_;

				capacity_ *= scale_factor_;

				array_ = new T[capacity_];

				for (size_t i = 0; i < curr_size_; ++i)
				{
					array_[i] = oldData[i];
				}

				delete[] oldData;
			}

			array_[curr_size_] = el;

			++curr_size_;

		}

		T& peek() const override
		{
			if (curr_size_ == 0) throw std::runtime_error("cannot peek into empty stack");

			return array_[curr_size_ - 1];
		}

		T pop() override
		{
			if (curr_size_ == 0) throw std::runtime_error("cannot pop from empty stack");

			// copy last element and pop it before proceeding
			T retElement = array_[--curr_size_];

			shrinkIfNeeded();

			return retElement;
		}

		void shrinkIfNeeded ()
		{
			if (capacity_ == 0) return;

			if (curr_size_ * scale_factor_ <= capacity_)
			{
				m_setCapac(capacity_ / scale_factor_);
			}
		}


	private:
		size_t capacity_;
		size_t curr_size_;
		T* array_;
		static constexpr size_t scale_factor_ = 2;

		ABS& m_copy (const ABS &other)
		{
			if (&other == this) return *this;

			if (array_) delete[] array_;

			capacity_ = other.capacity_;
			curr_size_ = other.curr_size_;

			array_ = new T[other.capacity_];

			for (size_t i = 0; i < curr_size_; ++i)
			{
				array_[i] = other.array_[i];
			}

			return *this;
		}
		ABS& m_move (ABS &&other) noexcept
		{
			if (&other == this) return *this;

			if (array_) delete[] array_;

			capacity_ = other.capacity_;
			curr_size_ = other.curr_size_;
			array_ = other.array_;

			other.capacity_ = 0;
			other.curr_size_ = 0;
			other.array_ = new T[0];

			return *this;
		}

		void m_setCapac (size_t capac)
		{
			T* newData = new T[capac];

			for (size_t i = 0; i < curr_size_; ++i)
			{
				newData[i] = array_[i];
			}

			delete[] array_;

			array_ = newData;
			capacity_ = capac;
		}

};
