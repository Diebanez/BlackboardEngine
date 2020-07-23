//
// Created by diego on 24/07/2020.
//

#include "BlackboardRuntime.h"

class TestApplication : public BlackboardRuntime::Application{
public:
    TestApplication(){
    }

    ~TestApplication(){
    }
};

BlackboardRuntime::Application* BlackboardRuntime::CreateApplication() {
    return new TestApplication();
}
