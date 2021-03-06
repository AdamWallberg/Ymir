#pragma once

#include "Transform.h"
#include "Graphics/Color.h"

class Camera
{
public:
	enum Projection
	{
		PERSPECTIVE,
		ORTHOGRAPHIC
	};

	Camera(
		float fov = 75.0f, 
		float aspect = 16.0f / 9.0f, 
		float near = 0.1f, 
		float far = 1000.0f);

	~Camera();

	// Call this after modifying camera position and/or rotation
	void update();
	// Call this after modifying camera fov, aspect, near- or far plane.
	void updateProjection();

	// Transformation
	Transform* transform_;
	pm::mat4 view_matrix_;
	pm::vec3 position_;
	pm::vec3 rotation_;


	// Projection
	Projection projection_type_;
	pm::mat4 projection_matrix_;
	float fov_;
	float aspect_;
	float near_;
	float far_;
	float left_;
	float right_;
	float top_;
	float bottom_;

	// Clearing
	Color clear_color_;
	uint clear_flags_;
};

#include "ServiceLocator.h"
SERVICE_LOCATOR_HEADER(Camera, MainCam)