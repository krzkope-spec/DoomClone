
#include "../include/EventManager.h"

#include <iostream>
#include <ostream>

void EventManager::MouseClick(int button) const{
    for (const auto& f : mouseClickListeners_) {
        f(button);
    }
}
void EventManager::MouseMove(int x, int y) const {
    for (const auto& f : mouseMoveListeners_) {
        f(x,y);
    }
}
void EventManager::KeyboardDown(int keyCode) const {
    for (const auto& f : keyboardDownListeners_) {
        f(keyCode);
    }
}
void EventManager::KeyboardUp(int keyCode) const {
    for (const auto& f : keyboardUpListeners_) {
        f(keyCode);
    }
}
void EventManager::Keyboard(int keyCode) const {
    for (const auto& f : keyboardListeners_) {
        f(keyCode);
    }
}
void EventManager::AddEventListener(EVENT_TYPE event, std::function<void(int, int)> listener) {
    if (event==MOUSE_MOVE) {
        mouseMoveListeners_.push_back(listener);
    }
}
void EventManager::AddEventListener(EVENT_TYPE event, std::function<void(int)> listener) {
    switch (event) {
        case MOUSE_CLICK:
            mouseClickListeners_.push_back(listener);
            break;
        case KEYBOARD:
            keyboardListeners_.push_back(listener);
            break;
        case KEYBOARD_UP:
            keyboardUpListeners_.push_back(listener);
            break;
        case KEYBOARD_DOWN:
            keyboardDownListeners_.push_back(listener);
            break;
        case MOUSE_MOVE:
            break;
    }
}
