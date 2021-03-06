/*************************************************************************
> File Name: Matrix2x2-Impl.h
> Project Name: CubbyFlow
> Author: Dongmin Kim
> Purpose: 2-D matrix class.
> Created Time: 2017/03/06
> Copyright (c) 2017, Dongmin Kim
*************************************************************************/
#ifndef CUBBYFLOW_MATRIX2X2_IMPL_H
#define CUBBYFLOW_MATRIX2X2_IMPL_H

#include <cassert>
#include <complex.h>

namespace CubbyFlow
{
	template <typename T>
	Matrix<T, 2, 2>::Matrix() :
		m_elements(1, 0,
				   0, 1)
	{
		// Do nothing
	}

	template <typename T>
	Matrix<T, 2, 2>::Matrix(T s) :
		m_elements(s, s,
				   s, s)
	{
		// Do nothing
	}

	template <typename T>
	Matrix<T, 2, 2>::Matrix(T m00, T m01,
							T m10, T m11) :
		m_elements(m00, m01,
				   m10, m11)
	{
		// Do nothing
	}

	template <typename T>
	template <typename U>
	Matrix<T, 2, 2>::Matrix(const std::initializer_list<std::initializer_list<U>>& list)
	{
		Set(list);
	}

	template <typename T>
	Matrix<T, 2, 2>::Matrix(const Matrix& m)
	{
		Set(m);
	}

	template <typename T>
	Matrix<T, 2, 2>::Matrix(const T* arr) :
		m_elements(arr[0], arr[1],
				   arr[2], arr[3])
	{
		// Do nothing
	}

	template <typename T>
	void Matrix<T, 2, 2>::Set(T s)
	{
		m_elements[0] = s;
		m_elements[1] = s;
		m_elements[2] = s;
		m_elements[3] = s;
	}

	template <typename T>
	void Matrix<T, 2, 2>::Set(T m00, T m01,
							  T m10, T m11)
	{
		m_elements[0] = m00;
		m_elements[1] = m01;
		m_elements[2] = m10;
		m_elements[3] = m11;
	}

	template <typename T>
	template <typename U>
	void Matrix<T, 2, 2>::Set(const std::initializer_list<std::initializer_list<U>>& list)
	{
		size_t height = list.size();
		size_t width = (height > 0) ? list.begin()->size() : 0;

		assert(width == 2);
		assert(height == 2);

		auto rowIter = list.begin();
		for (size_t i = 0; i < height; ++i)
		{
			assert(width == rowIter->size());

			auto colIter = rowIter->begin();
			for (size_t j = 0; j < width; ++j)
			{
				(*this)(i, j) = static_cast<T>(*colIter);
				++colIter;
			}

			++rowIter;
		}
	}

	template <typename T>
	void Matrix<T, 2, 2>::Set(const Matrix& m)
	{
		m_elements = m.m_elements;
	}
	
	template <typename T>
	void Matrix<T, 2, 2>::Set(const T* arr)
	{
		for (size_t i = 0; i < 4; ++i)
		{
			m_elements[i] = arr[i];
		}
	}

	template <typename T>
	void Matrix<T, 2, 2>::SetDiagonal(T s)
	{
		m_elements[0] = s;
		m_elements[3] = s;
	}

	template <typename T>
	void Matrix<T, 2, 2>::SetOffDiagonal(T s)
	{
		m_elements[1] = s;
		m_elements[2] = s;
	}

	template <typename T>
	void Matrix<T, 2, 2>::SetRow(size_t i, const Vector2<T>& row)
	{
		m_elements[i * 2] = row.x;
		m_elements[i * 2 + 1] = row.y;
	}

	template <typename T>
	void Matrix<T, 2, 2>::SetColumn(size_t i, const Vector2<T>& col)
	{
		m_elements[i] = col.x;
		m_elements[i + 2] = col.y;
	}

	template <typename T>
	bool Matrix<T, 2, 2>::IsSimilar(const Matrix& m, double tol = std::numeric_limits<double>::epsilon()) const
	{
		for (size_t i = 0; i < 4; ++i)
		{
			if (std::fabs(m_elements[i] - m.m_elements[i]) > tol)
			{
				return false;
			}
		}

		return true;
	}

	template <typename T>
	bool Matrix<T, 2, 2>::IsSquare() const
	{
		return true;
	}

	template <typename T>
	size_t Matrix<T, 2, 2>::Rows() const
	{
		return 2;
	}

	template <typename T>
	size_t Matrix<T, 2, 2>::Cols() const
	{
		return 2;
	}

	template <typename T>
	T* Matrix<T, 2, 2>::Data()
	{
		return m_elements.data();
	}

	template <typename T>
	const T* Matrix<T, 2, 2>::Data() const
	{
		return m_elements.data();
	}

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::Add(T s) const
	{
		return Matrix<T, 2, 2>(
			m_elements[0] + s, m_elements[1] + s,
			m_elements[2] + s, m_elements[3] + s);
	}

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::Add(const Matrix& m) const
	{
		return Matrix<T, 2, 2>(
			m_elements[0] + m.m_elements[0], m_elements[1] + m.m_elements[1],
			m_elements[2] + m.m_elements[2], m_elements[3] + m.m_elements[3]);
	}
	
	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::Sub(T s) const
	{
		return Matrix<T, 2, 2>(
			m_elements[0] - s, m_elements[1] - s,
			m_elements[2] - s, m_elements[3] - s);
	}

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::Sub(const Matrix& m) const
	{
		return Matrix<T, 2, 2>(
			m_elements[0] - m.m_elements[0], m_elements[1] - m.m_elements[1],
			m_elements[2] - m.m_elements[2], m_elements[3] - m.m_elements[3]);
	}

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::Mul(T s) const
	{
		return Matrix<T, 2, 2>(
			m_elements[0] * s, m_elements[1] * s,
			m_elements[2] * s, m_elements[3] * s);
	}

	template <typename T>
	Vector2<T> Matrix<T, 2, 2>::Mul(const Vector2<T> & v) const
	{
		return Vector<T, 2>(
			m_elements[0] * v.x + m_elements[1] * v.y,
			m_elements[2] * v.x + m_elements[3] * v.y);
	}

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::Mul(const Matrix& m) const
	{
		return Matrix<T, 2, 2>(
			m_elements[0] * m.m_elements[0] + m_elements[1] * m.m_elements[2],
			m_elements[0] * m.m_elements[1] + m_elements[1] * m.m_elements[3],
			m_elements[2] * m.m_elements[0] + m_elements[3] * m.m_elements[2],
			m_elements[2] * m.m_elements[1] + m_elements[3] * m.m_elements[3]);
	}

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::Div(T s) const
	{
		return Matrix<T, 2, 2>(
			m_elements[0] / s, m_elements[1] / s,
			m_elements[2] / s, m_elements[3] / s);
	}

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::RAdd(T s) const
	{
		return Matrix<T, 2, 2>(
			s + m_elements[0], s + m_elements[1],
			s + m_elements[2], s + m_elements[3]);
	}

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::RAdd(const Matrix& m) const
	{
		return Matrix<T, 2, 2>(
			m.m_elements[0] + m_elements[0], m.m_elements[1] + m_elements[1],
			m.m_elements[2] + m_elements[2], m.m_elements[3] + m_elements[3]);
	}

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::RSub(T s) const
	{
		return Matrix<T, 2, 2>(
			s - m_elements[0], s - m_elements[1],
			s - m_elements[2], s - m_elements[3]);
	}

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::RSub(const Matrix& m) const
	{
		return Matrix<T, 2, 2>(
			m.m_elements[0] - m_elements[0], m.m_elements[1] - m_elements[1],
			m.m_elements[2] - m_elements[2], m.m_elements[3] - m_elements[3]);
	}

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::RMul(T s) const
	{
		return Matrix<T, 2, 2>(
			s * m_elements[0], s * m_elements[1],
			s * m_elements[2], s * m_elements[3]);
	}

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::RMul(const Matrix& m) const
	{
		return m.Mul(*this);
	}

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::RDiv(T s) const
	{
		return Matrix<T, 2, 2>(
			s / m_elements[0], s / m_elements[1],
			s / m_elements[2], s / m_elements[3]);
	}

	template <typename T>
	void Matrix<T, 2, 2>::IAdd(T s)
	{
		m_elements[0] += s;
		m_elements[1] += s;
		m_elements[2] += s;
		m_elements[3] += s;
	}

	template <typename T>
	void Matrix<T, 2, 2>::IAdd(const Matrix& m)
	{
		m_elements[0] += m.m_elements[0];
		m_elements[1] += m.m_elements[1];
		m_elements[2] += m.m_elements[2];
		m_elements[3] += m.m_elements[3];
	}

	template <typename T>
	void Matrix<T, 2, 2>::ISub(T s)
	{
		m_elements[0] -= s;
		m_elements[1] -= s;
		m_elements[2] -= s;
		m_elements[3] -= s;
	}

	template <typename T>
	void Matrix<T, 2, 2>::ISub(const Matrix& m)
	{
		m_elements[0] -= m.m_elements[0];
		m_elements[1] -= m.m_elements[1];
		m_elements[2] -= m.m_elements[2];
		m_elements[3] -= m.m_elements[3];
	}

	template <typename T>
	void Matrix<T, 2, 2>::IMul(T s)
	{
		m_elements[0] *= s;
		m_elements[1] *= s;
		m_elements[2] *= s;
		m_elements[3] *= s;
	}

	template <typename T>
	void Matrix<T, 2, 2>::IMul(const Matrix& m)
	{
		Set(Mul(m));
	}

	template <typename T>
	void Matrix<T, 2, 2>::IDiv(T s)
	{
		m_elements[0] /= s;
		m_elements[1] /= s;
		m_elements[2] /= s;
		m_elements[3] /= s;
	}

	template <typename T>
	void Matrix<T, 2, 2>::Transpose()
	{
		std::swap(m_elements[1], m_elements[2]);
	}

	template <typename T>
	void Matrix<T, 2, 2>::Invert()
	{
		Set(Matrix(m_elements[3], -m_elements[1], -m_elements[2], m_elements[1]) / Determinant());
	}

	template <typename T>
	T Matrix<T, 2, 2>::Sum() const
	{
		T sum = 0;

		for (int i = 0; i < 4; ++i)
		{
			sum += m_elements[i];
		}

		return sum;
	}

	template <typename T>
	T Matrix<T, 2, 2>::Avg() const
	{
		return Sum() / 4;
	}

	template <typename T>
	T Matrix<T, 2, 2>::Min() const
	{
		return std::min_element(m_elements.begin(), m_elements.end());
	}

	template <typename T>
	T Matrix<T, 2, 2>::Max() const
	{
		return std::max_element(m_elements.begin(), m_elements.end());
	}

	template <typename T>
	T Matrix<T, 2, 2>::AbsMin() const
	{
		// TODO: Consider T is integral type.
		return std::min({ std::fabs(m_elements[0]), std::fabs(m_elements[1]), std::fabs(m_elements[2]), std::fabs(m_elements[3]) });
	}

	template <typename T>
	T Matrix<T, 2, 2>::AbsMax() const
	{
		// TODO: Consider T is integral type.
		return std::max({ std::fabs(m_elements[0]), std::fabs(m_elements[1]), std::fabs(m_elements[2]), std::fabs(m_elements[3]) });
	}

	template <typename T>
	T Matrix<T, 2, 2>::Trace() const
	{
		return m_elements[0] + m_elements[3];
	}

	template <typename T>
	T Matrix<T, 2, 2>::Determinant() const
	{
		return
			  m_elements[0] * m_elements[3]
			- m_elements[1] * m_elements[2];
	}

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::Diagonal() const
	{
		return Matrix<T, 2, 2>(
			m_elements[0], 0,
			0, m_elements[3]);
	}

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::OffDiagonal() const
	{
		return Matrix<T, 2, 2>(
			0, m_elements[1],
			m_elements[2], 0);
	}

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::StrictLowerTriangle() const
	{
		return Matrix<T, 2, 2>(
			0, 0,
			m_elements[2], 0);
	}

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::StrictUpperTriangle() const
	{
		return Matrix<T, 2, 2>(
			0, m_elements[1],
			0, 0);
	}

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::LowerTriangle() const
	{
		return Matrix<T, 2, 2>(
			m_elements[0], 0,
			m_elements[2], m_elements[3]);
	}

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::UpperTriangle() const
	{
		return Matrix<T, 2, 2>(
			m_elements[0], m_elements[1],
			0, m_elements[3]);
	}

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::Transposed() const
	{
		return Matrix<T, 2, 2>(
			m_elements[0], m_elements[2],
			m_elements[1], m_elements[3]);
	}

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::Inverse() const
	{
		Matrix m(*this);
		m.Invert();
		return m;
	}

	template <typename T>
	template <typename U>
	Matrix<U, 2, 2> Matrix<T, 2, 2>::CastTo() const
	{
		return Matrix<U, 2, 2>(
			static_cast<U>(m_elements[0]),
			static_cast<U>(m_elements[1]),
			static_cast<U>(m_elements[2]),
			static_cast<U>(m_elements[3]));
	}

	template <typename T>
	Matrix<T, 2, 2>& Matrix<T, 2, 2>::operator=(const Matrix& m)
	{
		Set(m);
		return *this;
	}

	template <typename T>
	Matrix<T, 2, 2>& Matrix<T, 2, 2>::operator+=(const Matrix& m)
	{
		IAdd(m);
		return *this;
	}
	
	template <typename T>
	Matrix<T, 2, 2>& Matrix<T, 2, 2>::operator+=(T s)
	{
		IAdd(s);
		return *this;
	}

	template <typename T>
	Matrix<T, 2, 2>& Matrix<T, 2, 2>::operator-=(const Matrix& m)
	{
		ISub(m);
		return *this;
	}

	template <typename T>
	Matrix<T, 2, 2>& Matrix<T, 2, 2>::operator-=(T s)
	{
		ISub(s);
		return *this;
	}

	template <typename T>
	Matrix<T, 2, 2>& Matrix<T, 2, 2>::operator*=(const Matrix& m)
	{
		IMul(m);
		return *this;
	}

	template <typename T>
	Matrix<T, 2, 2>& Matrix<T, 2, 2>::operator*=(T s)
	{
		IMul(s);
		return *this;
	}

	template <typename T>
	Matrix<T, 2, 2>& Matrix<T, 2, 2>::operator/=(T s)
	{
		IDiv(s);
		return *this;
	}

	template <typename T>
	T& Matrix<T, 2, 2>::operator[](size_t i)
	{
		return m_elements[i];
	}
	
	template <typename T>
	const T& Matrix<T, 2, 2>::operator[](size_t i) const
	{
		return m_elements[i];
	}

	template <typename T>
	T& Matrix<T, 2, 2>::operator()(size_t i, size_t j)
	{
		return m_elements[i * 2 + j];
	}

	template <typename T>
	const T& Matrix<T, 2, 2>::operator()(size_t i, size_t j) const
	{
		return m_elements[i * 2 + j];
	}

	template <typename T>
	bool Matrix<T, 2, 2>::operator==(const Matrix& m) const
	{
		for (size_t i = 0; i < 4; ++i)
		{
			if (m_elements[i] != m.m_elements[i])
			{
				return false;
			}
		}

		return true;
	}

	template <typename T>
	bool Matrix<T, 2, 2>::operator!=(const Matrix& m) const
	{
		return !(*this == m);
	}

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::MakeZero()
	{
		return Matrix<T, 2, 2>(0, 0, 0, 0);
	}

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::MakeIdentity()
	{
		return Matrix<T, 2, 2>(1, 0, 0, 1);
	}

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::MakeScaleMatrix(T sx, T sy)
	{
		return Matrix<T, 2, 2>(sx, 0, 0, sy);
	}

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::MakeScaleMatrix(const Vector2<T>& s)
	{
		return MakeScaleMatrix(s.x, s.y);
	}

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::MakeRotationMatrix(const T& rad)
	{
		return Matrix<T, 2, 2>(
			std::cos(rad), -std::sin(rad),
			std::sin(rad),  std::cos(rad));
	}

	template <typename T>
	Matrix<T, 2, 2> operator-(const Matrix<T, 2, 2>& a)
	{
		return a.Mul(-1);
	}

	template <typename T>
	Matrix<T, 2, 2> operator+(const Matrix<T, 2, 2>& a, const Matrix<T, 2, 2>& b)
	{
		return a.Add(b);
	}

	template <typename T>
	Matrix<T, 2, 2> operator+(const Matrix<T, 2, 2>& a, const T b)
	{
		return a.Add(b);
	}

	template <typename T>
	Matrix<T, 2, 2> operator+(const T a, const Matrix<T, 2, 2>& b)
	{
		return b.RAdd(a);
	}

	template <typename T>
	Matrix<T, 2, 2> operator-(const Matrix<T, 2, 2>& a, const Matrix<T, 2, 2>& b)
	{
		return a.Sub(b);
	}

	template <typename T>
	Matrix<T, 2, 2> operator-(const Matrix<T, 2, 2>& a, const T b)
	{
		return a.Sub(b);
	}

	template <typename T>
	Matrix<T, 2, 2> operator-(const T a, const Matrix<T, 2, 2>& b)
	{
		return b.RSub(a);
	}

	template <typename T>
	Matrix<T, 2, 2> operator*(const Matrix<T, 2, 2>& a, const T b)
	{
		return a.Mul(b);
	}

	template <typename T>
	Matrix<T, 2, 2> operator*(const T a, const Matrix<T, 2, 2>& b)
	{
		return b.RMul(a);
	}

	template <typename T>
	Vector2<T> operator*(const Matrix<T, 2, 2>& a, const Vector2<T>& b)
	{
		return a.Mul(b);
	}

	template <typename T>
	Matrix<T, 2, 2> operator*(const Matrix<T, 2, 2>& a, const Matrix<T, 2, 2>& b)
	{
		return a.Mul(b);
	}

	template <typename T>
	Matrix<T, 2, 2> operator/(const Matrix<T, 2, 2>& a, T b)
	{
		return a.Div(b);
	}

	template <typename T>
	Matrix<T, 2, 2> operator/(T a, const Matrix<T, 2, 2>& b)
	{
		return b.RDiv(a);
	}
}

#endif