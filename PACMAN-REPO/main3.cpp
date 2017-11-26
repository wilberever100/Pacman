#include <iostream>
#include <allegro.h>
#include <cstdlib>
#define MAXFILAS 20
#define MAXCOLS 31
#define FILAS 20
#define COLS 21
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
///////////////OPCION niveles///////////////
BITMAP *bufferNiveles;
BITMAP *Niv1bmp;
BITMAP *Niv2bmp;
BITMAP *Niv3bmp;
BITMAP *btnNivel1;
BITMAP *btnNivel2;
BITMAP *btnNivel3;
char mapaniveles[FILAS][COLS]={
  "XXXXXXXXXXXXXXXXXXXX",
  "X                  X",
  "X                  X",
  "X     P            X",
  "X                  X",
  "X                  X",
  "X                  X",
  "X                  X",
  "X     S            X",
  "X                  X",
  "X                  X",
  "X                  X",
  "X                  X",
  "X     T            X",
  "X                  X",
  "X                  X",
  "X                  X",
  "X       M          X",
  "X                  X",
  "XXXXXXXXXXXXXXXXXXXX",
};

void MENU_Nivel()
{
    int fila,colum;
    for(fila=0;fila<MAXFILAS;fila++){
        for(colum=0;colum<MAXCOLS;colum++){
            if(mapaniveles[fila][colum]=='X'){
                draw_sprite(bufferNiveles,roca,colum*30,fila*30);
            }
            if(mapaniveles[fila][colum]=='P'){
                draw_sprite(bufferNiveles,Niv1bmp,colum*30,fila*30);
            }
            if(mapaniveles[fila][colum]=='S'){
                draw_sprite(bufferNiveles,Niv2bmp,colum*30,fila*30);
            }
            if(mapaniveles[fila][colum]=='T'){
                draw_sprite(bufferNiveles,Niv3bmp,colum*30,fila*30);
            }
        }
    }

}
void pantallaNiveles(){
    blit(bufferNiveles,screen,0,0,0,0,600,600);
}
void OpcionNiveles(){
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,600,600,0,0);
    bufferNiveles = create_bitmap(600,600);
    roca = load_bitmap("roj.bmp",NULL);
    Niv1bmp = load_bitmap("nivel01.bmp",NULL);
    btnNivel1 = create_bitmap(43,43);
    Niv2bmp = load_bitmap("nivel02.bmp",NULL);
    btnNivel2 = create_bitmap(43,43);
    Niv3bmp = load_bitmap("nivel03.bmp",NULL);
    btnNivel3 = create_bitmap(43,43);

    bool cerrar=true;
    clear(bufferNiveles);
    MENU_Nivel();
    pantallaNiveles();
    rest(9000);




}

////////////////////INSTRUCCIONEES///////////////////

void MostrarInstrucciones(){
    BITMAP *bufferInstruccion;
    BITMAP *Instruccion;
    BITMAP *RegresarMenu;
    BITMAP *cursor;

    allegro_init();
	install_keyboard();
	install_mouse();

	set_color_depth(32);//formato grafico bits
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);

    Instruccion = load_bitmap("instcciones.bmp",NULL);
    RegresarMenu = load_bitmap("instruccmenu.bmp",NULL);
    cursor = load_bitmap("cursor.bmp",NULL);


    bufferInstruccion = create_bitmap(640,480);
    clear_to_color(bufferInstruccion, 0x333333);


    bool salida = false;


	while ( !salida )
	{
         // posicion del boton PLAY
         if ( mouse_x > 270 && mouse_x < 370 &&
              mouse_y > 295 && mouse_y < 340)
         {
            blit(RegresarMenu, bufferInstruccion, 0, 0, 0, 0, 640, 480);
            //pulsa el boton izquierdo y  para el derecho (!(mouse_b & 2))
            if ( mouse_b & 1 )
            {
                  salida = true;

            }
         }
         else{
            blit(Instruccion, bufferInstruccion, 0, 0, 0, 0, 640, 480);
         }


         masked_blit(cursor, bufferInstruccion, 0, 0, mouse_x, mouse_y, 13,22);

	     blit(bufferInstruccion, screen, 0, 0, 0, 0, 640, 480);


    }

    salida = false;
	destroy_bitmap(RegresarMenu);


}



///////////////PACMAN///////////////////////
char mapa[MAXFILAS][MAXCOLS]={
    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
    "X     o o o    X    o o    oX",
    "X XXX XX XXX  X  XXX XX XXX X",
    "X XXX XX XXX  X  XXX XX XXX X",
    "X o o o o o o o o o o o o o X",
    "X XXX  X XXXXXXXXXXX X XXXX X",
    "X XXX  X      X      X XXXX X",
    "X      XXXXXX X XXXXXX      X",
    "XXXXXX X o o o o o o X XXXXXX",
    "         XXXX   XXXX         ",
    "XXXX X X X         X X X XXXX",
    "   X X X X         X X X X   ",
    "XXXX X X XXXXXXXXXXX X X XXXX",
    "X o o o o o o o o o o o o o X",
    "X XXX  X XXXXXXXXXXX X XXXX X",
    "X XXX  X      X      X XXXX X",
    "X      X XXXX X XXXX X      X",
    "XXXXXXXX X         X XXXXXX X",
    "X o o o    XXXXXXX  o o o o X",
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
            rest(80);//miliseg
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
void Iniciarpacman()
{
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,880,600,0,0);
    buffer = create_bitmap(880,600);
    roca = load_bitmap("roj.bmp",NULL);
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

}





/////////////     //////////////////////////
/////////////MAIN///////////////////////////

int main()
{

//////////////////MENU///////////////////////////////////
    allegro_init();
	install_keyboard();
	install_mouse();

	set_color_depth(32);//formato grafico bits
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);


	BITMAP *bufferMenu = create_bitmap(640, 480);
	BITMAP *Inicio;
	BITMAP *Play;
	BITMAP *Niveles;
	BITMAP *Instruc;
	BITMAP *Salir;
	BITMAP *cursor;
	BITMAP *Score;


	clear_to_color(bufferMenu, 0x333333);
	Inicio = load_bitmap("menuInicio.bmp",NULL);
	Play = load_bitmap("menuPlay.bmp",NULL);
	Niveles=load_bitmap("menuNiveles.bmp",NULL);
	Instruc=load_bitmap("menuInstruc.bmp",NULL);
	Score=load_bitmap("menuScore.bmp",NULL);
	Salir=load_bitmap("menuSalir.bmp",NULL);

	cursor = load_bitmap("cursor.bmp",NULL);


    bool salida = false;


	while ( !salida )
	{
         // posicion del boton PLAY
         if ( mouse_x > 270 && mouse_x < 370 &&
              mouse_y > 295 && mouse_y < 340)
         {
            blit(Play, bufferMenu, 0, 0, 0, 0, 640, 480);
            //pulsa el boton izquierdo y  para el derecho (!(mouse_b & 2))
            if ( mouse_b & 1 )
            {
                  salida = true;
                  Iniciarpacman();
            }
         }

         // NIVELES

         else if ( mouse_x > 265 && mouse_x < 365&&
              mouse_y > 245 && mouse_y < 399 )
         {
            blit(Niveles, bufferMenu, 0, 0, 0, 0, 640, 480);

            //pulsa el boton izquierdo y  para el derecho (!(mouse_b & 2))
            if ( mouse_b & 1 )
            {
                  salida = true;
                  OpcionNiveles();

            }
         }
         else if ( mouse_x > 270 && mouse_x < 370&&
              mouse_y > 220 && mouse_y < 420 )
         {
            blit(Instruc, bufferMenu, 0, 0, 0, 0, 640, 480);

            //pulsa el boton izquierdo y  para el derecho (!(mouse_b & 2))
            if ( mouse_b & 1 )
            {
                  salida = true;
                  MostrarInstrucciones();

            }
         }
         else if ( mouse_x > 270 && mouse_x < 370&&
              mouse_y > 180 && mouse_y < 450 )
         {
            blit(Score, bufferMenu, 0, 0, 0, 0, 640, 480);

            //pulsa el boton izquierdo y  para el derecho (!(mouse_b & 2))
            if ( mouse_b & 1 )
            {
                  salida = true;
                  OpcionNiveles();

            }
         }
         else if ( mouse_x > 270 && mouse_x < 370&&
              mouse_y > 10 && mouse_y < 560 )
         {
            blit(Salir, bufferMenu, 0, 0, 0, 0, 640, 480);

            //pulsa el boton izquierdo y  para el derecho (!(mouse_b & 2))
            if ( mouse_b & 1 )
            {
                  salida = true;
                  //destroy_bitmap(Inicio);
                  destroy_bitmap(Salir);

            }
         }
         else{
            blit(Inicio, bufferMenu, 0, 0, 0, 0, 640, 480);
         }


         masked_blit(cursor, bufferMenu, 0, 0, mouse_x, mouse_y, 13,22);

	     blit(bufferMenu, screen, 0, 0, 0, 0, 640, 480);


    }

    salida = false;
    destroy_bitmap(Play);
	destroy_bitmap(Instruc);
	destroy_bitmap(Score);
	destroy_bitmap(Salir);
	destroy_bitmap(Inicio);


    return 0;
}
END_OF_MAIN();

