#define DEBUG

#define RE GPIO_NUM_4 // receiver enable
#define PIN_RED GPIO_NUM_12
#define PIN_GREEN GPIO_NUM_26
#define PIN_BLUE GPIO_NUM_25

int TXD_485 = GPIO_NUM_17;
int RXD_485 = GPIO_NUM_16;
int TXD_232 = GPIO_NUM_1; // PIN 35
int RXD_232 = GPIO_NUM_3; // PIN 34

const char *ssid = "Darkflow-Simulador-Balanzas";
const char *password = NULL;

int lastTimeCleanData_l4 = 0;
int lastTimeRead = 0;

int previousMillis = 0;
int previousTrama_1 = 0;
int previousTrama_2 = 0;
int previousTrama_3 = 0;
int previousTrama_4 = 0;
int ledState = LOW;

typedef enum
{ 
    NONE,
    SETUP_PREFERENCES,
    LOAD_NEW_PREFERENCES,
    SETUP_UART,
    START_UART
} States;

States currentState = SETUP_PREFERENCES;

IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

struct
{
    int baudrate = 115200;
    int delay = 0;
    String protocol = "rs232";
    String parity = "SERIAL_8N1";
    String trama = "trama_1";
    String trama_personalizada = "";
} config;
