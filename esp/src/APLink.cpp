#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "SPIFFS.h"
#include <Arduino_JSON.h>
#include <Preferences.h>

AsyncWebServer server(80); //  启动本地服务

const char *PARAM_INPUT_1 = "ssid";
const char *PARAM_INPUT_2 = "pass";

//  定义设置WIFI页面
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>

<head>
    <title>ESP Wi-Fi Manager</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="icon" href="data:,">
</head>

<body style="text-align: center; margin: 0;">
    <div style="background-color: #0A1128; color: #fff" class="topnav">
        <div style="font-size: 25px; font-weight: 600; padding: 20px;">ESP Wi-Fi Manager</div>
    </div>
    <div class="content" style="margin-top: 20px">
        <div class="card-grid">
            <div class="card">
                <form action="/" method="POST">
                    <table style="position: relative; left: 50%; width: 70%; padding: 20px; transform: translateX(-50%); background-color: white; box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5);">
                        <tr style="padding: 20px;">
                            <td style="padding: 10px;"><label for="ssid">SSID</label></td>
                            <td style="padding: 10px;"><input type="text" id="ssid" name="ssid"><br></td>
                        </tr>
                        <tr style="background-color: #f2f2f2; padding: 20px;">
                            <td style="padding: 10px;"><label for="pass">Password</label></td>
                            <td style="padding: 10px;"><input type="text" id="pass" name="pass"><br></td>
                        </tr>
                        <tr>
                            <td></td>
                            <td style="padding: 10px"><input type="submit" value="Submit" style="background-color: #0A1128; color: #fff; border: 0; border-radius: 10px; padding: 5px 30px"></td>
                        </tr>
                    </table>
                </form>
            </div>
        </div>
    </div>
</body>

</html>
    )rawliteral";

void APlink()
{
  Serial.println("Setting AP (Access Point)");
  WiFi.softAP("ESP-WIFI-MANAGER", NULL);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text/html", index_html); });

  // Get the parameters submited on the form
  server.on("/", HTTP_POST, [](AsyncWebServerRequest *request)
            {
                int params = request->params();
                for (int i = 0; i < params; i++)
                {
                  AsyncWebParameter *p = request->getParam(i);
                  if (p->isPost())
                  {
                    if (p->name() == PARAM_INPUT_1)
                    {
                      Preferences prefs;
                      prefs.begin("mynamespace");
                      Serial.println(prefs.freeEntries());
                      prefs.putString("ssid", p->value().c_str());
                      Serial.printf("ssid: %s\n\n", prefs.getString("ssid").c_str());
                    }
                    if (p->name() == PARAM_INPUT_2)
                    {
                       Preferences prefs;
                      prefs.begin("mynamespace");
                      Serial.println(prefs.freeEntries());
                      prefs.putString("password", p->value().c_str());
                      Serial.printf("password: %s\n\n", prefs.getString("password").c_str());
                    }
                  }
                }
                request->redirect("http://www.xuanxiaocheng.top:8000");
                ESP.restart(); });
  server.begin();
}