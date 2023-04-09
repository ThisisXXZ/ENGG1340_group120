#ifndef EVENT
#define EVENT

class event {
    int DD, MM;  // Date: DD/MM
    int t;       // Time: 0-24
    int place;   // Place
public:
    event();
    int getDay();
    int getMonth();
    int getTime();
    int getPlace();
    // + intelligence
};

#endif