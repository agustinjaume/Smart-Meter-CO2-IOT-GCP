#include "config/config_wifi.h"
// Cloud iot details.
const char *project_id = "<name-project>";
const char *location = "europe-west1";
const char *registry_id = "<name-registry>";
const char *device_id = "<name-device>";
// Configuration for NTP
const char* ntp_primary = "pool.ntp.org";
const char* ntp_secondary = "time.nist.gov";

#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif

// To get the private key run (where private-key.pem is the ec private key
// used to create the certificate uploaded to google cloud iot):
// openssl ec -in <private-key.pem> -noout -text
// and copy priv: part.
// The key length should be exactly the same as the key length bellow (32 pairs
// of hex digits). If it's bigger and it starts with "00:" delete the "00:". If
// it's smaller add "00:" to the start. If it's too big or too small something
// is probably wrong with your key.
const char *private_key_str =
    "71:46:0f:f0:a3:ef:5d:05:5d:fa:ea:05:f8:09:8e:"
    "71:46:0f:f0:a3:ef:5d:05:5d:fa:ea:05:f8:09:8e:"
    "71:46:0f:f0:a3:ef:5d:05:5d:fa:ea:05:f8:09:8e:"
   "05:f5";
// Time (seconds) to expire token += 20 minutes for drift
const int jwt_exp_secs = 60*20; // Maximum 24H (3600*24)

// To get the certificate for your region run:
//   openssl s_client -showcerts -connect mqtt.googleapis.com:8883
// for standard mqtt or for LTS:
//   openssl s_client -showcerts -connect mqtt.2030.ltsapis.goog:8883
// Copy the certificate (all lines between and including ---BEGIN CERTIFICATE---
// and --END CERTIFICATE--) to root.cert and put here on the root_cert variable.

const char *root_cert =
    "-----BEGIN CERTIFICATE-----\n"
    "MIIDDDCCArKgAwIBAgIURjzskJE39lD3SX0IkTs5jt4noWYwCgYIKoZIzj0EAwIw\n"
    "RDELMAkGA1UEBhMCVVMxIjAgBgNVBAoTGUdvb2dsZSBUcnVzdCBTZXJ2aWNlcyBM\n"
    "VFNMVFNYMCEGA1UdIAQaMBgwDAYKKwYBBAHWeQIFAzAIBgZngQwBAgIwMAYDVR0f\n"
    "MIIDDDCCArKgAwIBAgIURjzskJE39lD3SX0IkTs5jt4noWYwCgYIKoZIzj0EAwIw\n"
    "RDELMAkGA1UEBhMCVVMxIjAgBgNVBAoTGUdvb2dsZSBUcnVzdCBTZXJ2aWNlcyBM\n"
    "VFNMVFNYMCEGA1UdIAQaMBgwDAYKKwYBBAHWeQIFAzAIBgZngQwBAgIwMAYDVR0f\n"
    "MIIDDDCCArKgAwIBAgIURjzskJE39lD3SX0IkTs5jt4noWYwCgYIKoZIzj0EAwIw\n"
    "RDELMAkGA1UEBhMCVVMxIjAgBgNVBAoTGUdvb2dsZSBUcnVzdCBTZXJ2aWNlcyBM\n"
    "VFNMVFNYMCEGA1UdIAQaMBgwDAYKKwYBBAHWeQIFAzAIBgZngQwBAgIwMAYDVR0f\n"
    "Xt+ea9ZwVMYLXWQnGvKQ+Q==\n"
    "-----END CERTIFICATE-----\n";
// In case we ever need extra topics
const int ex_num_topics = 0;
const char* ex_topics[ex_num_topics];
//const int ex_num_topics = 1;
//const char* ex_topics[ex_num_topics] = {
//  "/devices/my-device/tbd/#"
//};
