#pragma once

enum class Event
{
    AROUND_THE_WORLD,
    FOLLOW_CHARA,
    IN_HEAD
};

class Observer
{
public:
	virtual ~Observer() {};
	virtual void onNotify(Event event) = 0;

};