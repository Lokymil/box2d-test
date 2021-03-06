#include <GL/gl.h>
#include <GLES3/gl3.h>
#include <SDL2/SDL.h>

#include <iostream>

int main(int argc, char** argv) {
    // Notre fenêtre
    SDL_Window* fenetre(0);
    SDL_GLContext contexteOpenGL(0);

    SDL_Event evenements;
    bool terminer(false);

    // Initialisation de la SDL

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();

        return -1;
    }

    // Création de la fenêtre

    fenetre = SDL_CreateWindow("Test SDL 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600,
                               SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if (fenetre == 0) {
        std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
        SDL_Quit();

        return -1;
    }

    // Création du contexte OpenGL

    contexteOpenGL = SDL_GL_CreateContext(fenetre);

    if (contexteOpenGL == 0) {
        std::cout << SDL_GetError() << std::endl;
        SDL_DestroyWindow(fenetre);
        SDL_Quit();

        return -1;
    }

    // Vertices et coordonnées

    float vertices[] = {-0.5, -0.5, 0.0, 0.5, 0.5, -0.5};
    float squares[] = {0.0, 1.0, -0.25, 0.75, 0.0, 0.5, 0.25, 0.75};

    // Boucle principale

    while (!terminer) {
        // Gestion des évènements

        SDL_WaitEvent(&evenements);

        if (evenements.window.event == SDL_WINDOWEVENT_CLOSE) terminer = true;

        // Nettoyage de l'écran

        glClear(GL_COLOR_BUFFER_BIT);

        // On remplie puis on active le tableau Vertex Attrib 0

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);
        glEnableVertexAttribArray(0);

        // On affiche le triangle

        glDrawArrays(GL_TRIANGLES, 0, 3);

        // On désactive le tableau Vertex Attrib puisque l'on n'en a plus besoin

        glDisableVertexAttribArray(0);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, squares);
        glEnableVertexAttribArray(0);
        glDrawArrays(GL_POLYGON, 0, 4);
        glDisableVertexAttribArray(0);

        // Actualisation de la fenêtre

        SDL_GL_SwapWindow(fenetre);
    }

    // On quitte la SDL

    SDL_GL_DeleteContext(contexteOpenGL);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();

    return 0;
}