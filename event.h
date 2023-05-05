#ifndef EVENT_H
#define EVENT_H

#include "player.h"
#include "interface.h"

#include <string>
#include <vector>

// Event class is a base class for various derived events
class Event {
public:

// getters for time
    int getYear();
    int getSem();
    int getWeek();
    

    Event(int year, int sem, int week) : year(year), sem(sem), week(week), process(0) {}
    virtual bool applyEvent(player& p, interface& INT); // the player will interact with events in this function

    bool checktime(int, int, int);
    int getProcess();
    void setProcess(int);

private:
    int year, sem;       // Date: year / sem
    int week;            // Time: 0-11
    int process;         // process indicates the event's status (unfinished/in progress/finished/refused...)
};

// The derived events
class StrugglingInClass : public Event {
public: 
    StrugglingInClass(int year, int sem, int week) : Event(year, sem, week) {}
    bool applyEvent(player& p, interface& INT) override;
};


class MissingDeadline : public Event {
public: 
    MissingDeadline(int year, int sem, int week) : Event(year, sem, week) {}
    bool applyEvent(player& p, interface& INT) override;
};

class JoiningClubs : public Event {
public: 
    JoiningClubs(int year, int sem, int week) : Event(year, sem, week) {}
    bool applyEvent(player& p, interface& INT) override;
};

class InternshipOrCoop : public Event {
public: 
    InternshipOrCoop(int year, int sem, int week) : Event(year, sem, week) {}
    bool applyEvent(player& p, interface& INT) override;
};

class StudyAbroad : public Event {
public: 
    StudyAbroad(int year, int sem, int week) : Event(year, sem, week) {}
    bool applyEvent(player& p, interface& INT) override;
};

class Scholarships : public Event {
public: 
    Scholarships(int year, int sem, int week) : Event(year, sem, week) {}
    bool applyEvent(player& p, interface& INT) override;
};

class Depression : public Event {
public:
    Depression(int year, int sem, int week) : Event(year, sem, week) {}
    bool applyEvent(player& p, interface& INT) override;
};

class Relationship : public Event {
public:
    Relationship(int year, int sem, int week) : Event(year, sem, week) {}
    bool applyEvent(player& p, interface& INT) override;
};

class Minor : public Event {
public:
    Minor(int year, int sem, int week) : Event(year, sem, week) {}
    bool applyEvent(player& p, interface& INT) override;
};

class GraduateCapstone : public Event {
public: 
    GraduateCapstone(int year, int sem, int week) : Event(year, sem, week) {}
    bool applyEvent(player& p, interface& INT) override;
};

class WatchDanceShow : public Event {
public: 
    WatchDanceShow(int year, int sem, int week) : Event(year, sem, week) {}
    bool applyEvent(player& p, interface& INT) override;
};

class WatchDebateCompetition : public Event {
public:
    WatchDebateCompetition(int year, int sem, int week) : Event(year, sem, week) {}
    bool applyEvent(player& p, interface& INT) override;
};

class GotoChurch : public Event {
public:
    GotoChurch(int year, int sem, int week) : Event(year, sem, week) {}
    bool applyEvent(player& p, interface& INT) override;
};



#endif // EVENT_H