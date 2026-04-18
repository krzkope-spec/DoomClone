//
// Created by krzko on 18/04/2026.
//

#ifndef DOOMCLONE_EVENTMANAGER_H
#define DOOMCLONE_EVENTMANAGER_H
#include<functional>


class EventManager {
private:
    std::vector<std::function<void(int,int)>> mouseMoveListeners_;
    std::vector<std::function<void(int)>> mouseClickListeners_;
    std::vector<std::function<void(int)>> keyboardDownListeners_;
    std::vector<std::function<void(int)>> keyboardListeners_;
    std::vector<std::function<void(int)>> keyboardUpListeners_;
public:
    void MouseClick(int button) const;
    void MouseMove(int deltaX, int deltaY) const;
    void KeyboardDown(int keyCode) const;
    void KeyboardUp(int keyCode) const;
    void Keyboard(int keyCode) const;
    enum EVENT_TYPE {
        MOUSE_MOVE, MOUSE_CLICK, KEYBOARD_DOWN, KEYBOARD, KEYBOARD_UP
    };
    void AddEventListener(EVENT_TYPE event, std::function<void(int,int)> listener);
    void AddEventListener(EVENT_TYPE event, std::function<void(int)> listener);
};


#endif //DOOMCLONE_EVENTMANAGER_H