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

	public:
		// Big 5
		ABDQ();
		explicit ABDQ(std::size_t capacity);
		ABDQ(const ABDQ& other);
		ABDQ(ABDQ&& other) noexcept;
		ABDQ& operator=(const ABDQ& other);
		ABDQ& operator=(ABDQ&& other) noexcept;
		~ABDQ() override;

		// Insertion
		void pushFront(const T& item) override;
		void pushBack(const T& item) override;

		// Deletion
		T popFront() override;
		T popBack() override;

		// Access
		const T& front() const override;
		const T& back() const override;

		// Getters
		std::size_t getSize() const noexcept override;

};
