#include <iostream>
#include <allegro.h>
#include <cstdlib>

#define MAXFILAS 20
#define MAXCOLS 31
BITMAP *buffer;
BITMAP *roca;
BITMAP *pacbmp;
BITMAP *pacman;
BITMAP *comida;
BITMAP *enemigobmp;
BITMAP *enemigo;
BITMAP *muertebmp;

int anteriorpx;
int anteriorpy;
int dir = 4;
int px = 30*10;
int py = 30*11;
int fdir = 0;
int _x=30*14, _y=30*15;
using namespace std;

char mapa[MAXFILAS][MAXCOLS]={
  "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
  "X  o |o o o XXXXX o o o| o  X",
  "X XXX XXXXX XXXXX XXXXX XXX X",
  "XoXXX XXXXX XXXXX XXXXX XXXoX",
  "X      o|o   o o   o|o      X",
  "XoXXXoXX XXXXXXXXXXX XXoXXXoX",
  "X    |XX    |XXX|    XX     X",
  "XoXXXoXXXXXX XXX XXXXXXoXXXoX",
  "X XXXoXX ooo|ooo|ooo XXoXXX X",
  " o   |XX XXXXXXXXXXX XX|   o ",
  "X XXXoXX XXXXXXXXXXX XXoXXX X",
  "XoXXXoXX oo |ooo|ooo XXoXXXoX",
  "X XXXoXXXXXX XXX XXXXXXoXXX X",
  "X     XX     XXX     XX     X",
  "X XXXoXX XXXXXXXXXXX XXoXXX X",
  "XoXXX| o| o o o o o |o |XXXoX",
  "X XXXoXXXX XXXXXXXX XXX XXX X",
  "XoXXXoXXXX          XXX XXXoX",
  "X  o |o o  XXXXXXXX o o| o  X",
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
void choque_pacman(){
    if((py==_y && px==_x)||(anteriorpx==_x&&anteriorpy ==_y)){
        for(int j=0;j<5;j++){
            clear (pacman);
            clear(buffer);
            dibujar_mapa();

            blit(muertebmp,pacman,j*33,0,0,0,33,33);
            draw_sprite(buffer,pacman,px,py);
            pantalla();
            rest(80);
        }
        px=30*14;
        py=30*17;
        dir=4;
    }
}
void dibujar_fantasma(){
    blit(enemigobmp,enemigo,0,0,0,0,33,33);
    draw_sprite(buffer,enemigo,_x,_y);
}
void fantasma(){
    dibujar_fantasma();
    choque_pacman();
    if(mapa[_y/30][_x/30]=='|')fdir=rand()%4;
    if (fdir==0){
        if(mapa[_y/30][(_x-30)/30] != 'X') _x-=30;
        else fdir=rand()%3;
    }
    if (fdir==1){
        if(mapa[_y/30][(_x+30)/30] != 'X') _x+=30;
        else fdir=rand()%3;
    }
    if (fdir==2){
        if(mapa[(_y-30)/30][(_x)/30] != 'X') _y-=30;
        else fdir=rand()%3;
    }
    if (fdir==3){
        if(mapa[(_y+30)/30][(_x)/30] != 'X') _y+=30;
        else fdir=rand()%3;
    }
    if(_x <= -30)_x=870;
          else if(_x >=870) _x= -30;

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
    enemigo= create_bitmap(30,30);
    enemigobmp= load_bitmap("enemigo.bmp",NULL);
    muertebmp= load_bitmap("muerte.bmp",NULL);



    while(!key[KEY_ESC] && game_over()){
        anteriorpx=px;
        anteriorpy=py;
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
        if(px <= -30) px=870;
          else if(px >=870) px= -30;
        clear(buffer);
        dibujar_mapa();
        dibujar_personaje();
        fantasma();
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

