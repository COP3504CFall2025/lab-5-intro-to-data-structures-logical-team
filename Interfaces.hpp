#pragma once

#include <cstddef>
#include <stdexcept>


template <typename T>
class StackInterface
{

	public:
		virtual void push (const T& el) = 0;
		virtual T pop () = 0;
		virtual T peek () const = 0;

		virtual std::size_t getSize () const noexcept = 0;

		virtual ~StackInterface () = 0;

};

template <typename T>
StackInterface<T>::~StackInterface () {}


template <typename T>
class QueueInterface
{

	public:
		virtual void enqueue (const T& el) = 0;
		virtual T dequeue () = 0;
		virtual T peek () const = 0;

		virtual std::size_t getSize () const noexcept = 0;

		virtual ~QueueInterface () = 0;

};

template <typename T>
QueueInterface<T>::~QueueInterface () {}


template <typename T>
class DequeInterface
{

	public:
		virtual void pushFront (const T& el) = 0;
		virtual void pushBack (const T& el) = 0;

		virtual T popFront () = 0;
		virtual T popBack () = 0;

		virtual const T& front () const = 0;
		virtual const T& back () const = 0;

		virtual std::size_t getSize () const noexcept = 0;

		virtual ~DequeInterface () = 0;

};

template <typename T>
DequeInterface<T>::~DequeInterface () {}

