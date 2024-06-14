# Trabajo Practico N° 5 - Sistemas de Computacion - Character Device Drivers

## Integrantes 

* Pary Joaquin
* Colque Santiago
* Angeloff Jorge

## Objetivos

El objetivo de este Trabajo Practico es diseñar y construir un `CDD` (Character Device Driver) que permita sensar dos señales externas con un periodo de un segundo. Posteriormente, se desarrollara una aplicacion a nivel de usuario que leera una de las dos señales y la graficara en funcion del tiempo. La aplicacion tambien debe tener la capacidad de indicar al `CDD` cual de las dos señales debe leer. Las correcciones de escalas de las mediciones si son necesarias, se realizaran a nivel de usuario. Los graficos de la señal deben mostrar el tipo de señal que se esta sensando, con unidades en las abcisas y tiempo en las ordenada. Ademas, al cambiar de señal, el grafico debe reiniciarse y ajustarse a la nueva medicion.

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
