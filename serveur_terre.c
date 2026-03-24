 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080 // On choisit un port arbitraire pour notre serveur Terre

int main() {
    int server_socket;
    struct sockaddr_in server_addr;

    // 1. Création du socket (le point d'accès du serveur)
    // AF_INET = on utilise des adresses IPv4
    // SOCK_STREAM = on utilise le protocole TCP (fiable, pas de perte de données)
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Erreur : impossible de créer le socket");
        exit(EXIT_FAILURE);
    }
    printf("1. Socket de la Terre créé avec succès.\n");

    // 2. Configuration de l'adresse du serveur
    server_addr.sin_family = AF_INET;         // Type d'adresse (IPv4)
    server_addr.sin_addr.s_addr = INADDR_ANY; // On écoute sur toutes les adresses locales
    server_addr.sin_port = htons(PORT);       // On convertit le port dans le format réseau

    // 3. Attachement (bind) du socket à notre port 8080
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Erreur : échec du bind (le port est peut-être déjà utilisé)");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    printf("2. Serveur attaché au port %d.\n", PORT);

    // 4. Mise en écoute (listen)
    // Le '5' correspond au nombre maximum de rovers qui peuvent patienter dans la file d'attente
    if (listen(server_socket, 5) < 0) {
        perror("Erreur : impossible de mettre le serveur en écoute");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    printf("3. Le centre de contrôle Terre est en écoute...\n");

    // Pour l'instant, le programme s'arrête ici. 
    // Plus tard, on ajoutera une boucle infinie pour accepter les rovers.

    // On ferme proprement le socket à la fin
    close(server_socket);
    return 0;
}
