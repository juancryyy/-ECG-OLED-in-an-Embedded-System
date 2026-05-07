# ECG OLED in an Embedded System

Proyecto de sistema embebido para la adquisición, visualización y análisis básico de una señal ECG. El sistema utiliza un microcontrolador compatible con Arduino/ESP32, una pantalla OLED SSD1306 y una interfaz en MATLAB App Designer para graficar señales ECG normales, patológicas y reales mediante comunicación serial.

## Descripción general

Este proyecto integra hardware y software para capturar una señal electrocardiográfica, mostrarla en una pantalla OLED en tiempo real y enviar datos por puerto serial para su posterior visualización y comparación en MATLAB.

El código principal del microcontrolador lee una entrada analógica asociada a la señal cardíaca, verifica el estado de los pines de detección de electrodos y dibuja la forma de onda en una pantalla OLED de 128x64 píxeles. Además, el proyecto incluye una aplicación de MATLAB diseñada para enviar y recibir datos seriales, graficar señales ECG simuladas y comparar la señal real mediante correlación.

## Objetivo del proyecto

Desarrollar un sistema embebido capaz de:

- Leer una señal ECG desde una entrada analógica.
- Detectar posibles desconexiones de electrodos mediante pines LO+ y LO-.
- Visualizar la señal en una pantalla OLED SSD1306.
- Transmitir datos hacia una interfaz en MATLAB.
- Comparar señales ECG simuladas y reales.
- Explorar conceptos de adquisición biomédica, procesamiento de señales y comunicación serial.

## Tecnologías y herramientas utilizadas

- Arduino IDE
- MATLAB App Designer
- C/C++ para Arduino
- MATLAB
- Comunicación serial UART
- Protocolo I2C
- Pantalla OLED SSD1306 128x64
- Librerías Adafruit GFX y Adafruit SSD1306

## Componentes principales

- Microcontrolador compatible con Arduino/ESP32
- Pantalla OLED SSD1306 128x64
- Sensor o módulo de adquisición ECG
- Electrodos ECG
- Conexión serial USB
- Computador con MATLAB

## Estructura del proyecto

```txt
ECG-OLED-in-an-Embedded-System/
├── OLEDCONECG.ino
└── app1.mlapp
```

## Archivos del repositorio

### `OLEDCONECG.ino`

Código para el microcontrolador. Sus funciones principales son:

- Inicializar la comunicación serial.
- Configurar la pantalla OLED por I2C.
- Leer la señal ECG desde una entrada analógica.
- Verificar los pines de detección de electrodos `LO+` y `LO-`.
- Dibujar la señal ECG en la pantalla OLED.
- Enviar los valores leídos por el puerto serial.

Pines usados en el código:

```cpp
const int LO1 = 26;
const int LO2 = 15;
const int entradaAD = 4;
```

La señal analógica se mapea usando un rango de `0` a `4095`, correspondiente a una resolución ADC típica de ESP32.

### `app1.mlapp`

Aplicación desarrollada en MATLAB App Designer. Incluye una interfaz gráfica con:

- Gráfica de señal ECG normal.
- Gráfica de señal ECG patológica.
- Gráfica de señal ECG real.
- Gráfica de correlación entre señal real y señal normal.
- Visualización de datos recibidos desde el microcontrolador.
- Controles tipo switch para enviar comandos por serial.

La aplicación utiliza el puerto serial `COM3` y una velocidad configurada de `115200` baudios.

## Funcionamiento general

1. El microcontrolador inicializa la pantalla OLED y la comunicación serial.
2. Se verifica si los electrodos están correctamente conectados.
3. Si no hay error de conexión, se lee la señal ECG por la entrada analógica.
4. La señal se envía por el puerto serial y se dibuja en la pantalla OLED.
5. MATLAB recibe los datos seriales y los grafica en la interfaz.
6. La aplicación compara la señal real con señales ECG generadas mediante series de Fourier.
7. Se calcula una correlación para analizar la similitud entre señales.

## Instalación y configuración

### Requisitos para Arduino

Instalar las siguientes librerías desde el Library Manager de Arduino IDE:

- `Adafruit GFX Library`
- `Adafruit SSD1306`

También se requiere compatibilidad con la placa utilizada, por ejemplo ESP32 si se trabaja con un ADC de 12 bits.

### Requisitos para MATLAB

- MATLAB instalado.
- App Designer habilitado.
- Acceso al puerto serial del microcontrolador.

## Uso del proyecto

### 1. Cargar el código al microcontrolador

Abrir el archivo:

```txt
OLEDCONECG.ino
```

Seleccionar la placa correspondiente en Arduino IDE y cargar el programa.

### 2. Conectar el hardware

Conectar:

- Pantalla OLED por I2C.
- Salida analógica del sensor ECG al pin definido como `entradaAD`.
- Pines de detección de electrodos a `LO1` y `LO2`.
- Microcontrolador al computador mediante USB.

### 3. Ejecutar la aplicación MATLAB

Abrir el archivo:

```txt
app1.mlapp
```

Ejecutar la aplicación desde MATLAB App Designer y presionar el botón **Inicio**.

### 4. Verificar el puerto serial

La aplicación MATLAB está configurada para usar:

```matlab
COM3
```

Si el microcontrolador aparece en otro puerto, se debe modificar esta línea dentro de la app:

```matlab
s = serialport('COM3', 115200);
```

## Nota importante sobre baudios

En el archivo Arduino se inicializa la comunicación serial con:

```cpp
Serial.begin(9600);
```

Mientras que la aplicación MATLAB usa:

```matlab
serialport('COM3', 115200);
```

Para evitar errores de comunicación, ambos valores deben coincidir. Se recomienda configurar los dos a la misma velocidad, por ejemplo:

```cpp
Serial.begin(115200);
```

## Resultados esperados

Al ejecutar correctamente el sistema, se espera obtener:

- Visualización de la señal ECG en la pantalla OLED.
- Envío de datos analógicos por comunicación serial.
- Gráficas ECG en MATLAB.
- Comparación entre señal ECG real y señales simuladas.
- Cálculo y visualización de correlación entre señales.

## Aplicaciones

Este proyecto puede utilizarse como base para:

- Sistemas biomédicos embebidos.
- Monitoreo básico de señales ECG.
- Procesamiento digital de señales biomédicas.
- Visualización de datos en tiempo real.
- Proyectos académicos de electrónica, instrumentación y bioingeniería.

## Aprendizajes del proyecto

Durante el desarrollo de este proyecto se trabajan conceptos como:

- Lectura de señales analógicas en microcontroladores.
- Uso de pantallas OLED con comunicación I2C.
- Comunicación serial entre microcontrolador y MATLAB.
- Diseño de interfaces gráficas con MATLAB App Designer.
- Representación de señales ECG.
- Correlación entre señales.
- Integración de hardware y software en sistemas embebidos.

## Posibles mejoras

- Corregir y estandarizar la velocidad serial entre Arduino y MATLAB.
- Agregar filtros digitales para reducir ruido en la señal ECG.
- Implementar detección de picos R.
- Calcular frecuencia cardíaca en BPM.
- Guardar datos ECG en archivos `.csv`.
- Mejorar la escala de visualización en la pantalla OLED.
- Agregar documentación del circuito y diagrama de conexiones.
- Incluir capturas de la interfaz y del montaje físico.

## Consideraciones de seguridad

Este proyecto tiene fines académicos y experimentales. No debe usarse como dispositivo médico profesional ni para diagnóstico clínico. Si se trabaja con señales biomédicas reales, se deben tomar precauciones de aislamiento eléctrico y seguridad del usuario.

## Autor

Desarrollado como proyecto académico de sistema embebido para adquisición y visualización de señales ECG.
