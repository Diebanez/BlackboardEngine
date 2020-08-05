//
// Created by diego on 04/08/2020.
//

#ifndef BLACKBOARDENGINE_TIMESTEP_H
#define BLACKBOARDENGINE_TIMESTEP_H

namespace BlackboardRuntime{
    class TimeStep{
    public:
        TimeStep(float time = 0.0f) : m_Time(time){}

        operator float() const {return m_Time;}

        float GetSeconds() const {return m_Time;}
        float GetMilliseconds() const {return m_Time * 1000.0f;}
        int GetFrameRate() const {return (float)(1.0f / m_Time);}
    private:
        float m_Time;
    };
}

#endif //BLACKBOARDENGINE_TIMESTEP_H
