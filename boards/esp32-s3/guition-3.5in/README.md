# GUITION JC3248W535C de 3,5 pulgadas — ESP32-S3

Firmware de monitorización informativa de glucosa para la placa **GUITION JC3248W535C**, con microcontrolador ESP32-S3 y pantalla táctil capacitiva de 3,5 pulgadas (320 × 480). La placa utiliza el controlador de pantalla AXS15231B por QSPI, 8 MB de PSRAM OPI y 16 MB de memoria flash.

> **Aviso médico:** no es un dispositivo médico ni debe utilizarse para tomar decisiones de tratamiento o dosificación. Consulta el [aviso médico y la exención de responsabilidad](../../../DISCLAIMER.md).

## Archivos principales

| Archivo | Función |
|---|---|
| `CGM_Dashboard.ino` | Firmware principal: Wi-Fi, consultas a Nightscout e interfaz |
| `secrets.example.h` | Plantilla de credenciales y configuración |
| `version.h` | Nombre y versión del firmware |
| `lv_conf.h` | Configuración de LVGL |
| `lv_port.*`, `esp_bsp.*`, `display.h` | Inicialización de placa y pantalla |
| `esp_lcd_axs15231b.*` | Controlador del panel |
| `esp_lcd_touch.*` | Controlador táctil |
| `partitions.csv` | Tabla de particiones de la memoria flash |

## 1. Preparar la configuración

Copia `secrets.example.h` y renombra la copia como `secrets.h`. Edita el nuevo archivo y completa los valores que aparecen en la plantilla, como mínimo los correspondientes a:

- Red Wi-Fi: `WIFI_SSID` y `WIFI_PASS`.
- Instancia de Nightscout y el método de autenticación indicado por la plantilla.
- Contraseña OTA, si vas a utilizar la actualización inalámbrica.
- Parámetros de MQTT/Home Assistant, si los necesitas.

**No subas `secrets.h` a GitHub ni compartas su contenido.** El archivo está excluido del control de versiones. Si se filtra una contraseña o un token, revócalo o cámbialo.

## 2. Instalar las herramientas

1. Instala [Arduino IDE](https://www.arduino.cc/en/software).
2. Instala el paquete de placas [Arduino-ESP32](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html).
3. Instala las bibliotecas **ArduinoJson**, **JPEGDEC** y **LVGL 8.4.x**.
4. Copia `lv_conf.h` junto a la carpeta de la biblioteca LVGL, tal como requiere la configuración de este proyecto.

## 3. Compilar y cargar

En las opciones de la placa selecciona:

- **Placa:** `ESP32S3 Dev Module`.
- **PSRAM:** `OPI PSRAM` / `OPI`, según cómo lo muestre tu versión del paquete ESP32.
- **Flash:** `16 MB`.
- Usa el puerto serie correspondiente a la placa y un cable USB que permita transferencia de datos.

Abre `CGM_Dashboard.ino`, compila y carga el firmware. Tras el primer arranque, utiliza la pantalla de configuración del dispositivo para revisar los ajustes de Nightscout.

## 4. Comprobaciones iniciales

- El dispositivo arranca y se conecta a la red Wi-Fi configurada.
- La URL y la autenticación de Nightscout son correctas y se muestran datos recientes.
- La fecha, la hora, el valor de glucosa y la tendencia se visualizan correctamente.
- Si usas MQTT, comprueba que Home Assistant recibe los sensores.
- Antes de utilizar OTA, confirma que la configuración de red y la contraseña OTA son correctas.

Si algo falla, registra el mensaje de error y la versión del firmware, pero elimina de los registros cualquier contraseña, token o dato privado antes de compartirlos.

## Versión

La versión de firmware preparada es **1.0.0**. La etiqueta `v1.0.0` y su publicación en [GitHub Releases](https://github.com/mapoloco/esp32-cgm/releases) están pendientes. Consulta el [registro de cambios](../../../CHANGELOG.md) para conocer los cambios incluidos.

