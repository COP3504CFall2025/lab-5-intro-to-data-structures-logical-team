#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

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

		void m_upscaleCapac ()
		{
			if (capacity_ == 0)
			{
				delete[] data_;

				capacity_ = 1;
				data_ = new T[1];

				return;
			}

			size_t oldCapac = capacity_;
			T* oldData = data_;

			capacity_ *= SCALE_FACTOR;
			data_ = new T[capacity_];

			size_t j = front_;
			for (size_t i = 0; i < size_; ++i)
			{
				data_[i] = oldData[j];
				j = (j + 1) % oldCapac;
			}

			front_ = 0;
			back_ = size_;

			delete[] oldData;
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
		ABDQ& operator=(const ABDQ& other)
		{
			return m_copy(other);
		}
		ABDQ& operator=(ABDQ&& other) noexcept
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
			if (size_ == capacity_) m_upscaleCapac();

			data_[back_] == el;

			++size_;
			back_ = back_ % capacity_ + 1;
		}
		void pushBack(const T& el) override;

		// Deletion
		T popFront() override;
		T popBack() override;

		// Access
		const T& front() const override;
		const T& back() const override;

		// Getters
		std::size_t getSize() const noexcept override;

};
