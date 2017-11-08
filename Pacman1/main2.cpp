#include <iostream>
#include <allegro.h>
#define MAXFILAS 20
#define MAXCOLS 31
BITMAP *buffer;
BITMAP *roca;
BITMAP *pacbmp;
BITMAP *pacman

int dir = 0;
int px = 30*10;
int py = 30*10;
using namespace std;

char mapa[MAXFILAS][MAXCOLS]={
    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
    "X           XXXXX           X",
    "X XXX XXXXX XXXXX XXXXX XXX X",
    "X XXX XXXXX XXXXX XXXXX XXX X",
    "X                           X",
    "X XXX XX XXXXXXXXXXX XX XXX X",
    "X     XX     XXX     XX     X",
    "X XXX XXXXXX XXX XXXXXX XXX X",
    "X XXX XX             XX XXX X",
    "X     XX             XX     X",
    "X     XX             XX     X",
    "X XXX XX             XX XXX X",
    "X XXX XXXXXX XXX XXXXXX XXX X",
    "X     XX     XXX     XX     X",
    "X XXX XX XXXXXXXXXXX XX XXX X",
    "X                           X",
    "X XXX XXXXX XXXXX XXXXX XXX X",
    "X XXX XXXXX XXXXX XXXXX XXX X",
    "X                           X",
    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
};
void dibujar_mapa(){
    int row,col;
    for(row=0;row<MAXFILAS;row++){
        for(col=0;col<MAXCOLS;col++){
            if(mapa[row][col]=='X'){
                draw_sprite(buffer,roca,col*30,row*30);
            }
        }

    }
}
void pantalla(){
    blit(buffer,screen,0,0,0,0,880,600);
}
void dibujar_personaje(){}
    blit(pacbmp,pacman,dir*33,0,0,0,33,33);
    draw_sprite(buffer,pacman,px,py);



int main()
{
    allegro_init();
    install_keyboard();
    install_mouse();

    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,880,600,0,0);
    buffer = create_bitmap(880,600);
    roca = load_bitmap("roca.bmp",NULL);
    pacbmp = load_bitmap("pacman",NULL);
    pacman = create_bitmap(33,33);

    while(!key[KEY_ESC]){
        if(key[KEY_RIGHT])
            dir = 1;
        else if(key[KEY_LEFT])
            dir = 0;
        else if(key[KEY_UP])
            dir = 2;
        else if(key[KEY_DOWN])
            dir = 3;

        if(dir == 0)px -=30;
        if(dir == 1)px +=30;
        if(dir == 2)py -=30;
        if(dir == 3)py +=30;
        clear(buffer);
        dibujar_mapa();
        dibujar_personaje();
        pantalla();
        rest(70);

        clear(pacman);
        blit(pacbmp,pacman,4*33,0,0,0,33,33);
        draw_sprite(buffer,pacman,px,py);
        pantalla();
        rest(90);


    }
    return 0;
}
END_OF_MAIN();

