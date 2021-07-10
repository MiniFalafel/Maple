#pragma once

#include "Maple/Core/Layer.h"

#include "Maple/Events/ApplicationEvent.h"
#include "Maple/Events/MouseEvent.h"
#include "Maple/Events/KeyEvent.h"

namespace Maple {
	
	class ImGuiLayer : public Layer {

	public:
		ImGuiLayer();
		~ImGuiLayer();
		
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:

		float m_Time = 0.0f;
	};

}