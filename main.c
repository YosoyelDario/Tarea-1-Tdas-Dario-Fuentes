#include "tdas/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

//Estructura paciente para almacenar la información de cada paciente.
typedef struct{  
  char nombreP[100]; //Se almacena el nombre del paciente.
  int edadP; //Se almacena la edad del paciente.
  char sintomaP[300]; //Se almacena el sintoma del paciente.
  char prioridadP[10]; //Se almacena la prioridad del paciente.
  char horaRegistroP[80]; // Hora de registro del paciente por medio de la funcion time.
}Paciente;

//Estructura que contiene listas de pacientes con diferentes prioridades(Alta,Media y Baja).
typedef struct{ 
  List *listaPrioBaja ; //Lista de pacientes con prioridad baja.
  List *listaPrioMedia ; //Lista de pacientes con prioridad media.
  List *listaPrioAlta; //Lista de pacientes con prioridad alta.
}listaAllPrio;

//Funcion para inicializar las listas de pacientes
listaAllPrio *inicializarListas(){ 
  listaAllPrio *listTodas = (listaAllPrio *)malloc(sizeof(listaAllPrio)); //Asignar memoria a la lista de todas las prioridades.
  listTodas->listaPrioBaja = list_create();  
  listTodas->listaPrioMedia = list_create();
  listTodas->listaPrioAlta = list_create();
  return listTodas; //Retorna la lista con todas las listas de prioridades.
}
// Función para limpiar la pantalla
void limpiarPantalla() { system("clear"); }

void presioneTeclaParaContinuar() {
  puts("Presione una tecla para continuar...");
  getchar(); // Consume el '\n' del buffer de entrada
  getchar(); // Espera a que el usuario presione una tecla
}
// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Sistema de Gestión Hospitalaria");
  puts("========================================");

  puts("1) Registrar paciente");
  puts("2) Asignar prioridad a paciente");
  puts("3) Mostrar lista de espera");
  puts("4) Atender al siguiente paciente");
  puts("5) Mostrar pacientes por prioridad");
  puts("6) Salir");
}

//Funcion para registrar la hora en zona horaria chile.
void obtenerHoraActual(char *horaActual)
{
  //Declaracion
  time_t tiempoActual; //Variable para almacenar el tiempo actual en segundos.
  struct tm *horaLocal; //Puntero para a un struct para almacenar la hora local.
  char aux[80]; //Arreglo para almacenar la hora formateada

  //Obtencion del tiempo actual en UTC
  tiempoActual = time(NULL);
  //conversion de UTC a zona horaria de chile GMT-4
  horaLocal = gmtime(&tiempoActual);
  
  horaLocal->tm_hour -= 4; //ajuste de la hora local para la zona horaria de Chile.
  mktime(horaLocal); //Conversion de la hora local a un tiempo valido.

  strftime(aux, sizeof(aux), "%a %d-%m-%Y %H:%M:%S", horaLocal); //Formateo de la hora y almacenamiento en el arreglo auxiliar.
  strcpy(horaActual, aux);
}

//Funcion para comprobar y registrar edad del paciente.
int comprobarEdad()
{
  char entrada[4]; //Maximo 3 cifras de edad y espacio para el \0
  scanf(" %3s", entrada); // Leer como cadena
  getchar();
  // Verificar si la cadena contiene solo dígitos
  for (int i = 0; i < strlen(entrada); i++)
  {
    if (!isdigit(entrada[i]))
    {
      printf("No se aceptan letras o numeros negativos, porfavor ingrese una edad valida : ");
      return comprobarEdad();
    } // No es valido
  }
  // Convertir la cadena a un entero y verificar si es mayor que cero
  int edad = strtol(entrada, NULL, 10);
  if (edad == 0)
  {
    printf("Porfavor ingrese una edad valida : ");
    return comprobarEdad();
  }
  //STRTULL()
  return edad;
}

//Funcion para comparar las horas de registro de 2 pacientes
int compararHoras(void *pivote, void *item) 
{
  Paciente *paciente1 = (Paciente*)pivote;
  Paciente *paciente2 = (Paciente*)item;

  if (paciente1 ->horaRegistroP  < paciente2 ->horaRegistroP)return 1; //Se haze el switch si el paciente 1 debe ir despues del segundo.
  return 0;
}

//Funcion para validar el nombre ingresado por un usuario.
char *validarNombre()
{
  char nombreAux[100];
  fscanf(stdin," %[^\n]s", nombreAux);
  getchar();
  
  int talla = strlen(nombreAux);
  for(int i = 0; i < talla; i++)
  {
    //Verifica que el nombre no contenga numeros, y  que solo contenga letras o espacios
    if(!isalpha(nombreAux[i]) && nombreAux[i] != ' ') 
    {
      printf("El nombre no puede contener numeros, ingrese un nombre valido a continuacion :");
      return validarNombre();
    }
  }
  char *nombreValido = (char*)malloc(strlen(nombreAux)+1);
  strcpy(nombreValido, nombreAux);
  return nombreValido; //Retorna el nombre valido.
}

//Funcion que busca un paciente por su nombre en las tres listas de prioridades.
Paciente* buscarPaciente(listaAllPrio *lista, char *nombre) //Retorna el paciente si lo encuentra, en caso contrario, retorna NULL.
{
  Paciente* auxPaciente = list_first(lista->listaPrioBaja);

  while(auxPaciente != NULL)
  {
    if(strcmp(auxPaciente->nombreP,nombre) == 0)
    {
      return auxPaciente;
    }
    auxPaciente = list_next(lista->listaPrioBaja);
  }

  auxPaciente = list_first(lista->listaPrioMedia);
  while(auxPaciente != NULL)
  {
    if(strcmp(auxPaciente->nombreP,nombre) == 0)
    {
      return auxPaciente;
    }
    auxPaciente = list_next(lista->listaPrioMedia);
  }

  auxPaciente = list_first(lista->listaPrioAlta);
  while(auxPaciente != NULL)
  {
    if(strcmp(auxPaciente->nombreP,nombre) == 0)
    {
      return auxPaciente;
    }
    auxPaciente = list_next(lista->listaPrioAlta);
  }
  return NULL;
}

//Funcion que permite al usuario registrar un paciente.
void registrarPaciente(listaAllPrio *pacientes)
{
  Paciente* newPaciente = malloc(sizeof(Paciente));
  //if (newPaciente == NULL)exit(EXIT_FAILURE);

  printf("A continuacion, porfavor ingrese los datos del paciente\n");

  printf("Ingrese el nombre del paciente : ");
  char *nombreAux;
  nombreAux = validarNombre(); 

  Paciente *pacienteEncontrado = buscarPaciente(pacientes, nombreAux); //Verifica si el paciente ya existe en las listas.
  if(pacienteEncontrado != NULL)
  {
    printf("El paciente ya se encuentra registrado, porfavor ingrese otro nombre : ");
    free(nombreAux);
    return;
  }
  
  strcpy(newPaciente->nombreP, nombreAux);
  free(nombreAux);

  printf("Ingrese la edad del paciente : ");
  int edadAux = comprobarEdad();
  newPaciente->edadP = edadAux;

  printf("Ingrese el sintoma del paciente : ");
  fscanf(stdin, " %[^\n]s", newPaciente->sintomaP);
  getchar();

  strcpy(newPaciente->prioridadP, "Baja"); //Asigna automaticamente prioridad baja al paciente.
  char auxHrActual[80];
  obtenerHoraActual(auxHrActual);
  strcpy(newPaciente->horaRegistroP, auxHrActual);

  list_pushBack(pacientes->listaPrioBaja, newPaciente);
  printf("El paciente fue registrado con exito. \n");
}

//Esta funcion busca un paciente en las tres listas, si lo encuentra lo elimina.
void eliminarPaciente(listaAllPrio *pacientes, char *nombre)
{
  Paciente *auxPaciente = list_first(pacientes->listaPrioBaja);
  while(auxPaciente != NULL)
  {
    if(strcmp(auxPaciente->nombreP,nombre) == 0)
    {
      list_popCurrent(pacientes->listaPrioBaja);
      return;
    }
    auxPaciente = list_next(pacientes->listaPrioBaja);
  }

  auxPaciente = list_first(pacientes->listaPrioMedia);
  while(auxPaciente != NULL)
  {
    if(strcmp(auxPaciente->nombreP,nombre) == 0)
    {
      list_popCurrent(pacientes->listaPrioMedia);
      return;
    }
    auxPaciente = list_next(pacientes->listaPrioMedia);
  }

  auxPaciente = list_first(pacientes->listaPrioAlta);
  while(auxPaciente != NULL)
  {
    if(strcmp(auxPaciente->nombreP,nombre) == 0)
    {
      list_popCurrent(pacientes->listaPrioAlta);
      return;
    }
    auxPaciente = list_next(pacientes->listaPrioAlta);
  }
}

//Esta funcion permite asignar prioridad a un paciente ya existente en la lista.
void asignarPrioridad(listaAllPrio *pacientes)
{
  char nombreAux[100];
  char newPrioridad[10];
  printf("Ingrese el nombre del paciente que desea asignarle una prioridad : ");
  fscanf(stdin, " %[^\n]s", nombreAux);
  getchar();

  Paciente *pacienteAux = buscarPaciente(pacientes, nombreAux); //Busca al paciente en las tres listas.
  if(pacienteAux == NULL)
  {
    printf("No se encontro el siguiente paciente en la lista : %s, porfavor intentelo de nuevo.\n",nombreAux);
    return;
  }

  printf("Ingrese la nueva prioridad del paciente ('Baja', 'Media' o 'Alta) : ");
  fscanf(stdin," %[^\n]s", newPrioridad);
  getchar();

  if(strcmp(newPrioridad,"Media") == 0)
  {
    strcpy(pacienteAux->prioridadP, "Media");
    eliminarPaciente(pacientes, pacienteAux->nombreP); 
    list_sortedInsert(pacientes->listaPrioMedia, pacienteAux, compararHoras); //Insertar paciente en la lista correspondiente ordenado por hora de registro.
  }
  if(strcmp(newPrioridad,"Alta") == 0)
  {
    strcpy(pacienteAux->prioridadP,"Alta");
    eliminarPaciente(pacientes, pacienteAux->nombreP);
    list_sortedInsert(pacientes->listaPrioAlta, pacienteAux, compararHoras); //Insertar paciente en la lista correspondiente ordenado por hora de registro.
  }
  printf("Se asigno correctamente la prioridad al paciente : %s\n", nombreAux);
}

void mostrarDatosP(Paciente *dato) //Muestra los datos de un paciente.
{
  printf("Nombre: %s\n", dato->nombreP);
  printf("Edad: %d\n", dato-> edadP);
  printf("Sintoma del Paciente: %s\n", dato-> sintomaP);
  printf("Prioridad del paciente: %s\n", dato->prioridadP);
  printf("Hora de registro del paciente: %s\n\n", dato->horaRegistroP);
}
void mostrarListaPacientes(listaAllPrio *pacientes) //Muestra los pacientes en espera con sus respectivos datos, de prioridad "Alta" a "Baja".
{
  limpiarPantalla();
  // Mostrar pacientes en la cola de espera
  printf("Pacientes en espera : \n\n");
  //Prioridad Alta
  Paciente* auxPaciente = list_first(pacientes->listaPrioAlta);
  while(auxPaciente != NULL)
  {
    mostrarDatosP(auxPaciente);
    auxPaciente = list_next(pacientes->listaPrioAlta);
  }
  //Prioridad Media
  auxPaciente = list_first(pacientes->listaPrioMedia);
  while(auxPaciente != NULL)
  {
    mostrarDatosP(auxPaciente);
    auxPaciente = list_next(pacientes->listaPrioMedia);
  }
  //Prioridad Baja
  auxPaciente = list_first(pacientes->listaPrioBaja);
  while(auxPaciente != NULL)
  {
    mostrarDatosP(auxPaciente);
    auxPaciente = list_next(pacientes->listaPrioBaja);
  }
}

void atenderSigPaciente(listaAllPrio *pacientes) //Funcion que muestra los datos del paciente a atender y lo elimina de la lista.
{
  //Desde prioridad "Alta" a "Baja"
  Paciente *auxPaciente = list_first(pacientes->listaPrioAlta);
  printf("Atendiendo al siguiente paciente. \n\n");
  if(auxPaciente != NULL)
  {
    list_popCurrent(pacientes->listaPrioAlta);
    mostrarDatosP(auxPaciente);
    return;
  }
  auxPaciente = list_first(pacientes->listaPrioMedia);
  if(auxPaciente != NULL)
  {
    list_popCurrent(pacientes->listaPrioMedia);
    mostrarDatosP(auxPaciente);
    return;
  }
  auxPaciente = list_first(pacientes->listaPrioBaja);
  if(auxPaciente != NULL)
  {
    list_popCurrent(pacientes->listaPrioBaja);
    mostrarDatosP(auxPaciente);
    return;
  }
  printf("No hay pacientes en espera.\n");
}

void mostrarDatosSinPrio(Paciente *dato) //Funcion para mostrar los datos de un paciente sin su prioridad.
{
  printf("Nombre: %s\n", dato->nombreP);
  printf("Edad: %d\n", dato-> edadP);
  printf("Sintoma del Paciente: %s\n", dato-> sintomaP);
  printf("Hora de registro del paciente: %s\n\n", dato->horaRegistroP);
}
void mostrarPacientesPorPrio(listaAllPrio *pacientes) //Muestra los pacientes en espera con sus respectivos datos, de una prioridad en especifica.
{
  limpiarPantalla();

  char auxPrio[10];
  printf("Ingrese el nivel de prioridad ('Alta', 'Media' o 'Baja') : ");
  fscanf(stdin," %[^\n]s", auxPrio);

  List *listaAux = NULL;
  if(strcmp(auxPrio,"Alta") == 0)
  {
    listaAux = pacientes->listaPrioAlta;
  }
  else if(strcmp(auxPrio,"Media") == 0)
  {
    listaAux = pacientes->listaPrioMedia;
  }
  else if(strcmp(auxPrio,"Baja") == 0)
  {
    listaAux = pacientes->listaPrioBaja;
  }
  else{
    printf("Nivel de prioridad no valido.\n");
    return;
  }

  if(listaAux == NULL)
  {
    printf("No hay pacientes en la lista de prioridad %s.\n", auxPrio);
  }
  else{
    printf("\nPacientes con prioridad %s :\n", auxPrio);
    Paciente *auxPaciente = list_first(listaAux);
    while(auxPaciente != NULL)
    {
      mostrarDatosSinPrio(auxPaciente);
      auxPaciente = list_next(listaAux);
    }
  }
}

int main() //Programa principal.
{
  char opcion;
  listaAllPrio *listaP = inicializarListas(); //Lista para gestionar los pacientes.

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el
                           // newline anterior

    switch (opcion) {
    case '1':
      registrarPaciente(listaP);
      break;
    case '2':
      asignarPrioridad(listaP);
      break;
    case '3':
      mostrarListaPacientes(listaP);
      break;
    case '4':
      atenderSigPaciente(listaP);
      break;
    case '5':
      mostrarPacientesPorPrio(listaP);
      break;
    case '6':
      puts("Saliendo del sistema de gestión hospitalaria...");
      break;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '6');

  // Liberar recursos
  list_clean(listaP->listaPrioBaja);
  list_clean(listaP->listaPrioMedia);
  list_clean(listaP->listaPrioAlta);
  free(listaP);

  return 0;
}