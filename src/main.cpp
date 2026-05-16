#include "Camera.h"
#include "LibsAndVariables.h"
#include "Objects.h"

/// ========== VAR ============ ///
extern std::vector<Objects> Cubos;

bool Running = true;
extern SDL_Window* window;
extern SDL_GLContext context;
extern Camera Cam;
extern Preferences Pref;
static int lastTypeAnim = Pref.TypeAnim;

/// =========== MAIN ============ ///
int main(int argc, char* argv[]){
    Init_WIN_and_GLEW();
    SpawnObjects(Pref.Position, Pref.Color, Pref.Sizes, Pref.Random);

    /// ==== LOOP ==== ///
        while (Running){
            Loop_OpenGL();
                Cam.CameraSetup();
                Cam.CameraApply();
            // Reset //
                if (Reset == true){
                    Cubos.clear();
                        Pref.Position = {0.0f, -0.0f, 0.0f};
                        Pref.PosOrigin = {0.0f, 0.21f, 0.0f};
                        Pref.Spin3 = {0.0f, 0.5f, 0.0f};
                        Pref.Color = {1.0f, 1.0f, 1.0f, 1.0f};
                        Pref.BG = {0.0f, 0.0f, 0.0f, 0.0f};
                        Pref.Sizes = 0.04f;
                        Pref.Spin = 0.2f;
                        Pref.LimitCube = 2.5f;
                        Pref.BGTextureID = 0;
                    SpawnObjects(Pref.Position, Pref.Color, Pref.Sizes, Pref.Random);
                    lastTypeAnim = Pref.TypeAnim;
                    Reset = false;
                }

                if (Pref.TypeAnim != lastTypeAnim || Reset == true) {
                    Cubos.clear();
                        Pref.Position = {0.0f, -0.0f, 0.0f};
                        Pref.PosOrigin = {0.0f, 0.21f, 0.0f};
                    SpawnObjects(Pref.Position, Pref.Color, Pref.Sizes, Pref.Random);
                    lastTypeAnim = Pref.TypeAnim;
                    Reset = false;
                }

            // Draw Here //
                glPushMatrix();
                    if(Pref.NoDraw){
                        RenderBackground();
                        for (int i = 0; i < Cubos.size(); i++) {
                            switch(Pref.Type){
                                case 0: Cubos[i].DrawCube();
                                    break;
                                case 1: Cubos[i].DrawTriangles();
                                    break;
                                }
                        }
                    }
                glPopMatrix();

            // Other Charge //
                for (int i = 0; i < Cubos.size(); i++) {
                    Cubos[i].SetColor(Pref.Color);
                    Cubos[i].SetSize (Pref.Sizes);
                }

            //IMGUI
                ImGui::Render();
                ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

            // SDL Refresh
            SDL_GL_MakeCurrent(window, context);
            SDL_GL_SwapWindow(window);
        }

    /// ====== Close the Program ===== ///
            ImGui_ImplOpenGL2_Shutdown();
            ImGui_ImplSDL2_Shutdown();
            ImGui::DestroyContext();
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
    return 0;
}
