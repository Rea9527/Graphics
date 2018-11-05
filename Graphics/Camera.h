#pragma once

#include <GL_CORE/gl_core_4_3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


enum CameraMovement {
	CAM_FOWARD,
	CAM_BACKWARD,
	CAM_LEFT,
	CAM_RIGHT
};

enum CameraState {
	DISABLE,
	ACTIVE
};

class Camera {

public:

	Camera();
	Camera(glm::vec3 pos, glm::vec3 up, GLfloat yaw, GLfloat pitch);

	void init(glm::vec3 pos, glm::vec3 up, GLfloat yaw, GLfloat pitch);
	void use();
	// camera movement -> translate\rotate\zomm
	void translate(CameraMovement moveDir, GLfloat deltaTime);
	void rotate(GLfloat xoff, GLfloat yoff);
	void zoom(GLfloat yoff);

	void setSensitivity(GLfloat sensitivity);
	void setSpeed(GLfloat speed);
	void setTarget(glm::vec3 target);

	glm::vec3 getPos();
	glm::vec3 getFront();
	glm::vec3 getUp();

	GLfloat getZoom();

	glm::mat4 getViewMat();

	float getYaw();
	float getPitch();

	void disable();

private:
	void updateCameraPos();

	GLboolean STATE;

	GLfloat Speed;
	GLfloat Sensitivity;

	GLfloat Yaw;
	GLfloat Pitch;

	glm::vec3 Pos;
	GLfloat Zoom;

	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 InitUp;
};