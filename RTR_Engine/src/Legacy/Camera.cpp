#include "rtrpch.h"
#include "Camera.h"

using namespace RTREngine;

Camera::Camera(float fov, float aspect, float near, float far, std::shared_ptr<InputLegacy> input)
	:_input(input)
{
	// Creates a new projection matrix
	//_projMatrix = glm::perspective(
	//	glm::radians(fov),
	//	aspect,
	//	near,
	//	far
	//);


	// For debugging only
	_projMatrix = glm::mat4(1.0f);

	// Initial values
	_position = glm::vec3(0.0f, 0.0f, 0.0f);
	_pitch = 0.0f;
	_yaw = 0.0f;
}

glm::vec3 Camera::getPosition()
{
	return this->_position;
};


glm::mat4 Camera::getViewMatrix()
{
	return this->_viewMatrix;
}


glm::mat4 Camera::getProjMatrix()
{
	return this->_projMatrix;
}


void Camera::processMouseMovement(int x, int y)
{
	// Calculate yaw by adding relative change of mouseX
	_yaw += (_mouseX - x);

	// Keep yaw in range between 0-360
	_yaw = fmodf(_yaw, 360.0f);
	_yaw = _yaw < 0.0f ? _yaw + 360.0f : _yaw;

	// Calculate pitch by adding relative change of mouseY
	_pitch += (_mouseY - y);

	// Clamp pitch to prevent camera inversion
	_pitch = Utils::clamp(_pitch, -90.0f, 90.0f);
}


void Camera::setUniforms(std::shared_ptr<ShaderLegacy> shader)
{
	shader->use();
	shader->setUniform("viewProjMatrix", this->_projMatrix * this->_viewMatrix);
	shader->setUniform("camera_world", this->_position);
	shader->unuse();
}

void Camera::update(float deltaTime)
{
	int x = _input->mouse_x;
	int y = _input->mouse_y;
	float zoom = _input->_zoom; 
	bool dragging = _input->_dragging;
	float height = _input->_height;


	// Update _yaw and _pitch if dragging is activated
	if (dragging)
	{
		processMouseMovement(x,y);
	}

	/* Viewmatrix transformations */

	// Reset _viewMatrix for calculating absolute values 
	_viewMatrix = glm::mat4(1.0f);

	// Apply _yaw (yAxis) and _pitch (xAxis) values to _viewMatrix 
	_viewMatrix = glm::rotate(_viewMatrix, glm::radians(_yaw), glm::vec3(0.0, 1.0, 0.0));
	_viewMatrix = glm::rotate(_viewMatrix, glm::radians(_pitch), glm::vec3(1.0, 0.0, 0.0));

	// Set distance based on zoom 
	_viewMatrix = glm::translate(_viewMatrix, glm::vec3(0, height, zoom)); // (y axis for debugging purposes!)

	// Receive camera position by getting translation vector (first 3 elements of the last column)
	_position = glm::vec3(_viewMatrix[3]);

	// Invert direction in order to view at origin
	_viewMatrix = inverse(_viewMatrix);

	// Updates current mouse positions
	_mouseX = x;
	_mouseY = y;
};

Camera::~Camera()
{
}
