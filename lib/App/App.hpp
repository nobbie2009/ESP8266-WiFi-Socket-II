#ifndef __APP_H__
#define __APP_H__

#include <Arduino.h>

#define LOG0( format ) Serial.printf( "(%ld) " format, millis())
#define LOG1( format, x) Serial.printf( "(%ld) " format, millis(), x )

#define APP_NAME "WiFi Socket II"
#define APP_VERSION "2.6.0"
#define APP_AUTHOR "Dr. Thorsten Ludewig <t.ludewig@gmail.com>"
#define APP_CONFIG_FILE "/config.bin"

#if OBI_VERSION == 2
  // Late 2018 Obi Wifi Socket
  #define WIFI_LED      12
  #define POWER_LED     13
  #define POWER_BUTTON  5
  #define RELAY_PIN     4
  #define WIFI_LED_ON   1
  #define WIFI_LED_OFF  0
#endif

#if OBI_VERSION == 1
  // First Obi Wifi Socket
  #define WIFI_LED          4
  #define POWER_BUTTON      14
  #define RELAY_TRIGGER_OFF 5
  #define RELAY_TRIGGER_ON  12
  #define WIFI_LED_ON       1
  #define WIFI_LED_OFF      0
#endif

#if DEVELOPMENT_VERSION == 1
  #define WIFI_LED      LED_BUILTIN // D4, GPIO2
  #define POWER_LED     D6          // GPIO12
  #define POWER_BUTTON  D7          // GPIO13
  #define RELAY_PIN     D5          // GPIO14
  #define WIFI_LED_ON   0
  #define WIFI_LED_OFF  1
#endif

#ifdef BW_SHP6
  #define WIFI_LED      2 
  #define POWER_LED     0
  #define POWER_BUTTON  13
  #define RELAY_PIN     15
  #define WIFI_LED_ON   0
  #define WIFI_LED_OFF  1

  #define HAVE_ENERGY_SENSOR
  #define HAVE_HLW8012
  #define SEL_PIN 12
  #define CF1_PIN 14
  #define CF_PIN 5
  #define UPDATE_TIME 2000
  #define CURRENT_MODE LOW
#endif

// Network mode
#define NET_MODE_STATIC 1
#define NET_MODE_DHCP 2

typedef struct appconfig
{
  char wifi_ssid[64];
  char wifi_password[64];
  int  wifi_mode;

  int net_mode;
  char net_host[64];
  char net_mask[64];
  char net_gateway[64];
  char net_dns[64];

  char ota_hostname[64];
  char ota_password[64];

  char admin_password[64];

  bool ohab_enabled;
  int  ohab_version;
  char ohab_host[64];
  int  ohab_port;
  bool ohab_useauth;
  char ohab_user[64];
  char ohab_password[64];
  char ohab_itemname[64];
#ifdef HAVE_ENERGY_SENSOR
  char ohab_item_voltage[64];
  char ohab_item_current[64];
  char ohab_item_power[64];
  time_t ohab_sending_interval;
#endif
  bool alexa_enabled;
  char alexa_devicename[64];

  bool mqtt_enabled;
  char mqtt_clientid[64];
  char mqtt_host[64];
  int  mqtt_port;
  bool mqtt_useauth;
  char mqtt_user[64];
  char mqtt_password[64];
  char mqtt_intopic[64];
  char mqtt_outtopic[64];
#ifdef HAVE_ENERGY_SENSOR
  char mqtt_topic_voltage[64];
  char mqtt_topic_current[64];
  char mqtt_topic_power[64];
  char mqtt_topic_json[64];
  time_t mqtt_sending_interval;
#endif

  bool syslog_enabled;
  char syslog_host[64];
  int syslog_port;
  char syslog_app_name[64];
} AppConfig;

class App
{
private:
  bool initialized = false;
  bool doSystemRestart;
  time_t systemRestartTimestamp;

  void loadConfig();
  void restartSystem();

public:
  size_t fsTotalBytes;
  size_t fsUsedBytes;

  App();

  void setup();
  void defaultConfig();
  void writeConfig();
  void printConfig();
  void delayedSystemRestart();
  void handle();
};

extern App app;
extern AppConfig appcfg;
extern AppConfig appcfgWR;

#endif
