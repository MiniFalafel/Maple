#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Maple {

	class OrthographicCamera {

	public:
		OrthographicCamera(float left, float right, float bottom, float top);
		~OrthographicCamera();

		void UpdateProjectionMatrix(float left, float right, float bottom, float top);
		void UpdateViewMatrix();

		inline const glm::mat4& GetProjectionMatrix() { return m_Projection; }
		inline const glm::mat4& GetViewMatrix() { return m_View; }
		inline const glm::mat4& GetViewProjectionMatrix() { return m_ViewProjectionMatrix; }

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; UpdateViewMatrix(); }
		void AddToPosition(const glm::vec3& offset) { m_Position += offset; UpdateViewMatrix(); }

		const float& GetRotation() const { return m_Rotation; }
		void SetRotation(const float& rotation) { m_Rotation = rotation; UpdateVectors(); UpdateViewMatrix(); }
		void AddToRotation(const float& offset) { m_Rotation += offset; UpdateVectors(); UpdateViewMatrix(); }

		const glm::vec3& GetRightVector() const { return m_Right; }
		const glm::vec3& GetUpVector() const { return m_Up; }

		void UpdateVectors();

	private:
		// Pos and rot
		glm::vec3 m_Position = glm::vec3(0.0f);
		float m_Rotation = 0.0f;

		// Direction vectors
		glm::vec3 m_Right;
		glm::vec3 m_Up;

		// ViewProjection Matrix
		glm::mat4 m_View, m_Projection;
		glm::mat4 m_ViewProjectionMatrix;
	};

}