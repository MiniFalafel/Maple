#include "mppch.h"
#include "OrthographicCamera.h"

namespace Maple {
	// ------------------- //
	// Orthographic camera //
	// ------------------- //

	OrthographicCamera::OrthographicCamera(
		float left, float right, float bottom, float top)
		: m_Projection(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_View(1.0f) {
		// Update Camera vectors
		UpdateVectors();
		// Update view matrix
		UpdateViewMatrix();
	}
	OrthographicCamera::~OrthographicCamera() {

	}

	void OrthographicCamera::UpdateProjectionMatrix(float left, float right, float bottom, float top) {
		m_Projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_Projection * m_View;
	}

	void OrthographicCamera::UpdateViewMatrix() {
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));
		m_View = glm::inverse(transform);
		m_ViewProjectionMatrix = m_Projection * m_View;
	}

	void OrthographicCamera::UpdateVectors() {
		// Calculate the right and up vectors from sin and cos of m_Rotation
		// Right
		m_Right.x = glm::cos(glm::radians(m_Rotation));
		m_Right.y = glm::sin(glm::radians(m_Rotation));
		m_Right.z = 0.0f;
		// Up
		m_Up.x = glm::cos(glm::radians(m_Rotation + 90.0f));
		m_Up.y = glm::sin(glm::radians(m_Rotation + 90.0f));
		m_Up.z = 0.0f;
	}
}
