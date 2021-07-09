#pragma once

#include "Maple/Renderer/OrthographicCamera.h"
#include "Maple/Core/Timestep.h"

#include "Maple/Events/ApplicationEvent.h"
#include "Maple/Events/MouseEvent.h"

namespace Maple {
	
	class OrthographicCameraController {

	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

	private:

		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation;
		
		float m_CameraTranslationSpeed = 2.0f, m_CameraRotationSpeed = 90.0f;
	};

}