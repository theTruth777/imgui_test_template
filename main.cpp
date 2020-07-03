#include<iostream>

#include "lib/imgui.h"
#include "lib/imgui_impl_sdl.h"
#include "lib/imgui_impl_opengl2.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

int main( int argc, const char* argv[] ) {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Window* window = SDL_CreateWindow("Dear ImGui SDL2+OpenGL example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, window_flags);
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL2_Init();

// Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    bool done = false;
            
    while (!done)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
        }

        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();

        //GUI code starts here
        static int counter = 0;

        //Statische Größe, Resize wird dann Disabled
        ImGui::SetNextWindowSize(ImVec2(800, 600));
        //Setzt die Position des Imgui Windows
        ImGui::SetNextWindowPos(ImVec2(0, 0));

        ImGui::Begin("Hello, world!", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);                          // Create a window called "Hello, world!" and append into it.
        ImGui::SetWindowFontScale(1);
        
        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state

        static char buf[128];
        static const char *dropDownItems[]{"Item 1", "Item 2", "Item 3"};
        static int selectedItems = 0;

        ImGui::PushItemWidth(200.0);
        ImGui::InputText("string", buf, IM_ARRAYSIZE(buf));

        ImGui::Combo("DropDowns", &selectedItems, dropDownItems, IM_ARRAYSIZE(dropDownItems));
        //ImGui::SameLine();
        
        ImGui::Text("counter = %d", counter);
        ImGui::Text("counter = %s", buf);
        ImGui::Text("Selected Dropdown index = %d", selectedItems);


        if (ImGui::Button("Button", ImVec2(120,40)))
            counter++;

        ImGui::End();
        //GUI Code Ends Here
   

        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }

    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}