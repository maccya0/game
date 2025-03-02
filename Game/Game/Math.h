#pragma once
#ifndef MATH_H
#define MATH_H
#include <cmath>
#include <memory.h>
#include <limits>
#include "Lib.h"


namespace Math
{
	const F32 Pi = 3.1415926535f;                          //π
	const F32 TwoPi = Pi * 2.0f;                              //2π
	const F32 PiOver2 = Pi / 2.0f;                              //1/2π
	const F32 Infinity = std::numeric_limits<F32>::infinity();  //正の∞
	const F32 NegInfinity = std::numeric_limits<F32>::infinity();  //負の∞



	inline F32 DegToRadians(F32 degrees)
	{
		return degrees * Pi / 180.0f;
	}

	inline F32 RadToDegrees(F32 radians)
	{
		return radians * 180.0f / Pi;
	}

	inline bool NearZero(F32 val, F32 epsilon = TOLEARANCE_RANGE)
	{
		//入力値が誤差範囲なら返す
		if (val <= epsilon)
		{
			return true;
		}
		else
		{
			return false;
		}

	}

	/* 勉強用: 参照渡しは関数コールが速い */
	/*       : 本来はメモリ領域を確保→コピーを行うが、参照渡しでは値の編集時に初めて確保される */
	template <typename T>
	T MAX(const T& a, const T& b)
	{
		//大きい値を返す
		if (a < b)
		{
			return b;
		}
		else
		{
			return a;
		}
	}

	template <typename T>
	T Min(const T& a, const T& b)
	{
		//小さい値を返す
		if (a < b)
		{
			return a;
		}
		else
		{
			return b;
		}
	}

	template <typename T>
	T Clamp(const T& value, const T& upper, const T& lower)
	{
		//3つの入力の真ん中の値を返す
		return Min(upper, Max(lower, value));
	}


	inline F32 Abs(F32 value)
	{
		return fabs(value);
	}

	//三角関数
	inline F32 Cos(F32 angle)
	{
		return cosf(angle);
	}
	inline F32 Sin(F32 angle)
	{
		return sinf(angle);
	}
	inline F32 Tan(F32 angle)
	{
		return tanf(angle);
	}

	//逆三角関数
	inline F32 Acos(F32 val)
	{
		//戻り値は角度
		return acosf(val);
	}
	inline F32 Asin(F32 val)
	{
		//戻り値は角度
		return asinf(val);
	}
	inline F32 Atan2(F32 y, F32 x)
	{
		//戻り値は角度
		return atan2f(y, x);
	}

	//セカント
	inline F32 Sec(F32 angle)
	{
		return 1.0f / Sin(angle);
	}
	//コセカント
	inline F32 Cosec(F32 angle)
	{
		return 1.0f / Cos(angle);
	}
	// コタンジェント
	inline F32 Cot(F32 angle)
	{
		return 1.0f / Tan(angle);
	}


	//線形補間
	inline F32 Leap(F32 a, F32 b, F32 f)
	{
		return a + f * (b - a);
	}

	//平方根
	inline F32 Sqrt(F32 value)
	{
		return sqrtf(value);
	}

	//浮動小数点の余り
	inline F32 Fmod(F32 number, F32 denom)
	{
		return fmod(number, denom);
	}

}
//2D ベクター
class Vector2
{
public:
	F32 x;
	F32 y;

	Vector2()
		:x(0.0f),
		y(0.0f)
	{}
	//ライブラリなので意図しない型変換を防ぐためにexplictで修飾する
	explicit Vector2(F32 inX, F32 inY)
		:x(inX),
		y(inY)
	{}

	void Set(F32 inX, F32 inY)
	{
		x = inX;
		y = inY;
	}
	//friend修飾子を用いてprivateなデータやopratorにアクセスする
	friend Vector2 operator+(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x + b.x, a.y + b.y);
	}
	friend Vector2 operator-(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x - b.x, a.y - b.y);
	}

	friend Vector2 operator*(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x * b.x, a.y * b.y);
	}

	friend Vector2 operator*(const Vector2& vec, F32 scalar)
	{
		return Vector2(vec.x * scalar, vec.y * scalar);
	}

	friend Vector2 operator*(F32 scalar, const Vector2& vec)
	{
		return Vector2(vec.x * scalar, vec.y * scalar);
	}


	Vector2& operator*=(F32 scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	Vector2& operator+=(const Vector2& right)
	{
		x += right.x;
		y += right.y;
		return *this;
	}

	Vector2& operator-=(const Vector2& right)
	{
		x -= right.x;
		y -= right.y;
		return *this;
	}

	//長さの2乗
	F32 LengthSq()const
	{
		//a^2
		return (x * x + y * y);
	}

	//長さ
	F32 Length()const
	{
		//|a|
		return (Math::Sqrt(LengthSq()));
	}

	//自身を正規化する
	void Normalize()
	{
		//単位ベクトル = ベクトルa/|a|
		F32 length = Length();
		x /= length;
		y /= length;
	}

	//※staticにする事で外部からのアクセスを可能にする
	//外部から与えられたベクターを正規化する
	static Vector2 Normalize(const Vector2& vec)
	{
		//単位ベクトル = ベクトルa/|a|
		Vector2 temp = vec;
		F32 length = temp.Length();
		temp.x /= length;
		temp.y /= length;
	}

	//内積を求める
	static F32 Dot(const Vector2& a, const Vector2& b)
	{
		//a.b = a.x*b.x + a.y*b.y
		return (a.x * b.x + a.y * b.y );
	}

	//角度を求める
	static F32 GetAngle(const Vector2& a, const Vector2& b)
	{
		//cosθ=a.b/(|a|*|b|)
		F32 length_a = a.Length();   //|a|
		F32 length_b = b.Length();   //|b|
		F32 temp_dot = Dot(a, b);    //a.b

		//角度を求めたいのでarccos
		return Math::Acos(( temp_dot/(length_a)* (length_b)));
	}

	//線形補完
	static Vector2 Leap(const Vector2& a, const Vector2& b, F32 f)
	{
		return
			(a + f*(a-b));
	}

	//反射ベクトル
	static Vector2 Reflect(const Vector2& in_vec, Vector2& n)
	{
		//in_vec =侵入ベクトル
		//n = 壁の法線ベクトル
		//ベクトルR = ベクトルin_vec - 2(in_vec.n)*n;
		return in_vec - 2.0f * Vector2::Dot(in_vec, n) * n;

	}
	
	//2次元ベクトルから行列への変換
	//static Vector2 Transform(const Vector2& vec, const class Matrix3& mat,F32 w = 1.0f);

	static const Vector2 Zero;      //ゼロベクトル
	static const Vector2 UnitX;     //X方向に大きさ1のベクトル
	static const Vector2 UnitY;     //Y方向に大きさ1のベクトル
	static const Vector2 NegUnitX;  //-X方向に大きさ1のベクトル
	static const Vector2 NegUnitY;  //-Y方向に大きさ1のベクトル

};


//3D ベクター
class Vector3
{
public:
	F32 x;
	F32 y;
	F32 z;

	Vector3()
		:x(0.0f),
		y(0.0f),
		z(0.0f)
	{}
	//ライブラリなので意図しない型変換を防ぐためにexplictで修飾する
	explicit Vector3(F32 inX, F32 inY, F32 inZ)
		:x(inX),
		y(inY),
		z(inZ)
	{}

	void Set(F32 inX, F32 inY, F32 inZ)
	{
		x = inX;
		y = inY;
		z = inZ;
	}
	//friend修飾子を用いてprivateなデータやopratorにアクセスする
	friend Vector3 operator+(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
	}
	friend Vector3 operator-(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	friend Vector3 operator*(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
	}

	friend Vector3 operator*(const Vector3& vec, F32 scalar)
	{
		return Vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
	}

	friend Vector3 operator*(F32 scalar, const Vector3& vec)
	{
		return Vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
	}


	Vector3& operator*=(F32 scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	Vector3& operator+=(const Vector3& right)
	{
		x += right.x;
		y += right.y;
		z += right.z;
		return *this;
	}

	Vector3& operator-=(const Vector3& right)
	{
		x -= right.x;
		y -= right.y;
		z -= right.z;
		return *this;
	}

	//長さの2乗
	F32 LengthSq()const
	{
		//a^2
		return (x * x + y * y + z * z);
	}

	//長さ
	F32 Length()const
	{
		//|a|
		return (Math::Sqrt(LengthSq()));
	}

	//自身を正規化する
	void Normalize()
	{
		//単位ベクトル = ベクトルa/|a|
		F32 length = Length();
		x /= length;
		y /= length;
		z /= length;
	}

	//※staticにする事で外部からのアクセスを可能にする
	//外部から与えられたベクターを正規化する
	static Vector3 Normalize(const Vector3& vec)
	{
		//単位ベクトル = ベクトルa/|a|
		Vector3 temp = vec;
		F32 length = temp.Length();
		temp.x /= length;
		temp.y /= length;
		temp.z /= length;
	}

	//内積を求める
	static F32 Dot(const Vector3& a, const Vector3& b)
	{
		//a.b = a.x*b.x + a.y*b.y
		return (a.x * b.x + a.y * b.y + a.z * b.z);
	}
	//外積を求める
	static F32 Cross(const Vector3& a, const Vector3& b)
	{
		Vector3 temp;
		temp.x = a.y * b.z - a.z * b.y;
		temp.y = a.z * b.x - a.x * b.z;
		temp.z = a.x * b.y - a.y * b.x;
		//a.b = a.x*b.x + a.y*b.y
		return (a.x * b.x + a.y * b.y + a.z * b.z);
	}

	//角度を求める
	static F32 GetAngle(const Vector3& a, const Vector3& b)
	{
		//cosθ=a.b/(|a|*|b|)
		F32 length_a = a.Length();   //|a|
		F32 length_b = b.Length();   //|b|
		F32 temp_dot = Dot(a, b);    //a.b

		//角度を求めたいのでarccos
		return Math::Acos((temp_dot / (length_a) * (length_b)));
	}

	//線形補完
	static Vector3 Leap(const Vector3& a, const Vector3& b, F32 f)
	{
		return
			(a + f * (a - b));
	}

	//反射ベクトル
	static Vector3 Reflect(const Vector3& in_vec, Vector3& n)
	{
		//in_vec =侵入ベクトル
		//n = 壁の法線ベクトル
		//ベクトルR = ベクトルin_vec - 2(in_vec.n)*n;
		return in_vec - 2.0f * Vector3::Dot(in_vec, n) * n;

	}

	//3次元ベクトルから行列への変換
	//static Vector3 Transform(const Vector3& vec, const class Matrix4& mat,F32 w = 1.0f);
	//クォーターニオンによる変換
	//static Vector3 Transform(const Vector3& v, const class Quaternion& q);
	//行列によるベクトル変換
	//static Vector3 TransformWithPerspDiv(const Vector3& vec, const class Matrix4& mat, float w = 1.0f);

	static const Vector3 Zero;        //ゼロベクトル
	static const Vector3 UnitX;       //X方向に大きさ1のベクトル
	static const Vector3 UnitY;       //Y方向に大きさ1のベクトル
	static const Vector3 UnitZ;       //Z方向に大きさ1のベクトル
	static const Vector3 NegUnitX;    //-X方向に大きさ1のベクトル
	static const Vector3 NegUnitY;    //-Y方向に大きさ1のベクトル
	static const Vector3 NegUnitZ;    //-Z方向に大きさ1のベクトル
	static const Vector3 Infinity;    //正の無限大
	static const Vector3 NegInfinity; //負の無限大
};

#endif