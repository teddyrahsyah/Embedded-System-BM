#include <WiFi.h>
#include <utlgbotlib.h>
#include "DHT.h"

#define DHTPIN 15
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float h, t;

#define DEBUG_LEVEL_UTLGBOT 0

// Initialize Wifi connection to the router
char ssid[] = "MELXXXX";     // your network SSID (name)
char password[] = "XXXX"; // your network key

// Initialize Telegram BOT
#define BOTtoken "1462918478:AAFK-aThVMIy1pkqvqNzZkLQMq6F_XXX"  // your Bot Token (Get from Botfather)
#define chatid "1160707XXX" // http://api.telegram.org/bot<token>/getUpdates

uTLGBot Bot(BOTtoken);

const char TEXT_START[] =
  "Hello, I'm a Bot that can help you to monitor The DHT11 Sensor.\n"
  "\n"
  "Type /help to see the available command.";

char buff[100];
boolean state_t, state_h;

const char TEXT_HELP[] =
  "Available Command:\n"
  "\n"
  "/tempstatus - Show actual Temperature status.\n"
  "/humstatus - Show actual Humidity status.\n";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  dht.begin();

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Bot.getMe();
}

void loop() {
// Check for Bot received messages
  while (Bot.getUpdates())
  {
    Serial.println("Received message:");
    Serial.println(Bot.received_msg.text);
    Serial.println(Bot.received_msg.chat.id);

    if (strncmp(Bot.received_msg.text, "/start", strlen("/start")) == 0)
    {
      Bot.sendMessage(Bot.received_msg.chat.id, TEXT_START);
    }

    else if (strncmp(Bot.received_msg.text, "/help", strlen("/help")) == 0)
    {
      Bot.sendMessage(Bot.received_msg.chat.id, TEXT_HELP);
    }
    else if (strncmp(Bot.received_msg.text, "/tempstatus", strlen("/tempstatus")) == 0)
    {
      t = dht.readTemperature();
      if (isnan(h) || isnan(t)) {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
      }
      String msg = "Temperature Status : ";
      msg += t;
      msg += " °C\n";

      msg.toCharArray(buff, 100);
      Bot.sendMessage(Bot.received_msg.chat.id, buff);
    }
    else if (strncmp(Bot.received_msg.text, "/humstatus", strlen("/humstatus")) == 0)
    {
      h = dht.readHumidity();
      if (isnan(h) || isnan(t)) {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
      }
      String msg = "Humidity Status : ";
      msg += h;
      msg += " %Rh\n";

      msg.toCharArray(buff, 100);
      Bot.sendMessage(Bot.received_msg.chat.id, buff);
   }
  }
}
