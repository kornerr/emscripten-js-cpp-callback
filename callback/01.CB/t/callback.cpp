
#include "callback.h"

using namespace callback;

AMLEO motor.Example-web/Instance
AMLEO motor.Loop-web/Begin
    AMLEO callback.Mir/CallJS
AMLEO motor.Loop-web/End

int main(int argc, char *argv[])
{
    AMLEO motor-web/Setup
    AMLEO motor.Example/Params
    AMLEO motor.Example-web/Init
    AMLEO motor.Loop-web/Run

    return 0;
}

