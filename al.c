#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include<stdio.h>



int main(){

    ALLEGRO_DISPLAY *janela = NULL;

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

    // Inicializa a Allegro
    al_init();

    // Inicializa o add-on para utilização de imagens
    al_init_image_addon();

    // Configura a janela
    janela = al_create_display(1920, 1080);

    // Carrega a imagem
    aguia = al_load_bitmap("img/aguia.png");
    baleia = al_load_bitmap("img/baleia.png");
    cabra = al_load_bitmap("img/cabra.jpg");
    cachorro = al_load_bitmap("img/cachorro.jpeg");
    camelo = al_load_bitmap("img/camelo.JPG");
    caranguejo = al_load_bitmap("img/caranguejo.jpg");
    cavalo = al_load_bitmap("img/cavalo.jpg");
    cobra = al_load_bitmap("img/cobra.jpg");
    coelho = al_load_bitmap("img/coelho.jpg");
    coruja = al_load_bitmap("img/coruja.jpg");
    elefante = al_load_bitmap("img/elefante.jpg");
    galo = al_load_bitmap("img/galo.jpg");
    gato = al_load_bitmap("img/gato.jpg");
    girafa = al_load_bitmap("img/girafa.jpg");
    leao = al_load_bitmap("img/leao.jpeg");
    lobo = al_load_bitmap("img/lobo.jpg");
    macaco = al_load_bitmap("img/macaco.jpeg");
    passarinho = al_load_bitmap("img/pato.jpg");
    pato = al_load_bitmap("img/aguia.jpg");
    peixe = al_load_bitmap("img/peixe.jpg");
    porco = al_load_bitmap("img/porco.jpg");
    sapo = al_load_bitmap("img/sapo.jpeg");
    tatu = al_load_bitmap("img/tatu.jpg");
    tigre = al_load_bitmap("img/tigre.jpg");
    touro = al_load_bitmap("img/touro.jpeg");
    vaca = al_load_bitmap("img/vaca.jpg");
    zebra = al_load_bitmap("img/zebra.jpg");


    al_draw_bitmap(zebra, 0, 0, 0);
    al_flip_display();
    al_rest(10.0);
    al_destroy_display(janela);

    return 0;
}
