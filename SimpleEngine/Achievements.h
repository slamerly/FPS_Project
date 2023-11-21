#pragma once
#include "Observer.h"
#include <iostream>

class Achievements :
    public Observer
{
public:
    virtual void onNotify(Event event)
    {
        switch (event)
        {
        case Event::AROUND_THE_WORLD:
            if (!unlockEventOne)
            {
                std::cout << "Success achieved: Around the World!" << std::endl;
                unlockEventOne = true;
            }
            break;
        case Event::FOLLOW_CHARA:
            if (!unlockEventTwo)
            {
                std::cout << "Success achieved: Follow the beautiful cube." << std::endl;
                unlockEventTwo = true;
            }
            break;
        case Event::IN_HEAD:
            if (!unlockEventThree)
            {
                std::cout << "Success achieved: In my head." << std::endl;
                unlockEventThree = true;
            }
            break;
        default:
            break;
        }
    }

private:
    bool unlockEventOne = false, unlockEventTwo = false, unlockEventThree = false;
};

