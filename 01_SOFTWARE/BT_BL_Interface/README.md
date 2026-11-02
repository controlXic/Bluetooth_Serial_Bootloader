# Control Xic Bootloader Bluetooth Classic Interface

## Desktop Application

### Usage

1. Connect to the `BL_BTL_Router` serial port.
2. Select the target device using its MAC address and establish a connection.
3. Activate the bootloader.
4. Disconnect the serial port.
5. Connect the serial port to STM32CubeProgrammer.
6. Flash the STM32.

### Bootloader Timeout

The bootloader has a timeout of 10/30 seconds. If no flashing operation is performed within this period, the connection will be automatically terminated and the device will need to be reconnected.

The timeout is reset after each flash operation, including read and write operations.

Nota: He utilitzat target device per referir-me al dispositiu destinatari i connection will be automatically terminated per descriure la desconnexió automàtica. Són expressions habituals en documentació tècnica.


