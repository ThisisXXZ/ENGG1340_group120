#ifndef EVENT_H
#define EVENT_H

#include "player.h"

#include <string>

class Event {
public:
    int getDay();
    int getMonth();
    int getTime();
    int getPlace();

    Event(int DD,int MM,int t, std::string place) : DD(DD), MM(MM), t(t), place(place) {}
    virtual void applyEvent(player& p) const;

private:
    int DD, MM;  // Date: DD/MM
    int t;       // Time: 0-24
    std::string place;   // Place
    // + intelligence
};

class StrugglingInClass : public Event {
public: 
    StrugglingInClass(int DD, int MM, int t, std::string place) : Event(DD, MM, t, place) {}
    void applyEvent(player& p) const override;
};

void StrugglingInClass::applyEvent(player& p) const {
    // Implementation for StrugglingInClass event
}

class MissingDeadline : public Event {
public: 
    MissingDeadline(int DD, int MM, int t, std::string place) : Event(DD, MM, t, place) {}
    void applyEvent(player& p) const override;
};

void MissingDeadline::applyEvent(player& p) const {
    // Implementation for MissingDeadline event
}

class JoiningClubs : public Event {
public: 
    JoiningClubs(int DD, int MM, int t, std::string place) : Event(DD, MM, t, place) {}
    void applyEvent(player& p) const override;
};

void JoiningClubs::applyEvent(player& p) const {
    // Implementation for JoiningClubs event
}

class InternshipOrCoop : public Event {
public: 
    InternshipOrCoop(int DD, int MM, int t, std::string place) : Event(DD, MM, t, place) {}
    void applyEvent(player& p) const override;
};

void InternshipOrCoop::applyEvent(player& p) const {
    // Implementation for InternshipOrCoop event
}

class StudyAbroad : public Event {
public: 
    StudyAbroad(int DD, int MM, int t, std::string place) : Event(DD, MM, t, place) {}
    void applyEvent(player& p) const override;
};

void StudyAbroad::applyEvent(player& p) const {
    // Implementation for StudyAbroad event
}

class Scholarships : public Event {
public: 
    Scholarships(int DD, int MM, int t, std::string place) : Event(DD, MM, t, place) {}
    void applyEvent(player& p) const override;
};

void Scholarships::applyEvent(player& p) const {
    // Implementation for Scholarships event
}

class CatchCOVID19 : public Event {
public:
    CatchCOVID19(int DD, int MM, int t, std::string place) : Event(DD, MM, t, place) {}
    void applyEvent(player &p) const override;
};

void CatchCOVID19::applyEvent(player &p) const {
    // Implementation for CatchCOVID19 event
}

class Depression : public Event {
public:
    Depression(int DD, int MM, int t, std::string place) : Event(DD, MM, t, place) {}
    void applyEvent(player &p) const override;
};

void Depression::applyEvent(player &p) const {
    // Implementation for Depression event
}

class AcademicChallenge : public Event {
public:
    AcademicChallenge(int DD, int MM, int t, std::string place) : Event(DD, MM, t, place) {}
    void applyEvent(player &p) const override;
};

void AcademicChallenge::applyEvent(player &p) const {
    // Implementation for AcademicChallenge event
}

class SingleLife : public Event {
public:
    SingleLife(int DD, int MM, int t, std::string place) : Event(DD, MM, t, place) {}
    void applyEvent(player &p) const override;
};

void SingleLife::applyEvent(player &p) const {
    // Implementation for SingleLife event
}


class Relationship : public Event {
public:
    Relationship(int DD, int MM, int t, std::string place) : Event(DD, MM, t, place) {}
    void applyEvent(player &p) const override;
};

void Relationship::applyEvent(player &p) const {
    // Implementation for Relationship event
}

class Minor : public Event {
public:
    Minor(int DD, int MM, int t, std::string place) : Event(DD, MM, t, place) {}
    void applyEvent(player &p) const override;
};

void Minor::applyEvent(player &p) const {
    // Implementation for Minor event
}

class Job : public Event {
public: 
    Job(int DD, int MM, int t, std::string place) : Event(DD, MM, t, place) {}
    void applyEvent(player& p) const override;
};

void Job::applyEvent(player& p) const {
    // Implementation for Job event
}

class GRE : public Event {
public: 
    GRE(int DD, int MM, int t, std::string place) : Event(DD, MM, t, place) {}
    void applyEvent(player& p) const override;
};

void GRE::applyEvent(player& p) const {
    // Implementation for GRE event
}

class GraduateCapstone : public Event {
public: 
    GraduateCapstone(int DD, int MM, int t, std::string place) : Event(DD, MM, t, place) {}
    void applyEvent(player& p) const override;
};

void GraduateCapstone::applyEvent(player& p) const {
    // Implementation for GraduateCapstone event
}

class PostGraduation : public Event {
public: 
    PostGraduation(int DD, int MM, int t, std::string place) : Event(DD, MM, t, place) {}
    void applyEvent(player& p) const override;
};

void PostGraduation::applyEvent(player& p) const {
    // Implementation for PostGraduation event
}

#endif // EVENT_H