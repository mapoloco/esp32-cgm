# ESP32-CGM — monitor de glucosa para ESP32

[![Licencia MIT](https://img.shields.io/badge/licencia-MIT-yellow.svg)](LICENSE)
[![Plataforma ESP32](https://img.shields.io/badge/plataforma-ESP32-blue.svg)](#hardware-compatible)
[![Versión](https://img.shields.io/badge/versión-1.0.0-informational.svg)](CHANGELOG.md)

Firmware de código abierto que convierte una pantalla táctil compatible con ESP32 en un monitor informativo de glucosa. Obtiene los datos de una instancia de [Nightscout](https://nightscout.github.io/) y muestra el valor actual, la tendencia y el historial reciente.

> **Aviso importante:** este proyecto no es un dispositivo médico y no debe utilizarse para tomar decisiones de tratamiento o dosificación de insulina. Se ofrece sin garantía y bajo la responsabilidad de quien lo utiliza. Lee el [aviso médico y la exención de responsabilidad](DISCLAIMER.md).

## Hardware compatible

| Placa | Microcontrolador | Pantalla | Estado |
|---|---|---|---|
| **GUITION JC3248W535C** | ESP32-S3 | Táctil capacitiva de 3,5 pulgadas, 320 × 480 | Compatible |
| GUITION de 10,1 pulgadas | ESP32-P4 + C6 para Wi-Fi | 10,1 pulgadas | En desarrollo; no incluida en esta versión |

Esta versión estable está preparada para la **GUITION JC3248W535C de 3,5 pulgadas con ESP32-S3**. No des por compatible otra placa solo porque también utilice ESP32.

## Funciones principales

- Consulta de datos de glucosa desde Nightscout.
- Valor actual, flecha de tendencia e historial reciente.
- Interfaz con opciones de visualización y configuración.
- Configuración de red y de Nightscout desde el dispositivo.
- Integración MQTT con Home Assistant.
- Actualización del firmware por OTA y mecanismos de recuperación compatibles con esta placa.
- Interfaz en español, incluidos caracteres acentuados y la letra ñ.

Consulta el [registro de cambios](CHANGELOG.md) para conocer los cambios de cada versión.

## Requisitos

- Ordenador con [Arduino IDE](https://www.arduino.cc/en/software).
- Paquete de placas [Arduino-ESP32](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html).
- Bibliotecas **ArduinoJson**, **JPEGDEC** y **LVGL 8.4.x**.
- Cable USB de datos para la primera instalación.
- Acceso a una instancia de Nightscout y sus datos de conexión.

## Instalación rápida

1. Descarga o clona este repositorio.
2. Abre la carpeta `boards/esp32-s3/guition-3.5in/`.
3. Copia `secrets.example.h` como `secrets.h` y completa los datos de tu Wi-Fi y Nightscout. Si vas a usar MQTT/OTA, configura también los campos correspondientes de acuerdo con la plantilla.
4. Instala las bibliotecas indicadas en los requisitos. Copia `lv_conf.h` junto a la carpeta de la biblioteca LVGL, según las instrucciones de la placa.
5. En Arduino IDE, abre `CGM_Dashboard.ino` y selecciona **ESP32S3 Dev Module**. Configura la PSRAM como **OPI** y la memoria flash como **16 MB**.
6. Compila y carga el firmware por USB. Tras el primer arranque, revisa la configuración de Nightscout en el dispositivo.

La guía específica de la placa contiene el detalle de archivos y configuración: [README de la GUITION JC3248W535C](boards/esp32-s3/guition-3.5in/README.md).

### Protección de credenciales

- **No publiques ni compartas tu `secrets.h`**: contiene credenciales privadas y está excluido del control de versiones mediante `.gitignore`.
- No incluyas tokens, contraseñas ni URL privadas en capturas de pantalla, incidencias o registros públicos.
- Si una credencial se publica por accidente, cámbiala; borrarla del último commit no garantiza que desaparezca del historial.

## Estructura del repositorio

```text
boards/esp32-s3/guition-3.5in/   Firmware y controladores de la placa de 3,5 pulgadas
docs/                            Referencias y documentación de hardware
CHANGELOG.md                     Historial de cambios en castellano
DISCLAIMER.md                    Aviso médico y exención de responsabilidad
secrets.example.h                Plantilla de configuración (sin credenciales reales)
```

## Versiones y actualizaciones

El proyecto utiliza [Versionado Semántico](https://semver.org/lang/es/). La versión de firmware preparada es **1.0.0**. La etiqueta `v1.0.0` y su publicación en [GitHub Releases](https://github.com/mapoloco/esp32-cgm/releases) están pendientes. Consulta el [registro de cambios](CHANGELOG.md) para ver los cambios incluidos.

## Ayuda y contribuciones

Antes de informar de un problema, indica el modelo exacto de la placa, la versión del firmware y los pasos para reproducirlo. **No adjuntes credenciales ni secretos.**

- [Contribuir al proyecto](CONTRIBUTING.md)
- [Política de seguridad](SECURITY.md)
- [Aviso médico](DISCLAIMER.md)

## Licencia

Este proyecto se distribuye bajo la licencia [MIT](LICENSE). Consulta el archivo de licencia para conocer sus condiciones.
