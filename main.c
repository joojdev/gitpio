#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define NAME_SIZE 51
#define DOCUMENT_SIZE 12
#define DESCRIPTION_SIZE 81
#define EMAIL_SIZE 71
#define PHONE_SIZE 21
#define ROLE_SIZE 31

typedef struct {
  int day;
  int month;
  int year;
  long int timestamp;
} Date;

typedef struct {
  char document_number[DOCUMENT_SIZE];
  char name[NAME_SIZE];
  Date admission_date;
  char role[ROLE_SIZE];
  char email[EMAIL_SIZE];
  char phone[PHONE_SIZE];
} Collaborator;

typedef struct {
  int code;
  char title[NAME_SIZE];
  char description[DESCRIPTION_SIZE];
  Date start_date;
  Date predicted_finish_date;
} Project;

typedef struct {
  char document_number[DOCUMENT_SIZE];
  int code;
  char function[ROLE_SIZE];
  int weekly_hours;
} Participation;

void getCharInput(char *output) {
  scanf("%c", output);
  getchar();
}

void printCollaboratorSubmenu() {
  printf("\n -=+ Submenu de Colaborador +=-\n\n");
  printf("   a) Registrar colaborador\n");
  printf("   b) Listar colaboradores\n");
  printf("   c) Procurar colaborador\n");
  printf("   d) Alterar dados de um colaborador\n");
  printf("   e) Remover um colaborador\n");
  printf("   f) Voltar\n\n");
}

void collaboratorSubmenu() {
  bool running = true;
  char option;

  while (running) {
    printCollaboratorSubmenu();

    getCharInput(&option);
    printf("\n");

    switch(option) {
      case 'a':
        break;
      case 'b':
        break;
      case 'c':
        break;
      case 'd':
        break;
      case 'e':
        break;
      case 'f':
        running = false;
        break;
      default:
        printf("   Opção inválida!");
        break;
    }

    if (option != 'f') {
      printf("\n\n");
    }
  }
}

void printProjectSubmenu() {
  printf("\n -=+ Submenu de Projeto +=-\n\n");
  printf("   a) Registrar projeto\n");
  printf("   b) Listar projetos\n");
  printf("   c) Procurar projeto\n");
  printf("   d) Alterar dados de um projeto\n");
  printf("   e) Remover um projeto\n");
  printf("   f) Voltar\n\n");
}

void projectSubmenu() {
  bool running = true;
  char option;

  while (running) {
    printProjectSubmenu();

    getCharInput(&option);
    printf("\n");

    switch(option) {
      case 'a':
        break;
      case 'b':
        break;
      case 'c':
        break;
      case 'd':
        break;
      case 'e':
        break;
      case 'f':
        running = false;
        break;
      default:
        printf("   Opção inválida!");
        break;
    }

    if (option != 'f') {
      printf("\n\n");
    }
  }
}

void printParticipationSubmenu() {
  printf("\n -=+ Submenu de Participação +=-\n\n");
  printf("   a) Registrar participação\n");
  printf("   b) Listar participações\n");
  printf("   c) Procurar participação\n");
  printf("   d) Alterar dados de uma participação\n");
  printf("   e) Remover uma participação\n");
  printf("   f) Voltar\n\n");
}

void participationSubmenu() {
  bool running = true;
  char option;

  while (running) {
    printParticipationSubmenu();

    getCharInput(&option);
    printf("\n");

    switch(option) {
      case 'a':
        break;
      case 'b':
        break;
      case 'c':
        break;
      case 'd':
        break;
      case 'e':
        break;
      case 'f':
        running = false;
        break;
      default:
        printf("   Opção inválida!");
        break;
    }

    if (option != 'f') {
      printf("\n\n");
    }
  }
}

void printReportSubmenu() {
  printf("\n -=+ Submenu de Relatório +=-\n\n");
  printf("   a) Listar colaboradores de um projeto\n");
  printf("   b) Listar projetos de um colaborador\n");
  printf("   c) Listar projetos e colaboradores em andamento entre duas datas\n");
  printf("   d) Voltar\n\n");
}

void reportSubmenu() {
  bool running = true;
  char option;

  while (running) {
    printReportSubmenu();

    getCharInput(&option);
    printf("\n");

    switch(option) {
      case 'a':
        break;
      case 'b':
        break;
      case 'c':
        break;
      case 'd':
        running = false;
        break;
      default:
        printf("   Opção inválida!");
        break;
    }

    if (option != 'd') {
      printf("\n\n");
    }
  }
}

void printMenu() {
  printf("\n -=+ Sistema de Gerenciamento de Projetos +=-\n\n");
  printf("   a) Submenu de Colaborador\n");
  printf("   b) Submenu de Projeto\n");
  printf("   c) Submenu de Participação\n");
  printf("   d) Submenu de Relatórios\n");
  printf("   e) Sair\n\n");
}

int main() {
  bool running = true;
  char option;

  while (running) {
    printMenu();

    getCharInput(&option);
    printf("\n");

    switch(option) {
      case 'a':
        collaboratorSubmenu();
        break;
      case 'b':
        projectSubmenu();
        break;
      case 'c':
        participationSubmenu();
        break;
      case 'd':
        reportSubmenu();
        break;
      case 'e':
        running = false;
        printf("   Até mais!");
        break;
      default:
        printf("   Opção inválida!");
        break;
    }

    printf("\n\n");
  }

  return 0;
}