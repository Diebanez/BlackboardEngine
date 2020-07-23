#include <Application.h>
#include <iostream>

using namespace BlackboardRuntime;

int main(){
    Application app = Application(1000);

    while(app.Run()){
        std::cout << "Running" << std::endl;
    }

    return 0;
}