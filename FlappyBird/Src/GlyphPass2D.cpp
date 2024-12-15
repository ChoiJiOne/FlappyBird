#include <glad/glad.h>

#include "Assertion.h"
#include "GlyphPass2D.h"
#include "TTFont.h"

GlyphPass2D::GlyphPass2D() : Shader("Shader/GlyphPass2D.vert", "Shader/GlyphPass2D.frag")
{
	GL_FAILED(glGenVertexArrays(1, &vertexArrayObject_));
	GL_FAILED(glGenBuffers(1, &vertexBufferObject_));

	GL_FAILED(glBindVertexArray(vertexArrayObject_));
	GL_FAILED(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject_));
	GL_FAILED(glBufferData(GL_ARRAY_BUFFER, VertexPositionUvColor2D::GetStride() * vertices_.size(), reinterpret_cast<const void*>(vertices_.data()), GL_DYNAMIC_DRAW));

	GL_FAILED(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, VertexPositionUvColor2D::GetStride(), (void*)(offsetof(VertexPositionUvColor2D, position))));
	GL_FAILED(glEnableVertexAttribArray(0));

	GL_FAILED(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, VertexPositionUvColor2D::GetStride(), (void*)(offsetof(VertexPositionUvColor2D, uv))));
	GL_FAILED(glEnableVertexAttribArray(1));

	GL_FAILED(glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, VertexPositionUvColor2D::GetStride(), (void*)(offsetof(VertexPositionUvColor2D, color))));
	GL_FAILED(glEnableVertexAttribArray(2));

	GL_FAILED(glBindVertexArray(0));
}

GlyphPass2D::~GlyphPass2D()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void GlyphPass2D::Release()
{
	CHECK(bIsInitialized_);

	GL_FAILED(glDeleteBuffers(1, &vertexBufferObject_));
	GL_FAILED(glDeleteVertexArrays(1, &vertexArrayObject_));

	Shader::Release();
}

void GlyphPass2D::DrawText2D(const Mat4x4f& ortho, const TTFont* font, const std::wstring& text, const Vec2f& position, const EAlignment& alignment, const Vec4f& color)
{
	CHECK(text.length() <= MAX_STRING_LEN);
	CHECK(font != nullptr);
	CHECK(alignment != EAlignment::None);

	float width = 0.0f;
	float height = 0.0f;
	font->MeasureText(text, width, height);

	Vec2f startPosition = position;
	switch (alignment)
	{
	case EAlignment::Left:
		startPosition.y += height;
		break;

	case EAlignment::Center:
		startPosition = position - Vec2f(width, -height) * 0.5f;
		break;

	default:
		ASSERT(false, "undefined text alignment type");
		break;
	}

	int32_t vertexCount = UpdateGlyphVertexBuffer(font, text, startPosition, color);

	const void* bufferPtr = reinterpret_cast<const void*>(vertices_.data());
	uint32_t bufferByteSize = static_cast<uint32_t>(VertexPositionUvColor2D::GetStride() * vertices_.size());
	WriteDynamicVertexBuffer(vertexBufferObject_, bufferPtr, bufferByteSize);

	Shader::Bind();

	GL_FAILED(glActiveTexture(GL_TEXTURE0));
	GL_FAILED(glBindTexture(GL_TEXTURE_2D, font->GetGlyphAtlasID()));

	Shader::SetUniform("ortho", ortho);

	GL_FAILED(glBindVertexArray(vertexArrayObject_));
	GL_FAILED(glDrawArrays(GL_TRIANGLES, 0, vertexCount));
	GL_FAILED(glBindVertexArray(0));

	Shader::Unbind();
}

void GlyphPass2D::DrawText2D(const Mat4x4f& ortho, const TTFont* font, const std::wstring& text, const Vec2f& position, const EAlignment& alignment, const std::vector<Vec4f>& colors)
{
	CHECK(text.length() <= MAX_STRING_LEN);
	CHECK(font != nullptr);
	CHECK(alignment != EAlignment::None);

	float width = 0.0f;
	float height = 0.0f;
	font->MeasureText(text, width, height);

	Vec2f startPosition = position;
	switch (alignment)
	{
	case EAlignment::Left:
		startPosition.y += height;
		break;

	case EAlignment::Center:
		startPosition = position - Vec2f(width, -height) * 0.5f;
		break;

	default:
		ASSERT(false, "undefined text alignment type");
		break;
	}

	int32_t vertexCount = UpdateGlyphVertexBuffer(font, text, startPosition, colors);

	const void* bufferPtr = reinterpret_cast<const void*>(vertices_.data());
	uint32_t bufferByteSize = static_cast<uint32_t>(VertexPositionUvColor2D::GetStride() * vertices_.size());
	WriteDynamicVertexBuffer(vertexBufferObject_, bufferPtr, bufferByteSize);

	Shader::Bind();

	GL_FAILED(glActiveTexture(GL_TEXTURE0));
	GL_FAILED(glBindTexture(GL_TEXTURE_2D, font->GetGlyphAtlasID()));

	Shader::SetUniform("ortho", ortho);

	GL_FAILED(glBindVertexArray(vertexArrayObject_));
	GL_FAILED(glDrawArrays(GL_TRIANGLES, 0, vertexCount));
	GL_FAILED(glBindVertexArray(0));

	Shader::Unbind();
}

uint32_t GlyphPass2D::UpdateGlyphVertexBuffer(const TTFont* font, const std::wstring& text, const Vec2f& startPosition, const Vec4f& color)
{
	float glyphAtlasSize = static_cast<float>(font->GetGlyphAtlasSize());
	
	Vec2f currentPosition = startPosition;
	int32_t vertexCount = 0;

	for (const auto& unicode : text)
	{
		const Glyph& glyph = font->GetGlyph(static_cast<int32_t>(unicode));

		float unicodeWidth = static_cast<float>(glyph.position1.x - glyph.position0.x);
		float unicodeHeight = static_cast<float>(glyph.position1.y - glyph.position0.y);

		vertices_[vertexCount + 0].position = Vec2f(currentPosition.x + glyph.xoffset, currentPosition.y + glyph.yoffset);
		vertices_[vertexCount + 0].uv       = Vec2f(static_cast<float>(glyph.position0.x) / glyphAtlasSize, static_cast<float>(glyph.position0.y) / glyphAtlasSize);
		vertices_[vertexCount + 0].color    = color;

		vertices_[vertexCount + 1].position = Vec2f(currentPosition.x + glyph.xoffset, currentPosition.y + unicodeHeight + glyph.yoffset);
		vertices_[vertexCount + 1].uv       = Vec2f(static_cast<float>(glyph.position0.x) / glyphAtlasSize, static_cast<float>(glyph.position1.y) / glyphAtlasSize);
		vertices_[vertexCount + 1].color    = color;

		vertices_[vertexCount + 2].position = Vec2f(currentPosition.x + glyph.xoffset + unicodeWidth, currentPosition.y + glyph.yoffset);
		vertices_[vertexCount + 2].uv       = Vec2f(static_cast<float>(glyph.position1.x) / glyphAtlasSize, static_cast<float>(glyph.position0.y) / glyphAtlasSize);
		vertices_[vertexCount + 2].color    = color;

		vertices_[vertexCount + 3].position = Vec2f(currentPosition.x + glyph.xoffset + unicodeWidth, currentPosition.y + glyph.yoffset);
		vertices_[vertexCount + 3].uv       = Vec2f(static_cast<float>(glyph.position1.x) / glyphAtlasSize, static_cast<float>(glyph.position0.y) / glyphAtlasSize);
		vertices_[vertexCount + 3].color    = color;

		vertices_[vertexCount + 4].position = Vec2f(currentPosition.x + glyph.xoffset, currentPosition.y + unicodeHeight + glyph.yoffset);
		vertices_[vertexCount + 4].uv       = Vec2f(static_cast<float>(glyph.position0.x) / glyphAtlasSize, static_cast<float>(glyph.position1.y) / glyphAtlasSize);
		vertices_[vertexCount + 4].color    = color;

		vertices_[vertexCount + 5].position = Vec2f(currentPosition.x + glyph.xoffset + unicodeWidth, currentPosition.y + unicodeHeight + glyph.yoffset);
		vertices_[vertexCount + 5].uv       = Vec2f(static_cast<float>(glyph.position1.x) / glyphAtlasSize, static_cast<float>(glyph.position1.y) / glyphAtlasSize);
		vertices_[vertexCount + 5].color    = color;

		currentPosition.x += glyph.xadvance;
		vertexCount += 6;
	}

	return vertexCount;
}

uint32_t GlyphPass2D::UpdateGlyphVertexBuffer(const TTFont* font, const std::wstring& text, const Vec2f& startPosition, const std::vector<Vec4f>& colors)
{
	float glyphAtlasSize = static_cast<float>(font->GetGlyphAtlasSize());

	Vec2f currentPosition = startPosition;
	int32_t vertexCount = 0;

	std::size_t index = 0;

	for (const auto& unicode : text)
	{
		const Glyph& glyph = font->GetGlyph(static_cast<int32_t>(unicode));

		float unicodeWidth = static_cast<float>(glyph.position1.x - glyph.position0.x);
		float unicodeHeight = static_cast<float>(glyph.position1.y - glyph.position0.y);

		vertices_[vertexCount + 0].position = Vec2f(currentPosition.x + glyph.xoffset, currentPosition.y + glyph.yoffset);
		vertices_[vertexCount + 0].uv = Vec2f(static_cast<float>(glyph.position0.x) / glyphAtlasSize, static_cast<float>(glyph.position0.y) / glyphAtlasSize);
		vertices_[vertexCount + 0].color = colors[index];

		vertices_[vertexCount + 1].position = Vec2f(currentPosition.x + glyph.xoffset, currentPosition.y + unicodeHeight + glyph.yoffset);
		vertices_[vertexCount + 1].uv = Vec2f(static_cast<float>(glyph.position0.x) / glyphAtlasSize, static_cast<float>(glyph.position1.y) / glyphAtlasSize);
		vertices_[vertexCount + 1].color = colors[index];

		vertices_[vertexCount + 2].position = Vec2f(currentPosition.x + glyph.xoffset + unicodeWidth, currentPosition.y + glyph.yoffset);
		vertices_[vertexCount + 2].uv = Vec2f(static_cast<float>(glyph.position1.x) / glyphAtlasSize, static_cast<float>(glyph.position0.y) / glyphAtlasSize);
		vertices_[vertexCount + 2].color = colors[index];

		vertices_[vertexCount + 3].position = Vec2f(currentPosition.x + glyph.xoffset + unicodeWidth, currentPosition.y + glyph.yoffset);
		vertices_[vertexCount + 3].uv = Vec2f(static_cast<float>(glyph.position1.x) / glyphAtlasSize, static_cast<float>(glyph.position0.y) / glyphAtlasSize);
		vertices_[vertexCount + 3].color = colors[index];

		vertices_[vertexCount + 4].position = Vec2f(currentPosition.x + glyph.xoffset, currentPosition.y + unicodeHeight + glyph.yoffset);
		vertices_[vertexCount + 4].uv = Vec2f(static_cast<float>(glyph.position0.x) / glyphAtlasSize, static_cast<float>(glyph.position1.y) / glyphAtlasSize);
		vertices_[vertexCount + 4].color = colors[index];

		vertices_[vertexCount + 5].position = Vec2f(currentPosition.x + glyph.xoffset + unicodeWidth, currentPosition.y + unicodeHeight + glyph.yoffset);
		vertices_[vertexCount + 5].uv = Vec2f(static_cast<float>(glyph.position1.x) / glyphAtlasSize, static_cast<float>(glyph.position1.y) / glyphAtlasSize);
		vertices_[vertexCount + 5].color = colors[index];

		currentPosition.x += glyph.xadvance;
		vertexCount += 6;

		index = (index + 1) % colors.size();
	}

	return vertexCount;
}
