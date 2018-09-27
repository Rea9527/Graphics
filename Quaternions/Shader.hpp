

#ifndef shader_hpp
#define shader_hpp


#include <iostream>
#include <vector>
#include <string>
// glew
#define GLEW_STATIC
#include <GL/glew.h>

//glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class Shader {
public:
    // program id
    GLuint Program;
    
    Shader();
    // create vertex and fragment shaders by paths
    Shader(string vertexPath, string fragmentPath);
    
    GLint getUniformLocation(string name);
    

    void loadMVP(glm::mat4 mvp);
    
    //set
    void setMat4(GLuint loc, glm::mat4 mat);
    void setInt(GLuint loc, GLint num);
    void setMat4(string name, glm::mat4 mat);
    void setInt(string name, GLint num);
    void setVec2(string name, glm::vec2 vec);
    void setVec3(string name, glm::vec3 vec);
    void setVec4(string name, glm::vec4 vec);

    // run and stop program
    void Use();
    void Stop();
    
private:
    GLuint mvpLoc;
    
};

#endif /* shader_hpp */
