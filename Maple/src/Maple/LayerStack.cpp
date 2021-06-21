#include "mppch.h"
#include "LayerStack.h"

namespace Maple {
	// Layer stack constructor
	LayerStack::LayerStack() {
		// Set the insertion point for the layers (divisor between overlays and layers)
		m_LayerInsert = m_Layers.begin();
	}
	// Destructor
	LayerStack::~LayerStack() {
		for (Layer* layer : m_Layers)
			delete layer;
	}
	// Push Layer
	void LayerStack::PushLayer(Layer* layer) {
		m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
	}
	// Push Overlay
	void LayerStack::PushOverlay(Layer* overlay) {
		m_Layers.emplace_back(overlay);
	}
	// Pop Layer
	void LayerStack::PopLayer(Layer* layer) {
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end()) {
			m_Layers.erase(it);
			m_LayerInsert--;
		}
	}
	// Pop Overlay
	void LayerStack::PopOverlay(Layer* overlay) {
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end()) {
			m_Layers.erase(it);
		}
	}
}