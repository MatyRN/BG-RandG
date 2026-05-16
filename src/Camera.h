#ifndef CAMERA_H
#define CAMERA_H
#include "LibsAndVariables.h"
#include <cmath>

/// == POS CAMERA == ///
    struct CameraPos {
        Vec3 Pos = {0.0f, 0.2f, 1.5f};
        float yaw   = 180.0f;
        float pitch = -10.0f;
    };

extern CameraPos CamP;
///===== CAMERA =====///
    class Camera {
        public:
            void CameraSetup();
            void CameraApply();
    };
    extern Camera Cam;
#endif
