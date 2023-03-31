#include <iostream>
#include <Arduino.h>
#include <global.hpp>
#include <httpServer.hpp>

Preferences myData;
uint32_t uart_config;

void blink(int timelapse = 1000);
void printParams();
void printTrama_1();
void printTrama_2();
void printTrama_3();
void printTrama_4();

void task1(void *parameters)
{
    for (;;)
    {
        switch (currentState)
        {
        case SETUP_PREFERENCES:
        {
            NetworkPortal::setupApMode();
            config.protocol = myData.getString("protocolo", "rs232");
            config.baudrate = myData.getInt("baudrate", 115200);
            config.parity = myData.getString("paridad", "SERIAL_8N1");
            config.delay = myData.getInt("delay", 1);
            config.trama = myData.getString("trama", "trama_1");
            config.trama_personalizada = myData.getString("trama_custom", "");
            currentState = SETUP_UART;
            break;
        }

        case LOAD_NEW_PREFERENCES:
        {
            myData.putString("protocolo", config.protocol);
            myData.putInt("baudrate", config.baudrate);
            myData.putString("paridad", config.parity);
            myData.putInt("delay", config.delay);
            myData.putString("trama", config.trama);    
            myData.putString("trama_custom", config.trama_personalizada);
            currentState = SETUP_PREFERENCES;
            break;
        }

        case SETUP_UART:
        {
            Serial.end();
            if (config.parity == "SERIAL_5N1")
            {
            }
            else if (config.parity == "SERIAL_6N1")
            {
                uart_config = SERIAL_6N1;
            }
            else if (config.parity == "SERIAL_7N1")
            {
                uart_config = SERIAL_7N1;
            }
            else if (config.parity == "SERIAL_8N1")
            {
                uart_config = SERIAL_8N1;
            }
            else if (config.parity == "SERIAL_5N2")
            {
                uart_config = SERIAL_5N2;
            }
            else if (config.parity == "SERIAL_6N2")
            {
                uart_config = SERIAL_6N2;
            }
            else if (config.parity == "SERIAL_7N2")
            {
                uart_config = SERIAL_7N2;
            }
            else if (config.parity == "SERIAL_8N2")
            {
                uart_config = SERIAL_8N2;
            }
            else if (config.parity == "SERIAL_5E1")
            {
                uart_config = SERIAL_5E1;
            }
            else if (config.parity == "SERIAL_6E1")
            {
                uart_config = SERIAL_6E1;
            }
            else if (config.parity == "SERIAL_7E1")
            {
                uart_config = SERIAL_7E1;
            }
            else if (config.parity == "SERIAL_8E1")
            {
                uart_config = SERIAL_8E1;
            }
            else if (config.parity == "SERIAL_5E2")
            {
                uart_config = SERIAL_5E2;
            }
            else if (config.parity == "SERIAL_6E2")
            {
                uart_config = SERIAL_6E2;
            }
            else if (config.parity == "SERIAL_7E2")
            {
                uart_config = SERIAL_7E2;
            }
            else if (config.parity == "SERIAL_8E2")
            {
                uart_config = SERIAL_8E2;
            }
            else if (config.parity == "SERIAL_5O1")
            {
                uart_config = SERIAL_5O1;
            }
            else if (config.parity == "SERIAL_6O1")
            {
                uart_config = SERIAL_6O1;
            }
            else if (config.parity == "SERIAL_7O1")
            {
                uart_config = SERIAL_7O1;
            }
            else if (config.parity == "SERIAL_8O1")
            {
                uart_config = SERIAL_8O1;
            }
            else if (config.parity == "SERIAL_5O2")
            {
                uart_config = SERIAL_5O2;
            }
            else if (config.parity == "SERIAL_6O2")
            {
                uart_config = SERIAL_6O2;
            }
            else if (config.parity == "SERIAL_7O2")
            {
                uart_config = SERIAL_7O2;
            }
            else if (config.parity == "SERIAL_8O2")
            {
                uart_config = SERIAL_8O2;
            }

            if (config.protocol == "rs232")
            {
                Serial.begin(config.baudrate,
                             uart_config,
                             RXD_232,
                             TXD_232);
            }
            else if (config.protocol == "rs485")
            {
                digitalWrite(RE, HIGH);
                Serial.begin(config.baudrate,
                             uart_config,
                             RXD_485,
                             TXD_485);
            }

            currentState = START_UART;
            break;
        }

        case START_UART:
        {
            if (config.trama_personalizada != "")
            {
                Serial.println(config.trama_personalizada);
            }
            else if (config.trama == "trama_1")
            {
                printTrama_1();
            }
            else if (config.trama == "trama_2")
            {
                printTrama_2();
            }
            else if (config.trama == "trama_3")
            {
                printTrama_3();
            }
            else if (config.trama == "trama_4")
            {
                printTrama_4();
            }
            else if (config.trama == "trama_5")
            {
                printParams();
            }
        }

            vTaskDelay(2);
        }
    }
}

void task2(void *parameters)
{
    for (;;)
    {
        switch (currentState)
        {
        case SETUP_PREFERENCES:
        {
            blink(50);
            break;
        }
        case LOAD_NEW_PREFERENCES:
        {
            blink(50);
            break;
        }
        case SETUP_UART:
        {
            blink(50);
            break;
        }
        }
        vTaskDelay(10);
    }
}

void setup()
{
    xTaskCreatePinnedToCore(
        task1,
        "Task 1...",
        12000,
        NULL,
        1,
        NULL,
        0);
    xTaskCreatePinnedToCore(
        task2,
        "Task 2...",
        5000,
        NULL,
        1,
        NULL,
        1);
    myData.begin("credentials", false);
    pinMode(PIN_RED, OUTPUT);
}

void loop()
{
}

void blink(int timelapse)
{
    if (millis() - previousMillis >= timelapse)
    {
        ledState = (ledState == LOW) ? HIGH : LOW;
        digitalWrite(PIN_RED, ledState);
        previousMillis = millis();
    }
}

void off()
{
    digitalWrite(PIN_RED, LOW);
    delay(20);
}

void on()
{
    digitalWrite(PIN_RED, HIGH);
}

void printParams()
{
    off();
    Serial.println("###############");
    Serial.println(String(config.baudrate));
    Serial.println(config.parity);
    Serial.println(config.trama);
    Serial.println(config.delay);
    Serial.println("");
    on();
}

void printTrama_1()
{
    if (millis() - previousTrama_1 >= config.delay)
    {
        off();
        Serial.print(
            String(random(1000, 9999)) +
            "KG\r\n");
        on();
        previousTrama_1 = millis();
    }
}

void printTrama_2()
{
    if (millis() - previousTrama_2 >= config.delay)
    {
        on();
        Serial.print(
            String(random(1000, 9999)) +
            "KG\t");
        off();
        previousTrama_2 = millis();
    }
}

void printTrama_3()
{
    if (millis() - previousTrama_3 >= config.delay)
    {
        on();
        Serial.print(
            String(random(1000, 9999)) +
            "KG\n");
        off();
        previousTrama_3 = millis();
    }
}

void printTrama_4()
{
    if (millis() - previousTrama_4 >= config.delay)
    {
        on();
        Serial.print(
            String(random(1000, 9999)) +
            "KG");
        off();
        previousTrama_4 = millis();
    }
}
