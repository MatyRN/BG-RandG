#include "Camera.h"
#include <GL/gl.h>
#include <GL/glu.h>

// ==== VAR ==== //
Camera Cam;
CameraPos CamP;

/// ======= CAMERA SETUP ====== ///
void Camera::CameraSetup(){
    glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(80.0, 800.0 / 600.0, 0.1, 300.0);
        glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/// ======== CAMERA APPLY ======== ///
void Camera::CameraApply(){
    // Convert to Radiant
    float yawRad   = CamP.yaw   * 0.0174533f;
    float pitchRad = CamP.pitch * 0.0174533f;

    // Vector forward REAL
    float fx = cos(pitchRad) * sin(yawRad);
    float fy = sin(pitchRad);
    float fz = cos(pitchRad) * cos(yawRad);

    gluLookAt(CamP.Pos.x, CamP.Pos.y, CamP.Pos.z, CamP.Pos.x + fx, CamP.Pos.y + fy, CamP.Pos.z + fz, 0, 1, 0);
}

