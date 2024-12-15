#include <windows.h>

#include <SDL.h>
#include <glad/glad.h>

#include "MathModule.h"

#include "Assertion.h"
#include "GeometryPass2D.h"
#include "GlyphPass2D.h"
#include "IResource.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "SDLManager.h"
#include "SpritePass2D.h"
#include "Texture2D.h"
#include "TTFont.h"

RenderManager& RenderManager::Get()
{
	static RenderManager instance;
	return instance;
}

void RenderManager::Startup()
{
	CHECK(!bIsStartup_);
	CHECK(!renderTargetWindow_);

	renderTargetWindow_ = SDLManager::Get().GetMainWindow();
	SDL_Window* window = reinterpret_cast<SDL_Window*>(renderTargetWindow_);

	context_ = SDL_GL_CreateContext(window);
	CHECK(context_ != nullptr);

	SDL_FAILED(SDL_GL_MakeCurrent(window, context_));

	CHECK(gladLoadGLLoader((GLADloadproc)(SDL_GL_GetProcAddress)));

	shaderCache_ = std::map<std::string, RUID>();
	shaderCache_.insert({ "GeometryPass2D", ResourceManager::Get().CreateID<GeometryPass2D>() });
	shaderCache_.insert({ "SpritePass2D",   ResourceManager::Get().CreateID<SpritePass2D>()   });
	shaderCache_.insert({ "GlyphPass2D",    ResourceManager::Get().CreateID<GlyphPass2D>()    });

	bIsStartup_ = true;
}

void RenderManager::Shutdown()
{
	CHECK(bIsStartup_);

	if (context_)
	{
		SDL_GL_DeleteContext(context_);
		context_ = nullptr;
	}

	renderTargetWindow_ = nullptr;
	bIsStartup_ = false;
}

void RenderManager::BeginFrame(float red, float green, float blue, float alpha, float depth, uint8_t stencil)
{
	int32_t width = 0;
	int32_t height = 0;
	GetRenderTargetWindowSize(width, height);
	screenOrtho_ = MathModule::CreateOrtho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);

	glClearColor(red, green, blue, alpha);
	glClearDepth(depth);
	glClearStencil(stencil);

	GL_FAILED(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
}

void RenderManager::EndFrame()
{
	SDL_GL_SwapWindow(reinterpret_cast<SDL_Window*>(renderTargetWindow_));
}

void RenderManager::SetViewport(int32_t x, int32_t y, int32_t width, int32_t height)
{
	glViewport(x, y, width, height);
}

void RenderManager::SetWindowViewport()
{
	int32_t width = 0;
	int32_t height = 0;
	GetRenderTargetWindowSize(width, height);

	SetViewport(0, 0, width, height);
}

void RenderManager::SetVsyncMode(bool bIsEnable)
{
	SDL_FAILED(SDL_GL_SetSwapInterval(static_cast<int32_t>(bIsEnable)));
}

void RenderManager::SetDepthMode(bool bIsEnable)
{
	if (bIsEnable)
	{
		GL_FAILED(glEnable(GL_DEPTH_TEST));
	}
	else
	{
		GL_FAILED(glDisable(GL_DEPTH_TEST));
	}
}

void RenderManager::SetStencilMode(bool bIsEnable)
{
	if (bIsEnable)
	{
		GL_FAILED(glEnable(GL_STENCIL_TEST));
	}
	else
	{
		GL_FAILED(glDisable(GL_STENCIL_TEST));
	}
}

void RenderManager::SetAlphaBlendMode(bool bIsEnable)
{
	if (bIsEnable)
	{
		GL_FAILED(glEnable(GL_BLEND));
		GL_FAILED(glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO));
	}
	else
	{
		GL_FAILED(glDisable(GL_BLEND));
	}
}

void RenderManager::SetMultisampleMode(bool bIsEnable)
{
	if (bIsEnable)
	{
		GL_FAILED(glEnable(GL_MULTISAMPLE));
	}
	else
	{
		GL_FAILED(glDisable(GL_MULTISAMPLE));
	}
}

void RenderManager::RenderPoints2D(const std::vector<Vec2f>& positions, const Vec4f& color, float pointSize)
{
	GeometryPass2D* pass = ResourceManager::Get().GetResource<GeometryPass2D>(shaderCache_.at("GeometryPass2D"));
	pass->DrawPoints2D(screenOrtho_, positions, color, pointSize);
}

void RenderManager::RenderConnectPoints2D(const std::vector<Vec2f>& positions, const Vec4f& color)
{
	GeometryPass2D* pass = ResourceManager::Get().GetResource<GeometryPass2D>(shaderCache_.at("GeometryPass2D"));
	pass->DrawConnectPoints2D(screenOrtho_, positions, color);
}

void RenderManager::RenderLine2D(const Vec2f& fromPosition, const Vec2f& toPosition, const Vec4f& color)
{
	GeometryPass2D* pass = ResourceManager::Get().GetResource<GeometryPass2D>(shaderCache_.at("GeometryPass2D"));
	pass->DrawLine2D(screenOrtho_, fromPosition, toPosition, color);
}

void RenderManager::RenderLine2D(const Vec2f& fromPosition, const Vec4f& fromColor, const Vec2f& toPosition, const Vec4f& toColor)
{
	GeometryPass2D* pass = ResourceManager::Get().GetResource<GeometryPass2D>(shaderCache_.at("GeometryPass2D"));
	pass->DrawLine2D(screenOrtho_, fromPosition, fromColor, toPosition, toColor);
}

void RenderManager::RenderTriangle2D(const Vec2f& fromPosition, const Vec2f& byPosition, const Vec2f& toPosition, const Vec4f& color)
{
	GeometryPass2D* pass = ResourceManager::Get().GetResource<GeometryPass2D>(shaderCache_.at("GeometryPass2D"));
	pass->DrawTriangle2D(screenOrtho_, fromPosition, byPosition, toPosition, color);
}

void RenderManager::RenderTriangle2D(const Vec2f& fromPosition, const Vec4f& fromColor, const Vec2f& byPosition, const Vec4f& byColor, const Vec2f& toPosition, const Vec4f& toColor)
{
	GeometryPass2D* pass = ResourceManager::Get().GetResource<GeometryPass2D>(shaderCache_.at("GeometryPass2D"));
	pass->DrawTriangle2D(screenOrtho_, fromPosition, fromColor, byPosition, byColor, toPosition, toColor);
}

void RenderManager::RenderWireframeTriangle2D(const Vec2f& fromPosition, const Vec2f& byPosition, const Vec2f& toPosition, const Vec4f& color)
{
	GeometryPass2D* pass = ResourceManager::Get().GetResource<GeometryPass2D>(shaderCache_.at("GeometryPass2D"));
	pass->DrawWireframeTriangle2D(screenOrtho_, fromPosition, byPosition, toPosition, color);
}

void RenderManager::RenderWireframeTriangle2D(const Vec2f& fromPosition, const Vec4f& fromColor, const Vec2f& byPosition, const Vec4f& byColor, const Vec2f& toPosition, const Vec4f& toColor)
{
	GeometryPass2D* pass = ResourceManager::Get().GetResource<GeometryPass2D>(shaderCache_.at("GeometryPass2D"));
	pass->DrawWireframeTriangle2D(screenOrtho_, fromPosition, fromColor, byPosition, byColor, toPosition, toColor);
}

void RenderManager::RenderRectangle2D(const Vec2f& center, float width, float height, float rotate, const Vec4f& color)
{
	GeometryPass2D* pass = ResourceManager::Get().GetResource<GeometryPass2D>(shaderCache_.at("GeometryPass2D"));
	pass->DrawRectangle2D(screenOrtho_, center, width, height, rotate, color);
}

void RenderManager::RenderWireframeRectangle2D(const Vec2f& center, float width, float height, float rotate, const Vec4f& color)
{
	GeometryPass2D* pass = ResourceManager::Get().GetResource<GeometryPass2D>(shaderCache_.at("GeometryPass2D"));
	pass->DrawWireframeRectangle2D(screenOrtho_, center, width, height, rotate, color);
}

void RenderManager::RenderRoundRectangle2D(const Vec2f& center, float width, float height, float side, float rotate, const Vec4f& color)
{
	GeometryPass2D* pass = ResourceManager::Get().GetResource<GeometryPass2D>(shaderCache_.at("GeometryPass2D"));
	pass->DrawRoundRectangle2D(screenOrtho_, center, width, height, side, rotate, color);
}

void RenderManager::RenderWireframeRoundRectangle2D(const Vec2f& center, float width, float height, float side, float rotate, const Vec4f& color)
{
	GeometryPass2D* pass = ResourceManager::Get().GetResource<GeometryPass2D>(shaderCache_.at("GeometryPass2D"));
	pass->DrawWireframeRoundRectangle2D(screenOrtho_, center, width, height, side, rotate, color);
}

void RenderManager::RenderCircle2D(const Vec2f& center, float radius, const Vec4f& color, int32_t sliceCount)
{
	GeometryPass2D* pass = ResourceManager::Get().GetResource<GeometryPass2D>(shaderCache_.at("GeometryPass2D"));
	pass->DrawCircle2D(screenOrtho_, center, radius, color, sliceCount);
}

void RenderManager::RenderWireframeCircle2D(const Vec2f& center, float radius, const Vec4f& color, int32_t sliceCount)
{
	GeometryPass2D* pass = ResourceManager::Get().GetResource<GeometryPass2D>(shaderCache_.at("GeometryPass2D"));
	pass->DrawWireframeCircle2D(screenOrtho_, center, radius, color, sliceCount);
}

void RenderManager::RenderEllipse2D(const Vec2f& center, float xAxis, float yAxis, const Vec4f& color, int32_t sliceCount)
{
	GeometryPass2D* pass = ResourceManager::Get().GetResource<GeometryPass2D>(shaderCache_.at("GeometryPass2D"));
	pass->DrawEllipse2D(screenOrtho_, center, xAxis, yAxis, color, sliceCount);
}

void RenderManager::RenderWireframeEllipse2D(const Vec2f& center, float xAxis, float yAxis, const Vec4f& color, int32_t sliceCount)
{
	GeometryPass2D* pass = ResourceManager::Get().GetResource<GeometryPass2D>(shaderCache_.at("GeometryPass2D"));
	pass->DrawWireframeEllipse2D(screenOrtho_, center, xAxis, yAxis, color, sliceCount);
}

void RenderManager::RenderSprite2D(const RUID& textureID, const Vec2f& center, float width, float height, float rotate, float transparent)
{
	SpritePass2D* pass = ResourceManager::Get().GetResource<SpritePass2D>(shaderCache_.at("SpritePass2D"));
	Texture2D* texture = ResourceManager::Get().GetResource<Texture2D>(textureID);

	pass->DrawSprite2D(screenOrtho_, texture, center, width, height, rotate, transparent);
}

void RenderManager::RenderSprite2D(const RUID& textureID, float transparent)
{
	SpritePass2D* pass = ResourceManager::Get().GetResource<SpritePass2D>(shaderCache_.at("SpritePass2D"));
	Texture2D* texture = ResourceManager::Get().GetResource<Texture2D>(textureID);

	pass->DrawSprite2D(texture, transparent);
}

void RenderManager::RenderHorizonScrollSprite2D(const RUID& textureID, float rate, float transparent)
{
	SpritePass2D* pass = ResourceManager::Get().GetResource<SpritePass2D>(shaderCache_.at("SpritePass2D"));
	Texture2D* texture = ResourceManager::Get().GetResource<Texture2D>(textureID);

	pass->DrawHorizonScrollSprite2D(texture, rate, transparent);
}

void RenderManager::RenderHorizonScrollSprite2D(const RUID& textureID, const Vec2f& center, float width, float height, float rotate, float rate, float transparent)
{
	SpritePass2D* pass = ResourceManager::Get().GetResource<SpritePass2D>(shaderCache_.at("SpritePass2D"));
	Texture2D* texture = ResourceManager::Get().GetResource<Texture2D>(textureID);

	pass->DrawHorizonScrollSprite2D(screenOrtho_, texture, center, width, height, rotate, rate, transparent);
}

void RenderManager::RenderVerticalScrollSprite2D(const RUID& textureID, float rate, float transparent)
{
	SpritePass2D* pass = ResourceManager::Get().GetResource<SpritePass2D>(shaderCache_.at("SpritePass2D"));
	Texture2D* texture = ResourceManager::Get().GetResource<Texture2D>(textureID);

	pass->DrawVerticalScrollSprite2D(texture, rate, transparent);
}

void RenderManager::RenderVerticalScrollSprite2D(const RUID& textureID, const Vec2f& center, float width, float height, float rotate, float rate, float transparent)
{
	SpritePass2D* pass = ResourceManager::Get().GetResource<SpritePass2D>(shaderCache_.at("SpritePass2D"));
	Texture2D* texture = ResourceManager::Get().GetResource<Texture2D>(textureID);

	pass->DrawVerticalScrollSprite2D(screenOrtho_, texture, center, width, height, rotate, rate, transparent);
}

void RenderManager::RenderOutlineSprite2D(const RUID& textureID, const Vec2f& center, float width, float height, float rotate, const Vec4f& outline, float transparent)
{
	SpritePass2D* pass = ResourceManager::Get().GetResource<SpritePass2D>(shaderCache_.at("SpritePass2D"));
	Texture2D* texture = ResourceManager::Get().GetResource<Texture2D>(textureID);

	pass->DrawOutlineSprite2D(screenOrtho_, texture, center, width, height, rotate, outline, transparent);
}

void RenderManager::RenderText2D(const RUID& fontID, const std::wstring& text, const Vec2f& position, const Vec4f& color, bool bIsCenter)
{
	GlyphPass2D* pass = ResourceManager::Get().GetResource<GlyphPass2D>(shaderCache_.at("GlyphPass2D"));
	TTFont* font = ResourceManager::Get().GetResource<TTFont>(fontID);

	GlyphPass2D::EAlignment alignment = bIsCenter ? GlyphPass2D::EAlignment::Center : GlyphPass2D::EAlignment::Left;

	pass->DrawText2D(screenOrtho_, font, text, position, alignment, color);
}

void RenderManager::RenderText2D(const RUID& fontID, const std::wstring& text, const Vec2f& position, const std::vector<Vec4f>& colors, bool bIsCenter)
{
	GlyphPass2D* pass = ResourceManager::Get().GetResource<GlyphPass2D>(shaderCache_.at("GlyphPass2D"));
	TTFont* font = ResourceManager::Get().GetResource<TTFont>(fontID);

	GlyphPass2D::EAlignment alignment = bIsCenter ? GlyphPass2D::EAlignment::Center : GlyphPass2D::EAlignment::Left;

	pass->DrawText2D(screenOrtho_, font, text, position, alignment, colors);
}

void RenderManager::GetRenderTargetWindowSize(int32_t& outWidth, int32_t& outHeight)
{
	SDL_Window* window = reinterpret_cast<SDL_Window*>(renderTargetWindow_);
	SDL_GetWindowSize(window, &outWidth, &outHeight);
}