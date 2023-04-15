#define _CRT_SECURE_NO_WARNINGS– отключение warning на Visual Studio
#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "Ws2_32.lib")

int main()
{
// подключаем WinSock библиотеки
WSADATA wsaDATA;
WORD word;
word = MAKEWORD(2, 2);
int start = WSAStartup(word, &wsaDATA);

// Создаем сокет
SOCKET sock;
sock = socket(AF_INET, SOCK_STREAM, 0); // SOCK_STREAM ( TCP )
if (sock != INVALID_SOCKET) // Проверка сокета
printf("Wait connection\n");
else
{
printf("ERROR");
closesocket(sock);
return -1;
}

// Привязывание сокета к порту
SOCKADDR_IN server; // Структура, хранящая всю информацию о сервере
server.sin_family = AF_INET;
server.sin_port = htons(2024); // Наш порт 2024
server.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

// Привязываемся к порту
int bind_sock = bind(sock, (SOCKADDR*)&server, sizeof(server));
if (bind_sock == SOCKET_ERROR) // Проверка связи с портом
{
printf("ERROR");
closesocket(sock);
return -1;
}

// Прослушивание
int listen_sock = listen(sock, 1);// 1- макс. число ожидающих
if (listen_sock == SOCKET_ERROR) // Проверка прослушивания
{
printf("ERROR");
closesocket(sock);
return -1;
}

// Принимаем подключение
int connect_sock = accept(sock, NULL, NULL);
if (connect_sock == INVALID_SOCKET) // Проверка соединения
{
printf("ERROR");
closesocket(sock);
return -1;
}

// Отправка сообщений клиенту

char *message = "HTTP/1.1 200 OK\r\n";
FILE *file;
char answer[128];
char buffer[1024];

send(connect_sock, message, strlen(message), 0);
file = fopen("D:\\test.txt", "r");
if (file)
{
while (!feof(file))
{
fgets(answer, 128, file);
send(connect_sock, answer, strlen(answer), 0);
}
}
else
printf("ERROR");
fclose(file);

int recieve = recv(connect_sock, buffer, 1024, 0);

buffer[1023] = '\0';
printf("%s", buffer);

// Закрываем сокет
closesocket(sock);

return 0;
}
