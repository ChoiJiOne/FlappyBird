#include <glad/glad.h>

#include "MathModule.h"

#include "Assertion.h"
#include "SpritePass2D.h"
#include "Texture2D.h"

#include <glad/glad.h>

SpritePass2D::SpritePass2D() : Shader("Shader/SpritePass2D.vert", "Shader/SpritePass2D.frag")
{
	GL_FAILED(glGenVertexArrays(1, &vertexArrayObject_));
	GL_FAILED(glGenBuffers(1, &vertexBufferObject_));

	GL_FAILED(glBindVertexArray(vertexArrayObject_));
	GL_FAILED(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject_));
	GL_FAILED(glBufferData(GL_ARRAY_BUFFER, VertexPositionUv2D::GetStride() * vertices_.size(), reinterpret_cast<const void*>(vertices_.data()), GL_DYNAMIC_DRAW));

	GL_FAILED(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, VertexPositionUv2D::GetStride(), (void*)(offsetof(VertexPositionUv2D, position))));
	GL_FAILED(glEnableVertexAttribArray(0));

	GL_FAILED(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, VertexPositionUv2D::GetStride(), (void*)(offsetof(VertexPositionUv2D, uv))));
	GL_FAILED(glEnableVertexAttribArray(1));

	GL_FAILED(glBindVertexArray(0));
}

SpritePass2D::~SpritePass2D()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void SpritePass2D::Release()
{
	CHECK(bIsInitialized_);

	GL_FAILED(glDeleteBuffers(1, &vertexBufferObject_));
	GL_FAILED(glDeleteVertexArrays(1, &vertexArrayObject_));

	Shader::Release();
}

void SpritePass2D::DrawSprite2D(const Mat4x4f& ortho, const Texture2D* texture, const Vec2f& center, float width, float height, float rotate, float transparent)
{
	uint32_t vertexCount = 0;

	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(center.x - width / 2.0f + 0.5f, center.y + height / 2.0f + 0.5f), Vec2f(0.0f, 0.0f));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(center.x + width / 2.0f + 0.5f, center.y + height / 2.0f + 0.5f), Vec2f(1.0f, 0.0f));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(center.x + width / 2.0f + 0.5f, center.y - height / 2.0f + 0.5f), Vec2f(1.0f, 1.0f));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(center.x - width / 2.0f + 0.5f, center.y - height / 2.0f + 0.5f), Vec2f(0.0f, 1.0f));

	Mat4x4f transform = MathModule::CreateTranslation(Vec3f(-center.x, -center.y, 0.0f))
		* MathModule::CreateRotateZ(rotate)
		* MathModule::CreateTranslation(Vec3f(+center.x, +center.y, 0.0f));

	DrawSprite2D(transform, ortho, EDrawType::TriangleFan, vertexCount, texture, false, transparent);
}

void SpritePass2D::DrawSprite2D(const Texture2D* texture, float transparent)
{
	uint32_t vertexCount = 0;

	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(-1.0f, -1.0f), Vec2f(0.0f, 0.0f));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(+1.0f, -1.0f), Vec2f(1.0f, 0.0f));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(+1.0f, +1.0f), Vec2f(1.0f, 1.0f));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(-1.0f, +1.0f), Vec2f(0.0f, 1.0f));

	DrawSprite2D(Mat4x4f::Identity(), Mat4x4f::Identity(), EDrawType::TriangleFan, vertexCount, texture, false, transparent);
}

void SpritePass2D::DrawHorizonScrollSprite2D(const Texture2D* texture, float rate, float transparent)
{
	rate = MathModule::Clamp<float>(rate, 0.0f, 1.0f);
	float x = -1.0f + 2.0f * (1.0f - rate);

	uint32_t vertexCount = 0;
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(-1.0f, -1.0f), Vec2f(rate, 0.0f));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(   +x, -1.0f), Vec2f(1.0f, 0.0f));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(   +x, +1.0f), Vec2f(1.0f, 1.0f));

	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(-1.0f, -1.0f), Vec2f(rate, 0.0f));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(   +x, +1.0f), Vec2f(1.0f, 1.0f));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(-1.0f, +1.0f), Vec2f(rate, 1.0f));

	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(   +x, -1.0f), Vec2f(0.0f, 0.0f));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(+1.0f, -1.0f), Vec2f(rate, 0.0f));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(+1.0f, +1.0f), Vec2f(rate, 1.0f));

	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(   +x, -1.0f), Vec2f(0.0f, 0.0f));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(+1.0f, +1.0f), Vec2f(rate, 1.0f));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(   +x, +1.0f), Vec2f(0.0f, 1.0f));

	DrawSprite2D(Mat4x4f::Identity(), Mat4x4f::Identity(), EDrawType::Triangles, vertexCount, texture, false, transparent);
}

void SpritePass2D::DrawHorizonScrollSprite2D(const Mat4x4f& ortho, const Texture2D* texture, const Vec2f& center, float width, float height, float rotate, float rate, float transparent)
{
	rate = MathModule::Clamp<float>(rate, 0.0f, 1.0f);

	float x0 = center.x - width / 2.0f;
	float y0 = center.y - height / 2.0f;
	float x1 = center.x + width / 2.0f;
	float y1 = center.y + height / 2.0f;

	float x = x0 + (x1 - x0) * (1.0f - rate);

	uint32_t vertexCount = 0;
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(x0 + 0.5f, y1 + 0.5f), Vec2f(rate, 0.0f));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(+x + 0.5f, y1 + 0.5f), Vec2f(1.0f, 0.0f));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(+x + 0.5f, y0 + 0.5f), Vec2f(1.0f, 1.0f));

	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(x0 + 0.5f, y1 + 0.5f), Vec2f(rate, 0.0f));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(+x + 0.5f, y0 + 0.5f), Vec2f(1.0f, 1.0f));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(x0 + 0.5f, y0 + 0.5f), Vec2f(rate, 1.0f));

	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(+x + 0.5f, y1 + 0.5f), Vec2f(0.0f, 0.0f));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(x1 + 0.5f, y1 + 0.5f), Vec2f(rate, 0.0f));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(x1 + 0.5f, y0 + 0.5f), Vec2f(rate, 1.0f));

	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(+x + 0.5f, y1 + 0.5f), Vec2f(0.0f, 0.0f));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(x1 + 0.5f, y0 + 0.5f), Vec2f(rate, 1.0f));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(+x + 0.5f, y0 + 0.5f), Vec2f(0.0f, 1.0f));

	Mat4x4f transform = MathModule::CreateTranslation(Vec3f(-center.x, -center.y, 0.0f))
		* MathModule::CreateRotateZ(rotate)
		* MathModule::CreateTranslation(Vec3f(+center.x, +center.y, 0.0f));

	DrawSprite2D(transform, ortho, EDrawType::Triangles, vertexCount, texture, false, transparent);
}

void SpritePass2D::DrawVerticalScrollSprite2D(const Texture2D* texture, float rate, float transparent)
{
	rate = MathModule::Clamp<float>(rate, 0.0f, 1.0f);
	float y = -1.0f + 2.0f * (1.0f - rate);

	uint32_t vertexCount = 0;
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(-1.0f, -1.0f), Vec2f(0.0f, rate));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(+1.0f, -1.0f), Vec2f(1.0f, rate));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(+1.0f,    +y), Vec2f(1.0f, 1.0f));

	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(-1.0f, -1.0f), Vec2f(0.0f, rate));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(+1.0f,    +y), Vec2f(1.0f, 1.0f));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(-1.0f,    +y), Vec2f(0.0f, 1.0f));

	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(-1.0f,    +y), Vec2f(0.0f, 0.0f));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(+1.0f,    +y), Vec2f(1.0f, 0.0f));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(+1.0f, +1.0f), Vec2f(1.0f, rate));

	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(-1.0f,    +y), Vec2f(0.0f, 0.0f));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(+1.0f, +1.0f), Vec2f(1.0f, rate));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(-1.0f, +1.0f), Vec2f(0.0f, rate));

	DrawSprite2D(Mat4x4f::Identity(), Mat4x4f::Identity(), EDrawType::Triangles, vertexCount, texture, false, transparent);
}

void SpritePass2D::DrawVerticalScrollSprite2D(const Mat4x4f& ortho, const Texture2D* texture, const Vec2f& center, float width, float height, float rotate, float rate, float transparent)
{
	rate = MathModule::Clamp<float>(rate, 0.0f, 1.0f);

	float x0 = center.x - width / 2.0f;
	float y0 = center.y - height / 2.0f;
	float x1 = center.x + width / 2.0f;
	float y1 = center.y + height / 2.0f;

	float y = y0 + (y1 - y0) * rate;

	uint32_t vertexCount = 0;
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(x0, y1), Vec2f(0.0f, rate));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(x1, y1), Vec2f(1.0f, rate));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(x1, +y), Vec2f(1.0f, 1.0f));

	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(x0, y1), Vec2f(0.0f, rate));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(x1, +y), Vec2f(1.0f, 1.0f));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(x0, +y), Vec2f(0.0f, 1.0f));

	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(x0, +y), Vec2f(0.0f, 0.0f));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(x1, +y), Vec2f(1.0f, 0.0f));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(x1, y0), Vec2f(1.0f, rate));

	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(x0, +y), Vec2f(0.0f, 0.0f));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(x1, y0), Vec2f(1.0f, rate));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(x0, y0), Vec2f(0.0f, rate));

	Mat4x4f transform = MathModule::CreateTranslation(Vec3f(-center.x, -center.y, 0.0f))
		* MathModule::CreateRotateZ(rotate)
		* MathModule::CreateTranslation(Vec3f(+center.x, +center.y, 0.0f));

	DrawSprite2D(transform, ortho, EDrawType::Triangles, vertexCount, texture, false, transparent);
}

void SpritePass2D::DrawOutlineSprite2D(const Mat4x4f& ortho, const Texture2D* texture, const Vec2f& center, float width, float height, float rotate, const Vec4f& outline, float transparent)
{
	uint32_t vertexCount = 0;
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(center.x - width / 2.0f + 0.5f, center.y + height / 2.0f + 0.5f), Vec2f(0.0f, 0.0f));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(center.x + width / 2.0f + 0.5f, center.y + height / 2.0f + 0.5f), Vec2f(1.0f, 0.0f));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(center.x + width / 2.0f + 0.5f, center.y - height / 2.0f + 0.5f), Vec2f(1.0f, 1.0f));
	vertices_[vertexCount++] = VertexPositionUv2D(Vec2f(center.x - width / 2.0f + 0.5f, center.y - height / 2.0f + 0.5f), Vec2f(0.0f, 1.0f));

	Mat4x4f transform = MathModule::CreateTranslation(Vec3f(-center.x, -center.y, 0.0f))
		* MathModule::CreateRotateZ(rotate)
		* MathModule::CreateTranslation(Vec3f(+center.x, +center.y, 0.0f));

	DrawSprite2D(transform, ortho, EDrawType::TriangleFan, vertexCount, texture, true, transparent, outline);
}

void SpritePass2D::DrawSprite2D(const Mat4x4f& transform, const Mat4x4f& ortho, const EDrawType& drawType, uint32_t vertexCount, const Texture2D* texture, bool bIsActiveOutline, float transparent, const Vec4f& outline)
{
	CHECK(drawType != EDrawType::None);

	const void* bufferPtr = reinterpret_cast<const void*>(vertices_.data());
	uint32_t bufferByteSize = static_cast<uint32_t>(VertexPositionUv2D::GetStride() * vertices_.size());
	WriteDynamicVertexBuffer(vertexBufferObject_, bufferPtr, bufferByteSize);

	Shader::Bind();

	texture->Active(0);

	Shader::SetUniform("transform", transform);
	Shader::SetUniform("ortho", ortho);
	Shader::SetUniform("bIsActiveOutline", bIsActiveOutline);
	Shader::SetUniform("transparent", transparent);
	Shader::SetUniform("outlineRGBA", outline);

	GL_FAILED(glBindVertexArray(vertexArrayObject_));
	GL_FAILED(glDrawArrays(static_cast<GLenum>(drawType), 0, vertexCount));
	GL_FAILED(glBindVertexArray(0));

	Shader::Unbind();
}