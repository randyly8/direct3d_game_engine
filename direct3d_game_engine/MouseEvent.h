#pragma once
struct Mousepoint
{
	int x;
	int y;
};

class MouseEvent
{
public:
	enum class EventType
	{
		LPress,
		LRelease,
		RPress,
		RRelease,
		MPress,
		MRelease,
		WheelUp,
		WheelDown,
		Move,
		RAW_MOVE,
		Invalid
	};
public:
	MouseEvent();
	MouseEvent(const EventType type, int x, int y);
	bool IsValid() const;
	EventType GetType() const;
	Mousepoint GetPos() const;
	int GetPosX() const;
	int GetPosY() const;
private:
	EventType type;
	int x; 
	int y;
};

