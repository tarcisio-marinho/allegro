#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include<stdio.h>

typedef struct animal{
    char nome[30];
    ALLEGRO_BITMAP * imagem;
    // som do animal
}Animal;

void modo1(ALLEGRO_DISPLAY *janela); // som +  foto de animais, objetos
void modo2(); // silaba inicial do animal + foto de animais, objetos
void modo3(); // silabas são iguais ou diferentes, KA KA, KA LA
void modo4(); // palavras são iguais ou diferentes, faca e vaca

int main(){

    al_init();
    al_init_image_addon();

    ALLEGRO_DISPLAY *janela = NULL;

    modo1(janela);
    return 0;
}

void modo1(ALLEGRO_DISPLAY *janela){
    Animal aguia, baleia, cabra, cachorro, camelo, caranguejo, cavalo, cobra, coelho, coruja;
    Animal elefante, galo, gato, girafa, leao, lobo, macaco, passarinho, pato, peixe;
    Animal porco, sapo, tatu, tigre, touro, vaca, zebra;

    strcpy(aguia.nome, "aguia");
    aguia.imagem = al_load_bitmap("img/aguia.png");

    strcpy(baleia.nome, "baleia");
    baleia.imagem = al_load_bitmap("img/baleia.png");

    strcpy(cabra.nome, "cabra");
    cabra.imagem = al_load_bitmap("img/cabra.jpg");

    strcpy(cachorro.nome, "cachorro");
    cachorro.imagem = al_load_bitmap("img/cachorro.jpeg");

    strcpy(camelo.nome, "camelo");
    camelo.imagem = al_load_bitmap("img/camelo.JPG");

    strcpy(cavalo.nome, "cavalo");
    cavalo.imagem = al_load_bitmap("img/cavalo.jpg");

    strcpy(cobra.nome, "cobra");
    cobra.imagem = al_load_bitmap("img/cobra.jpg");

    strcpy(coelho.nome, "coelho");
    coelho.imagem = al_load_bitmap("img/coelho.jpg");

    strcpy(coruja.nome, "coruja");
    coruja.imagem = al_load_bitmap("img/coruja.jpg");

    strcpy(elefante.nome, "elefante");
    elefante.imagem = al_load_bitmap("img/elefante.jpg");

    strcpy(galo.nome, "galo");
    galo.imagem = al_load_bitmap("img/galo.jpg");

    strcpy(gato.nome, "gato");
    gato.imagem = al_load_bitmap("img/gato.jpg");

    strcpy(girafa.nome, "girafa");
    girafa.imagem = al_load_bitmap("img/girafa.jpg");

    strcpy(leao.nome, "leao");
    leao.imagem = al_load_bitmap("img/leao.jpeg");

    strcpy(lobo.nome, "lobo");
    lobo.imagem = al_load_bitmap("img/lobo.jpg");

    strcpy(macaco.nome, "macaco");
    macaco.imagem = al_load_bitmap("img/macaco.jpeg");

    strcpy(passarinho.nome, "passarinho");
    passarinho.imagem = al_load_bitmap("img/passarinho.jpg");

    strcpy(pato.nome, "pato");
    pato.imagem = al_load_bitmap("img/pato.jpg");

    strcpy(peixe.nome, "peixe");
    peixe.imagem = al_load_bitmap("img/peixe.jpg");

    strcpy(porco.nome, "porco");
    porco.imagem = al_load_bitmap("img/porco.jpg");

    strcpy(sapo.nome, "sapo");
    sapo.imagem = al_load_bitmap("img/sapo.jpeg");

    strcpy(tatu.nome, "tatu");
    tatu.imagem = al_load_bitmap("img/tatu.jpg");

    strcpy(tigre.nome, "tigre");
    tigre.imagem = al_load_bitmap("img/tigre.jpg");


    strcpy(touro.nome, "touro");
    touro.imagem = al_load_bitmap("img/touro.jpeg");


    strcpy(vaca.nome, "vaca");
    vaca.imagem = al_load_bitmap("img/vaca.jpg");

    strcpy(zebra.nome, "zebra");
    zebra.imagem = al_load_bitmap("img/zebra.jpg");



    // Configura a janela
    janela = al_create_display(1920, 1080);

    al_draw_bitmap(vaca.imagem, 0, 0, 0);
    al_draw_bitmap(cavalo.imagem, 0, 500, 0);
    al_draw_bitmap(galo.imagem, 800, 0, 0);
    al_draw_bitmap(aguia.imagem, 800, 500, 0);
    al_flip_display();
    al_rest(10.0);
    al_destroy_display(janela);










}





