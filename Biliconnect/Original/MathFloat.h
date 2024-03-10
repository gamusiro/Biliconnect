/*=========================================================================
    Date : 2022/01/31(月)	MathFloat.h
        Author : がむしるぉ
        Update :
=========================================================================*/
#ifndef MATHFLOAT_H_
#define MATHFLOAT_H_

#include "Float2.h"
#include "Float3.h"
#include "Float4.h"

namespace math
{
    class MathFloat
    {
    public:
        //内積を求める関数
        static float Dot(const Float2& vec1, const Float2& vec2);
        static float Dot(const Float3& vec1, const Float3& vec2);
        static float Dot(const Float4& vec1, const Float4& vec2);

        //外積を求める関数
        static float  Cross(const Float2& vec1, const Float2& vec2);
        static Float3 Cross(const Float3& vec1, const Float3& vec2);

        //ベクトルの長さ(平方根の計算有)
        static float Length(const Float2& v);
        static float Length(const Float3& v);
        static float Length(const Float4& v);

        //ベクトルの長さ(平方根の計算無)
        static float LengthSq(const Float2& v);
        static float LengthSq(const Float3& v);
        static float LengthSq(const Float4& v);

        //線形補間
        static Float2 Lerp(const Float2& start, const Float2& end, float mediated);
        static Float3 Lerp(const Float3& start, const Float3& end, float mediated);
        static Float4 Lerp(const Float4& start, const Float4& end, float mediated);

        //最大値を返す
        static Float2 Maxmize(const Float2& vec1, const Float2& vec2);
        static Float3 Maxmize(const Float3& vec1, const Float3& vec2);
        static Float4 Maxmize(const Float4& vec1, const Float4& vec2);

        //最小値を返す
        static Float2 Minimize(const Float2& vec1, const Float2& vec2);
        static Float3 Minimize(const Float3& vec1, const Float3& vec2);
        static Float4 Minimize(const Float4& vec1, const Float4& vec2);

        //正規化値を返す
        static Float2 Normalize(const Float2& v);
        static Float3 Normalize(const Float3& v);
        static Float4 Normalize(const Float4& v);
    };
}

#endif // !MATHFLOAT_H_
