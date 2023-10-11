#pragma once

#include <string>
#include <Engine/Graphics/3d/CubeMesh.h>

class IEvent 
{
public:
	virtual std::string GetName() = 0;
};


class NewRenderEvent : public IEvent
{
public:
	inline static const std::string EventName = "NewRenderEvent";
	CubeMesh* m_value;

	NewRenderEvent(CubeMesh* value) {
		m_value = value;
	}

	CubeMesh* GetData() {
		return m_value;
	}

	std::string GetName() {
		return EventName;
	}
};