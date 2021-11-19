#include <iostream>
#include <memory>


#include "CInterface.h"
#include "CApplication.h"
#include "SRandom.h"


using namespace std;

int main() {
    SRandom::Initialize();
    CInterface interface(cin, cout);
    CApplication app (make_shared<CInterface>(interface));
    return app.Run();
}
