/*=========================================================================
    Date : 2022/01/31(åé)	MathMatrix.cpp
        Author : Ç™ÇﬁÇµÇÈÇß
        Update :
=========================================================================*/
#include <math.h>

#include "MathFloat.h"
#include "MathMatrix.h"
using namespace math;

/*=============================================================================================
    íPà çsóÒÇÃê∂ê¨
=============================================================================================*/
void MathMatrix::Identity(Matrix4x4& mat)
{
    mat.m11 = 1.0f;
    mat.m22 = 1.0f;
    mat.m33 = 1.0f;
    mat.m44 = 1.0f;
}

/*=============================================================================================
    ãtçsóÒÇÃê∂ê¨
=============================================================================================*/
void MathMatrix::Inverse(Matrix4x4& mat)
{
    Matrix4x4 matrix = mat;
    Matrix4x4 inverse;
	MathMatrix::Identity(inverse);

    float temp = 0.0f;

    //ë|Ç´èoÇµñ@
    for (int i = 0; i < 4; i++)
    {
        //É[ÉçèúéZÇÃâÒî
        if (matrix.mat[i][i] != 0.0f)
            temp = 1.0f / matrix.mat[i][i];
        else
            temp = 0.0f;

        for (int j = 0; j < 4; j++)
        {
            matrix.mat[i][j]    *= temp;
            inverse.mat[i][j]   *= temp;
        }

        for (int j = 0; j < 4; j++)
        {
            if (i != j)
            {
                temp = matrix.mat[j][i];

                for (int k = 0; k < 4; k++)
                {
                    matrix.mat[j][k] -= matrix.mat[i][k] * temp;
                    inverse.mat[j][k] -= inverse.mat[i][k] * temp;
                }
            }
        }
    }

    mat = inverse;
}

/*=============================================================================================
    ÉXÉPÅ[ÉäÉìÉO
=============================================================================================*/
void MathMatrix::Scaling(Matrix4x4& mat, float sx, float sy, float sz)
{
    mat.m11 = sx;
    mat.m22 = sy;
    mat.m33 = sz;
}
void MathMatrix::Scaling(Matrix4x4& mat, const Float3& scale)
{
    MathMatrix::Scaling(mat, scale.x, scale.y, scale.z);
}
void MathMatrix::Scaling(Matrix4x4& mat, const Float3* scale)
{
    MathMatrix::Scaling(mat, scale->x, scale->y, scale->z);
}

/*=============================================================================================
    ÉgÉâÉìÉXÉåÅ[ÉVÉáÉì(ïΩçsà⁄ìÆ)
=============================================================================================*/
void math::MathMatrix::Translation(Matrix4x4& mat, float sx, float sy, float sz)
{
    mat.m41 = sx;
    mat.m42 = sy;
    mat.m43 = sz;
}
void math::MathMatrix::Translation(Matrix4x4& mat, const Float3& scale)
{
    MathMatrix::Translation(mat, scale.x, scale.y, scale.z);
}
void math::MathMatrix::Translation(Matrix4x4& mat, const Float3* scale)
{
    MathMatrix::Translation(mat, scale->x, scale->y, scale->z);
}

/*====================================================================
	RotationX(Xé≤âÒì])
====================================================================*/
void MathMatrix::RotationX(Matrix4x4& mat, float radian)
{
	float s = sinf(radian);
	float c = cosf(radian);

	mat.m22 =  c;
	mat.m23 =  s;
	mat.m32 = -s;
	mat.m33 =  c;
}

/*====================================================================
	RotationY(Yé≤âÒì])
====================================================================*/
void MathMatrix::RotationY(Matrix4x4& mat, float radian)
{
	float s = sinf(radian);
	float c = cosf(radian);

	mat.m11 = c;
	mat.m13 = -s;
	mat.m31 = s;
	mat.m33 = c;
}

/*====================================================================
	RotationZ(Zé≤âÒì])
====================================================================*/
void MathMatrix::RotationZ(Matrix4x4& mat, float radian)
{
	float s = sinf(radian);
	float c = cosf(radian);

	mat.m11 =  c;
	mat.m12 =  s;
	mat.m21 = -s;
	mat.m22 =  c;
}

/*====================================================================
	RotationYawPitchRoll(ZYXÇÃèáÇ…âÒì])

	@Link : https://www.buildinsider.net/small/bookkinectv2/0804
====================================================================*/
void MathMatrix::RotationYawPitchRoll(Matrix4x4& mat, float yaw, float pitch, float roll)
{
	float cz = cosf(yaw);
	float cb = cosf(pitch);
	float ca = cosf(roll);

	float sz = sinf(yaw);
	float sb = sinf(pitch);
	float sa = sinf(roll);

	mat.m11 = sz * sb * sa + cz * ca;
	mat.m12 = cb * sa;
	mat.m13 = -sz * ca + cz * sb * sa;

	mat.m21 = sz * sb * ca - cz * sa;
	mat.m22 = cb * ca;
	mat.m23 = sz * sa + cz * sb * ca;

	mat.m31 = sz * cb;
	mat.m32 = -sb;
	mat.m33 = cz * cb;
}
void MathMatrix::RotationYawPitchRoll(Matrix4x4& mat, const Float3& rot)
{
	MathMatrix::RotationYawPitchRoll(mat, rot.x, rot.y, rot.z);
}
void MathMatrix::RotationYawPitchRoll(Matrix4x4& mat, const Float3* rot)
{
	MathMatrix::RotationYawPitchRoll(mat, rot->x, rot->y, rot->z);
}

/*====================================================================
	RotationAxis(ZYXÇÃèáÇ…âÒì])

	@Link : https://github.com/lriki/Lumino.Math/blob/master/src/Math/Matrix.cpp
====================================================================*/
void MathMatrix::RotationAxis(Matrix4x4& mat, const Float3& axis, float radian)
{
	Matrix4x4 mtxAxis;
	Matrix4x4 mtxThis = mat;

	MathMatrix::Identity(mtxAxis);
	Float3 Axis = MathFloat::Normalize(axis);

	float s = sinf(radian);
	float c = cosf(radian);

	float mc = 1.0f - c;

	mat.m11 = (Axis.x * Axis.x) * mc + c;
	mat.m12 = (Axis.x * Axis.y) * mc + (Axis.z * s);
	mat.m13 = (Axis.x * Axis.z) * mc - (Axis.y * s);

	mat.m21 = (Axis.x * Axis.y) * mc - (Axis.z * s);
	mat.m22 = (Axis.y * Axis.y) * mc + c;
	mat.m23 = (Axis.y * Axis.z) * mc + (Axis.x * s);

	mat.m31 = (Axis.x * Axis.z) * mc + (Axis.y * s);
	mat.m32 = (Axis.y * Axis.z) * mc - (Axis.x * s);
	mat.m33 = (Axis.z * Axis.z) * mc + c;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mat.mat[i][j] = mtxThis.mat[i][0] * mtxAxis.mat[0][j]
				+ mtxThis.mat[i][1] * mtxAxis.mat[1][j]
				+ mtxThis.mat[i][2] * mtxAxis.mat[2][j]
				+ mtxThis.mat[i][3] * mtxAxis.mat[3][j];
		}
	}
}

/*====================================================================
	Transpose(ì]ínçsóÒÇÃê∂ê¨)
====================================================================*/
void MathMatrix::Transpose(Matrix4x4& mat)
{
	Matrix4x4 a = mat;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			mat.mat[y][x] = a.mat[x][y];
		}
	}
}

/*====================================================================
	Determinant(çsóÒéÆÇÃåvéZ)

	@Link : https://thira.plavox.info/blog/2008/06/_c.html
====================================================================*/
float MathMatrix::Determinant(Matrix4x4& mat)
{
	Matrix4x4 matrix = mat;
	float determinant = 1.0f;

	//éOäpçsóÒÇçÏê¨
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i < j)
			{
				//É[ÉçèúéZÇâÒîÇ∑ÇÈ
				if (mat.mat[i][i] != 0.0f)
				{
					float temp = matrix.mat[j][i] / matrix.mat[i][i];

					for (int k = 0; k < 4; k++)
					{
						matrix.mat[j][k] -= matrix.mat[i][k] * temp;
					}
				}
			}
		}
	}

	//ëŒäpïîï™ÇÃêœ
	for (int i = 0; i < 4; i++)
	{
		determinant *= matrix.mat[i][i];
	}

	return determinant;
}

/*====================================================================
	ä|ÇØéZèàóù
====================================================================*/
void MathMatrix::Multiply(Matrix4x4& mat1, const Matrix4x4& mat2)
{
	Matrix4x4 b = mat1;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mat1.mat[i][j] = b.mat[i][0] * mat2.mat[0][j]
				+ b.mat[i][1] * mat2.mat[1][j]
				+ b.mat[i][2] * mat2.mat[2][j]
				+ b.mat[i][3] * mat2.mat[3][j];
		}
	}
}

/*====================================================================
	ä|ÇØéZèàóùÇ©Ç¬ì]ínçsóÒ
====================================================================*/
void MathMatrix::MultiplyTranspose(Matrix4x4& mat1, const Matrix4x4& mat2)
{
	MathMatrix::Multiply(mat1, mat2);
	MathMatrix::Transpose(mat1);
}

/*====================================================================
	ç∂éËånÇÃê≥ìäâeçsóÒ
====================================================================*/
void MathMatrix::OrthoLH(Matrix4x4& mat, float width, float height, float znear, float zfar)
{
	mat.m11 = 2.0f / width;
	mat.m22 = 2.0f / height;
	mat.m33 = 1.0f / (zfar - znear);
	mat.m43 = -znear / (zfar - znear);
}

/*====================================================================
	âEéËånÇÃê≥ìäâeçsóÒ
====================================================================*/
void MathMatrix::OrthoRH(Matrix4x4& mat, float width, float height, float znear, float zfar)
{
	mat.m11 = 2.0f / width;
	mat.m22 = 2.0f / height;
	mat.m33 = 1.0f / (zfar - znear);
	mat.m43 = znear / (zfar - znear);
}

/*====================================================================
	ç∂éËånÇÃê≥ìäâeçsóÒ
====================================================================*/
void MathMatrix::OrthoOffCenterLH(Matrix4x4& mat, float left, float right, float low, float tall, float znear, float zfar)
{
	mat.m11 = 2.0f / (right - left);
	mat.m22 = 2.0f / (tall - low);
	mat.m33 = 1.0f / (zfar - znear);
	mat.m41 = (left + right) / (left - right);
	mat.m42 = (tall + low) / (low - tall);
	mat.m43 = znear / (znear - zfar);
}

/*====================================================================
	âEéËånÇÃê≥ìäâeçsóÒ
====================================================================*/
void MathMatrix::OrthoOffCenterRH(Matrix4x4& mat, float left, float right, float low, float tall, float znear, float zfar)
{
	mat.m11 = 2.0f / (right - left);
	mat.m22 = 2.0f / (tall - low);
	mat.m33 = 1.0f / (znear - zfar);
	mat.m41 = (left + right) / (left - right);
	mat.m42 = (tall + low) / (low - tall);
	mat.m43 = znear / (znear - zfar);
}

/*====================================================================
	ç∂éËånÇÃÉpÅ[ÉXÉyÉNÉeÉBÉuìäâeçsóÒ
====================================================================*/
void MathMatrix::PerspectiveLH(Matrix4x4& mat, float width, float height, float znear, float zfar)
{
	mat.m11 = 2.0f * znear / width;
	mat.m22 = 2.0f * znear / height;
	mat.m33 = zfar / (zfar - znear);
	mat.m34 = 1.0f;
	mat.m43 = znear * zfar / (znear - zfar);
	mat.m44 = 0.0f;

}

/*====================================================================
	âEéËånÇÃÉpÅ[ÉXÉyÉNÉeÉBÉuìäâeçsóÒ
====================================================================*/
void MathMatrix::PerspectiveRH(Matrix4x4& mat, float width, float height, float znear, float zfar)
{
	mat.m11 = 2.0f * znear / width;
	mat.m22 = 2.0f * znear / height;
	mat.m33 = zfar / (zfar - znear);
	mat.m34 = -1.0f;
	mat.m43 = znear * zfar / (znear - zfar);
	mat.m44 = 0.0f;
}

/*====================================================================
	ç∂éËånÇÃâìãﬂìäâeçsóÒ
====================================================================*/
void MathMatrix::PerspectiveFovLH(Matrix4x4& mat, float fovy, float Aspect, float znear, float zfar)
{
	float yscale = 1.0f / tanf(fovy / 2.0f);
	float xscale = yscale / Aspect;

	mat.m11 = xscale;
	mat.m22 = yscale;
	mat.m33 = zfar / (zfar - znear);
	mat.m34 = 1.0f;
	mat.m43 = -znear * zfar / (zfar - znear);
	mat.m44 = 0.0f;
}

/*====================================================================
	ç∂éËånÇÃâìãﬂìäâeçsóÒ
====================================================================*/
void MathMatrix::PerspectiveOffCenterLH(Matrix4x4& mat, float left, float right, float low, float tall, float znear, float zfar)
{
	mat.m11 = 2.0f * zfar / (right - left);
	mat.m22 = 2.0f * znear / (tall - low);
	mat.m31 = (left + right) / (left - right);
	mat.m32 = (tall + low) / (low - tall);
	mat.m33 = zfar / (zfar - znear);
	mat.m34 = 1.0f;
	mat.m43 = znear * zfar / (znear - zfar);
	mat.m44 = 0.0f;
}

/*====================================================================
	âEéËånÇÃâìãﬂìäâeçsóÒ
====================================================================*/
void MathMatrix::PerspectiveFovRH(Matrix4x4& mat, float fovy, float Aspect, float znear, float zfar)
{
	float yscale = 1.0f / tanf(fovy / 2.0f);
	float xscale = yscale / Aspect;

	mat.m11 = xscale;
	mat.m22 = yscale;
	mat.m33 = zfar / (zfar - znear);
	mat.m34 = -1.0f;
	mat.m43 = znear * zfar / (zfar - znear);
	mat.m44 = 0.0f;
}

/*====================================================================
	âEéËånÇÃâìãﬂìäâeçsóÒ
====================================================================*/
void MathMatrix::PerspectiveOffCenterRH(Matrix4x4& mat, float left, float right, float low, float tall, float znear, float zfar)
{
	mat.m11 = 2.0f * zfar / (right - left);
	mat.m22 = 2.0f * znear / (tall - low);
	mat.m31 = (left + right) / (left - right);
	mat.m32 = (tall + low) / (low - tall);
	mat.m33 = zfar / (zfar - znear);
	mat.m34 = -1.0f;
	mat.m43 = znear * zfar / (znear - zfar);
	mat.m44 = 0.0f;
}

/*====================================================================
	ç∂éËånÇÃäOäœçsóÒ
====================================================================*/
void MathMatrix::LookAtLH(Matrix4x4& mat, const Float3& Eye, const Float3& At, const Float3& Up)
{
	Float3 zAxis, yAxis, xAxis;

	zAxis = At;
	zAxis = zAxis - Eye;
	zAxis = MathFloat::Normalize(zAxis);

	xAxis = Up;
	xAxis = MathFloat::Cross(xAxis, zAxis);
	xAxis = MathFloat::Normalize(xAxis);

	yAxis = zAxis;
	yAxis = MathFloat::Cross(yAxis, xAxis);

	mat.m11 = xAxis.x;		 mat.m12 = yAxis.x;		 mat.m13 = zAxis.x;
	mat.m21 = xAxis.y;		 mat.m22 = yAxis.y;		 mat.m23 = zAxis.y;
	mat.m31 = xAxis.z;		 mat.m32 = yAxis.z;		 mat.m33 = zAxis.z;
	mat.m41 = -MathFloat::Dot(xAxis, Eye);
	mat.m42 = -MathFloat::Dot(yAxis, Eye);
	mat.m43 = -MathFloat::Dot(zAxis, Eye);
}

/*====================================================================
	âEéËånÇÃäOäœçsóÒ
====================================================================*/
void MathMatrix::LookAtRH(Matrix4x4& mat, const Float3& Eye, const Float3& At, const Float3& Up)
{
	Float3 zAxis, yAxis, xAxis;

	zAxis = Eye;
	zAxis = zAxis - At;
	zAxis = MathFloat::Normalize(zAxis);

	xAxis = Up;
	xAxis = MathFloat::Cross(xAxis, zAxis);
	xAxis = MathFloat::Normalize(xAxis);

	yAxis = zAxis;
	yAxis = MathFloat::Cross(yAxis, xAxis);

	mat.m11 = xAxis.x;		 mat.m12 = yAxis.x;		  mat.m13 = zAxis.x;
	mat.m21 = xAxis.y;		 mat.m22 = yAxis.y;		  mat.m23 = zAxis.y;
	mat.m31 = xAxis.z;		 mat.m32 = yAxis.z;		  mat.m33 = zAxis.z;
	mat.m41 = -MathFloat::Dot(xAxis, Eye);
	mat.m42 = -MathFloat::Dot(yAxis, Eye);
	mat.m43 = -MathFloat::Dot(zAxis, Eye);
}