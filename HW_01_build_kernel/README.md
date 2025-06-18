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
sudo apt install curl -y
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
sudo apt install -y \
    build-essential \
    libncurses-dev \
    bison \
    flex \
    libssl-dev \
    bc \
    dwarves \
    pahole \
    libelf-dev \
    zlib1g-dev \
    git \
    make \
    gcc \
    dpkg-dev \
    fakeroot \
    rsync \
    kmod \
    cpio \
    python3
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
