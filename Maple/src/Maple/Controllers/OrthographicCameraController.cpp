#include "mppch.h"
#include "OrthographicCameraController.h"

#include "Maple/Core/Input.h"
#include "Maple/Core/KeyCodes.h"

namespace Maple {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio),
		m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),
		m_Rotation(rotation) {
		
	}

	void OrthographicCameraController::OnUpdate(Timestep ts) {
		if (Input::IsKeyPressed(MP_KEY_A))
			m_Camera.AddToPosition(-m_CameraTranslationSpeed * ts * m_Camera.GetRightVector());
		if (Input::IsKeyPressed(MP_KEY_D))
			m_Camera.AddToPosition(m_CameraTranslationSpeed * ts * m_Camera.GetRightVector());
		if (Input::IsKeyPressed(MP_KEY_W))
			m_Camera.AddToPosition(m_CameraTranslationSpeed * ts * m_Camera.GetUpVector());
		if (Input::IsKeyPressed(MP_KEY_S))
			m_Camera.AddToPosition(-m_CameraTranslationSpeed * ts * m_Camera.GetUpVector());

		if (m_Rotation) {
			if (Input::IsKeyPressed(MP_KEY_Q))
				m_Camera.AddToRotation(ts * m_CameraRotationSpeed);
			if (Input::IsKeyPressed(MP_KEY_E))
				m_Camera.AddToRotation(-ts * m_CameraRotationSpeed);
		}

		m_CameraTranslationSpeed = m_ZoomLevel * 1.5f;
	}

	void OrthographicCameraController::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(MP_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(MP_BIND_EVENT_FN(OrthographicCameraController::OnWindowResize));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e) {
		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.UpdateProjectionMatrix(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& e) {
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.UpdateProjectionMatrix(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

}
