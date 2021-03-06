#pragma once
#include "../Effekseer/Effekseer.h"
class MATRIX;
class VECTOR3;
//既存のライブラリをEFFEKSEERの型を変換する
namespace EFFEKSSER_CONNECT {
	using namespace ::Effekseer;
	Matrix44 cvtMatrix(const MATRIX& m);
	Vector3D cvtVector3D(const VECTOR3& vector3);
}