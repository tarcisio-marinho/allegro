#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

// SÓ TROCAR A COR QUANDO CLICAR - escolher o animal
// quantos errou e quantos acertou
// nome da criança que vai jogar
// salvar em arquivo
// botão para ler do arquivo qual score das crianças
// botão de como jogar
// animação de erro e acerto


typedef struct animal{
    char nome[30];
    ALLEGRO_BITMAP * imagem;
    ALLEGRO_SAMPLE * som;
    ALLEGRO_SAMPLE_ID *id;
}Animal;

typedef struct salvar{
    char nome[30];
    int acertos, erros;
}Salvar;

const int LARGURA_TELA = 1350;
const int ALTURA_TELA = 700;

ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;

void modo1(ALLEGRO_DISPLAY *janela, char nome[]); // som +  foto de animais, objetos
void acertou(ALLEGRO_DISPLAY *janela, char string[]);
void errou(ALLEGRO_DISPLAY *janela, char string[]);
void salvar(Salvar jogador);
void instrucoes(ALLEGRO_DISPLAY *janela);
void ler();

void init(){
    al_init();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_mouse();
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(1);
    al_install_keyboard();
}

int main(){
    ALLEGRO_BITMAP *quadrado1 = 0, *quadrado2 = 0, *sair = 0, *como_jogar = 0;
    ALLEGRO_FONT *fonte = NULL;
    ALLEGRO_BITMAP * wallpaper = NULL;
    ALLEGRO_DISPLAY *janela = NULL;
    
    char nome[30];

    init();


    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
    fonte = al_load_font("fontes/coolvetica.ttf", 40, 0);
    al_set_window_title(janela, "Jogo da audição");
    wallpaper = al_load_bitmap("img/wallpaper.png");

    fila_eventos = al_create_event_queue();
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));
    al_register_event_source(fila_eventos, al_get_mouse_event_source());
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
 

    quadrado1 = al_create_bitmap(200, 200);
    quadrado2 = al_create_bitmap(200, 200);
    sair = al_create_bitmap(100, 100);
    como_jogar = al_create_bitmap(100, 100);

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
                modo1(janela, nome);
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
                evento.mouse.x <= 600 &&
                evento.mouse.y >= 400 &&
                evento.mouse.y <= 600){
                ler();
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

        /* como jogar */
        al_set_target_bitmap(como_jogar);
        if (evento.type == ALLEGRO_EVENT_MOUSE_AXES){
            /* Verificamos se ele está sobre a região do retângulo central */
            if (evento.mouse.x >=  1250 &&
                evento.mouse.x <=  1350 &&
                evento.mouse.y >= 300 &&
                evento.mouse.y <= 400 ){
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
                // INSTRUÇÃO DE JOGO
                instrucoes(janela);
            }
        }
        al_set_target_bitmap(al_get_backbuffer(janela));
        al_draw_bitmap(wallpaper, 0, 0, 0);
        al_draw_bitmap(quadrado1, 400, 100, 0);
        al_draw_bitmap(quadrado2, 400, 400, 0);
        al_draw_bitmap(sair, 1250, 600, 0);
        al_draw_bitmap(como_jogar, 1250, 300, 0);

        al_draw_text(fonte, al_map_rgb(0, 0, 0), 1000 , 0, ALLEGRO_ALIGN_RIGHT, "Bem vindo ao jogo da audição");
        al_draw_text(fonte, al_map_rgb(255, 255, 255), 500 , 100, ALLEGRO_ALIGN_CENTRE, "Jogar");
        al_draw_text(fonte, al_map_rgb(255, 255, 255), 500 , 400, ALLEGRO_ALIGN_CENTRE, "Pontuação");
        al_draw_text(fonte, al_map_rgb(0, 0, 0), 1000 , 100, ALLEGRO_ALIGN_CENTRE, "Escolha qual animal emite o som tocado");
        al_draw_text(fonte, al_map_rgb(0, 0, 0), 900 , 400, ALLEGRO_ALIGN_CENTRE, "Ver a pontuação das crianças");
        al_draw_text(fonte, al_map_rgb(255, 255, 255), 1300 , 600, ALLEGRO_ALIGN_CENTRE, "Sair");
        al_draw_text(fonte, al_map_rgb(255, 255, 255), 1300 , 300, ALLEGRO_ALIGN_CENTRE, "Como");
        al_draw_text(fonte, al_map_rgb(255, 255, 255), 1300 , 340, ALLEGRO_ALIGN_CENTRE, "jogar");


        al_flip_display();
    }


    al_destroy_font(fonte);
    al_destroy_event_queue(fila_eventos);
    al_destroy_display(janela);
    return 0;
}

void modo1(ALLEGRO_DISPLAY *janela, char nome[]){
    Animal aguia, baleia, cabra, cachorro, camelo, caranguejo, cavalo, cobra, coelho, coruja;
    Animal elefante, galo, gato, girafa, leao, lobo, macaco, passarinho, pato, peixe;
    Animal porco, sapo, tatu, tigre, touro, vaca, zebra;
    
    Salvar jogador;

    int acertos = 0, erros = 0;

    ALLEGRO_BITMAP *quadrado1 = 0, *quadrado2 = 0, *quadrado3 = 0;
    ALLEGRO_BITMAP *quadrado4 = 0, *retornar = 0, *tocar = 0, *proximo = 0;
    ALLEGRO_FONT *fonte = NULL;
    int i = 0, vez = 0, sair = 0;
    ALLEGRO_BITMAP * wallpaper = NULL;

    //ALLEGRO_AUDIO_STREAM *musica = NULL;

    if(1){
        fonte = al_load_font("fontes/coolvetica.ttf", 40, 0);

        wallpaper = al_load_bitmap("img/wallpaper.jpg");

        strcpy(aguia.nome, "aguia");
        aguia.imagem = al_load_bitmap("img/aguia.png");
        aguia.som = al_load_sample("sound/animais/aguia.wav");
        aguia.id = NULL;

        strcpy(caranguejo.nome, "caranguejo");
        caranguejo.imagem = al_load_bitmap("img/caranguejo.jpg");

        strcpy(baleia.nome, "baleia");
        baleia.imagem = al_load_bitmap("img/baleia.jpg");

        strcpy(cabra.nome, "cabra");
        cabra.imagem = al_load_bitmap("img/cabra.jpg");
        cabra.som = al_load_sample("sound/animais/cabra.wav");
        cabra.id = NULL;

        strcpy(cachorro.nome, "cachorro");
        cachorro.imagem = al_load_bitmap("img/cachorro.jpg");
        cachorro.som = al_load_sample("sound/animais/cachorro.wav");
        cachorro.id = NULL;

        strcpy(camelo.nome, "camelo");
        camelo.imagem = al_load_bitmap("img/camelo.jpg");

        strcpy(cavalo.nome, "cavalo");
        cavalo.imagem = al_load_bitmap("img/cavalo.jpg");
        cavalo.som  = al_load_sample("sound/animais/cavalo.wav");
        cavalo.id = NULL;

        strcpy(cobra.nome, "cobra");
        cobra.imagem = al_load_bitmap("img/cobra.jpg");

        strcpy(coelho.nome, "coelho");
        coelho.imagem = al_load_bitmap("img/coelho.jpg");

        strcpy(coruja.nome, "coruja");
        coruja.imagem = al_load_bitmap("img/coruja.jpg");

        strcpy(elefante.nome, "elefante");
        elefante.imagem = al_load_bitmap("img/elefante.jpg");
        elefante.som = al_load_sample("sound/animais/elefante.wav");
        elefante.id = NULL;;

        strcpy(galo.nome, "galo");
        galo.imagem = al_load_bitmap("img/galo.jpg");
        galo.som = al_load_sample("sound/animais/galo.wav");
        galo.id = NULL;

        strcpy(gato.nome, "gato");
        gato.imagem = al_load_bitmap("img/gato.jpg");
        gato.som = al_load_sample("sound/animais/gato.wav");
        gato.id = NULL;

        strcpy(girafa.nome, "girafa");
        girafa.imagem = al_load_bitmap("img/girafa.jpg");

        strcpy(leao.nome, "leao");
        leao.imagem = al_load_bitmap("img/leao.jpeg");
        leao.som = al_load_sample("sound/animais/leao.wav");
        leao.id = NULL;

        strcpy(lobo.nome, "lobo");
        lobo.imagem = al_load_bitmap("img/lobo.jpg");
        lobo.som = al_load_sample("sound/animais/lobo.wav");
        lobo.id = NULL;

        strcpy(macaco.nome, "macaco");
        macaco.imagem = al_load_bitmap("img/macaco.jpeg");
        macaco.som = al_load_sample("sound/animais/macaco.wav");
        macaco.id = NULL;

        strcpy(passarinho.nome, "passarinho");
        passarinho.imagem = al_load_bitmap("img/passarinho.jpg");

        strcpy(pato.nome, "pato");
        pato.imagem = al_load_bitmap("img/pato.jpg");
        pato.som = al_load_sample("sound/animais/pato.wav");
        pato.id = NULL;

        strcpy(peixe.nome, "peixe");
        peixe.imagem = al_load_bitmap("img/peixe.jpg");

        strcpy(porco.nome, "porco");
        porco.imagem = al_load_bitmap("img/porco.jpg");
        porco.som  = al_load_sample("sound/animais/porco.wav");
        porco.id = NULL;

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
        vaca.som = al_load_sample("sound/animais/vaca.wav");
        vaca.id = NULL;

        strcpy(zebra.nome, "zebra");
        zebra.imagem = al_load_bitmap("img/zebra.jpg");

    }
   
        
    //  PARTE 1
    while(sair == 0){
        while(!al_is_event_queue_empty(fila_eventos)){
            quadrado1 = al_create_bitmap(420, 320);
            quadrado2 = al_create_bitmap(420, 320);
            quadrado3 = al_create_bitmap(420, 320);
            quadrado4 = al_create_bitmap(420, 320);
            retornar = al_create_bitmap(100, 100);
            tocar = al_create_bitmap(100, 100);
            
            fila_eventos = al_create_event_queue();
            al_register_event_source(fila_eventos, al_get_display_event_source(janela));
            al_register_event_source(fila_eventos, al_get_mouse_event_source());

            ALLEGRO_EVENT evento;
            ALLEGRO_TIMEOUT timeout;
            al_init_timeout(&timeout, 0.05);

            al_wait_for_event(fila_eventos, &evento);

            int tem_eventos = al_wait_for_event_until(fila_eventos, &evento, &timeout);

            /* Sair */

            if (tem_eventos && evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                exit(-1);
            }


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
                    al_stop_sample(&elefante.id);
                    acertou(janela, "elefante");
                    acertos++;
                    sair = 1;
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
                    al_stop_sample(&elefante.id);
                    errou(janela, "baleia");
                    erros++;
                    sair = 1;
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
                    al_stop_sample(&elefante.id);
                    errou(janela, "cabra");
                    erros++;
                    sair = 1;
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
                    al_stop_sample(&elefante.id);
                    errou(janela, "tigre");
                    erros++;
                    sair = 1;
                }
            }
            /* retornar */
            al_set_target_bitmap(retornar);
            if (evento.type == ALLEGRO_EVENT_MOUSE_AXES){
                /* Verificamos se ele está sobre a região do retângulo central */
                if (evento.mouse.x >=  1250 &&
                    evento.mouse.x <=  1350 &&
                    evento.mouse.y >=  600 &&
                    evento.mouse.y <= 700){
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
                    al_stop_sample(&elefante.id);
                    return;
                }
            }
            /* tocar dnv */
            al_set_target_bitmap(tocar);
            if (evento.type == ALLEGRO_EVENT_MOUSE_AXES){
                /* Verificamos se ele está sobre a região do retângulo central */
                if (evento.mouse.x >=  1250 &&
                    evento.mouse.x <=  1350 &&
                    evento.mouse.y >=  200 &&
                    evento.mouse.y <= 300){
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
                    evento.mouse.y >= 200 &&
                    evento.mouse.y <= 300){
                    al_play_sample(elefante.som, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, elefante.id);
                }
            }

            

            /* Configura a janela */
            al_set_target_bitmap(al_get_backbuffer(janela));
            al_draw_bitmap(wallpaper, 0, 0, 0);

            /* Desenhamos os retângulos na tela */
            al_draw_bitmap(quadrado1, 0, 0, 0);
            al_draw_bitmap(quadrado2, 440, 0, 0);
            al_draw_bitmap(quadrado3, 0, 360, 0);
            al_draw_bitmap(quadrado4, 440, 360, 0);
            al_draw_bitmap(retornar, 1250, 600, 0);
            al_draw_bitmap(tocar, 1250, 200, 0);

            /* Fontes */
            al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA , 50, ALLEGRO_ALIGN_RIGHT, "QUAL ANIMAL EMITE");
            al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA , 100, ALLEGRO_ALIGN_RIGHT, "ESSE SOM? ");
            al_draw_text(fonte, al_map_rgb(255, 255, 255), 1300 , 600, ALLEGRO_ALIGN_CENTRE, "Menu");
            al_draw_text(fonte, al_map_rgb(255, 255, 255), 1300 , 200, ALLEGRO_ALIGN_CENTRE, "Tocar");

            /* Animais */
            al_draw_bitmap(elefante.imagem, 0, 0, 0);
            al_draw_bitmap(baleia.imagem, 450, 0, 0);
            al_draw_bitmap(cabra.imagem, 0, 390, 0);
            al_draw_bitmap(tigre.imagem, 450, 390, 0);

            al_flip_display();

            i++; // condicional para tocar musica

            if(i < 1){ // condicao pra tocar musica
                //al_play_sample(porco.som, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            }
        }
    }

    sair = 0;
    //  PARTE 2
    while(sair == 0){
        while(!al_is_event_queue_empty(fila_eventos)){
            quadrado1 = al_create_bitmap(420, 320);
            quadrado2 = al_create_bitmap(420, 320);
            quadrado3 = al_create_bitmap(420, 320);
            quadrado4 = al_create_bitmap(420, 320);
            retornar = al_create_bitmap(100, 100);
            tocar = al_create_bitmap(100, 100);
            //proximo = al_create_bitmap(100, 100);

            ALLEGRO_EVENT evento;
            ALLEGRO_TIMEOUT timeout;
            al_init_timeout(&timeout, 0.05);

            int tem_eventos = al_wait_for_event_until(fila_eventos, &evento, &timeout);

            /* Sair */

            if (tem_eventos && evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                exit(-1);
            }


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
                    al_stop_sample(&cavalo.id);
                    errou(janela, "cachorro");
                    erros++;
                    sair = 1;    
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
                    al_stop_sample(&cavalo.id);
                    acertou(janela, "cavalo");
                    acertos++;
                    sair = 1;
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
                    al_stop_sample(&cavalo.id);
                    errou(janela, "tatu");
                    erros++;
                    sair = 1;
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
                    al_stop_sample(&cavalo.id);
                    errou(janela, "touro");
                    erros++;
                    sair = 1;
                }
            }
            /* retornar */
            al_set_target_bitmap(retornar);
            if (evento.type == ALLEGRO_EVENT_MOUSE_AXES){
                /* Verificamos se ele está sobre a região do retângulo central */
                if (evento.mouse.x >=  1250 &&
                    evento.mouse.x <=  1350 &&
                    evento.mouse.y >=  600 &&
                    evento.mouse.y <= 700){
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
                    al_stop_sample(&cavalo.id);
                    return;
                }
            }
            /* tocar dnv */
            al_set_target_bitmap(tocar);
            if (evento.type == ALLEGRO_EVENT_MOUSE_AXES){
                /* Verificamos se ele está sobre a região do retângulo central */
                if (evento.mouse.x >=  1250 &&
                    evento.mouse.x <=  1350 &&
                    evento.mouse.y >=  200 &&
                    evento.mouse.y <= 300){
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
                    evento.mouse.y >= 200 &&
                    evento.mouse.y <= 300){
                    al_play_sample(cavalo.som, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, cavalo.id);
                }
            }

            

            /* Configura a janela */
            al_set_target_bitmap(al_get_backbuffer(janela));
            al_draw_bitmap(wallpaper, 0, 0, 0);

            /* Desenhamos os retângulos na tela */
            al_draw_bitmap(quadrado1, 0, 0, 0);
            al_draw_bitmap(quadrado2, 440, 0, 0);
            al_draw_bitmap(quadrado3, 0, 360, 0);
            al_draw_bitmap(quadrado4, 440, 360, 0);
            al_draw_bitmap(retornar, 1250, 600, 0);
            al_draw_bitmap(tocar, 1250, 200, 0);

            /* Fontes */
            al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA , 50, ALLEGRO_ALIGN_RIGHT, "QUAL ANIMAL EMITE");
            al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA , 100, ALLEGRO_ALIGN_RIGHT, "ESSE SOM? ");
            al_draw_text(fonte, al_map_rgb(255, 255, 255), 1300 , 600, ALLEGRO_ALIGN_CENTRE, "Menu");
            al_draw_text(fonte, al_map_rgb(255, 255, 255), 1300 , 200, ALLEGRO_ALIGN_CENTRE, "Tocar");

            /* Animais */
            al_draw_bitmap(cachorro.imagem, 0, 0, 0);  
            al_draw_bitmap(cavalo.imagem, 450, 0, 0);
            al_draw_bitmap(tatu.imagem, 0, 390, 0);
            al_draw_bitmap(touro.imagem, 450, 390, 0);
            al_flip_display();
            i++; // condicional para tocar musica

            if(i < 1){ // condicao pra tocar musica
                //al_play_sample(porco.som, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            }
        }
    }

    sair = 0;
    //  PARTE 3
    while(sair == 0){
        while(!al_is_event_queue_empty(fila_eventos)){
            quadrado1 = al_create_bitmap(420, 320);
            quadrado2 = al_create_bitmap(420, 320);
            quadrado3 = al_create_bitmap(420, 320);
            quadrado4 = al_create_bitmap(420, 320);
            retornar = al_create_bitmap(100, 100);
            tocar = al_create_bitmap(100, 100);
            //proximo = al_create_bitmap(100, 100);

            ALLEGRO_EVENT evento;
            ALLEGRO_TIMEOUT timeout;
            al_init_timeout(&timeout, 0.05);

            int tem_eventos = al_wait_for_event_until(fila_eventos, &evento, &timeout);

            /* Sair */

            if (tem_eventos && evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                exit(-1);
            }


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
                    al_stop_sample(&gato.id);
                    errou(janela, "zebra");  
                    erros++;
                    sair = 1;    
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
                    al_stop_sample(&gato.id);
                    acertou(janela, "gato");
                    acertos++;
                    sair = 1;
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
                    al_stop_sample(&gato.id);
                    errou(janela, "girafa");
                    erros++;
                    sair = 1;
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
                    al_stop_sample(&gato.id);
                    errou(janela, "leao");
                    erros++;
                    sair = 1;
                }
            }
            /* retornar */
            al_set_target_bitmap(retornar);
            if (evento.type == ALLEGRO_EVENT_MOUSE_AXES){
                /* Verificamos se ele está sobre a região do retângulo central */
                if (evento.mouse.x >=  1250 &&
                    evento.mouse.x <=  1350 &&
                    evento.mouse.y >=  600 &&
                    evento.mouse.y <= 700){
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
                    al_stop_sample(&gato.id);
                    return;
                }
            }
            /* tocar dnv */
            al_set_target_bitmap(tocar);
            if (evento.type == ALLEGRO_EVENT_MOUSE_AXES){
                /* Verificamos se ele está sobre a região do retângulo central */
                if (evento.mouse.x >=  1250 &&
                    evento.mouse.x <=  1350 &&
                    evento.mouse.y >=  200 &&
                    evento.mouse.y <= 300){
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
                    evento.mouse.y >= 200 &&
                    evento.mouse.y <= 300){
                    al_play_sample(gato.som, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, gato.id);
                }
            }

            

            /* Configura a janela */
            al_set_target_bitmap(al_get_backbuffer(janela));
            al_draw_bitmap(wallpaper, 0, 0, 0);

            /* Desenhamos os retângulos na tela */
            al_draw_bitmap(quadrado1, 0, 0, 0);
            al_draw_bitmap(quadrado2, 440, 0, 0);
            al_draw_bitmap(quadrado3, 0, 360, 0);
            al_draw_bitmap(quadrado4, 440, 360, 0);
            al_draw_bitmap(retornar, 1250, 600, 0);
            al_draw_bitmap(tocar, 1250, 200, 0);

            /* Fontes */
            al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA , 50, ALLEGRO_ALIGN_RIGHT, "QUAL ANIMAL EMITE");
            al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA , 100, ALLEGRO_ALIGN_RIGHT, "ESSE SOM ? ");
            al_draw_text(fonte, al_map_rgb(255, 255, 255), 1300 , 600, ALLEGRO_ALIGN_CENTRE, "Menu");
            al_draw_text(fonte, al_map_rgb(255, 255, 255), 1300 , 200, ALLEGRO_ALIGN_CENTRE, "Tocar");

            /* Animais */
            al_draw_bitmap(zebra.imagem, 0, 0, 0);
            al_draw_bitmap(gato.imagem, 450, 0, 0);
            al_draw_bitmap(girafa.imagem, 0, 390, 0);
            al_draw_bitmap(leao.imagem, 450, 390, 0);
            al_flip_display();
            i++; // condicional para tocar musica
            

            if(i < 1){ // condicao pra tocar musica
                //al_play_sample(porco.som, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            }
        }
    }

    sair = 0;
    //  PARTE 4
    while(sair == 0){
        while(!al_is_event_queue_empty(fila_eventos)){
            quadrado1 = al_create_bitmap(420, 320);
            quadrado2 = al_create_bitmap(420, 320);
            quadrado3 = al_create_bitmap(420, 320);
            quadrado4 = al_create_bitmap(420, 320);
            retornar = al_create_bitmap(100, 100);
            tocar = al_create_bitmap(100, 100);
            //proximo = al_create_bitmap(100, 100);

            ALLEGRO_EVENT evento;
            ALLEGRO_TIMEOUT timeout;
            al_init_timeout(&timeout, 0.05);

            int tem_eventos = al_wait_for_event_until(fila_eventos, &evento, &timeout);

            /* Sair */

            if (tem_eventos && evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                exit(-1);
            }


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
                    al_stop_sample(&macaco.id);
                    errou(janela, "pato");  
                    erros++;
                    sair = 1;    
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
                    al_stop_sample(&macaco.id);
                    errou(janela, "peixe");
                    erros++;
                    sair = 1;
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
                    al_stop_sample(&macaco.id);
                    acertou(janela, "macaco");
                    acertos++;
                    sair = 1;
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
                    al_stop_sample(&macaco.id);
                    errou(janela, "coruja");
                    erros++;
                    sair = 1;
                }
            }
            /* retornar */
            al_set_target_bitmap(retornar);
            if (evento.type == ALLEGRO_EVENT_MOUSE_AXES){
                /* Verificamos se ele está sobre a região do retângulo central */
                if (evento.mouse.x >=  1250 &&
                    evento.mouse.x <=  1350 &&
                    evento.mouse.y >=  600 &&
                    evento.mouse.y <= 700){
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
                    al_stop_sample(&macaco.id);
                    return;
                }
            }
            /* tocar dnv */
            al_set_target_bitmap(tocar);
            if (evento.type == ALLEGRO_EVENT_MOUSE_AXES){
                /* Verificamos se ele está sobre a região do retângulo central */
                if (evento.mouse.x >=  1250 &&
                    evento.mouse.x <=  1350 &&
                    evento.mouse.y >=  200 &&
                    evento.mouse.y <= 300){
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
                    evento.mouse.y >= 200 &&
                    evento.mouse.y <= 300){
                    al_play_sample(macaco.som, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, macaco.id);
                }
            }

            

            /* Configura a janela */
            al_set_target_bitmap(al_get_backbuffer(janela));
            al_draw_bitmap(wallpaper, 0, 0, 0);

            /* Desenhamos os retângulos na tela */
            al_draw_bitmap(quadrado1, 0, 0, 0);
            al_draw_bitmap(quadrado2, 440, 0, 0);
            al_draw_bitmap(quadrado3, 0, 360, 0);
            al_draw_bitmap(quadrado4, 440, 360, 0);
            al_draw_bitmap(retornar, 1250, 600, 0);
            al_draw_bitmap(tocar, 1250, 200, 0);

            /* Fontes */
            al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA , 50, ALLEGRO_ALIGN_RIGHT, "QUAL ANIMAL EMITE");
            al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA , 100, ALLEGRO_ALIGN_RIGHT, "ESSE SOM? ");
            al_draw_text(fonte, al_map_rgb(255, 255, 255), 1300 , 600, ALLEGRO_ALIGN_CENTRE, "Menu");
            al_draw_text(fonte, al_map_rgb(255, 255, 255), 1300 , 200, ALLEGRO_ALIGN_CENTRE, "Tocar");

            /* Animais */
            al_draw_bitmap(pato.imagem, 0, 0, 0);  
            al_draw_bitmap(peixe.imagem, 450, 0, 0);
            al_draw_bitmap(macaco.imagem, 0, 390, 0);
            al_draw_bitmap(coruja.imagem, 450, 390, 0);
        
            al_flip_display();
            i++; // condicional para tocar musica

            if(i < 1){ // condicao pra tocar musica
                //al_play_sample(porco.som, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            }
        }
    }

    sair = 0;
    //  PARTE 5
    while(sair == 0){
        while(!al_is_event_queue_empty(fila_eventos)){
            quadrado1 = al_create_bitmap(420, 320);
            quadrado2 = al_create_bitmap(420, 320);
            quadrado3 = al_create_bitmap(420, 320);
            quadrado4 = al_create_bitmap(420, 320);
            retornar = al_create_bitmap(100, 100);
            tocar = al_create_bitmap(100, 100);
            //proximo = al_create_bitmap(100, 100);

            ALLEGRO_EVENT evento;
            ALLEGRO_TIMEOUT timeout;
            al_init_timeout(&timeout, 0.05);

            int tem_eventos = al_wait_for_event_until(fila_eventos, &evento, &timeout);

            /* Sair */

            if (tem_eventos && evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                exit(-1);
            }


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
                    al_stop_sample(&pato.id);
                    errou(janela, "aguia"); 
                    erros++; 
                    sair = 1;    
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
                    al_stop_sample(&pato.id);
                    errou(janela, "caranguejo"); 
                    erros++;
                    sair = 1;
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
                    al_stop_sample(&pato.id);
                    errou(janela, "porco");
                    erros++;
                    sair = 1;
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
                    al_stop_sample(&pato.id);
                    acertou(janela, "pato");
                    acertos++;
                    sair = 1;
                }
            }
            /* retornar */
            al_set_target_bitmap(retornar);
            if (evento.type == ALLEGRO_EVENT_MOUSE_AXES){
                /* Verificamos se ele está sobre a região do retângulo central */
                if (evento.mouse.x >=  1250 &&
                    evento.mouse.x <=  1350 &&
                    evento.mouse.y >=  600 &&
                    evento.mouse.y <= 700){
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
                    al_stop_sample(&pato.id);
                    return;
                }
            }
            /* tocar dnv */
            al_set_target_bitmap(tocar);
            if (evento.type == ALLEGRO_EVENT_MOUSE_AXES){
                /* Verificamos se ele está sobre a região do retângulo central */
                if (evento.mouse.x >=  1250 &&
                    evento.mouse.x <=  1350 &&
                    evento.mouse.y >=  200 &&
                    evento.mouse.y <= 300){
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
                    evento.mouse.y >= 200 &&
                    evento.mouse.y <= 300){
                    al_play_sample(pato.som, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, pato.id);
                }
            }

            

            /* Configura a janela */
            al_set_target_bitmap(al_get_backbuffer(janela));
            al_draw_bitmap(wallpaper, 0, 0, 0);

            /* Desenhamos os retângulos na tela */
            al_draw_bitmap(quadrado1, 0, 0, 0);
            al_draw_bitmap(quadrado2, 440, 0, 0);
            al_draw_bitmap(quadrado3, 0, 360, 0);
            al_draw_bitmap(quadrado4, 440, 360, 0);
            al_draw_bitmap(retornar, 1250, 600, 0);
            al_draw_bitmap(tocar, 1250, 200, 0);

            /* Fontes */
            al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA , 50, ALLEGRO_ALIGN_RIGHT, "QUAL ANIMAL EMITE");
            al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA , 100, ALLEGRO_ALIGN_RIGHT, "ESSE SOM? ");
            al_draw_text(fonte, al_map_rgb(255, 255, 255), 1300 , 600, ALLEGRO_ALIGN_CENTRE, "Menu");
            al_draw_text(fonte, al_map_rgb(255, 255, 255), 1300 , 200, ALLEGRO_ALIGN_CENTRE, "Tocar");

            /* Animais */
            al_draw_bitmap(aguia.imagem, 0, 0, 0);  
            al_draw_bitmap(caranguejo.imagem, 450, 0, 0);
            al_draw_bitmap(porco.imagem, 0, 390, 0);
            al_draw_bitmap(pato.imagem, 450, 390, 0);
        
            al_flip_display();
            i++; // condicional para tocar musica

            if(i < 1){ // condicao pra tocar musica
                //al_play_sample(porco.som, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            }
        }
    }

    printf("acertos: %d, erros: %d\n", acertos, erros);
    
    jogador.acertos = acertos;
    jogador.erros = erros;
    strcpy(jogador.nome, nome);
    salvar(jogador);
    al_rest(3);
    al_destroy_font(fonte);
    exit(0);
}






void acertou(ALLEGRO_DISPLAY *janela, char string[]){
    int sair = 0;
    ALLEGRO_BITMAP *continuar = 0;
    Animal acertou;
    continuar = al_create_bitmap(200, 200);

    strcpy(acertou.nome, "acertou");
    acertou.imagem = al_load_bitmap("img/correto.png");
    acertou.som = al_load_sample("sound/acerto.wav");
    acertou.id = NULL;
    al_play_sample(acertou.som, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, acertou.id);

    while(sair == 0){
        ALLEGRO_EVENT evento;
        ALLEGRO_TIMEOUT timeout;
        al_init_timeout(&timeout, 0.05);

        int tem_eventos = al_wait_for_event_until(fila_eventos, &evento, &timeout);

        ALLEGRO_FONT *fonte;
        fonte = al_load_font("fontes/coolvetica.ttf", 40, 0);
        char mensagem [100] = "PARABENS VOCE ACERTOU, É UM ";
        strcat(mensagem, string);
        
        
        al_set_target_bitmap(continuar);
        if (evento.type == ALLEGRO_EVENT_MOUSE_AXES){
            /* Verificamos se ele está sobre a região do retângulo central */
            if (evento.mouse.x >=  1150 &&
                evento.mouse.x <=  1350 &&
                evento.mouse.y >= 500 &&
                evento.mouse.y <= 700 ){
                al_clear_to_color(al_map_rgb(145, 9, 9));
            }
            else{
                al_clear_to_color(al_map_rgb(255, 0, 0));
            }
        }
        /* Ou se o evento foi um clique do mouse */
        else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
            if (evento.mouse.x >= 1150 &&
                evento.mouse.x <= 1350 &&
                evento.mouse.y >= 500 &&
                evento.mouse.y <= 700){
                // INSTRUÇÃO DE JOGO
                sair = 1;
            }
        }
        
        al_set_target_bitmap(al_get_backbuffer(janela));
        al_clear_to_color(al_map_rgb(255, 255, 200));
        al_draw_text(fonte, al_map_rgb(0, 0, 0), 1000, 400, 1, mensagem);
        al_draw_bitmap(acertou.imagem, 0, 0, 0);  
        al_draw_bitmap(continuar, 1150, 500, 0);
        al_draw_text(fonte, al_map_rgb(0, 0, 0), 1150, 500, 0, "continuar");
        al_flip_display();
    }
}

void errou(ALLEGRO_DISPLAY *janela, char string[]){
    int sair = 0;
    ALLEGRO_BITMAP *continuar = 0;
    Animal acertou;
    continuar = al_create_bitmap(200, 200);

    strcpy(acertou.nome, "acertou");
    acertou.imagem = al_load_bitmap("img/erro.jpg");
    acertou.som = al_load_sample("sound/erro.wav");
    acertou.id = NULL;
    al_play_sample(acertou.som, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, acertou.id);

    while(sair == 0){
        ALLEGRO_EVENT evento;
        ALLEGRO_TIMEOUT timeout;
        al_init_timeout(&timeout, 0.05);

        int tem_eventos = al_wait_for_event_until(fila_eventos, &evento, &timeout);

        ALLEGRO_FONT *fonte;
        fonte = al_load_font("fontes/coolvetica.ttf", 40, 0);
        char mensagem [100] = "VOCÊ ERROU, NÃO É UM ";
        strcat(mensagem, string);
        
        
        al_set_target_bitmap(continuar);
        if (evento.type == ALLEGRO_EVENT_MOUSE_AXES){
            /* Verificamos se ele está sobre a região do retângulo central */
            if (evento.mouse.x >=  1150 &&
                evento.mouse.x <=  1350 &&
                evento.mouse.y >= 500 &&
                evento.mouse.y <= 700 ){
                al_clear_to_color(al_map_rgb(145, 9, 9));
            }
            else{
                al_clear_to_color(al_map_rgb(255, 0, 0));
            }
        }
        /* Ou se o evento foi um clique do mouse */
        else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
            if (evento.mouse.x >= 1150 &&
                evento.mouse.x <= 1350 &&
                evento.mouse.y >= 500 &&
                evento.mouse.y <= 700){
                // INSTRUÇÃO DE JOGO
                sair = 1;
            }
        }
        
        al_set_target_bitmap(al_get_backbuffer(janela));
        al_clear_to_color(al_map_rgb(255, 255, 200));
        al_draw_text(fonte, al_map_rgb(0, 0, 0), 1000, 400, 1, mensagem);
        al_draw_bitmap(acertou.imagem, 0, 0, 0);  
        al_draw_bitmap(continuar, 1150, 500, 0);
        al_draw_text(fonte, al_map_rgb(0, 0, 0), 1150, 500, 0, "continuar");
        al_flip_display();
    }
}




void salvar(Salvar jogador){
    FILE * f;
    f = fopen("jogadores.txt", "r+");
    if(f == NULL){
        f = fopen("jogadores.txt", "w");
    }

    fseek(f, 0, 2);
    fwrite(&jogador, sizeof(jogador), 1, f);
    fclose(f);
}

void ler(){
    FILE *f;
    Salvar jogador;
    int status;
    char linha[100];
    f = fopen("jogadores.txt", "r");
    if(f == NULL){
        printf("Nenhuma criança cadastrada\n");
    }else{
        fseek(f, 0, 0);
        while(1){
            status = fread(&jogador, sizeof(jogador), 1, f);
            if(status != 1){
                if(!feof(f)){
                    printf("Erro\n");
                    break;
                }else{
                    break;
                }
            }else{
                printf("Nome = %s, acertos = %d, erros = %d\n\n", jogador.nome, jogador.acertos, jogador.erros);
            }
        }
    }
    fclose(f);
}

void instrucoes(ALLEGRO_DISPLAY *janela){

}