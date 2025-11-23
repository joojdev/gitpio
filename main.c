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
#define UNIT_SIZE 3
#define COLLABORATOR_FILE "collaborators.dat"
#define PROJECT_FILE "projects.dat"
#define PARTICIPATION_FILE "participations.dat"

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
  char buffer[10];
  fgets(buffer, sizeof(buffer), stdin);
  *output = buffer[0];
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

void bubbleSortParticipations(Participation *vector, int count)
{
  int i, j;
  Participation temp;

  for (i = 0; i < count - 1; i++)
  {
    for (j = 0; j < count - i - 1; j++)
    {
      int differenceOfDocument = strcmp(vector[j].document_number, vector[j + 1].document_number);

      if (differenceOfDocument > 0 || (differenceOfDocument == 0 && vector[j].code > vector[j + 1].code))
      {
        temp = vector[j];
        vector[j] = vector[j + 1];
        vector[j + 1] = temp;
      }
    }
  }
}

int binarySearchParticipation(Participation *vector, int count, char *document, int code)
{
  int left = 0;
  int right = count - 1;

  while (left <= right)
  {
    int middle = left + (right - left) / 2;
    int differenceOfDocument = strcmp(vector[middle].document_number, document);

    if (differenceOfDocument == 0 && vector[middle].code == code)
      return middle;

    if (differenceOfDocument < 0 || (differenceOfDocument == 0 && vector[middle].code < code))
      left = middle + 1;
    else
      right = middle - 1;
  }

  return -1;
}

int findParticipation(Participation *vector, int count, char *document, int code)
{
  return binarySearchParticipation(vector, count, document, code);
}

int findInsertPositionParticipation(Participation *vector, int count, char *document, int code)
{
  int left = 0;
  int right = count;

  while (left < right)
  {
    int middle = left + (right - left) / 2;
    int differenceOfDocument = strcmp(vector[middle].document_number, document);

    if (differenceOfDocument < 0 || (differenceOfDocument == 0 && vector[middle].code < code))
      left = middle + 1;
    else
      right = middle;
  }

  return left;
}

void insertParticipationSorted(Participation *vector, int count, Participation participation)
{
  int position = findInsertPositionParticipation(vector, count, participation.document_number, participation.code);

  for (int i = count; i > position; i--)
  {
    vector[i] = vector[i - 1];
  }

  vector[position] = participation;
}

void bubbleSortCollaborators(Collaborator *vector, int count)
{
  int i, j;
  Collaborator temp;

  for (i = 0; i < count - 1; i++)
  {
    for (j = 0; j < count - i - 1; j++)
    {
      if (strcmp(vector[j].document_number, vector[j + 1].document_number) > 0)
      {
        temp = vector[j];
        vector[j] = vector[j + 1];
        vector[j + 1] = temp;
      }
    }
  }
}

void bubbleSortProjects(Project *vector, int count)
{
  int i, j;
  Project temp;

  for (i = 0; i < count - 1; i++)
  {
    for (j = 0; j < count - i - 1; j++)
    {
      if (vector[j].code > vector[j + 1].code)
      {
        temp = vector[j];
        vector[j] = vector[j + 1];
        vector[j + 1] = temp;
      }
    }
  }
}

int binarySearchCollaborator(Collaborator *vector, int count, char *document)
{
  int left = 0;
  int right = count - 1;

  while (left <= right)
  {
    int middle = left + (right - left) / 2;
    int difference = strcmp(vector[middle].document_number, document);

    if (difference == 0)
      return middle;

    if (difference < 0)
      left = middle + 1;
    else
      right = middle - 1;
  }

  return -1;
}

int binarySearchProject(Project *vector, int count, int code)
{
  int left = 0;
  int right = count - 1;

  while (left <= right)
  {
    int middle = left + (right - left) / 2;

    if (vector[middle].code == code)
      return middle;

    if (vector[middle].code < code)
      left = middle + 1;
    else
      right = middle - 1;
  }

  return -1;
}

int findCollaborator(Collaborator *vector, int count, char *document)
{
  return binarySearchCollaborator(vector, count, document);
}

int findProject(Project *vector, int count, int code)
{
  return binarySearchProject(vector, count, code);
}

int findInsertPositionCollaborator(Collaborator *vector, int count, char *document)
{
  int left = 0;
  int right = count;

  while (left < right)
  {
    int middle = left + (right - left) / 2;

    if (strcmp(vector[middle].document_number, document) < 0)
      left = middle + 1;
    else
      right = middle;
  }

  return left;
}

void insertCollaboratorSorted(Collaborator *vector, int count, Collaborator collaborator)
{
  int position = findInsertPositionCollaborator(vector, count, collaborator.document_number);

  for (int i = count; i > position; i--)
  {
    vector[i] = vector[i - 1];
  }

  vector[position] = collaborator;
}

int findInsertPositionProject(Project *vector, int count, int code)
{
  int left = 0;
  int right = count;

  while (left < right)
  {
    int middle = left + (right - left) / 2;

    if (vector[middle].code < code)
      left = middle + 1;
    else
      right = middle;
  }

  return left;
}

void insertProjectSorted(Project *vector, int count, Project project)
{
  int position = findInsertPositionProject(vector, count, project.code);

  for (int i = count; i > position; i--)
  {
    vector[i] = vector[i - 1];
  }

  vector[position] = project;
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
  printf("CPF: ");
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

void printProject(Project project)
{
  printf("Código: %d\n", project.code);
  printf("Título: ");
  puts(project.title);
  printf("Descrição: ");
  puts(project.description);
  printf("Data de início: ");
  printDate(project.start_date);
  printf("\nData prevista de término: ");
  printDate(project.predicted_finish_date);
  printf("\n");
}

void printParticipation(Participation participation)
{
  printf("CPF do Colaborador: ");
  puts(participation.document_number);
  printf("Código do Projeto: %d\n", participation.code);
  printf("Função: ");
  puts(participation.function);
  printf("Carga Horária Semanal: %d horas\n", participation.weekly_hours);
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

Project *reallocateProjectVector(Project *vector, int size)
{
  Project *newVector = (Project *)realloc(vector, size * sizeof(Project));

  if (newVector == NULL)
  {
    printf("Erro ao realocar memória.\n");
    exit(0);
  }

  return newVector;
}

int loadCollaborators(Collaborator **vector, int *size)
{
  FILE *fp;
  int count = 0;
  Collaborator temp;

  fp = fopen(COLLABORATOR_FILE, "rb");

  if (fp == NULL)
  {
    printf("Nenhum arquivo de dados encontrado. Iniciando com lista vazia.\n");
    return 0;
  }

  while (fread(&temp, sizeof(Collaborator), 1, fp) == 1)
  {
    count++;
  }

  if (count > 0)
  {
    *size = ((count / UNIT_SIZE) + 1) * UNIT_SIZE;

    *vector = reallocateCollaboratorVector(*vector, *size);

    rewind(fp);

    for (int i = 0; i < count; i++)
    {
      if (fread(&(*vector)[i], sizeof(Collaborator), 1, fp) != 1)
      {
        printf("Erro ao ler dados do arquivo.\n");
        fclose(fp);
        return i;
      }
    }

    printf("Carregados %d colaborador(es) do arquivo.\n", count);
  }

  fclose(fp);
  return count;
}

void saveCollaborators(Collaborator *vector, int count)
{
  FILE *fp;

  fp = fopen(COLLABORATOR_FILE, "wb");

  if (fp == NULL)
  {
    printf("Erro ao abrir arquivo para gravação.\n");
    exit(0);
  }

  if (count > 0)
  {
    if (fwrite(vector, sizeof(Collaborator), count, fp) != count)
    {
      printf("Erro ao gravar dados no arquivo.\n");
    }
    else
    {
      printf("Dados salvos com sucesso! (%d colaborador(es))\n", count);
    }
  }

  fclose(fp);
}

int loadProjects(Project **vector, int *size)
{
  FILE *fp;
  int count = 0;
  Project temp;

  fp = fopen(PROJECT_FILE, "rb");

  if (fp == NULL)
  {
    printf("Nenhum arquivo de dados encontrado. Iniciando com lista vazia.\n");
    return 0;
  }

  while (fread(&temp, sizeof(Project), 1, fp) == 1)
  {
    count++;
  }

  if (count > 0)
  {
    *size = ((count / UNIT_SIZE) + 1) * UNIT_SIZE;

    *vector = reallocateProjectVector(*vector, *size);

    rewind(fp);

    for (int i = 0; i < count; i++)
    {
      if (fread(&(*vector)[i], sizeof(Project), 1, fp) != 1)
      {
        printf("Erro ao ler dados do arquivo.\n");
        fclose(fp);
        return i;
      }
    }

    printf("Carregados %d projeto(s) do arquivo.\n", count);
  }

  fclose(fp);
  return count;
}

void saveProjects(Project *vector, int count)
{
  FILE *fp;

  fp = fopen(PROJECT_FILE, "wb");

  if (fp == NULL)
  {
    printf("Erro ao abrir arquivo para gravação.\n");
    exit(0);
  }

  if (count > 0)
  {
    if (fwrite(vector, sizeof(Project), count, fp) != count)
    {
      printf("Erro ao gravar dados no arquivo.\n");
    }
    else
    {
      printf("Dados salvos com sucesso! (%d projeto(s))\n", count);
    }
  }

  fclose(fp);
}

Participation *reallocateParticipationVector(Participation *vector, int size)
{
  Participation *newVector = (Participation *)realloc(vector, size * sizeof(Participation));

  if (newVector == NULL)
  {
    printf("Erro ao realocar memória.\n");
    exit(0);
  }

  return newVector;
}

int loadParticipations(Participation **vector, int *size)
{
  FILE *fp;
  int count = 0;
  Participation temp;

  fp = fopen(PARTICIPATION_FILE, "rb");

  if (fp == NULL)
  {
    printf("Nenhum arquivo de dados encontrado. Iniciando com lista vazia.\n");
    return 0;
  }

  while (fread(&temp, sizeof(Participation), 1, fp) == 1)
  {
    count++;
  }

  if (count > 0)
  {
    *size = ((count / UNIT_SIZE) + 1) * UNIT_SIZE;

    *vector = reallocateParticipationVector(*vector, *size);

    rewind(fp);

    for (int i = 0; i < count; i++)
    {
      if (fread(&(*vector)[i], sizeof(Participation), 1, fp) != 1)
      {
        printf("Erro ao ler dados do arquivo.\n");
        fclose(fp);
        return i;
      }
    }

    printf("Carregados %d participação(ões) do arquivo.\n", count);
  }

  fclose(fp);
  return count;
}

void saveParticipations(Participation *vector, int count)
{
  FILE *fp;

  fp = fopen(PARTICIPATION_FILE, "wb");

  if (fp == NULL)
  {
    printf("Erro ao abrir arquivo para gravação.\n");
    exit(0);
  }

  if (count > 0)
  {
    if (fwrite(vector, sizeof(Participation), count, fp) != count)
    {
      printf("Erro ao gravar dados no arquivo.\n");
    }
    else
    {
      printf("Dados salvos com sucesso! (%d participação(ões))\n", count);
    }
  }

  fclose(fp);
}

void collaboratorSubmenu()
{
  Collaborator *collaboratorVector;
  int size = UNIT_SIZE;
  int count = 0;

  bool running = true, changed;
  char option, document[DOCUMENT_SIZE], newDocument[DOCUMENT_SIZE];
  int index;

  collaboratorVector = (Collaborator *)malloc(size * sizeof(Collaborator));
  if (collaboratorVector == NULL)
  {
    printf("Erro ao alocar memória.\n");
    exit(0);
  }

  count = loadCollaborators(&collaboratorVector, &size);

  if (count > 0)
  {
    bubbleSortCollaborators(collaboratorVector, count);
  }

  while (running)
  {
    printCollaboratorSubmenu();

    getCharInput(&option);
    printf("\n");

    if (count == size)
    {
      size = size + UNIT_SIZE;
      collaboratorVector = reallocateCollaboratorVector(collaboratorVector, size);
    }

    switch (option)
    {
    case 'a':
      Collaborator collaborator;

      printf("Digite o CPF: ");
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

        insertCollaboratorSorted(collaboratorVector, count, collaborator);
        count++;
      }
      else
      {
        printf("Já existe um colaborador com este CPF!");
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
      printf("Digite o CPF do colaborador que deseja procurar: ");
      getTextInput(document, DOCUMENT_SIZE);

      index = findCollaborator(collaboratorVector, count, document);

      if (index == -1)
      {
        printf("Não existe nenhum colaborador com este CPF.");
      }
      else
      {
        printf("Colaborador encontrado!\n\n");
        printCollaborator(collaboratorVector[index]);
      }
      break;
    case 'd':
      printf("Digite o CPF do colaborador que deseja procurar: ");
      getTextInput(document, DOCUMENT_SIZE);

      index = findCollaborator(collaboratorVector, count, document);
      changed = true;

      if (index == -1)
      {
        printf("Não existe nenhum colaborador com este CPF.");
        changed = false;
      }
      else
      {
        printf("Colaborador encontrado!\n\n");

        collaborator = collaboratorVector[index];
        printCollaborator(collaborator);

        printf("\nQual atributo deseja alterar?\n");
        printf("a. CPF\n");
        printf("b. Nome\n");
        printf("c. Data de Admissão\n");
        printf("d. Cargo\n");
        printf("e. E-mail\n");
        printf("f. Telefone\n\n");
        printf("g. Voltar\n\n");

        char modifyOption;

        getCharInput(&modifyOption);

        switch (modifyOption)
        {
        case 'a':
          printf("Digite o CPF: ");
          getTextInput(newDocument, DOCUMENT_SIZE);

          if (findCollaborator(collaboratorVector, count, newDocument) == -1)
          {
            strcpy(collaborator.document_number, newDocument);

            for (int i = index; i < count - 1; i++)
            {
              collaboratorVector[i] = collaboratorVector[i + 1];
            }
            count--;

            insertCollaboratorSorted(collaboratorVector, count, collaborator);
            count++;
          }
          else
          {
            printf("Já existe um colaborador com este CPF!\n");
            changed = false;
          }
          break;
        case 'b':
          printf("Digite o nome: ");
          getTextInput(collaborator.name, NAME_SIZE);
          break;
        case 'c':
          printf("Digite o dia de admissão: ");
          scanf("%d", &collaborator.admission_date.day);

          printf("Digite o mês de admissão: ");
          scanf("%d", &collaborator.admission_date.month);

          printf("Digite o ano de admissão: ");
          scanf("%d", &collaborator.admission_date.year);
          getchar();
          break;
        case 'd':
          printf("Digite o cargo: ");
          getTextInput(collaborator.role, ROLE_SIZE);
          break;
        case 'e':
          printf("Digite o e-mail: ");
          getTextInput(collaborator.email, EMAIL_SIZE);
          break;
        case 'f':
          printf("Digite o telefone: ");
          getTextInput(collaborator.phone, PHONE_SIZE);
          break;
        case 'g':
          printf("Nenhuma modificação");
          changed = false;
          break;
        default:
          printf("Opção inválida!");
          changed = false;
          break;
        }
      }

      if (changed)
      {
        printf("Colaborador alterado com sucesso!\n");
        collaboratorVector[index] = collaborator;
      }

      break;
    case 'e':
      printf("Digite o CPF do colaborador que deseja procurar: ");
      getTextInput(document, DOCUMENT_SIZE);

      index = findCollaborator(collaboratorVector, count, document);

      if (index == -1)
      {
        printf("Não existe nenhum colaborador com este CPF.");
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
            for (int i = index; i < count - 1; i++)
            {
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
      saveCollaborators(collaboratorVector, count);
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
  Project *projectVector;
  int size = UNIT_SIZE;
  int count = 0;

  bool running = true, changed;
  char option;
  int code, newCode, index;

  projectVector = (Project *)malloc(size * sizeof(Project));
  if (projectVector == NULL)
  {
    printf("Erro ao alocar memória.\n");
    exit(0);
  }

  count = loadProjects(&projectVector, &size);

  if (count > 0)
  {
    bubbleSortProjects(projectVector, count);
  }

  while (running)
  {
    printProjectSubmenu();

    getCharInput(&option);
    printf("\n");

    if (count == size)
    {
      size = size + UNIT_SIZE;
      projectVector = reallocateProjectVector(projectVector, size);
    }

    switch (option)
    {
    case 'a':
      Project project;

      printf("Digite o código: ");
      scanf("%d", &project.code);
      getchar();

      if (findProject(projectVector, count, project.code) == -1)
      {
        printf("Digite o título: ");
        getTextInput(project.title, NAME_SIZE);

        printf("Digite a descrição: ");
        getTextInput(project.description, DESCRIPTION_SIZE);

        printf("Digite o dia de início: ");
        scanf("%d", &project.start_date.day);

        printf("Digite o mês de início: ");
        scanf("%d", &project.start_date.month);

        printf("Digite o ano de início: ");
        scanf("%d", &project.start_date.year);

        printf("Digite o dia previsto de término: ");
        scanf("%d", &project.predicted_finish_date.day);

        printf("Digite o mês previsto de término: ");
        scanf("%d", &project.predicted_finish_date.month);

        printf("Digite o ano previsto de término: ");
        scanf("%d", &project.predicted_finish_date.year);
        getchar();

        insertProjectSorted(projectVector, count, project);
        count++;
      }
      else
      {
        printf("Já existe um projeto com este código!");
      }
      break;
    case 'b':
      printf("Lista de projetos:\n");

      for (int i = 0; i < count; i++)
      {
        printf("Projeto nº %d\n", i + 1);
        printProject(projectVector[i]);
        printf("\n");
      }
      break;
    case 'c':
      printf("Digite o código do projeto que deseja procurar: ");
      scanf("%d", &code);
      getchar();

      index = findProject(projectVector, count, code);

      if (index == -1)
      {
        printf("Não existe nenhum projeto com este código.");
      }
      else
      {
        printf("Projeto encontrado!\n\n");
        printProject(projectVector[index]);
      }
      break;
    case 'd':
      printf("Digite o código do projeto que deseja procurar: ");
      scanf("%d", &code);
      getchar();

      index = findProject(projectVector, count, code);
      changed = true;

      if (index == -1)
      {
        printf("Não existe nenhum projeto com este código.");
        changed = false;
      }
      else
      {
        printf("Projeto encontrado!\n\n");

        project = projectVector[index];
        printProject(project);

        printf("\nQual atributo deseja alterar?\n");
        printf("a. Código\n");
        printf("b. Título\n");
        printf("c. Descrição\n");
        printf("d. Data de Início\n");
        printf("e. Data Prevista de Término\n\n");
        printf("f. Voltar\n\n");

        char modifyOption;

        getCharInput(&modifyOption);

        switch (modifyOption)
        {
        case 'a':
          printf("Digite o código: ");
          scanf("%d", &newCode);
          getchar();

          if (findProject(projectVector, count, newCode) == -1)
          {
            project.code = newCode;

            for (int i = index; i < count - 1; i++)
            {
              projectVector[i] = projectVector[i + 1];
            }
            count--;

            insertProjectSorted(projectVector, count, project);
            count++;
          }
          else
          {
            printf("Já existe um projeto com este código!\n");
            changed = false;
          }
          break;
        case 'b':
          printf("Digite o título: ");
          getTextInput(project.title, NAME_SIZE);
          break;
        case 'c':
          printf("Digite a descrição: ");
          getTextInput(project.description, DESCRIPTION_SIZE);
          break;
        case 'd':
          printf("Digite o dia de início: ");
          scanf("%d", &project.start_date.day);

          printf("Digite o mês de início: ");
          scanf("%d", &project.start_date.month);

          printf("Digite o ano de início: ");
          scanf("%d", &project.start_date.year);
          getchar();
          break;
        case 'e':
          printf("Digite o dia previsto de término: ");
          scanf("%d", &project.predicted_finish_date.day);

          printf("Digite o mês previsto de término: ");
          scanf("%d", &project.predicted_finish_date.month);

          printf("Digite o ano previsto de término: ");
          scanf("%d", &project.predicted_finish_date.year);
          getchar();
          break;
        case 'f':
          printf("Nenhuma modificação");
          changed = false;
          break;
        default:
          printf("Opção inválida!");
          changed = false;
          break;
        }
      }

      if (changed)
      {
        printf("Projeto alterado com sucesso!\n");
        projectVector[index] = project;
      }

      break;
    case 'e':
      printf("Digite o código do projeto que deseja procurar: ");
      scanf("%d", &code);
      getchar();

      index = findProject(projectVector, count, code);

      if (index == -1)
      {
        printf("Não existe nenhum projeto com este código.");
      }
      else
      {
        printf("Projeto encontrado!\n");

        bool asking = true;

        while (asking)
        {
          printf("Deseja removê-lo? (S/N) ");
          char answer;
          getCharInput(&answer);

          if (answer == 'S' || answer == 's')
          {
            for (int i = index; i < count - 1; i++)
            {
              projectVector[i] = projectVector[i + 1];
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
      saveProjects(projectVector, count);
      free(projectVector);
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
  Participation *participationVector;
  Collaborator *collaboratorVector;
  Project *projectVector;

  int participationSize = UNIT_SIZE;
  int collaboratorSize = UNIT_SIZE;
  int projectSize = UNIT_SIZE;

  int participationCount = 0;
  int collaboratorCount = 0;
  int projectCount = 0;

  bool running = true, changed;
  char option, document[DOCUMENT_SIZE], newDocument[DOCUMENT_SIZE];
  int code, newCode, index, collaboratorIndex, projectIndex;

  participationVector = (Participation *)malloc(participationSize * sizeof(Participation));
  if (participationVector == NULL)
  {
    printf("Erro ao alocar memória.\n");
    exit(0);
  }

  collaboratorVector = (Collaborator *)malloc(collaboratorSize * sizeof(Collaborator));
  if (collaboratorVector == NULL)
  {
    printf("Erro ao alocar memória.\n");
    free(participationVector);
    exit(0);
  }

  projectVector = (Project *)malloc(projectSize * sizeof(Project));
  if (projectVector == NULL)
  {
    printf("Erro ao alocar memória.\n");
    free(participationVector);
    free(collaboratorVector);
    exit(0);
  }

  participationCount = loadParticipations(&participationVector, &participationSize);
  collaboratorCount = loadCollaborators(&collaboratorVector, &collaboratorSize);
  projectCount = loadProjects(&projectVector, &projectSize);

  if (participationCount > 0)
  {
    bubbleSortParticipations(participationVector, participationCount);
  }
  if (collaboratorCount > 0)
  {
    bubbleSortCollaborators(collaboratorVector, collaboratorCount);
  }
  if (projectCount > 0)
  {
    bubbleSortProjects(projectVector, projectCount);
  }

  while (running)
  {
    printParticipationSubmenu();

    getCharInput(&option);
    printf("\n");

    if (participationCount == participationSize)
    {
      participationSize = participationSize + UNIT_SIZE;
      participationVector = reallocateParticipationVector(participationVector, participationSize);
    }

    switch (option)
    {
    case 'a':
      Participation participation;

      printf("Digite o CPF do colaborador: ");
      getTextInput(participation.document_number, DOCUMENT_SIZE);

      collaboratorIndex = findCollaborator(collaboratorVector, collaboratorCount, participation.document_number);

      if (collaboratorIndex == -1)
      {
        printf("Erro: Não existe colaborador cadastrado com este CPF!\n");
        break;
      }

      printf("Digite o código do projeto: ");
      scanf("%d", &participation.code);
      getchar();

      projectIndex = findProject(projectVector, projectCount, participation.code);

      if (projectIndex == -1)
      {
        printf("Erro: Não existe projeto cadastrado com este código!\n");
        break;
      }

      if (findParticipation(participationVector, participationCount, participation.document_number, participation.code) == -1)
      {
        printf("Digite a função no projeto: ");
        getTextInput(participation.function, ROLE_SIZE);

        printf("Digite a carga horária semanal: ");
        scanf("%d", &participation.weekly_hours);
        getchar();

        insertParticipationSorted(participationVector, participationCount, participation);
        participationCount++;
        printf("Participação registrada com sucesso!\n");
      }
      else
      {
        printf("Já existe uma participação com este CPF e código de projeto!");
      }
      break;

    case 'b':
      if (participationCount == 0)
      {
        printf("Nenhuma participação cadastrada.\n");
      }
      else
      {
        printf("Lista de participações:\n\n");

        for (int i = 0; i < participationCount; i++)
        {
          printf("Participação nº %d\n", i + 1);
          printParticipation(participationVector[i]);

          collaboratorIndex = findCollaborator(collaboratorVector, collaboratorCount, participationVector[i].document_number);
          if (collaboratorIndex != -1)
          {
            printf("Nome do Colaborador: %s\n", collaboratorVector[collaboratorIndex].name);
          }

          projectIndex = findProject(projectVector, projectCount, participationVector[i].code);
          if (projectIndex != -1)
          {
            printf("Título do Projeto: %s\n", projectVector[projectIndex].title);
          }

          printf("\n");
        }
      }
      break;

    case 'c':
      printf("Digite o CPF do colaborador: ");
      getTextInput(document, DOCUMENT_SIZE);

      printf("Digite o código do projeto: ");
      scanf("%d", &code);
      getchar();

      index = findParticipation(participationVector, participationCount, document, code);

      if (index == -1)
      {
        printf("Não existe nenhuma participação com este CPF e código de projeto.");
      }
      else
      {
        printf("Participação encontrada!\n\n");
        printParticipation(participationVector[index]);

        collaboratorIndex = findCollaborator(collaboratorVector, collaboratorCount, document);
        if (collaboratorIndex != -1)
        {
          printf("Nome do Colaborador: %s\n", collaboratorVector[collaboratorIndex].name);
        }

        projectIndex = findProject(projectVector, projectCount, code);
        if (projectIndex != -1)
        {
          printf("Título do Projeto: %s\n", projectVector[projectIndex].title);
        }
      }
      break;

    case 'd':
      printf("Digite o CPF do colaborador: ");
      getTextInput(document, DOCUMENT_SIZE);

      printf("Digite o código do projeto: ");
      scanf("%d", &code);
      getchar();

      index = findParticipation(participationVector, participationCount, document, code);
      changed = true;

      if (index == -1)
      {
        printf("Não existe nenhuma participação com este CPF e código de projeto.");
        changed = false;
      }
      else
      {
        printf("Participação encontrada!\n\n");

        participation = participationVector[index];
        printParticipation(participation);

        printf("\nQual atributo deseja alterar?\n");
        printf("a. CPF do Colaborador\n");
        printf("b. Código do Projeto\n");
        printf("c. Função\n");
        printf("d. Carga Horária Semanal\n\n");
        printf("e. Voltar\n\n");

        char modifyOption;

        getCharInput(&modifyOption);

        switch (modifyOption)
        {
        case 'a':
          printf("Digite o CPF do colaborador: ");
          getTextInput(newDocument, DOCUMENT_SIZE);

          collaboratorIndex = findCollaborator(collaboratorVector, collaboratorCount, newDocument);

          if (collaboratorIndex == -1)
          {
            printf("Erro: Não existe colaborador cadastrado com este CPF!\n");
            changed = false;
            break;
          }

          if (findParticipation(participationVector, participationCount, newDocument, participation.code) == -1)
          {
            strcpy(participation.document_number, newDocument);

            for (int i = index; i < participationCount - 1; i++)
            {
              participationVector[i] = participationVector[i + 1];
            }
            participationCount--;

            insertParticipationSorted(participationVector, participationCount, participation);
            participationCount++;
          }
          else
          {
            printf("Já existe uma participação com este CPF e código de projeto!\n");
            changed = false;
          }
          break;

        case 'b':
          printf("Digite o código do projeto: ");
          scanf("%d", &newCode);
          getchar();

          projectIndex = findProject(projectVector, projectCount, newCode);

          if (projectIndex == -1)
          {
            printf("Erro: Não existe projeto cadastrado com este código!\n");
            changed = false;
            break;
          }

          if (findParticipation(participationVector, participationCount, participation.document_number, newCode) == -1)
          {
            participation.code = newCode;

            for (int i = index; i < participationCount - 1; i++)
            {
              participationVector[i] = participationVector[i + 1];
            }
            participationCount--;

            insertParticipationSorted(participationVector, participationCount, participation);
            participationCount++;
          }
          else
          {
            printf("Já existe uma participação com este CPF e código de projeto!\n");
            changed = false;
          }
          break;

        case 'c':
          printf("Digite a função no projeto: ");
          getTextInput(participation.function, ROLE_SIZE);
          break;

        case 'd':
          printf("Digite a carga horária semanal: ");
          scanf("%d", &participation.weekly_hours);
          getchar();
          break;

        case 'e':
          printf("Nenhuma modificação");
          changed = false;
          break;

        default:
          printf("Opção inválida!");
          changed = false;
          break;
        }
      }

      if (changed)
      {
        printf("Participação alterada com sucesso!\n");
        participationVector[index] = participation;
      }

      break;

    case 'e':
      printf("Digite o CPF do colaborador: ");
      getTextInput(document, DOCUMENT_SIZE);

      printf("Digite o código do projeto: ");
      scanf("%d", &code);
      getchar();

      index = findParticipation(participationVector, participationCount, document, code);

      if (index == -1)
      {
        printf("Não existe nenhuma participação com este CPF e código de projeto.");
      }
      else
      {
        printf("Participação encontrada!\n");

        bool asking = true;

        while (asking)
        {
          printf("Deseja removê-la? (S/N) ");
          char answer;
          getCharInput(&answer);

          if (answer == 'S' || answer == 's')
          {
            for (int i = index; i < participationCount - 1; i++)
            {
              participationVector[i] = participationVector[i + 1];
            }
            participationCount--;
            printf("Participação removida com sucesso!\n");
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
      saveParticipations(participationVector, participationCount);

      free(participationVector);
      free(collaboratorVector);
      free(projectVector);
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

void reportCollaboratorsOfProject(Participation *participationVector, int participationCount,
                                  Collaborator *collaboratorVector, int collaboratorCount,
                                  Project *projectVector, int projectCount)
{
  int code, collaboratorIndex, projectIndex;
  char filename[100];

  printf("Digite o código do projeto: ");
  scanf("%d", &code);
  getchar();

  projectIndex = findProject(projectVector, projectCount, code);

  if (projectIndex == -1)
  {
    printf("Não existe nenhum projeto com este código.\n");
    return;
  }

  printf("Digite o nome do arquivo para salvar o relatório (ex: relatorio.txt): ");
  getTextInput(filename, 100);

  FILE *fp = fopen(filename, "w");
  if (fp == NULL)
  {
    printf("Erro ao criar o arquivo.\n");
    return;
  }

  fprintf(fp, "Projeto: %s\n\n", projectVector[projectIndex].title);
  fprintf(fp, "Colaboradores participantes:\n\n");

  bool found = false;

  for (int i = 0; i < participationCount; i++)
  {
    if (participationVector[i].code == code)
    {
      collaboratorIndex = findCollaborator(collaboratorVector, collaboratorCount, participationVector[i].document_number);

      if (collaboratorIndex != -1)
      {
        fprintf(fp, "Nome: %s\n", collaboratorVector[collaboratorIndex].name);
        fprintf(fp, "Cargo: %s\n", collaboratorVector[collaboratorIndex].role);
        fprintf(fp, "E-mail: %s\n", collaboratorVector[collaboratorIndex].email);
        fprintf(fp, "Função no projeto: %s\n\n", participationVector[i].function);
        found = true;
      }
    }
  }

  if (!found)
    fprintf(fp, "Nenhum colaborador encontrado para este projeto.\n");

  fclose(fp);
  printf("Relatório salvo em %s\n", filename);
}

void reportProjectsOfCollaborator(Participation *participationVector, int participationCount,
                                  Collaborator *collaboratorVector, int collaboratorCount,
                                  Project *projectVector, int projectCount)
{
  int collaboratorIndex, projectIndex, code;
  char document[DOCUMENT_SIZE], filename[100];

  printf("Digite o CPF do colaborador: ");
  getTextInput(document, DOCUMENT_SIZE);

  collaboratorIndex = findCollaborator(collaboratorVector, collaboratorCount, document);

  if (collaboratorIndex == -1)
  {
    printf("Não existe nenhum colaborador com este CPF.\n");
    return;
  }

  printf("Digite o nome do arquivo para salvar o relatório (ex: relatorio.txt): ");
  getTextInput(filename, 100);

  FILE *fp = fopen(filename, "w");
  if (fp == NULL)
  {
    printf("Erro ao criar o arquivo.\n");
    return;
  }

  fprintf(fp, "Colaborador: %s\n", collaboratorVector[collaboratorIndex].name);
  fprintf(fp, "Projetos:\n\n");

  bool found = false;

  for (int i = 0; i < participationCount; i++)
  {
    if (strcmp(participationVector[i].document_number, document) == 0)
    {
      code = participationVector[i].code;
      projectIndex = findProject(projectVector, projectCount, code);

      if (projectIndex != -1)
      {
        fprintf(fp, "Título: %s\n", projectVector[projectIndex].title);
        fprintf(fp, "Data de início: %02d/%02d/%d\n",
                projectVector[projectIndex].start_date.day,
                projectVector[projectIndex].start_date.month,
                projectVector[projectIndex].start_date.year);
        fprintf(fp, "Data prevista de término: %02d/%02d/%d\n",
                projectVector[projectIndex].predicted_finish_date.day,
                projectVector[projectIndex].predicted_finish_date.month,
                projectVector[projectIndex].predicted_finish_date.year);
        fprintf(fp, "Carga horária semanal: %d horas\n\n", participationVector[i].weekly_hours);
        found = true;
      }
    }
  }

  if (!found)
    fprintf(fp, "Nenhum projeto encontrado para este colaborador.\n");

  fclose(fp);
  printf("Relatório salvo em %s\n", filename);
}

void reportProjectsBetweenDates(Project *projectVector, int projectCount,
                                Participation *participationVector, int participationCount,
                                Collaborator *collaboratorVector, int collaboratorCount)
{
  Date startDate, endDate;
  char filename[100];
  int collaboratorIndex;

  printf("Digite a data de início do período:\nDia: ");
  scanf("%d", &startDate.day);
  printf("Mês: ");
  scanf("%d", &startDate.month);
  printf("Ano: ");
  scanf("%d", &startDate.year);

  printf("\nDigite a data de fim do período:\nDia: ");
  scanf("%d", &endDate.day);
  printf("Mês: ");
  scanf("%d", &endDate.month);
  printf("Ano: ");
  scanf("%d", &endDate.year);
  getchar();

  printf("Digite o nome do arquivo para salvar o relatório (ex: relatorio.txt): ");
  getTextInput(filename, 100);

  FILE *fp = fopen(filename, "w");
  if (fp == NULL)
  {
    printf("Erro ao criar o arquivo.\n");
    return;
  }

  long int startTimestamp = startDate.year * 10000L + startDate.month * 100 + startDate.day;
  long int endTimestamp = endDate.year * 10000L + endDate.month * 100 + endDate.day;

  fprintf(fp, "Projetos em andamento entre %02d/%02d/%d e %02d/%02d/%d:\n\n",
          startDate.day, startDate.month, startDate.year,
          endDate.day, endDate.month, endDate.year);

  bool found = false;

  for (int i = 0; i < projectCount; i++)
  {
    long int projectStartTimestamp = projectVector[i].start_date.year * 10000L +
                                     projectVector[i].start_date.month * 100 +
                                     projectVector[i].start_date.day;
    long int projectEndTimestamp = projectVector[i].predicted_finish_date.year * 10000L +
                                   projectVector[i].predicted_finish_date.month * 100 +
                                   projectVector[i].predicted_finish_date.day;

    if (projectStartTimestamp <= endTimestamp && projectEndTimestamp >= startTimestamp)
    {
      fprintf(fp, "Código: %d\n", projectVector[i].code);
      fprintf(fp, "Título: %s\n", projectVector[i].title);
      fprintf(fp, "Data de início: %02d/%02d/%d\n",
              projectVector[i].start_date.day,
              projectVector[i].start_date.month,
              projectVector[i].start_date.year);
      fprintf(fp, "Colaboradores:\n");

      for (int j = 0; j < participationCount; j++)
      {
        if (participationVector[j].code == projectVector[i].code)
        {
          collaboratorIndex = findCollaborator(collaboratorVector, collaboratorCount, participationVector[j].document_number);
          if (collaboratorIndex != -1)
          {
            fprintf(fp, "  CPF: %s\n", collaboratorVector[collaboratorIndex].document_number);
            fprintf(fp, "  Nome: %s\n", collaboratorVector[collaboratorIndex].name);
          }
        }
      }

      fprintf(fp, "\n");
      found = true;
    }
  }

  if (!found)
    fprintf(fp, "Nenhum projeto encontrado neste período.\n");

  fclose(fp);
  printf("Relatório salvo em %s\n", filename);
}

void reportSubmenu()
{
  Participation *participationVector;
  Collaborator *collaboratorVector;
  Project *projectVector;

  int participationSize = UNIT_SIZE;
  int collaboratorSize = UNIT_SIZE;
  int projectSize = UNIT_SIZE;

  int participationCount = 0;
  int collaboratorCount = 0;
  int projectCount = 0;

  bool running = true;
  char option;
  int code, collaboratorIndex, projectIndex;
  char document[DOCUMENT_SIZE];
  Date startDate, endDate;

  participationVector = (Participation *)malloc(participationSize * sizeof(Participation));
  if (participationVector == NULL)
  {
    printf("Erro ao alocar memória.\n");
    exit(0);
  }

  collaboratorVector = (Collaborator *)malloc(collaboratorSize * sizeof(Collaborator));
  if (collaboratorVector == NULL)
  {
    printf("Erro ao alocar memória.\n");
    free(participationVector);
    exit(0);
  }

  projectVector = (Project *)malloc(projectSize * sizeof(Project));
  if (projectVector == NULL)
  {
    printf("Erro ao alocar memória.\n");
    free(participationVector);
    free(collaboratorVector);
    exit(0);
  }

  participationCount = loadParticipations(&participationVector, &participationSize);
  collaboratorCount = loadCollaborators(&collaboratorVector, &collaboratorSize);
  projectCount = loadProjects(&projectVector, &projectSize);

  if (participationCount > 0)
  {
    bubbleSortParticipations(participationVector, participationCount);
  }
  if (collaboratorCount > 0)
  {
    bubbleSortCollaborators(collaboratorVector, collaboratorCount);
  }
  if (projectCount > 0)
  {
    bubbleSortProjects(projectVector, projectCount);
  }

  while (running)
  {
    printReportSubmenu();

    getCharInput(&option);
    printf("\n");

    switch (option)
    {
    case 'a':
      reportCollaboratorsOfProject(participationVector, participationCount, collaboratorVector, collaboratorCount, projectVector, projectCount);
      break;

    case 'b':
      reportProjectsOfCollaborator(participationVector, participationCount, collaboratorVector, collaboratorCount, projectVector, projectCount);
      break;

    case 'c':
      reportProjectsBetweenDates(projectVector, projectCount, participationVector, participationCount, collaboratorVector, collaboratorCount);
      break;

    case 'd':
      running = false;
      free(participationVector);
      free(collaboratorVector);
      free(projectVector);
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