#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include<stdio.h>

typedef struct animal{
    char nome[30];
    ALLEGRO_BITMAP * imagem;
    // som do animal
}Animal;

void modo1(ALLEGRO_DISPLAY *janela); // som +  foto de animais, objetos
void modo2(ALLEGRO_DISPLAY *janela); // silaba inicial do animal + foto de animais, objetos
void modo3(ALLEGRO_DISPLAY *janela); // silabas são iguais ou diferentes, KA KA, KA LA
void modo4(ALLEGRO_DISPLAY *janela); // palavras são iguais ou diferentes, faca e vaca
void menu(ALLEGRO_DISPLAY *janela);


int main(){

    al_init();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_mouse();
    
    ALLEGRO_DISPLAY *janela = NULL;
    janela = al_create_display(1350, 700);
    al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
    al_set_window_title(janela, "Jogo da audição");
    
    //menu(janela);
    modo1(janela);
   // modo2(janela);
   // modo3(janela);
   // modo4(janela);
    return 0;
}

void modo1(ALLEGRO_DISPLAY *janela){
    Animal aguia, baleia, cabra, cachorro, camelo, caranguejo, cavalo, cobra, coelho, coruja;
    Animal elefante, galo, gato, girafa, leao, lobo, macaco, passarinho, pato, peixe;
    Animal porco, sapo, tatu, tigre, touro, vaca, zebra;

    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
    
    ALLEGRO_BITMAP *botao_sair = NULL, *area_central = 0;
    ALLEGRO_FONT *wood = NULL;
    ALLEGRO_FONT *cubic = NULL;
    ALLEGRO_FONT *elfic = NULL;
    ALLEGRO_FONT *sculock = NULL;

    ALLEGRO_BITMAP * wallpaper = NULL;
    
    

    
    
    wood = al_load_font("fontes/wood.ttf", 70, 0);
    cubic = al_load_font("fontes/cubic.ttf", 70, 0);
    elfic = al_load_font("fontes/orderElfic.ttf", 70, 0);
    sculock = al_load_font("fontes/sculock.ttf", 70, 0);


  
    
    wallpaper = al_load_bitmap("img/wallpaper.jpg");

    strcpy(aguia.nome, "aguia");
    aguia.imagem = al_load_bitmap("img/aguia.png");

    strcpy(caranguejo.nome, "caranguejo");
    caranguejo.imagem = al_load_bitmap("img/caranguejo.jpg");

    strcpy(baleia.nome, "baleia");
    baleia.imagem = al_load_bitmap("img/baleia.jpg");

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

    fila_eventos = al_create_event_queue();
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));
    

    /* Loop principal do jogo */
    while (1){
        ALLEGRO_EVENT evento;
        ALLEGRO_TIMEOUT timeout;
        al_init_timeout(&timeout, 0.05);

        int tem_eventos = al_wait_for_event_until(fila_eventos, &evento, &timeout);
 
        if (tem_eventos && evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            break;
        }
        
        // Configura a janela


        al_draw_bitmap(wallpaper, 0, 0, 0);
        al_draw_text(sculock, al_map_rgb(0, 0, 0), 1350 , 50, ALLEGRO_ALIGN_RIGHT, "Qual animal "); 
        al_draw_text(sculock, al_map_rgb(0, 0, 0), 1350 , 90, ALLEGRO_ALIGN_RIGHT, "emite esse som? ");    
        al_draw_bitmap(vaca.imagem, 0, 0, 0);
        al_draw_bitmap(caranguejo.imagem, 0, 390, 0);
        al_draw_bitmap(baleia.imagem, 450, 0, 0);
        al_draw_bitmap(tigre.imagem, 450, 390, 0);
        al_flip_display();

    }

    al_destroy_font(sculock);
    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);










}

void modo2(ALLEGRO_DISPLAY *janela){


    ALLEGRO_BITMAP * wallpaper = NULL;
    wallpaper = al_load_bitmap("img/wallpaper.jpg");


    janela = al_create_display(1350, 700);
    
    al_draw_bitmap(wallpaper, 0, 0, 0);
    al_flip_display();
    al_rest(2);
    al_destroy_display(janela);
    
}



