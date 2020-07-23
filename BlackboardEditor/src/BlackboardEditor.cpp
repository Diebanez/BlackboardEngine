//
// Created by diego on 24/07/2020.
//

#include "BlackboardRuntime.h"

class BlackboardEditorApplication : public BlackboardRuntime::Application{
public:
    BlackboardEditorApplication(){
    }

    ~BlackboardEditorApplication(){
    }
};

BlackboardRuntime::Application* BlackboardRuntime::CreateApplication() {
    return new BlackboardEditorApplication();
}



