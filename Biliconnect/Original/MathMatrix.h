/*=========================================================================
    Date : 2022/01/31(��)	MathMatrix.h
        Author : ���ނ��邧
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
        //�P�ʍs��̕ϊ�
        static void Identity(Matrix4x4& mat);

        //�t�s��̕ϊ�
        static void Inverse(Matrix4x4& mat);

        //�X�P�[�����O�̕ϊ�
        static void Scaling(Matrix4x4& mat, float sx, float sy, float sz);
        static void Scaling(Matrix4x4& mat, const Float3& scale);
        static void Scaling(Matrix4x4& mat, const Float3* scale);

        //���s�ړ��̕ϊ�
        static void Translation(Matrix4x4& mat, float sx, float sy, float sz);
        static void Translation(Matrix4x4& mat, const Float3& scale);
        static void Translation(Matrix4x4& mat, const Float3* scale);

        //��]�ړ��̕ϊ�
        static void RotationX(Matrix4x4& mat, float radian);
        static void RotationY(Matrix4x4& mat, float radian);
        static void RotationZ(Matrix4x4& mat, float radian);
        static void RotationYawPitchRoll(Matrix4x4& mat, float yaw, float pitch, float roll);
        static void RotationYawPitchRoll(Matrix4x4& mat, const Float3& ypr);
        static void RotationYawPitchRoll(Matrix4x4& mat, const Float3* ypr);
        static void RotationAxis(Matrix4x4& mat, const Float3& axis, float radian);

        //�]�u�s��
        static void Transpose(Matrix4x4& mat);

        //�s�񎮂����߂�
        static float Determinant(Matrix4x4& mat);

        //�|���Z����
        static void Multiply(Matrix4x4& mat, const Matrix4x4& mat2);
        static void MultiplyTranspose(Matrix4x4& mat, const Matrix4x4& mat2);

        //�������e
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

