#include "MathModule.h"

#include "Assertion.h"
#include "BoundBox2D.h"

BoundBox2D::BoundBox2D(const Vec2f& minPosition, const Vec2f& maxPosition)
	: IBound2D(EType::Box)
	, minPosition_(Vec2f(MathModule::Min<float>(minPosition.x, maxPosition_.x), MathModule::Min<float>(minPosition.y, maxPosition_.y)))
	, maxPosition_(Vec2f(MathModule::Max<float>(minPosition.x, maxPosition_.x), MathModule::Max<float>(minPosition.y, maxPosition_.y)))
{
	ComputeBoundBoxProperties(minPosition_, maxPosition_, center_, width_, height_);
}

BoundBox2D::BoundBox2D(const Vec2f& center, const float& width, const float& height)
	: IBound2D(EType::Box)
	, center_(center)
	, width_(width)
	, height_(height)
{
	ComputeBoundBoxProperties(center_, width_, height_, minPosition_, maxPosition_);
}

void BoundBox2D::SetProperty(const Vec2f& minPosition, const Vec2f& maxPosition)
{
	minPosition_ = Vec2f(MathModule::Min<float>(minPosition.x, maxPosition_.x), MathModule::Min<float>(minPosition.y, maxPosition_.y));
	maxPosition_ = Vec2f(MathModule::Max<float>(minPosition.x, maxPosition_.x), MathModule::Max<float>(minPosition.y, maxPosition_.y));

	ComputeBoundBoxProperties(minPosition_, maxPosition_, center_, width_, height_);
}

void BoundBox2D::SetProperty(const Vec2f& center, const float& width, const float& height)
{
	center_ = center;
	width_ = width;
	height_ = height;

	ComputeBoundBoxProperties(center_, width_, height_, minPosition_, maxPosition_);
}

void BoundBox2D::SetCenter(const Vec2f& center)
{
	center_ = center;

	ComputeBoundBoxProperties(center_, width_, height_, minPosition_, maxPosition_);
}

bool BoundBox2D::Intersect(const IBound2D* bound) const
{
	return IBound2D::IsIntersect(this, bound);
}

void BoundBox2D::ComputeBoundBoxProperties(const Vec2f& center, const float& width, const float& height, Vec2f& outMinPosition, Vec2f& outMaxPosition) const
{
	CHECK(width >= 0.0f && height >= 0.0f);

	outMinPosition = center - Vec2f(width * 0.5f, height * 0.5f);
	outMaxPosition = center + Vec2f(width * 0.5f, height * 0.5f);
}

void BoundBox2D::ComputeBoundBoxProperties(const Vec2f& minPosition, const Vec2f& maxPosition, Vec2f& outCenter, float& outWidth, float& outHeight) const
{
	outCenter = (minPosition + maxPosition) * 0.5f;
	outWidth = (maxPosition.x - minPosition.x);
	outHeight = (maxPosition.y - minPosition.y);
}