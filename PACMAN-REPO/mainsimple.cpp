
#include <allegro.h>


int main()
{

	allegro_init();
	install_keyboard();
	install_mouse();

	set_color_depth(32);//formato grafico bits
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);


	BITMAP *buffer = create_bitmap(640, 480);
	BITMAP *fondo;
	BITMAP *fondo2;
	BITMAP *cursor;


	clear_to_color(buffer, 0x333333);
	fondo = load_bitmap("fndo1.bmp",NULL);
	fondo2 = load_bitmap("fndo2.bmp",NULL);
	cursor = load_bitmap("cursor.bmp",NULL);

    bool salida = false;


	while ( !salida )
	{
         // posicion del boton
         if ( mouse_x > 270 && mouse_x < 370 &&
              mouse_y > 295 && mouse_y < 340)
         {
            blit(fondo2, buffer, 0, 0, 0, 0, 640, 480);

            //pulsa el boton izquierdo y  para el derecho (!(mouse_b & 2))
            if ( mouse_b & 1 )
            {
                  salida = true;
            }
         }else{
            blit(fondo, buffer, 0, 0, 0, 0, 640, 480);
         }

         masked_blit(cursor, buffer, 0, 0, mouse_x, mouse_y, 13,22);

	     blit(buffer, screen, 0, 0, 0, 0, 640, 480);

          if ( key[KEY_ESC] )
          {
               salida = true;
          }

    }


    salida = false;
	destroy_bitmap(fondo);
	destroy_bitmap(fondo2);

	return 0;
}
END_OF_MAIN();
