/*=========================================================================
    Date : 2022/01/31(ŒŽ)	Matrix4x4.h
        Author : ‚ª‚Þ‚µ‚é‚§
        Update :
=========================================================================*/
#ifndef MATRIX4X4_H_
#define MATRIX4X4_H_

namespace math
{
    class Matrix4x4
    {
    public:
        //ƒRƒ“ƒXƒgƒ‰ƒNƒ^
        Matrix4x4(bool zero = false);
        Matrix4x4(
            float _11, float _12, float _13, float _14,
            float _21, float _22, float _23, float _24,
            float _31, float _32, float _33, float _34,
            float _41, float _42, float _43, float _44);

        //ƒfƒXƒgƒ‰ƒNƒ^
        ~Matrix4x4();

    public:
        //‰‰ŽZŽq(‘«‚µŽZ)
        Matrix4x4 operator +	(const Matrix4x4& vec);
        Matrix4x4 operator +	(const float& v);
        Matrix4x4 operator +=	(const Matrix4x4& vec);
        Matrix4x4 operator +=	(const float& v);

        //‰‰ŽZŽq(ˆø‚«ŽZ)
        Matrix4x4 operator -	(const Matrix4x4& vec);
        Matrix4x4 operator -	(const float& v);
        Matrix4x4 operator -=	(const Matrix4x4& vec);
        Matrix4x4 operator -=	(const float& v);

        //‰‰ŽZŽq(Š|‚¯ŽZ)
        Matrix4x4 operator *	(const Matrix4x4& vec);
        Matrix4x4 operator *	(const float& v);
        Matrix4x4 operator *=	(const Matrix4x4& vec);
        Matrix4x4 operator *=	(const float& v);

        //‰‰ŽZŽq(Š„‚èŽZ)
        Matrix4x4 operator /	(const Matrix4x4& vec);
        Matrix4x4 operator /	(const float& v);
        Matrix4x4 operator /=	(const Matrix4x4& vec);
        Matrix4x4 operator /=	(const float& v);

    public:
        union
        {
            float mat[4][4];
            struct
            {
                float m11, m12, m13, m14;
                float m21, m22, m23, m24;
                float m31, m32, m33, m34;
                float m41, m42, m43, m44;
            };
        };
    };
}

#endif // !MATRIX4X4_H_

