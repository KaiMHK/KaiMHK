#pragma once


// Function Prototypes
//
void MySetupSurfaces();                // Called once, before rendering begins.
void SetupForTextures();               // Loads textures, sets Phong material
void MyRemeshGeometries();             // Called when mesh changes, must update resolutions.
void MyRemeshCircularSurf();      // Update resolution of the surface of rotation.

void MyRenderGeometries();            // Called to render the two surfaces
void SamsRenderCircularSurf();      // Renders the meshed circular surface



