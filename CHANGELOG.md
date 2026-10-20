# Registro de cambios

Aquí se documentan los cambios importantes de este proyecto. El formato se basa en
[Keep a Changelog](https://keepachangelog.com/en/1.1.0/) y el proyecto sigue
[Versionado Semántico](https://semver.org/lang/es/).

## [Sin publicar]

### Añadido
- **Panel Big Glucose:** nueva opción de diseño desde la configuración web, con glucosa destacada, flecha de tendencia, variación, gráfico inferior y barra de actualización de 10 segundos.
- **Inversión de colores con el sol:** el mismo panel alterna entre fondo verde `#35DE84` con elementos negros y fondo negro con elementos verdes y claros.
- Se conservan los umbrales de glucosa crítica y los avisos `LOW!` / `HIGH!` ya implementados.

### Pendiente de validación
- La nueva revisión del firmware está publicada, pero todavía no se ha confirmado una compilación completa ni una prueba física en la GUITION JC3248W535C.

## [1.0.0-rc3.1] - 2026-10-19

Actualización incremental sobre la versión anterior **1.0.0-rc3**, preparada para este fork y la **GUITION JC3248W535C con ESP32-S3**. La compilación y el funcionamiento en el hardware objetivo han sido validados por el mantenedor. Esta publicación conserva la numeración de versiones preliminares; no es una versión estable 1.0.0.

### Añadido
- **Diseños de panel seleccionables:** se puede elegir y guardar entre el panel original y una vista minimalista centrada en la glucosa, con un gráfico compacto del historial.
- **Selector de idioma en la configuración web:** permite elegir entre español e inglés y conserva la selección.
- **Información más clara al configurar el Wi-Fi:** muestra el nombre del punto de acceso de configuración y su dirección, e indica expresamente que la red de configuración no requiere contraseña.
- **Fecha en el diseño minimalista:** muestra el año con dos cifras.
- **Interfaz en castellano:** caracteres acentuados, letra ñ, etiquetas y opciones en español.

### Cambiado
- **Persistencia de la configuración:** el diseño del panel y el idioma de la interfaz web se conservan después de reiniciar el dispositivo.
- Se ha eliminado la generación de archivos de imagen de diagnóstico que ya no forman parte del firmware.
- **Documentación:** README principal, guía específica de la placa y registro de cambios en castellano.

### Seguridad y mantenimiento
- Se mantienen las protecciones de credenciales: `secrets.h` debe permanecer local y no debe publicarse.
- Se conserva el historial de cambios anteriores de la línea 1.0.0-rc.

## Versiones anteriores

## [1.0.0-rc3] - 2026-08-04

### Seguridad
- **El transporte de OTA ahora valida certificados fijados.** Antes, la descarga del manifiesto de actualización y del firmware omitía la verificación TLS, por lo que alguien capaz de interceptar el tráfico podía enviar al panel una actualización maliciosa, con la posibilidad de ejecutar código. Ambas descargas validan ahora la cadena de certificados mediante un conjunto reducido de autoridades raíz a las que encadenan los servidores de actualización (Let's Encrypt, Sectigo/USERTrust y una familia anterior como protección ante rotaciones). Se sincroniza el reloj mediante SNTP antes del primer intercambio: si el reloj no está configurado, se rechazan los certificados; si falla la sincronización, se omite la comprobación en lugar de rebajar la conexión a TLS sin verificar. Las consultas de glucosa a los servidores Nightscout/Dexcom configurados por el usuario no han cambiado.

### Cambiado
- El sensor de Home Assistant ahora se etiqueta como **GMI**. La expresión «A1C estimada» dejó de utilizarse en ese contexto por parte de la FDA en 2018; el portal alojado ya mostraba GMI y el panel ahora usa la misma denominación.

## [1.0.0-rc2] - 2026-07-31

### Añadido
- **Sistema escalonado de recuperación OTA:** una actualización inalámbrica defectuosa ya no debería dejar el panel necesitando un cable USB. Si el nuevo firmware entra en un bucle de reinicios, el panel vuelve automáticamente al firmware anterior de la otra partición de la aplicación. Si eso no es posible, muestra una pantalla de «Recuperación» y descarga por Wi-Fi una solución publicada. También sigue funcionando la instalación OTA local. Cada arranque correcto marca el firmware como válido para conservar una actualización que funciona.
  
  Probado en hardware antes de esta versión: se instaló por OTA una compilación que provocaba reinicios continuos y el panel volvió por sí solo a la versión anterior. Después se dañaron deliberadamente ambas particiones de aplicación y el panel se recuperó desde el modo seguro, sin necesidad de USB.
  
### Cambiado
- Los binarios publicados incluyen ahora la ubicación actual del proyecto para las actualizaciones (`getglucoscout/esp32-cgm`). Los binarios rc1 apuntaban a la ubicación anterior del repositorio; es necesario volver a instalarlos una vez y, después, las actualizaciones OTA funcionarán con normalidad.

## [1.0.0-rc1] - 2026-06-27

Primera **versión candidata**. Añade integración con Home Assistant, actualizaciones por internet (OTA) y configuración Wi-Fi simplificada.

### Añadido
- **Integración de Home Assistant mediante MQTT** con descubrimiento automático (glucosa, tendencia, variación y GMI estimada), además de una cuarta página de «Control de HA» que publica comandos de aviso, luz, posponer y dos comandos adicionales para automatizaciones propias.
- **Actualizaciones OTA por internet:** el panel consulta diariamente un archivo `manifest.json` específico de cada placa (también se puede solicitar manualmente) y se actualiza desde una versión publicada en GitHub, sin necesidad de USB.
- **Configuración Wi-Fi mediante portal cautivo:** permite configurar el panel sin volver a flashearlo; en el primer arranque crea un punto de acceso `glucoscout-XXXX`.
- **Interfaz de cuatro páginas con deslizamiento:** panel, glucosa ampliada, información del dispositivo y control de Home Assistant. Mantener pulsado sigue abriendo Ajustes.
- Dirección IP en pantalla, botón para restablecer los valores de fábrica y endpoint de diagnóstico `/dbg`.
- Tarjeta «Home Assistant (MQTT)» en la configuración web.

### Cambiado
- Firmware más compacto: se eliminó el marco de fotos con tarjeta SD y la página de configuración se envía de forma más eficiente (aproximadamente un 10 % menos de uso de flash y un 17 % menos de RAM).

### Corregido
- **La meteorología podía aparecer en blanco:** Open-Meteo responde con transferencia fragmentada (`chunked transfer-encoding`), que el analizador de flujo no podía leer. Ahora se lee el cuerpo completo antes de analizarlo.
- **MQTT no llegaba a conectar (estado -2):** el nombre del servidor del broker se conserva ahora en un búfer persistente; la biblioteca guardaba el puntero en vez de una copia.
- **La página de configuración podía truncarse** cuando algunos campos estaban vacíos.

## [1.0.0-beta.2] - 2026-06-25

### Corregido
- **Estabilidad en ejecuciones largas (bloqueo después de varias horas).** La causa era la fragmentación de la memoria interna, no una fuga: cada consulta asignaba un búfer TLS, un `DynamicJsonDocument` y una cadena `String` con la respuesta completa en la limitada memoria interna. Con el paso de las horas, el mayor bloque contiguo disponible se reducía hasta que fallaba la siguiente asignación y se activaba el watchdog de la tarea. Soluciones:
  - Los documentos JSON ahora se asignan en **PSRAM** mediante un asignador personalizado de ArduinoJson v7.
  - Las respuestas de Nightscout y meteorología se **analizan directamente desde el flujo TLS**, sin crear una gran cadena interna con toda la respuesta.
  - Como medida de protección, se activa un **reinicio controlado cuando queda poca memoria**, antes de que el dispositivo se bloquee por completo.

## [1.0.0-beta.1] - 2026-06-25

Primera versión **beta pública**.

### Añadido
- Panel de glucosa para ESP32-S3 y pantalla GUITION JC3248W535C de 3,5 pulgadas (`boards/esp32-s3/guition-3.5in/`): consultas a Nightscout, valor actual con flecha de tendencia, gráfico del historial reciente e interfaz de configuración de Wi-Fi/Nightscout en el dispositivo.
- Credenciales de Wi-Fi y Nightscout aisladas en `secrets.h`, excluido de Git, con una plantilla `secrets.example.h` incluida en el repositorio.
- Referencia de hardware para la JC3248W535C en `docs/`.
- Estructura inicial del proyecto: licencia MIT, aviso médico, políticas de contribución y seguridad, plantillas de incidencias/solicitudes de cambios y CI.

### Notas
- **Beta:** las interfaces y el diseño pueden cambiar antes de la versión `1.0.0`. No es un dispositivo médico; consulta el [aviso médico](DISCLAIMER.md).
- La compatibilidad con ESP32-P4 (GUITION de 10,1 pulgadas) está en desarrollo y no forma parte de esta versión.

[Sin publicar]: https://github.com/mapoloco/esp32-cgm/compare/v1.0.0...HEAD
[1.0.0]: https://github.com/mapoloco/esp32-cgm/releases/tag/v1.0.0
[1.0.0-rc3]: https://github.com/mapoloco/esp32-cgm/compare/v1.0.0-rc2...v1.0.0-rc3
[1.0.0-rc2]: https://github.com/mapoloco/esp32-cgm/compare/v1.0.0-rc1...v1.0.0-rc2
[1.0.0-rc1]: https://github.com/mapoloco/esp32-cgm/compare/v1.0.0-beta.2...v1.0.0-rc1
[1.0.0-beta.2]: https://github.com/mapoloco/esp32-cgm/compare/v1.0.0-beta.1...v1.0.0-beta.2
[1.0.0-beta.1]: https://github.com/mapoloco/esp32-cgm/releases/tag/v1.0.0-beta.1
