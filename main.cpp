#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

#include "gl_utils.hpp"
#include "program.hpp"
#include "object_vbo.hpp"

MyGL::Program *program;
uint vao_id;

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);TEST_OPENGL_ERROR();
  glBindVertexArray(vao_id);TEST_OPENGL_ERROR();
  glDrawArrays(GL_TRIANGLES, 0, vertex_buffer_data.size());TEST_OPENGL_ERROR();
  glBindVertexArray(0);TEST_OPENGL_ERROR();
  glutSwapBuffers();TEST_OPENGL_ERROR();
}

bool init_glut(int &argc, char *argv[]) {
    glutInit(&argc, argv);TEST_OPENGL_ERROR();
    glutInitContextVersion(4, 5);TEST_OPENGL_ERROR();
    glutInitContextProfile(GLUT_CORE_PROFILE);TEST_OPENGL_ERROR();
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);TEST_OPENGL_ERROR();
    glutInitWindowSize(1024, 1024);TEST_OPENGL_ERROR();
    glutInitWindowPosition (10, 10);TEST_OPENGL_ERROR();
    glutCreateWindow("Paul Galand");TEST_OPENGL_ERROR();

    glutDisplayFunc(display);TEST_OPENGL_ERROR();

    return true;

}

bool init_glew() {
    return glewInit() == GLEW_OK;
}

bool init_GL() {
    glEnable(GL_DEPTH_TEST);TEST_OPENGL_ERROR();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);TEST_OPENGL_ERROR();
    glEnable(GL_CULL_FACE);TEST_OPENGL_ERROR();
    glClearColor(.2, .2, .2, 1.);TEST_OPENGL_ERROR();
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    glPixelStorei(GL_PACK_ALIGNMENT,1);
    return true;
}

bool init_object() {
    int color_location = glGetUniformLocation(program->get_program_id(), "color");TEST_OPENGL_ERROR();

    if (color_location == -1)
        return false;

    glUniform3f(color_location, 1., 1., 1.);TEST_OPENGL_ERROR();

    uint vbo_id[1];

    int vertex_position = glGetAttribLocation(program->get_program_id(), "position");TEST_OPENGL_ERROR();

    if (vertex_position == -1)
        return false;

    glGenVertexArrays(1, &vao_id);TEST_OPENGL_ERROR();
    glBindVertexArray(vao_id);TEST_OPENGL_ERROR();

    glGenBuffers(1, vbo_id);TEST_OPENGL_ERROR();

    glBindBuffer(GL_ARRAY_BUFFER, vbo_id[0]);TEST_OPENGL_ERROR();
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(float), vertex_buffer_data.data(), GL_STATIC_DRAW);TEST_OPENGL_ERROR();
    glVertexAttribPointer(vertex_position, 3, GL_FLOAT, GL_FALSE, 0, 0);TEST_OPENGL_ERROR();
    glEnableVertexAttribArray(vertex_position);TEST_OPENGL_ERROR();

    glBindVertexArray(0);TEST_OPENGL_ERROR();
    return true;
}

bool init_pov() {
    int world_camera_location = glGetUniformLocation(program->get_program_id(), "world_camera");TEST_OPENGL_ERROR();

    if (world_camera_location == -1)
        return false;

    MyGL::Matrix4 matrix = MyGL::lookAt(0, 4, 0, 2, 0, 1, 0, 0, 1);
    glUniformMatrix4fv(world_camera_location, 1, false, matrix.get_ptr());TEST_OPENGL_ERROR();

    int projection_location = glGetUniformLocation(program->get_program_id(), "projection");TEST_OPENGL_ERROR();

    if (projection_location == -1)
        return false;

    matrix = MyGL::frustum(-3, 3, -3, 3, 2, 300);
    glUniformMatrix4fv(projection_location, 1, false, matrix.get_ptr());TEST_OPENGL_ERROR();

    return true;
}

bool init_shaders() {
    std::string vertex_src = "vertex.shd";
    std::string fragment_src = "fragment.shd";
    program = MyGL::Program::make_program(vertex_src, fragment_src);

    if (program == NULL)
        return false;

    if (!program->get_program_id()) {
        delete program;
        return false;
    }

    glUseProgram(program->get_program_id());TEST_OPENGL_ERROR();
    return true;
}

int main(int argc, char *argv[]) {
    if (!init_glut(argc, argv)) {
        std::cerr << "Having trouble initializing glut\n";
        return 1;
    }

    if (!init_glew()) {
        std::cerr << "Having trouble initializing glew\n";
        return 2;
    }

    if (!init_GL()) {
        std::cerr << "Having trouble initializing GL\n";
        return 3;
    }

    if (!init_shaders()) {
        std::cerr << "Having trouble initializing shaders\n";
        return 4;
    }

    if (!init_pov()) {
        std::cerr << "Having trouble initializing pov\n";
        return 5;
    }

    if (!init_object()) {
        std::cerr << "Having trouble initializing object\n";
        return 6;
    }

    glutMainLoop();
}
