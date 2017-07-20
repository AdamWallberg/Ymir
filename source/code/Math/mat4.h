#pragma once

#include "vec3.h"

namespace pm
{

class mat4
{
public:

	enum EMultiplyOrder
	{
		COMBINE_REPLACE,
		COMBINE_PRE_MULTIPLY,
		COMBINE_POST_MULTIPLY
	};

	// Sets all values to 0 as default
	mat4();
	mat4(const mat4& other);

	// Defaults all values to 0, except the diagonal.
	// ie. pmMat4( 1.0f ) creates an identity matrix.
	// ASCII ART TIME!
	// [1 0 0 0]
	// [0 1 0 0]
	// [0 0 1 0]
	// [0 0 0 1]
	mat4(const float diagonal);

	~mat4();

	union
	{
		// Single elements of the matrix
		float elements[16];

		// Matrix represented as directional vectors and translation
		struct
		{
			// Instead of using padding floats, we align the vectors with 16 bytes
			_declspec(align(16)) vec3 left;
			_declspec(align(16)) vec3 up;
			_declspec(align(16)) vec3 forward;
			_declspec(align(16)) vec3 translation;
		};
	};

	void translate(const vec3& translation, EMultiplyOrder Order = COMBINE_POST_MULTIPLY);
	void rotateZYX(const vec3& axis, EMultiplyOrder Order = COMBINE_POST_MULTIPLY); // Recommended for camera rotation
	void rotateXYZ(const vec3& axis, EMultiplyOrder Order = COMBINE_POST_MULTIPLY);
	void scale(const vec3& scale, EMultiplyOrder Order = COMBINE_POST_MULTIPLY);
	void transpose();

	// Orthogonalizes this matrix, then normalizes it. 
	void orthonormalize();

	// Orthogonalizes this matrix using the following priority order:
	// forward-up-left
	void orthogonalize();

	mat4 getViewMatrix() const;

	static mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
	static mat4 perspective(float fov, float aspectRatio, float near, float far);

	mat4 operator * (const mat4& other);
	float& operator [] (unsigned char id);

	void* operator new(size_t i)
	{
		return _mm_malloc(i, 16);
	}

	void operator delete(void* p)
	{
		_mm_free(p);
	}

};

}
