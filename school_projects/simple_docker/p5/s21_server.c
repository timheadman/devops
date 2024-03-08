#include <fcgi_stdio.h>

int main(void) {
  while (FCGI_Accept() >= 0) {
    printf(
        "Content-type: text/html\r\n\r\n"
        "Hello World!");
  }

  return 0;
}

// #include <fcgiapp.h>
// #include <fcgios.h>
// #include <stdio.h>

// int main(void) {
//   FCGX_Init();
//   int socket = FCGX_OpenSocket("127.0.0.1:2023", 1024);
//   FCGX_Request request;
//   FCGX_InitRequest(&request, socket, 0);

//   while (FCGX_Accept_r(&request) >= 0) {
//     printf("Request Accepted\n");
//     FCGX_FPrintF(request.out,
//                  "Content-type: text/html\r\n\r\n"
//                  "<h1>Hello World!</h1>");
//     FCGX_Finish_r(&request);
//   }

//   FCGX_Free(&request, 0);
//   OS_LibShutdown();

//   return 0;
// }
