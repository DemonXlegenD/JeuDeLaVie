#define SIZE_LINE 120
#define SIZE_COLUMN 120
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

typedef struct {
    SDL_Rect rect; // rectangle représentant la position et la taille du bouton
    SDL_Color color; // couleur du bouton
    SDL_bool isPressed; // booléen pour indiquer si le bouton est enfoncé ou non
    SDL_bool isVisible; // booléen pour indiquer si le bouton est visible ou non
    int *variable; // pointeur vers la variable associée
} Button;

void buttonPressed(SDL_Renderer *renderer, SDL_Texture* textTexture, Button *button);
void initButton(Button*, int, int, int, int, int*);
void drawButton(SDL_Renderer*, Button*);

int** creer_grille(int, int);
void randomize_grille(int**, int, int);
SDL_Rect creer_cellule(int, int);
void afficher_grille(int**, SDL_Renderer*, int, int);
void copy_grille(int**, int**, int, int);
void nombre_cellule(int**, int, int, int*, int*);
int change_cellule(int, int);
void carre_cellule(int**, int**, int, int, int, int);
bool meme_grille(int**, int**, int, int);
void vider_grille(int**, int);