![Результат работы локального образа (ничем не отличается от образа с docker-hub)](https://raw.githubusercontent.com/bakafox/ynnpno/task2/output-docker.png)

*Результат работы локального образа (ничем не отличается от образа с docker-hub)*

### Как собрать и запустить в контейнере локальный образ в docker?

См. `DOCKER-RUN.SH`

### Как залить образ на docker-hub?

0. Подрубаем VPN
1. Создаём учётку на [Docker Hub](https://hub.docker.com)
2. Пишем `docker login`, логинимся
3. Собираем образ: `docker build -t bakafox/bitset .`
4. Пушим образ на Dockerhub (если не пушится, значит, VPN хреновый): `docker push bakafox/bitset`

### Как загрузить образ с docker-hub?

0. Не забываем подрубить VPN
1. Вытягиваем образ: `docker pull bakafox/bitset`
2. Собственно, запускаем: `docker run bakafox/bitset`
