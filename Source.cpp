#include "Angel.h"
#include "Sphere.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <random>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"



typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

float bo=0;

Sphere sphere1(0.3f);
Sphere sphere2(0.9f);
GLuint vao, vbo1, ibo1,vbo2,ibo2, vPosition, transAttrib, program, vNormal, modelUnifrom, viewUnifrom, projectionUnifrom, cameraUnifrom, vTexture, texture1, t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,tf,tb,st,ring,bomb,F,speedd;
glm::mat4 trans;
float speed = 0.1f, yaw = -90.0f;
float translate = 0.f;
//float factor = 0.0001;
glm::mat4 model;
glm::vec3 cameraPos, cameraTarget, cameraDirection, cameraRight, cameraUp, cameraFront;
float ra1,ra2,ra3,ra4,ra5,ra6,ra7,ra8,ra10=0.0;
float shx=0.1, shy=0.05, shz=0.05;
float thx =0.0, thy = 0.0, thz = 2.0;
float tux = 0.0, tuy = 0.0, tuz = 0.0;
glm::mat4 view, projection;
Sphere ship(0.05);
float fuel = 2000;
float timer = 0;
float fx = 1.0, fy = -0.2, fz = 1.0;
float x[10];
float y[10];
float z[10];
float x2[10];
float y2[10];
float z2[10];
float x3[10];
float y3[10];
float z3[10];
int fuel2 = 20000;
float flagld = 0;
float flagDis[10];
float flagDis3[10];
float vn = 0.0;
float flagvn = 0;


float vx = 0.0, vy = 0.0, vz = 0.0;


//float  distance_of_ship_from_camera = 0.2;
float fuelc = 125;
float tfx=-0.8, tfy=0.8, tfz=0.0, sfx = 0.5

, sfy = 0.5, sfz = 0.3;
float time2 = 0;


void ds(GLuint& vao, GLuint& vbo2, GLuint& ibo2, Sphere& sphere2)
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glBufferData(GL_ARRAY_BUFFER, sphere2.getInterleavedVertexSize(), sphere2.getInterleavedVertices(), GL_STATIC_DRAW);
    glGenBuffers(1, &ibo2);
    glGenBuffers(1, &vbo2);
    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glBufferData(GL_ARRAY_BUFFER, sphere2.getInterleavedVertexSize(), sphere2.getInterleavedVertices(), GL_STATIC_DRAW);
    glGenBuffers(1, &ibo2);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphere2.getIndexSize(), sphere2.getIndices(), GL_STATIC_DRAW);
}

void dis(GLuint& vbo2, GLuint& ibo2, Sphere& sphere2, float tx, float ty, float tz, float rotationAngle,GLuint tex,float &sx,float &sy ,float &sz,glm::mat4 view)
{
    glUniformMatrix4fv(viewUnifrom, 1, GL_FALSE, glm::value_ptr(view));
    glUniform3fv(cameraUnifrom, 1, glm::value_ptr(cameraPos));
    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo2);
    glBindTexture(GL_TEXTURE_2D, tex);//texture


    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, sphere2.getInterleavedStride(), BUFFER_OFFSET(0));
    glVertexAttribPointer(vNormal, 3, GL_FLOAT, false, sphere2.getInterleavedStride(), (void*)(3 * sizeof(float)));

    glVertexAttribPointer(vTexture, 2, GL_FLOAT, false, sphere2.getInterleavedStride(), (void*)(6 * sizeof(float)));


    trans = glm::mat4(1.0f);
     trans = glm::rotate(trans, glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));
    trans = glm::translate(trans, glm::vec3(tx, ty, tz));
    trans = glm::scale(trans, glm::vec3(sx, sy, sz));
    trans = glm::rotate(trans, glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(transAttrib, 1, GL_FALSE, glm::value_ptr(trans));
    glUniformMatrix4fv(modelUnifrom, 1, GL_FALSE, glm::value_ptr(trans));
    
    glDrawElements(GL_TRIANGLES, sphere2.getIndexCount(), GL_UNSIGNED_INT, (void*)0);
    //  glBindTexture(GL_TEXTURE_2D, texture1);
}
void initLight()
{
    point4 light_direction1(-0.35, 0.0, 0.0f, 1.0);
    point4 light_direction2(0.35, 0.0, 0.0f, 1.0);
    color4 light_ambient(0.5f, 0.5f, 0.5f, 1.0);
    color4 light_diffuse(1.0, 1.0, 0.0, 1.0); // Yellow for diffuse component
    color4 light_specular(1.0, 1.0, 1.0, 1.0); // White for specular component
 //.....+...................................................................+....//
    // Set up lights[0]
    glUniform4fv(glGetUniformLocation(program, "directionalLights[0].ambient"), 1, light_ambient);
    glUniform4fv(glGetUniformLocation(program, "directionalLights[0].diffuse"), 1, light_diffuse);
    glUniform4fv(glGetUniformLocation(program, "directionalLights[0].specular"), 1, light_specular);
    glUniform4fv(glGetUniformLocation(program, "directionalLights[0].direction"), 1, light_direction1);

    // Set up lights[1]
    glUniform4fv(glGetUniformLocation(program, "directionalLights[1].ambient"), 1, light_ambient);
    glUniform4fv(glGetUniformLocation(program, "directionalLights[1].diffuse"), 1, light_diffuse);
    glUniform4fv(glGetUniformLocation(program, "directionalLights[1]].specular"), 1, light_specular);
    glUniform4fv(glGetUniformLocation(program, "directionalLights[1].direction"), 1, light_direction2);
    //here i was think to add 4 light sources insted of 2 but it doesont look good as i excpected so i discard the idea 

    //// Set up lights[2]
    //glUniform4fv(glGetUniformLocation(program, "lights[2].ambient"), 1, light_ambient);
    //glUniform4fv(glGetUniformLocation(program, "lights[2].diffuse"), 1, light_diffuse);
    //glUniform4fv(glGetUniformLocation(program, "lights[2].specular"), 1, light_specular);
    //glUniform4fv(glGetUniformLocation(program, "lights[2].direction"), 1, light_direction3);

    //// Set up lights[3]
    //glUniform4fv(glGetUniformLocation(program, "lights[3].ambient"), 1, light_ambient);
    //glUniform4fv(glGetUniformLocation(program, "lights[3].diffuse"), 1, light_diffuse);
    //glUniform4fv(glGetUniformLocation(program, "lights[3].specular"), 1, light_specular);
    //glUniform4fv(glGetUniformLocation(program, "lights[3].direction"), 1, light_direction4);

    color4 material_ambient(0.5, 0.5, 0.5, 1.0); // Gray for material ambient
    color4 material_diffuse(1.0, 1.0, 1.0, 1.0); // White for material diffuse
    color4 material_specular(1.0, 1.0, 1.0, 1.0); // White for material specular
    float material_shininess = 100.0;

    // Set up material
    glUniform4fv(glGetUniformLocation(program, "material.ambient"), 1, material_ambient);
    glUniform4fv(glGetUniformLocation(program, "material.diffuse"), 1, material_diffuse);
    glUniform4fv(glGetUniformLocation(program, "material.specular"), 1, material_specular);
    glUniform1f(glGetUniformLocation(program, "material.shininess"), material_shininess);
}
void images(const char* im, GLuint & texture1)
{
    stbi_set_flip_vertically_on_load(true);

    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //GL_LINEAR_MIPMAP
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, channels;
   unsigned char* data1 = stbi_load(im, &width, &height, &channels, 0);
    if (data1)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data1);
}
//in this function i send images to the images function to define thim 
void initTexture()
{
    images("sun.jpg",texture1);
    images("earth_daymap.jpg", t2);
    images("jupiter.jpg", t3);
    images("mars.jpg", t4);
    images("neptune.jpg", t5);
    images("saturn.jpg", t6);
    images("venus_surface.jpg", t7);
    images("mercury.jpg", t8);
    images("uranus.jpg", t9);
    images("z.jpg", t10);
    images("z.jpg", tf);
    images("b.jpg", tb);
    images("satrs.jpg", st);
    images("ring.png", ring);
    images("w.jpg", bomb);
    images("w22.jpg",F);
    images("90.jpg",speedd);

}


void init()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    ds(vao, vbo1, ibo1, sphere1);
    ds(vao, vbo2, ibo2, sphere2);

     program = InitShader("vshader.glsl", "fshader.glsl");
    glUseProgram(program);

    vPosition = glGetAttribLocation(program, "vertexPosition");
    glEnableVertexAttribArray(vPosition);

    transAttrib = glGetUniformLocation(program, "trans");

    glEnableVertexAttribArray(vPosition);

    vNormal = glGetAttribLocation(program, "vertexNormal");
    glEnableVertexAttribArray(vNormal);

    vTexture = glGetAttribLocation(program, "vertexTexture");
    glEnableVertexAttribArray(vTexture);

    modelUnifrom = glGetUniformLocation(program, "model");
    viewUnifrom = glGetUniformLocation(program, "view");
    projectionUnifrom = glGetUniformLocation(program, "projection");
    cameraUnifrom = glGetUniformLocation(program, "camera");
    cameraPos = glm::vec3(2.0, 0.0f, 2.0f);
    cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    cameraDirection = glm::normalize(cameraPos - cameraTarget);
    cameraRight = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), cameraDirection));
    cameraUp = glm::cross(cameraDirection, cameraRight);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    projection = glm::perspective(glm::radians(45.f), 1.f, 0.1f, 100.0f);
    glUniformMatrix4fv(projectionUnifrom, 1, GL_FALSE, glm::value_ptr(projection));
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> dis(-40.0, 40.0), dis2(0.0, 1.0);

    

    for (int i = 0; i < 10; ++i) {
        x[i] = dis(gen);
        y[i] = dis(gen);
        z[i] = dis2(gen);
        flagDis[i] = 1;
    }

    std::random_device rd2;
    std::mt19937 gen2(rd2());

    std::uniform_real_distribution<float> dis3(-40.0, 40.0), dis4(0.0, 1.0);

   

    for (int i = 0; i < 10; ++i) {
        x2[i] = dis3(gen2);
        y2[i] = dis3(gen2);
        z2[i] = dis4(gen2);
        
    }
    std::random_device rd3;
    std::mt19937 gen3(rd3());

    std::uniform_real_distribution<float> dis5(-30.0, 30.0), dis6(0.0, 1.0);
   


    for (int i = 0; i < 10; ++i) {
        x3[i] = dis5(gen3);
        y3[i] = dis5(gen3);
        z3[i] = dis6(gen3);
        flagDis3[i] = 1;
    }
    initLight();
    initTexture();
   

  
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);

}
float tnx = 15.0, tny = 0.0, tnz = 0.6;
//this flag to know if itis bomb or itis fuel
void DetectCollision(float &tux,float &tuz,float &tuy)
{
    float d = 1.0 + tux;
    float dy = 1.0 + tuy;
    float dz = 2.0+ abs(tuz);
    if (cameraPos.x >= tux-1.5 && cameraPos.x <= tux+1.5&& cameraPos.z >tuz-1.5&& cameraPos.z<=tuz+1.5)
    {
        if (cameraPos.y >= tuy-1.5 && cameraPos.y <= tuy+1.5)
        {
                fuel2 = 0;
                //std::cout << "test";
        }
    }
   
}
void DetectCollision2(float& tux, float& tuz, float& tuy,float &flagd)
{
    float d = 1.0 + tux;
    float dy = 1.0 + tuy;
    float dz = 2.0 + abs(tuz);
    if (flagd == 1)
    {
        if (cameraPos.x >= tux - 1.5 && cameraPos.x <= tux + 1.5 && cameraPos.z > tuz - 1.5 && cameraPos.z <= tuz + 1.5)
        {
            if (cameraPos.y >= tuy - 1.5 && cameraPos.y <= tuy + 1.5)
            {
                fuel2 += 100;
                std::cout << " Good Job! Fuel Increased By 100 :)"<<"\n";
                std::cout << " YOUR FULE IS =" <<fuel2<< "\n";

                flagd = 0;
            }
        }
    }

}

void DetectCollision3(float& tux, float& tuz, float& tuy, float& flagd)
{
    float d = 1.0 + tux;
    float dy = 1.0 + tuy;
    float dz = 2.0 + abs(tuz);
    if (flagd == 1)
    {
        if (cameraPos.x >= tux - 1.5 && cameraPos.x <= tux + 1.5 && cameraPos.z > tuz - 1.5 && cameraPos.z <= tuz + 1.5)
        {
            if (cameraPos.y >= tuy - 1.5 && cameraPos.y <= tuy + 1.5)
            {
                speed += 0.2;
                std::cout << " YOUR SPEED INCREASED BY 0.2:)" << "\n";
                std::cout << " YOUR TOTAL SPEED NOW IS EQUAL =" << speed << "\n";

                flagd = 0;
            }
        }
    }

}
float randomX ;
float randomY ;
float randomZ ;

float randomX2;
float randomY2;
float randomZ2;

void display()
{

    if (fuel2 >0 &&speed <5)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glm::mat4 nullview = glm::mat4(glm::mat3(view));
  

        float s1x = 1.5, s1y = 1.5, s1z = 1.5;
        dis(vbo1, ibo1, sphere1, -2.0f, 0.0f, -3.0f, ra3, t3, s1x, s1y, s1z, view);
        float sux = 3.0, suy = 3.0, suz = 3.0;
        dis(vbo1, ibo1, sphere1, tux, tuy, tuz, ra2, texture1, sux, suy, suz, view);//sun
        float s3x = 0.6, s3y = 0.6, s3z = 0.6;
        dis(vbo1, ibo1, sphere1, -4.0f, 0.0f, -2.25f, ra3, t8, s3x, s3y, s3z, view);//small gray
        float s4x = 0.8, s4y = 0.8, s4z = 0.8;
        dis(vbo1, ibo1, sphere1, -8.0f, 0.0f, 5.3f, ra4, t7, s4x, s4y, s4z, view);//after the small gray
        float s5x = 0.9, s5y = 0.9, s5z = 0.9;
        dis(vbo1, ibo1, sphere1, -15.0f, 0.0f, 8.0f, ra5, t2, s5x, s5y, s5z, view);//after 
        float s6x = 1.0, s6y = 1.0, s6z = 1.0;
        dis(vbo1, ibo1, sphere1, 2.0f, 0.0f, 2.5f, ra6, t4, s6x, s6y, s6z, view);//after
        float s7x = 2.2, s7y = 2.2, s7z = 2.2;
        dis(vbo1, ibo1, sphere1, 4.0f, 0.0f, -4.0f, ra7, t6, s7x, s7y, s7z, view);
        float rx = 3.7, ry = 0.4, rz = 3.7;//here
        dis(vbo1, ibo1, sphere1, 4.0f, 0.0f, -4.0f, ra7, ring, rx, ry, rz, view);
        float s8x = 1.0, s8y = 1.0, s8z = 1.0;
        dis(vbo1, ibo1, sphere1, 8.0, 0.0f, -7.9f, ra8, t9, s8x, s8y, s8z, view);
        float s9x = 4.5, s9y = 4.5, s9z = 4.5;
        dis(vbo1, ibo1, sphere1, tnx, tny, tnz, 0, t5, s9x, s9y, s9z, view);
        //drawing THE SHIP
        float ssx = 0.05, ssy = 0.01, ssz = 0.5;
        dis(vbo1, ibo1, sphere1, vx, vy, vz, ra10, t10, ssx, ssy, ssz, glm::mat4(1));//here is the ship 
        
        float vx2 = vx;float vy2 = vy, vz2 = vz;
        dis(vbo1, ibo1, sphere1, vx2, vy2, vz2, ra10, tf, fx, fy, fz, glm::mat4(1));
        for (int i = 0; i < 10;i++)
        {
            if (flagDis[i] == 1)
            {
                dis(vbo1, ibo1, sphere1, x[i], y[i], z[i], 0, bomb, s9x, s9y, s9z, view);
            }
            DetectCollision2(x[i], z[i], y[i], flagDis[i]);
        }
        for (int i = 0; i < 10;i++)
        {
            if (flagDis3[i] == 1)
            {
                dis(vbo1, ibo1, sphere1, x3[i], y3[i], z3[i], 0, speedd, s9x, s9y, s9z, view);
            }
            DetectCollision3(x3[i], z3[i], y3[i], flagDis3[i]);
        }
        
        for (int i = 0; i < 10;i++)
        {
            
 
           if (i % 2 == 0)
           {
               dis(vbo1, ibo1, sphere1, x2[i], y2[i], vn, 0, F, s9x, s9y, s9z, view);

               
           }
           
           else
           {
               dis(vbo1, ibo1, sphere1, vn, y2[i], z[i], 0, F, s9x, s9y, s9z, view);
               
              
           }
           DetectCollision(vn, z2[i], y2[i]);
           DetectCollision(x2[i], vn, y2[i]);
        }

        float ax = 100.0, ay = 100.0, az = 100.0;
        dis(vbo2, ibo2, sphere2, tux, tuy, tuz, bo, st, ax, ay, az, nullview);//universe

        glutSwapBuffers();
    }
    if(fuel2<=0)
    {
        std::cout << "        / \\" << std::endl;
        std::cout << "       |x x|" << std::endl;
        std::cout << "       | - |" << std::endl;
        std::cout << "      // | \\\\" << std::endl;
        std::cout << "     //  |  \\\\" << std::endl;
        std::cout << "    //   |   \\\\" << std::endl;
        std::cout << "   //    |    \\\\" << std::endl;
        std::cout << "  //     |     \\\\" << std::endl;
        std::cout << " //      |      \\\\" << std::endl;
        std::cout << "//       |       \\\\" << std::endl;
        std::cout << "|========|========|" << std::endl;
        std::cout << "'--------'--------'" << std::endl;

        std::cout << "\nSpaceship is dead :/" << std::endl;



        //scanf("%c");

        std::cout << "YOUR TOTAL TIME FLYING IN THE GAME IS :" << timer << "sec"<<std::endl;
        std::cout << "YOUR TOTAL FUEL IS  :" << fuel2;


        exit(EXIT_SUCCESS);
    }
    if (speed >= 1.0)
    {



        std::cout << "        / \\" << std::endl;
        std::cout << "       |0 0|" << std::endl;
        std::cout << "       | o |" << std::endl;
        std::cout << "      // | \\\\" << std::endl;
        std::cout << "     //  |  \\\\" << std::endl;
        std::cout << "    //   |   \\\\" << std::endl;
        std::cout << "   //    |    \\\\" << std::endl;
        std::cout << "  //     |     \\\\" << std::endl;
        std::cout << " //      |      \\\\" << std::endl;
        std::cout << "//       |       \\\\" << std::endl;
        std::cout << "|========|========|" << std::endl;
        std::cout << "'--------'--------'" << std::endl;

            std::cout << "\nCongratulations! You've reached maximum speed. You win! :)" << std::endl;
            exit(EXIT_SUCCESS);

            
        }

    }



    float speed2 = 0.1;
void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 033:
        std::cout << "YOUR TOTAL TIME FLYING IN THE GAME IS :" << timer << "sec" << std::endl;
        std::cout << "YOUR TOTAL FUEL IS  :" << fuel2;
        exit(EXIT_SUCCESS);
        break;
    case 'r':
        cameraPos += speed * cameraUp;
        
        timer += 1;
        fuel2 -= 1;
        break;
    case 'f':
        cameraPos -= speed * cameraUp;
       
        timer += 1;
        fuel2 -= 1;
        break;
    case 'w':
        cameraPos += speed * cameraFront;
        
        timer += 1;
        fuel2 -= 1;
        break;
    case 's':
        cameraPos -= speed * cameraFront;
        timer += 1;
        fuel2 -= 1;
        break;
    case 'a':
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) *
            speed2;
        fuel2 -= 1;
        timer += 1;
        
        break;
    case 'd':
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) *
            speed2;
        fuel2 -= 1;
        timer += 1;
        break;
    case 'q':
        yaw -= 1.0f;
        cameraDirection.x = glm::cos(glm::radians(yaw));
        cameraDirection.z = glm::sin(glm::radians(yaw));
        cameraFront = glm::normalize(cameraDirection);
        break;
    case 'e':
        yaw += 1.0f;
        cameraDirection.x = glm::cos(glm::radians(yaw));
        cameraDirection.z = glm::sin(glm::radians(yaw));
        cameraFront = glm::normalize(cameraDirection);
        break;
    }
}
void rotationspeed(float &ra1,float ff)
{
    ra1 += ff;
    if (ra1 >= 360)
    {
        ra1 = 0;
    }
}

void idle() {

 //those rotation angels 
    rotationspeed(ra2, 0.002);
    rotationspeed(ra3, 0.003);
    rotationspeed(ra4, 0.004);
    rotationspeed(ra5, 0.006);
    rotationspeed(ra6, 0.007);
    rotationspeed(ra7, 0.008);
    rotationspeed(ra8, 0.01);
    rotationspeed(bo, 0.01);
    if (fuel < 100&&fuel>50)
    {
        fx = 0.015;
        fy = 0.015;
    }
    if ( fuel<50)
    {
        fx = 0.01;
        fy = 0.01;
    }
    if (fuel >= 100)
    {
        fx = 0.02;
        fy = 0.02;
    }
    for (int i = 0; i < 20;i += 1)
    {
        if (flagvn == 0)
        {
            if (vn < 0)
            {
                vn += 0.001;
            }
            else
            {
                flagvn = 1;
            }
        }
        else
        {
            if (vn > -20)
            {
                vn -= 0.001;
            }
            else
            {
                flagvn = 0;
            }
        }
    }
  
    glutPostRedisplay();
}
void distime(float &time2)
{
    
}
int main(int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(900,  1080);
    glutInitContextVersion(3, 2);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutCreateWindow("Sphere");

    glewInit();

    init();
    
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    //distime(time2);
    return 0;
}
