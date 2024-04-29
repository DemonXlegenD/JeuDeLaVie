#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "jeudelavie.h"

int main(int argc, char *argv[])
{
    SDL_Init( SDL_INIT_EVERYTHING);

  /*-------------------------------------------------------------------------------*/
 /*-------------------------INITIALISATION DE LA FENÊTRE--------------------------*/
/*-------------------------------------------------------------------------------*/
    int windowFlags = 0;
    SDL_Window *window = SDL_CreateWindow("Jeu de la vie", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
    if (!window) {
        SDL_Log("Échec de la création de la fenêtre : %s", SDL_GetError());
        return 1;
    }

  /*-------------------------------------------------------------------------------*/
 /*-------------------------INITIALISATION D'UN RENDU-----------------------------*/
/*-------------------------------------------------------------------------------*/

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0); //crée un objet de rendu pour la fenêtre
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //définit la couleur de dessin pour le rendu
    SDL_RenderClear(renderer); //efface le rendu avec la couleur de dessin actuelle
    SDL_RenderPresent(renderer); //affiche le rendu sur la fenêtre
    if (!renderer) {
        SDL_Log("Échec de la création du rendu : %s", SDL_GetError());
        return 1;
    }

  /*-------------------------------------------------------------------------------*/
 /*----------------------INITIALISATION DE L'ÉVÉNEMENT----------------------------*/
/*-------------------------------------------------------------------------------*/

    SDL_Event event;

  /*-------------------------------------------------------------------------------*/
 /*------------------------INITIALISATION DE LA POLICE----------------------------*/
/*-------------------------------------------------------------------------------*/

    TTF_Init();
    if (TTF_Init() != 0) {
        SDL_Log("Échec lors du chargement de la police : %s", TTF_GetError());
        return 1;
    }
    TTF_Font* font = TTF_OpenFont("ChangaOne-Regular.ttf", 100);
    if (font == NULL) {
        SDL_Log("Échec lors du chargement de la police : %s", TTF_GetError());
        return 1;
    }
    SDL_Color textcolor = {255, 255, 255, 255}; // définir la couleur du texte
    
  /*-------------------------------------------------------------------------------*/
 /*------------------------INITIALISATION DU BOUTON PLAY--------------------------*/
/*-------------------------------------------------------------------------------*/

    int variablePlay = 0; // variable associée au bouton
    
    Button buttonPlay; // initialisation du bouton

    
    SDL_Surface* textSurfacePlay = TTF_RenderText_Solid(font, "Play", textcolor); // définir la surface de texte avec la police, le string et la couleur
    SDL_Texture* textTexturePlay = SDL_CreateTextureFromSurface(renderer, textSurfacePlay); // créer la texture du tex
    initButton(&buttonPlay, (SCREEN_WIDTH - textSurfacePlay->w)/2, (SCREEN_HEIGHT - textSurfacePlay->h)/3, textSurfacePlay->w, textSurfacePlay->h, &variablePlay); // initialise la position, la taille, la variable a laquelle est lié le bouton
    SDL_FreeSurface(textSurfacePlay); // la surface n'est plus nécessaire
    
  /*-------------------------------------------------------------------------------*/
 /*---------------------INITIALISATION DU BOUTON SETTINGS-------------------------*/
/*-------------------------------------------------------------------------------*/

    int variableSettings = 0; // variable associée au bouton
    
    Button buttonSettings; // initialisation du bouton
    SDL_Surface* textSurfaceSettings = TTF_RenderText_Solid(font, "Settings", textcolor); // définir la surface de texte avec la police, le string et la couleur
    SDL_Texture* textTextureSettings = SDL_CreateTextureFromSurface(renderer, textSurfaceSettings); // créer la texture du tex
    initButton(&buttonSettings, (SCREEN_WIDTH - textSurfaceSettings->w)/2, (SCREEN_HEIGHT - textSurfaceSettings->h)/2, textSurfaceSettings->w, textSurfaceSettings->h, &variableSettings); // initialise la position, la taille, la variable a laquelle est lié le bouton
    SDL_FreeSurface(textSurfaceSettings); // la surface n'est plus nécessaire

  /*-------------------------------------------------------------------------------*/
 /*---------------------INITIALISATION DU BOUTON SETTINGS-------------------------*/
/*-------------------------------------------------------------------------------*/

    int variableQuit = 0; // variable associée au bouton
    
    Button buttonQuit; // initialisation du bouton
    SDL_Surface* textSurfaceQuit = TTF_RenderText_Solid(font, "Quit", textcolor); // définir la surface de texte avec la police, le string et la couleur
    SDL_Texture* textTextureQuit = SDL_CreateTextureFromSurface(renderer, textSurfaceQuit); // créer la texture du tex
    initButton(&buttonQuit, (SCREEN_WIDTH - textSurfaceQuit->w)/2, (SCREEN_HEIGHT - textSurfaceQuit->h)/1.5, textSurfaceQuit->w, textSurfaceQuit->h, &variableQuit); // initialise la position, la taille, la variable a laquelle est lié le bouton
    SDL_FreeSurface(textSurfaceQuit); // la surface n'est plus nécessaire

  /*-------------------------------------------------------------------------------*/
 /*---------------------INITIALISATION DU BOUTON Back---------------------------*/
/*-------------------------------------------------------------------------------*/


    int variableBack = 1; // variable associée au bouton
    
    Button buttonBack; // initialisation du bouton
    SDL_Surface* textSurfaceBack = TTF_RenderText_Solid(font, "Back", textcolor); // définir la surface de texte avec la police, le string et la couleur
    SDL_Texture* textTextureBack = SDL_CreateTextureFromSurface(renderer, textSurfaceBack); // créer la texture du tex
    initButton(&buttonBack, 100, 100, textSurfaceBack->w , textSurfaceBack->h, &variableBack); // initialise la position, la taille, la variable a laquelle est lié le bouton
    SDL_FreeSurface(textSurfaceBack); // la surface n'est plus nécessaire

  /*-------------------------------------------------------------------------------*/
 /*------------------------INITIALISATION DU TEXTE MODE---------------------------*/
/*-------------------------------------------------------------------------------*/

    SDL_bool textIsVisible = SDL_FALSE;
    SDL_Rect rectangle = {200, 200, 200, 200};
    SDL_Color color = { 255, 255, 255 };
    SDL_Surface* surface = TTF_RenderText_Solid(font, "Hello, World!", color);// définir la surface de texte avec la police, le string et la couleur
    SDL_Texture* textTextureMode = SDL_CreateTextureFromSurface(renderer, surface); // créer la texture du texte

  /*-------------------------------------------------------------------------------*/
 /*---------------------INITIALISATION DU BOUTON RANDOM---------------------------*/
/*-------------------------------------------------------------------------------*/


    int variableRandom = 1; // variable associée au bouton
    
    Button buttonRandom; // initialisation du bouton
    SDL_Surface* textSurfaceRandom = TTF_RenderText_Solid(font, "Random", textcolor); // définir la surface de texte avec la police, le string et la couleur
    SDL_Texture* textTextureRandom = SDL_CreateTextureFromSurface(renderer, textSurfaceRandom); // créer la texture du tex
    initButton(&buttonRandom, 100, 600, textSurfaceRandom->w, textSurfaceRandom->h, &variableRandom); // initialise la position, la taille, la variable a laquelle est lié le bouton


  /*-------------------------------------------------------------------------------*/
 /*------------------------INITIALISATION DU BOUTON FILL--------------------------*/
/*-------------------------------------------------------------------------------*/


    int variableFill = 1; // variable associée au bouton
    
    Button buttonFill; // initialisation du bouton
    SDL_Surface* textSurfaceFill = TTF_RenderText_Solid(font, "Fill", textcolor); // définir la surface de texte avec la police, le string et la couleur
    SDL_Texture* textTextureFill = SDL_CreateTextureFromSurface(renderer, textSurfaceFill); // créer la texture du tex
    initButton(&buttonFill,  500, 600, textSurfaceFill->w, textSurfaceFill->h, &variableFill); // initialise la position, la taille, la variable a laquelle est lié le bouton


  /*----------------------------------------------------------------------------------------*/
 /*--------------------------INITIALISATION DU SCROLL DE VITESSE---------------------------*/
/*----------------------------------------------------------------------------------------*/

    int speedBarSize = 400;
    int variableSpeed = 1;

    Button buttonSpeed; // initialisation du bouton
    initButton(&buttonSpeed, SCREEN_WIDTH/2 - 20, 20, 40, 40, &variableSpeed);
    buttonSpeed.color.r = 100;
    buttonSpeed.color.g = 100;
    buttonSpeed.color.b = 100;

    SDL_Rect speedBar = {SCREEN_WIDTH/2 - speedBarSize/2, 30, speedBarSize, 20};

  /*-------------------------------------------------------------------------------*/
 /*--------------------------INITIALISATION DES GRILLES---------------------------*/
/*-------------------------------------------------------------------------------*/

    //Grilles qui vont effectuer les étapes du jeu de la vie
    int** grille = creer_grille(SIZE_LINE, SIZE_COLUMN);
    int** grille_change = creer_grille(SIZE_LINE, SIZE_COLUMN);

    //Grilles de stockage, utile pour le cas d'oscillation qui est géré pour 2 temps
    int** grille_stock1 = creer_grille(SIZE_LINE, SIZE_COLUMN);
    int** grille_stock2 = creer_grille(SIZE_LINE, SIZE_COLUMN);

    //Varriable qui permet de switch entre la grille de stockage 1 et la deuxième
    int switcher = 1;

    //Booléen qui fait tourner la boucle de jeu
    bool running = true;
    bool playing = false;
    bool editing = false;
    bool pause = false;

  /*------------------------------------------------------------------------------------------------*/
 /*--------------------------INITIALISATION DU DELAI AFIN DE RAFFRAICHIR---------------------------*/
/*------------------------------------------------------------------------------------------------*/

    Uint32 curr_frame_loop = SDL_GetTicks();
    int loop_delay = 50;

  /*-------------------------------------------------------------------------------------------*/
 /*--------------------------POINTEUR DU FICHIER AVEC LES RESULTATS---------------------------*/
/*-------------------------------------------------------------------------------------------*/

    FILE * fPtr = fopen("resultats.txt", "ab+");;
    int nb_cellule_vivante = 0, nb_cellule_morte = 0;

  /*------------------------------------------------------------------------------------------------*/
 /*----------------------------------------BOUCLE DE JEU-------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

    while( running )
    {
        if (SDL_PollEvent( &event ))
        {
            //Fermeture de la fenêtre
            if ( event.type == SDL_QUIT )
            {
                break;
            // Bouton souris gauche clické
            } else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                
                // Vérifier si le clic est sur le bouton
                int mouseX = event.button.x;
                int mouseY = event.button.y;

                // Le bouton Play est pressé
                if (mouseX >= buttonPlay.rect.x && mouseX < buttonPlay.rect.x + buttonPlay.rect.w && mouseY >= buttonPlay.rect.y && mouseY < buttonPlay.rect.y + buttonPlay.rect.h) {
                    
                    // Inverser l'état du bouton
                    if (buttonPlay.isVisible) {
                        
                        buttonPlay.isPressed = SDL_TRUE;
                        playing = true;

                        // Cacher les autres boutons
                        buttonSettings.isVisible = SDL_FALSE;
                        buttonRandom.isVisible = SDL_FALSE;
                        buttonBack.isVisible = SDL_FALSE;
                        buttonQuit.isVisible = SDL_FALSE;

                        // Cacher le texte
                        textIsVisible = SDL_FALSE;
                    }
                }
                // Le bouton Settings est pressé
                else if (mouseX >= buttonSettings.rect.x && mouseX < buttonSettings.rect.x + buttonSettings.rect.w && mouseY >= buttonSettings.rect.y && mouseY < buttonSettings.rect.y + buttonSettings.rect.h) {
                    
                    // Inverser l'état du bouton
                    if (buttonSettings.isVisible) {
                        textIsVisible = SDL_TRUE;
                        buttonSettings.isPressed = SDL_TRUE;
                        buttonPlay.isVisible = SDL_FALSE;
                        buttonSettings.isVisible = SDL_FALSE;
                        buttonBack.isVisible = SDL_TRUE;
                        buttonRandom.isVisible = SDL_TRUE;
                        buttonFill.isVisible = SDL_TRUE;
                        buttonQuit.isVisible = SDL_FALSE;
                    }

                }
                // Le bouton Random est pressé
                else if (mouseX >= buttonRandom.rect.x && mouseX < buttonRandom.rect.x + buttonRandom.rect.w && mouseY >= buttonRandom.rect.y && mouseY < buttonRandom.rect.y + buttonRandom.rect.h) {
                    
                    // Inverser l'état du bouton
                    
                    if (buttonRandom.isVisible) {
                        buttonRandom.isPressed = !buttonRandom.isPressed;
                        textIsVisible = SDL_FALSE;
                    }

                }
                // Le bouton Fill est pressé
                else if (mouseX >= buttonFill.rect.x && mouseX < buttonFill.rect.x + buttonFill.rect.w && mouseY >= buttonFill.rect.y && mouseY < buttonFill.rect.y + buttonFill.rect.h) {
                    
                    // Inverser l'état du bouton
                    
                    if ( buttonFill.isVisible ) {
                        textIsVisible = SDL_FALSE;
                        buttonFill.isPressed = SDL_TRUE;
                        editing = true;
                        buttonBack.isVisible = SDL_FALSE;
                        buttonRandom.isVisible = SDL_FALSE;
                        buttonFill.isVisible = SDL_FALSE;
                        buttonPlay.isVisible = SDL_FALSE;
                        buttonSettings.isVisible = SDL_FALSE;
                        buttonQuit.isVisible = SDL_FALSE;
                    }
                }
                // Le bouton Retour est pressé
                else if (mouseX >= buttonBack.rect.x && mouseX < buttonBack.rect.x + buttonBack.rect.w && mouseY >= buttonBack.rect.y && mouseY < buttonBack.rect.y + buttonBack.rect.h) {
                    
                    // Inverser l'état du bouton
                    if (buttonBack.isVisible) {
                        buttonBack.isPressed = SDL_TRUE;
                        buttonBack.isVisible = SDL_FALSE;
                        buttonRandom.isVisible = SDL_FALSE;
                        buttonFill.isVisible = SDL_FALSE;
                        buttonPlay.isVisible = SDL_TRUE;
                        buttonSettings.isPressed = SDL_FALSE;
                        buttonSettings.isVisible = SDL_TRUE;
                        buttonQuit.isVisible = SDL_TRUE;
                        textIsVisible = SDL_FALSE;
                    }
                }
                // Le bouton Quit est pressé
                else if (mouseX >= buttonQuit.rect.x && mouseX < buttonQuit.rect.x + buttonQuit.rect.w && mouseY >= buttonQuit.rect.y && mouseY < buttonQuit.rect.y + buttonQuit.rect.h) {
                    running = false;
                }
            }
        }

        // Effacer l'écran
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

          /*------------------------------------------------------------------------------------------------*/
         /*-------------------------------------AFFICHER LES BOUTONS---------------------------------------*/
        /*------------------------------------------------------------------------------------------------*/

        if( buttonPlay.isVisible ){
            // Dessiner le bouton  
            buttonPressed(renderer, textTexturePlay, &buttonPlay);
        }
        if ( buttonSettings.isVisible )
        {
            // Dessiner le bouton
            buttonPressed(renderer, textTextureSettings, &buttonSettings);
        }
        if ( buttonQuit.isVisible ) 
        {
            buttonPressed(renderer, textTextureQuit, &buttonQuit);
        }
        if( textIsVisible){
             SDL_RenderCopy(renderer, textTextureMode, NULL, &rectangle);
        }
        if ( buttonRandom.isVisible )
        {
            buttonPressed(renderer, textTextureRandom, &buttonRandom);

            if ( buttonRandom.isPressed && *buttonRandom.variable == 1){
                randomize_grille(grille, SIZE_LINE, SIZE_COLUMN);
                *buttonRandom.variable = 2;
            } else if ( !buttonRandom.isPressed && *buttonRandom.variable == 2 ){
                copy_grille(grille_change, grille, SIZE_LINE, SIZE_COLUMN);
                *buttonRandom.variable = 1;
            }
        }
        if ( buttonFill.isVisible ) 
        {
            buttonPressed(renderer, textTextureFill, &buttonFill);
        }
        if ( buttonBack.isVisible )
        {
            // Dessiner le bouton
            buttonPressed(renderer, textTextureBack, &buttonBack);
        }
        
          /*------------------------------------------------------------------------------------------------*/
         /*----------------------------------------AFFICHER LE JEU-----------------------------------------*/
        /*------------------------------------------------------------------------------------------------*/
        if ( playing && !buttonSettings.isVisible && !buttonRandom.isVisible && !buttonBack.isVisible && !buttonFill.isVisible )
        {   
            // On gère le clic de la souris afin de pouvoir scroll
            int mouseX = event.button.x;
            int mouseY = event.button.y;

            loop_delay = ((SCREEN_WIDTH/2 + speedBarSize/2) - buttonSpeed.rect.w / 2 - buttonSpeed.rect.x) * 3;

            // Click souris down
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (mouseX >= buttonSpeed.rect.x && mouseX < buttonSpeed.rect.x + buttonSpeed.rect.w && mouseY >= buttonSpeed.rect.y && mouseY < buttonSpeed.rect.y + buttonSpeed.rect.h) {
                    buttonSpeed.isPressed = SDL_TRUE;
                }
            }
            // Click souris up
            if (event.type == SDL_MOUSEBUTTONUP) {
                buttonSpeed.isPressed = SDL_FALSE;
            }
            // Le bouton est pressé
            if (buttonSpeed.isPressed){
                if (mouseX > SCREEN_WIDTH/2 - speedBarSize/2 && mouseX < SCREEN_WIDTH/2 + speedBarSize/2) {
                    buttonSpeed.rect.x = mouseX - buttonSpeed.rect.w / 2;
                }
            }
            //Affiche l'écran
            afficher_grille(grille, renderer, SIZE_LINE, SIZE_COLUMN);
            SDL_SetRenderDrawColor(renderer, 200, 200, 200, SDL_ALPHA_OPAQUE);
            SDL_RenderFillRect(renderer, &speedBar);
            drawButton(renderer, &buttonSpeed);
            SDL_RenderPresent(renderer);

            if ( SDL_TICKS_PASSED(SDL_GetTicks(), curr_frame_loop) && !pause) {
                curr_frame_loop = SDL_GetTicks() + loop_delay;
                nombre_cellule(grille, SIZE_LINE, SIZE_COLUMN, &nb_cellule_vivante, &nb_cellule_morte);
                for(int j = 0; j < SIZE_LINE; j++){
                    for(int k = 0; k < SIZE_COLUMN; k++){
                        //Regarde le carré de cellules de la cellule (j,k)
                        carre_cellule(grille, grille_change, j, k, SIZE_LINE, SIZE_COLUMN);
                    }
                }
                copy_grille(grille_change, grille, SIZE_LINE, SIZE_COLUMN);
                //La grille stockage 1 copie la grille précédente pour arreter le programme lors d'un cas d'oscillation
                if(switcher == 1){
                    if(meme_grille(grille_change, grille_stock1, SIZE_LINE, SIZE_COLUMN)){
                        SDL_Delay(3000);
                        playing = false;
                        buttonQuit.isVisible = SDL_TRUE;
                        buttonPlay.isVisible = SDL_TRUE;
                        buttonSettings.isVisible = SDL_TRUE;
                    }
                    copy_grille(grille, grille_stock1, SIZE_LINE, SIZE_COLUMN);
                    switcher++;
                }
                //La grille stockage 2 copie la grille précédente pour arreter le programme lors d'un cas d'oscillation
                else if(switcher == 2){
                    if(meme_grille(grille_change, grille_stock2, SIZE_LINE, SIZE_COLUMN)){
                        SDL_Delay(3000);
                        playing = false;
                        buttonQuit.isVisible = SDL_TRUE;
                        buttonPlay.isVisible = SDL_TRUE;
                        buttonSettings.isVisible = SDL_TRUE;
                    }
                    copy_grille(grille, grille_stock2, SIZE_LINE, SIZE_COLUMN);
                    switcher--;
                }
            }
            // Retour au menu principal en cliquant sur échape
            if( event.key.keysym.scancode == SDL_SCANCODE_ESCAPE ){
                    SDL_Delay(3000);
                    playing = false;
                    buttonQuit.isVisible = SDL_TRUE;
                    buttonPlay.isVisible = SDL_TRUE;
                    buttonSettings.isVisible = SDL_TRUE;
            }
            // Met en pause
            else if(event.key.keysym.scancode == SDL_SCANCODE_SPACE){
                pause = !pause;
            }
        // Retire la pause
        else if(event.key.keysym.scancode == SDL_SCANCODE_SPACE){
                pause = !pause;
        }
        } else if (editing) {

            if ( buttonFill.isPressed && *buttonFill.variable == 1){
                int mousePosX, mousePosY;
                SDL_GetMouseState(&mousePosX, &mousePosY);

                int caseX = mousePosX / (SCREEN_WIDTH / SIZE_LINE);
                int caseY = mousePosY / (SCREEN_HEIGHT / SIZE_COLUMN);

                if (*buttonFill.variable == 1) {
                    afficher_grille(grille, renderer, SIZE_LINE, SIZE_COLUMN);
                }

                SDL_SetRenderDrawColor(renderer, 200, 200, 200, SDL_ALPHA_OPAQUE);
                for (int ligne_i = 1; ligne_i < SIZE_LINE; ligne_i++) {
                    SDL_RenderDrawLine(renderer, SCREEN_WIDTH/SIZE_LINE*ligne_i, 0, SCREEN_WIDTH/SIZE_LINE*ligne_i, SCREEN_HEIGHT);
                }

                SDL_SetRenderDrawColor(renderer, 200, 200, 200, SDL_ALPHA_OPAQUE);
                for (int colonne_i = 1; colonne_i < SIZE_LINE; colonne_i++) {
                    SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT/SIZE_LINE*colonne_i, SCREEN_WIDTH, SCREEN_HEIGHT/SIZE_LINE*colonne_i);
                }

                SDL_RenderPresent(renderer);

                if(event.type == SDL_MOUSEBUTTONDOWN){
                    if(grille[caseX][caseY] == 1){
                        grille[caseX][caseY] = 0;
                      
                    }
                    else{
                        grille[caseX][caseY] = 1;
                    }
                }
                // Quitter l'écran fill
                if( event.key.keysym.scancode == SDL_SCANCODE_SPACE || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE ){
                    *buttonFill.variable = 1;
                    editing = false;
                    buttonBack.isVisible = SDL_TRUE;
                    buttonRandom.isVisible = SDL_TRUE;
                    buttonFill.isVisible = SDL_TRUE;
            }
            } 
            //else if ( !buttonFill.isPressed && *buttonFill.variable == 2 ){
            //     copy_grille(grille_change, grille, SIZE_LINE, SIZE_COLUMN);
            //     *buttonFill.variable = 1;
            // }
        } else {
            SDL_RenderPresent(renderer);
        }
    }

    // On stocke le résultat dans un string
    char resultat[100] = "";
    sprintf(resultat, "Il y a %d cellules mortes et %d cellules vivantes.\n", nb_cellule_morte, nb_cellule_vivante);

    printf("%s", resultat);

    // On ouvre le fichier en lecture
    fPtr = fopen("resultats.txt", "wb");

    // On gère le cas ou on ne peut pas écrire
    if(fPtr == NULL)
    {
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }

    // On ecrit le resultat dans le .txt
    fputs(resultat, fPtr);

    // On ferme le fichier
    fclose(fPtr);

    //Libération de la mémoire des grille créées au début
    vider_grille(grille, SIZE_LINE);
    vider_grille(grille_change, SIZE_LINE);
    vider_grille(grille_stock1, SIZE_LINE);
    vider_grille(grille_stock2, SIZE_LINE);

    // Nettoyer la mémoire
    SDL_FreeSurface(textSurfacePlay);
    SDL_DestroyTexture(textTexturePlay);
    SDL_FreeSurface(textSurfaceSettings);
    SDL_DestroyTexture(textTextureSettings);
    TTF_CloseFont(font);
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    SDL_Quit();
    return EXIT_SUCCESS;
}



void buttonPressed(SDL_Renderer *renderer, SDL_Texture* textTexture, Button *button){
    if ( button->isPressed ) {
        button->color.r = 20;
        button->color.g = 150;
        drawButton(renderer, button);
        SDL_RenderCopy(renderer, textTexture, NULL, &button->rect);
        // Cacher le bouton
        if( *(button->variable) == 0){
            SDL_Delay(1000);
            button->isVisible = SDL_FALSE;
            button->isPressed = SDL_FALSE;
        }
    } else {
        button->color.r = 255;
        button->color.g = 0;
        drawButton(renderer, button);
        SDL_RenderCopy(renderer, textTexture, NULL, &button->rect);    
    } 
}


//Fonction initialisant un bouton
void initButton(Button *button, int x, int y, int width, int height, int *variable) {
    button->rect.x = x;
    button->rect.y = y;
    button->rect.w = width;
    button->rect.h = height;
    button->color.r = 255;
    button->color.g = 0;
    button->color.b = 0;
    button->color.a = 255;
    button->isPressed = SDL_FALSE;
    button->variable = variable;
    switch (*variable)
    {
    case 0:
        button->isVisible = SDL_TRUE; // boutons du menu du jeu
        break;
    case 1:
        button->isVisible = SDL_FALSE; //boutons des settings
        break;
    default:
        break;
    }
    
}

//Fonction dessinant un bouton
void drawButton(SDL_Renderer *renderer, Button *button) {
    SDL_SetRenderDrawColor(renderer, button->color.r, button->color.g, button->color.b, button->color.a);
    SDL_RenderFillRect(renderer, &button->rect);
    
}

//Fonction créant une matrice carrée avec une dimension prise en argument
int** creer_grille(int ligne, int colonne){

    //Allocation de la mémoire
    int **grille = (int**)malloc(ligne * sizeof(int*));
    for(int i = 0; i < ligne; i++){
        grille[i] = (int *)malloc(colonne * sizeof(int));
    }

    //Initialisation grille nulle
    for(int i =0; i < ligne; i++){
        for(int j = 0; j < colonne; j++){
                grille[i][j] = 0;
            }    
        }
    
    return grille;
}

void randomize_grille(int** grille, int ligne, int colonne){
    int random1, random2;
    time_t t;
    // On initialise le générateur de nombre aléatoire
    srand((unsigned) time(&t));
     //Initialisation de la grille
    for(int i =0; i < ligne; i++){
        for(int j = 0; j < colonne; j++){
            random1 = rand() % 2;
            random2 = rand() % 2;
            if(random1==random2){
                grille[i][j]= random1;
            }  
        }
    }
}

SDL_Rect creer_cellule(int i, int j) {
    SDL_Rect rectangle;
    rectangle.x = SCREEN_WIDTH/SIZE_COLUMN * i;
    rectangle.y = SCREEN_HEIGHT/SIZE_LINE * j;
    rectangle.w = SCREEN_WIDTH/SIZE_COLUMN;
    rectangle.h = SCREEN_HEIGHT/SIZE_LINE;

    return rectangle;
}

//Fonction affichant la matrice
void afficher_grille(int** grille, SDL_Renderer *renderer, int ligne, int colonne){
    
    for(int i = 0; i < ligne ; i++){
        for(int j = 0; j < colonne; j++){
            int r = 255, g = 255, b = 255;
            if (grille[i][j] == 1) {
                r = 255, g = 100, b = 0;
            }
            SDL_Rect cellule = creer_cellule(i, j);

            SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);

            SDL_RenderFillRect(renderer, &cellule);
        }
    }
}

//Fonction copiant la grille
void copy_grille(int** grille, int** grille_copy, int ligne, int colonne){

    for(int i = 0; i < ligne; i++){
        for(int j = 0; j < colonne; j++){
            grille_copy[i][j] = grille[i][j];
        }
    }

}

//Fonction renvoyant le nombre de cellule mortes et le nombre de cellules vivantes
void nombre_cellule(int **grille, int ligne, int colonne, int* nb_cellule_vivante, int* nb_cellule_morte){

    int tmp_nb_cellule_vivante = 0, tmp_nb_cellule_morte = 0;

    for(int i = 0; i < ligne ; i++){
        for(int j = 0; j < colonne; j++){

            if(grille[i][j] == 0){
                tmp_nb_cellule_morte ++;
            }
            else if(grille[i][j] == 1){
                tmp_nb_cellule_vivante ++;
            }
        }
    }

    *nb_cellule_vivante = tmp_nb_cellule_vivante;
    *nb_cellule_morte = tmp_nb_cellule_morte;

    printf("Il y a %d cellules mortes et %d cellules vivantes.\n", nb_cellule_morte, nb_cellule_vivante);
}

//Fonction modifiant la cellule
int change_cellule(int cellule, int nb_cellule_vivante){

    //Cellule vivante reste vivante
    if(cellule == 1 && ( nb_cellule_vivante == 2 || nb_cellule_vivante == 3)){
        return 1;
    }
    //Cellule vivante meurt
    else if((cellule == 1 && (nb_cellule_vivante <2 || nb_cellule_vivante > 3))){
        return 0;
    }
    //Cellule morte devient vivante
    else if(cellule == 0 && nb_cellule_vivante == 3){
        return 1;
    }
}

//Fonction regardant les 8 cellules autour de la cellule (formant un carré)
void carre_cellule(int **grille, int** grille_copy, int i, int j, int ligne, int colonne){
    int nb_cellule_vivante = 0, nb_cellule_morte = 0;
    //Vérification du carré
    int x_coin_carre = i-1;
    int y_coin_carre = j-1;
   

    for(int k = 0; k < 3; k++){

        for(int l = 0; l < 3; l++){

            //Ne pas oublier de retirer le cas de la cellule centrale
            if(((x_coin_carre +k >=0) && (y_coin_carre + l >=0))&&((x_coin_carre +k <=ligne-1) && (y_coin_carre + l <=colonne-1))&&((x_coin_carre +k !=i) || (y_coin_carre + l != j)) && grille[x_coin_carre + k][y_coin_carre + l] == 0)
            {
                nb_cellule_morte++;
            }
            else if(((x_coin_carre +k >=0) && (y_coin_carre + l >=0))&&((x_coin_carre +k <=ligne-1) && (y_coin_carre + l <=colonne-1))&&((x_coin_carre +k !=i) || (y_coin_carre + l != j)) && grille[x_coin_carre + k][y_coin_carre + l] == 1)
            {
                nb_cellule_vivante++;
            }   
    
        }
        
    }
    //Transforme la Cellule en morte ou vivante 
    grille_copy[i][j]=change_cellule(grille[i][j], nb_cellule_vivante);  
}



//Fonction renvoyant true si les deux grilles sont pareilles sinon false
bool meme_grille(int** grille1, int** grille2, int ligne, int colonne){
    bool pareil = true;
    for(int i = 0; i < ligne ; i++){
        for(int j = 0; j < colonne; j++){
            //Une cellule est différente d'une autre aux coordonnées (i,j)
            if(grille1[i][j] != grille2[i][j]){
                pareil = false;
            }

        }
    }
    return pareil;
}

//Fonction libérant la mémoire de la grille
void vider_grille(int** grille, int ligne){
    for(int i = 0; i < ligne; i++){
        free(grille[i]);
    }
    free(grille);
}