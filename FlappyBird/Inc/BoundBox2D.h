#pragma once

#include "Vec2.h"

#include "IBound2D.h"


/**
 * @brief 2D 축 정렬 경계 영역입니다.
 */
class BoundBox2D : public IBound2D
{
public:
	/**
	 * @brief 2D 축 정렬 경계 영역의 기본 생성자입니다.
	 */
	explicit BoundBox2D() : IBound2D(EType::Box) {}


	/**
	 * @brief 2D 축 정렬 경계 영역의 생성자입니다.
	 * 
	 * @param minPosition 축 정렬 경계 영역의 최소값입니다.
	 * @param maxPosition 축 정렬 경계 영역의 최댓값입니다.
	 */
	explicit BoundBox2D(const Vec2f& minPosition, const Vec2f& maxPosition);


	/**
	 * @brief 2D 축 정렬 경계 영역의 생성자입니다.
	 * 
	 * @param center 축 정렬 경계 영역의 중심좌표입니다.
	 * @param width 축 정렬 경계 영역의 가로 크기입니다.
	 * @param height 축 정렬 경계 영역의 세로 크기입니다.
	 */
	explicit BoundBox2D(const Vec2f& center, const float& width, const float& height);


	/**
	 * @brief 2D 축 정렬 경계 영역의 복사 생성자입니다.
	 * 
	 * @param instance 복사를 수행할 인스턴스입니다.
	 */
	explicit BoundBox2D(BoundBox2D&& instance) noexcept
		: IBound2D(instance)
		, center_(instance.center_)
		, width_(instance.width_)
		, height_(instance.height_)
		, minPosition_(instance.minPosition_)
		, maxPosition_(instance.maxPosition_) {}


	/**
	 * @brief 2D 축 정렬 경계 영역의 복사 생성자입니다.
	 *
	 * @param instance 복사를 수행할 인스턴스입니다.
	 */
	explicit BoundBox2D(const BoundBox2D& instance) noexcept
		: IBound2D(instance)
		, center_(instance.center_)
		, width_(instance.width_)
		, height_(instance.height_)
		, minPosition_(instance.minPosition_)
		, maxPosition_(instance.maxPosition_) {}


	/**
	 * @brief 2D 축 정렬 경계 영역의 가상 소멸자입니다.
	 */
	virtual ~BoundBox2D() {}


	/**
	 * @brief 2D 축 정렬 경계 영역의 대입 연산자입니다.
	 * 
	 * @param instance 대입 연산을 수행할 인스턴스입니다.
	 * 
	 * @return 대입을 수행한 객체의 참조자를 반환합니다.
	 */
	BoundBox2D& operator=(BoundBox2D&& instance) noexcept
	{
		if (this == &instance) return *this;

		IBound2D::operator=(instance);

		center_ = instance.center_;
		width_ = instance.width_;
		height_ = instance.height_;
		minPosition_ = instance.minPosition_;
		maxPosition_ = instance.maxPosition_;

		return *this;
	}


	/**
	 * @brief 2D 축 정렬 경계 영역의 대입 연산자입니다.
	 *
	 * @param instance 대입 연산을 수행할 인스턴스입니다.
	 *
	 * @return 대입을 수행한 객체의 참조자를 반환합니다.
	 */
	BoundBox2D& operator=(const BoundBox2D& instance) noexcept
	{
		if (this == &instance) return *this;

		IBound2D::operator=(instance);

		center_ = instance.center_;
		width_ = instance.width_;
		height_ = instance.height_;
		minPosition_ = instance.minPosition_;
		maxPosition_ = instance.maxPosition_;

		return *this;
	}


	/**
	 * @brief 2D 경계 영역 상자의 프로퍼티를 설정합니다.
	 *
	 * @param minPosition 축 정렬 경계 상자의 최소 좌표입니다.
	 * @param maxPosition 축 정렬 경계 상자의 최대 좌표입니다.
	 */
	void SetProperty(const Vec2f& minPosition, const Vec2f& maxPosition);


	/**
	 * @brief 2D 경계 영역 상자의 프로퍼티를 설정합니다.
	 *
	 * @param center 축 정렬 경계 상자의 중심 좌표입니다.
	 * @param width 축 정렬 경계 상자의 가로 크기입니다.
	 * @param height 축 정렬 경계 상자의 세로 크기입니다.
	 */
	void SetProperty(const Vec2f& center, const float& width, const float& height);


	/**
	 * @brief 2D 경계 영역 상자의 중심을 설정합니다.
	 * 
	 * @param center 축 정렬 경계 상자의 중심입니다.
	 */
	void SetCenter(const Vec2f& center);


	/**
	 * @brief 2D 경계 영역 상자의 중심을 얻습니다.
	 * 
	 * @return 2D 경계 영역 상자의 중심을 반환합니다.
	 */
	Vec2f GetCenter() { return center_; }


	/**
	 * @brief 2D 경계 영역 상자의 중심을 얻습니다.
	 *
	 * @return 2D 경계 영역 상자의 중심을 반환합니다.
	 */
	const Vec2f& GetCenter() const { return center_; }
	

	/**
	 * @brief 2D 경계 영역 상자의 가로 크기를 얻습니다.
	 * 
	 * @return 2D 경계 영역 상자의 가로 크기를 반환합니다.
	 */
	float GetWidth() { return width_; }


	/**
	 * @brief 2D 경계 영역 상자의 세로 크기를 얻습니다.
	 *
	 * @return 2D 경계 영역 상자의 세로 크기를 반환합니다.
	 */
	const float& GetWidth() const { return width_; }


	/**
	 * @brief 2D 경계 영역 상자의 세로 크기를 얻습니다.
	 *
	 * @return 2D 경계 영역 상자의 세로 크기를 반환합니다.
	 */
	float GetHeight() { return height_; }


	/**
	 * @brief 2D 경계 영역 상자의 세로 크기를 얻습니다.
	 *
	 * @return 2D 경계 영역 상자의 세로 크기를 반환합니다.
	 */
	const float& GetHeight() const { return height_; }


	/**
	 * @brief 2D 경계 영역의 최소값을 얻습니다.
	 * 
	 * @return 2D 경계 영역의 최소값을 반환합니다.
	 */
	Vec2f GetMinPosition() { return minPosition_; }


	/**
	 * @brief 2D 경계 영역의 최소값을 얻습니다.
	 *
	 * @return 2D 경계 영역의 최소값을 반환합니다.
	 */
	const Vec2f& GetMinPosition() const { return minPosition_; }


	/**
	 * @brief 2D 경계 영역의 최대값을 얻습니다.
	 *
	 * @return 2D 경계 영역의 최대값을 반환합니다.
	 */
	Vec2f GetMaxPosition() { return maxPosition_; }


	/**
	 * @brief 2D 경계 영역의 최대값을 얻습니다.
	 *
	 * @return 2D 경계 영역의 최대값을 반환합니다.
	 */
	const Vec2f& GetMaxPosition() const { return maxPosition_; }


	/**
	 * @brief 다른 2D 영역과 충돌하는지 검사합니다.
	 *
	 * @param bound 충돌 여부를 검사할 경계 영역입니다.
	 *
	 * @return 다른 경계 영역과 충돌한다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	virtual bool Intersect(const IBound2D* bound) const override;


private:
	/**
	 * @brief 경계 영역의 중심 좌표와 가로/세로 크기로부터 최대/최소값을 계산합니다.
	 * 
	 * @param center 경계 영역의 중심좌표입니다.
	 * @param width 경계 영역의 가로 크기입니다.
	 * @param height 경계 영역의 세로 크기입니다.
	 * @param outMinPosition 경계 영역의 최소값입니다.
	 * @param outMaxPosition 경계 영역의 최대값입니다.
	 */
	void ComputeBoundBoxProperties(const Vec2f& center, const float& width, const float& height, Vec2f& outMinPosition, Vec2f& outMaxPosition) const;
	

	/**
	 * @brief 경계 영역의 최대/최소값으로부터 중심 좌표와 가로/세로 크기를 계산합니다.
	 * 
	 * @param minPosition 경계 영역의 최소값입니다.
	 * @param maxPosition 경계 영역의 최대값입니다.
	 * @param outCenter 경계 영역의 중심좌표입니다.
	 * @param outWidth 경계 영역의 가로 크기입니다.
	 * @param outHeight 경계 영역의 세로 크기입니다.
	 */
	void ComputeBoundBoxProperties(const Vec2f& minPosition, const Vec2f& maxPosition, Vec2f& outCenter, float& outWidth, float& outHeight) const;


private:
	/**
	 * @brief 경계 영역의 중심 좌표입니다.
	 */
	Vec2f center_;


	/**
	 * @brief 경계 영역의 가로 크기입니다.
	 */
	float width_ = 0.0f;


	/**
	 * @brief 경계 영역의 세로 크기입니다.
	 */
	float height_ = 0.0f;


	/**
	 * @brief 경계 영역의 최소값입니다.
	 */
	Vec2f minPosition_;


	/**
	 * @brief 경계 영역의 최댓값입니다.
	 */
	Vec2f maxPosition_;
};