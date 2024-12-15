#include "MathModule.h"

#include "BoundBox2D.h"
#include "BoundCircle2D.h"
#include "IBound2D.h"

bool IBound2D::IsIntersect(const IBound2D* bound0, const IBound2D* bound1) const
{
	bool bIsIntersect = false;
	EType type0 = bound0->GetType();
	EType type1 = bound1->GetType();
	
	if (type0 == EType::None || type1 == EType::None)
	{
		return false;
	}

	if (type0 == EType::Box)
	{
		if (type1 == EType::Box)
		{
			bIsIntersect = IntersectBoxToBox(bound0, bound1);
		}
		else if (type1 == EType::Circle)
		{
			bIsIntersect = IntersectBoxToCircle(bound0, bound1);
		}
		else // other thing...
		{
			bIsIntersect = false;
		}
	}
	else if (type0 == EType::Circle)
	{
		if (type1 == EType::Box)
		{
			bIsIntersect = IntersectBoxToCircle(bound1, bound0);
		}
		else if (type1 == EType::Circle)
		{
			bIsIntersect = IntersectCircleToCircle(bound0, bound1);
		}
		else // other thing...
		{
			bIsIntersect = false;
		}
	}
	else // other thing...
	{
		bIsIntersect = false;
	}
	
	return bIsIntersect;
}

bool IBound2D::IntersectBoxToBox(const IBound2D* bound0, const IBound2D* bound1) const
{
	const BoundBox2D* boundBox0 = reinterpret_cast<const BoundBox2D*>(bound0);
	const BoundBox2D* boundBox1 = reinterpret_cast<const BoundBox2D*>(bound1);

	const Vec2f& minPosition0 = boundBox0->GetMinPosition();
	const Vec2f& maxPosition0 = boundBox0->GetMaxPosition();
	const Vec2f& minPosition1 = boundBox1->GetMinPosition();
	const Vec2f& maxPosition1 = boundBox1->GetMaxPosition();

	if (minPosition0.x > maxPosition1.x || maxPosition0.x < minPosition1.x)
	{
		return false;
	}

	if (minPosition0.y > maxPosition1.y || maxPosition0.y < minPosition1.y)
	{
		return false;
	}

	return true;
}

bool IBound2D::IntersectBoxToCircle(const IBound2D* bound0, const IBound2D* bound1) const
{
	const BoundBox2D* boundBox = reinterpret_cast<const BoundBox2D*>(bound0);
	const BoundCircle2D* boundCircle = reinterpret_cast<const BoundCircle2D*>(bound1);

	const Vec2f& minPosition = boundBox->GetMinPosition();
	const Vec2f& maxPosition = boundBox->GetMaxPosition();

	const Vec2f& c = boundCircle->GetCenter();
	const float& r = boundCircle->GetRadius();

	float x = MathModule::Clamp<float>(c.x, minPosition.x, maxPosition.x);
	float y = MathModule::Clamp<float>(c.y, minPosition.y, maxPosition.y);
	float dx = (c.x - x);
	float dy = (c.y - y);
	float d2 = (dx * dx) + (dy * dy); // d^2
	float r2 = r * r; // r^2

	if (d2 <= r2)
	{
		return true;
	}

	return false;
}

bool IBound2D::IntersectCircleToCircle(const IBound2D* bound0, const IBound2D* bound1) const
{
	const BoundCircle2D* boundCircle0 = reinterpret_cast<const BoundCircle2D*>(bound0);
	const BoundCircle2D* boundCircle1 = reinterpret_cast<const BoundCircle2D*>(bound1);

	const Vec2f& c0 = boundCircle0->GetCenter();
	const float& r0 = boundCircle0->GetRadius();
	const Vec2f& c1 = boundCircle1->GetCenter();
	const float& r1 = boundCircle1->GetRadius();

	Vec2f d = c0 - c1;
	float d2 = Vec2f::LengthSquare(d); // d^2
	float sum2 = (r0 + r1) * (r0 + r1); // (r0 + r1)^2

	return d2 <= sum2;
}