#pragma once

#include <cstddef>
#include <stdexcept>


template <typename T>
class StackInterface
{

	void push (const T& el);
	T pop ();
	T peek () const;

	std::size_t getSize () const noexcept;

	virtual ~StackInterface () = 0;

};


template <typename T>
class QueueInterface
{

	void enqueue (const T& el);
	T dequeue ();
	T peek () const;

	std::size_t getSize () const noexcept;

	virtual ~QueueInterface () = 0;
};


template <typename T>
class DequeInterface
{

	void pushFront (const T& el);
	void pushBack (const T& el);

	T popFront ();
	T popBack ();
	
	const T& front () const;
	const T& back () const;

	std::size_t getSize () const noexcept;

	virtual ~DequeInterface () = 0;

};

