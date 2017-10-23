#include <allegro5/allegro.h>
#include "src/initializer.h"


int main(){
    al_init();
    ALLEGRO_BITMAP * aguia = NULL;
    ALLEGRO_BITMAP * baleia = NULL;
    ALLEGRO_BITMAP * cabra = NULL;
    ALLEGRO_BITMAP * cachorro = NULL;
    ALLEGRO_BITMAP * camelo = NULL;
    ALLEGRO_BITMAP * caranguejo = NULL;
    ALLEGRO_BITMAP * cavalo = NULL;
    ALLEGRO_BITMAP * cobra = NULL;
    ALLEGRO_BITMAP * coelho = NULL;
    ALLEGRO_BITMAP * coruja = NULL;
    ALLEGRO_BITMAP * elefante = NULL;
    ALLEGRO_BITMAP * galo = NULL;
    ALLEGRO_BITMAP * gato = NULL;
    ALLEGRO_BITMAP * girafa = NULL;
    ALLEGRO_BITMAP * leao = NULL;
    ALLEGRO_BITMAP * lobo = NULL;
    ALLEGRO_BITMAP * macaco = NULL;
    ALLEGRO_BITMAP * passarinho = NULL;
    ALLEGRO_BITMAP * pato = NULL;
    ALLEGRO_BITMAP * peixe = NULL;
    ALLEGRO_BITMAP * porco = NULL;
    ALLEGRO_BITMAP * sapo = NULL;
    ALLEGRO_BITMAP * tatu = NULL;
    ALLEGRO_BITMAP * tigre = NULL;
    ALLEGRO_BITMAP * touro = NULL;
    ALLEGRO_BITMAP * vaca = NULL;
    ALLEGRO_BITMAP * zebra = NULL;

    ALLEGRO_DISPLAY * janela = NULL;

    aguia = al_load_bitmap("img/aguia.jpg");
    baleia = al_load_bitmap("img/baleia.png");
    cabra = al_load_bitmap("img/cabra.jpg");
    cachorro = al_load_bitmap("img/cachorro.jpeg");
    camelo = al_load_bitmap("img/camelo.jpg");
    caranguejo = al_load_bitmap("img/caranguejo.jpg");
    cavalo = al_load_bitmap("img/cavalo.jpg");
    cobra = al_load_bitmap("img/cobra.jpg");
    coelho = al_load_bitmap("img/coelho.jpg");
    coruja = al_load_bitmap("img/coruja.jpg");
    elefante = al_load_bitmap("img/elefante.jpg");
    galo = al_load_bitmap("img/galo.jpg");
    gato = al_load_bitmap("img/gato.jpg");
    girafa = al_load_bitmap("img/girafa.jpg");
    leao = al_load_bitmap("img/leao.jpg");
    lobo = al_load_bitmap("img/lobo.jpg");
    macaco = al_load_bitmap("img/macaco.jpg");
    passarinho = al_load_bitmap("img/pato.png");
    pato = al_load_bitmap("img/aguia.jpg");
    peixe = al_load_bitmap("img/peixe.jpg");
    porco = al_load_bitmap("img/porco.jpg");
    sapo = al_load_bitmap("img/sapo.jpg");
    tatu = al_load_bitmap("img/tatu.png");
    tigre = al_load_bitmap("img/tigre.jpg");
    touro = al_load_bitmap("img/touro.jpg");
    vaca = al_load_bitmap("img/vaca.jpg");
    zebra = al_load_bitmap("img/zebra.jpg");

    al_init_image_addon();

    janela = al_create_display(640, 480); // cria a janela
    al_draw_bitmap(vaca, 0, 0, 0); // imprime a imagem na tela
    al_flip_display(); // atualiza a tela


    al_rest(10.0); // Segura a execução por 10 segundos
    al_destroy_display(janela); //destroy

    return 0;
}
