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

| ID   | Y Pos | Position | Item           | Text         | Font      |
|------|-------|----------|----------------|--------------|-----------|
| date | -10   | Left     | Date           | `Sun 31 Dec` | Gothic 28 |
| pchg | -10   | Right    | Phone charging | `C`          | Gothic 28 |
| home | 14    | Line     | Home time      | `23:39`      | Roboto 49 |
| noti | 64    | Center   | Notifications  | `MK`         | Gothic 28 |
| wbat | 64    | Left     | Pebble Battery | `99`         | Gothic 28 |
| pbat | 64    | Right    | Phone Battery  | `99`         | Gothic 28 |
| bt   | 94    | Left     | Bluetooth      | `Bose:90`    | Gothic 24 |
| wifi | 115   | Left     | WiFi           | `SFR_box`    | Gothic 18 |
| net  | 115   | Right    | Network        | `4G`         | Gothic 18 |
| away | 139   | Left     | Away date/time | `Mon 03:39`  | Gothic 24 |
| dnd  | 139   | Right    | Quiet mode     | `Q`          | Gothic 24 |

Black background

- (0, 0, 144, 21): date and pchg

- (28, 70, 88, 26): noti

- (0, 146, 144, 22): away and dnd

# Display items

## Pebble internal

### Date and time home and away

### Battery and charging

## Phone state

### Battery and charging

### WiFi

### Mobile network

### Bluetooth devices

### DND

## Notifications

# Android app

## Layout

| Item          | Input                       |
|---------------|-----------------------------|
| Pebble watch  | Connect                     |
| Away timezone | Hours, Minutes              |
| Notifications | (list) Package name, Letter |
| Bluetooth     | (list) Device ID, Menmonic  |

## Permissions

# Watch-app

| Button | Function      |
|--------|---------------|
| Up     | DND toggle    |
| Center | Find my phone |
| Down   |               |

# Communication
