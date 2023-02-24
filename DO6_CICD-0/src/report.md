## Part 1. Настройка gitlab-runner ##
* Устанавливаем gitlab-runner по интсрукции на сайте `https://docs.gitlab.com/runner/install/linux-repository.html` \
  ![1.0_add_gitlab_repo](screenshots/1.0_add_gitlab_repo.png)
  

* Устанавливаем с помощью `sudo apt-get install gitlab-runner` и проверяем версию командой `gitlab-runner --version` \
  ![1.1_gitlab-runner_version](screenshots/1.1_gitlab-runner_version.png)
  

* Регистрируем раннер командой `sudo gitlab-runner register` \
  ![1.2_register](screenshots/1.2_register.png)
  

## Part 2. Сборка ##
* Напишем `.gitlab-ci.yml` для сборки проекта `SimpleBash`, сам проект склонируем и положим в `src` \
  ![2.0_gitlab-ci](screenshots/2.0_gitlab-ci.png)
* Файлы после сборки будем сохранять в папке `artifacts`
  

* Запустим gitlab-runner командой `sudo gitlab-runner run` и запушим проект (также предварительно установили на ВМ `gcc` и `make` для сборки проекта) \
  ![2.1_push](screenshots/2.1_push.png)

  ![2.2_jobs_received](screenshots/2.2_jobs_received.png)
  

* Смотрим результат в gitlab \
  ![2.3_build_result](screenshots/2.3_build_result.png)

  ![2.4_cat_build_result](screenshots/2.4_cat_build_result.png)

  ![2.5_grep_build_result](screenshots/2.5_grep_build_result.png)
  

## Part 3. Тест кодстайла ##
* Первым делом установим `clang-format` на ВМ
  

* Дополним наш `.gitlab-ci.yml` следующими строками \
  ![3.0_yml_update](screenshots/3.0_yml_update.png)
  

* Попортим файл `s21_grep.c`, чтобы тест стиля кода выдавал ошибки, запушим и проверим pipeline \
  ![3.1_pipline](screenshots/3.1_pipline.png)
* Как видим, тест стиля grep не пройден, весь пайплайн зафейлен
  

* Посмотрим вывод для теста стиля grep (job: style_code_grep) \
  ![3.2_style_code_grep_fail](screenshots/3.2_style_code_grep_fail.png)
* Видим вывод утилиты `clang-format`
  

## Part 4. Интеграционные тесты ##
* Напишем скрипты тестов (папка src/tests)
  
* В `.gitlab-ci.yml` добавим следующие jobs (а также stage: test) \
  ![4.0_test_stage_and_jobs](screenshots/4.0_test_stage_and_jobs.png)
  

* Коммитим, пушим и видим, что появилась новая стадия в пайплайне. (Стадия не запускается, если зафейлен build или style)
  

## Part 5. Этап деплоя ##
* Первым делом поднимем вторую виртуальную машину, добавим обеим по адаптеру типа "Сетевой мост" и настроим `/etc/netplan/00-installer-config.yaml`.
  

* Настройки на обеих машинах \
  ![5.0_netplan_config](screenshots/5.0_netplan_config.png)
  

* Применили, проверили с помощью ping. Подключились к машине prod с cicdserver с помощью `ssh gonzalol@196.168.1.105`. Всё работает хорошо. \
  ![5.1_ssh](screenshots/5.1_ssh.png)
  

* Теперь добавим следующую стадию deploy в `.gitlab-ci.yml` и новый job \
  ![5.2_deploy](screenshots/5.2_deploy.png)
  

* Скрипт для копирования артефактов (вторая строка для того, чтобы показать, что файлы действительно скопировались на вторую машину) \
  ![5.3_scp](screenshots/5.3_scp.png)
  

* После коммита и пуша видим новую стадию deploy в пайплайне. Запуск возможен только вручную и только в случае успеха всех предыдущих стадий. \
  ![5.4_pipeline](screenshots/5.4_pipeline.png)
  

* Видим проблему, связанную с необходимостью введения пароля при подключении
  

* Меняем пароль от пользователя `gitlab-runner` командой `sudo passwd gitlab-runner` и переходим на него командой `su gitlab-runner` предварительно добавиви его в sudoers (команда `sudo visudo` и добавляем следующиее) \
  ![5.5_gitlab-runner_sudo](screenshots/5.5_gitlab-runner_sudo.png)
* Это позволит данному пользователю использовать sudo и не вводить пароль
  

* Теперь можем сгенерировать ключ `ssh-keygen` и командой `ssh-copy-id gonzalol@192.168.1.105` копируем ключ на машину, к которой будем подключаться по ssh.
  

* Далее пробуем подключиться командой `ssh gonzalol@192.168.1.105` и видим, что пароль теперь не требуется
  

* Снова пушим и после запуска deploy стадии снова сталкиваемся с проблемой - нет разрешения на копирование в директорию `/usr/local/bin`
  

* Решаем данную проблему, дав права на данную директорию пользователю `gitlab-runner` командой `sudo chmod -R 777 /usr/local/bin`
  

* Пробуем снова, всё работает \
  ![5.6_scp_result](screenshots/5.6_scp_result.png)
  

## Part 6. Дополнительно. Уведомления ##
* Первым делом создали своего бота с помощью `@BotFather`
  

* В каждом job были дополнены скрипты получением статуса выполнения и записью его в файл (и вынесены в отдельный файл, вместо написания непосредственно в `.gitlab-ci.yml`). 
* Как пример - скрип build стадии \
  ![6.0_status_message](screenshots/6.0_status_message.png)
  

* Сами файлы добавлены в artifacts. (также пример на основе стадии build) \
  ![6.1_artifacts](screenshots/6.1_artifacts.png)
  

* Добавлен stage `notify` и два job - на успешное и неуспешное выполнение пайплайна (в данном случае этапа ci, то есть стадия выполняется раньше стадии deploy). \
  ![6.2_notify_ci](screenshots/6.2_notify_ci.png)
  

* Скрипт в `notify` собирает все артефакты с записями о статусах работ и записывает их в общий файл, после чего передаёт его скрипту для отправки сообщения ботом.
* В сам скрипт сообщения от бота (взяли из materials) внесли изменения, а именно добавили переменные `TELEGRAM_BOT_TOKEN` и `TELEGRAM_USER_ID` (один от `@BotFather`, второй от `@myidbot`), а также изменили сообщение (первым параметром теперь ему требуется файл с сообщением, а не статус).
* Стадия `deploy` отдельно вызывает скрипты для получения сообщения от бота.
  
* Пример сообщений \
  ![6.3_notifications](screenshots/6.3_notifications.png)
