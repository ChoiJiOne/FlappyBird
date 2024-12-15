#include "MathModule.h"

#include "Assertion.h"
#include "BoundCircle2D.h"

bool BoundCircle2D::Intersect(const IBound2D* bound) const
{
	return IBound2D::IsIntersect(this, bound);
}