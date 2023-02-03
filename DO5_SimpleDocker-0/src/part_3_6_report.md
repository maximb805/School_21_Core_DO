## Part 3. Мини веб-сервер ##

* Первым делом качаем образ nginx и запускаем контейнер с замапленным 81 портом \
  ![3.1_container_run](part_3_6_screenshots/3.1_container_run.png)
  

* Напишем минисервер на C и FastCGI, который будет возвращать страницу с надписью `Hello World!` \
  ![3.2_container_run](part_3_6_screenshots/3.1_server_c.png)
  

* Напишем свой nginx.conf, который будет проксировать все запросы с `81` порта на `127.0.0.1:8080` \
  ![3.3_nginx_conf](part_3_6_screenshots/3.3_nginx_conf.png)
  

* Скопируем сервер и nginx.conf в контейнер \
  ![3.4_files_cp](part_3_6_screenshots/3.4_files_cp.png)
  

* Для входа в контейнер воспользовался командой `docker exec -it zen_taussig bash`
* Для написания сервера потребовалось установить библиотеку libfcgi. Также установим её в контейнер + gcc для возможности компилирования С файлов и утилиту spawn-fcgi для запуска сервера.
* Все использованные команды после входа в контейнер: `apt update`, `apt upgrade`, `apt install gcc`, `apt install libfcgi-dev`, `apt install spawn-fcgi`
  
* Скомпилируем и запустим сервер с помощью `spawn-fcgi` и перезагрузим nginx\
  ![3.5_start_server](part_3_6_screenshots/3.5_start_server.png)
  

* Проверим, что страничка отображается по `localhost:81` \
  ![3.6_check_page](part_3_6_screenshots/3.6_check_page.png)
  

## Part 4. Свой докер ##
* Напишем свой Dockerfile, в качестве базового образа будем использовать последнюю версию nginx (указываем после инструкции `FROM`)
* После инструкции `COPY` указываем файлы, которые хотим копировать внутрь контейнера (нам нужен конфиг nginx и сервер, написанные нами в 3-ей части, а также скрипт `entrypoint.sh`, который будет выполнять роль entrypoint)
* После инструкции `RUN` указываем команды, которые необходимо выполнить после создания образа (используем для обновления и установки необходимых нам пакетов)
* И наконец, инструкция `CMD` указывает, какую команду необходимо выполнить после запуска контейнера (в данном случае это наш скрипт `entrypoint.sh`, в котором указаны команды для сборки и запуска нашего сервера и команда `nginx -g "daemon off;"`, необходимая для того, чтобы контейнер после запуска продолжал работать)
  

* Dockerfile \
  ![4.1_dockerfile](part_3_6_screenshots/4.1_dockerfile.png)
  

* entrypoint.sh \
  ![4.2_entrypoint](part_3_6_screenshots/4.2_entrypoint.sh.png)
  

* Соберём образ с помощью нашего Dockerfile, указав также имя и тег, командой `docker build -t part_4:ver1 .` \
  ![4.3_docker_build](part_3_6_screenshots/4.3_docker_build.png)
  

* Проверим наличие нашего образа командой `docker images` \
  ![4.4_image_check](part_3_6_screenshots/4.4_image_check.png)
  

* По заданию, нам необходимо запустить контейнер с маппиногом `81` порта на `80` и маппингом папки `./nginx` внутрь контейнера по адресу `/etc/nginx`
* Для маппинга папки нам необходмо сначала достать её из образа на локальную машину, поэтому запустим контейнер для экспорта командой `docker run -d part_4:ver1` и проверим командой `docker ps` \
  ![4.5_container_first_run](part_3_6_screenshots/4.5_container_first_run.png)
  

* Теперь остановим контейнер командой `docker stop affectionate_pare` и получим архив с файловой системой командой `docker export -o container.tar affectionate_pare` и удалим контейнер командой `docker rm affectionate_pare` \
  ![4.6_get_archive](part_3_6_screenshots/4.6_get_archive.png)
  

* Содержимое `/etc/nginx` в архиве \
  ![4.7_nginx_folder](part_3_6_screenshots/4.7_nginx_folder.png)
  

* Распаковываем командой `tar -xvf container.tar etc/nginx` \
  ![4.8_unpacking](part_3_6_screenshots/4.8_unpacking.png)
  

* Запускаем контейнер с маппингом порта и папки по заданию \
  ![4.9_container_run_with_mappings](part_3_6_screenshots/4.9_container_run_with_mappings.png)
  

* Проверяем в браузере, что по `localhost:80` нам доступна стартовая страничка nginx \
  ![4.10_browser_check_start](part_3_6_screenshots/4.10_browser_check_start.png)
  

* Добавим в `nginx.conf` (в тот, что в `src/nginx/`) проксирование странички `/status`, по которой будем отдавать статус сервера nginx \
  ![4.11_nginx_changed](part_3_6_screenshots/4.11_nginx_changed.png)
  

* Перезапустим докер образ `docker restart ` \
  ![4.12_docker_restart](part_3_6_screenshots/4.12_docker_restart.png)
  

* Проверим, что теперь по `localhost:80/status` отдается страничка со статусом nginx \
  ![4.13_status_check](part_3_6_screenshots/4.13_status_check.png)
  

## Part 5. Dockle ##
* Устанавливаем dockle \
  ![5.1_dockle_install](part_3_6_screenshots/5.1_dockle_install.png)
  

* Проверяем наш образ командой `sudo dockle part_4:ver1` \
  ![5.2_errors](part_3_6_screenshots/5.2_errors.png)
  

* Чтобы исправить `CIS-DI-0005` используем команду `export DOCKER_CONTENT_TRUST=1` \
  ![5.3_docker_content_trus](part_3_6_screenshots/5.3_docker_content_trus.png)
  

* Перепишем наш Dockerfile, чтобы избавиться от ошибок `DKL-DI-0005`, `CIS-DI-0001`, `CIS-DI-0006` и `CIS-DI-0008`:
* Добавим в инструкцию `RUN` команду `rm -rf /var/lib/apt/lists` для очистки кэша apt-get
* Добавим инструкцию `USER`, в которой укажем не root пользователя
* Добавим инструкцию `HEALTHCHECK`, проверяющую подключение к localhost (то есть работу нашего сервера nginx) каждые 5 минут
* Добавим в инструкцию `RUN` установку UID и GID директориям, которым требуется
  

* Измененный Dockerfile \
  ![5.4_dockerfile_changed](part_3_6_screenshots/5.4_dockerfile_changed.png)
* Также был изменен владелец на пользователя nginx всех директорий, к которым необходим доступ
  

* С ошибкой `CIS-DI-0010` нам не справиться, связана она с переменной среды `NGINX_GPGKEY`. Сам dockle предлагает нам её подавить с помощью ключа `--accept-key`.
  

* Cоздадим новый образ командой `docker build -t part_5:ver2 .` и проверим, что он создался, командой `docker images` \
  ![5.5_image_build](part_3_6_screenshots/5.5_image_build.png)
  

* Проверим образ командой `dockle --accept-key NGINX_GPGKEY part_5:ver2` \
  ![5.6_dockle_check](part_3_6_screenshots/5.6_dockle_check.png)
  

* Чтобы не подавлять ошибку, попробуем взять образ `ubuntu/nginx`
* Сначала создадим образ без копирования файла `nginx.conf`, чтобы получить измененный файл
  

* Измененный Dockerfile \
  ![5.7_change_image](part_3_6_screenshots/5.7_dockerfile_changed_v1.png)


* Далее запакуем файловую систему в архив и вытащим папку `/etc/nginx` в нашу рабочую директорию `src` для последующего маппинга (старую переименуем в `nginx_part_4`)
  

* Новый `nginx.conf` \
  ![5.8_nginx_new](part_3_6_screenshots/5.8_nginx_new.png)
  

* Внесём в него необходимые изменения по заданию части 4 \
  ![5.9_nginx_new_changed](part_3_6_screenshots/5.9_nginx_new_changed.png)
  

* Раскомментируем строку с копированием nginx.conf в Dockerfile \
  ![5.10_dockerfile_changed_final](part_3_6_screenshots/5.10_dockerfile_changed_final.png)
  

* Удалим все старые контейнеры и образы, и создадим новый (тег теперь - ver3) `sudo docker build -t part_5:ver3 .`
* Проверяем наличие образа \
  ![5.11_change_image](part_3_6_screenshots/5.11_change_image.png)
  

* Запустим контейнер командой `sudo docker run -d -p 127.0.0.1:80:81 -v $(pwd)/nginx/:/etc/nginx/ part_5:ver3`
* Проверяем командой `docker ps` \
  ![5.12_docker_run](part_3_6_screenshots/5.12_docker_run.png)
  

* Проверим в браузере странички `localhost:80` и `localhost:80/status` \
  ![5.13_browser_check](part_3_6_screenshots/5.13_browser_check.png)
  

* И наконец, проверим образ командой `dockle part_5:ver3` \
  ![5.14_dockle_done](part_3_6_screenshots/5.14_dockle_done.png)
  

## Part 6. Базовый Docker Compose ##
* Создадим папку `06`, где будем хранить Dockerfile, entrypoint.sh для запуска второго контейнера и папку nginx
  

* Dockerfile \
  ![6.1_second_dockerfile](part_3_6_screenshots/6.1_second_dockerfile.png)
  

* entrypoint.sh (вызываем команду, чтобы контейнер не останавливался после запуска) \
  ![6.2_second_entrypoint](part_3_6_screenshots/6.2_second_entrypoint.png)
  

* Напишем `docker-compose.yml` \
  ![6.3_docker_compose](part_3_6_screenshots/6.3_docker_compose.png)
  

* Впишем настройки проксирования в nginx.conf \
  ![6.4_part_6_nginx_conf](part_3_6_screenshots/6.4_part_6_nginx_conf.png)
  

* Удалим все старые контейнеры и образы
* Проверим, что ничего не осталось \
  ![6.5_delete_check](part_3_6_screenshots/6.5_delete_check.png)
  

* Введём команды `sudo docker-compose build` и `sudo docker-compose up` (предварительно установили `docker-compose`) \
  ![6.6_docker_compose_up](part_3_6_screenshots/6.6_docker_compose_up.png)
  

* Проверим, что в браузере по `localhost:80` отдается написанная нами страничка \
  ![6.7_browser_check](part_3_6_screenshots/6.7_browser_check.png)
  
