#include <GL/glut.h>
#include <cmath> // For sin and cos functions

// Global variable to keep track of the current angle of rotation
float currentAngle = 0.0f;

// Function to convert degrees to radians
float degreesToRadians(float degrees) {
    return degrees * M_PI / 180.0f;
}

// Function to rotate a 2D Quad around a pivot point
void rotateQuad(float quad[4][2], float angle, float pivot[2]) {
    float radianAngle = degreesToRadians(angle); // Convert the angle to radians
    float cosAngle = cos(radianAngle); // Calculate cosine of the angle
    float sinAngle = sin(radianAngle); // Calculate sine of the angle

    for (int i = 0; i < 4; ++i) {
        // Translate each vertex to the pivot
        float x = quad[i][0] - pivot[0];
        float y = quad[i][1] - pivot[1];

        // Apply rotation
        float rotatedX = x * cosAngle - y * sinAngle;
        float rotatedY = x * sinAngle + y * cosAngle;

        // Translate the vertex back
        quad[i][0] = rotatedX + pivot[0];
        quad[i][1] = rotatedY + pivot[1];
    }
}

// Function to draw the original quad in gray for reference
void drawOriginalQuad(float quad[4][2]) {
    glColor3f(0.5f, 0.5f, 0.5f); // Gray color for the original quad
    glBegin(GL_QUADS);
    for (int i = 0; i < 4; ++i) {
        glVertex2f(quad[i][0], quad[i][1]); // Draw each vertex
    }
    glEnd();
}

// Function to handle keyboard input for rotating the quad
void handleKeyPress(unsigned char key, int x, int y) {
    if (key == 'r' || key == 'R') {
        currentAngle += 5.0f; // Increase rotation by 5 degrees
        if (currentAngle >= 360.0f) {
            currentAngle -= 360.0f; // Reset angle after 360 degrees
        }
    }
    glutPostRedisplay(); // Redraw the scene after updating the angle
}

// Example usage in a display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen

    // Define a quad (4 vertices)
    float quad[4][2] = {{-0.5f, -0.5f}, {0.5f, -0.5f}, {0.5f, 0.5f}, {-0.5f, 0.5f}};
    float originalQuad[4][2] = {{-0.5f, -0.5f}, {0.5f, -0.5f}, {0.5f, 0.5f}, {-0.5f, 0.5f}}; // For visualization

    // Define a pivot point
    float pivot[2] = {0.0f, 0.0f};

    // Rotate the quad by the current angle
    rotateQuad(quad, currentAngle, pivot);

    // Draw the original quad for reference
    drawOriginalQuad(originalQuad);

    // Draw the rotated quad in red
    glColor3f(1.0f, 0.0f, 0.0f); // Red color for the rotated quad
    glBegin(GL_QUADS);
    for (int i = 0; i < 4; ++i) {
        glVertex2f(quad[i][0], quad[i][1]); // Draw the rotated quad
    }
    glEnd();

    glFlush(); // Display everything
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Rotate Quad Example");
    glClearColor(0.0, 0.0, 0.0, 0.0); // Set the background color to black
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // Set up orthographic projection for 2D space
    glutDisplayFunc(display); // Register display function to draw
    glutKeyboardFunc(handleKeyPress); // Register keyboard function for handling input
    glutMainLoop(); // Start the main loop to handle events
    return 0;
}
