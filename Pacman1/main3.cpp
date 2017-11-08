#include <iostream>
#include <allegro.h>
#define MAXFILAS 20
#define MAXCOLS 31
BITMAP *buffer;
BITMAP *roca;
BITMAP *pacbmp;
BITMAP *pacman;
BITMAP *comida;

int dir = 0;
int px = 30*10;
int py = 30*10;
using namespace std;

char mapa[MAXFILAS][MAXCOLS]={
    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
    "X      o o  XXXXX  o o      X",
    "X XXX XXXXX XXXXX XXXXX XXX X",
    "X XXX XXXXX XXXXX XXXXX XXX X",
    "X                           X",
    "X XXX XX XXXXXXXXXXX XX XXX X",
    "X     XX     XXX     XX     X",
    "X XXX XXXXXX XXX XXXXXX XXX X",
    "X XXX XX o         o XX XXX X",
    "      XX             XX      ",
    "X     XX             XX     X",
    "X XXX XX o         o XX XXX X",
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
             else if(mapa[row][col]=='o'){
                 draw_sprite(buffer,comida,col*30,row*30);
                 if(py/30 ==row && px/30== col){
                        mapa[row][col]=' ';

                 }
            }
        }

    }
}
void pantalla(){
    blit(buffer,screen,0,0,0,0,880,600);
}
void dibujar_personaje(){
    blit(pacbmp,pacman,dir*33,0,0,0,33,33);
    draw_sprite(buffer,pacman,px,py);
}
bool game_over(){
    int row,col;
    for(row=0;row<MAXFILAS;row++){
        for(col=0;col<MAXCOLS;col++){
            if(mapa[row][col]=='o') return true;
        }
    }
    return false;
}

int main()
{
    allegro_init();
    install_keyboard();
    install_mouse();

    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,880,600,0,0);
    buffer = create_bitmap(880,600);
    roca = load_bitmap("roca.bmp",NULL);
    pacbmp = load_bitmap("pacman.bmp",NULL);
    pacman = create_bitmap(33,33);
    comida= load_bitmap("Comida.bmp",NULL);


    while(!key[KEY_ESC] && game_over()){
        if(key[KEY_RIGHT])
            dir = 1;
        else if(key[KEY_LEFT])
            dir = 0;
        else if(key[KEY_UP])
            dir = 2;
        else if(key[KEY_DOWN])
            dir = 3;

        if(dir == 0){
            if(mapa[py/30][(px-30)/30]!='X')
                px -=30;
            else  dir=4;
        }
        if(dir == 1){
            if((mapa[py/30][(px+30)/30])!='X'){
                px +=30;}
            else dir=4;
        }
        if(dir == 2){
            if(mapa[(py-30)/30][(px)/30]!='X')
            py -=30;
            else dir=4;

        }
        if(dir == 3){
            if(mapa[(py+30)/30][px/30]!='X'){
                py +=30;}
            else dir=4;
        }
        if(px <= -30){ px=870;}
          else if(px >=870){ px= -30;}
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

