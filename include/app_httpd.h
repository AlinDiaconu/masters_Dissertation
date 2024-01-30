#ifndef MASTERS_DISSERTATION_APP_HTTPD_H
#define MASTERS_DISSERTATION_APP_HTTPD_H

#include "esp_http_server.h"
#include "esp_timer.h"
#include "esp_camera.h"
#include "img_converters.h"
#include "camera_index.h"
#include "Arduino.h"

extern int gpLed;
extern String WiFiAddr;
byte txdata[3] = {0xA5, 0, 0x5A};
const int Forward       = 92;                               // Înainte
const int Backward      = 163;                              // Înapoi
const int Turn_Left     = 149;                              // Înclinare la stânga
const int Turn_Right    = 106;                              // Înclinare la dreapta
const int Top_Left      = 20;                               // Deplasare în sus la stânga
const int Bottom_Left   = 129;                              // Deplasare în jos la stânga
const int Top_Right     = 72;                               // Deplasare în sus la dreapta
const int Bottom_Right  = 34;                               // Deplasare în jos la dreapta
const int Stop          = 0;                                // Oprire
// const int Contrarotate  = 172;                              // Rotire în sens antiorar
const int Clockwise     = 83;                               // Rotire în sens orar
const int Moedl1        = 25;                               // Modul 1
const int Moedl2        = 26;                               // Modul 2
const int Moedl3        = 27;                               // Modul 3
const int Moedl4        = 28;                               // Modul 4
const int MotorLeft     = 230;                              // Încălcare la stânga a servo-motorului
const int MotorRight    = 231;                              // Încălcare la dreapta a servo-motorului

#define HTTPD_DEFAULT_CONFIG_demo() {                        \
        .task_priority      = tskIDLE_PRIORITY+5,       \
        .stack_size         = 8192,                     \
        .server_port        = 80,                       \
        .ctrl_port          = 32768,                    \
        .max_open_sockets   = 7,                        \
        .max_uri_handlers   = 19,                        \
        .max_resp_headers   = 19,                        \
        .backlog_conn       = 5,                        \
        .lru_purge_enable   = false,                    \
        .recv_wait_timeout  = 5,                        \
        .send_wait_timeout  = 5,                        \
        .global_user_ctx = NULL,                        \
        .global_user_ctx_free_fn = NULL,                \
        .global_transport_ctx = NULL,                   \
        .global_transport_ctx_free_fn = NULL,           \
        .open_fn = NULL,                                \
        .close_fn = NULL,                               \
        .uri_match_fn = NULL                            \
}

typedef struct
{
    size_t size;  // numărul de valori folosite pentru filtrare
    size_t index; // indexul valorii curente
    size_t count; // numărul total de valori
    int sum;
    int *values; // vector în care se vor stoca valorile
} ra_filter_t;

typedef struct
{
    httpd_req_t *req;
    size_t len;
} jpg_chunking_t;

#define PART_BOUNDARY "123456789000000000000987654321"
static const char *_STREAM_CONTENT_TYPE = "multipart/x-mixed-replace;boundary=" PART_BOUNDARY;
static const char *_STREAM_BOUNDARY = "\r\n--" PART_BOUNDARY "\r\n";
static const char *_STREAM_PART = "Content-Type: image/jpeg\r\nContent-Length: %u\r\n\r\n";

static ra_filter_t ra_filter;
httpd_handle_t stream_httpd = NULL;
httpd_handle_t camera_httpd = NULL;

#endif //MASTERS_DISSERTATION_APP_HTTPD_H
