## Part 1. Готовый докер ##

* Так как docker engine не установлен, устанавливаем его согласно инструкции на сайте `https://docs.docker.com/engine/install/ubuntu/`
  

* Проверим, успешна ли установка командой `sudo docker run hello-world`\
  ![1.1_docker_installation_check](screenshots/1.1_docker_installation_check.png)
  

* Выкачиваем официальный докер образ с nginx командой `sudo docker pull nginx` \
  ![1.2_pull_nginx](screenshots/1.2_pull_nginx.png)
  

* Проверим наличие докер образа через `docker images` \
  ![1.3_images](screenshots/1.3_images.png)
  

* Запустим докер образ командой `docker run -d [image_id|repository]` \
  ![1.4_image_run](screenshots/1.4_image_run.png)
  

* Проверим, что образ запустился командой `docker ps` \
  ![1.5_run_check](screenshots/1.5_run_check.png)
  

* Посмотрим информацию о контейнере командой `docker inspect [container_id|container_name]` \
  ![1.6_container_info](screenshots/1.6_container_info.png)
  

**По выводу команды определить размер контейнера, список замапленных портов и ip контейнера**
  

* Найдём размер контейнера (в байтах), для удобства воспользуемся командой `docker inspect distracted_newton -s | grep -i sizerw` \
  ![1.7_container_size](screenshots/1.7_container_size.png)
  

* Список замапленных портов с помощью `grep` достать не удалось (сами порты прописаны ниже), находим вручную \
  ![1.8_ports](screenshots/1.8_ports.png)
  

* Найдём ip-адрес контейнера, для удобства воспользуемся командой `docker inspect distracted_newton | grep -i ip` \
  ![1.9_container_ip](screenshots/1.9_container_ip.png)
  

* Остановим докер образ командой `docker stop [container_id|container_name]` и проверим, что он остановился командой `docker ps` \
  ![1.10_docker_stop](screenshots/1.10_docker_stop.png)
  

* Запустим докер с замапленными портами `80` и `443` на локальную машину командой `docker run -d -p 127.0.0.1:80:80 -p 127.0.0.1:443:443 nginx` и проверим, что он запустился командой `docker ps` \
  ![1.11_start_with_port_mapping](screenshots/1.11_start_with_port_mapping.png)
  

* Проверим, что в браузере по адресу `localhost:80` доступна стартовая страница nginx \
  ![1.12_browser_check](screenshots/1.12_browser_check.png)
  

* Перезапустим докер контейнер командой `docker restart [container_id|container_name]` и проверим, что он перезапустился командой `docker ps` \
  ![1.13_container_restart](screenshots/1.13_container_restart.png)
  

## Part 2. Операции с контейнером ##
**Прочитать конфигурационный файл nginx.conf внутри докер контейнера через команду exec**
  

* Для начала определим его местоположение командой `docker exec wonderful_nightingale find -type f 2>/dev/null | grep nginx.conf` \
  ![2.1_find_conf](screenshots/2.1_find_conf.png)
  

* Просмотрим файл командой `docker exec wonderful_nightingale cat /etc/nginx/nginx.conf` \
  ![2.2_cat_conf](screenshots/2.2_cat_conf.png)
  

* Создадим на локальной машине файл nginx.conf командой `touch nginx.conf` и проверим его наличие командой `ls` \
  ![2.3_conf_create](screenshots/2.3_conf_create.png)
  

* По ошибке файл был создан не в директории проекта, переходим в рабочую директорию и переносим файл туда \
  ![2.4_conf_move](screenshots/2.4_conf_move.png)
  

* Скопируем данные из файла `nginx.conf`, находящегося в контейнере, в наш файл и внесём изменения в блок `http` для настройки в нём по пути `/status` отдачи страницы статуса сервера nginx \
  ![2.5_nginx_conf_change](screenshots/2.5_nginx_conf_change.png) 
* Добавили блок `server` с необходимыми параметрами и закомментировали строку `include /etc/nginx/conf.d/*.conf;`, так как с ней статус не отображался
  

* Скопируем файл внутрь докер образа командой `docker cp nginx.conf wonderful_nightingale:/etc/nginx/nginx.conf` и перезапустим nginx внутри докер образа командой `docker exec wonderful_nightingale nginx -s reload` \
  ![2.6_conf_copy_restart](screenshots/2.6_conf_copy_restart.png)
  

* Проверяем, что по адресу `localhost:80/status` отображается страничка со статусом сервера nginx \
  ![2.7_browser_status](screenshots/2.7_browser_status.png)
  

* Экспортируем контейнер в файл container.tar командой `docker export -o container.tar wonderful_nightingale` \
  ![2.8_export](screenshots/2.8_export.png)
   

* Остановим контейнер и проверим, что он остановился \
  ![2.9_stop_container](screenshots/2.9_stop_container.png)
  

* Удаляем образ через `docker rmi [image_id|repository]`, не удаляя перед этим контейнеры \
  ![2.10_remove_nginx](screenshots/2.10_remove_nginx.png)
  

* Удаляем остановленный контейнер командой `docker rm wonderful_nightingale` и проверяем, что он удалился, командой `docker ps -a` \
  ![2.11_delete_container](screenshots/2.11_delete_container.png)
* Видим, что с прошлых заданий остались ещё контейнеры, удаляем их тем же способом, а также образ `hello_world`, оставшийся с проверки установки docker
  

* Импортируем контейнер обратно командой `docker import --change 'CMD ["nginx", "-g", "daemon off;"]' container.tar container` и проверим, что образ создался, командой `docker images` \
  ![2.12_backup](screenshots/2.12_backup.png)
  

* Теперь запускаем его командой `docker run -d -p 127.0.0.1:80:80 -p 127.0.0.1:443:443 container` и проверяем командой `docker ps` \
  ![2.13_backup_run](screenshots/2.13_backup_run.png)
  

* Проверим, что по адресу `localhost:80/status` отдается страничка со статусом сервера nginx \
  ![2.14_status_check](screenshots/2.14_status_check.png)
  
