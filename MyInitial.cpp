//
//  MyInitial.cpp   - Version 0.4 - October 24, 2020
//
//   Sets up and renders the initial (alphabet letter)
//   for the Math 155A project.
//
//   Comes supplied with some code for a cylinders, a torus,
//      and a revolving ellipsoid.
//
//  THIS FILE IS WHAT YOU WILL MODIFY FOR PROJECT #3.
//  IT WILL ALSO BE USED FOR PROJECTS #4 and #5.
//


// Use the static library (so glew32.dll is not needed):
#define GLEW_STATIC
#include <GL/glew.h> 
#include <GLFW/glfw3.h>

#include "LinearR3.h"		// Adjust paths as needed.
#include "LinearR4.h"		
#include "GlGeomSphere.h"
#include "GlGeomCylinder.h"
#include "GlGeomTorus.h"

// Enable standard input and output via printf(), etc.
// Put this include *after* the includes for glew and GLFW!
#include <stdio.h>

#include "MyInitial.h"
#include "PhongProj.h"
//#include "SurfaceProj.h"      // Replace previous line with this line for Project #4

// ***********
// Animation Controls.  
//     Optional: you may customize these for Project #3.
// ***********

// YOU MAY WISH TO RE-DO THIS FOR YOUR CUSTOM ANIMATION.  
double animateIncrement = 0.001;   // Make bigger to speed up animation, smaller to slow it down.
double currentTime = 0.0;         // Current "time" for the animation.
double maxTime = 2.0;             // Time cycles back to 0 after reaching maxTime.

// These two variables control whether running or paused.
//  IT IS OPTIONAL TO INCLUDE THIS FUNCTIONALITY IN YOUR PROGRAMMING ASSIGNMENT
bool spinMode = true;
bool singleStep = false;


// These objects take care of generating and loading VAO's, VBO's and EBO's,
//    rendering ellipsoids and cylinders
// IF YOU ADDED EXTRA TORII, THEY SHOULD BE DECLARED HERE



// Object part
GlGeomSphere unitSphere;
GlGeomCylinder unitCylinder;
GlGeomTorus torus1(6, 6, 0.05f);   // Set default mesh resolutions and inner radius// Initialize multiple tori if they have different inder radii.

                                  
                                  
// **********************
// This sets up a sphere and a cylinder and a torus needed for the "Initial" (the 3-D alphabet letter)
//  This routine is called only once, for the first initialization.
//  IF YOU ADD EXTRA TORII, THEY NEED TO HANDLED HERE.
// **********************
void MySetupInitialGeometries() {
    // Initialize the sphere and cylinder, and give them the vertPos, vertNormal, and vertTexCoords locations.
    MyRemeshGeometries();
    unitSphere.InitializeAttribLocations(vPos_loc,vNormal_loc,vTexcoords_loc);
    unitCylinder.InitializeAttribLocations(vPos_loc, vNormal_loc, vTexcoords_loc);
    torus1.InitializeAttribLocations(vPos_loc, vNormal_loc, vTexcoords_loc);

    check_for_opengl_errors();
}

// *********************
// This is called when geometric shapes are initialized.
// And is called again whenever the mesh resolution changes.
// IF YOU ADD EXTRA TORII, THEY NEED TO BE HANDLED HERE
// ********************
void MyRemeshGeometries() {
    unitSphere.Remesh(meshRes, meshRes);              // Number of slices and stacks both set to meshRes
    unitCylinder.Remesh(meshRes, meshRes, meshRes);   // Number of slices, stacks and rings all set to meshRes
    torus1.Remesh(meshRes, meshRes);                  // Number of rings and number of sides per ring.
}

// *************************************
// Render the initial (3D alphabet letter)
// THIS CODE IS THE CORE PART TO RE_WRITE FOR YOUR 155A PROJECT  ****************************
// ************
void MyRenderInitial() {
    // Compute the "currentTime" for the animation.
    //    As initially implemented, CurrentTime goes from 0.0 to 1.0, and then back to 0.0
    //    THIS IS SPECIFIC TO THE ANIMATION IN THE DEMO.
    //    FOR PROJECT 3 YOU MAY DO SOMETHING DIFFERENT, FOR INSTANCE, SIMILAR TO WHAT 
	//       THE SOLAR SYSTEM PROJECT DID.
    //  
    if (spinMode) {
        currentTime += animateIncrement;
        if (currentTime >= maxTime) {
            currentTime = currentTime - 2*floor(currentTime/maxTime);  // Floor function = round down to nearest integer
        }
        if (singleStep) {
            spinMode = false;       // If in single step mode, turn off future animation
        }
    }

    // Render the letter "X" (Sam's initial) with two cylinders,
    //    Plus a revolving ellipsoid.
   
    // Setup the main Model view matrix
    LinearMapR4 matbase = viewMatrix;              // Base off of viewMatrix
    matbase.Mult_glTranslate(-2.5, 2.0, -2.5);     // Center of the letter

    // Make the X partgreen-ish (YOU ARE ENCOURAGED TO ALTER COLORS)
    myMaterials[0].LoadIntoShaders();

    
    //Third cylinder(|)
    LinearMapR4 zeropoint = matbase;
    zeropoint.Mult_glTranslate(-0.6, 0, 0);
    
    LinearMapR4 mat3 = zeropoint;                                // Modelview matrix for cylinders & sphere
    myMaterials[2].LoadIntoShaders();

    //mat3.Mult_glTranslate(-0.6, 0, 0);         // Translate slightly towards the viewer  
    mat3.Mult_glRotate(currentTime * PI2, 0, 1, 0);
    mat3.Mult_glScale(0.2, 1.8, 0.2);          // Scale the cylinder, to thiner, flater and taller 
    mat3.DumpByColumns(matEntries);
    glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);
    unitCylinder.Render();
    
    // First Cylinder(/)
    LinearMapR4 rotate = zeropoint;
    if (currentTime < 1) rotate.Mult_glRotate(currentTime * PI2, 0, 1, 0);
    rotate.Mult_glTranslate(1.2, 0.9, 0.0);

    LinearMapR4 mat1 = rotate;     
    myMaterials[4].LoadIntoShaders();

    mat1.Mult_glRotate(-PI/4.8, 0.0, 0.0, 1.0); // Rotate -30 degrees
    if (currentTime < 1) mat1.Mult_glRotate(2*currentTime * PI2, 0, 0, 1);
    mat1.Mult_glScale(0.2, 1.0, 0.2);          // Scale the cylinder, to thiner, flater and taller 
    mat1.DumpByColumns(matEntries);
    glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);
    unitCylinder.Render();

    // Second Cylinder(\)
    rotate = zeropoint;
    if (currentTime < 1) rotate.Mult_glRotate(-currentTime * PI2, 0, 1, 0);
    rotate.Mult_glTranslate(1.2, -0.9, 0.0);

    LinearMapR4 mat2 = rotate;                   // Modelview matrix for cylinders & sphere
    myMaterials[4].LoadIntoShaders();

    mat2.Mult_glRotate(PI/4.8, 0.0, 0.0, 1.0); // Rotate -30 degrees
    if (currentTime < 1) mat2.Mult_glRotate(-currentTime * 2 * PI2, 0, 0, 1);
    mat2.Mult_glScale(0.2, 1.0, 0.2);            // Scale the cylinder, to thiner, flater and taller 
    mat2.DumpByColumns(matEntries);
    glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);
    unitCylinder.Render();

    // Render the torus
    myMaterials[3].LoadIntoShaders();

    mat1 = matbase;                              // Back to the main Modelview matrix
    mat1.Mult_glScale(0.3);                   // Uniform scaling
    mat1.Mult_glTranslate(-2, 4.5, 0);
    mat1.Mult_glScale(1, 20, 1);
    mat1.DumpByColumns(matEntries);
    glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);
    torus1.Render();

    mat1.Mult_glTranslate(0, -4, 0);
    mat1.DumpByColumns(matEntries);
    glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);
    torus1.Render();

    // NewNode
    LinearMapR4 spherepos = matbase;
    mat1.Mult_glTranslate(-0.6, currentTime, 0);
    //mat1 = spherepos;
    mat1.Mult_glScale(0.05);
    mat1.DumpByColumns(matEntries);
    glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);
    unitSphere.Render();

    // NewNode2
    LinearMapR4 pos = matbase;
    pos.Mult_glRotate(PI / 4, 0, 0, 1);
    LinearMapR4 sp2 = pos;
    myMaterials[3].LoadIntoShaders();

    sp2.Mult_glRotate(2 * currentTime * PI2,0,1,0);
    sp2.Mult_glTranslate(0, 0, 3.5);
    sp2.Mult_glScale(0.1);
    sp2.DumpByColumns(matEntries);
    glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);
    unitSphere.Render();


    // NewNode3
    pos = matbase;
    pos.Mult_glRotate(-PI / 4, 0, 0, 1);
    LinearMapR4 sp3 = pos;
    myMaterials[3].LoadIntoShaders();

    sp3.Mult_glRotate(2 * currentTime * PI2, 0, 1, 0);
    sp3.Mult_glTranslate(0, 0, 3.5);
    sp3.Mult_glScale(0.1);
    sp3.DumpByColumns(matEntries);
    glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);
    unitSphere.Render();

    
    

    // Render the revolving ellipsoid
    /*glVertexAttrib3f(vColor_loc, 0.6f, 0.4f, 1.0f);  // Blue/Magenta-ish color
    mat1 = spherepos;                              // Back to the main Modelview matrix
    mat1.Mult_glRotate(5*currentTime*PI2, 0.0, 1.0, 0.0);   // PI2 is 2*pi (defined in MathMisc.h)
    mat1.Mult_glTranslate(0.0, 0.0, 1.8);     // Pull towards the viewer (for revolution)
    mat1.Mult_glScale(0.5, 0.2, 1.0);         // Nonuniform scaling  
    mat1.DumpByColumns(matEntries);
    glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);
    unitSphere.Render();*/
}








