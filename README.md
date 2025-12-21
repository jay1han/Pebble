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

| ID   | Line | Position | Item           | Text         | Font      | Actual GRect     |
|------|------|----------|----------------|--------------|-----------|------------------|
| date | 1    | Left     | Date           | `Sun 31 Dec` | Gothic 28 | 0, -10, 144, 31  |
| pchg | 1    | Right    | Phone charging | `C`          | Gothic 28 |                  |
| time | 2    | Line     | Time           | `23:39`      | Roboto 49 | 0, 11, 144, 51   |
| wbat | 3    | Left     | Pebble Battery | `99`         | Gothic 28 | 0, 62, 50, 31    |
| noti | 3    | Center   | Notifications  | `MK`         | Gothic 28 |                  |
| pbat | 3    | Right    | Phone Battery  | `99`         | Gothic 28 |                  |
| bt   | 4    | Left     | Bluetooth      | `Bose:90`    | Gothic 24 |                  |
| wifi | 5    | Left     | WiFi           | `SFR_box`    | Gothic 18 |                  |
| net  | 5    | Right    | Network        | `4G`         | Gothic 18 |                  |
| away | 6    | Left     | Away           | `Mon 03:39`  | Gothic 24 | 2, 138, 128, 30  |
| dnd  | 6    | Right    | Quiet mode     | `Q`          | Gothic 24 | 130, 138, 14, 30 |

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
