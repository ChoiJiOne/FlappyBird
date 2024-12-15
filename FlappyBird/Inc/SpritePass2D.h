#pragma once

#include <array>

#include "Shader.h"
#include "Vertex2D.h"

class Texture2D;


/**
 * @brief 2D 스프라이트를 렌더링하는 셰이더입니다.
 *
 * @note
 * - 2D 스프라이트 렌더링 시 기준이 되는 좌표계는 윈도우 좌표계입니다.
 * - 위치나 크기 관련 인자를 받지 않고 렌더링하는 메서드는 윈도우 화면 전체를 기준으로 합니다.
 */
class SpritePass2D : public Shader
{
public:
	/**
	 * @brief 2D 스프라이트를 렌더링하는 셰이더의 생성자입니다.
	 */
	explicit SpritePass2D();


	/**
	 * @brief 2D 스프라이트를 렌더링하는 셰이더의 가상 소멸자입니다.
	 *
	 * @note 셰이더의 내부에서 할당된 요소를 해제하기 위해서는 반드시 Release를 호출해야 합니다.
	 */
	virtual ~SpritePass2D();


	/**
	 * @brief 2D 스프라이트를 렌더링하는 셰이더의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(SpritePass2D);


	/**
	 * @brief 셰이더의 내부 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


	/**
	 * @brief 2D 스프라이트를 화면에 그립니다.
	 *
	 * @param ortho 직교 투영 행렬입니다.
	 * @param texture 텍스처 리소스입니다.
	 * @param center 텍스처의 중심 좌표입니다.
	 * @param width 텍스처의 가로 크기입니다.
	 * @param height 텍스처의 세로 크기입니다.
	 * @param rotate 텍스처의 라디안 회전 각도입니다.
	 * @param transparent 텍스처의 투명도입니다. 기본 값은 1.0f(불투명)입니다.
	 */
	void DrawSprite2D(const Mat4x4f& ortho, const Texture2D* texture, const Vec2f& center, float width, float height, float rotate, float transparent = 1.0f);


	/**
	 * @brief 2D 스프라이트를 화면에 그립니다.
	 *
	 * @note 2D 스프라이트를 윈도우 전체에 채워지도록 그립니다.
	 *
	 * @param texture 텍스처 리소스입니다.
	 * @param transparent 텍스처의 투명도입니다. 기본 값은 1.0f(불투명)입니다.
	 */
	void DrawSprite2D(const Texture2D* texture, float transparent = 1.0f);


	/**
	 * @brief 가로로 스크롤된 2D 스프라이트를 그립니다.
	 *
	 * @note
	 * - 2D 스프라이트를 윈도우 전체에 채워지도록 그립니다.
	 * - 텍스처 분할 비율은 다음과 같습니다.
	 * ┌────────────┬──────────────────┐
	 * │            │                  │
	 * │            │                  │
	 * │            │                  │
	 * │            │                  │
	 * │ 1.0f - rate│       rate       │
	 * │            │                  │
	 * │            │                  │
	 * │            │                  │
	 * └────────────┴──────────────────┘
	 *
	 * @param texture 텍스처 리소스입니다.
	 * @param rate 분할 비율입니다. 값의 범위는 0.0f ~ 1.0f 입니다.
	 * @param transparent 텍스처의 투명도입니다. 기본 값은 1.0f(불투명)입니다.
	 */
	void DrawHorizonScrollSprite2D(const Texture2D* texture, float rate, float transparent = 1.0f);


	/**
	 * @brief 가로로 스크롤된 2D 스프라이트를 그립니다.
	 *
	 * @note
	 * - 텍스처 분할 비율은 다음과 같습니다.
	 * ┌────────────┬──────────────────┐
	 * │            │                  │
	 * │            │                  │
	 * │            │                  │
	 * │            │                  │
	 * │ 1.0f - rate│       rate       │
	 * │            │                  │
	 * │            │                  │
	 * │            │                  │
	 * └────────────┴──────────────────┘
	 *
	 * @param ortho 직교 투영 행렬입니다.
	 * @param texture 텍스처 리소스입니다.
	 * @param center 텍스처의 중심 좌표입니다.
	 * @param width 텍스처의 가로 크기입니다.
	 * @param height 텍스처의 세로 크기입니다.
	 * @param rotate 텍스처의 회전 각도입니다. 단위는 라디안입니다.
	 * @param rate 분할 비율입니다. 값의 범위는 0.0f ~ 1.0f 입니다.
	 * @param transparent 텍스처의 투명도입니다. 기본 값은 1.0f(불투명)입니다.
	 */
	void DrawHorizonScrollSprite2D(const Mat4x4f& ortho, const Texture2D* texture, const Vec2f& center, float width, float height, float rotate, float rate, float transparent = 1.0f);


	/**
	 * @brief 세로로 스크롤된 2D 스프라이트를 그립니다.
	 *
	 * @note
	 * - 2D 스프라이트를 윈도우 전체에 채워지도록 그립니다.
	 * - 텍스처 분할 비율은 다음과 같습니다.
	 * ┌─────────────────────────────┐
	 * │                             │
	 * │                             │
	 * │              rate           │
	 * │                             │
	 * ├─────────────────────────────┤
	 * │                             │
	 * │          1.0f - rate        │
	 * │                             │
	 * └─────────────────────────────┘
	 *
	 * @param texture 텍스처 리소스입니다.
	 * @param rate 분할 비율입니다. 값의 범위는 0.0f ~ 1.0f 입니다.
	 * @param transparent 텍스처의 투명도입니다. 기본 값은 1.0f(불투명)입니다.
	 */
	void DrawVerticalScrollSprite2D(const Texture2D* texture, float rate, float transparent = 1.0f);


	/**
	 * @brief 세로로 스크롤된 2D 스프라이트를 그립니다.
	 *
	 * @note
	 * - 텍스처 분할 비율은 다음과 같습니다.
	 * ┌─────────────────────────────┐
	 * │                             │
	 * │                             │
	 * │              rate           │
	 * │                             │
	 * ├─────────────────────────────┤
	 * │                             │
	 * │          1.0f - rate        │
	 * │                             │
	 * └─────────────────────────────┘
	 *
	 * @param ortho 직교 투영 행렬입니다.
	 * @param texture 텍스처 리소스입니다.
	 * @param center 텍스처의 중심 좌표입니다.
	 * @param width 텍스처의 가로 크기입니다.
	 * @param height 텍스처의 세로 크기입니다.
	 * @param rotate 텍스처의 회전 각도입니다. 단위는 라디안입니다.
	 * @param rate 분할 비율입니다. 값의 범위는 0.0f ~ 1.0f 입니다.
	 * @param transparent 텍스처의 투명도입니다. 기본 값은 1.0f(불투명)입니다.
	 */
	void DrawVerticalScrollSprite2D(const Mat4x4f& ortho, const Texture2D* texture, const Vec2f& center, float width, float height, float rotate, float rate, float transparent = 1.0f);


	/**
	 * @brief 2D 스프라이트의 외곽선을 화면에 그립니다.
	 *
	 * @param ortho 직교 투영 행렬입니다.
	 * @param texture 텍스처 리소스입니다.
	 * @param center 텍스처의 중심 좌표입니다.
	 * @param width 텍스처의 가로 크기입니다.
	 * @param height 텍스처의 세로 크기입니다.
	 * @param rotate 텍스처의 라디안 회전 각도입니다.
	 * @param outline 텍스처 외곽선 색상입니다.
	 * @param transparent 텍스처의 투명도입니다. 기본 값은 1.0f 입니다.
	 *
	 * @see https://github.com/gdquest-demos/godot-shaders/blob/master/godot/Shaders/outline2D_outer.shader
	 */
	void DrawOutlineSprite2D(const Mat4x4f& ortho, const Texture2D* texture, const Vec2f& center, float width, float height, float rotate, const Vec4f& outline, float transparent = 1.0f);


private:
	/**
	 * @brief 2D 기본 도형의 그리기 타입입니다.
	 */
	enum class EDrawType : int32_t
	{
		Triangles   = 0x0004,
		TriangleFan = 0x0006,
		None        = 0xFFFF,
	};


	/**
	 * @brief 스프라이트 그리기를 수행합니다.
	 *
	 * @param transform 변환 행렬입니다.
	 * @param ortho 투영 행렬입니다.
	 * @param texture 텍스처 리소스입니다.
	 * @param vertexCount 정점 수입니다.
	 * @param bIsActiveOutline 텍스처의 외곽선 활성화 여부입니다.
	 * @param transparent 텍스처의 투명도입니다.
	 * @param outline 텍스처의 외곽선 색상입니다. 기본 값은 흰색입니다.
	 */
	void DrawSprite2D(const Mat4x4f& transform, const Mat4x4f& ortho, const EDrawType& drawType, uint32_t vertexCount, const Texture2D* texture, bool bIsActiveOutline, float transparent, const Vec4f& outline = Vec4f(1.0f, 1.0f, 1.0f, 1.0f));


private:
	/**
	 * @brief 텍스처 정점 목록의 최대 크기입니다.
	 */
	static const int32_t MAX_VERTEX_SIZE = 12;


	/**
	 * @brief 텍스처의 정점 목록입니다.
	 */
	std::array<VertexPositionUv2D, MAX_VERTEX_SIZE> vertices_;


	/**
	 * @brief 정점 버퍼의 오브젝트입니다.
	 */
	uint32_t vertexBufferObject_ = 0;


	/**
	 * @brief 정점 버퍼 목록의 오브젝트입니다.
	 */
	uint32_t vertexArrayObject_ = 0;
};