#include "Objects.h"

// ====== VAR ====== //
std::vector<Objects> Cubos;
int RandomSeed = 0;
Preferences Pref;

// ============= OBJECTS PREFERENCES ============== //
Objects::Objects(Vec3 _Pos, Colour _Color, float _Size){
    OfftenPos = _Pos;
    Color = _Color;
    Size = _Size;
    Angle = {0.0f, 0.0f, 0.0f};
}

/// ========== SET COLOR ======== ///
void Objects::SetColor (Colour Colorr){
    Color = Colorr;
}

/// ========= SET POSITION ======== ///
void Objects::SetPos (Vec3 Poss){
    Pos = Poss;
}

/// ========= SET SIZE ============ ///
void Objects::SetSize (float Sizze){
    Size = Sizze;
}

/// ================ DRAW CUBE ====================== ///
void Objects::DrawCube (){
    Angle.x += Pref.Spin3.x;
    Angle.y += Pref.Spin3.y;
    Angle.z += Pref.Spin3.z;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glTranslatef(Pref.Position.x + OfftenPos.x, Pref.Position.y + OfftenPos.y, Pref.Position.z + OfftenPos.z);
        glRotatef(Angle.x, 1.0f, 0.0f, 0.0f);
        glRotatef(Angle.y, 0.0f, 1.0f, 0.0f);
        glRotatef(Angle.z, 0.0f, 0.0f, 1.0f);

    glBegin(GL_QUADS);
        // Front
        glColor4f(Color.r, Color.g, Color.b, Color.a);
        glVertex3f(-Size,-Size, Size);
        glVertex3f( Size,-Size, Size);
        glVertex3f( Size, Size, Size);
        glVertex3f(-Size, Size, Size);

        // Back
        glColor4f(Color.r, Color.g, Color.b, Color.a);
        glVertex3f(-Size,-Size,-Size);
        glVertex3f(-Size, Size,-Size);
        glVertex3f( Size, Size,-Size);
        glVertex3f( Size,-Size,-Size);

        // Left
        glColor4f(Color.r, Color.g, Color.b, Color.a);
        glVertex3f(-Size,-Size,-Size);
        glVertex3f(-Size,-Size, Size);
        glVertex3f(-Size, Size, Size);
        glVertex3f(-Size, Size,-Size);

        // Right
        glColor4f(Color.r, Color.g, Color.b, Color.a);
        glVertex3f( Size,-Size,-Size);
        glVertex3f( Size, Size,-Size);
        glVertex3f( Size, Size, Size);
        glVertex3f( Size,-Size, Size);

        // Top
        glColor4f(Color.r, Color.g, Color.b, Color.a);
        glVertex3f(-Size, Size,-Size);
        glVertex3f(-Size, Size, Size);
        glVertex3f( Size, Size, Size);
        glVertex3f( Size, Size,-Size);

        // Down
        glColor4f(Color.r, Color.g, Color.b, Color.a);
        glVertex3f(-Size,-Size,-Size);
        glVertex3f( Size,-Size,-Size);
        glVertex3f( Size,-Size, Size);
        glVertex3f(-Size,-Size, Size);
    glEnd();
}

/// ================ DRAW TRIANGLES =================== ///
void Objects::DrawTriangles (){
    Angle.x += Pref.Spin3.x;
    Angle.y += Pref.Spin3.y;
    Angle.z += Pref.Spin3.z;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glTranslatef(Pref.Position.x + OfftenPos.x, Pref.Position.y + OfftenPos.y, Pref.Position.z + OfftenPos.z);
        glRotatef(Angle.x, 1.0f, 0.0f, 0.0f);
        glRotatef(Angle.y, 0.0f, 1.0f, 0.0f);
        glRotatef(Angle.z, 0.0f, 0.0f, 1.0f);

    glBegin(GL_TRIANGLES);
        // Front
        glColor4f(Color.r, Color.g, Color.b, Color.a);
        glVertex3f( 0.0f, Size, 0.0f);
        glVertex3f(-Size,-Size, Size);
        glVertex3f( Size,-Size, Size);

        // Back
        glColor4f(Color.r, Color.g, Color.b, Color.a);
        glVertex3f( 0.0f, Size, 0.0f);
        glVertex3f( Size,-Size, Size);
        glVertex3f( Size,-Size,-Size);

        // Left
        glColor4f(Color.r, Color.g, Color.b, Color.a);
        glVertex3f( 0.0f, Size, 0.0f);
        glVertex3f( Size,-Size,-Size);
        glVertex3f(-Size,-Size,-Size);

        // Right
        glColor4f(Color.r, Color.g, Color.b, Color.a);
        glVertex3f( 0.0f, Size, 0.0f);
        glVertex3f(-Size,-Size,-Size);
        glVertex3f(-Size,-Size, Size);
    glEnd();
}

/// ================ SPAWN OBJECTS ==================== ///
void SpawnObjects(Vec3 PosOBJ, Colour _ColorOBJ, float _SizeOBJ, int _Random){
    if(Pref.TypeAnim == 0){ // Invocacion
        for (float i = 0.0f; i < Pref.LimitCube; i+=0.15f) {
            RandomSeed = std::rand() % _Random;
            float valueAct = sin(i) * 0.05f;
                Vec3 newPos = { PosOBJ.x, PosOBJ.y, PosOBJ.z};

            Objects NewCube(newPos, Pref.Color, _SizeOBJ);
            Cubos.push_back(NewCube);
        }
    }else if (Pref.TypeAnim == 1){ //Galaxia
         for (float i = 0.0f; i < Pref.LimitCube; i+=0.15f) {
            RandomSeed = std::rand() % _Random;
            float valueAct = sin(i) * 0.05f;
                Vec3 newPos = { PosOBJ.x, PosOBJ.y, PosOBJ.z + (float)i};

            Objects NewCube(newPos, Pref.Color, _SizeOBJ);
            Cubos.push_back(NewCube);
        }
    }else if(Pref.TypeAnim == 2) { // Espacio Estelar
        int cantidadEstrellas = 350;
            for (int i = 0; i < cantidadEstrellas; i++) {
                float rx = ((float)rand() / (float)RAND_MAX) * 5.0f - 5.0f;
                float ry = ((float)rand() / (float)RAND_MAX) * 10.0f - 5.0f;
                float rz = ((float)rand() / (float)RAND_MAX) * 5.0f - 5.0f;

                Vec3 newPos = {PosOBJ.x + rx, PosOBJ.y + ry, PosOBJ.z + rz };

                Objects Star(newPos, Pref.Color, 0.01f);
                Cubos.push_back(Star);
            }
    }else if (Pref.TypeAnim == 3) { // Tornadito
        for (float i = 0.0f; i < Pref.LimitCube * 10.0f; i += 0.2f) {
            float radio = i * 0.1f;
            Vec3 newPos = {
                sin(i) * radio,
                i * 0.1f,
                cos(i) * radio
            };
            Objects NewCube(newPos, Pref.Color, _SizeOBJ);
            Cubos.push_back(NewCube);
        }
    }else if (Pref.TypeAnim == 4) { // Plasma
        for (int i = 0; i < 200; i++) {
            float u = (float)rand() / RAND_MAX;
            float v = (float)rand() / RAND_MAX;
            float theta = 2.0f * 3.14159f * u;
            float phi = acos(2.0f * v - 1.0f);
            float r = 1.5f;
            Vec3 newPos = {
                r * sin(phi) * cos(theta),
                r * sin(phi) * sin(theta),
                r * cos(phi)
            };
            Objects NewCube(newPos, Pref.Color, _SizeOBJ);
            Cubos.push_back(NewCube);
        }
    }else if (Pref.TypeAnim == 5) { // Rain Matrix
        for (int i = 0; i < 150; i++) {
            Vec3 newPos = {
                (float)(rand() % 20 - 10) * 0.2f,
                (float)(rand() % 50) * 0.1f,
                (float)(rand() % 10 - 5) * 0.2f
            };
            Objects NewCube(newPos, Pref.Color, _SizeOBJ);
            Cubos.push_back(NewCube);
        }
    }else if (Pref.TypeAnim == 6) { // Big Bang
        for (int i = 0; i < 100; i++) {
            float dirX = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
            float dirY = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
            float dirZ = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;

            Vec3 newPos = { dirX * i * 0.02f, dirY * i * 0.02f, dirZ * i * 0.02f };
            Objects NewCube(newPos, Pref.Color, _SizeOBJ);
            Cubos.push_back(NewCube);
        }
    }else if (Pref.TypeAnim == 7) { // Saturn
        for (int i = 0; i < 300; i++) {
            float angulo = ((float)rand() / RAND_MAX) * 2.0f * 3.14159f;
            float dist = 1.0f + ((float)rand() / RAND_MAX) * 0.5f;
            Vec3 newPos = { cos(angulo) * dist, ((float)rand()/RAND_MAX - 0.5f) * 0.1f, sin(angulo) * dist };
            Objects NewCube(newPos, Pref.Color, _SizeOBJ);
            Cubos.push_back(NewCube);
        }
    }else if (Pref.TypeAnim == 8) { // Cube 3D
        int lado = 5;
        for (int x = 0; x < lado; x++) {
            for (int y = 0; y < lado; y++) {
                for (int z = 0; z < lado; z++) {
                    Vec3 newPos = { x * 0.3f - 0.6f, y * 0.3f - 0.6f, z * 0.3f - 0.6f };
                    Objects NewCube(newPos, Pref.Color, _SizeOBJ);
                    Cubos.push_back(NewCube);
                }
            }
        }
    }else if (Pref.TypeAnim == 9) { // Infinity
        for (float i = 0.0f; i < 6.28f; i += 0.1f) {
            float scale = 2.0f / (3.0f - cos(2.0f * i));
            Vec3 newPos = {
                scale * cos(i),
                scale * sin(2.0f * i) / 2.0f,
                0.0f
            };
            Objects NewCube(newPos, Pref.Color, _SizeOBJ);
            Cubos.push_back(NewCube);
        }
    }
}

/// ============= RENDER BACKGROUND ============ ///
void RenderBackground() {
    if (Pref.BGTextureID == 0) return;
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, Pref.BGTextureID);
            glColor3f(1.0f, 1.0f, 1.0f);

            glMatrixMode(GL_PROJECTION);
            glPushMatrix();
            glLoadIdentity();
            glOrtho(0, 1, 0, 1, -1, 1);

            glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        glBegin(GL_QUADS);
            glTexCoord2f(0, 1); glVertex2f(0, 0);
            glTexCoord2f(1, 1); glVertex2f(1, 0);
            glTexCoord2f(1, 0); glVertex2f(1, 1);
            glTexCoord2f(0, 0); glVertex2f(0, 1);
        glEnd();

        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);

        glDisable(GL_TEXTURE_2D);
        glEnable(GL_DEPTH_TEST);
}

/// ================ LOAD BACKGROUND ============== ///
void ApplyBackGrounds(const char* namefile) {
    std::string subFolder = (Pref.ChargeRes == 0) ? "Normal/" : "WideScreen/";
    std::string Path = "BackGrounds/" + subFolder + std::string(namefile);

    SDL_Surface* surface = SDL_LoadBMP(Path.c_str());

    if (surface) {
        if (Pref.BGTextureID != 0) glDeleteTextures(1, &Pref.BGTextureID);

        glGenTextures(1, &Pref.BGTextureID);
        glBindTexture(GL_TEXTURE_2D, Pref.BGTextureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, GL_BGR, GL_UNSIGNED_BYTE, surface->pixels);
        SDL_FreeSurface(surface);
    } else {
        std::cout << "Error " << Path << std::endl;
    }
}
