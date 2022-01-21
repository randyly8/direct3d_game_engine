#include "KeyboardEvent.h"

KeyboardEvent::KeyboardEvent()
	:
	type(EventType::Invalid),
	key(0u)
{
}

KeyboardEvent::KeyboardEvent(EventType type, const unsigned char key)
	: 
	type(type),
	key(key)
{
}

bool KeyboardEvent::IsPress() const
{
	return this->type == EventType::Press;
}

bool KeyboardEvent::IsRelease() const
{
	return this->type == EventType::Release;
}

bool KeyboardEvent::IsValid() const
{
	return this->type != EventType::Invalid;
}

unsigned char KeyboardEvent::GetKeyCode() const
{
	return key;
}
