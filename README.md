# Pebble

A Pebble watchface including all the features I need.

### Screen size

| Platform       | Screen size |
|----------------|-------------|
| Aplite, Basalt | 144x168     |
| Time 2         | 200x228     |

### Fonts

- Roboto 49
- Gothic 28 Bold
- Gothic 24 Bold

### Display layout

| ID     | Y Pos | Position | Item           | Text         | Font      |
|--------|-------|----------|----------------|--------------|-----------|
| `date` | -10   | Center   | Date           | `Sun 31 Dec` | Gothic 28 |
| `dnd`  | -10   | Left     | Quiet mode     | `X`          | Gothic 28 |
| `pchg` | -10   | Right    | Phone charging | `C`          | Gothic 28 |
| `home` | 14    | Line     | Home time      | `23:39`      | Roboto 49 |
| `noti` | 64    | Center   | Notifications  | `GK`         | Gothic 28 |
| `bt`   | 94    | Left     | Bluetooth      | `Bose:90`    | Gothic 24 |
| `wifi` | 115   | Left     | WiFi           | `SFR_box`    | Gothic 24 |
| `net`  | 115   | Right    | Network        | `4G`         | Gothic 24 |
| `away` | 139   | Center   | Away date/time | `03:39`      | Gothic 28 |
| `wbat` | 139   | Left     | Pebble Battery | `99`         | Gothic 28 |
| `pbat` | 139   | Right    | Phone Battery  | `99`         | Gothic 28 |

Black background

- (0, 0, 144, 21): `date` and `pchg`

- (0, 70, 144, 26): `noti`

- (0, 146, 144, 22): `away` and `dnd`

# Display items

## Watch internal

Date and time is based on the Pebble internal clock, which is synchronized with the phone.
The away time is calculated as a constant offset from the home time,
the offset being defined in hours and minutes (positive or negative).

The watch battery is standard Pebble C SDK.

## Phone state

### Battery and charging

### Bluetooth devices

### WiFi

### Mobile network

### DND

## Notifications

Notifications are intercepted, then the emitting package name is compared to the configuration list.
If a package matches, the corresponding letter (upper case only) is added to the notification string.
Notification removal is also intercepted in order to remove the corresponding letter from the string.
If a package is not found in the list, a `+` is added.
Up to 9 packages can be stored in the list.

Examples

| Letter | App      | Package                             |
|--------|----------|-------------------------------------|
| `G`    | Gmail    | `com.google.android.gm`             |
| `K`    | Kakao    | `com.kakao.talk`                    |
| `L`    | LinkedIn | `com.linkedin.android`              |
| `M`    | Meet     | `com.google.android.apps.tachyon`   |
| `O`    | Outlook  | `com.microsoft.office.outlook`      |
| `S`    | SMS      | `com.google.android.apps.messaging` |
| `T`    | Teams    | `com.microsoft.teams`               |
| `W`    | WhatsApp | `com.whatsapp`                      |
| `Z`    | Zoom     | `us.zoom.videomeetings`             |

# Android app

## Layout

| Item          | Info/Input                                         |
|---------------|----------------------------------------------------|
| Pebble watch  | Connection status                                  |
| Notifications | Confirm access or link to settings                 |
| Away timezone | Hours, Minutes (+ or -)                            |
| Notifications | (list up to 9) Package name, Letter                |
| Bluetooth     | (list up to 9) Device ID, Mnemonic (up to 5 chars) |

## Permissions

- Notification access

- Bluetooth connections (event)

- WiFi status (event)

- Mobile network type (event)

- Battery and charging (event)

- DND status (event)

# Watch-app

| Button | Function      |
|--------|---------------|
| Up     | DND toggle    |
| Center | Find my phone |
| Down   |               |

# Communication
