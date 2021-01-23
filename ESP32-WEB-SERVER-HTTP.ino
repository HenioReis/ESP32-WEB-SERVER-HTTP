/*
 * Autor: Henio Reis
 * Proj. Web server http com esp32
 * Ano:18/01/2021
 */
 
#include "esp_http_server.h"
#include <WiFi.h>

const char *ssid = "wifi";
const char *password = "senha";

httpd_handle_t server = NULL;    // manipulador http
httpd_req_t *req;                // struc para requisição

// function prototipo para as request
static esp_err_t index_handler(httpd_req_t *req){
    uint8_t payload[1024]= {0};

    int16_t size = snprintf( (char*)payload, 1024,
           "<html>"
           "<head></head>"
           "<body>"
           "<div style='color:blue; font-size:50px;'>Hello Mundo! meu primeiro web server</div>"
           "</body>"
           "</html>"
           );
    
    httpd_resp_set_type(req, "text/html");
    Serial.println("Request..ok");
    return httpd_resp_send(req, (const char *)payload, size);
}

// function web server
void startServer(){
    //struct de config do server
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    // struct de manipulador url
    httpd_uri_t index_uri = {
        .uri       = "/webserver",
        .method    = HTTP_GET,
        .handler   = index_handler,
        .user_ctx  = NULL
    };

    Serial.printf("Starting web server http port: '%d'\n", config.server_port);
    //function para start server
    if (httpd_start(&server, &config) == ESP_OK) {
        httpd_register_uri_handler(server, &index_uri); // registrado manipulador uri
    }

}

void setup()
{ 
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  startServer();   // start web server
  
  Serial.print("Use http://");
  Serial.print(WiFi.localIP());
  Serial.println("to connect");
}

void loop()
{
  
}
