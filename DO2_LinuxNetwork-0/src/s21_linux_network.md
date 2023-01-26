## Part 1. Инструмент ipcalc ##
### 1.1. Сети и маски ###
**1) Адрес сети 192.167.38.54/13**
* Устанавливаем утилиту ipcalc командой `sudo apt-get install ipcalc`
* Введём команду `ipcalc 192.167.38.54/13` \
  ![1.1.1_ipcalc_network](screenshots/1.1.1_ipcalc_network.png)
  

* Адрес сети - `192.160.0.0/13`

**2) Перевод маски 255.255.255.0 в префиксную и двоичную запись, /15 в обычную и двоичную, 11111111.11111111.11111111.11110000 в обычную и префиксную**
* Введём команду `ipcalc 0.0.0.0/255.255.255.0` \
  ![1.1.2_ipcalc_mask_1](screenshots/1.1.2_ipcalc_mask_1.png)
* Префиксная форма - `/24`, двоичная запись - `11111111.11111111.11111111.00000000`
  

* Введём команду `ipcalc 0.0.0.0/15` \
  ![1.1.2_ipcalc_mask_2](screenshots/1.1.2_ipcalc_mask_2.png)
* Обычная форма - `255.254.0.0`, двоичная запись - `11111111.11111110.00000000.00000000`
  

* Переведём `11111111.11111111.11111111.11110000` в десятичную форму - `255.255.255.240`
* Введём команду `ipcalc 0.0.0.0/255.255.255.240` \
  ![1.1.2_ipcalc_mask_3](screenshots/1.1.2_ipcalc_mask_3.png)
* Обычная форма - `255.255.255.240`, префиксная - `/28`

**3) Минимальный и максимальный хост в сети 12.167.38.4 при масках: /8, 11111111.11111111.00000000.00000000, 255.255.254.0 и /4**
* Введём команду `ipcalc 12.167.38.4/8` \
  ![1.1.3_ipcalc_min_max_1](screenshots/1.1.3_ipcalc_min_max_1.png)
* Минимальный хост - `12.0.0.1`, максимальный хост - `12.255.255.254`
  

* Переведём `11111111.11111111.00000000.00000000` в десятичную форму - `255.255.0.0`
* Введём команду `ipcalc 12.167.38.4/255.255.0.0` \
  ![1.1.3_ipcalc_min_max_2](screenshots/1.1.3_ipcalc_min_max_2.png)
* Минимальный хост - `12.167.0.1`, максимальный хост - `12.167.255.254`
  

* Введём команду `ipcalc 12.167.38.4/255.255.254.0` \
  ![1.1.3_ipcalc_min_max_3](screenshots/1.1.3_ipcalc_min_max_3.png)
* Минимальный хост - `12.167.38.1`, максимальный хост - `12.167.39.254`
  

* Введём команду `ipcalc 12.167.38.4/4` \
  ![1.1.3_ipcalc_min_max_4](screenshots/1.1.3_ipcalc_min_max_4.png)
* Минимальный хост - `0.0.0.1`, максимальный хост - `15.255.255.254`
  

### 1.2. localhost ###
**Определить и записать в отчёт, можно ли обратиться к приложению, работающему на localhost, со следующими IP: 194.34.23.100, 127.0.0.2, 127.1.0.1, 128.0.0.1**
* localhost - зарезервированное доменное имя для частных ip-адресов (диапазон `127.0.0.1` - `127.255.255.254`). Из этого можно сделать вывод, что обратиться можно будет только к приложениям, работающим с ip `127.0.0.2` и `127.1.0.1` из данного списка. Проверим:
  

* Введём команду `ipcalc 194.34.23.100` \
  ![1.2_ip_check_1](screenshots/1.2_ip_check_1.png)
* Интерфейс `loopback` отсутствует в строке `Host/Net`, значит адрес нам не подходит.
  

* Введём команду `ipcalc 127.0.0.2` \
  ![1.2_ip_check_2](screenshots/1.2_ip_check_2.png)
* Интерфейс `loopback` присутствует в строке `Host/Net`, значит адрес нам подходит.
  

* Введём команду `ipcalc 127.1.0.1` \
  ![1.2_ip_check_3](screenshots/1.2_ip_check_3.png)
* Интерфейс `loopback` присутствует в строке `Host/Net`, значит адрес нам подходит.
  

* Введём команду `ipcalc 128.0.0.1` \
  ![1.2_ip_check_4](screenshots/1.2_ip_check_4.png)
* Интерфейс `loopback` отсутствует в строке `Host/Net`, значит адрес нам не подходит.
  

### 1.3. Диапазоны и сегменты сетей ###
**1) Какие из перечисленных IP можно использовать в качестве публичного, а какие только в качестве частных: 10.0.0.45, 134.43.0.2, 192.168.4.2, 172.20.250.4, 172.0.2.1, 192.172.0.1, 172.68.0.2, 172.16.255.255, 10.10.10.10, 192.169.168.1**
* Выведем информацию о каждом ip адресе \
  ![1.3.1_private_public](screenshots/1.3.1_private_public.png)
  

* В строке `Host/Net` наличие записи `Private Internet`, говорит о то, что ip адрес принадлежит частной сети.
* Адреса `134.43.0.2`, `172.0.2.1`, `192.172.0.1`, `172.68.0.2`, `192.169.168.1` можно использовать в качестве публичных.
* Адреса `10.0.0.45`, `192.168.4.2`, `172.20.250.4`, `172.16.255.255`, `10.10.10.10` можно использовать только в качестве частных.

**2) Какие из перечисленных IP адресов шлюза возможны у сети 10.10.0.0/18: 10.0.0.1, 10.10.0.2, 10.10.10.10, 10.10.100.1, 10.10.1.255**
* Введём команду `ipcalc 10.10.0.0/18` \
  ![1.3.2_gateways](screenshots/1.3.2_gateways.png)
  

* Возможные адреса шлюза: `10.10.0.2`, `10.10.10.10`, `10.10.1.255`.
  

## Part 2. Статическая маршрутизация между двумя машинами ##
**1) Поднять две виртуальные машины (далее -- ws1 и ws2)** 
* Виртуальные машины ws1 и ws2 в работе \
  ![2.0.1_second_machine](screenshots/2.0.1_second_machine.png)
  

**2) C помощью команды `ip a` посмотреть существующие сетевые интерфейсы** 
* Перед запуском машинам был добавлен второй адаптер с типом подключения "сетевой мост"
  

* Машина ws1 \
  ![2.0.2_ws1_ip](screenshots/2.0.2_ws1_ip.png)
  

* Машина ws2 \
  ![2.0.2_ws2_ip](screenshots/2.0.2_ws2_ip.png)
  

**3) Описать сетевой интерфейс, соответствующий внутренней сети, на обеих машинах и задать следующие адреса и маски: ws1 - 192.168.100.10, маска /16, ws2 - 172.24.116.8, маска /12**
* На каждой машине введём команду `sudo vim /etc/netplan/00-installer-config.yaml` и вносим изменения согласно заданию.
  

* Машина ws1 \
  ![2.0.3_ws1_config](screenshots/2.0.3_ws1_config.png)
  

* Машина ws2 \
  ![2.0.3_ws2_config](screenshots/2.0.3_ws2_config.png)
  

* На каждой машине вводим команду `sudo netplan apply`
  

* Машина ws1 \
  ![2.0.3_ws1_netplan_apply](screenshots/2.0.3_ws1_netplan_apply.png)
  

* Машина ws2 \
  ![2.0.3_ws2_netplan_apply](screenshots/2.0.3_ws2_netplan_apply.png)
  

### 2.1. Добавление статического маршрута вручную ###
**1) Добавить статический маршрут от одной машины до другой и обратно при помощи команды вида `ip r add`**
* Вводим на машине ws1 команду `ip r add 172.24.116.8 via 192.168.100.10 dev enp0s8` \
  ![2.1.1_ws1_r_add](screenshots/2.1.1_ws1_r_add.png)
  

* Вводим на машине ws2 команду `ip r add 192.168.100.10 via 172.24.116.8 dev enp0s8` \
  ![2.1.1_ws2_r_add](screenshots/2.1.1_ws2_r_add.png)
  
**2) Пропинговать соединение между машинами**
  

* Машина ws1 \
  ![2.1.2_ws1_ping](screenshots/2.1.2_ws1_ping.png)
  

* Машина ws2 \
  ![2.1.2_ws1_ping](screenshots/2.1.2_ws2_ping.png)
  

### 2.2. Добавление статического маршрута с сохранением ###
* Перезапускаем машины командой `reboot`
  
**1) Добавить статический маршрут от одной машины до другой с помощью файла etc/netplan/00-installer-config.yaml**
  

* Измененный файл `etc/netplan/00-installer-config.yaml` на ws1 \
  ![2.2.1_ws1_netplan_config_changed](screenshots/2.2.1_ws1_netplan_config_changed.png)
  

* Измененный файл `etc/netplan/00-installer-config.yaml` на ws2 \
  ![2.2.1_ws2_netplan_config_changed](screenshots/2.2.1_ws2_netplan_config_changed.png)

**2) Пропинговать соединение между машинами**
* Применяем изменения на обеих машинах командой `sudo netplan apply`, после чего воспользуемся командой `ping`
  

* Машина ws1 \
  ![2.2.2_ws1_ping](screenshots/2.2.2_ws1_ping.png)


* Машина ws2 \
  ![2.2.2_ws1_ping](screenshots/2.2.2_ws2_ping.png)
  

## Part 3. Утилита iperf3 ##
### 3.1. Скорость соединения ###
**Перевести и записать в отчёт: 8 Mbps в MB/s, 100 MB/s в Kbps, 1 Gbps в Mbps**
* 8 Mbps = 1 MB/s
* 100 MB/s = 819200 Kbps
* 1 Gbps = 1024 Mbps
  

### 3.2. Утилита iperf3 ###
**Измерить скорость соединения между ws1 и ws2**
* Пусть ws1 выступает в роли сервера, вводим команду `iperf3 -s -f m` \
  ![3.2_ws1_iperf3](screenshots/3.2_ws1_iperf3.png)
  

* Пусть ws2 выступает в роли клиента, вводим команду `iperf3 -c 192.168.100.10 -f m` \
  ![3.2_ws2_iperf3](screenshots/3.2_ws2_iperf3.png)
  

## Part 4. Сетевой экран ##
### 4.1. Утилита iptables ###
**Создать файл /etc/firewall.sh, имитирующий фаерволл, на ws1 и ws2:**

    #!/bin/sh

    # Удаление всех правил в таблице "filter" (по-умолчанию).  
    iptables -F  
    iptables –X  
  
**Нужно добавить в файл подряд следующие правила:**

**1) на ws1 применить стратегию когда в начале пишется запрещающее правило, а в конце пишется разрешающее правило (это касается пунктов 4 и 5)**

**2) на ws2 применить стратегию когда в начале пишется разрешающее правило, а в конце пишется запрещающее правило (это касается пунктов 4 и 5)**

**3) открыть на машинах доступ для порта 22 (ssh) и порта 80 (http)**

**4) запретить echo reply (машина не должна "пинговаться”, т.е. должна быть блокировка на OUTPUT)**

**5) разрешить echo reply (машина должна "пинговаться")**
* Содержимое файла /etc/firewall.sh машины ws1 \
  ![4.1_ws1_firewall](screenshots/4.1_ws1_firewall.png)
  

* Содержимое файла /etc/firewall.sh машины ws2 \
  ![4.1_ws2_firewall](screenshots/4.1_ws2_firewall.png)
  
**Запустить файлы на обеих машинах командами `chmod +x /etc/firewall.sh` и `/etc/firewall.sh`**
* Вводим указанные команды на машине ws1 \
  ![4.1_ws1_run_firewall](screenshots/4.1_ws1_run_firewall.png)
  

* Вводим указанные команды на машине ws2 \
  ![4.1_ws2_run_firewall](screenshots/4.1_ws2_run_firewall.png)
  
* Разница стратегий: поскольку применяется только первое подходящее правило, а остальные игнорируются, на машине ws1 для входящего пакета будет применяться запрет, а на ws2 - разрешение.
  

### 4.2. Утилита nmap ###
**Командой `ping` найти машину, которая не "пингуется", после чего утилитой `nmap` показать, что хост машины запущен**
* Пинг ws2 c ws1 \
  ![4.2_ws1-ws2_ping](screenshots/4.2_ws1-ws2_ping.png)
  

* Пинг ws1 c ws2 и проверка хоста утилитой nmap (в выводе есть строка `Host is up`) \
  ![4.2_ws2-ws1_ping](screenshots/4.2_ws2-ws1_ping.png)
  
## Part 5. Статическая маршрутизация сети ##
**Поднять пять виртуальных машин (3 рабочие станции (ws11, ws21, ws22) и 2 роутера (r1, r2))**
* Виртуальные машины в работе \
  ![5.0_more_VMs](screenshots/5.0_more_VMs.png)
  

### 5.1. Настройка адресов машин ###
**1) Настроить конфигурации машин в `etc/netplan/00-installer-config.yaml` согласно сети на рисунке.**
* r1 \
  ![5.1.1_r1_config](screenshots/5.1.1_r1_config.png)
  

* r2 \
  ![5.1.1_r2_config](screenshots/5.1.1_r2_config.png)
  

* ws11 \
  ![5.1.1_ws11_config](screenshots/5.1.1_ws11_config.png)
  

* ws21 \
  ![5.1.1_ws21_config](screenshots/5.1.1_ws21_config.png)
  

* ws22 \
  ![5.1.1_ws22_config](screenshots/5.1.1_ws22_config.png)
  

**2) Перезапустить сервис сети. Если ошибок нет, то командой ip -4 a проверить, что адрес машины задан верно. Также пропинговать ws22 с ws21. Аналогично пропинговать r1 с ws11.**
* Результат ввода команд на r1 \
  ![5.1.2_r1_check](screenshots/5.1.2_r1_check.png)
  

* Результат ввода команд на r2 \
  ![5.1.2_r2_check](screenshots/5.1.2_r2_check.png)
  

* Результат ввода команд на ws11 и пинг r1 \
  ![5.1.2_ws11_check](screenshots/5.1.2_ws11_check.png)
  

* Результат ввода команд на ws21 и пинг ws22 \
  ![5.1.2_ws21_check](screenshots/5.1.2_ws21_check.png)
  

* Результат ввода команд на ws22 \
  ![5.1.2_ws22_check](screenshots/5.1.2_ws22_check.png)
  

### 5.2. Включение переадресации IP-адресов. ###
**1) Для включения переадресации IP, выполните команду на роутерах:**
`sysctl -w net.ipv4.ip_forward=1`
* Вывод команды на r1 \
  ![5.2.1_r1_term_forward](screenshots/5.2.1_r1_term_forward.png)
  

* Вывод команды на r2 \
  ![5.2.1_r2_term_forward](screenshots/5.2.1_r2_term_forward.png)


**2) Откройте файл /etc/sysctl.conf и добавьте в него следующую строку:**
`net.ipv4.ip_forward = 1`
* Измененный файл на r1 \
  ![5.2.2_r1_conf_forward](screenshots/5.2.2_r1_conf_forward.png)
  

* Измененный файл на r2 \
  ![5.2.2_r2_conf_forward](screenshots/5.2.2_r2_conf_forward.png)
  

### 5.3. Установка маршрута по-умолчанию ###
**1) Настроить маршрут по-умолчанию (шлюз) для рабочих станций. Для этого добавить default перед IP роутера в файле конфигураций**
* Файл `etc/netplan/00-installer-config.yaml` на ws11 \
  ![5.3.1_ws11_conf_gateway](screenshots/5.3.1_ws11_conf_gateway.png)
  

* Файл `etc/netplan/00-installer-config.yaml` на ws21 \
  ![5.3.1_ws21_conf_gateway](screenshots/5.3.1_ws21_conf_gateway.png)
  

* Файл `etc/netplan/00-installer-config.yaml` на ws22 \
  ![5.3.1_ws22_conf_gateway](screenshots/5.3.1_ws22_conf_gateway.png)
  

* Также задаём шлюзы для роутеров, чтобы иметь доступ в соседнюю сеть
  
* Файл `etc/netplan/00-installer-config.yaml` на r1 \
  ![5.3.1_r1_conf_gateway](screenshots/5.3.1_r1_conf_gateway.png)
  

* Файл `etc/netplan/00-installer-config.yaml` на r2 \
  ![5.3.1_r2_conf_gateway](screenshots/5.3.1_r2_conf_gateway.png)
  

**2) Вызвать `ip r` и показать, что добавился маршрут в таблицу маршрутизации**
* На ws11 \
  ![5.3.2_ws11_ip_r_check](screenshots/5.3.2_ws11_ip_r_check.png)
  

* На ws21 \
  ![5.3.2_ws21_ip_r_check](screenshots/5.3.2_ws21_ip_r_check.png)
  

* На ws22 \
  ![5.3.2_ws22_ip_r_check](screenshots/5.3.2_ws22_ip_r_check.png)
  

* На r1 \
  ![5.3.2_r1_ip_r_check](screenshots/5.3.2_r1_ip_r_check.png)
  

* На r2 \
  ![5.3.2_r2_ip_r_check](screenshots/5.3.2_r2_ip_r_check.png)
  
**3) Пропинговать с ws11 роутер r2 и показать на r2, что пинг доходит. Для этого использовать команду: `tcpdump -tn -i eth1`**
* Пинг роутера r2 с ws11 \
  ![5.3.3_ws11-r2_ping](screenshots/5.3.3_ws11-r2_ping.png)
  

* Так как названия интерфейсов у нас не `eth0` и `eth1`, а `enp0s8` и `enp0s9`, меняем его на соответсвующее
* Пинг доходит до роутера r2 \
  ![5.3.3_r2_ping_check](screenshots/5.3.3_r2_ping_check.png)
  

### 5.4. Добавление статических маршрутов ###
**1) Добавить в роутеры r1 и r2 статические маршруты в файле конфигураций. Пример для r1 маршрута в сетку 10.20.0.0/26:**

    # Добавить в конец описания сетевого интерфейса eth1:
    - to: 10.20.0.0  
    via: 10.100.0.12
  
* Файл на r1 \
  ![5.4.1_r1_static_route](screenshots/5.4.1_r1_static_route.png)
  

* Файл на r2 \
  ![5.4.1_r2_static_route](screenshots/5.4.1_r2_static_route.png)
  

**2) Вызвать `ip r` и показать таблицы с маршрутами на обоих роутерах. Пример таблицы на r1:**

    10.100.0.0/16 dev eth1 proto kernel scope link src 10.100.0.11
    10.20.0.0/26 via 10.100.0.12 dev eth1
    10.10.0.0/18 dev eth0 proto kernel scope link src 10.10.0.1
  
* Результат вызова для r1 \
  ![5.4.2_r1_ip_r_check](screenshots/5.4.2_r1_ip_r_check.png)
  

* Результат вызова для r2 \
  ![5.4.2_r2_ip_r_check](screenshots/5.4.2_r2_ip_r_check.png)

**3) Запустить команды на ws11:**
`ip r list 10.10.0.0/[маска сети]` и `ip r list 0.0.0.0/0`
  

* Результат вызова \
  ![5.4.3_ws11_ip_r_lists](screenshots/5.4.3_ws11_ip_r_lists.png)
  
* Для адреса `10.10.0.0/18` был выбран маршрут, отличный от `0.0.0.0/0`, так как маршрут по-умолчанию имеет более низкий приоритет, чем маршрут, указанный в таблице маршрутизации. Поскольку для сети `10.10.0.0` нами было создано правило, созданный маршрут был использован.
  

### 5.5. Построение списка маршрутизаторов ###
**Запустить на r1 команду дампа: `tcpdump -tnv -i eth0`**
* В нашем случае имя сетевого интерфейса `enp0s8`
  
**При помощи утилиты traceroute построить список маршрутизаторов на пути от ws11 до ws21**
* Устанавливаем утилиту traceroute командой `sudo apt-get install traceroute`
  

* Вызываем команду `traceroute 10.20.0.10` на ws11 \
  ![5.5.1_ws11-ws21_traceroute](screenshots/5.5.1_ws11-ws21_traceroute.png)
  

* Вывод на роутере r1 \
  ![5.5.1_r1_traceroute_check](screenshots/5.5.1_r1_traceroute_check.png)
  
* Принцип работы traceroute :
  
  Для определения промежуточных маршрутизаторов traceroute отправляет серию пакетов данных целевому узлу, при этом каждый раз увеличивая на 1 значение поля TTL («время жизни»). Это поле обычно указывает максимальное количество маршрутизаторов, которое может быть пройдено пакетом. Первый пакет отправляется с TTL, равным 1, и поэтому первый же маршрутизатор возвращает обратно сообщение ICMP, указывающее на невозможность доставки данных. Traceroute фиксирует адрес маршрутизатора, а также время между отправкой пакета и получением ответа (эти сведения выводятся на монитор компьютера). Затем traceroute повторяет отправку пакета, но уже с TTL, равным 2, что позволяет первому маршрутизатору пропустить пакет дальше. Процесс повторяется до тех пор, пока при определённом значении TTL пакет не достигнет целевого узла. При получении ответа от этого узла процесс трассировки считается завершённым.
  

### 5.6. Использование протокола ICMP при маршрутизации ###
**1) Запустить на r1 перехват сетевого трафика, проходящего через eth0 с помощью команды: `tcpdump -n -i eth0 icmp`**

**2) Пропинговать с ws11 несуществующий IP (например, `10.30.0.111`) с помощью команды: `ping -c 1 10.30.0.111`**
* Вывод на r1 \
  ![5.6_r1_tcpdump](screenshots/5.6_r1_tcpdump.png)
  

* Вывод на ws11 \
  ![5.6_ws11_not_exist_addr_ping](screenshots/5.6_ws11_not_exist_addr_ping.png)
  

## Part 6. Динамическая настройка IP с помощью DHCP ##
**Для r2 настроить в файле `/etc/dhcp/dhcpd.conf` конфигурацию службы DHCP:**
* Сначала скачаем `isc-dhcp-server` командой `sudo apt install isc-dhcp-server`
  

**1) Указать адрес маршрутизатора по-умолчанию, DNS-сервер и адрес внутренней сети.**
* Измененный файл `/etc/dhcp/dhcpd.conf` на r2 \
  ![6.1_r2_dhcp_conf](screenshots/6.1_r2_dhcp_conf.png)
  

**2) В файле resolv.conf прописать nameserver 8.8.8.8.**
* Измененный файл `/etc/resolv.conf` на r2 \
  ![6.2_r2_resolv_conf](screenshots/6.2_r2_resolv_conf.png)
  

**3) Перезагрузить службу DHCP командой `systemctl restart isc-dhcp-server`. Машину ws21 перезагрузить при помощи `reboot` и через `ip a` показать, что она получила адрес. Также пропинговать ws22 с ws21.**
* Перезагрузка службы DHCP на r2 \
  ![6.3_r2_dhcp_restart](screenshots/6.3_r2_dhcp_restart.png)
  

* Перезагружаем машину ws21 командой `reboot` и вызываем команду `ip a`, видим, что ip-адрес получен (`10.20.0.11`) \
  ![6.3_ws21_dynamic_ip](screenshots/6.3_ws21_dynamic_ip.png)
  

* Пинг ws22 с ws21 \
  ![6.3_ws21-ws22_ping](screenshots/6.3_ws21-ws22_ping.png)
  

**4) Указать MAC адрес у ws11, для этого в `etc/netplan/00-installer-config.yaml` надо добавить строки: `macaddress: 10:10:10:10:10:BA`, `dhcp4: true`**
* Измененный файл `/etc/netplan/00-installer-config.yaml` на ws11 \
  ![6.4_ws11_config_change](screenshots/6.4_ws11_config_change.png)
  

**Для r1 настроить аналогично r2, но сделать выдачу адресов с жесткой привязкой к MAC-адресу (ws11). Провести аналогичные тесты**
* Устанавливаем `ics-dhcp-server` на роутер r1 и вносим изменения в файл `/etc/dhcp/dhcpd.conf` \
  ![6.4_r1_dhcp_config_change](screenshots/6.4_r1_dhcp_config_change.png)
  

* Измененный файл `/etc/resolv.conf` на r1 \
  ![6.4_r1_resolv_conf](screenshots/6.4_r1_resolv_conf.png)
  

* Перезагружаем службу DHCP командой `systemctl restart isc-dhcp-server` \
  ![6.4_r1_dhcp_restart](screenshots/6.4_r1_dhcp_restart.png)
  

* Перезагружаем машину ws11 командой `reboot` и вызываем `ip a` (видим, что ip-адрес изменился на заданый нами - `10.10.0.51`) \
  ![6.4_ws11_dynamic_ip](screenshots/6.4_ws11_dynamic_ip.png)
  

* Пинг ws22 с машины ws11 \
  ![6.4_ws11-ws22_ping](screenshots/6.4_ws11-ws22_ping.png)
  

**5) Запросить с ws21 обновление ip адреса**
* `ip a` на ws21 до обновления \
  ![6.5_ws21_ip_before_update](screenshots/6.5_ws21_ip_before_update.png)
  

* Сначала вызовем команду `sudo dhclient enp0s8 -r` (флаг `-r` позволяет очистить список ip-адресов), после чего вызываем `sudo dhclient enp0s8` для обновления адреса
* `ip a` на ws21 после обновления \
  ![6.5_ws21_ip_after_update](screenshots/6.5_ws21_ip_after_update.png)
  

## Part 7. NAT ##
**1) В файле `/etc/apache2/ports.conf` на ws22 и r1 изменить строку `Listen 80` на `Listen 0.0.0.0:80`, то есть сделать сервер Apache2 общедоступным**
* Измененный файл на ws22 \
  ![7.1_ws22_apache_port_config](screenshots/7.1_ws22_apache_port_config.png)
  

* Измененный файл на r1 \
  ![7.1_r1_apache_port_config](screenshots/7.1_r1_apache_port_config.png)
  

**2) Запустить веб-сервер Apache командой `service apache2 start` на ws22 и r1**
* Выполнение команды на ws22 \
  ![7.2_ws22_apache_start](screenshots/7.2_ws22_apache_start.png)
  

* Выполнение команды на r1 \
  ![7.2_r1_apache_start](screenshots/7.2_r1_apache_start.png)
  

**3) Добавить в фаервол, созданный по аналогии с фаерволом из Части 4, на r2 следующие правила:**
1) Удаление правил в таблице filter - iptables -F
2) Удаление правил в таблице "NAT" - iptables -F -t nat
3) Отбрасывать все маршрутизируемые пакеты - iptables --policy FORWARD DROP
  

* Содержимое файла `/etc/firewall.sh` на r2 \
  ![7.3.1_r2_firewall](screenshots/7.3.1_r2_firewall.png)
  

* Запускаем firewall.sh на r2 \
  ![7.3.2_r2_firewall_start](screenshots/7.3.2_r2_firewall_start.png)
  

* Проверяем соединение между ws22 и r1 командой `ping` (не должно пинговаться) \
  ![7.3.3_r1-ws22_ping](screenshots/7.3.3_r1-ws22_ping.png)
  

**4) Разрешить маршрутизацию всех пакетов протокола ICMP**
* Добавляем ещё одно правило в `/etc/firewall.sh` на r2 \
  ![7.4.1_r2_icmp_forward_accept](screenshots/7.4.1_r2_icmp_forward_accept.png)
  

* Запускаем firewall.sh на r2 \
  ![7.4.2_r2_firewall_start](screenshots/7.4.2_r2_firewall_start.png)
  

* Проверяем соединение между ws22 и r1 командой `ping` (должно пинговаться) \
  ![7.4.3_r1-ws22_ping](screenshots/7.4.3_r1-ws22_ping.png)
  

**5) Включить SNAT, а именно маскирование всех локальных ip из локальной сети, находящейся за r2 (по обозначениям из Части 5 - сеть 10.20.0.0)**

**6) Включить DNAT на 8080 порт машины r2 и добавить к веб-серверу Apache, запущенному на ws22, доступ извне сети**
* Содержимое файла `/etc/firewall.sh` на r2 \
  ![7.6.1_r2_firewall_SNAT_DNAT](screenshots/7.6.1_r2_firewall_SNAT_DNAT.png)
  

* Запускаем firewall.sh на r2 \
  ![7.6.2_r2_firewall_start](screenshots/7.6.2_r2_firewall_start.png)
  

* Проверяем соединение по TCP для SNAT, для этого с ws22 подключиться к серверу Apache на r1 командой `telnet [адрес] [порт]` \
  ![7.6.3_ws22-r1_connection_check](screenshots/7.6.3_ws22-r1_connection_check.png)
  

* Проверить соединение по TCP для DNAT, для этого с r1 подключиться к серверу Apache на ws22 командой `telnet` (обращаться по адресу r2 и порту 8080) \
  ![7.6.4_r1-ws22_apache_connection_check](screenshots/7.6.4_r1-ws22_apache_connection_check.png)
  

## Part 8. Дополнительно. Знакомство с SSH Tunnels ##
**1) Запустить на r2 фаервол с правилами из Части 7**
* Содержимое файла `/etc/firewall.sh` на роутере r2 \
  ![8.1.1_r2_firewall_config](screenshots/8.1.1_r2_firewall_config.png)
  

* Запускаем `/etc/firewall.sh` \
  ![8.1.2_r2_firewall_start](screenshots/8.1.2_r2_firewall_start.png)
  

**2) Запустить веб-сервер Apache на ws22 только на localhost (то есть в файле `/etc/apache2/ports.conf` изменить строку `Listen 80` на `Listen localhost:80`)**
* Измененный файл `/etc/apache2/ports.conf` на ws22 \
  ![8.2.1_ws22_ports_conf](screenshots/8.2.1_ws22_ports_conf.png)
  

* Запускаем сервер Apache командой `service apache2 start` на ws22 \
  ![8.2.2_ws22_apache_start](screenshots/8.2.2_ws22_apache_start.png)
  

**3) Воспользоваться Local TCP forwarding с ws21 до ws22, чтобы получить доступ к веб-серверу на ws22 с ws21**
* Воспользуемся командой `ssh -L 2222:localhost:80 10.20.0.20` на машине ws21 \
  ![8.3.1_ws21_local_TCP_forwarding](screenshots/8.3.1_ws21_local_TCP_forwarding.png)
  

* Проверим, сработало ли подключение (переходим в другой терминал сочетанием клавиш `Alt` + `F2` и вводим команду `telnet 127.0.0.1 2222`) \
  ![8.3.2_ws21_connection_check](screenshots/8.3.2_ws21_connection_check.png)
  

**4) Воспользоваться Remote TCP forwarding c ws11 до ws22, чтобы получить доступ к веб-серверу на ws22 с ws11**
* Воспользуемся командой `ssh -R 2222:localhost:80 10.20.0.20` на машине ws21 \
  ![8.4.1_ws11_remote_TCP_forwarding](screenshots/8.4.1_ws11_remote_TCP_forwarding.png)
  

* Проверим, сработало ли подключение \
  ![8.4.2_ws11_connection_check](screenshots/8.4.2_ws11_connection_check.png)
  
