# Trabajo Practico N° 5 - Sistemas de Computacion - Character Device Drivers

## Integrantes 

* Pary Joaquin
* Colque Santiago
* Angeloff Jorge

## Objetivos

El objetivo de este Trabajo Practico es diseñar y construir un `CDD` (Character Device Driver) que permita sensar dos señales externas con un periodo de un segundo. Posteriormente, se desarrollara una aplicacion a nivel de usuario que leera una de las dos señales y la graficara en funcion del tiempo. La aplicacion tambien debe tener la capacidad de indicar al `CDD` cual de las dos señales debe leer. Las correcciones de escalas de las mediciones si son necesarias, se realizaran a nivel de usuario. Los graficos de la señal deben mostrar el tipo de señal que se esta sensando, con unidades en las abcisas y tiempo en las ordenada. Ademas, al cambiar de señal, el grafico debe reiniciarse y ajustarse a la nueva medicion.

## Conceptos

### Device Driver

Un `Device Driver` (controlador de dispositivo) es un software que permite al sistema operativo comunicarse con el hardware de un dispositivo. Actúa como un traductor entre el sistema operativo y el hardware, gestionando las comunicaciones y facilitando la ejecución de las instrucciones entre ellos.

### Device Controller
Un device controller es un componente de hardware que gestiona la comunicación y control de un dispositivo periférico, actuando como intermediario entre el dispositivo y el sistema operativo. Traduce señales eléctricas del dispositivo en datos comprensibles para la CPU y viceversa, gestionando la transmisión de datos y las interrupciones generadas por el dispositivo para notificar eventos a la CPU.

### Bus Controller
Un bus controller es un componente que gestiona la comunicación entre la CPU y varios dispositivos conectados a un bus del sistema. Coordina el flujo de datos en el bus, gestiona las solicitudes de acceso al bus para evitar conflictos y facilita la comunicación entre la CPU, la memoria y los dispositivos periféricos, asegurando una transferencia de datos ordenada y eficiente.

### Conexión entre Device Controllers y Bus Controllers
Los device controllers se conectan al bus del sistema y se comunican con sus respectivos dispositivos periféricos. Los bus controllers gestionan las solicitudes de la CPU para interactuar con estos dispositivos a través del bus, coordinando el acceso y manejo de interrupciones para asegurar una operación eficiente y sin conflictos entre los diferentes componentes del sistema.

![DevBus](img/device_bus.png)

## Desarrollo

El Trabajo requiere el uso de una `Raspberry Pi`, por lo que se detallara la configuracion del entorno para trabajar con el dispositivo.

### Configuracion de SSH

Se puede configurar la `Rasberry Pi` para poder conectarse mediante `SSH` para evitar el uso de un monitor y tambien para permitir que otras computadoras puedan usar el dispositivo al mismo tiempo.

Para habilitar se debe usar el siguente comando:

```bash
sudo raspi-config
```

![SSH](/img/ssh1.png)

>Interfacing Options >>> SSH >>> Yes 

Seguido de un `sudo reboot` para asegurarse de aplicar los cambios.

Por ultimo, se podra conectar a la `Raspi`

```bash
ssh sistcomp@192.178.1.57
```
![SSHLocal](/img/ssh_local.png)

### SSH Fuera del Area Local

Tambien se puede configurar para poder acceder desde otra computadora que este fuera del `Area Local`.

Para ello, se debe entrar a la configuracion del `Router` y abrir un puerto, por ejemplo el puerto `22`.

![SSH2](/img/ssh2.png)

Entonces obteniendo la `IP` publica se puede conectar de la misma manera:

```bash
ssh sistcomp@xxx.xxx.x.xx
```

