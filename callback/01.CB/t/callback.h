
#ifndef CALLBACK_H
#define CALLBACK_H

AMLEO motor.Any.LOG/Include
AMLEO motor.Application/Include
AMLEO motor.Example/Include
AMLEO motor.Application.Window-web/Include
AMLEO motor.Application.Rendering/Include
AMLEO motor.setupCamera/Include


AMLEO callback.Mir/Include


AMLEO callback.splitString/Impl

AMLEO callback.Mir/Call
AMLEO callback.Mir/Array
AMLEO callback.Mir/SetArray
AMLEO callback.Mir/SetCustomArray
AMLEO callback.Mir/CallJSImpl

namespace callback
{

AMLEO motor.setupCamera/Impl

AMLEO motor.Application/Setup
            AMLEO motor.Application.Rendering/Setup
            AMLEO motor.Application.LOGTranslations-ru/ОШИБКА_ОКНО_SDL
            AMLEO motor.Application.LOGTest/Impl
AMLEO motor.Application/TearDown
            AMLEO motor.Application.Rendering/TearDown
AMLEO motor.Application/Impl
    AMLEO motor.Any.LOG/Impl
    AMLEO motor.Application.Window-embedded/Impl
    AMLEO motor.Application.Window-web/Impl
    AMLEO motor.Application.Rendering/Impl

    AMLEO motor.Application+LOG/Impl
    AMLEO motor.Application+frame/Impl
    AMLEO motor.Application+run/Impl
AMLEO motor.Application/End

AMLEO motor.Example/Setup
AMLEO motor.Example/TearDown
AMLEO motor.Example/Impl
    AMLEO callback.Example.Title.01/Impl
AMLEO motor.Example/End

} // namespace callback

#endif // CALLBACK_H

