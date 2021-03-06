/*************************************************************************
> File Name: BoundingBox-Impl.h
> Project Name: CubbyFlow
> Author: Dongmin Kim
> Purpose: Generic N-D axis-aligned bounding box class.
> Created Time: 2017/03/30
> Copyright (c) 2017, Dongmin Kim
*************************************************************************/
#ifndef CUBBYFLOW_BOUNDING_BOX_IMPL_H
#define CUBBYFLOW_BOUNDING_BOX_IMPL_H

#include <Utils/MathUtils.h>

namespace CubbyFlow
{
	template <typename T, size_t N>
	BoundingBox<T, N>::BoundingBox()
	{
		Reset();
	}

	template <typename T, size_t N>
	BoundingBox<T, N>::BoundingBox(const VectorType& point1, const VectorType& point2)
	{
		for (size_t i = 0; i < N; ++i)
		{
			lowerCorner[i] = std::min(point1[i], point2[i]);
			upperCorner[i] = std::max(point1[i], point2[i]);
		}
	}

	template <typename T, size_t N>
	BoundingBox<T, N>::BoundingBox(const BoundingBox& other) :
		lowerCorner(other.lowerCorner), upperCorner(other.upperCorner)
	{
		// Do nothing
	}

	template <typename T, size_t N>
	bool BoundingBox<T, N>::Overlaps(const BoundingBox& other) const
	{
		for (size_t i = 0; i < N; ++i)
		{
			if (upperCorner[i] < other.lowerCorner[i] || lowerCorner[i] > other.upperCorner[i])
			{
				return false;
			}
		}

		return true;
	}

	template <typename T, size_t N>
	bool BoundingBox<T, N>::Contains(const VectorType& point) const
	{
		for (size_t i = 0; i < N; ++i)
		{
			if (upperCorner[i] < point[i] || lowerCorner[i] > point[i])
			{
				return false;
			}
		}

		return true;
	}

	template <typename T, size_t N>
	Vector<T, N> BoundingBox<T, N>::MidPoint() const
	{
		Vector<T, N> result;

		for (size_t i = 0; i < N; ++i)
		{
			result[i] = (upperCorner[i] + lowerCorner[i]) / 2;
		}

		return result;
	}

	template <typename T, size_t N>
	T BoundingBox<T, N>::DiagonalLength() const
	{
		T result = 0;

		for (size_t i = 0; i < N; ++i)
		{
			result += Square(upperCorner[i] - lowerCorner[i]);
		}

		return std::sqrt(result);
	}

	template <typename T, size_t N>
	T BoundingBox<T, N>::DiagonalLengthSquared() const
	{
		T result = 0;

		for (size_t i = 0; i < N; ++i)
		{
			result += square(upperCorner[i] - lowerCorner[i]);
		}

		return result;
	}

	template <typename T, size_t N>
	void BoundingBox<T, N>::Reset()
	{
		for (size_t i = 0; i < N; ++i)
		{
			lowerCorner[i] = std::numeric_limits<T>::max();
			upperCorner[i] = -std::numeric_limits<T>::max();
		}
	}

	template <typename T, size_t N>
	void BoundingBox<T, N>::Merge(const VectorType& point)
	{
		for (size_t i = 0; i < N; ++i)
		{
			lowerCorner[i] = std::min(lowerCorner[i], point[i]);
			upperCorner[i] = std::max(upperCorner[i], point[i]);
		}
	}

	template <typename T, size_t N>
	void BoundingBox<T, N>::Merge(const BoundingBox& other)
	{
		for (size_t i = 0; i < N; ++i)
		{
			lowerCorner[i] = std::min(lowerCorner[i], other.lowerCorner[i]);
			upperCorner[i] = std::max(upperCorner[i], other.upperCorner[i]);
		}
	}

	template <typename T, size_t N>
	void BoundingBox<T, N>::Expand(T delta)
	{
		for (size_t i = 0; i < N; ++i)
		{
			lowerCorner[i] -= delta;
			upperCorner[i] += delta;
		}
	}
}

#endif