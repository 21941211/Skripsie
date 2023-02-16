#include <pgmspace.h>
 
#define SECRET
#define THINGNAME "ESP32"                         //change this
 
const char WIFI_SSID[] = "Bowman";               //change this
const char WIFI_PASSWORD[] = "Michael1";           //change this
const char AWS_IOT_ENDPOINT[] = "acqvfq2ae88i6-ats.iot.us-east-1.amazonaws.com";  //change this
 
// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";
 
// Device Certificate                                               //change this
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUL1sT3H4FmKvuFQSJJzAtxRqZT2YwDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTIzMDEyNjE2MDc1
MVoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAMLXgREEyCAzIvy8IZa2
LE1EpT9jCupaKMQWOc8P6jx+baWz4oyb8Xxa5mB9iGK2taxiiCzvr8wQjTgmF+Ht
9GxbPOTVov/UjFzZ8XeSHm9sCV+lg+I+1I5zR5Z8Mkpc3fEFE+Jcv091dL4AMNFv
AMuVWnxLEAWixVNSQF6Gq+i5iQ4jS1XIy1Ve0tGmdz9/sxmNl4y4dlvAZyOeo+4r
oDvKVh8/uwjPr/pwCgFxtqF4YQ/OfzSwipskANtJ9updUiQlYXPRG1JZFPRgTnsg
eML5cB3XQ1vGQX3NCx4izj99gfsOv1kSX+q6KTiPd1RLkLrhv6OoTHZ6/sPwontF
ZO0CAwEAAaNgMF4wHwYDVR0jBBgwFoAUf3IljIO9yVIQ6ZNHfo8AYsIWECUwHQYD
VR0OBBYEFE1JUU9UA6fShE5KT4s0JSnDbRrFMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQBVOIWstz0hw8dbg9TJ12N7d14n
sWVNNFX5+XsVRi9DdlYFOKlkZ5dldLOww0Z+XV5rVT+LtYAInVHqG+0BNaGVuZ+l
nu1Vw89/8N2ALi3ZPr5psU5+nl0+WXNA4fyY0RYgtLAToDPrwkemIjnkxM/H7axb
WAN3TWN4p9B4B1xJ/gljSbnkiXSYzbuT2v4snF5lrbP99Ep2RdaouVTaE/IbpTQO
PE81N+zRZO1F4Kt1obf5yheHA8pVPjaaJsxIp5M3lTp6QPtvoZvlSstRPZmNp+SY
+oz8C86vdZFtn0vOePNEYgwDNLMPLeP0jWYDo/2JlwffS5iwTgI++3aqi1Jx
-----END CERTIFICATE-----
 
 
)KEY";
 
// Device Private Key                                               //change this
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEowIBAAKCAQEAwteBEQTIIDMi/LwhlrYsTUSlP2MK6looxBY5zw/qPH5tpbPi
jJvxfFrmYH2IYra1rGKILO+vzBCNOCYX4e30bFs85NWi/9SMXNnxd5Ieb2wJX6WD
4j7UjnNHlnwySlzd8QUT4ly/T3V0vgAw0W8Ay5VafEsQBaLFU1JAXoar6LmJDiNL
VcjLVV7S0aZ3P3+zGY2XjLh2W8BnI56j7iugO8pWHz+7CM+v+nAKAXG2oXhhD85/
NLCKmyQA20n26l1SJCVhc9EbUlkU9GBOeyB4wvlwHddDW8ZBfc0LHiLOP32B+w6/
WRJf6ropOI93VEuQuuG/o6hMdnr+w/Cie0Vk7QIDAQABAoIBAA1xpTwxYkWmgaGC
saaeh0wFkolfIh+tfOaayf5ZkMX/yz0FvnoJQI5eD0tVHhYBmWN9oPvIxg6Ejdnz
9u3l51maqgb4HrkcR1sYxqqDcIoroDHzT7hKsYvqtGPTyfyLj9zTht21nJW0+wsp
JDUvPZTOh2HQJBjfdFIdeMeM70utcrJgcQ6ENSDqB+6oFPEm/+haiMYgdAjiUiP2
J1+oxCQ7SnXgLVjCeKIn39Obun+6cSDoMBoc4N2M3nBsOFKDdjXG9cTsjioPeJMc
ngQFqpibdLsTn4t6k75Lb3ggAvcJd+OkKgjsV7uKxbV0C8P7VQMOhfgQJ/xjbrd3
3dwYQ4ECgYEA81brvVksFcnOGLaDOMQoUA4lBv1B9BOiW/Yzticd84vBADAZLQp7
/s5VM2HHLMCREwHmX93B8bUKtLmRhzD5Cy2LSP2bGh/f2ykzQqpSVWaCVoyWlrbP
HjdMGfi43+gr5ld+VMRC1IUqBXaV6BhjhvN3vzkUtHi4sR21kbZsoV0CgYEAzPqi
W288mhTXN77468IcHFDnMuLz88UYxwAcgIbY7GBb1kOxaV528G3b//rWPLC631ue
BEMP8Wp5Fe/6Sm6QDdQAltOaQn4gwv0KVfD6mao/UVtWfdIFj7HjAe2fppxcbNCC
2QbOYAnSpQwJkX82ckNOxQ25v1zJfLMa8qdJyNECgYEA6dHCsW3G46THCY4OZvRt
fAcrYxzlS9+16cGYDNZnfEb0i/arqlDhtoSS781rckAS5n2z3LgcDOIWSHPrN0lC
dJAtv1QYvjCUjGV5YPyCIpdedEWgyW8dc35U/Lu3AUd5L1sxA8iWItlV+GvrPVp6
AAlgLfluQL+jUGUou7vbg+0CgYAis5++6QMSdsrEtkD/8Lm/lXa+p6tzLn/2WK96
ltmskteZW5ZyZzqtk3u2R2nzllvcqm8C+7N8RHFBZII0Dam3nZeH8UThUucK+7m/
OO/ECg10IYlv/ZlRbWUoE2l+1GPVTCuKwFs56Q/PP01zY1z9VSXFuIAkxHmb8dpz
EB0usQKBgDKrd/n4Tubtk+h1TUnHHKYtlaFpQ3dStrq9RXu2/Xqrv/iubYSjphx7
Ujl7SuIxn3UZPiCheXWO7yHwk/v1U4vpBWE5/T7SpwtIxnyhkn4+P1mvbZwnJhTf
RxGiEAjDcU8K9diKv7yw426PSc/bZx8AN4lI/zGe0KOggEvZo1GK
-----END RSA PRIVATE KEY-----
 
 
)KEY";