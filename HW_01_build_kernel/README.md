## **СБОРКА ЯДРА LINUX 6.1.130**

### 1. Стать `root`

```bash
su
```

### 2. Обновить источники пакетов

```bash
echo "deb http://deb.debian.org/debian bookworm main contrib non-free non-free-firmware" > /etc/apt/sources.list
```

### 3. Установить все необходимые зависимости

```bash
apt update
apt install -y \
    build-essential libncurses-dev bison flex libssl-dev bc \
    dwarves pahole libelf-dev zlib1g-dev git make gcc \
    dpkg-dev fakeroot rsync kmod cpio python3 curl
```

### 4. Очистить ненужные модули и проверка загруженных модулей (не обязательно)

```bash
sudo modprobe -r bluetooth
sudo modprobe -r snd_hda_codec_hdmi
```

Проверь загруженные модули:

```bash
lsmod
```

### 5. Загрузить исходный код ядра

```bash
cd /usr/src
```

```bash
curl -O https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.1.130.tar.gz
```

```bash
tar -xvf linux-6.1.130.tar.gz
```

```bash
cd linux-6.1.130
```

### 6. Скопировать текущую конфигурацию ядра (не обязательно)

```bash
cp -v /boot/config-$(uname -r) .config
```

### 7. Изменить конфигурацию (отключить ненужные опции)

```bash
./scripts/config \
--disable SECURITY_SELINUX \
--disable SECURITY_SMACK \
--disable SECURITY_TOMOYO \
--disable SECURITY_APPARMOR \
--disable SECURITY_YAMA \
--disable RANDOMIZE_BASE \
--disable CPU_MITIGATIONS \
--disable MITIGATION_SPECTRE_BHI \
--disable MITIGATION_RFDS \
--disable PAGE_TABLE_ISOLATION \
--disable ZSWAP \
--disable BPF \
--disable BPF_SYSCALL \
--disable BPF_JIT \
--disable BPF_EVENTS \
--disable BPFILTER \
--disable MODULE_SIG
```

### 8. Обновить конфигурацию


Минимальное ядро для железа

```bash
make localmodconfig       # Создает конфигурацию только для загруженных модулей текущей системы (минималистичная)
```

Базовая конфигурация (не обязательно)

```bash
make defconfig            # Создает базовую конфигурацию по умолчанию от разработчиков ядра.
```

Если уже есть .config (не обязательно)

```bash
make olddefconfig         # Обновляет существующую .config, задавая дефолтные значения для новых параметров.
```

### 9. Копировать на флэшку .config (не обязательно)

```bash
df -h
```

```bash
cp -r .config /media/linux/78D48F66D48F260A
```

### 10. Собрать .deb пакеты ядра

```bash
make -j$(nproc) deb-pkg 2> ../error.log
```

### 11. Проверить наличие ошибок

```bash
cat ../error.log
```

### 12. Копировать на флэшку error.log (не обязательно)

```bash
df -h
```

```bash
cp -r ../error.log /media/linux/78D48F66D48F260A
```

### 13. Проверить наличия ядра

```bash
ls -la ../ | grep deb
```

Ожидаемый вывод:

```
-rw-r--r--  1 root root   8544440 июн 18 13:04 linux-headers-6.1.130_6.1.130-3_amd64.deb
-rw-r--r--  1 root root  13288196 июн 18 13:04 linux-image-6.1.130_6.1.130-3_amd64.deb
-rw-r--r--  1 root root 148206204 июн 18 13:05 linux-image-6.1.130-dbg_6.1.130-3_amd64.deb
-rw-r--r--  1 root root   1275312 июн 18 13:04 linux-libc-dev_6.1.130-3_amd64.deb
```

### 14. Копировать на флэшку ядро 6.1.130 (не обязательно)

```bash
df -h
```

```bash
cp -r ../linux-*6.1.130*_amd64.deb /media/linux/78D48F66D48F260A
```

```bash
tar -czvf linux-6.1.130.tar.gz linux-*.deb
```

### 15. Установить новое ядро

```bash
cd ..
dpkg -i linux-image-6.1.130*.deb linux-headers-6.1.130*.deb
```

### 16. Перезагрузить систему

```bash
reboot
```

### 17. Проверить, что новое ядро загружено

После перезагрузки:

```bash
uname -r
```

Ожидаемый вывод:

```
6.1.130
```
