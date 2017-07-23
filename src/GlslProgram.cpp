#include "GlslProgram.hpp"

GlslProgram::GlslProgram(void) :
programID(0),
vertexShaderID(0),
fragmentShaderID(0),
numAttributes(0)
{

}

GlslProgram::~GlslProgram(void)
{

}

void    GlslProgram::compileShaders(const std::string &vertexShaderFilePath,
                                    const std::string &fragmentShaderFilePath)
{
    programID = glCreateProgram();

    vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    if (vertexShaderID == 0)
        std::cout << "error, vertex shader failed with NULL" << std::endl;

    fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    if (fragmentShaderID == 0)
        std::cout << "error, fragment shader failed with NULL" << std::endl;


    compileShader(vertexShaderFilePath, vertexShaderID);
    compileShader(fragmentShaderFilePath, fragmentShaderID);
}

void    GlslProgram::linkShaders()
{
    //Attach our shaders to our program
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);

    //Link our program
    glLinkProgram(programID);

    //Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(programID, GL_LINK_STATUS, (int *)&isLinked);
    if(isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

        //The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(programID, maxLength, &maxLength, &infoLog[0]);
        
        //We don't need the program anymore.
        glDeleteProgram(programID);
        //Don't leak shaders either.
        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);

        //Use the infoLog as you see fit.
        std::printf("%s\n", &(infoLog[0]));
        std::cout << "shader link failure" << std::endl;    
    }

    //Always detach shaders after a successful link.
    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
}

GLuint  GlslProgram::getUniformLocation(const std::string &uniformName)
{
    GLuint location = glGetUniformLocation(programID, uniformName.c_str());
    if (location == GL_INVALID_INDEX)
    {
        std::cout << "UniformName: " << uniformName <<
         " not found in shader." << std::endl;
        exit(0);
    }
    return location;
}

void    GlslProgram::use()
{
    glUseProgram(programID);
    for (int i = 0; i < numAttributes; i++) {
        glEnableVertexAttribArray(i);
    }
}

void    GlslProgram::unuse()
{
    glUseProgram(0);
    for (int i = 0; i < numAttributes; i++) {
        glDisableVertexAttribArray(i);
    }
}

void    GlslProgram::update(const Transform &transform, const Camera &camera)
{
    glm::mat4 modelViewProjection = camera.getViewProjection() * transform.getModel();
    //set GL_FALSE to GL_TRUE if matrix must be transposed
    glUniformMatrix4fv(uniforms[TRANSFORM_U], 1, GL_FALSE, &modelViewProjection[0][0]);
}

void    GlslProgram::addAttribute(const std::string attributeName)
{
    glBindAttribLocation(programID, numAttributes++, attributeName.c_str());
}

void    GlslProgram::compileShader(const std::string filepath, GLuint id)
{

    std::fstream vertexFile(filepath);
    if (vertexFile.fail())
    {
        std::cout << "failed to open shader from path: " <<
         filepath << std::endl;
    }
    std::string fileContents = "";
    std::string line;
    while(std::getline(vertexFile, line))
    {
        fileContents += line + "\n";
    }
    vertexFile.close();
    const char *contentsPtr = fileContents.c_str();
    glShaderSource(id, 1, &contentsPtr, nullptr);

    glCompileShader(id);

    GLint   success = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);

    if(success == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

        // Provide the infolog in whatever manor you deem best.
        // Exit with failure.
        glDeleteShader(id); // Don't leak the shader.
        std::printf("%s\n", &(errorLog[0]));
    } 
}