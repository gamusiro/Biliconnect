/*=========================================================================
    Date : 2022/01/31(月)	MathMatrix.h
        Author : がむしるぉ
        Update :
=========================================================================*/
#ifndef MATHMATRIX_H_
#define MATHMATRIX_H_

#include "Float3.h"
#include "Matrix4x4.h"

namespace math
{
    class MathMatrix
    {
    public:
        //単位行列の変換
        static void Identity(Matrix4x4& mat);

        //逆行列の変換
        static void Inverse(Matrix4x4& mat);

        //スケーリングの変換
        static void Scaling(Matrix4x4& mat, float sx, float sy, float sz);
        static void Scaling(Matrix4x4& mat, const Float3& scale);
        static void Scaling(Matrix4x4& mat, const Float3* scale);

        //平行移動の変換
        static void Translation(Matrix4x4& mat, float sx, float sy, float sz);
        static void Translation(Matrix4x4& mat, const Float3& scale);
        static void Translation(Matrix4x4& mat, const Float3* scale);

        //回転移動の変換
        static void RotationX(Matrix4x4& mat, float radian);
        static void RotationY(Matrix4x4& mat, float radian);
        static void RotationZ(Matrix4x4& mat, float radian);
        static void RotationYawPitchRoll(Matrix4x4& mat, float yaw, float pitch, float roll);
        static void RotationYawPitchRoll(Matrix4x4& mat, const Float3& ypr);
        static void RotationYawPitchRoll(Matrix4x4& mat, const Float3* ypr);
        static void RotationAxis(Matrix4x4& mat, const Float3& axis, float radian);

        //転置行列
        static void Transpose(Matrix4x4& mat);

        //行列式を求める
        static float Determinant(Matrix4x4& mat);

        //掛け算処理
        static void Multiply(Matrix4x4& mat, const Matrix4x4& mat2);
        static void MultiplyTranspose(Matrix4x4& mat, const Matrix4x4& mat2);

        //透視投影
        static void OrthoLH(Matrix4x4& mat, float width, float height, float znear, float zfar);
        static void OrthoRH(Matrix4x4& mat, float width, float height, float znear, float zfar);
        static void OrthoOffCenterLH(Matrix4x4& mat, float left, float right, float low, float tall, float znear, float zfar);
        static void OrthoOffCenterRH(Matrix4x4& mat, float left, float right, float low, float tall, float znear, float zfar);
        static void PerspectiveLH(Matrix4x4& mat, float width, float height, float znear, float zfar);
        static void PerspectiveRH(Matrix4x4& mat, float width, float height, float znear, float zfar);
        static void PerspectiveFovLH(Matrix4x4& mat, float fovy, float Aspect, float znear, float zfar);
        static void PerspectiveFovRH(Matrix4x4& mat, float fovy, float Aspect, float znear, float zfar);
        static void PerspectiveOffCenterLH(Matrix4x4& mat, float left, float right, float low, float tall, float znear, float zfar);
        static void PerspectiveOffCenterRH(Matrix4x4& mat, float left, float right, float low, float tall, float znear, float zfar);
        static void LookAtLH(Matrix4x4& mat, const Float3& Eye, const Float3& At, const Float3& Up);
        static void LookAtRH(Matrix4x4& mat, const Float3& Eye, const Float3& At, const Float3& Up);
    };
}
#endif // !MATHMATRIX_H_

