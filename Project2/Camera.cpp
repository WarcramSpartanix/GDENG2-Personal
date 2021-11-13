#include "Camera.h"
#include "EngineTime.h"
#include "InputSystem.h"

Camera::Camera() : AGameObject("camera"), m_width(0), m_height(0)
{
	setPosition(0, 0, -2);
	updateViewMatrix();
}

Camera::Camera(float width, float height) : AGameObject("Camera"), m_width(0), m_height(0)
{
	setPosition(0, 0, -2);
	updateViewMatrix();
}

Camera::~Camera()
{
}

void Camera::update(float deltaTime)
{
	Matrix4x4 temp(m_world_camera);
	temp.inverse();

	Vector3D new_pos = temp.getZDirection() * (m_forward * 0.1f);
	new_pos += temp.getXDirection() * (m_rightward * 0.1f);

	translate(new_pos);

	updateViewMatrix();
}

void Camera::draw(int width, int height)
{
}

void Camera::updateViewMatrix()
{
	Matrix4x4 temp;
	Matrix4x4 world_cam;
	world_cam.setIdentity();

	temp.setIdentity();
	temp.setRotationX(getLocalRotation().m_x);
	world_cam *= temp;

	temp.setIdentity();
	temp.setRotationY(getLocalRotation().m_y);
	world_cam *= temp;

	temp.setIdentity();
	temp.setTranslation(this->getLocalPosition());
	world_cam *= temp;

	world_cam.inverse();

	m_world_camera.setMatrix(world_cam);
}

void Camera::setDimensions(float width, float height)
{
	m_width = width;
	m_height = height;
}

Matrix4x4 Camera::getViewMatrix()
{
	return m_world_camera;
}

Matrix4x4 Camera::getProjMatrix()
{
	Matrix4x4 returnMatrix;
	if (m_perspective_toggle)
	{
		returnMatrix.setPerspectiveFovLH(1.57 - (m_near_plane * 0.5), ((float)m_width / ((float)m_height)), m_near_plane, 100.0f);
		return returnMatrix;
	}
	else
	{
		returnMatrix.setOrthoLH
			(
				m_width / 300.0f,
				m_height / 300.0f,
				0.1f,
				100.0f
			);
		return returnMatrix;
	}
}

void Camera::onKeyDown(int key)
{
	float offset = EngineTime::getDeltaTime() * 1.5f;
	if (key == 'W')
	{
		m_forward = 1.0f;
		//translate(0, 0, offset);
	}
	else if (key == 'S')
	{
		m_forward = -1.0f;
		//translate(0, 0,-offset);
	}
	else if (key == 'A')
	{
		m_rightward = -1.0f;
		//translate(-offset, 0, 0);
	}
	else if (key == 'D')
	{
		m_rightward = 1.0f;
		//translate(offset, 0, 0);
	}
	else if (key == 'Q')
	{
	}
	else if(key == 'E')
	{
	}
	else if (key == 'Z')
	{
		offset = EngineTime::getDeltaTime() * 1.0f;
		if (m_near_plane + offset <= m_far_plane)
		{
			m_near_plane += offset;
		}
	}
	else if (key == 'X')
	{
		offset = EngineTime::getDeltaTime() * 1.0f;
		if (m_near_plane - offset >= m_min_near_plane)
		{
			m_near_plane -= offset;
		}
	}
	
	
	/*float offset = EngineTime::getDeltaTime() * 1.5f;
	if (key == 'W')
	{
		translate(m_world_camera.getZDirection() * (offset));
	}
	else if (key == 'S')
	{
		translate(m_world_camera.getZDirection() * (-offset));
	}
	else if (key == 'A')
	{
		translate(m_world_camera.getXDirection() * (-offset));
		
	}
	else if (key == 'D')
	{
		translate(m_world_camera.getXDirection() * (offset));
	}
	*/
}

void Camera::onKeyUp(int key)
{
	if (key == 'T')
	{
		m_perspective_toggle = !m_perspective_toggle;
	}

	m_forward = 0.0f;
	m_rightward = 0.0f;
}

void Camera::onMouseMove(const Point& delta_mouse_pos)
{
	if(m_camera_move_toggle)
	{
		Vector3D rotation;
		rotation.m_x += delta_mouse_pos.m_y * EngineTime::getDeltaTime() * 0.2f;
		rotation.m_y += delta_mouse_pos.m_x * EngineTime::getDeltaTime() * 0.2f;

		rotate(rotation);
	}
}

void Camera::onLeftMouseDown(const Point& mouse_pos)
{

	std::cout << "left click" << std::endl;
}

void Camera::onLeftMouseUp(const Point& mouse_pos)
{
}

void Camera::onRightMouseDown(const Point& mouse_pos)
{
	m_camera_move_toggle = true;
}

void Camera::onRightMouseUp(const Point& mouse_pos)
{
	m_camera_move_toggle = false;
}
