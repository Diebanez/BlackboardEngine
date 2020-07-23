#include "Application.h"
#include <iostream>

namespace BlackboardRuntime
{
    Application::Application(unsigned int maxTickCount) : m_MaxTickCount(maxTickCount), m_ActualTickCount(0)
    {
        std::cout << "Initialized Application!" << std::endl;
    }

    bool Application::Run()
    {
        m_ActualTickCount++;
        std::cout << "Actual tick " << m_ActualTickCount << std::endl;

        return m_ActualTickCount < m_MaxTickCount;
    }
} // namespace BlackboardRuntime