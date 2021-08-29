# TpF-PdM
Aplicación:

De acuerdo a los manuales de los fabricantes, se debe evitar que los grupos electrógenos operen con poca carga o en vacío, por ello se implementa un banco de carga resistiva de 3 pasos controlables. Éstos ingresarán de acuerdo a la demanda.

Se realizará una lectura de un canal de ADC que simule un valor de potencia registrado por un transductor y de acuerdo a rangos determinados encenderá de uno a tres LEDS. Se enviarán mensajes de estado a través de la UART en cada estado del sistema. 

Periféricos (1 ó 2): 
GPIO, UART, ADC

MODO INICIAL
En este estado se realiza la inicialización de la UART a 115200 baudios enviando un mensaje “System Ready to Work” y se habilita el canal 1 (CH1) del ADC. Se espera que el usuario presione la Tecla 1 (TEC1) para pasar al ESTADO NORMAL.
MODO NORMAL
En este estado se realiza la lectura del ADC para establecer cuántos pasos de carga se activarán. Si se registra muy poca carga, se encenderán los 3 bancos y si la carga es suficiente se pueden llegar a desactivar todos los bancos. Los rangos se especifican en el código.
MODO ALARMA
En estado se registra cuando el valor de lectura del ADC es muy alto, simulando una carga excesiva sobre el grupo electrógeno. Se envía un mensaje de “Alerta” a través de la UART. En caso el valor de lectura mejore, podrá pasar al MODO NORMAL, y si se presiona RESET pasará al MODO INICIAL.

Módulos de software:

fsmsys.c  y fsmsys.h para el manejo de los estados del sistema.
fsm_tecla.c  y fsm_tecla.h para el manejo de los estados del sistema antirrebote para una tecla.
led.c y led.h para el manejo de LEDs de la EDU-CIAA_NXP.
teclas.c y teclas.h para lectura de pulsadores de la EDU-CIAA_NXP.

Prototipos de funciones:

fsmsys.c
typedef enum{MODO_INICIAL,MODO_NORMAL, MODO_ALARMA} fsmEstado_t;
void fsmSysUpdate(void); // La función actualiza el estado de la máquina de estados finitos. No recibe ni devuelve ningún valor.
fsm_tecla.c
typedef enum{ESTADO_BUTTON_UP,ESTADO_BUTTON_DOWN, ESTADO_BUTTON_FALLING, ESTADO_BUTTON_RISING} fsmButtonState_t;
teclas.c
bool_t leerTecla(gpioMap tecla); // Verifica el estado de la tecla. Recibe como parámetro la TECLA y devuelve el estado de la tecla pulsada (verdadero) y liberada (falso).
led.c
void encenderLed(gpioMap_t led); // Enciende un el Led determinado. Recibe como argumento el Led que se desea encender.
 bool_t apagarLeds(); // Apaga todo los Leds de la placa. No recibe argumento.
