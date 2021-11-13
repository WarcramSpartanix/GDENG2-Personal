#pragma once
#include "AGameObject.h"
#include "InputListener.h"

class Camera :
    public AGameObject, public InputListener
{
public:
	Camera();
	Camera(float width, float height);
	~Camera();

	void update(float deltaTime) override;
	void draw(int width, int height) override;

	void updateViewMatrix();
	void setDimensions(float width, float height);
	Matrix4x4 getViewMatrix();
	Matrix4x4 getProjMatrix();
	
	void onKeyDown(int key) override;
	void onKeyUp(int key) override;
	void onMouseMove(const Point& delta_mouse_pos) override;
	void onLeftMouseDown(const Point& mouse_pos) override;
	void onLeftMouseUp(const Point& mouse_pos) override;
	void onRightMouseDown(const Point& mouse_pos) override;
	void onRightMouseUp(const Point& mouse_pos) override;

private:
	float m_forward = 0.0f;
	float m_rightward = 0.0f;
	bool m_camera_move_toggle = false;
	bool m_perspective_toggle = true;
	Matrix4x4 m_world_camera;

	float m_width;
	float m_height;

	float m_near_plane = 0.1f;
	
	float m_far_plane = 100.0f;
	float m_min_near_plane = 0.1f;
};

