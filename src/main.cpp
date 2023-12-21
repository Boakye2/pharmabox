/**
 * e-mail : openprogramming23@gmail.com
 * gitHub : https://github.com/RS-malik-el
 * Donation : paypal.me/RachelSysteme
 *
 * @AUTEUR : Exaucé KIMBEMBE / @OpenProgramming
 * DATE    : 09/05/2023
 *
 * @Bibliothèques nécessaires pour réaliser ce projet:
 * *** https://github.com/me-no-dev/ESPAsyncWebServer
 * *** https://github.com/me-no-dev/AsyncTCP
 * 
 *@Plugin : extension a installer sur l'IDE arduino pour le transfert des fichiers dans la
 * mémoire flash.
 * *** https://github.com/me-no-dev/arduino-esp32fs-plugin/releases/  
 * 
 * @Board : ESP32
 * 
 * Ce code permet de contrôler une LED en utilisant une page web.
 * Si l'ESP32 est connecté à un réseau WiFi, la LED intégrée à l'ESP32 clignote régulièrement 
 * pour indiquer que la connexion est active. Si la connexion est perdue, l'ESP32 tente de se 
 * reconnecter automatiquement. 
 * 
 * Le code est composé de plusieurs fichiers, 
 * *** Un fichier HTML qui contient la page web, 
 * *** Un fichier CSS pour la mise en forme, 
 * *** Un fichier JavaScript pour la gestion des événements
 * *** Deux photos qui sont utilisées comme images de fond.
 * 
*/


// Interruption de la compilation si la carte ESP32 n'est pas sélectionné
#ifndef ESP32
  #error "Veillez selectionner une carte ESP32"
#endif

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h> // SPIFFS (SPI Flash File System)
#include <Stepper.h>

// Remplacez ici par votre SSID et votre mot de passe WiFi
const char* ssid = "Klay";
const char* password = "abcd1234567";

AsyncWebServer server(80);// Crée un objet de serveur web sur le port 80

// pin utilisé
#define BUZZER_PIN 15 // Pin GPIO à laquelle le buzzer est connecté
#define LEDR_PIN 2 // Pin GPIO à laquelle le buzzer est connecté
#define LEDV_PIN 4 // Pin GPIO à laquelle le buzzer est connecté
#define LEDB_PIN 22 // Pin GPIO à laquelle le buzzer est connecté

// Prototype
void blink(void); // Indique que l'esp32 est en mode AP_STA
void refusAcces(); // Indique que l'esp32 est en mode AP_STA
void autorisationAcces(); // Indique que l'esp32 est en mode AP_STA

double stepsPerRevolution = 2048;
int i=0;
int j=0;



Stepper myStepper1(stepsPerRevolution,  21, 19, 18, 5);   // Pin inversion to make the library work
Stepper myStepper2(stepsPerRevolution,  26, 27, 14, 12);  // Pin inversion to make the library work

  


void setup() {
  Serial.begin(115200);          // Initialisation de la communication série
  pinMode(LEDB_PIN, OUTPUT);      // Définit la broche LED comme une sortie
  pinMode(BUZZER_PIN, OUTPUT); // Définir la broche du buzzer comme sortie
  pinMode(LEDR_PIN, OUTPUT); // Définir la broche du buzzer comme sortie
  pinMode(LEDV_PIN, OUTPUT); // Définir la broche du buzzer comme sortie
  pinMode(LEDB_PIN, OUTPUT); // Définir la broche du buzzer comme sortie
  digitalWrite(LEDB_PIN, LOW);    // Éteint la LED au démarrage
  myStepper1.setSpeed(10);   
  myStepper2.setSpeed(10);   



  // Initialisation du SPIFFS
  if (!SPIFFS.begin(true)){
    Serial.println("Une erreur s'est produite lors du montage de SPIFFS.");
    return;
  }

  // Ouverture du répertoire racine de SPIFFS
  File root = SPIFFS.open("/");
  // Ouverture du premier fichier contenu dans le répertoire racine de SPIFFS
  File file = root.openNextFile();

  Serial.println("\n\n");
  // Affichage des titres des fichiers contenu dans le SPIFFS
  while (file){
    Serial.print("Fichier stocker: ");
    Serial.println(file.name());
    file.close();
    file = root.openNextFile();
  }

  Serial.println("\n\n");
  // Configuration du wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connexion en cours au WiFi...");
  }

  Serial.println("\nConnecté au WiFi avec succès !");
  Serial.print("Adresse IP : http://");
  Serial.println(WiFi.localIP());
 
  //------------ Initialisation du serveur
  server.begin();
  Serial.println("\nServeur web démarré !");
 
  //------------- Page d'acceuil (page Web)
  server.on("/", HTTP_GET,[](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/page_web.html", "text/html");// envoi du fichier html
  });
                      
  server.on("/doliprane.jpg", HTTP_GET,[](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/doliprane.jpg", "image/jpg");// envoi du fichier png
  });
                      
  server.on("/tramadol.jpg", HTTP_GET,[](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/tramadol.jpg", "image/jpg");// envoi du fichier png
  });


  //----------- BNZRAI
 
 server.on("/1d", HTTP_GET, [](AsyncWebServerRequest *request){
  
    myStepper1.step(stepsPerRevolution/3);   
    autorisationAcces(); 
    request->send(200);
});

 server.on("/1t", HTTP_GET, [](AsyncWebServerRequest *request){
    myStepper2.step(stepsPerRevolution/3);  
    autorisationAcces(); 
 
    request->send(200);
});

/**server.on("/2d", HTTP_GET, [](AsyncWebServerRequest *request){
    
    
    myStepper1.step(stepsPerRevolution/3);   
    delay(2000); 
    autorisationAcces();
    request->send(200);
});
server.on("/2t", HTTP_GET, [](AsyncWebServerRequest *request){
    
    myStepper1.step(stepsPerRevolution/3);   
    delay(2000); 
    autorisationAcces();
    request->send(200);

});

server.on("/3d", HTTP_GET, [](AsyncWebServerRequest *request){
    
    
    myStepper1.step(stepsPerRevolution/3);   
    delay(2000); 
    autorisationAcces();
    request->send(200);
});
server.on("/3t", HTTP_GET, [](AsyncWebServerRequest *request){
    
    myStepper1.step(stepsPerRevolution/3);   
    delay(2000); 
    autorisationAcces();
    request->send(200);
});**/

  

  //----------- banzrai
  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
    
      refusAcces();
      request->send(200);
  });  

   server.on("/p", HTTP_GET, [](AsyncWebServerRequest *request){
      digitalWrite(LEDB_PIN, HIGH);
      request->send(200);
  });  
}//fin setup()


void loop(){
  // Clignotement du voyant si WIFI actif
  if(WiFi.isConnected()==true)
    blink();
  // Reconnexion automatique en cas de perte de connexion WIFI
  else{
    WiFi.reconnect(); 
  }  


  



  

}

// Clignotement du voyant
void blink(void){
  static unsigned long int init_t = millis();
  static bool etat = false;

  if ((millis()-init_t) >= 250){
    etat = not etat;
    init_t = millis();
  }
}

void refusAcces() {
  // Émettre trois bips pour signifier le refus
  digitalWrite(LEDB_PIN, 0); // Fréquence du son pour l'autorisation
  digitalWrite(LEDR_PIN, 1); // Fréquence du son pour l'autorisation

  for (int i = 0; i < 3; i++) {
    digitalWrite(BUZZER_PIN, 1); // Fréquence du son pour le refus
    delay(200); // Durée d'un bip
   digitalWrite(BUZZER_PIN, 0); // Arrêter le son pendant un court instant
    delay(100); // Attendre avant le prochain bip
  }

    digitalWrite(LEDR_PIN, 0); // Fréquence du son pour l'autorisation

}

void autorisationAcces() {
  // Émettre un son pour signifier l'autorisation
  digitalWrite(LEDB_PIN, 0); // Fréquence du son pour l'autorisation
  digitalWrite(LEDV_PIN, 1); // Fréquence du son pour l'autorisation
  digitalWrite(BUZZER_PIN, 1); // Fréquence du son pour l'autorisation
  delay(2000); // Émettre le son pendant 1 seconde
  digitalWrite(BUZZER_PIN, 0) ;// Arrêter le son
  digitalWrite(LEDV_PIN, 0); // Fréquence du son pour l'autorisation

}