#pragma once

#include <cstdint>


/**
 * @brief 2D 경계 영역 인터페이스입니다.
 */
class IBound2D
{
public:
	/**
	 * @brief 2D 경계 영역의 종류입니다.
	 */
	enum class EType : int32_t
	{
		None   = 0x00,
		Box    = 0x01, // 축 정렬 경계 상자 (AABB)입니다.
		Circle = 0x02,
	};


public:
	/**
	 * @brief 2D 경계 영역의 생성자입니다.
	 *
	 * @param type 2D 경계 영역의 종류입니다.
	 */
	explicit IBound2D(EType&& type) noexcept 
		: type_(type) {}
	
	
	/**
	 * @brief 2D 경계 영역의 생성자입니다.
	 * 
	 * @param type 2D 경계 영역의 종류입니다.
	 */
	explicit IBound2D(const EType& type) noexcept 
		: type_(type) {}


	/**
	 * @brief 2D 경계 영역의 복사 생성자입니다.
	 * 
	 * @param instance 복사를 수행할 인스턴스입니다.
	 */
	explicit IBound2D(IBound2D&& instance) noexcept 
		: type_(instance.type_) {}


	/**
	 * @brief 2D 경계 영역의 복사 생성자입니다.
	 *
	 * @param instance 복사를 수행할 인스턴스입니다.
	 */
	explicit IBound2D(const IBound2D& instance) noexcept 
		: type_(instance.type_) {}


	/**
	 * @brief 2D 경계 영역의 가상 소멸자입니다.
	 */
	virtual ~IBound2D() {}


	/**
	 * @brief 2D 경계 영역의 대입 연산자입니다.
	 *
	 * @param instance 대입 연산을 수행할 인스턴스입니다.
	 * 
	 * @return 대입을 수행한 객체의 참조자를 반환합니다.
	 */
	IBound2D& operator=(IBound2D&& instance) noexcept
	{
		if (this == &instance) return *this;

		type_ = instance.type_;

		return *this;
	}


	/**
	 * @brief 2D 경계 영역의 대입 연산자입니다.
	 * 
	 * @param instance 대입 연산을 수행할 인스턴스입니다.
	 * 
	 * @return 대입을 수행한 객체의 참조자를 반환합니다.
	 */
	IBound2D& operator=(const IBound2D& instance) noexcept
	{
		if (this == &instance) return *this;

		type_ = instance.type_;

		return *this;
	}

	
	/**
	 * @brief 2D 경계 영역의 종류를 얻습니다.
	 * 
	 * @return 2D 경계 영역의 종류를 반환합니다.
	 */
	EType GetType() { return type_; }


	/**
	 * @brief 2D 경계 영역의 종류를 얻습니다.
	 *
	 * @return 2D 경계 영역의 종류를 반환합니다.
	 */
	const EType& GetType() const { return type_; }


	/**
	 * @brief 다른 2D 영역과 충돌하는지 검사합니다.
	 * 
	 * @param bound 충돌 여부를 검사할 경계 영역입니다.
	 * 
	 * @return 다른 경계 영역과 충돌한다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	virtual bool Intersect(const IBound2D* bound) const = 0;


protected:
	/**
	 * @brief 서로 다른 2D 영역이 충돌하는지 검사합니다.
	 * 
	 * @param bound0 두 2D 영역이 충돌하는지 검사할 영역입니다.
	 * @param bound1 두 2D 영역이 충돌하는지 검사할 또 다른 영역입니다.
	 */
	bool IsIntersect(const IBound2D* bound0, const IBound2D* bound1) const;


private:
	/**
	 * @brief Box와 Box가 충돌하는지 검사합니다.
	 * 
	 * @param bound0 충돌 여부를 검출할 Box 영역입니다.
	 * @param bound1 충돌 여부를 검출할 또 다른 Box 영역입니다.
	 */
	bool IntersectBoxToBox(const IBound2D* bound0, const IBound2D* bound1) const;


	/**
	 * @brief Box와 Circle이 충돌하는지 검사합니다.
	 *
	 * @param bound0 충돌 여부를 검출할 Box 영역입니다.
	 * @param bound1 충돌 여부를 검출할 또 다른 Circle 영역입니다.
	 */
	bool IntersectBoxToCircle(const IBound2D* bound0, const IBound2D* bound1) const;


	/**
	 * @brief Circle와 Circle이 충돌하는지 검사합니다.
	 *
	 * @param bound0 충돌 여부를 검출할 Circle 영역입니다.
	 * @param bound1 충돌 여부를 검출할 또 다른 Circle 영역입니다.
	 */
	bool IntersectCircleToCircle(const IBound2D* bound0, const IBound2D* bound1) const;


protected:
	/**
	 * @brief 경계 영역의 종류입니다.
	 */
	EType type_ = EType::None;
};