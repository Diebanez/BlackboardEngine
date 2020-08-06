//
// Created by diego on 24/07/2020.
//

#ifndef BLACKBOARDENGINE_ENTRYPOINT_H
#define BLACKBOARDENGINE_ENTRYPOINT_H

extern BlackboardRuntime::Application* BlackboardRuntime::CreateApplication();

int main(int argx, char** argv){
    BlackboardRuntime::Log::Init();

#ifdef BB_ENABLE_ASSERTS
    BB_CORE_WARN("Assertion enabled");
#endif

    auto app = BlackboardRuntime::CreateApplication();
    app->Run();
    delete app;
}

#endif //BLACKBOARDENGINE_ENTRYPOINT_H
