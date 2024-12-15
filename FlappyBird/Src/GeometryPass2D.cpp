#include <glad/glad.h>

#include "MathModule.h"

#include "Assertion.h"
#include "GeometryPass2D.h"

GeometryPass2D::GeometryPass2D() : Shader("Shader/GeometryPass2D.vert", "Shader/GeometryPass2D.frag")
{
	GL_FAILED(glGenVertexArrays(1, &vertexArrayObject_));
	GL_FAILED(glGenBuffers(1, &vertexBufferObject_));

	GL_FAILED(glBindVertexArray(vertexArrayObject_));
	GL_FAILED(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject_));
	GL_FAILED(glBufferData(GL_ARRAY_BUFFER, VertexPositionColor2D::GetStride() * vertices_.size(), reinterpret_cast<const void*>(vertices_.data()), GL_DYNAMIC_DRAW));

	GL_FAILED(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, VertexPositionColor2D::GetStride(), (void*)(offsetof(VertexPositionColor2D, position))));
	GL_FAILED(glEnableVertexAttribArray(0));

	GL_FAILED(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexPositionColor2D::GetStride(), (void*)(offsetof(VertexPositionColor2D, color))));
	GL_FAILED(glEnableVertexAttribArray(1));

	GL_FAILED(glBindVertexArray(0));
}

GeometryPass2D::~GeometryPass2D()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void GeometryPass2D::Release()
{
	CHECK(bIsInitialized_);

	GL_FAILED(glDeleteBuffers(1, &vertexBufferObject_));
	GL_FAILED(glDeleteVertexArrays(1, &vertexArrayObject_));

	Shader::Release();
}

void GeometryPass2D::DrawPoints2D(const Mat4x4f& ortho, const std::vector<Vec2f>& positions, const Vec4f& color, float pointSize)
{
	CHECK(positions.size() <= MAX_VERTEX_SIZE);
	CHECK(pointSize >= 0.0f);

	for (std::size_t index = 0; index < positions.size(); ++index)
	{
		vertices_[index].position = Vec2f(positions[index].x + 0.5f, positions[index].y + 0.5f);
		vertices_[index].color = color;
	}

	pointSize_ = pointSize;
	DrawGeometry2D(Mat4x4f::Identity(), ortho, EDrawType::Points, static_cast<uint32_t>(positions.size()));
}

void GeometryPass2D::DrawConnectPoints2D(const Mat4x4f& ortho, const std::vector<Vec2f>& positions, const Vec4f& color)
{
	CHECK(positions.size() <= MAX_VERTEX_SIZE);

	for (std::size_t index = 0; index < positions.size(); ++index)
	{
		vertices_[index].position = Vec2f(positions[index].x + 0.5f, positions[index].y + 0.5f);
		vertices_[index].color = color;
	}

	DrawGeometry2D(Mat4x4f::Identity(), ortho, EDrawType::LineStrip, static_cast<uint32_t>(positions.size()));
}

void GeometryPass2D::DrawLine2D(const Mat4x4f& ortho, const Vec2f& fromPosition, const Vec2f& toPosition, const Vec4f& color)
{
	vertices_[0] = VertexPositionColor2D(Vec2f(fromPosition.x + 0.5f, fromPosition.y + 0.5f), color);
	vertices_[1] = VertexPositionColor2D(Vec2f(  toPosition.x + 0.5f,   toPosition.y + 0.5f), color);

	DrawGeometry2D(Mat4x4f::Identity(), ortho, EDrawType::LineStrip, 2);
}

void GeometryPass2D::DrawLine2D(const Mat4x4f& ortho, const Vec2f& fromPosition, const Vec4f& fromColor, const Vec2f& toPosition, const Vec4f& toColor)
{
	vertices_[0] = VertexPositionColor2D(Vec2f(fromPosition.x + 0.5f, fromPosition.y + 0.5f), fromColor);
	vertices_[1] = VertexPositionColor2D(Vec2f(  toPosition.x + 0.5f,   toPosition.y + 0.5f),   toColor);

	DrawGeometry2D(Mat4x4f::Identity(), ortho, EDrawType::LineStrip, 2);
}

void GeometryPass2D::DrawTriangle2D(const Mat4x4f& ortho, const Vec2f& fromPosition, const Vec2f& byPosition, const Vec2f& toPosition, const Vec4f& color)
{
	vertices_[0] = VertexPositionColor2D(Vec2f(fromPosition.x + 0.5f, fromPosition.y + 0.5f), color);
	vertices_[1] = VertexPositionColor2D(Vec2f(  byPosition.x + 0.5f,   byPosition.y + 0.5f), color);
	vertices_[2] = VertexPositionColor2D(Vec2f(  toPosition.x + 0.5f,   toPosition.y + 0.5f), color);

	DrawGeometry2D(Mat4x4f::Identity(), ortho, EDrawType::Triangles, 3);
}

void GeometryPass2D::DrawTriangle2D(const Mat4x4f& ortho, const Vec2f& fromPosition, const Vec4f& fromColor, const Vec2f& byPosition, const Vec4f& byColor, const Vec2f& toPosition, const Vec4f& toColor)
{
	vertices_[0] = VertexPositionColor2D(Vec2f(fromPosition.x + 0.5f, fromPosition.y + 0.5f), fromColor);
	vertices_[1] = VertexPositionColor2D(Vec2f(  byPosition.x + 0.5f,   byPosition.y + 0.5f),   byColor);
	vertices_[2] = VertexPositionColor2D(Vec2f(  toPosition.x + 0.5f,   toPosition.y + 0.5f),   toColor);

	DrawGeometry2D(Mat4x4f::Identity(), ortho, EDrawType::Triangles, 3);
}

void GeometryPass2D::DrawWireframeTriangle2D(const Mat4x4f& ortho, const Vec2f& fromPosition, const Vec2f& byPosition, const Vec2f& toPosition, const Vec4f& color)
{
	vertices_[0] = VertexPositionColor2D(Vec2f(fromPosition.x + 0.5f, fromPosition.y + 0.5f), color);
	vertices_[1] = VertexPositionColor2D(Vec2f(  byPosition.x + 0.5f,   byPosition.y + 0.5f), color);
	vertices_[2] = VertexPositionColor2D(Vec2f(  toPosition.x + 0.5f,   toPosition.y + 0.5f), color);
	vertices_[3] = VertexPositionColor2D(Vec2f(fromPosition.x + 0.5f, fromPosition.y + 0.5f), color);

	DrawGeometry2D(Mat4x4f::Identity(), ortho, EDrawType::LineStrip, 4);
}

void GeometryPass2D::DrawWireframeTriangle2D(const Mat4x4f& ortho, const Vec2f& fromPosition, const Vec4f& fromColor, const Vec2f& byPosition, const Vec4f& byColor, const Vec2f& toPosition, const Vec4f& toColor)
{
	vertices_[0] = VertexPositionColor2D(Vec2f(fromPosition.x + 0.5f, fromPosition.y + 0.5f), fromColor);
	vertices_[1] = VertexPositionColor2D(Vec2f(  byPosition.x + 0.5f,   byPosition.y + 0.5f),   byColor);
	vertices_[2] = VertexPositionColor2D(Vec2f(  toPosition.x + 0.5f,   toPosition.y + 0.5f),   toColor);
	vertices_[3] = VertexPositionColor2D(Vec2f(fromPosition.x + 0.5f, fromPosition.y + 0.5f), fromColor);

	DrawGeometry2D(Mat4x4f::Identity(), ortho, EDrawType::LineStrip, 4);
}

void GeometryPass2D::DrawRectangle2D(const Mat4x4f& ortho, const Vec2f& center, float width, float height, float rotate, const Vec4f& color)
{
	vertices_[0] = VertexPositionColor2D(Vec2f(center.x - width / 2.0f + 0.5f, center.y + height / 2.0f + 0.5f), color);
	vertices_[1] = VertexPositionColor2D(Vec2f(center.x + width / 2.0f + 0.5f, center.y + height / 2.0f + 0.5f), color);
	vertices_[2] = VertexPositionColor2D(Vec2f(center.x + width / 2.0f + 0.5f, center.y - height / 2.0f + 0.5f), color);
	vertices_[3] = VertexPositionColor2D(Vec2f(center.x - width / 2.0f + 0.5f, center.y - height / 2.0f + 0.5f), color);
	
	Mat4x4f transform = MathModule::CreateTranslation(Vec3f(-center.x, -center.y, 0.0f))
		* MathModule::CreateRotateZ(rotate)
		* MathModule::CreateTranslation(Vec3f(+center.x, +center.y, 0.0f));

	DrawGeometry2D(transform, ortho, EDrawType::TriangleFan, 4);
}

void GeometryPass2D::DrawWireframeRectangle2D(const Mat4x4f& ortho, const Vec2f& center, float width, float height, float rotate, const Vec4f& color)
{
	vertices_[0] = VertexPositionColor2D(Vec2f(center.x - width / 2.0f + 0.5f, center.y - height / 2.0f + 0.5f), color);
	vertices_[1] = VertexPositionColor2D(Vec2f(center.x - width / 2.0f + 0.5f, center.y + height / 2.0f + 0.5f), color);
	vertices_[2] = VertexPositionColor2D(Vec2f(center.x + width / 2.0f + 0.5f, center.y + height / 2.0f + 0.5f), color);
	vertices_[3] = VertexPositionColor2D(Vec2f(center.x + width / 2.0f + 0.5f, center.y - height / 2.0f + 0.5f), color);
	vertices_[4] = VertexPositionColor2D(Vec2f(center.x - width / 2.0f + 0.5f, center.y - height / 2.0f + 0.5f), color);

	Mat4x4f transform = MathModule::CreateTranslation(Vec3f(-center.x, -center.y, 0.0f))
		* MathModule::CreateRotateZ(rotate)
		* MathModule::CreateTranslation(Vec3f(+center.x, +center.y, 0.0f));

	DrawGeometry2D(transform, ortho, EDrawType::LineStrip, 5);
}

void GeometryPass2D::DrawRoundRectangle2D(const Mat4x4f& ortho, const Vec2f& center, float width, float height, float side, float rotate, const Vec4f& color)
{
	float halfWidth = width * 0.5f;
	float halfHeight = height * 0.5f;
	side = MathModule::Min<float>(side, MathModule::Min<float>(halfWidth, halfHeight));

	uint32_t vertexCount = 0;
	vertices_[vertexCount++].position = center;

	auto computeSpline = [&](const Vec2f& startPosition, const Vec2f& endPosition, const Vec2f& controlPosition)
	{
		for (int32_t slice = 0; slice <= MAX_SLICE_SIZE; ++slice)
		{
			float t = static_cast<float>(slice) / static_cast<float>(MAX_SLICE_SIZE);
			Vec2f p = startPosition * (1.0f - t) + controlPosition * t;
			Vec2f q = controlPosition * (1.0f - t) + endPosition * t;
			Vec2f r = p * (1.0f - t) + q * t;
			vertices_[vertexCount++].position = r;
		}
	};

	Vec2f control, start, end;
	
	control = Vec2f(center.x - halfWidth, center.y - halfHeight);
	start = Vec2f(control.x + side, control.y);
	end = Vec2f(control.x, control.y + side);
	computeSpline(start, end, control);

	control = Vec2f(center.x - halfWidth, center.y + halfHeight);
	start = Vec2f(control.x, control.y - side);
	end = Vec2f(control.x + side, control.y);
	computeSpline(start, end, control);

	control = Vec2f(center.x + halfWidth, center.y + halfHeight);
	start = Vec2f(control.x - side, control.y);
	end = Vec2f(control.x, control.y - side);
	computeSpline(start, end, control);

	control = Vec2f(center.x + halfWidth, center.y - halfHeight);
	start = Vec2f(control.x, control.y + side);
	end = Vec2f(control.x - side, control.y);
	computeSpline(start, end, control);

	control = Vec2f(center.x - halfWidth, center.y - halfHeight);
	vertices_[vertexCount++].position = Vec2f(control.x + side, control.y);

	for (int32_t index = 0; index < vertexCount; ++index)
	{
		vertices_[index].color = color;
	}

	Mat4x4f transform = MathModule::CreateTranslation(Vec3f(-center.x, -center.y, 0.0f))
		* MathModule::CreateRotateZ(rotate)
		* MathModule::CreateTranslation(Vec3f(+center.x, +center.y, 0.0f));

	DrawGeometry2D(transform, ortho, EDrawType::TriangleFan, vertexCount);
}

void GeometryPass2D::DrawWireframeRoundRectangle2D(const Mat4x4f& ortho, const Vec2f& center, float width, float height, float side, float rotate, const Vec4f& color)
{
	float halfWidth = width * 0.5f;
	float halfHeight = height * 0.5f;
	side = MathModule::Min<float>(side, MathModule::Min<float>(halfWidth, halfHeight));

	uint32_t vertexCount = 0;

	auto computeSpline = [&](const Vec2f& startPosition, const Vec2f& endPosition, const Vec2f& controlPosition)
	{
		for (int32_t slice = 0; slice <= MAX_SLICE_SIZE; ++slice)
		{
			float t = static_cast<float>(slice) / static_cast<float>(MAX_SLICE_SIZE);
			Vec2f p = startPosition * (1.0f - t) + controlPosition * t;
			Vec2f q = controlPosition * (1.0f - t) + endPosition * t;
			Vec2f r = p * (1.0f - t) + q * t;
			vertices_[vertexCount++].position = r;
		}
	};

	Vec2f control, start, end;

	control = Vec2f(center.x - halfWidth, center.y - halfHeight);
	start = Vec2f(control.x + side, control.y);
	end = Vec2f(control.x, control.y + side);
	computeSpline(start, end, control);

	control = Vec2f(center.x - halfWidth, center.y + halfHeight);
	start = Vec2f(control.x, control.y - side);
	end = Vec2f(control.x + side, control.y);
	computeSpline(start, end, control);

	control = Vec2f(center.x + halfWidth, center.y + halfHeight);
	start = Vec2f(control.x - side, control.y);
	end = Vec2f(control.x, control.y - side);
	computeSpline(start, end, control);

	control = Vec2f(center.x + halfWidth, center.y - halfHeight);
	start = Vec2f(control.x, control.y + side);
	end = Vec2f(control.x - side, control.y);
	computeSpline(start, end, control);

	control = Vec2f(center.x - halfWidth, center.y - halfHeight);
	vertices_[vertexCount++].position = Vec2f(control.x + side, control.y);

	for (int32_t index = 0; index < vertexCount; ++index)
	{
		vertices_[index].color = color;
	}

	Mat4x4f transform = MathModule::CreateTranslation(Vec3f(-center.x, -center.y, 0.0f))
		* MathModule::CreateRotateZ(rotate)
		* MathModule::CreateTranslation(Vec3f(+center.x, +center.y, 0.0f));

	DrawGeometry2D(transform, ortho, EDrawType::LineStrip, vertexCount);
}

void GeometryPass2D::DrawCircle2D(const Mat4x4f& ortho, const Vec2f& center, float radius, const Vec4f& color, int32_t sliceCount)
{
	CHECK(radius >= 0.0f);
	CHECK(sliceCount <= MAX_VERTEX_SIZE - 2);

	for (int32_t slice = 1; slice <= sliceCount; ++slice)
	{
		float radian = (static_cast<float>(slice - 1) * MathModule::TwoPi) / static_cast<float>(sliceCount);
		float x = radius * MathModule::Cos(radian);
		float y = radius * MathModule::Sin(radian);

		vertices_[slice] = VertexPositionColor2D(Vec2f(center.x + x + 0.5f, center.y + y + 0.5f), color);
	}

	vertices_[0] = VertexPositionColor2D(Vec2f(center.x + 0.5f, center.y + 0.5f), color);
	vertices_[sliceCount + 1] = vertices_[1];
	uint32_t vertexCount = static_cast<uint32_t>(sliceCount + 2);

	DrawGeometry2D(Mat4x4f::Identity(), ortho, EDrawType::TriangleFan, vertexCount);
}

void GeometryPass2D::DrawWireframeCircle2D(const Mat4x4f& ortho, const Vec2f& center, float radius, const Vec4f& color, int32_t sliceCount)
{
	CHECK(radius >= 0.0f);
	CHECK(sliceCount <= MAX_VERTEX_SIZE);

	for (int32_t index = 0; index < sliceCount; ++index)
	{
		float radian = (static_cast<float>(index) * MathModule::TwoPi) / static_cast<float>(sliceCount);
		float x = radius * MathModule::Cos(radian);
		float y = radius * MathModule::Sin(radian);

		vertices_[index] = VertexPositionColor2D(Vec2f(center.x + x + 0.5f, center.y + y + 0.5f), color);
	}

	vertices_[sliceCount] = vertices_[0];
	uint32_t vertexCount = static_cast<uint32_t>(sliceCount + 1);

	DrawGeometry2D(Mat4x4f::Identity(), ortho, EDrawType::LineStrip, vertexCount);
}

void GeometryPass2D::DrawEllipse2D(const Mat4x4f& ortho, const Vec2f& center, float xAxis, float yAxis, const Vec4f& color, int32_t sliceCount)
{
	CHECK(xAxis >= 0.0f && yAxis >= 0.0f);
	CHECK(sliceCount <= MAX_VERTEX_SIZE - 2);

	float halfXAxis = xAxis / 2.0f;
	float haflYAxis = yAxis / 2.0f;

	for (int32_t slice = 1; slice <= sliceCount; ++slice)
	{
		float radian = (static_cast<float>(slice - 1) * MathModule::TwoPi) / static_cast<float>(sliceCount);
		float x = halfXAxis * MathModule::Cos(radian);
		float y = haflYAxis * MathModule::Sin(radian);

		vertices_[slice] = VertexPositionColor2D(Vec2f(center.x + x + 0.5f, center.y + y + 0.5f), color);
	}

	vertices_[0] = VertexPositionColor2D(Vec2f(center.x + 0.5f, center.y + 0.5f), color);
	vertices_[sliceCount + 1] = vertices_[1];
	uint32_t vertexCount = static_cast<uint32_t>(sliceCount + 2);

	DrawGeometry2D(Mat4x4f::Identity(), ortho, EDrawType::TriangleFan, vertexCount);
}

void GeometryPass2D::DrawWireframeEllipse2D(const Mat4x4f& ortho, const Vec2f& center, float xAxis, float yAxis, const Vec4f& color, int32_t sliceCount)
{
	CHECK(xAxis >= 0.0f && yAxis >= 0.0f);
	CHECK(sliceCount <= MAX_VERTEX_SIZE - 2);

	float halfXAxis = xAxis / 2.0f;
	float haflYAxis = yAxis / 2.0f;

	for (int32_t index = 0; index < sliceCount; ++index)
	{
		float radian = (static_cast<float>(index) * MathModule::TwoPi) / static_cast<float>(sliceCount);
		float x = halfXAxis * MathModule::Cos(radian);
		float y = haflYAxis * MathModule::Sin(radian);

		vertices_[index] = VertexPositionColor2D(Vec2f(center.x + x + 0.5f, center.y + y + 0.5f), color);
	}

	vertices_[sliceCount] = vertices_[0];
	uint32_t vertexCount = static_cast<uint32_t>(sliceCount + 1);

	DrawGeometry2D(Mat4x4f::Identity(), ortho, EDrawType::LineStrip, vertexCount);
}

void GeometryPass2D::DrawGeometry2D(const Mat4x4f& transform, const Mat4x4f& ortho, const EDrawType& drawType, uint32_t vertexCount)
{
	CHECK(drawType != EDrawType::None);

	const void* bufferPtr = reinterpret_cast<const void*>(vertices_.data());
	uint32_t bufferByteSize = static_cast<uint32_t>(VertexPositionColor2D::GetStride() * vertices_.size());
	WriteDynamicVertexBuffer(vertexBufferObject_, bufferPtr, bufferByteSize);

	Shader::Bind();
	if (drawType == EDrawType::Points)
	{
		Shader::SetUniform("pointSize", pointSize_);
	}

	Shader::SetUniform("transform", transform);
	Shader::SetUniform("ortho", ortho);

	GL_FAILED(glBindVertexArray(vertexArrayObject_));
	GL_FAILED(glDrawArrays(static_cast<GLenum>(drawType), 0, vertexCount));
	GL_FAILED(glBindVertexArray(0));

	Shader::Unbind();
}