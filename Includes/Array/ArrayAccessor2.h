/*************************************************************************
> File Name: ArrayAccessor2.h
> Project Name: CubbyFlow
> Author: Chan-Ho Chris Ohk
> Purpose: 2-D array accessor class.
> Created Time: 2017/01/28
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef CUBBYFLOW_ARRAY_ACCESSOR2_H
#define CUBBYFLOW_ARRAY_ACCESSOR2_H

#include <Array/ArrayAccessor.h>

#include <SIze/Size2.h>

namespace CubbyFlow
{
	//!
	//! \brief 2-D array accessor class.
	//!
	//! This class represents 2-D array accessor. Array accessor provides array-like
	//! data read/write functions, but does not handle memory management. Thus, it
	//! is more like a random access iterator, but with multi-dimension support.
	//! Similar to Array<T, 2>, this class interprets a linear array as a 2-D array
	//! using i-major indexing.
	//!
	//! \see Array<T, 2>
	//!
	//! \tparam T - Array value type.
	//!
	template <typename T>
	class ArrayAccessor<T, 2> final
	{
	public:
		//! Constructs empty 2-D array accessor.
		ArrayAccessor();

		//! Constructs an array accessor that wraps given array.
		//! \param size Size of the 2-D array.
		//! \param data Raw array pointer.
		ArrayAccessor(const Size2& size, T* const data);

		//! Constructs an array accessor that wraps given array.
		//! \param width Width of the 2-D array.
		//! \param height Height of the 2-D array.
		//! \param data Raw array pointer.
		ArrayAccessor(size_t width, size_t height, T* const data);

		//! Copy constructor.
		ArrayAccessor(const ArrayAccessor& other);

		//! Replaces the content with given \p other array accessor.
		void Set(const ArrayAccessor& other);

		//! Resets the array.
		void Reset(const Size2& size, T* const data);

		//! Resets the array.
		void Reset(size_t width, size_t height, T* const data);

		//! Returns the reference to the i-th element.
		T& At(size_t i);

		//! Returns the const reference to the i-th element.
		const T& At(size_t i) const;

		//! Returns the reference to the element at (pt.x, pt.y).
		T& At(const Point2UI& pt);

		//! Returns the const reference to the element at (pt.x, pt.y).
		const T& At(const Point2UI& pt) const;

		//! Returns the reference to the element at (i, j).
		T& At(size_t i, size_t j);

		//! Returns the const reference to the element at (i, j).
		const T& At(size_t i, size_t j) const;

		//! Returns the begin iterator of the array.
		T* const Begin() const;

		//! Returns the end iterator of the array.
		T* const End() const;

		//! Returns the begin iterator of the array.
		T* Begin();

		//! Returns the end iterator of the array.
		T* End();

		//! Returns the size of the array.
		Size2 Size() const;

		//! Returns the width of the array.
		size_t Width() const;

		//! Returns the height of the array.
		size_t Height() const;

		//! Returns the raw pointer to the array data.
		T* const Data() const;

		//! Swaps the content of with \p other array accessor.
		void Swap(ArrayAccessor& other);

		//!
		//! \brief Iterates the array and invoke given \p func for each index.
		//!
		//! This function iterates the array elements and invoke the callback
		//! function \p func. The callback function takes array's element as its
		//! input. The order of execution will be the same as the nested for-loop
		//! below:
		//!
		//! \code{.cpp}
		//! int data = {1, 2, 3, 4, 5, 6};
		//! ArrayAccessor<int, 2> acc(2, 3, data);
		//! for (size_t j = 0; j < acc.height(); ++j) {
		//!     for (size_t i = 0; i < acc.width(); ++i) {
		//!         func(acc(i, j));
		//!     }
		//! }
		//! \endcode
		//!
		//! Below is the sample usage:
		//!
		//! \code{.cpp}
		//! int data = {1, 2, 3, 4, 5, 6};
		//! ArrayAccessor<int, 2> acc(2, 3, data);
		//! acc.ForEach([](int elem) {
		//!     printf("%d\n", elem);
		//! });
		//! \endcode
		//!
		template <typename Callback>
		void ForEach(Callback func) const;

		//!
		//! \brief Iterates the array and invoke given \p func for each index.
		//!
		//! This function iterates the array elements and invoke the callback
		//! function \p func. The callback function takes two parameters which are
		//! the (i, j) indices of the array. The order of execution will be the same
		//! as the nested for-loop below:
		//!
		//! \code{.cpp}
		//! int data = {1, 2, 3, 4, 5, 6};
		//! ArrayAccessor<int, 2> acc(2, 3, data);
		//! for (size_t j = 0; j < acc.height(); ++j) {
		//!     for (size_t i = 0; i < acc.width(); ++i) {
		//!         func(i, j);
		//!     }
		//! }
		//! \endcode
		//!
		//! Below is the sample usage:
		//!
		//! \code{.cpp}
		//! int data = {1, 2, 3, 4, 5, 6};
		//! ArrayAccessor<int, 2> acc(2, 3, data);
		//! acc.ForEachIndex([&](size_t i, size_t j) {
		//!     acc(i, j) = 4.f * i + 7.f * j + 1.5f;
		//! });
		//! \endcode
		//!
		template <typename Callback>
		void ForEachIndex(Callback func) const;

		//!
		//! \brief Iterates the array and invoke given \p func for each index in
		//!     parallel.
		//!
		//! This function iterates the array elements and invoke the callback
		//! function \p func. The callback function takes array's element as its
		//! input. The order of execution will be non-deterministic since it runs in
		//! parallel. Below is the sample usage:
		//!
		//! \code{.cpp}
		//! int data = {1, 2, 3, 4, 5, 6};
		//! ArrayAccessor<int, 2> acc(2, 3, data);
		//! acc.ParallelForEach([](int& elem) {
		//!     elem *= 2;
		//! });
		//! \endcode
		//!
		//! The parameter type of the callback function doesn't have to be T&, but
		//! const T& or T can be used as well.
		//!
		template <typename Callback>
		void ParallelForEach(Callback func);

		//!
		//! \brief Iterates the array and invoke given \p func for each index in
		//!     parallel using multi-threading.
		//!
		//! This function iterates the array elements and invoke the callback
		//! function \p func in parallel using multi-threading. The callback
		//! function takes two parameters which are the (i, j) indices of the array.
		//! The order of execution will be non-deterministic since it runs in
		//! parallel. Below is the sample usage:
		//!
		//! \code{.cpp}
		//! int data = {1, 2, 3, 4, 5, 6};
		//! ArrayAccessor<int, 2> acc(2, 3, data);
		//! acc.ParallelForEachIndex([&](size_t i, size_t j) {
		//!     acc(i, j) *= 2;
		//! });
		//! \endcode
		//!
		template <typename Callback>
		void ParallelForEachIndex(Callback func) const;

		//! Returns the linear index of the given 2-D coordinate (pt.x, pt.y).
		size_t Index(const Point2UI& pt) const;

		//! Returns the linear index of the given 2-D coordinate (i, j).
		size_t Index(size_t i, size_t j) const;

		//! Returns the reference to the i-th element.
		T& operator[](size_t i);

		//! Returns the const reference to the i-th element.
		const T& operator[](size_t i) const;

		//! Returns the reference to the element at (pt.x, pt.y).
		T& operator()(const Point2UI& pt);

		//! Returns the const reference to the element at (pt.x, pt.y).
		const T& operator()(const Point2UI& pt) const;

		//! Returns the reference to the element at (i, j).
		T& operator()(size_t i, size_t j);

		//! Returns the const reference to the element at (i, j).
		const T& operator()(size_t i, size_t j) const;

		//! Copies given array accessor \p other.
		ArrayAccessor& operator=(const ArrayAccessor& other);

		//! Casts type to ConstArrayAccessor.
		operator ConstArrayAccessor<T, 2>() const;

	private:
		Size2 m_size;
		T* m_data;
	};

	//! Type alias for 2-D array accessor.
	template <typename T> using ArrayAccessor2 = ArrayAccessor<T, 2>;

	//!
	//! \brief 2-D read-only array accessor class.
	//!
	//! This class represents 2-D read-only array accessor. Array accessor provides
	//! array-like data read/write functions, but does not handle memory management.
	//! Thus, it is more like a random access iterator, but with multi-dimension
	//! support. Similar to Array2<T, 2>, this class interprets a linear array as a
	//! 2-D array using i-major indexing.
	//!
	//! \see Array2<T, 2>
	//!
	template <typename T>
	class ConstArrayAccessor<T, 2> {
	public:
		//! Constructs empty 2-D read-only array accessor.
		ConstArrayAccessor();

		//! Constructs a read-only array accessor that wraps given array.
		//! \param size Size of the 2-D array.
		//! \param data Raw array pointer.
		ConstArrayAccessor(const Size2& size, const T* const data);

		//! Constructs an array accessor that wraps given array.
		//! \param width Width of the 2-D array.
		//! \param height Height of the 2-D array.
		//! \param data Raw array pointer.
		ConstArrayAccessor(
			size_t width, size_t height, const T* const data);

		//! Constructs a read-only array accessor from read/write accessor.
		explicit ConstArrayAccessor(const ArrayAccessor<T, 2>& other);

		//! Copy constructor.
		ConstArrayAccessor(const ConstArrayAccessor& other);

		//! Returns the reference to the i-th element.
		const T& At(size_t i) const;

		//! Returns the const reference to the element at (pt.x, pt.y).
		const T& At(const Point2UI& pt) const;

		//! Returns the const reference to the element at (i, j).
		const T& At(size_t i, size_t j) const;

		//! Returns the begin iterator of the array.
		const T* const Begin() const;

		//! Returns the end iterator of the array.
		const T* const End() const;

		//! Returns the size of the array.
		Size2 Size() const;

		//! Returns the width of the array.
		size_t Width() const;

		//! Returns the height of the array.
		size_t Height() const;

		//! Returns the raw pointer to the array data.
		const T* const Data() const;

		//!
		//! \brief Iterates the array and invoke given \p func for each index.
		//!
		//! This function iterates the array elements and invoke the callback
		//! function \p func. The callback function takes array's element as its
		//! input. The order of execution will be the same as the nested for-loop
		//! below:
		//!
		//! \code{.cpp}
		//! int data = {1, 2, 3, 4, 5, 6};
		//! ConstArrayAccessor<int, 2> acc(2, 3, data);
		//! for (size_t j = 0; j < acc.height(); ++j) {
		//!     for (size_t i = 0; i < acc.width(); ++i) {
		//!         func(acc(i, j));
		//!     }
		//! }
		//! \endcode
		//!
		//! Below is the sample usage:
		//!
		//! \code{.cpp}
		//! int data = {1, 2, 3, 4, 5, 6};
		//! ConstArrayAccessor<int, 2> acc(2, 3, data);
		//! acc.ForEach([](int elem) {
		//!     printf("%d\n", elem);
		//! });
		//! \endcode
		//!
		template <typename Callback>
		void ForEach(Callback func) const;

		//!
		//! \brief Iterates the array and invoke given \p func for each index.
		//!
		//! This function iterates the array elements and invoke the callback
		//! function \p func. The callback function takes two parameters which are
		//! the (i, j) indices of the array. The order of execution will be the same
		//! as the nested for-loop below:
		//!
		//! \code{.cpp}
		//! int data = {1, 2, 3, 4, 5, 6};
		//! ConstArrayAccessor<int, 2> acc(2, 3, data);
		//! for (size_t j = 0; j < acc.height(); ++j) {
		//!     for (size_t i = 0; i < acc.width(); ++i) {
		//!         func(i, j);
		//!     }
		//! }
		//! \endcode
		//!
		//! Below is the sample usage:
		//!
		//! \code{.cpp}
		//! int data = {1, 2, 3, 4, 5, 6};
		//! ConstArrayAccessor<int, 2> acc(2, 3, data);
		//! acc.ForEachIndex([&](size_t i, size_t j) {
		//!     acc(i, j) = 4.f * i + 7.f * j + 1.5f;
		//! });
		//! \endcode
		//!
		template <typename Callback>
		void ForEachIndex(Callback func) const;

		//!
		//! \brief Iterates the array and invoke given \p func for each index in
		//!     parallel using multi-threading.
		//!
		//! This function iterates the array elements and invoke the callback
		//! function \p func in parallel using multi-threading. The callback
		//! function takes two parameters which are the (i, j) indices of the array.
		//! The order of execution will be non-deterministic since it runs in
		//! parallel. Below is the sample usage:
		//!
		//! \code{.cpp}
		//! int data = {1, 2, 3, 4, 5, 6};
		//! ConstArrayAccessor<int, 2> acc(2, 3, data);
		//! acc.ParallelForEachIndex([&](size_t i, size_t j) {
		//!     acc(i, j) *= 2;
		//! });
		//! \endcode
		//!
		template <typename Callback>
		void ParallelForEachIndex(Callback func) const;

		//! Returns the linear index of the given 2-D coordinate (pt.x, pt.y).
		size_t Index(const Point2UI& pt) const;

		//! Returns the linear index of the given 2-D coordinate (i, j).
		size_t Index(size_t i, size_t j) const;

		//! Returns the const reference to the i-th element.
		const T& operator[](size_t i) const;

		//! Returns the const reference to the element at (pt.x, pt.y).
		const T& operator()(const Point2UI& pt) const;

		//! Returns the const reference to the element at (i, j).
		const T& operator()(size_t i, size_t j) const;

	private:
		Size2 m_size;
		const T* m_data;
	};

	//! Type alias for 2-D const array accessor.
	template <typename T> using ConstArrayAccessor2 = ConstArrayAccessor<T, 2>;
}

#include <Array/ArrayAccessor2-Impl.h>

#endif