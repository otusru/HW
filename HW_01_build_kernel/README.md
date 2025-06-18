# Шаги

```bash
sudo vim /etc/apt/sources.list
```

```bash
sudo echo "deb http://deb.debian.org/debian bookworm main contrib non-free non-free-firmware" > /etc/apt/sources.list
```

```bash
sudo apt update
```

```bash
sudo apt install -y curl                # Утилита командной строки для отправки HTTP, FTP и других запросов; используется для скачивания файлов
sudo apt install -y build-essential     # Набор базовых инструментов для компиляции C/C++ (gcc, g++, make и др.)
sudo apt install -y libncurses-dev      # Библиотека для создания текстовых интерфейсов; используется, например, в menuconfig ядра
sudo apt install -y bison               # Генератор синтаксических анализаторов (альтернатива yacc); нужен при сборке ядра и других проектов
sudo apt install -y flex                # Генератор лексических анализаторов; часто используется с bison
sudo apt install -y libssl-dev          # Заголовочные файлы OpenSSL — для поддержки криптографии (например, TLS)
sudo apt install -y bc                  # Консольный калькулятор с поддержкой скриптов; используется в сборочных скриптах ядра
sudo apt install -y dwarves             # Набор утилит для анализа DWARF-отладочной информации (в частности, используется pahole)
sudo apt install -y pahole              # Утилита для анализа и оптимизации структур в C; полезна при работе с ядром
sudo apt install -y libelf-dev          # Работа с форматом ELF (исполняемые файлы, библиотеки, объектные файлы)
sudo apt install -y zlib1g-dev          # Библиотека сжатия zlib, часто требуется при сборке ядра и других приложений
sudo apt install -y git                 # Система контроля версий Git, нужна для получения исходников
sudo apt install -y make                # Утилита автоматической сборки проектов (Makefile)
sudo apt install -y gcc                 # Компилятор языка C от GNU
sudo apt install -y dpkg-dev            # Инструменты для сборки .deb-пакетов (в т.ч. dpkg-source)
sudo apt install -y fakeroot            # Позволяет "эмулировать" root-доступ при сборке пакетов
sudo apt install -y rsync               # Утилита синхронизации и копирования файлов/каталогов
sudo apt install -y kmod                # Управление модулями ядра Linux (insmod, rmmod, modprobe и др.)
sudo apt install -y cpio                # Архиватор, используется в процессе сборки initramfs и др.
sudo apt install -y python3             # Интерпретатор Python 3 — часто требуется в сборочных скриптах и утилитах
```

```bash
curl -O https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.1.130.tar.gz
```

```bash
tar -xvf linux-6.1.130.tar.gz
```

```bash
cd ./linux-6.1.130
```

```bash
./scripts/config --disable SECURITY_SELINUX \
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
                --disable BPFILTER
```

```bash
cp -v /boot/config-$(uname -r) .config
```

```bash
make -j$(nproc) deb-pkq 2>error.log
```

```bash
cat ./error.log
```

```bash
ls -la ../ | grep deb
```
