#include "main.hpp"
int mybynery[8] = {0, 1, 0, 1, 0, 1, 0, 1};
const char* ssid = "iPhone van Dorus";
const char* password = "were is bob?";

String json_array;
int pins[8] = {2, 4, 5, 18, 19, 21, 22, 23};


//std::map<uint8_t, uint8_t> bynery{{1, 2}, {2,4}, {3, 5}, {4, 18}, {5,19}, {6,21}, {7,22}, {8,23}};
void setClock() {
  configTime(0, 0, "pool.ntp.org");

  Serial.print(F("Waiting for NTP time sync: "));
  time_t nowSecs = time(nullptr);
  while (nowSecs < 8 * 3600 * 2) {
    delay(500);
    Serial.print(F("."));
    yield();
    nowSecs = time(nullptr);
  }

  Serial.println();
  struct tm timeinfo;
  gmtime_r(&nowSecs, &timeinfo);
  Serial.print(F("Current time: "));
  Serial.print(asctime(&timeinfo));
}

void setup() {
  Serial.begin(115200);
  for (int i : pins) {
    pinMode(i, OUTPUT);
    
  }
  
  
    
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("\nConnecting");

    while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(200);
    }
     Serial.println("\nConnected to the WiFi network");
   Serial.print("Local ESP32 IP: ");
   Serial.println(WiFi.localIP());
   Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("First set of readings will appear after 10 seconds");
  setClock();
}

void loop() {
  
  delay(10000);
    if(WiFi.status()== WL_CONNECTED){
       WiFiClientSecure *client = new WiFiClientSecure;
  if(client) {
    client -> setCACert(rootCACertificate);

    {
      // Add a scoping block for HTTPClient https to make sure it is destroyed before WiFiClientSecure *client is 
      HTTPClient https;
  
      Serial.print("[HTTPS] begin...\n");
      if (https.begin(*client, "https://api.technoviumunlimited.nl/v1/score/fY0cJVemqT0UKI43rMNu/users/level_data")) {  // HTTPS 
      //
        Serial.print("[HTTPS] GET...\n");
        // start connection and send HTTP header
        int httpCode = https.GET();
  
        // httpCode will be negative on error
        if (httpCode > 0) {
          // HTTP header has been send and Server response header has been handled
          Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
  
          // file found at server
          if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
            String payload = https.getString();
            Serial.println(payload);
            StaticJsonDocument<200> doc;
            DeserializationError error = deserializeJson(doc, payload);
            if (error) {
              Serial.print(F("deserializeJson() failed: "));
              Serial.println(error.f_str());
              return;
            }
            json_array = doc["binary"].as<String>();           
            Serial.println(json_array);

          
            int count = 1;
            for (int pin : pins) {
              const String jj = std::to_string(count).c_str();
              Serial.println(jj);
              const String  hhhh = doc["binary"][std::to_string(count).c_str()];
              Serial.println(hhhh);
              Serial.println("i is:");
              if(doc["binary"][std::to_string(count).c_str()] == "0"){

                digitalWrite(pin, LOW);

              } else if(doc["binary"][std::to_string(count).c_str()] == "1"){
                //Serial.print(pins[i] + "pin is high");
                digitalWrite(pin, HIGH);
                Serial.println(" pin is high");
              } else {
                Serial.println("error boob");
              }
              count++;
            }
          }
        } else {
          Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
        }
  
        https.end();
      } else {
        Serial.printf("[HTTPS] Unable to connect\n");
      }

      // End extra scoping block
    }
  
    delete client;
  } else {
    Serial.println("Unable to create client");
  }

  Serial.println();
  Serial.println("Waiting 5s before the next round...");
  delay(5000);
     
     

    }
    else {
      Serial.println("WiFi Disconnected");
    }
   
  }
  
  
  /*for (int pin : pins) {
    if(bynery[pin] == 0){
      digitalWrite(pin, LOW);
      Serial.println("pin is low");
    } else if(bynery[pin] == 1){
      Serial.print("pin is high");
      digitalWrite(pin, HIGH);
      Serial.println(" pin is high");
    } else {
      Serial.println("error boob");
    }
  }*/










 
