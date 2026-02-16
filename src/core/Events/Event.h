#pragma once

/*
    For linear:
        - Array      (Insert, Erase, Update)
        - LinkedList (Insert, Erase, Update)
        - Stack      (Push, Pop, Top)
        - Queue      (Enqueue, Dequeue, Front)
*/

enum class EventType {
    Insert,
    Erase,
    Update,
    Push,
    Pop,
    Top,
    Enqueue,
    Dequeue,
    Front
};

struct Event {
    EventType type;
    size_t index;
    int value;
};
