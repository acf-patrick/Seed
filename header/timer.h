#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
    Timer();
    int getElapsedMilliseconds();
    float getElapsedSeconds();
    void restart();

protected:
    int start_time;
};

class Chrono: public Timer
{
public:
	// wait time in milliseconds
    Chrono(int);
    void restart(int r_time = -1);
    bool out();

private:
    int remaining;
};

#endif // TIMER_H

