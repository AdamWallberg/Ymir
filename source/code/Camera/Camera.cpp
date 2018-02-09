#include "Camera.h"
#include "Graphics/Window.h"
#include "Core.h"
#include "Graphics/GL.h"
#include "Logger.h"

Camera::Camera(
	float fov /*= 75.0f*/,
	float aspect /*= 16.0f / 9.0f*/,
	float near /*= 0.1f*/,
	float far /*= 1000.0f*/)
	: fov_(fov)
	, aspect_(aspect)
	, near_(near)
	, far_(far)
	, clear_color_(Color::light_gray)
	, clear_flags_(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
{
	transform_ = newp Transform;
	updateProjection();
	update();
}

Camera::~Camera()
{
	delete transform_;
}

void Camera::updateProjection()
{
	projection_ = pm::mat4::perspective(
		fov_,
		aspect_,
		near_,
		far_);
}

void Camera::update()
{
	// Apply rotation
	transform_->local_matrix_.rotateZYX(rotation_.toRadians(), pm::mat4::COMBINE_REPLACE);

	// Apply position
	transform_->local_matrix_.translate(position_);

	transform_->update();

	// Update view matrix
	view_ = transform_->local_matrix_.getViewMatrix();
}

SERVICE_LOCATOR_SOURCE(Camera, MainCam)