# Сборка ---------------------------------------

# В качестве базового образа для сборки используем gcc:latest
FROM gcc:latest as STAGE_BUILD

# Добавляем исходники в рабочую директорию
ADD . /app
# Установим рабочую директорию
WORKDIR /app

# Установим зависимости
RUN apt-get update && apt-get install -y build-essential cmake

# Выполним сборку и тестирование проекта
RUN cmake -S . -B build
RUN cmake --build build
RUN CTEST_OUTPUT_ON_FAILURE=1 cd build && ctest



# Запуск ---------------------------------------

# В качестве базового образа используем ubuntu:latest
FROM ubuntu:latest as STAGE_RUN

# Добавим пользователя, потому как в Docker по умолчанию используется root
# Запускать незнакомое приложение под root'ом неприлично :)
RUN groupadd -r sample && useradd -r -g sample sample
USER sample

# Установим рабочую директорию нашего приложения
WORKDIR /app

# Скопируем приложение со сборочного контейнера в рабочую директорию
COPY --from=STAGE_BUILD /app/build/src/bitset_example .

# Установим точку входа
ENTRYPOINT ["./bitset_example"]