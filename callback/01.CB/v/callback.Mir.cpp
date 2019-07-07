AMLEO Include
#include <emscripten/bind.h>
#include <emscripten/val.h>

AMLEO Call
void cppcall(const std::string &message)
{
    printf("cppcall(%s)\n", message.c_str());
}

EMSCRIPTEN_BINDINGS(mycppcall) {
    emscripten::function("cppcall", &cppcall);
}

AMLEO Array
std::vector<std::string> cpparray()
{
    return std::vector<std::string>({
            "One",
            "Two",
            "3ee",
    });
}

EMSCRIPTEN_BINDINGS(mycpparray) {
    emscripten::register_vector<std::string>("StringList");
    emscripten::function("cpparray", &cpparray);
}

AMLEO SetArray
std::vector<std::string> cppsetarray(std::vector<std::string> values)
{
    printf("cppsetarray values:\n");
    for (auto value : values)
    {
        printf("- '%s'\n", value.c_str());
    }
    return values;
}

EMSCRIPTEN_BINDINGS(mycppsetarray) {
    emscripten::function("cppsetarray", &cppsetarray);
}

AMLEO SetCustomArray
std::vector<std::string> cppSetCustomArray(
    const std::string &valuesString,
    const std::string &delimiter
) {
    auto values = splitString(valuesString, delimiter);
    printf("cppSetCustomArray values:\n");
    for (auto value : values)
    {
        printf("- '%s'\n", value.c_str());
    }
    return values;
}

EMSCRIPTEN_BINDINGS(mycppSetCustomArray) {
    emscripten::function("cppSetCustomArray", &cppSetCustomArray);
}

AMLEO CallJS
callJSMir();

AMLEO CallJSImpl
void callJSMir()
{
    // Only execute once.
    static bool execute = true;
    if (!execute)
    {
        return;
    }
    execute = false;

    // Execute "window.mir.callback()" in JS.
    auto mir = emscripten::val::global("mir");
    mir.call<emscripten::val>("callback");
}
