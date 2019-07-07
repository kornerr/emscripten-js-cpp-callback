
#include "callback.h"

using namespace callback;

// Global instance to be used in free functions.
Example *example = 0;
// Function to be used by Emscripten to run the application.
void loop()
{
    if (example)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
    callJSMir();
        }
        example->app->frame();
    }
}

int main(int argc, char *argv[])
{
    Example::Parameters parameters;
    example = new Example(parameters);
    // Create rendering window of initial size.
    if (!example->app->setupWindow(example->title, 800, 600))
    {
        printf("ERROR WINDOW");
        return 1;
    }
    // Render asynchronously.
    emscripten_set_main_loop(loop, -1, 0);

    return 0;
}

