# Sistema de Gestión de Pacientes en Hospital

## Descripción

Este sistema permite a los usuarios gestionar la atención de pacientes en un hospital. Los usuarios pueden registrar nuevos pacientes, asignar prioridades, ver la lista de espera ordenada por prioridades, atender al siguiente paciente mostrando sus datos y mostrar los pacientes con la prioridad pedida. Esta herramienta está diseñada para mejorar la eficiencia en la atención de los pacientes, asegurando que aquellos en situaciones críticas reciban atención lo más pronto posible.

## Cómo compilar y ejecutar

Dado que el sistema está diseñado para ser accesible y fácil de probar, recomendamos usar [Repl.it](http://repl.it/) para una rápida configuración y ejecución. Sigue estos pasos para comenzar:

1. Visita [Repl.it](https://repl.it/).
2. Crea una nueva cuenta o inicia sesión si ya tienes una.
3. Una vez en tu dashboard, selecciona "New Repl" y elige "Import from GitHub".
4. Pega la URL del repositorio: `https://github.com/YosoyelDario/Tarea-1-Tdas-Dario-Fuentes.git`.
5. [Repl.it](http://repl.it/) clonará el repositorio y preparará un entorno de ejecución.
6. En la pestaña "Configurate Repl", sección "Configure the Compile Command", escriba o pegue de preferencia el siguiente comando "gcc tdas/*.c main.c -Wno-unused-result -o main" y presione "done".
7. Presiona el botón "Run" para compilar y ejecutar la aplicación.
## Funcionalidades 

### Funcionando correctamente:


- Registrar pacientes con sus datos básicos y una prioridad inicial.
- Asignar o modificar la prioridad de los pacientes.
- Mostrar la lista de espera de pacientes, ordenada por prioridad y hora de registro.
- Atender al siguiente paciente, respetando el orden de prioridad y mostrando sus respectivos datos.
- Al ingresar un nivel de prioridad, muestra la lista de los pacientes que corresponden a ese nivel, ordenados en orden de llegada.

### Problemas conocidos:

- El buffer de entrada de la edad acepta hasta 4 caracteres incluyendo '\0'(fin de la cadena).
  Si se ingresa más de 4 caracteres, el comportamiento no esta definido y puede llevar a resultados no esperados.
  Un ejemplo seria, como que parte del numero ingresado se interprete como parte del siguiente campo, en este caso sintoma del paciente.
- Los datos del paciente deben ser ingresados en minúsculas o en mayúsculas, ya que sino el programa sufrira errores.
- Se pueden ingresar numeros en el buffer de entrada de la prioridad.
- El usuario debe ingresar los datos correctamentes tal y como se pide en el programa, si por ejemplo al registrar paciente se ingresa el nombre "Hery" (imaginando que el usuario se salta una letra por accidente), haria imposible luego buscar al paciente como Henry, el programa no lo detectaria.

### A mejorar:

- Implementar una interfaz de usuario más amigable.
- Permitir la edición de los datos de los pacientes en caso de algun error.
- Permitir la reasignacion de las prioridades de los pacientes cuando ya se ingreso su prioridad anteriormente.
- Implementar que luego de cierto tiempo en una opcion, si no se han ingresado datos, volver al menu principal.
- Mejorar la lectura de datos para aceptar errores del usuario.
- Implementar una validacion que al ingresar numeros al asignar prioridad, no lo permita.

## Ejemplo de uso:
### EL USUARIO NO SE EQUIVOCARA AL INGRESAR LOS DATOS DE LOS PACIENTES DURANTE LA EJECUCION DE TODO EL PROGRAMA.

#### Paso 1: Registrar un Nuevo Paciente

Se comienza registrando dos nuevos pacientes que acaban de llegar al hospital.
````
Opción seleccionada: 1) Registrar paciente
Ingrese el nombre del paciente : Michael Jackson
Ingrese la edad del paciente: 50
Ingrese el síntoma del paciente: Fractura en la pierna izquierda.

Opción seleccionada: 1) Registrar paciente
Ingrese el nombre del paciente : Henry Cavil
Ingrese la edad del paciente: 40
Ingrese el síntoma del paciente: Fatiga muscula severa.

````
El sistema registra a Michael Jackson y a Henry Cavil con una prioridad inicial "Bajo" y guarda la hora actual de registro. La prioridad inicial puede ser ajustada más tarde basada en una evaluación médica más detallada.

#### Paso 2: Asignar Prioridad a un Paciente

Tras una evaluación inicial, el médico determina que el estado del paciente Michael Jackson requiere atención prioritaria de nivel Alta, mientras que el estado del paciente Henry Cavil requiere atención prioritaria de nivel Media.
````
Opción seleccionada: 2) Asignar prioridad a paciente
Ingrese el nombre del paciente: Michael Jackson
Seleccione el nuevo nivel de prioridad (Alta, Media, Baja): Alta

Opción seleccionada: 2) Asignar prioridad a paciente
Ingrese el nombre del paciente: Henry Cavil
Seleccione el nuevo nivel de prioridad (Alta, Media, Baja): Media
````
El sistema actualiza la prioridad de Michael Jackson a "Alta", asegurando que será uno de los próximos pacientes en ser atendido, luego asigna la prioridad de Henry Cavil a "Media", asegurando que sera el proximo paciente en ser atendido luego de atender a Michael.

#### Paso 3: Ver la Lista de Espera

El usuario revisa la lista de espera para ver todos los pacientes y sus prioridades.
````
Opción seleccionada: 3) Mostrar lista de espera

Pacientes en espera : 

Nombre: Michael Jackson
Edad: 50
Sintoma del Paciente: Fractura en la pierna izquierda.
Prioridad del paciente: Alta
Hora de registro del paciente: Sun 21-04-2024 19:13:39

Nombre: Henry Cavil
Edad: 40
Sintoma del Paciente: fatiga muscular severa.
Prioridad del paciente: Media
Hora de registro del paciente: Sun 21-04-2024 19:30:54
````
(Notese que en el formato de la hora se muestra el dia de registro abreviado en ingles, el dia, mes y año en numeros, y luego finalmente la hora, minutos y segundos en el cual se registro al paciente)

Se muestra en la lista de espera los pacientes en orden de prioridad, en prioridad "Alta" a Michael Jackson, y finalmente en prioridad "Media" a Henry Cavil

#### Paso 4: Atender al Siguiente Paciente
Michael Jackson es llamado para ser atendido basándose en su prioridad.
````
Opción seleccionada: 4) Atender al siguiente paciente
Atendiendo al siguiente paciente.

Nombre: Michael Jackson
Edad: 50
Sintoma del Paciente: Fractura en la pierna izquierda.
Prioridad del paciente: Alta
Hora de registro del paciente: Sun 21-04-2024 19:13:39
````
El sistema muestra los datos del paciente que esta siendo atendido, muestra sus datos y luego lo elimina de la lista de espera.

#### Paso 5: Mostrar pacientes por prioridad
Se muestra los pacientes de prioridad Media.
````
Opción seleccionada: 5) Mostrar pacientes por prioridad
Ingrese el nivel de prioridad ('Alta', 'Media' o 'Baja') : Media

Pacientes con prioridad Media :
Nombre: Henry Cavil
Edad: 40
Sintoma del Paciente: fatiga muscular severa.
Hora de registro del paciente: Sun 21-04-2024 19:30:54
````
El sistema muestra los pacientes por prioridad, en este caso solamente un paciente.

#### Paso 6: Atender finalmente al ultimo Paciente.
Henry Cavil es llamado para ser atendido basándose en su prioridad, luego de que anteriormente se atendio al paciente Michael Jackson.
````
Opción seleccionada: 4) Atender al siguiente paciente
Atendiendo al siguiente paciente.

Nombre: Henry Cavil
Edad: 40
Sintoma del Paciente: fatiga muscular severa.
Prioridad del paciente: Media
Hora de registro del paciente: Sun 21-04-2024 19:30:54
````
El sistema muestra los datos del paciente que esta siendo atendido, muestra sus datos y luego lo elimina de la lista de espera.

#### Paso 7: Salir
Al momento de querer dejar de usar el programa, el usuario selecciona la opción de salir.
````
Opción seleccionada: 6) Salir
Saliendo del sistema de gestión hospitalaria...
````
(Se sabe que no habian más pacientes por lo que se sale del programa, pero en caso de no saberlos o para verificar, se puede implementar otro paso antes del paso 7, que seria Seleccionar la opcion 3 y mostrar la lista de espera por orden de prioridad.)

