# Flipper Zero 101

## Instalación

El requisito mínimo es contar con Python 3.8 instalado

Para instalar [UFBT](https://github.com/flipperdevices/flipperzero-ufbt) debe ejecutar el siguiente comando:

```
pip install --upgrade ufbt
```

## Pasos para crear una aplicación

1. Crear proyecto:

```
ufbt create APPID=id_aplicación
```

2. Configurar vscode:

```
ufbt vscode_dist
```

3. Compilar y ejecutar:

```
ufbt launch
```

4. Ver bitácoras:

```
ufbt cli
>:log
```

## Carpetas

- new-app: Tiene la aplicación básica ni bien se crea
- hello-world: Tiene los diferentes ejemplos mostrados
- videos: Tiene los videos de cada ejemplo.

## Hello-World!

### Bitácoras

#### app_log_1

Aplicación mínima con tres mensajes de información.

#### app_log_2

Muestra tres tipos de bitácoras: información, alerta y excepción.

Se establecen 2 definiciones, una para el nombre del TAG y otra para desactivar las bitácoras.

### Notificaciones

#### app_notification_1

Muestra como manipular el vibrador y el led, de a una notificación por vez.

### app_notification_2

Mismo ejemplo que el anterior pero estableciendo secuencia de notificaciones.

### GPIO

#### app_gpio

Muestra como encender y apagar un led conectado al pin C7.

### Infrarrojo

#### app_if

Desde la aplicación IR incluida en el Flipper, se obtiene el archivo de configuración de un control remoto.

El archivo laser.ir contiene esa captura y este ejemplo muestra como enviar esos códigos.

### SubGHz

#### app_rf

Muestra como obtener la fuerza de señal capturada desde el módulo RF.

### UI

#### app_viewport_1

Aplicación mínima para mostrar contenido en pantalla, aunque esta aplicación no hace nada más que escribir algunas bitácoras.

- context_alloc obtendrá los recursos del sistema.
- draw_callback es una función que el sistema operativo llamará para informar a la aplicación que debe dibujar el contenido en la pantalla.
- context_free liberará los recursos solicitados.

#### app_viewport_2

Dibuja tres líneas de texto en pantalla con dos fuentes diferentes, FontPrimary y FontSecundary. Las funciones canvas_set_font deben ser llamadas previamente a canvas_draw_str, que es quien dibuja el texto.

canvas_width y canvas_height informan el ancho y alto disponible en pixel

#### app_viewport_3

A la aplicación anterior se agrega soporte para manejar los eventos de los botones. Este soporte se realiza por medio de input_callback, que es una función que el sistema operativo llamará para informar que se presionó un botón.

En este ejemplo se saldrá de la aplicación cuando se haga una presión larga con el botón atrás.

A diferencia del anterior, se agrega una función "run" que es quien obtiene los mensajes del sistema informando las teclas presionadas y cuando detecta la combinación elegida, la aplicación termina. furi_message_queue_get esperará infinitamente (por el parámetro FuriWaitForever) hasta un evento de entrada.

#### app_viewport_4

En este ejemplo se agrega un contador en segundo plano y su valor se mostrará en pantalla. 

Se destacan dos hilos de ejecución, el primario (función run) que será el encargado de determinar cuando la aplicación debe terminar a pedido del usuario y el secundario (job_callback) que es el hilo donde se realizan las tareas de la aplicación, en este caso sumar 1 al contador y esperar un segundo.

Con furi_thread_flags_wait se determina si el hilo principal envió la señal de terminación, caso contrario, su resultado será FuriFlagErrorTimeout e indica que el hilo principal no solicitó su detención.

### Escenas

#### app_scene

En este ejemplo minimalista se dibuja un menú con dos opciones. 

A destacar, app_event_helper y app_config permiten instanciar en forma automatizada los siguientes eventos en el administrador de escenas:

- on_enter: se llama cuando se navega a la escena
- on_event: se llama cuando hay un evento del sistema
- on_exit: se llama cuando se cambia de escena y se utiliza para liberar recursos

Debe agregar una línea por cada escena disponible. Por ejemplo, para la primera opción, quedaría app_scene_menu_on_enter, app_scene_menu_on_event y app_scene_menu_on_exit.

```
ADD_SCENE(app, menu, Menu)
ADD_SCENE(app, demo1, Demo1)
ADD_SCENE(app, demo2, Demo2)
```
