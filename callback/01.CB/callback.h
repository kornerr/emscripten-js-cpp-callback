
#ifndef CALLBACK_H
#define CALLBACK_H

#include <cstdarg>
#include <string>
#include <map>
#include <emscripten.h>
#include <SDL2/SDL.h>
#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>
#include <osg/Camera>


#include <emscripten/bind.h>
#include <emscripten/val.h>


// Topic: Parse (split) a string in C++ using string delimiter (standard C++)
// Source: https://stackoverflow.com/a/44495206
std::vector<std::string> splitString(
    std::string str,
    const std::string &delimiter
) {
    std::vector<std::string> result;
    std::size_t pos = 0;
    while ((pos = str.find(delimiter)) != std::string::npos)
    {
        auto token = str.substr(0, pos);
        result.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    result.push_back(str);
    return result;
}

void cppcall(const std::string &message)
{
    printf("cppcall(%s)\n", message.c_str());
}

EMSCRIPTEN_BINDINGS(mycppcall) {
    emscripten::function("cppcall", &cppcall);
}
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

namespace callback
{

//! Configure camera with common defaults.
void setupCamera(
    osg::Camera *cam,
    osg::GraphicsContext *gc,
    double fovy,
    int width,
    int height
) {
    // Provide GC.
    cam->setGraphicsContext(gc);
    // Viewport must have the same size.
    cam->setViewport(new osg::Viewport(0, 0, width, height));
    // Clear depth and color buffers each frame.
    cam->setClearMask(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    // Aspect ratio.
    float aspect = static_cast<float>(width) / static_cast<float>(height);
    // Configure projection.
    cam->setProjectionMatrixAsPerspective(fovy, aspect, 1, 1000);
}

class Application
{
    public:
        Application(const std::string &name)
        {
            this->setupRendering();
            this->translations["ОШИБКА_ОКНО_SDL"] = "ОШИБКА Не удалось создать окно SDL: '%s'";
            this->LOG("ОШИБКА_ОКНО_SDL", "Что-то пошло не так");
        }
        ~Application()
        {
            delete this->viewer;
        }
    private:
        std::map<std::string, std::string> translations;
    
        void LOG(const char *key, ...)
        {
            // Locate translation.
            auto it = this->translations.find(key);
            // Print without arguments if no translation was found.
            if (it == this->translations.end())
            {
                printf("%s\n", key);
                return;
            }
    
            // Print translation with arguments.
            auto format = it->second;
            va_list args;
            va_start(args, key);
            vprintf(format.c_str(), args);
            printf("\n");
            va_end(args);
        }
    private:
        int windowWidth;
        int windowHeight;
    public:
        void setupWindow(int width, int height)
        {
            this->viewer->setUpViewerAsEmbeddedInWindow(0, 0, width, height);
            this->windowWidth = width;
            this->windowHeight = height;
        }
    private:
        SDL_Window *sdlWindow = 0;
    public:
        bool setupWindow(
            const std::string &title,
            int width,
            int height
        ) {
            this->configureSDLGLContext();
            this->sdlWindow =
                SDL_CreateWindow(
                    title.c_str(),
                    SDL_WINDOWPOS_CENTERED,
                    SDL_WINDOWPOS_CENTERED,
                    width,
                    height,
                    SDL_WINDOW_OPENGL
                );
            if (!this->sdlWindow)
            {
                this->LOG("ОШИБКА_ОКНО_SDL", SDL_GetError());
                return false;
            }
    
            SDL_GL_CreateContext(this->sdlWindow);
            this->setupWindow(width, height);
    
            return true;
        }
        void configureSDLGLContext()
        {
            SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
            SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
            SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        }
    private:
        osgViewer::Viewer *viewer;
        void setupRendering()
        {
            // Create OpenSceneGraph viewer.
            this->viewer = new osgViewer::Viewer;
            // Use single thread: CRITICAL for mobile and web because
            // multiple threads have issues with OpenSceneGraph there.
            this->viewer->setThreadingModel(osgViewer::ViewerBase::SingleThreaded);
            // Create manipulator: CRITICAL for mobile and web to focus on the
            // nodes in the scene.
            this->viewer->setCameraManipulator(new osgGA::TrackballManipulator);
        }

    public:
        void frame()
        {
            this->viewer->frame();
        }
    public:
        void run()
        {
            while (!this->viewer->done())
            {
                this->frame();
            }
        }
};

struct Example
{
    Application *app;

    typedef std::map<std::string, std::string> Parameters;

    Example(const Parameters &parameters)
    {
        this->app = new Application(this->title);
    }
    ~Example()
    {
        delete this->app;
    }
    const std::string title = "callback-01: JS + C++";
};

} // namespace callback

#endif // CALLBACK_H

