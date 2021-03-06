/*************************************************************************
> File Name: Transform2.cpp
> Project Name: CubbyFlow
> Author: Dongmin Kim
> Purpose: Represents 2-D rigid body transform.
> Created Time: 2017/03/30
> Copyright (c) 2017, Dongmin Kim
*************************************************************************/
#include <Transform/Transform2.h>

namespace CubbyFlow
{
	Transform2::Transform2()
	{
		// Do nothing
	}

	Transform2::Transform2(const Vector2D& translation, double orientation) :
		m_translation(translation), m_orientation(orientation)
	{
		m_cosAngle = std::cos(orientation);
		m_sinAngle = std::sin(orientation);
	}

	const Vector2D& Transform2::Translation() const
	{
		return m_translation;
	}

	void Transform2::SetTranslation(const Vector2D& translation)
	{
		m_translation = translation;
	}

	double Transform2::Orientation() const {
		return m_orientation;
	}

	void Transform2::SetOrientation(double orientation)
	{
		m_orientation = orientation;
	}

	Vector2D Transform2::ToLocal(const Vector2D& pointInWorld) const
	{
		// Convert to the local frame
		Vector2D xmt = pointInWorld - m_translation;
		return Vector2D(
			m_cosAngle * xmt.x + m_sinAngle * xmt.y,
			-m_sinAngle * xmt.x + m_cosAngle * xmt.y);
	}

	Vector2D Transform2::ToLocalDirection(const Vector2D& dirInWorld) const
	{
		// Convert to the local frame
		return Vector2D(
			m_cosAngle * dirInWorld.x + m_sinAngle * dirInWorld.y,
			-m_sinAngle * dirInWorld.x + m_cosAngle * dirInWorld.y);
	}

	Ray2D Transform2::ToLocal(const Ray2D& rayInWorld) const
	{
		return Ray2D(
			ToLocal(rayInWorld.origin),
			ToLocalDirection(rayInWorld.direction));
	}

	BoundingBox2D Transform2::ToLocal(const BoundingBox2D& bboxInWorld) const
	{
		BoundingBox2D bboxInLocal = bboxInWorld;

		for (size_t i = 0; i < 4; ++i)
		{
			auto cornerInLocal = ToLocal(bboxInWorld.Corner(i));

			bboxInLocal.lowerCorner	= Min(bboxInLocal.lowerCorner, cornerInLocal);
			bboxInLocal.upperCorner	= Max(bboxInLocal.upperCorner, cornerInLocal);
		}

		return bboxInLocal;
	}

	Vector2D Transform2::ToWorld(const Vector2D& pointInLocal) const
	{
		// Convert to the world frame
		return Vector2D(
			m_cosAngle * pointInLocal.x - m_sinAngle * pointInLocal.y + m_translation.x,
			m_sinAngle * pointInLocal.x + m_cosAngle * pointInLocal.y + m_translation.y);
	}

	Vector2D Transform2::ToWorldDirection(const Vector2D& dirInLocal) const
	{
		// Convert to the world frame
		return Vector2D(
			m_cosAngle * dirInLocal.x - m_sinAngle * dirInLocal.y,
			m_sinAngle * dirInLocal.x + m_cosAngle * dirInLocal.y);
	}

	Ray2D Transform2::ToWorld(const Ray2D& rayInLocal) const
	{
		return Ray2D(
			ToWorld(rayInLocal.origin),
			ToWorldDirection(rayInLocal.direction));
	}

	BoundingBox2D Transform2::ToWorld(const BoundingBox2D& bboxInLocal) const
	{
		BoundingBox2D bboxInWorld = bboxInLocal;

		for (size_t i = 0; i < 4; ++i)
		{
			auto cornerInWorld = ToWorld(bboxInLocal.Corner(i));

			bboxInWorld.lowerCorner	= Min(bboxInWorld.lowerCorner, cornerInWorld);
			bboxInWorld.upperCorner	= Max(bboxInWorld.upperCorner, cornerInWorld);
		}

		return bboxInWorld;
	}
}