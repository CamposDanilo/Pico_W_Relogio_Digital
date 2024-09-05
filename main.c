#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

int hora = 0;
int min = 0;
int seg = 0;
volatile bool flag;


bool per_timer_callback(struct repeating_timer *t) {
    // verifica se esta na virada do dia
    if ((hora == 23) && (min == 59) && (seg == 59)){
        hora =0;
        min = 0;
        seg = 0;
        printf ("Relogio: %d : %d : %d \n",hora,min,seg);
    }
    //verifica se esta na virada da hora
    else if ((min == 59) && (seg == 59)){
        min = 0;
        seg = 0;
        hora = hora +1;
        printf ("Relogio: %d : %d : %d \n",hora,min,seg);  
    }
    //verifica se esta na virada do minuto
    else if (seg == 59){
        seg = 0;
        min = min +1;
        printf ("Relogio: %d : %d : %d \n",hora,min,seg);
    }
    //senão, Incrementa o segundo 
    else{
    seg = seg +1;
    printf ("Relogio: %d : %d : %d \n",hora,min,seg);   
    }     
    return true;
}

 void digital_clock(){
    sleep_ms(1000);
    // Aguarda a inserção das horas, e depois com o IF verifica se o valor inserido esta correto
    while(flag == false){
        printf("Insira Hora:     (0 - 23)\n");
        scanf("%d",&hora);
        printf("%d\n",hora);
        if (hora >= 0 && hora < 24){break;}
    }
    sleep_ms(500);
    // Aguarda a inserção das minutos, e depois com o IF verifica se o valor inserido esta correto
    while(flag == false){
        printf("Insira Minutos:    (0 - 59)\n");
        scanf("%d",&min);
        printf("%d\n",min);
        if (min >= 0 && min < 60){break;}
    }   
    sleep_ms(500);
    // Aguarda a inserção das segundos, e depois com o IF verifica se o valor inserido esta correto
    while(flag == false){
        printf("Insira Segundos:    (0 - 59)\n");
        scanf("%d",&seg);
        printf("%d\n",seg);
        if (seg >= 0 && seg < 60){break;}
    }
    sleep_ms(500);
    printf ("Relogio: %d : %d : %d      ",hora,min,seg);
                
}



int main() {
    stdio_init_all();
    cyw43_arch_init();
    
    // struct timer para acionar o timer
    struct repeating_timer timer;
    
    sleep_ms(1500);
    printf("Inicio:\n\n");
    sleep_ms(3000);
    
    //booleana que irá aguardar a inserção das horas dentro da função digital clock
    flag = false;
    //booleana que irá acionar a função digital clock apenas uma vez
    bool aciona_relogio = false;
    
    while(true){
        printf("Relogio Digital \n\n");
        // variavel tempo defini o timer para cionar a cada 1 segundo
        int tempo = 1000;
        if (aciona_relogio == false){
            //interroga as horas
            digital_clock();
        }
        //não perguntará mais as horas
        aciona_relogio = true;
        
        //cada vez que o timer é acionado (a cada 1000 ms) incrementa 1segundo nas horas
        add_repeating_timer_ms(tempo, &per_timer_callback, NULL, &timer);

        
        //Para o programa aqui e fica aguardando a contagem das horas pelo timer
        int k = 0;
        while(true){
            printf("(200) Encerra o relogio\n");
            scanf("%d", &k);
            //se o valor for 200, cancela o timer
            
            if (k == 200){
                cancel_repeating_timer(&timer);
                printf("%d\n",k);
                aciona_relogio = false;
                break;
            }
        
        }

    }
   
    return 0;
}