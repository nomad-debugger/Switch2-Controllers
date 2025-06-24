# Nintendo Switch BLE Enabler Daemon

Dieses Tool aktiviert Bluetooth-fähige Nintendo Switch Controller (Pro Controller, Joy-Con, GameCube) über BLE (Bluetooth Low Energy), indem es den notwendigen Initialisierungs-Handshake durchführt und die Controller für die Nutzung auf anderen Systemen vorbereitet.

Der Daemon funktioniert ähnlich wie der NS2-USB-Enabler, jedoch für Bluetooth-Verbindungen.

## Funktionen

- Erkennung von Nintendo Switch Pro Controller, Joy-Con und GameCube-Controllern über BLE
- Durchführen der Initialisierungssequenz (wie beim originalen SW2-Code)
- Konfiguration der Controller-LEDs
- Mapping von Controller-Eingängen auf ein Standard-Format
- Rumble-Feedback-Support

## Voraussetzungen

- Linux-System mit Bluetooth
- Bluetooth 4.0+ Adapter mit BLE-Unterstützung
- GattLib-Bibliothek
- Root-Rechte für Bluetooth-Zugriff

## Installation

1. Installiere die benötigten Pakete:

```bash
sudo apt-get install libbluetooth-dev libglib2.0-dev
sudo apt-get install libreadline-dev
```

2. Installiere GattLib:

```bash
git clone https://github.com/labapart/gattlib
cd gattlib
mkdir build && cd build
cmake -DGATTLIB_PYTHON_INTERFACE=OFF -DGATTLIB_BUILD_EXAMPLES=OFF ..
make
sudo make install
sudo ldconfig
```

3. Kompiliere den BLE-Enabler:

```bash
git clone https://github.com/your-username/ns2-ble-enabler
cd ns2-ble-enabler
make
```

## Verwendung

1. Bringe den Controller in den Pairing-Modus:
   - Pro Controller/GameCube: Halte die kleine Pairing-Taste auf der Oberseite gedrückt, bis die LEDs blinken
   - Joy-Con: Halte die SL+SR-Tasten gedrückt

2. Starte den Daemon mit Root-Rechten:

```bash
sudo ./bt_enabler_daemon
```

3. Der Daemon sucht nun nach kompatiblen Controllern, verbindet sich und führt die Initialisierung durch.

4. Nach erfolgreicher Initialisierung gibt der Daemon die Controller-Eingaben in der Konsole aus.

5. Beenden mit Strg+C

## Fehlerbehebung

- **Controller wird nicht gefunden**: Stelle sicher, dass der Controller im Pairing-Modus ist (LEDs blinken)
- **Verbindungsfehler**: Überprüfe, ob der Bluetooth-Adapter korrekt funktioniert
- **Berechtigungsprobleme**: Starte den Daemon mit sudo-Rechten
- **Initialisierungsfehler**: Entferne den Controller aus den Bluetooth-Geräten und versuche es erneut

## Weitere Entwicklung

Der Code kann noch weiter angepasst werden:
- Integration mit udev für automatische Gerätererkennung
- Daemon-Modus (Hintergrund)
- Konfigurationsdatei für benutzerdefinierte Einstellungen
- Vollständiger GameCube-Controller-Support

## Lizenz

Apache-2.0, basierend auf der Original-Arbeit von Jacques Gagnon