#include <allegro5/allegro.h>

int main(){
    ALLEGRO_DISPLAY *janela = NULL;
    ALLEGRO_BITMAP *imagem = NULL;

    al_init();
    al_init_image_addon();

    imagem = al_load_bitmap("teste.jpg"); // carrega a imagem na memoria

    janela = al_create_display(640, 480); // cria a janela
    al_draw_bitmap(imagem, 0, 0, 0); // imprime a imagem na tela
    al_flip_display(); // atualiza a tela


    al_rest(10.0); // Segura a execução por 10 segundos
    al_destroy_display(janela); //destroy

    return 0;
}
