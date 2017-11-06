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

const int LARGURA_TELA = 1350;
const int ALTURA_TELA = 700;

void modo1(ALLEGRO_DISPLAY *janela); // som +  foto de animais, objetos
void modo2(ALLEGRO_DISPLAY *janela); // silaba inicial do animal + foto de animais, objetos
void modo3(ALLEGRO_DISPLAY *janela); // silabas são iguais ou diferentes, KA KA, KA LA
void modo4(ALLEGRO_DISPLAY *janela); // palavras são iguais ou diferentes, faca e vaca


int main(){
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
    ALLEGRO_BITMAP *quadrado1 = 0, *quadrado2 = 0, *sair = 0;
    ALLEGRO_FONT *fonte = NULL;
    ALLEGRO_BITMAP * wallpaper = NULL;
    ALLEGRO_DISPLAY *janela = NULL;
    al_init();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_mouse();
    
    
    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
    fonte = al_load_font("fontes/coolvetica.ttf", 40, 0);
    al_set_window_title(janela, "Jogo da audição");
    wallpaper = al_load_bitmap("img/wallpaper.png");

    fila_eventos = al_create_event_queue();
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));
    al_register_event_source(fila_eventos, al_get_mouse_event_source());
    
    quadrado1 = al_create_bitmap(200, 200);
    quadrado2 = al_create_bitmap(200, 200);
    sair = al_create_bitmap(100, 100);

    /* Loop para decidir o modo do jogo */
    while(1){
        ALLEGRO_EVENT evento;
        ALLEGRO_TIMEOUT timeout;
        al_init_timeout(&timeout, 0.05);

        int tem_eventos = al_wait_for_event_until(fila_eventos, &evento, &timeout);

        /* Sair */
        if (tem_eventos && evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            return 0;
        }

        /* quadrado1 */
        al_set_target_bitmap(quadrado1);
        if (evento.type == ALLEGRO_EVENT_MOUSE_AXES){
            /* Verificamos se ele está sobre a região do retângulo central */
            if (evento.mouse.x >= 400 &&
                evento.mouse.x <= 600 &&
                evento.mouse.y >= 100 &&
                evento.mouse.y <= 300){
                al_clear_to_color(al_map_rgb(153, 0, 153));
            }
            else{
                al_clear_to_color(al_map_rgb(0, 3, 123));
            }
        }
        /* Ou se o evento foi um clique do mouse */
        else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
            if (evento.mouse.x >= 400 &&
                evento.mouse.x <= 600 &&
                evento.mouse.y >= 100 &&
                evento.mouse.y <= 300){
                modo1(janela);
            }
        }

        /* quadrado2 */
        al_set_target_bitmap(quadrado2);
        if (evento.type == ALLEGRO_EVENT_MOUSE_AXES){
            /* Verificamos se ele está sobre a região do retângulo central */
            if (evento.mouse.x >= 400 &&
                evento.mouse.x <= 600 &&
                evento.mouse.y >= 400 &&
                evento.mouse.y <= 600){
                al_clear_to_color(al_map_rgb(153, 0, 153));
            }
            else{
                al_clear_to_color(al_map_rgb(0, 3, 123));
            }
        }
        /* Ou se o evento foi um clique do mouse */
        else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
            if (evento.mouse.x >= 440 &&
                evento.mouse.x <= 860 &&
                evento.mouse.y >= 0 &&
                evento.mouse.y <= 320){
                //modo2(janela);
            }
        }

        /* sair */
        al_set_target_bitmap(sair);
        if (evento.type == ALLEGRO_EVENT_MOUSE_AXES){
            /* Verificamos se ele está sobre a região do retângulo central */
            if (evento.mouse.x >=  1250 &&
                evento.mouse.x <=  1350 &&
                evento.mouse.y >= 600 &&
                evento.mouse.y <= 700 ){
                al_clear_to_color(al_map_rgb(145, 9, 9));
            }
            else{
                al_clear_to_color(al_map_rgb(255, 0, 0));
            }
        }
        /* Ou se o evento foi um clique do mouse */
        else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
            if (evento.mouse.x >= 1250 &&
                evento.mouse.x <= 1350 &&
                evento.mouse.y >= 600 &&
                evento.mouse.y <= 700){
                return 0;
            }
        }
        al_set_target_bitmap(al_get_backbuffer(janela));
        al_draw_bitmap(wallpaper, 0, 0, 0);
        al_draw_bitmap(quadrado1, 400, 100, 0);
        al_draw_bitmap(quadrado2, 400, 400, 0);
        al_draw_bitmap(sair, 1250, 600, 0);

        al_draw_text(fonte, al_map_rgb(0, 0, 0), 1000 , 0, ALLEGRO_ALIGN_RIGHT, "Bem vindo ao jogo da audição");
        al_draw_text(fonte, al_map_rgb(255, 255, 255), 500 , 100, ALLEGRO_ALIGN_CENTRE, "Modo 1");
        al_draw_text(fonte, al_map_rgb(255, 255, 255), 500 , 400, ALLEGRO_ALIGN_CENTRE, "Modo 2");
        al_draw_text(fonte, al_map_rgb(0, 0, 0), 1000 , 100, ALLEGRO_ALIGN_CENTRE, "Escolha qual animal emite o som tocado");
        al_draw_text(fonte, al_map_rgb(0, 0, 0), 900 , 400, ALLEGRO_ALIGN_CENTRE, "Diferença entre sílabas");
        al_draw_text(fonte, al_map_rgb(255, 255, 255), 1300 , 600, ALLEGRO_ALIGN_CENTRE, "Sair");
        
        
        al_flip_display();
    }


   al_destroy_font(fonte);
   al_destroy_event_queue(fila_eventos);
   al_destroy_display(janela);
    return 0;
}

void modo1(ALLEGRO_DISPLAY *janela){
    Animal aguia, baleia, cabra, cachorro, camelo, caranguejo, cavalo, cobra, coelho, coruja;
    Animal elefante, galo, gato, girafa, leao, lobo, macaco, passarinho, pato, peixe;
    Animal porco, sapo, tatu, tigre, touro, vaca, zebra;

    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;

    ALLEGRO_BITMAP *quadrado1 = 0, *quadrado2 = 0, *quadrado3 = 0, *quadrado4 = 0;
    ALLEGRO_FONT *fonte = NULL;

    ALLEGRO_BITMAP * wallpaper = NULL;



    if(1){

        fonte = al_load_font("fontes/coolvetica.ttf", 60, 0);

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

    }

    fila_eventos = al_create_event_queue();
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));
    al_register_event_source(fila_eventos, al_get_mouse_event_source());

    quadrado1 = al_create_bitmap(420, 320);
    quadrado2 = al_create_bitmap(420, 320);
    quadrado3 = al_create_bitmap(420, 320);
    quadrado4 = al_create_bitmap(420, 320);

    /* Loop principal do jogo */

    while (1){
        ALLEGRO_EVENT evento;
        ALLEGRO_TIMEOUT timeout;
        al_init_timeout(&timeout, 0.05);

        int tem_eventos = al_wait_for_event_until(fila_eventos, &evento, &timeout);

        /* Sair */
        if (tem_eventos && evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            exit(-1);
        }
        if(1){



            /* quadrado1 */
            al_set_target_bitmap(quadrado1);
            if (evento.type == ALLEGRO_EVENT_MOUSE_AXES){
                /* Verificamos se ele está sobre a região do retângulo central */
                if (evento.mouse.x >= 0 &&
                    evento.mouse.x <= 420 &&
                    evento.mouse.y >= 0 &&
                    evento.mouse.y <= 320){
                    al_clear_to_color(al_map_rgb(153, 0, 153));
                }
                else{
                    al_clear_to_color(al_map_rgb(0, 3, 123));
                }
            }
            /* Ou se o evento foi um clique do mouse */
            else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                if (evento.mouse.x >= 0 &&
                    evento.mouse.x <= 420 &&
                    evento.mouse.y >= 0 &&
                    evento.mouse.y <= 320){
                    al_clear_to_color(al_map_rgb(255, 255, 255));
                }
            }

            /* quadrado2 */
            al_set_target_bitmap(quadrado2);
            if (evento.type == ALLEGRO_EVENT_MOUSE_AXES){
                /* Verificamos se ele está sobre a região do retângulo central */
                if (evento.mouse.x >= 440 &&
                    evento.mouse.x <=  860 &&
                    evento.mouse.y >=  0&&
                    evento.mouse.y <= 320){
                    al_clear_to_color(al_map_rgb(153, 0, 153));
                }
                else{
                    al_clear_to_color(al_map_rgb(0, 3, 123));
                }
            }
            /* Ou se o evento foi um clique do mouse */
            else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                if (evento.mouse.x >= 440 &&
                    evento.mouse.x <= 860 &&
                    evento.mouse.y >= 0 &&
                    evento.mouse.y <= 320){
                    al_clear_to_color(al_map_rgb(255, 255, 255));
                }
            }

            /* quadrado3 */
            al_set_target_bitmap(quadrado3);
            if (evento.type == ALLEGRO_EVENT_MOUSE_AXES){
                /* Verificamos se ele está sobre a região do retângulo central */
                if (evento.mouse.x >=  0 &&
                    evento.mouse.x <=  420 &&
                    evento.mouse.y >= 360 &&
                    evento.mouse.y <= 680 ){
                    al_clear_to_color(al_map_rgb(153, 0, 153));
                }
                else{
                    al_clear_to_color(al_map_rgb(0, 3, 123));
                }
            }
            /* Ou se o evento foi um clique do mouse */
            else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                if (evento.mouse.x >= 0 &&
                    evento.mouse.x <= 420 &&
                    evento.mouse.y >= 360 &&
                    evento.mouse.y <= 680){
                    al_clear_to_color(al_map_rgb(255, 255, 255));
                }
            }

            /* quadrado4 */
            al_set_target_bitmap(quadrado4);
            if (evento.type == ALLEGRO_EVENT_MOUSE_AXES){
                /* Verificamos se ele está sobre a região do retângulo central */
                if (evento.mouse.x >=  440 &&
                    evento.mouse.x <=  860 &&
                    evento.mouse.y >=  360 &&
                    evento.mouse.y <= 680){
                    al_clear_to_color(al_map_rgb(153, 0, 153));
                }
                else{
                    al_clear_to_color(al_map_rgb(0, 3, 123));
                }
            }
            /* Ou se o evento foi um clique do mouse */
            else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                if (evento.mouse.x >= 440 &&
                    evento.mouse.x <= 860 &&
                    evento.mouse.y >= 360 &&
                    evento.mouse.y <= 680){
                    al_clear_to_color(al_map_rgb(255, 255, 255));
                }
            }


        }










        /* Configura a janela */
        al_set_target_bitmap(al_get_backbuffer(janela));
        al_draw_bitmap(wallpaper, 0, 0, 0);

        /* Desenhamos os retângulos na tela   (410, 320)  */
        al_draw_bitmap(quadrado1, 0, 0, 0);
        al_draw_bitmap(quadrado2, 440, 0, 0);
        al_draw_bitmap(quadrado3, 0, 360, 0);
        al_draw_bitmap(quadrado4, 440, 360, 0);

        al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA , 50, ALLEGRO_ALIGN_RIGHT, "Qual animal emite");
        al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA , 100, ALLEGRO_ALIGN_RIGHT, "esse som? ");
        al_draw_bitmap(vaca.imagem, 0, 0, 0);
        al_draw_bitmap(cabra.imagem, 0, 390, 0);
        al_draw_bitmap(baleia.imagem, 450, 0, 0);
        al_draw_bitmap(tigre.imagem, 450, 390, 0);
        al_flip_display();

    }

    al_destroy_font(fonte);
    al_destroy_event_queue(fila_eventos);

}





void modo2(ALLEGRO_DISPLAY *janela){


    ALLEGRO_BITMAP * wallpaper = NULL;
    wallpaper = al_load_bitmap("img/wallpaper.jpg");


    
    al_draw_bitmap(wallpaper, 0, 0, 0);
    al_flip_display();
    al_rest(2);
    al_destroy_display(janela);

}
