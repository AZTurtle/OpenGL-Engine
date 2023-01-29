#include"mainWindow.h"

MainWindow::MainWindow(int x, int y, int w, int h, const char* title) : Window{x, y, w, h, title},
cam(glm::vec3(0.0f, 40.0f, 40.0f), glm::vec3(0.0f, -1.0f, -1.0f), 20.0f, &this->w, &this->h, 0.2f),
levelManager(&cam, window, &levelComplete),
resumeButton("resume.png",&resumeTransform,&cam,&resumeHover),
restartButton("restart.png",&restartTransform,&cam,&restartHover),
exitButton("exit.png",&exitTransform,&cam,&exitHover),
failedText("failed.png",&failedTransform,&cam,&failedColor),
continueButton("continue.png",&continueTransform,&cam,&continueColor),
playButton("play.png",&playTransform,&cam,&playColor),
mainSprite("mainscreen.png",&mainTransform,&cam,&mainscreenColor)
{
    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int w, int h){
        glfwMakeContextCurrent(window);
        glViewport(0, 0, w, h);
        glfwSetWindowSize(window, w, h);
    });
    fadeVAO.bindVertexBuffer(fadeMesh, 4, GL_STATIC_DRAW);
    fadeVAO.bindIndexBuffer(fadeInds, 6, GL_STATIC_DRAW);
    fadeVAO.addAttribute<glm::vec2>(0, 2, GL_FLOAT, 0);
}

void MainWindow::resize(GLFWwindow* window, int w, int h){

}

void MainWindow::load(){
    glfwMakeContextCurrent(window);
    glViewport(x, y, w, h);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void MainWindow::update(){
    int ratio = w / h;
    glfwMakeContextCurrent(window);
    glfwGetWindowSize(window, &w, &h);
    resumeTransform = glm::scale(glm::mat4(1.0f), glm::vec3(0.4f * ((float)h/(float)w),0.4f, 1.0f));
    resumeTransform = glm::translate(resumeTransform, glm::vec3(0.0f, 0.4f, 0.0f));
    
    restartTransform = glm::scale(glm::mat4(1.0f), glm::vec3(0.4f * ((float)h/(float)w),0.4f, 1.0f));
    restartTransform = glm::translate(restartTransform, glm::vec3(0.0f, 0.0f, 0.0f));
    

    failedTransform = glm::scale(glm::mat4(1.0f), glm::vec3(0.6f * ((float)h/(float)w),0.6f, 1.0f));
    failedTransform = glm::translate(failedTransform, glm::vec3(0.0f, 0.6f, 0.0f));

    continueTransform = glm::scale(glm::mat4(1.0f), glm::vec3(0.4f * ((float)h/(float)w),0.4f, 1.0f));
    continueTransform = glm::translate(continueTransform, glm::vec3(-0.05f, -0.2f, 0.0f));

    playTransform = glm::scale(glm::mat4(1.0f), glm::vec3(0.4f * ((float)h/(float)w),0.4f, 1.0f));
    playTransform = glm::translate(playTransform, glm::vec3(0.0f, 0.4f, 0.0f));

    mainTransform = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f * ((float)h/(float)w),2.0f, 1.0f));

    cam.update();

    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    if(!loading){
        if(!levelComplete){
            exitTransform = glm::scale(glm::mat4(1.0f), glm::vec3(0.4f * ((float)h/(float)w),0.4f, 1.0f));
            exitTransform = glm::translate(exitTransform, glm::vec3(0.0f, -0.4f, 0.0f));
            if(!hasLetters || paused){
                fade += (0.8f - fade) * 2.0f * delta_time;
            } else {
                fade += (0.0f - fade) * 2.0f * delta_time;
            }

            if(lastKeyPressed == VK_ESCAPE && hasLetters && globalTime - lastPressed >= 150){
                paused = !paused;
                lastPressed = globalTime;
            }

            if(!paused && hasLetters && !mainscreen){
                levelManager.update();
            } else {
                if(mouseX > 0.4f * w && mouseX < 0.6f * w && mouseY > 0.35f * h && mouseY < 0.45f * h){
                    resumeHover = 1.0f;
                    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
                        paused = false;
                    }
                } else {
                    resumeHover = 0.7f;
                }
                if(mouseX > 0.4f * w && mouseX < 0.6f * w && mouseY > 0.45f * h && mouseY < 0.55f * h){
                    restartHover = 1.0f;
                    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
                        levelManager.restart();
                        paused = false;
                    }
                } else {
                    restartHover = 0.7f;
                }
                if(mouseX > 0.4f * w && mouseX < 0.6f * w && mouseY > 0.55f * h && mouseY < 0.65f * h){
                    exitHover = 1.0f;
                    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
                        glfwTerminate();
                    }
                } else {
                    exitHover = 0.7f;
                }
            }
        } else {
            exitTransform = glm::scale(glm::mat4(1.0f), glm::vec3(0.4f * ((float)h/(float)w),0.4f, 1.0f));
            exitTransform = glm::translate(exitTransform, glm::vec3(0.0f, -1.0f, 0.0f));
            fade += (1.0f - fade) * 4.0f * delta_time;
            if(mouseX > 0.35f * w && mouseX < 0.65f * w && mouseY > 0.4f * h && mouseY < 0.6f * h){
                continueColor = 1.0f;
                if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
                    levelComplete = false;
                    loading = true;
                    hasLetters = true;
                }
            } else {
                continueColor = 0.7f;
            }
            if(mouseX > 0.4f * w && mouseX < 0.6f * w && mouseY > 0.6f * h && mouseY < 0.7f * h){
                exitHover = 1.0f;
                if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
                    glfwTerminate();
                }
            } else {
                exitHover = 0.7f;
            }
        }
    } else {
        fade += (1.0f - fade) * 4.0f * delta_time;
        if(fade >= 0.98f){
            newLevel();
            loading = false;
            mainscreen = false;
            hasLetters = true;
            paused = false;
            levelComplete = false;
        }
    }

    if(mainscreen){
        exitTransform = glm::scale(glm::mat4(1.0f), glm::vec3(0.3f * ((float)h/(float)w),0.3f, 1.0f));
        exitTransform = glm::translate(exitTransform, glm::vec3(0.0f, 0.0f, 0.0f));
        if(mouseX > 0.4f * w && mouseX < 0.6f * w && mouseY > 0.35f * h && mouseY < 0.45f * h){
            playColor = 1.0f;
            if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
                loading = true;
            }
        } else {
            playColor = 0.7f;
        }
        if(mouseX > 0.4f * w && mouseX < 0.6f * w && mouseY > 0.45f * h && mouseY < 0.55f * h){
            exitHover = 1.0f;
            if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
                glfwTerminate();
            }
        } else {
            exitHover = 0.7f;
        }
    }

    draw();

    Window::update();
}

void MainWindow::newLevel(){
    switch(levelNum){
        case 0:
            levelManager.loadLevel<levels::l1>();
            break;
        case 1:
            levelManager.loadLevel<levels::l2>();
            break;
        case 2:
            levelManager.loadLevel<levels::l3>();
            break;
    }
    levelNum++;
}

void MainWindow::draw(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClearColor(0.1f, 0.2f, 0.7f, 1.0f);
    
    //------------Opaque--------------
    if(mainscreen){
        glDisable(GL_DEPTH_TEST);
        mainSprite.draw();
        playButton.draw();
        exitButton.draw();
        glEnable(GL_DEPTH_TEST);
    } else {
        levelManager.drawOpaque();
    }

    //-------------Masks--------------



    //-----------Transparent----------
    glDepthMask(false);

    if(!mainscreen){
        levelManager.drawTransparent();
    }

    fadeShader_->bind();
    fadeVAO.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
    if(!loading){
        if(!levelComplete){
            if(paused || !hasLetters){
                restartButton.draw();
                exitButton.draw();
            }
            if(paused && hasLetters){
                resumeButton.draw();
            }
            if(!hasLetters){
                failedText.draw();
            }
        } else {
            continueButton.draw();
            exitButton.draw();
        }
    }

    glDepthMask(true);


    glfwSwapBuffers(window);
}

void MainWindow::openWindow(){
    Window::openWindow();
}