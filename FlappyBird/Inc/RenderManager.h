#pragma once

#include <string>
#include <vector>
#include <map>

#include "Mat4x4.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"

#include "IManager.h"
#include "IResource.h"


/**
 * @brief 렌더링에 관련된 처리를 수행하는 매니저입니다.
 * 
 * @note 이 클래스는 싱글턴입니다.
 */
class RenderManager : public IManager
{
public:
	/**
	 * @brief 렌더링 처리를 수행하는 매니저의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(RenderManager);


	/**
	 * @brief 렌더링 처리를 수행하는 매니저의 참조 인스턴스를 얻습니다.
	 *
	 * @return 렌더링 처리를 수행하는 매니저의 참조자를 반환합니다.
	 */
	static RenderManager& Get();


	/**
	 * @brief 렌더링 처리를 수행하는 매니저의 사용을 시작합니다.
	 *
	 * @note
	 * - 이 메서드 호출 전에 렌더링 대상이 되는 윈도우 포인터를 설정해야 합니다.
	 * - 이 메서드는 한 번만 호출되어야 합니다.
	 */
	virtual void Startup() override;


	/**
	 * @brief 렌더링 처리를 수행하는 매니저의 사용을 종료합니다.
	 *
	 * @note
	 * - 애플리케이션 종료 전에 이 메서드를 반드시 호출하여 내부 리소스를 정리해야 합니다.
	 * - 이 메서드는 반드시 한 번만 호출되어야 합니다.
	 */
	virtual void Shutdown() override;

	
	/**
	 * @brief 프레임 렌더링을 시작합니다.
	 *
	 * @param red 색상 버퍼의 R 값입니다.
	 * @param green 색상 버퍼의 G 값입니다.
	 * @param blue 색상 버퍼의 B 값입니다.
	 * @param alpha 색상 버퍼의 A 값입니다.
	 * @param depth 깊이 버퍼의 초기화 값입니다.
	 * @param stencil 스텐실 버퍼의 초기화 값입니다.
	 */
	void BeginFrame(float red, float green, float blue, float alpha, float depth = 1.0f, uint8_t stencil = 0);


	/**
	 * @brief 백버퍼와 프론트 버퍼를 스왑합니다.
	 */
	void EndFrame();


	/**
	 * @brief 뷰 포트를 설정합니다.
	 *
	 * @param x 뷰포트 사각형의 왼쪽 아래 모서리(픽셀)입니다. 기본값은 (0,0)입니다.
	 * @param y 뷰포트 사각형의 왼쪽 아래 모서리(픽셀)입니다. 기본값은 (0,0)입니다.
	 * @param width 뷰포트의 너비입니다. OpenGL 컨텍스트가 창에 처음 연결되면 너비 와 높이 가 해당 창의 크기로 설정됩니다.
	 * @param height 뷰포트의 높이입니다. OpenGL 컨텍스트가 창에 처음 연결되면 너비 와 높이 가 해당 창의 크기로 설정됩니다.
	 */
	void SetViewport(int32_t x, int32_t y, int32_t width, int32_t height);


	/**
	 * @brief 윈도우 뷰포트를 설정합니다.
	 *
	 * @note 기준은 렌더 타켓 윈도우 기준입니다.
	 */
	void SetWindowViewport();


	/**
	 * @brief 수직 동기화 옵션을 설정합니다.
	 *
	 * @param bIsEnable 수직 동기화 옵션을 활성화하려면 true, 비활성화하려면 false입니다.
	 */
	void SetVsyncMode(bool bIsEnable);


	/**
	 * @brief 깊이 테스트 옵션을 설정합니다.
	 *
	 * @param bIsEnable 깊이 테스트 옵션을 활성화하려면 true, 비활성화하려면 false입니다.
	 */
	void SetDepthMode(bool bIsEnable);


	/**
	 * @brief 스텐실 테스트 옵션을 설정합니다.
	 *
	 * @param bIsEnable 스텐실 테스트 옵션을 활성화하려면 true, 비활성화하려면 false입니다.
	 */
	void SetStencilMode(bool bIsEnable);


	/**
	 * @brief 알파 블랜딩 옵션을 설정합니다.
	 *
	 * @param bIsEnable 알파 블랜딩 옵션을 활성화하려면 true, 비활성화하려면 false입니다.
	 */
	void SetAlphaBlendMode(bool bIsEnable);


	/**
	 * @brief 멀티 샘플링 옵션을 설정합니다.
	 * 
	 * @param bIsEnable 멀티 샘플링 옵션을 활성화하려면 true, 비활성화하려면 false입니다.
	 */
	void SetMultisampleMode(bool bIsEnable);


	/**
	 * @brief 바인딩된 프레임 버퍼에 2D 점들을 그립니다.
	 * 
	 * @param positions 2D 점들입니다.
	 * @param color 점들의 색상입니다.
	 * @param pointSize 점의 크기입니다. 기본 값은 1.0f입니다.
	 *
	 * @note 2D 점들의 개수는 MAX_VERTEX_SIZE(10000)의 크기를 넘을 수 없습니다.
	 */
	void RenderPoints2D(const std::vector<Vec2f>& positions, const Vec4f& color, float pointSize = 1.0f);


	/**
	 * @brief 바인딩된 프레임 버퍼에 점들을 연결한 2D 선을 그립니다.
	 * 
	 * @param positions 2D 점들입니다.
	 * @param color 점들의 색상입니다.
	 *
	 * @note 2D 점들의 개수는 MAX_VERTEX_SIZE(10000)의 크기를 넘을 수 없습니다.
	 */
	void RenderConnectPoints2D(const std::vector<Vec2f>& positions, const Vec4f& color);


	/**
	 * @brief 바인딩된 프레임 버퍼에 2D 선을 그립니다.
	 * 
	 * @param fromPosition 선의 시작점입니다.
	 * @param toPosition 선의 끝점입니다.
	 * @param color 선의 색상입니다.
	 */
	void RenderLine2D(const Vec2f& fromPosition, const Vec2f& toPosition, const Vec4f& color);


	/**
	 * @brief 바인딩된 프레임 버퍼에 2D 선을 그립니다.
	 * 
	 * @param fromPosition 선의 시작점입니다.
	 * @param fromColor 선의 시작점 색상입니다.
	 * @param toPosition 선의 끝점입니다.
	 * @param toColor 선의 끝점 색상입니다.
	 */
	void RenderLine2D(const Vec2f& fromPosition, const Vec4f& fromColor, const Vec2f& toPosition, const Vec4f& toColor);


	/**
	 * @brief 바인딩된 프레임 버퍼에 2D 삼각형을 그립니다.
	 * 
	 * @param fromPosition 삼각형 시작 점입니다.
	 * @param byPosition 삼각형 중간 점입니다.
	 * @param toPosition 삼각형 끝 점입니다.
	 * @param color 삼각형의 색상입니다.
	 */
	void RenderTriangle2D(const Vec2f& fromPosition, const Vec2f& byPosition, const Vec2f& toPosition, const Vec4f& color);


	/**
	 * @brief 바인딩된 프레임 버퍼에 2D 삼각형을 그립니다.
	 * 
	 * @param fromPosition 삼각형 시작 점입니다.
	 * @param fromColor 삼각형 시작 점의 색상입니다.
	 * @param byPosition 삼각형 중간 점입니다.
	 * @param byColor 삼각형 중간 점의 색상입니다.
	 * @param toPosition 삼각형 끝 점입니다.
	 * @param toColor 삼각형 끝 점의 색상입니다.
	 */
	void RenderTriangle2D(
		const Vec2f& fromPosition, const Vec4f& fromColor,
		const Vec2f& byPosition, const Vec4f& byColor,
		const Vec2f& toPosition, const Vec4f& toColor
	);


	/**
	 * @brief 바인딩된 프레임 버퍼에 2D 와이어 프레임 삼각형을 그립니다.
	 * 
	 * @param fromPosition 삼각형 시작 점입니다.
	 * @param byPosition 삼각형 중간 점입니다.
	 * @param toPosition 삼각형 끝 점입니다.
	 * @param color 삼각형의 색상입니다.
	 */
	void RenderWireframeTriangle2D(const Vec2f& fromPosition, const Vec2f& byPosition, const Vec2f& toPosition, const Vec4f& color);


	/**
	 * @brief 바인딩된 프레임 버퍼에 2D 와이어 프레임 삼각형을 그립니다.
	 * 
	 * @param fromPosition 삼각형 시작 점입니다.
	 * @param fromColor 삼각형 시작 점의 색상입니다.
	 * @param byPosition 삼각형 중간 점입니다.
	 * @param byColor 삼각형 중간 점의 색상입니다.
	 * @param toPosition 삼각형 끝 점입니다.
	 * @param toColor 삼각형 끝 점의 색상입니다.
	 */
	void RenderWireframeTriangle2D(
		const Vec2f& fromPosition, const Vec4f& fromColor,
		const Vec2f& byPosition, const Vec4f& byColor,
		const Vec2f& toPosition, const Vec4f& toColor
	);


	/**
	 * @brief 바인딩된 프레임 버퍼에 2D 직사각형을 그립니다.
	 * 
	 * @param center 직사각형의 중심 좌표입니다.
	 * @param width 직사각형의 가로 크기입니다.
	 * @param heigt 직사각형의 세로 크기입니다.
	 * @param rotate 직사각형의 라디안 회전 각도입니다.
	 * @param color 직사각형의 색상입니다.
	 */
	void RenderRectangle2D(const Vec2f& center, float width, float height, float rotate, const Vec4f& color);


	/**
	 * @brief 바인딩된 프레임 버퍼에 2D 와이어 프레임 직사각형을 그립니다.
	 * 
	 * @param center 직사각형의 중심 좌표입니다.
	 * @param width 직사각형의 가로 크기입니다.
	 * @param heigt 직사각형의 세로 크기입니다.
	 * @param rotate 직사각형의 라디안 회전 각도입니다.
	 * @param color 직사각형의 색상입니다.
	 */
	void RenderWireframeRectangle2D(const Vec2f& center, float width, float height, float rotate, const Vec4f& color);


	/**
	 * @brief 바인딩된 프레임 버퍼에 모서리가 둥근 2D 사각형을 그립니다.
	 * 
	 * @param center 직사각형의 중심 좌표입니다.
	 * @param width 직사각형의 가로 크기입니다.
	 * @param heigt 직사각형의 세로 크기입니다.
	 * @param side 사각형의 둥근 부분의 크기입니다.
	 * @param rotate 직사각형의 라디안 회전 각도입니다.
	 * @param color 직사각형의 색상입니다.
	 */
	void RenderRoundRectangle2D(const Vec2f& center, float width, float height, float side, float rotate, const Vec4f& color);


	/**
	 * @brief 바인딩된 프레임 버퍼에 모서리가 둥근 2D 와이어 프레임 사각형을 그립니다.
	 * 
	 * @param center 직사각형의 중심 좌표입니다.
	 * @param width 직사각형의 가로 크기입니다.
	 * @param heigt 직사각형의 세로 크기입니다.
	 * @param side 사각형의 둥근 부분의 크기입니다.
	 * @param rotate 직사각형의 라디안 회전 각도입니다.
	 * @param color 직사각형의 색상입니다.
	 */
	void RenderWireframeRoundRectangle2D(const Vec2f& center, float width, float height, float side, float rotate, const Vec4f& color);


	/**
	 * @brief 바인딩된 프레임 버퍼에 2D 원을 그립니다.
	 * 
	 * @param center 원의 중심 좌표입니다.
	 * @param radius 원의 반지름 길이입니다.
	 * @param color 원의 색상입니다.
	 * @param sliceCount 원의 둘레 절단 횟수입니다. 기본 값은 300입니다.
	 */
	void RenderCircle2D(const Vec2f& center, float radius, const Vec4f& color, int32_t sliceCount = 300);


	/**
	 * @brief 바인딩된 프레임 버퍼에 2D 와이어 프레임 원을 그립니다.
	 * 
	 * @param center 원의 중심 좌표입니다.
	 * @param radius 원의 반지름 길이입니다.
	 * @param color 원의 색상입니다.
	 * @param sliceCount 원 둘레의 절단 횟수입니다. 기본 값은 300입니다.
	 */
	void RenderWireframeCircle2D(const Vec2f& center, float radius, const Vec4f& color, int32_t sliceCount = 300);


	/**
	 * @brief 바인딩된 프레임 버퍼에 2D 타원을 그립니다.
	 * 
	 * @param center 타원의 중심 좌표입니다.
	 * @param xAxis 타원의 x축 길이입니다. 만약, 이 길이가 y축 길이보다 크다면 장축이 되고, 그렇지 않으면 단축이 됩니다.
	 * @param yAxis 타원의 y축 길이입니다. 만약, 이 길이가 x축 길이보다 크다면 장축이 되고, 그렇지 않으면 단축이 됩니다.
	 * @param color 타원의 색상입니다.
	 * @param sliceCount 타원 둘레의 절단 횟수입니다. 기본 값은 300입니다.
	 */
	void RenderEllipse2D(const Vec2f& center, float xAxis, float yAxis, const Vec4f& color, int32_t sliceCount = 300);


	/**
	 * @brief 바인딩된 프레임 버퍼에 2D 와이어 프레임 타원을 그립니다.
	 * 
	 * @param center 타원의 중심 좌표입니다.
	 * @param xAxis 타원의 x축 길이입니다. 만약, 이 길이가 y축 길이보다 크다면 장축이 되고, 그렇지 않으면 단축이 됩니다.
	 * @param yAxis 타원의 y축 길이입니다. 만약, 이 길이가 x축 길이보다 크다면 장축이 되고, 그렇지 않으면 단축이 됩니다.
	 * @param color 타원의 색상입니다.
	 * @param sliceCount 타원 둘레의 절단 횟수입니다. 기본 값은 300입니다.
	 */
	void RenderWireframeEllipse2D(const Vec2f& center, float xAxis, float yAxis, const Vec4f& color, int32_t sliceCount = 300);


	/**
	 * @brief 2D 스프라이트를 바인딩된 프레임 버퍼에 그립니다.
	 *
	 * @param textureID 텍스처 리소스 아이디입니다.
	 * @param center 텍스처의 중심 좌표입니다.
	 * @param width 텍스처의 가로 크기입니다.
	 * @param height 텍스처의 세로 크기입니다.
	 * @param rotate 텍스처의 라디안 회전 각도입니다.
	 * @param transparent 텍스처의 투명도입니다. 기본 값은 1.0f(불투명)입니다.
	 */
	void RenderSprite2D(const RUID& textureID, const Vec2f& center, float width, float height, float rotate, float transparent = 1.0f);


	/**
	 * @brief 2D 스프라이트를 바인딩된 프레임 버퍼에 그립니다.
	 *
	 * @note 2D 스프라이트를 윈도우 전체에 채워지도록 그립니다.
	 *
	 * @param textureID 텍스처 리소스 아이디입니다.
	 * @param transparent 텍스처의 투명도입니다. 기본 값은 1.0f(불투명)입니다.
	 */
	void RenderSprite2D(const RUID& textureID, float transparent = 1.0f);


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
	 * @param textureID 텍스처 리소스 아이디 입니다.
	 * @param rate 분할 비율입니다. 값의 범위는 0.0f ~ 1.0f 입니다.
	 * @param transparent 텍스처의 투명도입니다. 기본 값은 1.0f(불투명)입니다.
	 */
	void RenderHorizonScrollSprite2D(const RUID& textureID, float rate, float transparent = 1.0f);


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
	 * @param textureID 텍스처 리소스 아이디 입니다.
	 * @param center 텍스처의 중심 좌표입니다.
	 * @param width 텍스처의 가로 크기입니다.
	 * @param height 텍스처의 세로 크기입니다.
	 * @param rotate 텍스처의 회전 각도입니다. 단위는 라디안입니다.
	 * @param rate 분할 비율입니다. 값의 범위는 0.0f ~ 1.0f 입니다.
	 * @param transparent 텍스처의 투명도입니다. 기본 값은 1.0f(불투명)입니다.
	 */
	void RenderHorizonScrollSprite2D(const RUID& textureID, const Vec2f& center, float width, float height, float rotate, float rate, float transparent = 1.0f);


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
	 * @param textureID 텍스처 리소스 아이디 입니다.
	 * @param rate 분할 비율입니다. 값의 범위는 0.0f ~ 1.0f 입니다.
	 * @param transparent 텍스처의 투명도입니다. 기본 값은 1.0f(불투명)입니다.
	 */
	void RenderVerticalScrollSprite2D(const RUID& textureID, float rate, float transparent = 1.0f);


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
	 * @param textureID 텍스처 리소스 아이디 입니다.
	 * @param center 텍스처의 중심 좌표입니다.
	 * @param width 텍스처의 가로 크기입니다.
	 * @param height 텍스처의 세로 크기입니다.
	 * @param rotate 텍스처의 회전 각도입니다. 단위는 라디안입니다.
	 * @param rate 분할 비율입니다. 값의 범위는 0.0f ~ 1.0f 입니다.
	 * @param transparent 텍스처의 투명도입니다. 기본 값은 1.0f(불투명)입니다.
	 */
	void RenderVerticalScrollSprite2D(const RUID& textureID, const Vec2f& center, float width, float height, float rotate, float rate, float transparent = 1.0f);


	/**
	 * @brief 2D 스프라이트의 외곽선을 바인딩된 프레임 버퍼에 그립니다.
	 *

	 * @param textureID 텍스처 리소스 아이디 입니다.
	 * @param center 텍스처의 중심 좌표입니다.
	 * @param width 텍스처의 가로 크기입니다.
	 * @param height 텍스처의 세로 크기입니다.
	 * @param rotate 텍스처의 라디안 회전 각도입니다.
	 * @param outline 텍스처 외곽선 색상입니다.
	 * @param transparent 텍스처의 투명도입니다. 기본 값은 1.0f 입니다.
	 */
	void RenderOutlineSprite2D(const RUID& textureID, const Vec2f& center, float width, float height, float rotate, const Vec4f& outline, float transparent = 1.0f);


	/**
	 * @brief 2D 텍스트를 바인딩된 프레임 버퍼에 그립니다.
	 * 
	 * @param fontID 폰트 리소스 아이디입니다.
	 * @param text 렌더링할 텍스트입니다.
	 * @param center 텍스트의 좌표입니다.
	 * @param color 텍스트의 RGBA 색상입니다.
	 * @param bIsCenter 텍스트 좌표가 텍스트의 중심인지 확인하는 옵션입니다.
	 * 
	 * @note 중심으로 설정하지 않으면 왼쪽 상단을 기준으로 합니다.
	 */
	void RenderText2D(const RUID& fontID, const std::wstring& text, const Vec2f& position, const Vec4f& color, bool bIsCenter = true);


	/**
	 * @brief 글자마다 색이 다른 2D 텍스트를 바인딩된 프레임 버퍼에 그립니다.
	 * 
	 * @param fontID 폰트 리소스 아이디입니다.
	 * @param text 렌더링할 텍스트입니다.
	 * @param position 텍스트의 좌표입니다.
	 * @param colors 각 글자의 색상 목록입니다.
	 * @param bIsCenter 텍스트 좌표가 텍스트의 중심인지 확인하는 옵션입니다.
	 */
	void RenderText2D(const RUID& fontID, const std::wstring& text, const Vec2f& position, const std::vector<Vec4f>& colors, bool bIsCenter = true);


	/**
	 * @brief 렌더 타겟 윈도우의 가로 세로 크기를 얻습니다.
	 *
	 * @param outWidth 렌더 타겟 윈도우의 가로 크기입니다.
	 * @param outHeight 렌더 타겟 윈도우의 세로 크기입니다.
	 */
	void GetRenderTargetWindowSize(int32_t& outWidth, int32_t& outHeight);


private:
	/**
	 * @brief 렌더링 처리를 수행하는 매니저에 디폴트 생성자와 빈 가상 소멸자를 삽입합니다.
	 */
	DEFAULT_CONSTRUCTOR_AND_VIRTUAL_DESTRUCTOR(RenderManager);


private:
	/**
	 * @brief 렌더링 대상이 되는 윈도우 포인터입니다.
	 */
	void* renderTargetWindow_ = nullptr;


	/**
	 * @brief OpenGL 컨텍스트입니다.
	 */
	void* context_ = nullptr;


	/**
	 * @brief 스크린 투영 행렬입니다.
	 */
	Mat4x4f screenOrtho_;


	/**
	 * @brief 렌더 매니저가 렌더링 시 사용할 셰이더입니다.
	 */
	std::map<std::string, RUID> shaderCache_;
};