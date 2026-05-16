#include "LibsAndVariables.h"
#include "imgui.h"
#include "Objects.h"
// ======== RESOLUTION ======== //
const int WIDTH[] = {800, 1280};
const int HEIGHT[] = {600, 720};

// ==== Var ==== //
bool Reset;
SDL_Event e;
SDL_Window* window;
SDL_Window* SecWin;
SDL_GLContext context;
SDL_GLContext Seccontext;
extern Preferences Pref;
extern std::vector<Objects> Cubos;
std::string Directory;

/// ================= TAKE NAMES BACKGROUNDS =============== ///
std::vector<std::string> TakeNameBackgrounds(int chargeRes) {
    std::vector<std::string> names;
    WIN32_FIND_DATAA data;
    std::string searchPath = (chargeRes == 0) ? "BackGrounds/Normal/*.bmp" : "BackGrounds/WideScreen/*.bmp";

    HANDLE hSearch = FindFirstFileA(searchPath.c_str(), &data);

    if (hSearch != INVALID_HANDLE_VALUE) {
        do {
            names.push_back(data.cFileName);
        } while (FindNextFileA(hSearch, &data));
        FindClose(hSearch);
    }
    return names;
}

/// ==== SEARCH DIRECTORY GAME ==== ///
void GetDirectoryFiles() {
    char buffer[PATH_MAX];
    if (getcwd(buffer, sizeof(buffer)) != nullptr) {
        std::cout << "current Path: " << buffer << std::endl;
        Directory = buffer;
    } else {
        perror("getcwd");
    }

}

/// ========== INIT GLEW & WIN ========= ///
void Init_WIN_and_GLEW(){
    // ====== Window and Context ======== //
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) std::cout << "SDL Error\n";
        window = SDL_CreateWindow("BG RandOld", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH[Pref.ChargeRes], HEIGHT[Pref.ChargeRes], SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        if (!window){
            std::cout << "Window Error\n";
            SDL_Quit();
        }
        context = SDL_GL_CreateContext(window);
        if (!context){
            std::cout << "Context Error\n";
            SDL_DestroyWindow(window);
            SDL_Quit();
        }
        SDL_SysWMinfo wmInfo;
        SDL_VERSION(&wmInfo.version);
        if (SDL_GetWindowWMInfo(window, &wmInfo)) {
            HWND hwnd = wmInfo.info.win.window;
            HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(1));
            if (hIcon) {
                SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
                SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
            }
        }
        SDL_GL_SetSwapInterval(1);
        glewExperimental = GL_TRUE;
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
    }

    // ====== GLEW ======= //
    {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
            glewExperimental = GL_TRUE;
            if (glewInit() != GLEW_OK){
                std::cout << "GLEW Error\n";
            }

        // Info
            std::cout << "--> OpenGL Version: " << glGetString(GL_VERSION) << "\n";
            std::cout << "--> GPU: " << glGetString(GL_RENDERER) << "\n";

        // Base GL
            glViewport(0, 0, WIDTH[Pref.ChargeRes], HEIGHT[Pref.ChargeRes]);
            glEnable(GL_DEPTH_TEST);

        // ========= IMG ========== //
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

        // Setup Platform/Renderer backends
            ImGui_ImplSDL2_InitForOpenGL(window, context);
            ImGui_ImplOpenGL2_Init();
    }

}

/// ========== Loop GLEW & WIN ========= ///
void Loop_OpenGL(){
    while (SDL_PollEvent(&e)){
            ImGui_ImplSDL2_ProcessEvent(&e);
            if (e.type == SDL_QUIT)
                Running = false;

            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
                Running = false;
        }

    // === INTERFACE === //
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

    // ================= MENU =================== //
         if (ImGui::BeginMainMenuBar()) {
                if (ImGui::BeginMenu("Program")) {
                    if (ImGui::MenuItem("Reset")) {
                        Reset = true;
                    }
                    if (ImGui::MenuItem(Pref.ResText.c_str())) {
                        if(Pref.ChargeRes == 0) {
                            Pref.ChargeRes = 1;
                            Pref.ResText = "16:9";
                        } else {
                            Pref.ChargeRes = 0;
                            Pref.ResText = "4:3";
                        }
                        Pref.SelectedIndex = 0;
                        SDL_SetWindowSize(window, WIDTH[Pref.ChargeRes], HEIGHT[Pref.ChargeRes]);
                        SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
                        glViewport(0, 0, WIDTH[Pref.ChargeRes], HEIGHT[Pref.ChargeRes]);
                    }
                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("View")) {
                        ImGui::MenuItem("BG Custom List", nullptr, &Pref.BGToolActive);
                        ImGui::MenuItem("Tools", nullptr, &Pref.ToolsActive);
                    ImGui::EndMenu();
                }
                ImGui::EndMainMenuBar();
            }

    // ================== TOOLS ====================== //
        if(Pref.ToolsActive){
            ImGui::Begin("Tools");
                ImGui::Text("Is a Mini Tool bar to the Background", 100);
                ImGui::Checkbox("No Draw",&Pref.NoDraw);
                ImGui::ColorEdit3("ColorBackground", (float*)&Pref.BG);
                ImGui::SliderInt("TypeAnim", &Pref.TypeAnim, 0, 9);
                ImGui::Text("Object", 100);
                ImGui::ColorEdit4("Color", (float*)&Pref.Color);
                ImGui::SliderFloat("X.", &Pref.Position.x, -5.0f, 5.0f);
                ImGui::SliderFloat("Y.", &Pref.Position.y, -5.0f, 5.0f);
                ImGui::SliderFloat("Z.", &Pref.Position.z, -5.0f, 5.0f);
                ImGui::InputFloat("Size",&Pref.Sizes, 0.01f,0.1f);
                ImGui::InputFloat3("Spin", &Pref.Spin3.x, "%.3f");
                ImGui::SliderFloat("LimitOfObj", &Pref.LimitCube, 0.0f, 5.0f);
                ImGui::Text("Type of Object", 100);
                ImGui::SliderInt("Type", &Pref.Type, 0, 1);
            ImGui::End();
        }

    // =============== TOOLS BACKGROUND =============== //
        std::vector<std::string> MyBG = TakeNameBackgrounds(Pref.ChargeRes);

        if (Pref.SelectedIndex >= MyBG.size()) {
            Pref.SelectedIndex  = 0;
        }

        if (Pref.BGToolActive) {
            ImGui::Begin("BackGrounds");
                // Mostramos el nombre del archivo seleccionado o "Empty" si la carpeta está realmente vacía
                std::string comboLabel = MyBG.empty() ? "Empty" : MyBG[Pref.SelectedIndex];

                if (ImGui::BeginCombo("List", comboLabel.c_str())) {
                    for (int n = 0; n < MyBG.size(); n++) {
                        bool isSelected = (Pref.SelectedIndex  == n);
                        if (ImGui::Selectable(MyBG[n].c_str(), isSelected)) {
                            Pref.SelectedIndex  = n;
                            ApplyBackGrounds(MyBG[n].c_str());
                        }

                        // Almacena el foco inicial de ImGui
                        if (isSelected) {
                            ImGui::SetItemDefaultFocus();
                        }
                    }
                    ImGui::EndCombo();
                }
            ImGui::End();
        }
    // Clear Background //
    glClearColor(Pref.BG.r,Pref.BG.g,Pref.BG.b,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
