#pragma once

#include "Vec2.h"

#include "IBound2D.h"


/**
 * @brief 2D 경계 원입니다.
 */
class BoundCircle2D : public IBound2D
{
public:
	/**
	 * @brief 2D 경계 원의 기본 생성자입니다.
	 */
	explicit BoundCircle2D() : IBound2D(EType::Circle) {}


	/**
	 * @brief 2D 경계 원의 생성자입니다.
	 * 
	 * @param center 경계 원의 중심좌표입니다.
	 * @param radius 경계 원의 반지름 길이입니다.
	 */
	explicit BoundCircle2D(const Vec2f& center, const float& radius) noexcept
		: IBound2D(EType::Circle)
		, center_(center)
		, radius_(radius) {}


	/**
	 * @brief 2D 경계 원의 복사 생성자입니다.
	 * 
	 * @param instance 복사를 수행할 인스턴스입니다.
	 */
	explicit BoundCircle2D(BoundCircle2D&& instance) noexcept
		: IBound2D(instance)
		, center_(instance.center_)
		, radius_(instance.radius_) {}


	/**
	 * @brief 2D 경계 원의 복사 생성자입니다.
	 *
	 * @param instance 복사를 수행할 인스턴스입니다.
	 */
	explicit BoundCircle2D(const BoundCircle2D& instance) noexcept
		: IBound2D(instance)
		, center_(instance.center_)
		, radius_(instance.radius_) {}


	/**
	 * @brief 2D 경계 원의 가상 소멸자입니다.
	 */
	virtual ~BoundCircle2D() {}


	/**
	 * @brief 2D 경계 원의 대입 연산자입니다.
	 * 
	 * @param instance 대입 연산자를 수행할 인스턴스입니다.
	 * 
	 * @return 대입을 수행한 객체의 참조자를 반환합니다.
	 */
	BoundCircle2D& operator=(BoundCircle2D&& instance) noexcept
	{
		if (this == &instance) return *this;

		IBound2D::operator=(instance);

		center_ = instance.center_;
		radius_ = instance.radius_;

		return *this;
	}


	/**
	 * @brief 2D 경계 원의 대입 연산자입니다.
	 *
	 * @param instance 대입 연산자를 수행할 인스턴스입니다.
	 *
	 * @return 대입을 수행한 객체의 참조자를 반환합니다.
	 */
	BoundCircle2D& operator=(const BoundCircle2D& instance) noexcept
	{
		if (this == &instance) return *this;

		IBound2D::operator=(instance);

		center_ = instance.center_;
		radius_ = instance.radius_;

		return *this;
	}
	

	/**
	 * @brief 경계 원의 중심을 설정합니다.
	 * 
	 * @param center 설정할 경계 원의 중심입니다.
	 */
	void SetCenter(const Vec2f& center) { center_ = center; }


	/**
	 * @brief 경계 원의 반지름 길이를 설정합니다.
	 * 
	 * @param radius 설정할 경계 원의 반지름 길이입니다.
	 */
	void SetRadius(const float& radius) { radius_ = radius; }


	/**
	 * @brief 경계 원의 중심 좌표를 얻습니다.
	 * 
	 * @return 경계 원의 중심 좌표를 반환합니다.
	 */
	Vec2f GetCenter() { return center_; }


	/**
	 * @brief 경계 원의 중심 좌표를 얻습니다.
	 *
	 * @return 경계 원의 중심 좌표를 반환합니다.
	 */
	const Vec2f& GetCenter() const { return center_; }


	/**
	 * @brief 경계 원의 반지름 길이를 얻습니다.
	 * 
	 * @return 경계 원의 반지름 길이를 반환합니다.
	 */
	float GetRadius() { return radius_; }


	/**
	 * @brief 경계 원의 반지름 길이를 얻습니다.
	 *
	 * @return 경계 원의 반지름 길이를 반환합니다.
	 */
	const float& GetRadius() const { return radius_; }


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
	 * @brief 경계 원의 중심좌표입니다.
	 */
	Vec2f center_;


	/**
	 * @brief 경계 원의 반지름 길입니다.
	 */
	float radius_ = 0.0f;
};