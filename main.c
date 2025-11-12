#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NAME_SIZE 51
#define DOCUMENT_SIZE 12
#define DESCRIPTION_SIZE 81
#define EMAIL_SIZE 71
#define PHONE_SIZE 21
#define ROLE_SIZE 31
#define UNIT_SIZE 50

typedef struct
{
  int day;
  int month;
  int year;
  long int timestamp;
} Date;

typedef struct
{
  char document_number[DOCUMENT_SIZE];
  char name[NAME_SIZE];
  Date admission_date;
  char role[ROLE_SIZE];
  char email[EMAIL_SIZE];
  char phone[PHONE_SIZE];
} Collaborator;

typedef struct
{
  int code;
  char title[NAME_SIZE];
  char description[DESCRIPTION_SIZE];
  Date start_date;
  Date predicted_finish_date;
} Project;

typedef struct
{
  char document_number[DOCUMENT_SIZE];
  int code;
  char function[ROLE_SIZE];
  int weekly_hours;
} Participation;

void getCharInput(char *output)
{
  scanf("%c", output);
  getchar();
}

void getTextInput(char *string, int length)
{
  fgets(string, length + 1, stdin);
  string[strcspn(string, "\n")] = '\0';
}

void printCollaboratorSubmenu()
{
  printf("\n -=+ Submenu de Colaborador +=-\n\n");
  printf("   a) Registrar colaborador\n");
  printf("   b) Listar colaboradores\n");
  printf("   c) Procurar colaborador\n");
  printf("   d) Alterar dados de um colaborador\n");
  printf("   e) Remover um colaborador\n");
  printf("   f) Voltar\n\n");
}

int findCollaborator(Collaborator *vector, int count, char *document)
{
  int index = -1;
  Collaborator collaborator;

  for (int i = 0; i < count; i++)
  {
    collaborator = vector[i];

    if (strcmp(collaborator.document_number, document) == 0)
    {
      index = i;
      break;
    }
  }

  return index;
}

void printDate(Date date)
{
  if (date.day < 10)
  {
    printf("0");
  }
  printf("%d/", date.day);

  if (date.month < 10)
  {
    printf("0");
  }
  printf("%d/%d", date.month, date.year);
}

void printCollaborator(Collaborator collaborator)
{
  printf("Documento: ");
  puts(collaborator.document_number);
  printf("Nome: ");
  puts(collaborator.name);
  printf("Data de admissão: ");
  printDate(collaborator.admission_date);
  printf("\nCargo: ");
  puts(collaborator.role);
  printf("E-mail: ");
  puts(collaborator.email);
  printf("Telefone: ");
  puts(collaborator.phone);
}

Collaborator *reallocateCollaboratorVector(Collaborator *vector, int size)
{
  Collaborator *newVector = (Collaborator *)realloc(vector, size * sizeof(Collaborator));

  if (newVector == NULL)
  {
    printf("Erro ao realocar memória.\n");
    exit(0);
  }

  return newVector;
}

void collaboratorSubmenu()
{
  Collaborator *collaboratorVector;
  int size = UNIT_SIZE;
  int count = 0;

  bool running = true;
  char option, document[DOCUMENT_SIZE];
  int index;

  collaboratorVector = (Collaborator *)malloc(size * sizeof(Collaborator));
  if (collaboratorVector == NULL)
  {
    printf("Erro ao alocar memória.\n");
    exit(0);
  }

  while (running)
  {
    printCollaboratorSubmenu();

    getCharInput(&option);
    printf("\n");

    if (count == size)
    {
      size = size + UNIT_SIZE;
      reallocateCollaboratorVector(collaboratorVector, size);
    }

    switch (option)
    {
    case 'a':
      Collaborator collaborator;

      printf("Digite o documento: ");
      getTextInput(collaborator.document_number, DOCUMENT_SIZE);

      if (findCollaborator(collaboratorVector, count, collaborator.document_number) == -1)
      {
        printf("Digite o nome: ");
        getTextInput(collaborator.name, NAME_SIZE);

        printf("Digite o dia de admissão: ");
        scanf("%d", &collaborator.admission_date.day);

        printf("Digite o mês de admissão: ");
        scanf("%d", &collaborator.admission_date.month);

        printf("Digite o ano de admissão: ");
        scanf("%d", &collaborator.admission_date.year);
        getchar();

        printf("Digite o cargo: ");
        getTextInput(collaborator.role, ROLE_SIZE);

        printf("Digite o e-mail: ");
        getTextInput(collaborator.email, EMAIL_SIZE);

        printf("Digite o telefone: ");
        getTextInput(collaborator.phone, PHONE_SIZE);

        collaboratorVector[count] = collaborator;
        count++;
      }
      else
      {
        printf("Já existe um colaborador com este documento!");
      }
      break;
    case 'b':
      printf("Lista de colaboradores:\n");

      for (int i = 0; i < count; i++)
      {
        printf("Colaborador nº %d\n", i + 1);
        printCollaborator(collaboratorVector[i]);
        printf("\n");
      }
      break;
    case 'c':
      document[DOCUMENT_SIZE];
      printf("Digite o documento do colaborador que deseja procurar: ");
      getTextInput(document, DOCUMENT_SIZE);

      index = findCollaborator(collaboratorVector, count, document);

      if (index == -1)
      {
        printf("Não existe nenhum colaborador com este documento.");
      }
      else
      {
        printf("Colaborador encontrado!\n\n");
        printCollaborator(collaboratorVector[index]);
      }
      break;
    case 'd':
      break;
    case 'e':
      printf("Digite o documento do colaborador que deseja procurar: ");
      getTextInput(document, DOCUMENT_SIZE);

      index = findCollaborator(collaboratorVector, count, document);

      if (index == -1)
      {
        printf("Não existe nenhum colaborador com este documento.");
      }
      else
      {
        printf("Colaborador encontrado!\n");

        bool asking = true;

        while (asking)
        {
          printf("Deseja removê-lo? (S/N) ");
          char answer;
          getCharInput(&answer);

          if (answer == 'S' || answer == 's')
          {
            for (int i = index; i < count - 1; i++) {
              collaboratorVector[i] = collaboratorVector[i + 1];
            }
            count--;
            asking = false;
          }
          else if (answer == 'N' || answer == 'n')
          {
            asking = false;
          }
          else
          {
            printf("Opção inválida!\n");
          }
        }
      }
      break;
    case 'f':
      running = false;
      free(collaboratorVector);
      break;
    default:
      printf("   Opção inválida!");
      break;
    }

    if (option != 'f')
    {
      printf("\n");
    }
  }
}

void printProjectSubmenu()
{
  printf("\n -=+ Submenu de Projeto +=-\n\n");
  printf("   a) Registrar projeto\n");
  printf("   b) Listar projetos\n");
  printf("   c) Procurar projeto\n");
  printf("   d) Alterar dados de um projeto\n");
  printf("   e) Remover um projeto\n");
  printf("   f) Voltar\n\n");
}

void projectSubmenu()
{
  bool running = true;
  char option;

  while (running)
  {
    printProjectSubmenu();

    getCharInput(&option);
    printf("\n");

    switch (option)
    {
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

    if (option != 'f')
    {
      printf("\n");
    }
  }
}

void printParticipationSubmenu()
{
  printf("\n -=+ Submenu de Participação +=-\n\n");
  printf("   a) Registrar participação\n");
  printf("   b) Listar participações\n");
  printf("   c) Procurar participação\n");
  printf("   d) Alterar dados de uma participação\n");
  printf("   e) Remover uma participação\n");
  printf("   f) Voltar\n\n");
}

void participationSubmenu()
{
  bool running = true;
  char option;

  while (running)
  {
    printParticipationSubmenu();

    getCharInput(&option);
    printf("\n");

    switch (option)
    {
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

    if (option != 'f')
    {
      printf("\n");
    }
  }
}

void printReportSubmenu()
{
  printf("\n -=+ Submenu de Relatório +=-\n\n");
  printf("   a) Listar colaboradores de um projeto\n");
  printf("   b) Listar projetos de um colaborador\n");
  printf("   c) Listar projetos e colaboradores em andamento entre duas datas\n");
  printf("   d) Voltar\n\n");
}

void reportSubmenu()
{
  bool running = true;
  char option;

  while (running)
  {
    printReportSubmenu();

    getCharInput(&option);
    printf("\n");

    switch (option)
    {
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

    if (option != 'd')
    {
      printf("\n");
    }
  }
}

void printMenu()
{
  printf("\n -=+ Sistema de Gerenciamento de Projetos +=-\n\n");
  printf("   a) Submenu de Colaborador\n");
  printf("   b) Submenu de Projeto\n");
  printf("   c) Submenu de Participação\n");
  printf("   d) Submenu de Relatórios\n");
  printf("   e) Sair\n\n");
}

int main()
{
  bool running = true;
  char option;

  while (running)
  {
    printMenu();

    getCharInput(&option);
    printf("\n");

    switch (option)
    {
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