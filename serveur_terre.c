#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080 // On choisit un port arbitraire pour notre serveur Terre

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    // 1. Création du socket (le point d'accès du serveur)
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Erreur : impossible de créer le socket");
        exit(EXIT_FAILURE);
    }
    printf("1. Socket de la Terre créé avec succès.\n");

    // 2. Configuration de l'adresse du serveur
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // 3. Attachement (bind) du socket à notre port 8080
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Erreur : échec du bind (le port est peut-être déjà utilisé)");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    printf("2. Serveur attaché au port %d.\n", PORT);

    // 4. Mise en écoute (listen)
    if (listen(server_socket, 5) < 0) {
        perror("Erreur : impossible de mettre le serveur en écoute");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    printf("3. Le centre de contrôle Terre est en écoute...\n");

    // 5. Accepter une connexion entrante
    printf("En attente de la connexion d'un rover...\n");
    
    // Le code va se bloquer ici et attendre qu'un client se connecte
    client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
    if (client_socket < 0) {
        perror("Erreur : impossible d'accepter la connexion du rover");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    
    printf("4. Connexion établie ! Un rover est sur le réseau.\n");

    // On ferme proprement la connexion avec ce rover spécifique
    close(client_socket);

    // On ferme proprement le socket du serveur à la fin
    close(server_socket);
    return 0;
}