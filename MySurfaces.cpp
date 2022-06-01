//
//  MySurfaces.cpp
//
//   Sets up and renders 
//     - the ground plane, and
//     - the surface of rotation
//   for the Math 155A project #4.
//
//   Comes supplied with the code for Sam Buss's "X".
//


// Use the static library (so glew32.dll is not needed):
#define GLEW_STATIC
#include <GL/glew.h> 
#include <GLFW/glfw3.h>

#include "LinearR3.h"		// Adjust path as needed.
#include "LinearR4.h"		// Adjust path as needed.
#include "MathMisc.h"       // Adjust path as needed

#include "MySurfaces.h"
#include "PhongProj.h"


// ************************
// General data helping with setting up VAO (Vertex Array Objects)
//    and Vertex Buffer Objects.
// ***********************
const int NumObjects = 2;
const int iFloor = 0;
const int iCircularSurf = 1;

unsigned int myVBO[NumObjects];  // a Vertex Buffer Object holds an array of data
unsigned int myVAO[NumObjects];  // a Vertex Array Object - holds info about an array of vertex data;
unsigned int myEBO[NumObjects];  // a Element Array Buffer Object - holds an array of elements (vertex indices)

// **********************
// This sets up geometries needed for the "Initial" (the 3-D alphabet letter)
//  It is called only once.
// **********************
void MySetupSurfaces() {
    // Initialize the VAO's, VBO's and EBO's for the ground plane,
    // and the surface of rotation. Give them the "aPos" location,
    // and the "aNormal" location in the shader program.
    // No data is loaded into the VBO's or EBO's until the "Remesh"
    //   routines are called.

    // For the floor:
    // Allocate the needed Vertex Array Objects (VAO's),
    //      Vertex Buffer Objects (VBO's) and Element Array Buffer Objects (EBO's)
    // Since the floor has normal (0,1,0) everywhere, it will be given as
    // generic vertex attribute, not loaded in the VBO as a per-vertex value.
    // The color is also a generic vertex attribute.
    glGenVertexArrays(NumObjects, &myVAO[0]);
    glGenBuffers(NumObjects, &myVBO[0]);
    glGenBuffers(NumObjects, &myEBO[0]);

    glBindVertexArray(myVAO[iFloor]);
    glBindBuffer(GL_ARRAY_BUFFER, myVBO[iFloor]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myEBO[iFloor]);

    glVertexAttribPointer(vPos_loc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Store vertices in the VBO
    glEnableVertexAttribArray(vPos_loc);									// Enable the stored vertices
 
    // For the circular surface:
    // Allocate the needed VAO, VBO< EBO
    // The normal vector is specified separately for each vertex. (It is not a generic attribute.)
    // The color is still a generic vertex attribute.
    glBindVertexArray(myVAO[iCircularSurf]);
    glBindBuffer(GL_ARRAY_BUFFER, myVBO[iCircularSurf]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myEBO[iCircularSurf]);

    glVertexAttribPointer(vPos_loc, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);	// Store vertices in the VBO
    glEnableVertexAttribArray(vPos_loc);									// Enable the stored vertices
    glVertexAttribPointer(vNormal_loc, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // Store normals in the VBO
    glEnableVertexAttribArray(vNormal_loc);                                 // Enabled the stored normals (so they are not generic)

    // No data has been loaded into the VBO's yet.
    // This is done next by the "Remesh" routines.

    MyRemeshSurfaces();
    
    check_for_opengl_errors();      // Watch the console window for error messages!
}

// **********************************************
// MODIFY THIS ROUTINE TO CALL YOUR OWN CODE IN
//   MyRemeshFloor AND MyRemeshCircularSurf
// INSTEAD OF THE "DEMO" VERSIONS.
// **********************************************

void MyRemeshSurfaces() 
{
    // WRITE MyRemeshFloor (see below) AND USE IT INSTEAD OF RemeshPlaneDemo
    //RemeshFloorDemo();
    MyRemeshFloor();

    // WRITE MyRemeshCircularSurf (see below) AND USE IT INSTEAD OF RemeshCircularDemo
    //RemeshCircularDemo();
    MyRemeshCircularSurf();

    check_for_opengl_errors();      // Watch the console window for error messages!
}

// **********************************************
// MODIFY THIS ROUTINE TO CALL YOUR OWN CODE IN
//   MyRemeshFloor AND MyRemeshCircularSurf
// INSTEAD OF THE "DEMO" VERSIONS.
// **********************************************

void MyRenderSurfaces() {
    // WRITE MyRemeshFloor (see below) AND USE IT INSTEAD OF RemeshPlaneDemo
    //RenderFloorDemo();
    MyRenderFloor();

    // WRITE MyRemeshCircularSurf (see below) AND USE IT INSTEAD OF RemeshCircularDemo
    //RenderCircularDemo();
    MyRenderCircularSurf();

    check_for_opengl_errors();      // Watch the console window for error messages!
}

// *********************************************
// THE CODE FOR THE NEXT FOUR "Demo" ROUIINTES BELOW GIVES SIMPLE FIXED SIZE OBJECTS:
// A plane gridded into 4x4 array of rectangles (triangulated)
// and Circular piece with 4 slices, and 4 rings.
// THIS CODE WILL NOT BE USED IN YOUR PROGRAMMING SOLUTION.
// INSTEAD, FINISH WRITING MyRemeshFloor() and MyRemeshCircularSurf() below.
// *********************************************************

// Make the floor a 4x4 grid of triangulated quads.
// Render it as four triangle strips.
void RemeshFloorDemo()
{
    // Floor vertices.
    float floorVerts[][3] = {
        { -5.0f, 0.0f, -5.0f }, { -2.5f, 0.0f, -5.0f }, { 0.0f, 0.0f, -5.0f }, { 2.5f, 0.0f, -5.0f }, { 5.0f, 0.0f, -5.0f },  // Back row
        { -5.0f, 0.0f, -2.5f }, { -2.5f, 0.0f, -2.5f }, { 0.0f, 0.0f, -2.5f }, { 2.5f, 0.0f, -2.5f }, { 5.0f, 0.0f, -2.5f },  // Fourth row
        { -5.0f, 0.0f,  0.0f }, { -2.5f, 0.0f,  0.0f }, { 0.0f, 0.0f,  0.0f }, { 2.5f, 0.0f,  0.0f }, { 5.0f, 0.0f,  0.0f },  // Third row
        { -5.0f, 0.0f,  2.5f }, { -2.5f, 0.0f,  2.5f }, { 0.0f, 0.0f,  2.5f }, { 2.5f, 0.0f,  2.5f }, { 5.0f, 0.0f,  2.5f },  // Second row
        { -5.0f, 0.0f,  5.0f }, { -2.5f, 0.0f,  5.0f }, { 0.0f, 0.0f,  5.0f }, { 2.5f, 0.0f,  5.0f }, { 5.0f, 0.0f,  5.0f },  // Front row
    };
    // Floor elements (indices to vertices in a triangle strip)
    unsigned int floorElements[] = {
        0,5,1,6,2,7,3,8,4,9,            // Elements for first triangle strip (back strip)
        5,10,6,11,7,12,8,13,9,14,       // Elements for second triangle strip
        10,15,11,16,12,17,13,18,14,19,  // Elements for third triangle strip
        15,20,16,21,17,22,18,23,19,24,  // Elements for fourth triangle strip (front strip)
    };
    glBindBuffer(GL_ARRAY_BUFFER, myVBO[iFloor]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(floorVerts), floorVerts, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myEBO[iFloor]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(floorElements), floorElements, GL_STATIC_DRAW);
}

void RemeshCircularDemo()
{
    // Circular surface as four triangle strips (low resolution)
    // Both vertex positions AND normal vectors
    // Note how this corresponds to the call to glVertexAttribPointer and glEnableVertexAttribArray
    //      in MySetupSurfaces() above.
    float circularVerts[] = {
        // Vertex positions     Normals (please make them *unit* vectors)
        0.0f, 1.0f, 0.0f,       0.0f, 1.0f, 0.0f,        // Central vertex
        0.0f, 0.866f, 0.5f,     0.0f, 0.866f, 0.5f,     // Over positive z axis
        0.0f, 0.5f, 0.866f,     0.0f, 0.5f, 0.866f,     
        0.5f, 0.866f, 0.0f,     0.5f, 0.866f, 0.0f,     // Over positive x-axis
        0.866f, 0.5f, 0.0f,     0.866f, 0.5f, 0.0f,
        0.0f, 0.866f, -0.5f,    0.0f, 0.866f, -0.5f,    // Over negative z axis
        0.0f, 0.5f, -0.866f,    0.0f, 0.5f, -0.866f,
        -0.5f, 0.866f, 0.0f,    -0.5f, 0.866f, 0.0f,    // Over negative x-axis
        -0.866f, 0.5f, 0.0f,    -0.866f, 0.5f, 0.0f,
    };
    // Circular elements (indices to vertices in triangle strips)
    unsigned int circularElements[] = {
        0, 1, 3, 2, 4,            // Elements for first triangle strip 
        0, 3, 5, 4, 6,            // Elements for second triangle strip
        0, 5, 7, 6, 8,            // Elements for third triangle strip
        0, 7, 1, 8, 2            // Elements for fourth triangle strip 
    };
    glBindVertexArray(myVAO[iCircularSurf]);
    glBindBuffer(GL_ARRAY_BUFFER, myVBO[iCircularSurf]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(circularVerts), circularVerts, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myEBO[iCircularSurf]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(circularElements), circularElements, GL_STATIC_DRAW);
}

void RenderFloorDemo()
{
    glBindVertexArray(myVAO[iFloor]);

    // Set the uniform values (they are not stored with the VAO and thus must be set again everytime
    glVertexAttrib3f(vNormal_loc, 0.0, 1.0, 0.0);    // Generic vertex attribute: Normal is (0,1,0) for the floor.
    myMaterials[0].LoadIntoShaders();
    viewMatrix.DumpByColumns(matEntries);
    glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);

    // Draw the four triangle strips
    glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT, (void*)0);                              // Draw first triangle strip (back strip)
    glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT, (void*)(10 * sizeof(unsigned int)));    // Draw second triangle strip
    glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT, (void*)(20 * sizeof(unsigned int)));    // Draw third triangle strip
    glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT, (void*)(30 * sizeof(unsigned int)));    // Draw fourth triangle strip (front strip)
}

void RenderCircularDemo()
{
    glBindVertexArray(myVAO[iCircularSurf]);

    // Calculute the model view matrix for the circular surface
    LinearMapR4 matDemo = viewMatrix;
    matDemo.Mult_glTranslate(2.5, 1.0, 2.5);     // Center in the front right quadrant & raise up
    matDemo.Mult_glScale(3.0, 1.0, 3.0);         // Increase the circular diameter

    // Set the uniform values (they are not stored with the VAO and thus must be set again everytime
    myMaterials[0].LoadIntoShaders();

    matDemo.DumpByColumns(matEntries);
    glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);

    // Draw the four triangle strips
    glDrawElements(GL_TRIANGLE_STRIP, 5, GL_UNSIGNED_INT, (void*)0);                             // Draw first triangle strip 
    glDrawElements(GL_TRIANGLE_STRIP, 5, GL_UNSIGNED_INT, (void*)(5 * sizeof(unsigned int)));    // Draw second triangle strip
    glDrawElements(GL_TRIANGLE_STRIP, 5, GL_UNSIGNED_INT, (void*)(10 * sizeof(unsigned int)));   // Draw third triangle strip
    glDrawElements(GL_TRIANGLE_STRIP, 5, GL_UNSIGNED_INT, (void*)(15 * sizeof(unsigned int)));   // Draw fourth triangle strip 

}


// *********************************************
// THE CODE BELOW MUST BE WRITTEN FOR PROJECT 4.
// *********************************************

void MyRemeshFloor() {
    int numFloorVerts = (meshRes + 1) * (meshRes + 1);
    float* floorVerts = new float[3 * numFloorVerts];

    int numFloorElts = meshRes * 2 * (meshRes + 1);
    unsigned int* floorElements = new unsigned int[numFloorElts];
    float distance = 10.000f / meshRes;


    for (int row = 0; row < meshRes + 1; row++) {
        for (int i = row * 3 * (meshRes + 1); i < (row + 1) * 3 * (meshRes + 1); i += 3) {
            floorVerts[i] = (i / 3) * distance - row * 10 - row * distance - 5;
            floorVerts[i + 1] = 0;
            floorVerts[i + 2] = row * distance - 5;
        }
    }

    floorElements[0] = 0;
    int val = 1;
    int num = meshRes;

    for (int i = 1; i < (meshRes + 1) * (meshRes) * 2; i++) {
        if (i % 2 == 0) floorElements[i] = val++;
        else floorElements[i] = 1 + num++;
    }

    glBindBuffer(GL_ARRAY_BUFFER, myVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, 3 * (meshRes + 1) * (meshRes + 1) * sizeof(float), floorVerts, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myEBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * (meshRes) * (meshRes + 1) * sizeof(float), floorElements, GL_STATIC_DRAW);

    delete[] floorVerts;
    delete[] floorElements;
}

void MyRemeshCircularSurf()
{
    float r = PI4;
    float each_r = r / meshRes;
    float angle = PI2 / meshRes;
    int numsurfverts = 3 * (meshRes + 1);
    float height = 0;
    

    float* surfverts = new float[6 * ((meshRes) * meshRes+1)];
    
    for (int cir = 0; cir < meshRes; cir++) {
        float cur_angle = 0.00f;
        for (int i = (cir * meshRes * 6); i + 5 < (6 * (cir + 1) * meshRes) + 6; i += 6) {
      
            surfverts[i] =   r * cos(cur_angle);
            surfverts[i + 2] =  -r * sin(cur_angle);
            
            if (cur_angle == 0.00f) { 
                float x = r;
                height = 1+(1 + 0.08 * x * x) * sin(x) / x;
            }
            float R = sinf(r) * (0.08 - (1 / (r * r))) + cosf(r) * ((1 / r) + (0.08 * r));
            surfverts[i + 1] = height;
            surfverts[i + 3] = -R*cos(cur_angle);
            surfverts[i + 4] = 1;
            surfverts[i + 5] = R*sin(cur_angle);

            cur_angle = cur_angle + angle;
        }
        r = r - each_r;
    }
    
    int last = 6 * meshRes * meshRes + 5;
    surfverts[last - 5] = 0;
    surfverts[last - 4] = 2;
    surfverts[last - 3] = 0;
    surfverts[last - 2] = 0;
    surfverts[last - 1] = 1;
    surfverts[last] = 0;

    unsigned int* surfelements = new unsigned int[meshRes*meshRes*2+meshRes];
    int piece = 0;
    int bias = 0;

    for (int j = 0; j < meshRes; j++) {
        int floor = 0;
        for (int i = piece*meshRes*2+bias; i < meshRes*2*(piece+1)+bias; i += 2) {
            surfelements[i] = floor*meshRes+piece;
            surfelements[i + 1] = surfelements[i] + 1;
            for (int n = 0; n < meshRes+1;n++) {
                if (surfelements[i + 1] == n*meshRes)surfelements[i + 1] = (n-1)*meshRes;
            }
            floor++;
        }
        surfelements[meshRes * 2 * (piece + 1) + bias] = meshRes*meshRes;
        bias++;
        piece++;
    }
    /*
    printf("floorVerts:\n");
    for (int k = 0; k/2 < (meshRes) * (meshRes) + 1; k+=2) {
        printf("k =%3d:  pos = %7.4f, %7.4f, %7.4f. \n", k/2, surfverts[3 * k], surfverts[3 * k + 1], surfverts[3 * k + 2]);
    }
    printf("floorElements:\n");
    for (int k = 0; k < 2*meshRes*meshRes+meshRes+1; k++) {
        printf("%d, ", surfelements[k]);
    }
    printf("\n");
    */
    glBindBuffer(GL_ARRAY_BUFFER, myVBO[1]);
    glBufferData(GL_ARRAY_BUFFER, 6 * (meshRes*meshRes+1) * sizeof(float), surfverts, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myEBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,( 2 * meshRes * meshRes + meshRes) * sizeof(float), surfelements, GL_STATIC_DRAW);    
}

void MyRenderFloor()
{
    glBindVertexArray(myVAO[0]);
    // Set the uniform values (they are not stored with the VAO and thus must be set again everytime
    glVertexAttrib3f(vNormal_loc, 0.0, 1.0, 0.0);    // Generic vertex attribute: Normal is (0,1,0) for the floor.
    myMaterials[0].LoadIntoShaders();

    viewMatrix.DumpByColumns(matEntries);
    glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);

    // Draw the four triangle strips
    //glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT, (void*)0);                              
    for (int i = 0; i < meshRes; i++) {
        glDrawElements(GL_TRIANGLE_STRIP, 2 * (meshRes + 1), GL_UNSIGNED_INT, (void*)( 2 * i * (meshRes + 1)*sizeof(unsigned int)));
    }
}

void MyRenderCircularSurf()
{
    glBindVertexArray(myVAO[1]);
    LinearMapR4 matDemo = viewMatrix;
    matDemo.Mult_glTranslate(2.4, 0.7, 2.5);     // Center in the front right quadrant & raise up
    matDemo.Mult_glScale(0.35, 0.7, 0.35);         // Increase the circular diameter
    
    //glVertexAttrib3f(vNormal_loc, 0.0, 1.0, 0.0);    // Generic vertex attribute: Normal is (0,1,0) for the floor.
    myMaterials[1].LoadIntoShaders();

    matDemo.DumpByColumns(matEntries);
    glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);
    

    // Draw the four triangle strips
    
    for (int i = 0; i < meshRes; i++) {
        glDrawElements(GL_TRIANGLE_STRIP,  2*meshRes+1 , GL_UNSIGNED_INT, (void*)(i*( 2*meshRes+1 ) * sizeof(unsigned int)));
    }
}

