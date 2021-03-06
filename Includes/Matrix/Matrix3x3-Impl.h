/*************************************************************************
> File Name: Matrix3x3-Impl.h
> Project Name: CubbyFlow
> Author: Dongmin Kim
> Purpose: 3-D matrix class.
> Created Time: 2017/03/07
> Copyright (c) 2017, Dongmin Kim
*************************************************************************/
#ifndef CUBBYFLOW_MATRIX3X3_IMPL_H
#define CUBBYFLOW_MATRIX3X3_IMPL_H

#include <cassert>

namespace CubbyFlow
{
	template <typename T>
	Matrix<T, 3, 3>::Matrix()
	{
		Set(1, 0, 0,
			0, 1, 0,
			0, 0, 1);
	}

	template <typename T>
	Matrix<T, 3, 3>::Matrix(T s)
	{
		Set(s);
	}

	template <typename T>
	Matrix<T, 3, 3>::Matrix(T m00, T m01, T m02, 
							T m10, T m11, T m12, 
							T m20, T m21, T m22)
	{
		Set(m00, m01, m02,
			m10, m11, m12,
			m20, m21, m22);
	}

	template <typename T>
	template <typename U>
	Matrix<T, 3, 3>::Matrix(const std::initializer_list<std::initializer_list<U>>& list)
	{
		Set(list);
	}

	template <typename T>
	Matrix<T, 3, 3>::Matrix(const Matrix& m)
	{
		Set(m);
	}

	template <typename T>
	Matrix<T, 3, 3>::Matrix(const T* arr) :
		m_elements(arr[0], arr[1], arr[2],
				   arr[3], arr[4], arr[5],
				   arr[6], arr[7], arr[8])
	{
		// Do nothing
	}

	template <typename T>
	void Matrix<T, 3, 3>::Set(T s)
	{
		m_elements[0] = s;
		m_elements[1] = s;
		m_elements[2] = s;
		m_elements[3] = s;
		m_elements[4] = s;
		m_elements[5] = s;
		m_elements[6] = s;
		m_elements[7] = s;
		m_elements[8] = s;
	}

	template <typename T>
	void Matrix<T, 3, 3>::Set(T m00, T m01, T m02,
							  T m10, T m11, T m12,
							  T m20, T m21, T m22)
	{
		m_elements[0] = m00;
		m_elements[1] = m01;
		m_elements[2] = m02;
		m_elements[3] = m10;
		m_elements[4] = m11;
		m_elements[5] = m12;
		m_elements[6] = m20;
		m_elements[7] = m21;
		m_elements[8] = m22;
	}

	template <typename T>
	template <typename U>
	void Matrix<T, 3, 3>::Set(const std::initializer_list<std::initializer_list<U>>& list)
	{
		size_t height = list.size();
		size_t width = (height > 0) ? list.begin()->size() : 0;

		assert(width == 3);
		assert(height == 3);

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
	void Matrix<T, 3, 3>::Set(const Matrix& m)
	{
		m_elements = m.m_elements;
	}

	template <typename T>
	void Matrix<T, 3, 3>::Set(const T* arr)
	{
		for (size_t i = 0; i < 9; ++i)
		{
			m_elements[i] = arr[i];
		}
	}

	template <typename T>
	void Matrix<T, 3, 3>::SetDiagonal(T s)
	{
		m_elements[0] = s;
		m_elements[4] = s;
		m_elements[8] = s;
	}

	template <typename T>
	void Matrix<T, 3, 3>::SetOffDiagonal(T s)
	{
		m_elements[1] = s;
		m_elements[2] = s;
		m_elements[3] = s;
		m_elements[5] = s;
		m_elements[6] = s;
		m_elements[7] = s;
	}

	template <typename T>
	void Matrix<T, 3, 3>::SetRow(size_t i, const Vector3<T>& row)
	{
		m_elements[i * 3] = row.x;
		m_elements[i * 3 + 1] = row.y;
		m_elements[i * 3 + 2] = row.z;
	}

	template <typename T>
	void Matrix<T, 3, 3>::SetColumn(size_t i, const Vector3<T>& col)
	{
		m_elements[i] = col.x;
		m_elements[i + 3] = col.y;
		m_elements[i + 6] = col.z;
	}

	template <typename T>
	bool Matrix<T, 3, 3>::IsSimilar(const Matrix& m, double tol = std::numeric_limits<double>::epsilon()) const
	{
		for (size_t i = 0; i < 9; ++i)
		{
			if (std::fabs(m_elements[i] - m.m_elements[i]) > tol)
			{
				return false;
			}
		}

		return true;
	}

	template <typename T>
	bool Matrix<T, 3, 3>::IsSquare() const
	{
		return true;
	}

	template <typename T>
	size_t Matrix<T, 3, 3>::Rows() const
	{
		return 3;
	}

	template <typename T>
	size_t Matrix<T, 3, 3>::Cols() const
	{
		return 3;
	}

	template <typename T>
	T* Matrix<T, 3, 3>::Data()
	{
		return m_elements.data();
	}

	template <typename T>
	const T* Matrix<T, 3, 3>::Data() const
	{
		return m_elements.data();
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::Add(T s) const
	{
		return Matrix<T, 3, 3>(
			m_elements[0] + s, m_elements[1] + s, m_elements[2] + s,
			m_elements[3] + s, m_elements[4] + s, m_elements[5] + s,
			m_elements[6] + s, m_elements[7] + s, m_elements[8] + s);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::Add(const Matrix& m) const
	{
		return Matrix<T, 3, 3>(
			m_elements[0] + m.m_elements[0], m_elements[1] + m.m_elements[1], m_elements[2] + m.m_elements[2],
			m_elements[3] + m.m_elements[3], m_elements[4] + m.m_elements[4], m_elements[5] + m.m_elements[5],
			m_elements[6] + m.m_elements[6], m_elements[7] + m.m_elements[7], m_elements[8] + m.m_elements[8]);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::Sub(T s) const
	{
		return Matrix<T, 3, 3>(
			m_elements[0] - s, m_elements[1] - s, m_elements[2] - s,
			m_elements[3] - s, m_elements[4] - s, m_elements[5] - s,
			m_elements[6] - s, m_elements[7] - s, m_elements[8] - s);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::Sub(const Matrix& m) const
	{
		return Matrix<T, 3, 3>(
			m_elements[0] - m.m_elements[0], m_elements[1] - m.m_elements[1], m_elements[2] - m.m_elements[2],
			m_elements[3] - m.m_elements[3], m_elements[4] - m.m_elements[4], m_elements[5] - m.m_elements[5],
			m_elements[6] - m.m_elements[6], m_elements[7] - m.m_elements[7], m_elements[8] - m.m_elements[8]);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::Mul(T s) const
	{
		return Matrix<T, 3, 3>(
			m_elements[0] * s, m_elements[1] * s, m_elements[2] * s,
			m_elements[3] * s, m_elements[4] * s, m_elements[5] * s,
			m_elements[6] * s, m_elements[7] * s, m_elements[8] * s);
	}

	template <typename T>
	Vector3<T> Matrix<T, 3, 3>::Mul(const Vector3<T> & v) const
	{
		return Vector<T, 3>(
			v.x * m_elements[0] + v.y * m_elements[1] + v.z * m_elements[2],
			v.x * m_elements[3] + v.y * m_elements[4] + v.z * m_elements[5],
			v.x * m_elements[6] + v.y * m_elements[7] + v.z * m_elements[8]);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::Mul(const Matrix& m) const
	{
		Matrix tmp;

		for (size_t i = 0; i < 3; ++i)
		{
			for (size_t j = 0; j < 3; ++j)
			{
				tmp.m_elements[i * 3 + j] =
					m_elements[i * 3] * m.m_elements[i * 3 + j]
					+ m_elements[i * 3 + 1] * m.m_elements[(i + 1) * 3 + j]
					+ m_elements[i * 3 + 2] * m.m_elements[(i + 2) * 3 + j];
			}
		}

		return tmp;
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::Div(T s) const
	{
		return Matrix(
			m_elements[0] / s, m_elements[1] / s, m_elements[2] / s,
			m_elements[3] / s, m_elements[4] / s, m_elements[5] / s,
			m_elements[6] / s, m_elements[7] / s, m_elements[8] / s);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::RAdd(T s) const
	{
		return Matrix<T, 3, 3>(
			s + m_elements[0], s + m_elements[1], s + m_elements[2],
			s + m_elements[3], s + m_elements[4], s + m_elements[5],
			s + m_elements[6], s + m_elements[7], s + m_elements[8]);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::RAdd(const Matrix& m) const
	{
		return Matrix<T, 3, 3>(
			m.m_elements[0] + m_elements[0], m.m_elements[1] + m_elements[1], m.m_elements[2] + m_elements[2],
			m.m_elements[3] + m_elements[3], m.m_elements[4] + m_elements[4], m.m_elements[5] + m_elements[5],
			m.m_elements[6] + m_elements[6], m.m_elements[7] + m_elements[7], m.m_elements[8] + m_elements[8]);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::RSub(T s) const
	{
		return Matrix<T, 3, 3>(
			s - m_elements[0], s - m_elements[1], s - m_elements[2],
			s - m_elements[3], s - m_elements[4], s - m_elements[5],
			s - m_elements[6], s - m_elements[7], s - m_elements[8]);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::RSub(const Matrix& m) const
	{
		return Matrix<T, 3, 3>(
			m.m_elements[0] - m_elements[0], m.m_elements[1] - m_elements[1], m.m_elements[2] - m_elements[2],
			m.m_elements[3] - m_elements[3], m.m_elements[4] - m_elements[4], m.m_elements[5] - m_elements[5],
			m.m_elements[6] - m_elements[6], m.m_elements[7] - m_elements[7], m.m_elements[8] - m_elements[8]);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::RMul(T s) const
	{
		return Matrix<T, 3, 3>(
			s * m_elements[0], s * m_elements[1], s * m_elements[2],
			s * m_elements[3], s * m_elements[4], s * m_elements[5],
			s * m_elements[6], s * m_elements[7], s * m_elements[8]);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::RMul(const Matrix& m) const
	{
		return m.Mul(*this);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::RDiv(T s) const
	{
		return Matrix<T, 3, 3>(
			s / m_elements[0], s / m_elements[1], s / m_elements[2],
			s / m_elements[3], s / m_elements[4], s / m_elements[5],
			s / m_elements[6], s / m_elements[7], s / m_elements[8]);
	}

	template <typename T>
	void Matrix<T, 3, 3>::IAdd(T s)
	{
		for (size_t i = 0; i < 9; ++i)
		{
			m_elements[i] += s;
		}
	}

	template <typename T>
	void Matrix<T, 3, 3>::IAdd(const Matrix& m)
	{
		for (size_t i = 0; i < 9; ++i)
		{
			m_elements[i] += m.m_elements[i];
		}
	}

	template <typename T>
	void Matrix<T, 3, 3>::ISub(T s)
	{
		for (size_t i = 0; i < 9; ++i)
		{
			m_elements[i] -= s;
		}
	}

	template <typename T>
	void Matrix<T, 3, 3>::ISub(const Matrix& m)
	{
		for (size_t i = 0; i < 9; ++i)
		{
			m_elements[i] -= m.m_elements[i];
		}
	}

	template <typename T>
	void Matrix<T, 3, 3>::IMul(T s)
	{
		for (size_t i = 0; i < 9; ++i)
		{
			m_elements[i] *= s;
		}
	}

	template <typename T>
	void Matrix<T, 3, 3>::IMul(const Matrix& m)
	{
		Set(Mul(m));
	}

	template <typename T>
	void Matrix<T, 3, 3>::IDiv(T s)
	{
		for (size_t i = 0; i < 9; ++i)
		{
			m_elements[i] /= s;
		}
	}

	template <typename T>
	void Matrix<T, 3, 3>::Transpose()
	{
		std::swap(m_elements[1], m_elements[3]);
		std::swap(m_elements[2], m_elements[6]);
		std::swap(m_elements[5], m_elements[7]);
	}

	template <typename T>
	void Matrix<T, 3, 3>::Invert()
	{
		Matrix m;
		m.m_elements[0] = m_elements[4] * m_elements[8] - m_elements[5] * m_elements[7];
		m.m_elements[1] = m_elements[2] * m_elements[7] - m_elements[1] * m_elements[8];
		m.m_elements[2] = m_elements[1] * m_elements[5] - m_elements[2] * m_elements[4];
		m.m_elements[3] = m_elements[5] * m_elements[6] - m_elements[3] * m_elements[8];
		m.m_elements[4] = m_elements[0] * m_elements[8] - m_elements[2] * m_elements[6];
		m.m_elements[5] = m_elements[2] * m_elements[3] - m_elements[0] * m_elements[5];
		m.m_elements[6] = m_elements[3] * m_elements[7] - m_elements[4] * m_elements[6];
		m.m_elements[7] = m_elements[1] * m_elements[6] - m_elements[0] * m_elements[7];
		m.m_elements[8] = m_elements[0] * m_elements[4] - m_elements[1] * m_elements[3];

		m.IDiv(Determinant());
		Set(m);
	}

	template <typename T>
	T Matrix<T, 3, 3>::Sum() const
	{
		T sum = 0;

		for (int i = 0; i < 9; ++i)
		{
			sum += m_elements[i];
		}

		return sum;
	}

	template <typename T>
	T Matrix<T, 3, 3>::Avg() const
	{
		return Sum() / 9;
	}

	template <typename T>
	T Matrix<T, 3, 3>::Min() const
	{
		return std::min_element(m_elements.begin(), m_elements.end());
	}

	template <typename T>
	T Matrix<T, 3, 3>::Max() const
	{
		return std::max_element(m_elements.begin(), m_elements.end());
	}

	template <typename T>
	T Matrix<T, 3, 3>::AbsMin() const
	{
		// TODO: Consider T is integral type.
		return std::min({
			std::fabs(m_elements[0]), std::fabs(m_elements[1]), std::fabs(m_elements[2]),
			std::fabs(m_elements[3]), std::fabs(m_elements[4]), std::fabs(m_elements[5]),
			std::fabs(m_elements[6]), std::fabs(m_elements[7]), std::fabs(m_elements[8]) });
	}

	template <typename T>
	T Matrix<T, 3, 3>::AbsMax() const
	{
		// TODO: Consider T is integral type.
		return std::max({
			std::fabs(m_elements[0]), std::fabs(m_elements[1]), std::fabs(m_elements[2]),
			std::fabs(m_elements[3]), std::fabs(m_elements[4]), std::fabs(m_elements[5]),
			std::fabs(m_elements[6]), std::fabs(m_elements[7]), std::fabs(m_elements[8]) });
	}

	template <typename T>
	T Matrix<T, 3, 3>::Trace() const
	{
		return m_elements[0] + m_elements[4] + m_elements[8];
	}

	template <typename T>
	T Matrix<T, 3, 3>::Determinant() const
	{
		return
			  m_elements[0] * (m_elements[4] * m_elements[8] - m_elements[5] * m_elements[7])
			- m_elements[1] * (m_elements[3] * m_elements[8] - m_elements[5] * m_elements[6])
			+ m_elements[2] * (m_elements[3] * m_elements[7] - m_elements[4] * m_elements[6]);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::Diagonal() const
	{
		return Matrix<T, 3, 3>(
			m_elements[0], 0, 0,
			0, m_elements[4], 0,
			0, 0, m_elements[8]);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::OffDiagonal() const
	{
		return Matrix<T, 3, 3>(
			0, m_elements[1], m_elements[2],
			m_elements[3], 0, m_elements[5],
			m_elements[6], m_elements[7], 0);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::StrictLowerTriangle() const
	{
		return Matrix<T, 3, 3>(
			0, 0, 0,
			m_elements[3], 0, 0,
			m_elements[6], m_elements[7], 0);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::StrictUpperTriangle() const
	{
		return Matrix<T, 3, 3>(
			0, m_elements[1], m_elements[2],
			0, 0, m_elements[5],
			0, 0, 0);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::LowerTriangle() const
	{
		return Matrix<T, 3, 3>(
			m_elements[0], 0, 0,
			m_elements[3], m_elements[4], 0,
			m_elements[6], m_elements[7], m_elements[8]);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::UpperTriangle() const
	{
		return Matrix<T, 3, 3>(
			m_elements[0], m_elements[1], m_elements[2],
			0, m_elements[4], m_elements[5],
			0, 0, m_elements[8]);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::Transposed() const
	{
		return Matrix<T, 3, 3>(
			m_elements[0], m_elements[3], m_elements[6],
			m_elements[1], m_elements[4], m_elements[7],
			m_elements[2], m_elements[5], m_elements[8]);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::Inverse() const
	{
		Matrix m(*this);
		m.Invert();
		return m;
	}

	template <typename T>
	template <typename U>
	Matrix<U, 3, 3> Matrix<T, 3, 3>::CastTo() const
	{
		return Matrix<U, 3, 3>(
			static_cast<U>(m_elements[0]),
			static_cast<U>(m_elements[1]),
			static_cast<U>(m_elements[2]),
			static_cast<U>(m_elements[3]),
			static_cast<U>(m_elements[4]),
			static_cast<U>(m_elements[5]),
			static_cast<U>(m_elements[6]),
			static_cast<U>(m_elements[7]),
			static_cast<U>(m_elements[8]));
	}

	template <typename T>
	Matrix<T, 3, 3>& Matrix<T, 3, 3>::operator=(const Matrix& m)
	{
		Set(m);
		return *this;
	}

	template <typename T>
	Matrix<T, 3, 3>& Matrix<T, 3, 3>::operator+=(T s)
	{
		IAdd(s);
		return *this;
	}

	template <typename T>
	Matrix<T, 3, 3>& Matrix<T, 3, 3>::operator+=(const Matrix& m)
	{
		IAdd(m);
		return *this;
	}

	template <typename T>
	Matrix<T, 3, 3>& Matrix<T, 3, 3>::operator-=(T s)
	{
		ISub(s);
		return *this;
	}

	template <typename T>
	Matrix<T, 3, 3>& Matrix<T, 3, 3>::operator-=(const Matrix& m)
	{
		ISub(m);
		return *this;
	}

	template <typename T>
	Matrix<T, 3, 3>& Matrix<T, 3, 3>::operator*=(T s)
	{
		IMul(s);
		return *this;
	}

	template <typename T>
	Matrix<T, 3, 3>& Matrix<T, 3, 3>::operator*=(const Matrix& m)
	{
		IMul(m);
		return *this;
	}

	template <typename T>
	Matrix<T, 3, 3>& Matrix<T, 3, 3>::operator/=(T s)
	{
		IDiv(s);
		return *this;
	}

	template <typename T>
	T& Matrix<T, 3, 3>::operator[](size_t i)
	{
		return m_elements[i];
	}

	template <typename T>
	const T& Matrix<T, 3, 3>::operator[](size_t i) const
	{
		return m_elements[i];
	}

	template <typename T>
	T& Matrix<T, 3, 3>::operator()(size_t i, size_t j)
	{
		return m_elements[i * 3 + j];
	}

	template <typename T>
	const T& Matrix<T, 3, 3>::operator()(size_t i, size_t j) const
	{
		return m_elements[i * 3 + j];
	}

	template <typename T>
	bool Matrix<T, 3, 3>::operator==(const Matrix& m) const
	{
		for (size_t i = 0; i < 9; ++i)
		{
			if (m_elements[i] != m.m_elements[i])
			{
				return false;
			}
		}

		return true;
	}

	template <typename T>
	bool Matrix<T, 3, 3>::operator!=(const Matrix& m) const
	{
		return !(*this == m);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::MakeZero()
	{
		return Matrix<T, 3, 3>(
			0, 0, 0,
			0, 0, 0,
			0, 0, 0);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::MakeIdentity()
	{
		return Matrix<T, 3, 3>(
			1, 0, 0,
			0, 1, 0,
			0, 0, 1);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::MakeScaleMatrix(T sx, T sy, T sz)
	{
		return Matrix<T, 3, 3>(
			sx, 0, 0,
			0, sy, 0,
			0, 0, sz);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::MakeScaleMatrix(const Vector3<T>& s)
	{
		return MakeScaleMatrix(s.x, s.y, s.z);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::MakeRotationMatrix(const Vector3<T>& axis, const T rad)
	{
		return Matrix<T, 3, 3>(
			std::cos(rad) + axis.x * axis.x * (1 - std::cos(rad)),
			axis.x * axis.y * (1 - std::cos(rad)) - axis.z * std::sin(rad),
			axis.x * axis.z * (1 - std::cos(rad)) + axis.y * std::sin(rad),
			
			axis.y * axis.x * (1 - std::cos(rad)) + axis.z * std::sin(rad), 
			std::cos(rad) + axis.y * axis.y * (1 - std::cos(rad)),
			axis.y * axis.z * (1 - std::cos(rad)) - axis.x * std::sin(rad),

			axis.z * axis.x * (1 - std::cos(rad)) - axis.y * std::sin(rad),
			axis.z * axis.y * (1 - std::cos(rad)) + axis.x * std::sin(rad),
			std::cos(rad) + axis.z * axis.z * (1 - std::cos(rad)));
	}

	template <typename T>
	Matrix<T, 3, 3> operator-(const Matrix<T, 3, 3>& a)
	{
		return a.Mul(-1);
	}

	template <typename T>
	Matrix<T, 3, 3> operator+(const Matrix<T, 3, 3>& a, const Matrix<T, 3, 3>& b)
	{
		return a.Add(b);
	}

	template <typename T>
	Matrix<T, 3, 3> operator+(const Matrix<T, 3, 3>& a, const T b)
	{
		return a.Add(b);
	}

	template <typename T>
	Matrix<T, 3, 3> operator+(const T a, const Matrix<T, 3, 3>& b)
	{
		return b.RAdd(a);
	}

	template <typename T>
	Matrix<T, 3, 3> operator-(const Matrix<T, 3, 3>& a, const Matrix<T, 3, 3>& b)
	{
		return a.Sub(b);
	}

	template <typename T>
	Matrix<T, 3, 3> operator-(const Matrix<T, 3, 3>& a, const T b)
	{
		return a.Sub(b);
	}

	template <typename T>
	Matrix<T, 3, 3> operator-(const T a, const Matrix<T, 3, 3>& b)
	{
		return b.RSub(a);
	}

	template <typename T>
	Matrix<T, 3, 3> operator*(const Matrix<T, 3, 3>& a, T b)
	{
		return a.Mul(b);
	}

	template <typename T>
	Matrix<T, 3, 3> operator*(T a, const Matrix<T, 3, 3>& b)
	{
		return b.RMul(a);
	}

	template <typename T>
	Vector<T, 3> operator*(const Matrix<T, 3, 3>& a, const Vector<T, 3>& b)
	{
		return a.Mul(b);
	}

	template <typename T>
	Matrix<T, 3, 3> operator*(const Matrix<T, 3, 3>& a, const Matrix<T, 3, 3>& b)
	{
		return a.Mul(b);
	}

	template <typename T>
	Matrix<T, 3, 3> operator/(const Matrix<T, 3, 3>& a, T b)
	{
		return a.Div(b);
	}

	template <typename T>
	Matrix<T, 3, 3> operator/(T a, const Matrix<T, 3, 3>& b)
	{
		return b.RDiv(a);
	}
}

#endif