![Слева — локально запущенный образ; Справа — образ с docker-hub.](README-IMG.png)

*Результаты работы локального образа и образа с docker-hub, соответственно.*

### Как собрать и запустить в контейнере локальный образ в docker?

См. `DOCKER-RUN.SH`

### Как залить образ на docker-hub?

0. Подрубаем VPN
1. Создаём учётку на [Docker Hub](https://hub.docker.com)
2. Пишем `docker login`, логинимся
3. Собираем образ: `docker build -t bakafox/bitset .`
4. Пушим образ на Dockerhub: `docker push bakafox/bitset`

### Как загрузить образ с docker-hub?

0. Не забываем подрубить VPN
1. Вытягиваем образ: `docker pull bakafox/bitset`
2. Собственно, запускаем: `docker run bakafox/bitset`
