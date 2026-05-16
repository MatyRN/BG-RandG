#ifndef OBJECTS_H_INCLUDED
#define OBJECTS_H_INCLUDED
#include "LibsAndVariables.h"

// ========= PREFERENCES ========= //
    struct Preferences {
        // Position
            Vec3 Position = {0.0f, -0.0f, 0.0f};
            Vec3 PosOrigin = {0.0f, 0.21f, 0.0f};
            Vec3 Spin3 = {0.0f, 0.5f, 0.0f};
        // Colours
            Colour Color = {1.0f, 1.0f, 1.0f, 1.0f};
            Colour BG = {0.0f, 0.0f, 0.0f, 1.0f};
            float CuboAlpha = 0.5f;
        // Other Values
            float Sizes = 0.04f;
            float Spin = 0.2f;
            float LimitCube = 2.5f;
            GLuint BGTextureID;
            int Random = 1;
            bool NoDraw = 1;
            bool BGToolActive = false;
            bool ToolsActive = true;
            int Type = 0;
            int TypeAnim = 1;
            int ChargeRes = 0;
            int SelectedIndex = 0;
            std::string ResText = "4:3";
    };

/// === OBJECTS === ///
class Objects {
    public:
    // Object Individual
        Objects(Vec3 _Pos, Colour _Color, float _Size);
        void DrawCube();
        void DrawTriangles();
        void DrawOthers();

    // Set
        void SetColor (Colour Colorr);
        void SetPos (Vec3 Poss);
        void SetSize (float Sizze);
    private:
        Vec3 OfftenPos;
        Vec3 Pos;
        Colour Color;
        float Size;
        int Random;
        Vec3 Angle;
};
    void ApplyBackGrounds(const char* namefile);
    void RenderBackground();
    void SpawnObjects(Vec3 PosOBJ, Colour _ColorOBJ, float _SizeOBJ, int _Random);
#endif
