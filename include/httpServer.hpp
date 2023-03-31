#ifdef isESP8266
#include <esp8266WiFi.h>
#include <ESPAsyncTCP.h>
#else
#include <WiFi.h>
#include <AsyncTCP.h>
#endif
#include <LittleFS.h>
#include <ESPAsyncWebServer.h>
#include <Preferences.h>

AsyncWebServer server(80);

class NetworkPortal
{
protected:
public:
  static void setupApMode()
  {

    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(local_ip, gateway, subnet);
    WiFi.softAP(ssid, password);

    if (!LittleFS.begin())
    {
      Serial.println("An Error has occurred while mounting LittleFS");
      return;
    }

    // ESPAsyncWebServer Setup
    // Web Server Root URL
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(LittleFS, "/index.html", "text/html"); });

    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/style.css", "text/css");});
    
    /*
    server.on("/allvalues", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "application/json", processor()); });
              */
    server.on("/logo.png", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(LittleFS, "/logo.png", "image/png"); });

    server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request)
              {
            String inputMessage, inputParam;
            if (request->hasParam("protocolo"))
            {
            inputMessage = request->getParam("protocolo")->value();
            inputParam = "protocolo";
            config.protocol = inputMessage;
            }
            if (request->hasParam("baudrate"))
            {
            inputMessage = request->getParam("baudrate")->value();
            inputParam = "baudrate";
            config.baudrate = std::stoi(inputMessage.c_str());
            }
            if (request->hasParam("paridad"))
            {
            inputMessage = request->getParam("paridad")->value();
            inputParam = "paridad";
            config.parity = inputMessage;
            }
            if (request->hasParam("delay"))
            {
            inputMessage = request->getParam("delay")->value();
            inputParam = "delay";
            config.delay = std::stoi(inputMessage.c_str());
            }
            if (request->hasParam("trama"))
            {
            inputMessage = request->getParam("trama")->value();
            inputParam = "trama";
            config.trama = inputMessage;
            }
            if (request->hasParam("trama_custom"))
            {
            inputMessage = request->getParam("trama_custom")->value();
            inputParam = "trama_custom";
            config.trama_personalizada = inputMessage;
            }
            request->send(200, "text/html", "HTTP GET request sent to your ESP on input field (" 
                                            + inputParam + ") with value: " + inputMessage +
                                            "<br><a href=\"/\">Return to Home Page</a>"); 
            
            currentState = LOAD_NEW_PREFERENCES; });
    server.begin();
  }
};
